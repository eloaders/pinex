#ifndef ENUM_ELEMENTS_H
#define ENUM_ELEMENTS_H

// Enumerations for pages, elements, fonts, images
enum {
	E_PG_MAIN, 
	E_PG_EXTRA,
	E_PG_OPTIONS
     };
enum {
	E_ELEM_BOX,
	E_ELEM_BTN_REBOOT,
	E_ELEM_BTN_QUIT,
	E_ELEM_BTN_EXTRA,
	E_ELEM_BTN_POWEROFF,
	E_ELEM_BTN_OPTIONS,
	E_ELEM_BTN_SAVE_OPTIONS,
	E_ELEM_BTN_BACK,
	E_ELEM_BTN_BACK_OPTIONS,
	E_ELEM_BTN_MCPENABLE,
	E_ELEM_BTN_PRZ1,
	E_ELEM_BTN_PRZ2,
	E_ELEM_BTN_PRZ3,
	E_ELEM_BTN_PRZ4,
	E_ELEM_BTN_PRZ5,
	E_ELEM_BTN_PRZ6,
	E_ELEM_BTN_PRZ7,
	E_ELEM_BTN_PRZ8,
	E_ELEM_BTN_REMOTE_RELAY_E1,
	E_ELEM_BTN_REMOTE_RELAY_E2,
	E_ELEM_BTN_REMOTE_RELAY_E3,
	E_ELEM_BTN_REMOTE_RELAY_D1,
	E_ELEM_BTN_REMOTE_RELAY_D2,
	E_ELEM_BTN_REMOTE_RELAY_D3,
	E_ELEM_BTN_GPA0,
	E_ELEM_BTN_GPA1,
	E_ELEM_BTN_GPA2,
	E_ELEM_BTN_GPA3,
	E_ELEM_BTN_GPA4,
	E_ELEM_BTN_GPA5,
	E_ELEM_BTN_GPA6,
	E_ELEM_BTN_GPA7,
	E_ELEM_BTN_GPB0,
	E_ELEM_BTN_GPB1,
	E_ELEM_BTN_GPB2,
	E_ELEM_BTN_GPB3,
	E_ELEM_BTN_GPB4,
	E_ELEM_BTN_GPB5,
	E_ELEM_BTN_GPB6,
	E_ELEM_BTN_GPB7,
	E_ELEM_BTN_MCPDISABLE,
	E_ELEM_TXT_COUNT,
 	E_ELEM_TXT_CPUTEMP,
	E_ELEM_TXT_STEROWNIK,
	E_ELEM_PROGRESS,
	E_ELEM_PROGRESS1,
	E_ELEM_CHECK1,
	E_ELEM_RADIO1,
	E_ELEM_RADIO2,
	E_ELEM_TXT_APP_TITLE,
	E_RAMP,
	E_RADIAL,
	E_ELEM_MEM,
	E_ELEM_CPU,
	E_ELEM_SLIDER,
	E_ELEM_SLIDER2,
	E_ELEM_TEXTBOX,
	E_SCROLLBAR,
	E_ELEM_TXT_TIME,
	E_ELEM_ADC0,
	E_ELEM_ADC1,
	E_ELEM_ADC2,
	E_ELEM_ADC3,
	E_ELEM_ADC4,
	E_ELEM_ADC5,
	E_ELEM_ADC6,
	E_ELEM_ADC7,
	E_ELEM_TXT_ADC0,
	E_ELEM_TXT_ADC1,
	E_ELEM_TXT_ADC2,
	E_ELEM_TXT_ADC3,
	E_ELEM_TXT_ADC4,
	E_ELEM_TXT_ADC5,
	E_ELEM_TXT_ADC6,
	E_ELEM_TXT_ADC7,
	E_ELEM_GRAPH,
	E_ELEM_TEXT_MONGO
};

enum {
	E_FONT_BTN,
	E_FONT_TXT,
	E_FONT_TITLE,
	E_FONT_CPUTEMP,
	E_FONT_TEMP,
	E_FONT_DEJAVU_SANS_BOLD,
	E_FONT_HEAD,
	E_FONT_TXT_ADC,
	E_FONT_ALARM_CLOCK,
	E_FONT_LIQUID_CRYSTAL_NORMAL,
	E_FONT_LIQUID_CRYSTAL_BOLD,
	E_FONT_TITLE_TEMP
     };

enum {E_GROUP1};


#define I2C_BUS     "/dev/i2c-1"    //!< Device File for I2C Bus

// Defines for resources
#define MAX_PATH  	255
#define IMG_BKGND       "/res/pinex2.bmp"
#define CONF 		"pinex.conf"

float temp1=0,temp2=0,temp3=0,temp4=0,temp5=0,temp6=0,temp7=0,temp8=0;
double ds3231_temperature;
char  m_strImgBkgnd[MAX_PATH];



bool        	m_bQuit = false;
int 		pinex_conf();
// Free-running counter for display
unsigned    m_nCount = 0;

// Instantiate the GUI
#define MAX_PAGE		3
#define MAX_FONT		32
#define MAX_ELEM_PG_MAIN	101
#define MAX_ELEM_PG_EXTRA	101
#define MAX_ELEM_PG_OPTIONS	101

gslc_tsGui                  m_gui;
gslc_tsDriver               m_drv;
gslc_tsFont                 m_asFont[MAX_FONT];
gslc_tsPage                 m_asPage[MAX_PAGE];
gslc_tsElem                 m_asPageElem[MAX_ELEM_PG_MAIN];
gslc_tsElemRef              m_asPageElemRef[MAX_ELEM_PG_MAIN];
gslc_tsElem                 m_asExtraElem[MAX_ELEM_PG_EXTRA];
gslc_tsElemRef              m_asExtraElemRef[MAX_ELEM_PG_EXTRA];
gslc_tsElem                 m_asOptionsElem[MAX_ELEM_PG_OPTIONS];
gslc_tsElemRef              m_asOptionsElemRef[MAX_ELEM_PG_OPTIONS];

gslc_tsXGauge               m_sXGauge,m_sXGauge1,m_sXGauge10,m_sXGauge11;
gslc_tsXCheckbox            m_asXCheck[3];
gslc_tsXSlider              m_sXSlider,m_sXSlider2;
gslc_tsXGauge               m_sXRamp,m_sXRamp2,m_sXRadial;
gslc_tsXGauge		    m_sXADC0,m_sXADC1,m_sXADC2,m_sXADC3,m_sXADC4,m_sXADC5,m_sXADC6,m_sXADC7;

#define TBOX_ROWS           9
#define TBOX_COLS           25
gslc_tsXTextbox             m_sTextbox;
char                        m_acTextboxBuf[TBOX_ROWS*TBOX_COLS];

#define MAX_STR             100

// Enable frame/update rate reporting? (1 to enable, 0 to disable)
#define TEST_UPDATE_RATE     0

//For MCP module
#define AF_RESET	1
#define AF_BASE 	100
#define AF_GPA0		(AF_BASE + 0)
#define AF_GPA1		(AF_BASE + 1)
#define AF_GPA2		(AF_BASE + 2)
#define AF_GPA3		(AF_BASE + 3)
#define AF_GPA4		(AF_BASE + 4)
#define AF_GPA5		(AF_BASE + 5)
#define AF_GPA6		(AF_BASE + 6)
#define AF_GPA7		(AF_BASE + 7)
#define AF_GPB0		(AF_BASE + 8)
#define AF_GPB1		(AF_BASE + 9)
#define AF_GPB2		(AF_BASE + 10)
#define AF_GPB3		(AF_BASE + 11)
#define AF_GPB4		(AF_BASE + 12)
#define AF_GPB5		(AF_BASE + 13)
#define AF_GPB6		(AF_BASE + 14)
#define AF_GPB7		(AF_BASE + 15)
//end

#endif