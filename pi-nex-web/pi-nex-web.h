#define PI_NEX_WEB_H

#define I2C_BUS			"/dev/i2c-1"    //!< Device File for I2C Bus

#define _APP_NAME			"Pi-Nex" // Skrócona nazwa programu
#define _APP_NAME_MORE			"Sterownik Centralnego Ogrzewania" //Rozszerzona nazwa programu
#define _APP_VERSION			"1.0.0" //Wersja programu

#define _PAGE_SYSINFO_TITLE		"Informacje o platformie bazowej"
#define _PAGE_DASH_TITLE		"Panel informacyjny"
#define _PAGE_TEMPERATURE		"Czujniki Temperatury"
float temp1=0,temp2=0,temp3=0,temp4=0,temp5=0,temp6=0,temp7=0,temp8=0;
double ds3231_temperature;