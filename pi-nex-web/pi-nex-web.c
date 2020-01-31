//
//   Pi-Nex Sterownik C.O dla Raspberry Pi 0 1.1
//   Działa dzięki Mongoose - Embedded Web Server / Embedded Networking Library
// - https://www.cesanta.com
//
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

#include "mongoose/mongoose.h"
#include "bcm_host.h"

#include "interface/vmcs_host/vc_vchi_gencmd.h"

#include "pi-nex-web.h"
#include "cpu_usage.h"
#include "mem_info.h"
#include "DS3231.h"

#include <cjson/cJSON.h>

#include <linux/input.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <wiringPi.h>
#include <mcp23017.h>
#include <ds18b20.h>
//#include <pthread.h>
#include <interface/vcos/vcos.h>

#include <libgen.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <assert.h>
#include <signal.h>
#include <syslog.h>
#include <locale.h>
#include <ctype.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>

#include <dlfcn.h>
#include <inttypes.h>

#include "raspberry_pi_revision.h"
//-----------------------------------------------------------------------

typedef unsigned (*bhgpa)(void);

//-----------------------------------------------------------------------

uint32_t getPeripheralBaseFromBcmHost(void)
{
    uint32_t base = 0;

    void *dl = dlopen("/opt/vc/lib/libbcm_host.so", RTLD_NOW);

    if (dl != NULL)
    {
        bhgpa func = dlsym(dl, "bcm_host_get_peripheral_address");

        if (func != NULL)
        {
            base = func();
        }

        dlclose(dl);
    }

    return base;
}

//-----------------------------------------------------------------------

void * ds3231() {
	int ds3231_fd;
	int retval;
	
	while(1) {
		ds3231_fd = DS3231_open(I2C_BUS);

		if(ds3231_fd < 0) {
			exit(EXIT_FAILURE);
		}

		retval = DS3231_read_temperature(ds3231_fd, &ds3231_temperature);
	
		if(retval != 0) {
			exit(EXIT_FAILURE);
		}

		//printf("DS3231 Temperature: %+3.2lf 'C\n", ds3231_temperature);
		DS3231_close(ds3231_fd);

		usleep(10 * 400000); // s * microseconds
	}
	exit(EXIT_SUCCESS);
}

int read_temp(char *device_path){
    FILE *fp;
    char tmp[120],tmp2[120];
    char junk[120],crc[10],crc2[10];
    int value=0;
    if ((fp = fopen(device_path,"rt")) != (FILE *)NULL) {
	fgets(tmp,120,fp); /* Get first line w/ checksums */
        fgets(tmp2,120,fp); /* Get 2nd line w/ temp */
	sscanf(tmp,"%[^:]: %[^ ] %s\n",junk,crc,crc2);
        sscanf(tmp2,"%[^=]=%d\n",junk,&value);
	fclose(fp);
    }
    return value;
}

void * Monitor() {
	
	char *SENSOR[] = {
				"/sys/bus/w1/devices/28-000009ecfead/w1_slave", 
				"/sys/bus/w1/devices/28-000009ee0441/w1_slave",
				"/sys/bus/w1/devices/28-0317316b1eff/w1_slave",
				"/sys/bus/w1/devices/28-000009edbff6/w1_slave",
				"/sys/bus/w1/devices/28-000009ee2891/w1_slave",
				"/sys/bus/w1/devices/28-0317316c9aff/w1_slave",
				"/sys/bus/w1/devices/28-000009edd921/w1_slave",
				"/sys/bus/w1/devices/28-0317310a1cff/w1_slave",
	};

	while(1) {
		temp1=read_temp(SENSOR[0]);
		temp2=read_temp(SENSOR[1]);
		temp3=read_temp(SENSOR[2]);		
		temp4=read_temp(SENSOR[3]);
		temp5=read_temp(SENSOR[4]);		
		temp6=read_temp(SENSOR[5]);
		temp7=read_temp(SENSOR[6]);
		temp8=read_temp(SENSOR[7]);
	}
	pthread_exit(NULL);
}

struct device_settings {
  char setting1[100];
  char setting2[100];
};

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;
static struct device_settings s_settings = {"value1", "value2"};

static void handle_save(struct mg_connection *nc, struct http_message *hm) {
  // Get form variables and store settings values
  mg_get_http_var(&hm->body, "setting1", s_settings.setting1,
                  sizeof(s_settings.setting1));
  mg_get_http_var(&hm->body, "setting2", s_settings.setting2,
                  sizeof(s_settings.setting2));

  // Send response
  mg_http_send_redirect(nc, 302, mg_mk_str("/"), mg_mk_str(NULL));
}

static void handle_relay_remote(struct mg_connection *nc, struct http_message *hm) {
	char relay_remote[50];
	/* JSON Apply Merge tests: */
	/*const char *ENABLE_REMOTE_RELAY[3][2] =
	{
	    {"1", "5264691"},
	    {"2", "5264835"},
	    {"3", "5265155"}
	};
	const char *DISABLE_REMOTE_RELAY[3][2] =
	{
	    {"1", "5264700"},
	    {"2", "5264844"},
	    {"3", "5265164"}
	};*/
	
}

static void handle_relay(struct mg_connection *nc, struct http_message *hm) {
	char relay[50], relay_method[50];
	char API_RELAY[1000];
	int RELAY[] = {0,21,22,23,24,25,26,27,28};

	mg_get_http_var(&hm->body, "relay", relay, sizeof(relay));
	mg_get_http_var(&hm->body, "relay_method", relay_method, sizeof(relay_method));
	
	mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
	wiringPiSetup();

		if (strcmp(relay_method, "set") == 0) {

			if (digitalRead(RELAY[atoi(relay)]) == 0)
			{		
				pinMode(RELAY[atoi(relay)], OUTPUT);
				digitalWrite(RELAY[atoi(relay)], 1);
			}
			else
			{		
				pinMode(RELAY[atoi(relay)], OUTPUT);
				digitalWrite(RELAY[atoi(relay)], 0);
			}
			mg_printf_http_chunk(nc, "{ \"state\": %d }", digitalRead(RELAY[atoi(relay)]));

		} else if (strcmp(relay_method, "get") == 0) {

			sprintf(API_RELAY,"{						"
    					"	\"Relays\": [				"
      					"	{					"
        				"		\"name\": \"Jane Doe\",		"
        				"		\"id\": \"1\",			"
        				"		\"comment\": \"spouse\",	"
					"		\"function\": \"spouse\",	"
					"		\"state\": \"%d\"		"
      					"	},					"
      					"	{					"
        				"		\"name\": \"Jane Doe\",		"
        				"		\"id\": \"2\",			"
        				"		\"comment\": \"spouse\",	"
					"		\"function\": \"spouse\",	"
					"		\"state\": \"%d\"		"
      					"	},					"
					"	{					"
        				"		\"name\": \"Jane Doe\",		"
        				"		\"id\": \"3\",			"
        				"		\"comment\": \"spouse\",	"
					"		\"function\": \"spouse\",	"
					"		\"state\": \"%d\"		"
      					"	},					"
      					"	{					"
        				"		\"name\": \"Jane Doe\",		"
        				"		\"id\": \"4\",			"
        				"		\"comment\": \"spouse\",	"
					"		\"function\": \"spouse\",	"
					"		\"state\": \"%d\"		"
      					"	},					"
      					"	{					"
        				"		\"name\": \"Jane Doe\",		"
        				"		\"id\": \"5\",			"
        				"		\"comment\": \"spouse\",	"
					"		\"function\": \"spouse\",	"
					"		\"state\": \"%d\"		"
      					"	},					"
      					"	{					"
        				"		\"name\": \"Jane Doe\",		"
        				"		\"id\": \"6\",			"
        				"		\"comment\": \"spouse\",	"
					"		\"function\": \"spouse\",	"
					"		\"state\": \"%d\"		"
      					"	},					"
      					"	{					"
        				"		\"name\": \"Jane Doe\",		"
        				"		\"id\": \"7\",			"
        				"		\"comment\": \"spouse\",	"
					"		\"function\": \"spouse\",	"
					"		\"state\": \"%d\"		"
      					"	},					"
      					"	{					"
        				"		\"name\": \"Jane Doe\",		"
        				"		\"id\": \"8\",			"
        				"		\"comment\": \"spouse\",	"
					"		\"function\": \"spouse\",	"
					"		\"state\": \"%d\"		"
      					"	}					"
    					"	]					"
					"}"
					, digitalRead(RELAY[1])
					, digitalRead(RELAY[2])
					, digitalRead(RELAY[3])
					, digitalRead(RELAY[4])
					, digitalRead(RELAY[5])
					, digitalRead(RELAY[6])
					, digitalRead(RELAY[7])
					, digitalRead(RELAY[8]));

			mg_printf_http_chunk(nc, "%s", API_RELAY);
		}

  	mg_send_http_chunk(nc, "", 0);
}

int get_rpi_cpu_temp()
{
	int temp;
	FILE *fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
	if (fp == NULL)
		return -1;
	fscanf(fp, "%d\n", &temp);
	fclose(fp);

	return temp / 1000;
}

static void handle_api(struct mg_connection *nc) {
	char                API_PINEX[1000];
	
	sprintf(API_PINEX,"{\n"
			  "\"TEMP1\": \"%.1f\",\n"
		          "\"TEMP1_NAME\": \"Temperatura zasilania CO\",\n"
		          "\"TEMP2\": \"%.1f\",\n"
		          "\"TEMP2_NAME\": \"Temperatura powrotu CO\",\n"
			  "\"TEMP1_2_SHORT_NAME\": \"Ogrzewanie CO\",\n"
		          "\"TEMP3\": \"%.1f\",\n"
		          "\"TEMP3_NAME\": \"Temperatura zasilania zasobnika C.W.U\",\n"
		          "\"TEMP4\": \"%.1f\",\n"
		          "\"TEMP4_NAME\": \"Temperatura powrotu zasobnika C.W.U\",\n"
			  "\"TEMP3_4_SHORT_NAME\": \"Zasobnik C.W.U\",\n"
		          "\"TEMP5\": \"%.1f\",\n"
		          "\"TEMP5_NAME\": \"Zasilanie Ogrzewania Podłogowego\",\n"
		          "\"TEMP6\": \"%.1f\",\n"
		          "\"TEMP6_NAME\": \"Powrót ogrzewania Podłogowego\",\n"
			  "\"TEMP5_6_SHORT_NAME\": \"Ogrzewanie Podłogowe\",\n"
			  "\"DS3231\": \"%+3.2lf °C\",\n"
			  "\"CPU_TEMP\": \"%i °C\"\n"
			  "}"
			, temp1 / 1000
			, temp2 / 1000
			, temp3 / 1000
			, temp4 / 1000
			, temp5 / 1000
			, temp6 / 1000
			, ds3231_temperature
			, get_rpi_cpu_temp());
  
	mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");

	mg_printf_http_chunk(nc, "%s", API_PINEX);

	mg_send_http_chunk(nc, "", 0);
}

static void handle_get_cpu_usage(struct mg_connection *nc) {
  // Generate random value, as an example of changing CPU usage
  // Getting real CPU usage depends on the OS.
  int cpu_usage = getCPUPercentage();

  // Use chunked encoding in order to avoid calculating Content-Length
  mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");

  // Output JSON object which holds CPU usage data
  mg_printf_http_chunk(nc, "{ \"resultint\": %d }", cpu_usage);

  // Send empty chunk, the end of response
  mg_send_http_chunk(nc, "", 0);
}

static void handle_get_mem_usage_percentage(struct mg_connection *nc) {
  // Generate random value, as an example of changing CPU usage
  // Getting real CPU usage depends on the OS.
  int mem_usage_percentage = getMemoryPercentage();

  // Use chunked encoding in order to avoid calculating Content-Length
  mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");

  // Output JSON object which holds CPU usage data
  mg_printf_http_chunk(nc, "{ \"mem_usage_percentage\": %d }", mem_usage_percentage);

  // Send empty chunk, the end of response
  mg_send_http_chunk(nc, "", 0);
}

static void handle_get_mq7_sensor(struct mg_connection *nc) {
	FILE* mq7;
	
	unsigned short int 	x = 0;
	int			volt[8];
	double			frmv[8];
	char			ADC_DATA[1000];
	char *adc [] =
  	{
  		"/sys/bus/iio/devices/iio:device0/in_voltage0_raw", 
		"/sys/bus/iio/devices/iio:device0/in_voltage1_raw", 
		"/sys/bus/iio/devices/iio:device0/in_voltage2_raw", 
		"/sys/bus/iio/devices/iio:device0/in_voltage3_raw", 
		"/sys/bus/iio/devices/iio:device0/in_voltage4_raw", 
		"/sys/bus/iio/devices/iio:device0/in_voltage5_raw", 
		"/sys/bus/iio/devices/iio:device0/in_voltage6_raw", 
		"/sys/bus/iio/devices/iio:device0/in_voltage7_raw"
	};
	//MQ-7
	for (x = 0; x < 7; x++)
	{
		mq7 = fopen(adc[x], "r"); 
		assert(mq7 != NULL);
		fscanf(mq7, "%d", &volt[x]);
		frmv[x] = (volt[x] * 100) / 1023.0;
		fclose(mq7);
	}

	sprintf(ADC_DATA,"{"
			"\n\"ADC0_RAW\": \"%d\","
			"\n\"ADC0_PERCENTAGE\": \"%.0f\","
			"\n\"ADC1_RAW\": \"%d\","
			"\n\"ADC1_PERCENTAGE\": \"%.0f\","
			"\n\"ADC2_RAW\": \"%d\","
			"\n\"ADC2_PERCENTAGE\": \"%.0f\","
			"\n\"ADC3_RAW\": \"%d\","
			"\n\"ADC3_PERCENTAGE\": \"%.0f\","
			"\n\"ADC4_RAW\": \"%d\","
			"\n\"ADC4_PERCENTAGE\": \"%.0f\","
			"\n\"ADC5_RAW\": \"%d\","
			"\n\"ADC5_PERCENTAGE\": \"%.0f\","
			"\n\"ADC6_RAW\": \"%d\","
			"\n\"ADC6_PERCENTAGE\": \"%.0f\","
			"\n\"ADC7_RAW\": \"%d\","
			"\n\"ADC7_PERCENTAGE\": \"%.0f\""
			"\n}"
			, volt[0]
			, frmv[0]
			, volt[1]
			, frmv[1]
			, volt[2]
			, frmv[2]
			, volt[3]
			, frmv[3]
			, volt[4]
			, frmv[4]
			, volt[5]
			, frmv[5]
			, volt[6]
			, frmv[6]
			, volt[7]
			, frmv[7]);

  // Use chunked encoding in order to avoid calculating Content-Length
  mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");

  // Output JSON object which holds CPU usage data
  mg_printf_http_chunk(nc, "%s", ADC_DATA);

  // Send empty chunk, the end of response
  mg_send_http_chunk(nc, "", 0);
}

static void handle_get_piinfo(struct mg_connection *nc) {
	char                API_PIINFO[1000];
	char		    bcm_host_peripheralBase_match[100];

	RASPBERRY_PI_INFO_T info;
	struct utsname uninfo;
	uint32_t base = getPeripheralBaseFromBcmHost();
	
	if (uname (&uninfo) < 0)
    	{
		fprintf(stderr, "cannot get system name: %s\n", strerror (errno));
    		exit(1);
    	}
	

        if (base == 0)
        {
		sprintf(bcm_host_peripheralBase_match," function not found in bcm_host library");
        }
        else if (base != info.peripheralBase)
        {
		sprintf(bcm_host_peripheralBase_match," does not match base from bcm_host");
        }
        else
        {
		sprintf(bcm_host_peripheralBase_match,"  matches base from bcm_host");
        };

	if (getRaspberryPiInformation(&info) > 0)
    	{
	sprintf(API_PIINFO,"{"
			"\n\"processor\": \"%s\","
			"\n\"memory\": \"%s\","
			"\n\"i2cDevice\": \"%s\","
		       	"\n\"model\": \"%s\","
		       	"\n\"manufacturer\": \"%s\","
		       	"\n\"pcb_revision\": \"%d\","
		       	"\n\"warranty_void\": \"%s\","
		       	"\n\"revision\": \"%04x\","
		       	"\n\"peripheral_base\": \"0x%"PRIX32"\","
			"\n\"peripheral_base_match\": \"Peripheral base %s\","
			"\n\"uname_sysname\": \"%s\","
			"\n\"uname_nodename\": \"%s\","
			"\n\"uname_release\": \"%s\","
			"\n\"uname_version\": \"%s\","
			"\n\"uname_machine\": \"%s\""
			"\n}"
			, raspberryPiProcessorToString(info.processor)
			, raspberryPiMemoryToString(info.memory)
			, raspberryPiI2CDeviceToString(info.i2cDevice)
			, raspberryPiModelToString(info.model)
			, raspberryPiManufacturerToString(info.manufacturer)
			, info.pcbRevision
			, (info.warrantyBit) ? "yes" : "no"
			, info.revisionNumber
			, info.peripheralBase
			, bcm_host_peripheralBase_match
			, uninfo.sysname
			, uninfo.nodename
			, uninfo.release
			, uninfo.version
			, uninfo.machine
		);
  	}

	mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");

	mg_printf_http_chunk(nc, "%s", API_PIINFO);

	mg_send_http_chunk(nc, "", 0);
}

static void handle_ssi_call(struct mg_connection *nc, const char *param) {
	if (strcmp(param, "app_name") == 0) {
		mg_printf_html_escape(nc, "%s", _APP_NAME);
	} else if (strcmp(param, "app_name_more") == 0) {
		mg_printf_html_escape(nc, "%s", _APP_NAME_MORE);
	} else if (strcmp(param, "app_version") == 0) {
		mg_printf_html_escape(nc, "%s", _APP_VERSION);
	} else if (strcmp(param, "page_sysinfo_title") == 0) {
		mg_printf_html_escape(nc, "%s", _PAGE_SYSINFO_TITLE);
	} else if (strcmp(param, "page_dash_title") == 0) {
		mg_printf_html_escape(nc, "%s", _PAGE_DASH_TITLE);
	} else if (strcmp(param, "page_temperature") == 0) {
		mg_printf_html_escape(nc, "%s", _PAGE_TEMPERATURE);
	}
}

static void handle_vchi_command(struct mg_connection *nc, struct http_message *hm) {
	char		vchi_command[50], vchi_method[50];
    	int vchi_command_check = mg_get_http_var(&hm->body, "vchi_command", vchi_command, sizeof(vchi_command));
	int vchi_method_check = mg_get_http_var(&hm->body, "vchi_method", vchi_method, sizeof(vchi_method));

	char response[80];
	VCHI_INSTANCE_T vchi_instance;
	VCHI_CONNECTION_T *vchi_connection = NULL;

	if (vchi_command_check > 0 && vchi_method_check > 0) { // Sprawdzenie czy w metodzie POST zawarte są obie wartości
		
		vcos_init();
		if ( vchi_initialise( &vchi_instance ) != 0)
		{
			sprintf(response, "VCHI initialization failed");
		}
		//create a vchi connection
		if ( vchi_connect( NULL, 0, vchi_instance ) != 0)
		{
			sprintf(response, "VCHI connection failed");
		}
			vc_vchi_gencmd_init(vchi_instance, &vchi_connection, 1 );
		
		/* lista możliwych akcji dla komendy VCHI.
		/  Poniżej lista sprawdzająca daną komendę,
		/  Jeśli komenda się zgadza, następuje jej uruchomienie.
		*/

		/* Instrukcja włączenia lub wyłączenia aktywności ekranu
		/  Gdy ekran nie jest aktywny = Następuje jego włączenie	
		/  Gdy ekran jest aktywny = Następuje jego wyłączenie
		/  Z poziomu interfejsu web, zarządzanie zrealizowane jest po przez przycisk
		/	który wedle aktywnoci ekranu zmienia swój kolor.
		*/
		if (strcmp(vchi_command, "display_power") == 0) {
			
			vc_gencmd(response, sizeof response, "display_power");
			response[sizeof(response) - 1] = '\n';						
			if (strcmp(vchi_method, "set") == 0)
			{
				if (strcmp(response, "display_power=0") == 0) 
				{
					vc_gencmd_send("%s", "display_power 1");
          				//printf( "ON vc_gencmd_send returned %d, Response= %s\n", ret , response);	
				} 
				if (strcmp(response, "display_power=1") == 0) 
				{
					vc_gencmd_send("%s", "display_power 0");
          				//printf( "OFF vc_gencmd_send returned %d, Response= %s\n", ret , response);
				}
				vc_gencmd(response, sizeof response, "display_power");
				response[sizeof(response) - 1] = '\n';	
			} else if (strcmp(vchi_method, "get") == 0) {
				vc_gencmd(response, sizeof response, "display_power");
				response[sizeof(response) - 1] = '\n';	
			}	
		}
		/* Koniec Instrukcji włączenia lub wyłączenia aktywności ekranu*/	
		vc_gencmd_stop();

    		//close the vchi connection
    		if ( vchi_disconnect( vchi_instance ) != 0)
    		{
        		sprintf(response, "VCHI disconnect failed");
    		}	
	}

	

	mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");

	mg_printf_http_chunk(nc, "{\"vchi_response\": \"%s\"}", response);

	mg_send_http_chunk(nc, "", 0);
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
  struct http_message *hm = (struct http_message *) ev_data;

  switch (ev) {
    case MG_EV_HTTP_REQUEST:
      if (mg_vcmp(&hm->uri, "/save") == 0) {
        	handle_save(nc, hm);
      	} else if (mg_vcmp(&hm->uri, "/get_cpu_usage") == 0) {
        	handle_get_cpu_usage(nc);
	} else if (mg_vcmp(&hm->uri, "/get_mem_usage_percentage") == 0) {
        	handle_get_mem_usage_percentage(nc);
	} else if (mg_vcmp(&hm->uri, "/get_mq7_sensor") == 0) {
        	handle_get_mq7_sensor(nc);
	} else if (mg_vcmp(&hm->uri, "/get_piinfo") == 0) {
        	handle_get_piinfo(nc);
	} else if (mg_vcmp(&hm->uri, "/vchi_command") == 0) {
        	handle_vchi_command(nc, hm);
	} else if (mg_vcmp(&hm->uri, "/api_v1") == 0) {
        	handle_api(nc);
	} else if (mg_vcmp(&hm->uri, "/set_relay") == 0) {
        	handle_relay(nc, hm);
	} else if (mg_vcmp(&hm->uri, "/set_relay_remote") == 0) {
        	handle_relay_remote(nc, hm);
      	} else {
        	mg_serve_http(nc, hm, s_http_server_opts);  // Serve static content
      }
      break;
    case MG_EV_SSI_CALL:
      handle_ssi_call(nc, ev_data);
      break;
    default:
      break;
  }
}

/*static void push_data_to_all_websocket_connections(struct mg_mgr *m) {
  struct mg_connection *c;
  int memory_usage = (double) rand() / RAND_MAX * 100.0;

  for (c = mg_next(m, NULL); c != NULL; c = mg_next(m, c)) {
    if (c->flags & MG_F_IS_WEBSOCKET) {
      mg_printf_websocket_frame(c, WEBSOCKET_OP_TEXT, "%d", memory_usage);
    }
  }
}
*/
int main(void) {
	struct mg_mgr mgr;
	struct mg_connection *nc;
	
	cs_stat_t st;
	bcm_host_init();

		VCOS_STATUS_T sthread1;
		VCOS_STATUS_T sthread2;
		VCOS_THREAD_T thread1;
		VCOS_THREAD_T thread2;
	   	VCOS_THREAD_ATTR_T attrs;
	   	vcos_thread_attr_init(&attrs);
	   	vcos_thread_attr_settimeslice(&attrs,1);
	
		sthread1 = vcos_thread_create(&thread1, "thread1", &attrs, Monitor, (void*)0);
		vcos_assert(sthread1 == VCOS_SUCCESS);
		sthread2 = vcos_thread_create(&thread2, "thread2", &attrs, ds3231, (void*)0);
   		vcos_assert(sthread2 == VCOS_SUCCESS);

  mg_mgr_init(&mgr, NULL);
  nc = mg_bind(&mgr, s_http_port, ev_handler);
  if (nc == NULL) {
    fprintf(stderr, "Cannot bind to %s\n", s_http_port);
    exit(1);
  }

  // Set up HTTP server parameters
  mg_set_protocol_http_websocket(nc);
  s_http_server_opts.document_root = "/home/pi/PINEX/pi-nex-web/gentelella/production";  // Set up web root directory
  s_http_server_opts.ssi_pattern = "**.shtml$|**.html$";
  s_http_server_opts.auth_domain = "pinex.local:8000";
  s_http_server_opts.enable_directory_listing = "yes";

  if (mg_stat(s_http_server_opts.document_root, &st) != 0) {
    fprintf(stderr, "%s", "Cannot find web_root directory, exiting\n");
    exit(1);
  }

  printf("Starting web server on port %s\n", s_http_port);
  for (;;) {
    static time_t last_time;
    time_t now = time(NULL);
    mg_mgr_poll(&mgr, 1000);
    if (now - last_time > 0) {
      //push_data_to_all_websocket_connections(&mgr);
      last_time = now;
    }
  }
  bcm_host_deinit();
  mg_mgr_free(&mgr);

  return 0;
}
