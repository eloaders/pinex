//
//   Pi-Nex Sterownik C.O dla Raspberry Pi 0 1.1
//   Działa dzięki GUIslice Library
// - Calvin Hass
// - https://www.impulseadventure.com/elec/guislice-gui.html
// - https://github.com/ImpulseAdventure/GUIslice
//
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

#include "config.h"
#include "GUIslice.c"
#include "GUIslice_ex.h"
#include "GUIslice_drv.h"
#include "bcm_host.h"

#include "interface/vmcs_host/vc_vchi_gencmd.h"

#include "pi-nex.h"
#include "cpu_usage.h"
#include "mem_info.h"
#include "DS3231.h"

#include <linux/input.h>
#include <sys/types.h>
#include <libconfig.h>
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
#include <config.h>
#include <locale.h>
#include <ctype.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
// Configure environment variables suitable for display
// - These may need modification to match your system
//   environment and display type
// - Defaults for GSLC_DEV_FB and GSLC_DEV_TOUCH are in GUIslice_config.h
// - Note that the environment variable settings can
//   also be set directly within the shell via export
//   (or init script).
//   - eg. export TSLIB_FBDEVICE=/dev/fb1
void UserInitEnv()
{
#if defined(DRV_DISP_SDL1) || defined(DRV_DISP_SDL2)
  setenv((char*)"FRAMEBUFFER",GSLC_DEV_FB,1);
  setenv((char*)"SDL_FBDEV",GSLC_DEV_FB,1);
  setenv((char*)"SDL_VIDEODRIVER",GSLC_DEV_VID_DRV,1);
  //setenv((char*)"SDL1_VIDEODRIVER","dispmanx",1);
#endif
#if defined(DRV_TOUCH_TSLIB)
  setenv((char*)"TSLIB_FBDEVICE","/dev/fb0",0);
  setenv((char*)"TSLIB_TSDEVICE","/dev/input/event2",0);
  setenv((char*)"TSLIB_CALIBFILE",(char*)"/etc/pointercal",0);
  setenv((char*)"TSLIB_CONFFILE",(char*)"/etc/ts.conf",0);
  setenv((char*)"TSLIB_PLUGINDIR",(char*)"/usr/local/lib/ts",0);
#endif
}

// Define debug message function
static int16_t DebugOut(char ch) { fputc(ch,stderr); return 0; }

bool CbBtnPRZ(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY)
{
	gslc_tsGui*     pGui      = (gslc_tsGui*)(pvGui);
	gslc_tsElemRef* pElemRef  = (gslc_tsElemRef*)(pvElemRef);
	gslc_tsElem*    pElem     = gslc_GetElemFromRef(pGui,pElemRef);
	int16_t nElemId = pElem->nId;
						//GPIO	|BCM
	const int RELAY1 = 21; 	// 1	|18
	const int RELAY2 = 22; 	// 3	|27
	const int RELAY3 = 23; 	// 3	|22
	const int RELAY4 = 24; 	// 4	|23
	const int RELAY5 = 25; 	// 5	|24
	const int RELAY6 = 26; 	// 6	|25
	const int RELAY7 = 27; 	// 6	|25
	const int RELAY8 = 28; 	// 6	|25

	if (eTouch == GSLC_TOUCH_UP_IN) {
		switch (nElemId) 
		{
			case E_ELEM_BTN_PRZ1:
				
				if (digitalRead(RELAY1) == 0)
				{		
					pinMode(RELAY1, OUTPUT);
					digitalWrite(RELAY1, 1);
					printf("\n Przekaźnik jest aktualnie wyłączony \n");
				}
				else
				{	
					pinMode(RELAY1, OUTPUT);
					digitalWrite(RELAY1, 0);
					printf("\n Przekaźnik jest aktualnie włączony \n");
				}
				return true;
			case E_ELEM_BTN_PRZ2:
				
				if (digitalRead(RELAY2) == 0)
				{		
					pinMode(RELAY2, OUTPUT);
					digitalWrite(RELAY2, 1);
					printf("\n Przekaźnik jest aktualnie wyłączony \n");
				}
				else
				{	
					pinMode(RELAY2, OUTPUT);
					digitalWrite(RELAY2, 0);
					printf("\n Przekaźnik jest aktualnie włączony \n");
				}
				return true;
			case E_ELEM_BTN_PRZ3:
				
				if (digitalRead(RELAY3) == 0)
				{		
					pinMode(RELAY3, OUTPUT);
					digitalWrite(RELAY3, 1);
					printf("\n Przekaźnik jest aktualnie wyłączony \n");
				}
				else
				{	
					pinMode(RELAY3, OUTPUT);
					digitalWrite(RELAY3, 0);
					printf("\n Przekaźnik jest aktualnie włączony \n");
				}	
				return true;
			case E_ELEM_BTN_PRZ4:
				
				if (digitalRead(RELAY4) == 0)
				{		
					pinMode(RELAY4, OUTPUT);
					digitalWrite(RELAY4, 1);
					printf("\n Przekaźnik jest aktualnie wyłączony \n");
				}
				else
				{	
					pinMode(RELAY4, OUTPUT);
					digitalWrite(RELAY4, 0);
					printf("\n Przekaźnik jest aktualnie włączony \n");
				}	
				return true;
			case E_ELEM_BTN_PRZ5:
				
				if (digitalRead(RELAY5) == 0)
				{		
					pinMode(RELAY5, OUTPUT);
					digitalWrite(RELAY5, 1);
					printf("\n Przekaźnik jest aktualnie wyłączony \n");
				}
				else
				{	
					pinMode(RELAY5, OUTPUT);
					digitalWrite(RELAY5, 0);
					printf("\n Przekaźnik jest aktualnie włączony \n");
				}	
				return true;
			case E_ELEM_BTN_PRZ6:
				
				if (digitalRead(RELAY6) == 0)
				{		
					pinMode(RELAY6, OUTPUT);
					digitalWrite(RELAY6, 1);
					printf("\n Przekaźnik jest aktualnie wyłączony \n");
				}
				else
				{	
					pinMode(RELAY6, OUTPUT);
					digitalWrite(RELAY6, 0);
					printf("\n Przekaźnik jest aktualnie włączony \n");
				}	
				return true;
			case E_ELEM_BTN_PRZ7:
				
				if (digitalRead(RELAY7) == 0)
				{		
					pinMode(RELAY7, OUTPUT);
					digitalWrite(RELAY7, 1);
					printf("\n Przekaźnik jest aktualnie wyłączony \n");
				}
				else
				{	
					pinMode(RELAY7, OUTPUT);
					digitalWrite(RELAY7, 0);
					printf("\n Przekaźnik jest aktualnie włączony \n");
				}	
				return true;
			case E_ELEM_BTN_PRZ8:
				
				if (digitalRead(RELAY8) == 0)
				{		
					pinMode(RELAY8, OUTPUT);
					digitalWrite(RELAY8, 1);
					printf("\n Przekaźnik jest aktualnie wyłączony \n");
				}
				else
				{	
					pinMode(RELAY8, OUTPUT);
					digitalWrite(RELAY8, 0);
					printf("\n Przekaźnik jest aktualnie włączony \n");
				}	
				return true;
		}
	}
	return true;
}

bool MCP_ENABLE_PIN(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY)
{
  gslc_tsGui*     pGui      = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef  = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem     = gslc_GetElemFromRef(pGui,pElemRef);
  int16_t nElemId = pElem->nId;
  if (eTouch == GSLC_TOUCH_UP_IN) {
	pinMode(AF_RESET, OUTPUT);
	pinMode(AF_RESET, LOW);	
    	switch (nElemId) 
	{
		case E_ELEM_BTN_GPA0:
			pinMode(AF_GPA0, OUTPUT);
			digitalWrite(AF_GPA0, 1);
			return true;
		case E_ELEM_BTN_GPA1:
			pinMode(AF_GPA1, OUTPUT);
			digitalWrite(AF_GPA1, 1);
			return true;
		case E_ELEM_BTN_GPA2:
			pinMode(AF_GPA2, OUTPUT);
			digitalWrite(AF_GPA2, 1);
			return true;
		case E_ELEM_BTN_GPA3:
			pinMode(AF_GPA3, OUTPUT);
			digitalWrite(AF_GPA3, 1);
			return true;
		case E_ELEM_BTN_GPA4:
			pinMode(AF_GPA4, OUTPUT);
			digitalWrite(AF_GPA4, 1);
			return true;
		case E_ELEM_BTN_GPA5:
			pinMode(AF_GPA5, OUTPUT);
			digitalWrite(AF_GPA5, 1);
			return true;
		case E_ELEM_BTN_GPA6:
			pinMode(AF_GPA6, OUTPUT);
			digitalWrite(AF_GPA6, 1);
			return true;
		case E_ELEM_BTN_GPA7:
			pinMode(AF_GPA7, OUTPUT);
			digitalWrite(AF_GPA7, 1);
			return true;
		case E_ELEM_BTN_GPB0:
			pinMode(AF_GPB0, OUTPUT);
			digitalWrite(AF_GPB0, 1);
			return true;
		case E_ELEM_BTN_GPB1:
			pinMode(AF_GPB1, OUTPUT);
			digitalWrite(AF_GPB1, 1);
			return true;
		case E_ELEM_BTN_GPB2:
			pinMode(AF_GPB2, OUTPUT);
			digitalWrite(AF_GPB2, 1);
			return true;
		case E_ELEM_BTN_GPB3:
			pinMode(AF_GPB3, OUTPUT);
			digitalWrite(AF_GPB3, 1);
			return true;
		case E_ELEM_BTN_GPB4:
			pinMode(AF_GPB4, OUTPUT);
			digitalWrite(AF_GPB4, 1);
			return true;
		case E_ELEM_BTN_GPB5:
			pinMode(AF_GPB5, OUTPUT);
			digitalWrite(AF_GPB5, 1);
			return true;
		case E_ELEM_BTN_GPB6:
			pinMode(AF_GPB6, OUTPUT);
			digitalWrite(AF_GPB6, 1);
			return true;
		case E_ELEM_BTN_GPB7:
			pinMode(AF_GPB7, OUTPUT);
			digitalWrite(AF_GPB7, 1);
			return true;
	}
  }
  return true;
}

bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY)
{
  unsigned short int x = 0;

  if (eTouch == GSLC_TOUCH_UP_IN) {
	pinMode(AF_RESET, OUTPUT);
	pinMode(AF_RESET, LOW);
	for (x = 0; x < 16; x++)
	{
		pinMode((AF_BASE + x), OUTPUT);	
		digitalWrite((AF_BASE + x), 1);
		
	}
  }
  return true;
}

bool CbBtnMcpDisable(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY)
{
  unsigned short int x = 0;

  if (eTouch == GSLC_TOUCH_UP_IN) {
        pinMode(AF_RESET, OUTPUT);
        pinMode(AF_RESET, LOW); 
        for (x = 0; x < 16; x++)
	{
		pinMode((AF_BASE + x), OUTPUT);	
		digitalWrite((AF_BASE + x), 0);
	}
  }
  return true;
}


// Button callbacks
bool FUNCTIONAL_BUTTONS(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY)
{
  gslc_tsGui*     pGui      = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef  = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem     = gslc_GetElemFromRef(pGui,pElemRef);
  int16_t nElemId = pElem->nId;
  if (eTouch == GSLC_TOUCH_UP_IN) {
    	switch (nElemId) 
	{
		case E_ELEM_BTN_QUIT:
			m_bQuit = true;
			return true;
		case E_ELEM_BTN_EXTRA:
			gslc_SetPageCur(&m_gui,E_PG_EXTRA);
			return true;
		case E_ELEM_BTN_OPTIONS:
			if (opts_init()) 
			{ 
			gslc_SetPageCur(&m_gui,E_PG_OPTIONS);
			return true;
			}
			else
			{
			return false;
			}
		case E_ELEM_BTN_BACK:
			gslc_SetPageCur(&m_gui,E_PG_MAIN);
			return true;
		case E_ELEM_BTN_BACK_OPTIONS:
			gslc_SetPageCur(&m_gui,E_PG_MAIN);
			return true;
		case E_ELEM_BTN_SAVE_OPTIONS:
			if (opts_save()) 
			{ 
			return true;
			}
		case E_ELEM_BTN_REBOOT:
			m_bQuit = true;     
			system("reboot");
			return true;
		case E_ELEM_BTN_POWEROFF:
			m_bQuit = true;
			system("poweroff");
			return true;
	}
  }
  return true;
}
//Zdalne przekaźniki
bool RemoteRelay(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY)
{
  gslc_tsGui*     pGui      = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef  = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem     = gslc_GetElemFromRef(pGui,pElemRef);
  int16_t nElemId = pElem->nId;

  if (eTouch == GSLC_TOUCH_UP_IN) {
	switch (nElemId) 
	{
		case E_ELEM_BTN_REMOTE_RELAY_E1:
			system("codesend 5264691");
			return true;
		case E_ELEM_BTN_REMOTE_RELAY_E2:
			system("codesend 5264835");
			return true;
		case E_ELEM_BTN_REMOTE_RELAY_E3:
			system("codesend 5265155");
			return true;
		case E_ELEM_BTN_REMOTE_RELAY_D1:
			system("codesend 5264700");
			return true;
		case E_ELEM_BTN_REMOTE_RELAY_D2:
			system("codesend 5264844");
			return true;
		case E_ELEM_BTN_REMOTE_RELAY_D3:
			system("codesend 5265164");
			return true;
	}
  }
  return true;
}
/*
bool CbControls(void* pvGui,void* pvElemRef,int16_t nPos)
{
  gslc_tsGui*       pGui      = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef*   pElemRef  = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*      pElem     = gslc_GetElemFromRef(pGui,pElemRef);

  int16_t         nVal;
  gslc_tsElemRef* pElemRefTmp = NULL;

  // Handle various controls
  switch (pElem->nId) {
    case E_SCROLLBAR:
      // Fetch the scrollbar value
      nVal = gslc_ElemXSliderGetPos(pGui,pElemRef);
      // Update the textbox scroll position
      pElemRefTmp = gslc_PageFindElemById(pGui,E_PG_MAIN,E_ELEM_TEXTBOX);
      gslc_ElemXTextboxScrollSet(pGui,pElemRefTmp,nVal,100);
      break;
    default:
      break;
  }
  return true;
}
*/
// Create page elements
bool InitOverlays(char *strPath)
{
  	gslc_tsElemRef*  pElemRef;

  	gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPageElem,MAX_ELEM_PG_MAIN,m_asPageElemRef,MAX_ELEM_PG_MAIN);
  	gslc_PageAdd(&m_gui,E_PG_EXTRA,m_asExtraElem,MAX_ELEM_PG_EXTRA,m_asExtraElemRef,MAX_ELEM_PG_EXTRA);
	gslc_PageAdd(&m_gui,E_PG_OPTIONS,m_asOptionsElem,MAX_ELEM_PG_OPTIONS,m_asOptionsElemRef,MAX_ELEM_PG_OPTIONS);

  // Background flat color
  //gslc_SetBkgndColor(&m_gui,GSLC_COL_GRAY_DK2);
  strncpy(m_strImgBkgnd,strPath,MAX_PATH);
  strncat(m_strImgBkgnd,IMG_BKGND,MAX_PATH);
  gslc_SetBkgndImage(&m_gui,gslc_GetImageFromFile(m_strImgBkgnd,GSLC_IMGREF_FMT_BMP24));

  // Create background box
  pElemRef = gslc_ElemCreateBox(&m_gui,GSLC_ID_AUTO,E_PG_OPTIONS,(gslc_tsRect){10,10,1004,580});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_BLACK);
  
  //Sterownik Info // Create title
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TXT_APP_TITLE,E_PG_MAIN,(gslc_tsRect){20,15,410,40},"",0,E_FONT_TITLE);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);

  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT_MONGO,E_PG_MAIN,(gslc_tsRect){40,110,240,60},"ęĘóÓąĄśŚłŁżŻźŹćĆńŃ",0,E_FONT_TEMP);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);

		//pElemRef = gslc_ElemXGaugeCreate(&m_gui,E_RAMP2,E_PG_MAIN,&m_sXRamp2,(gslc_tsRect){15,300,300,100},0,1024,1024,GSLC_COL_YELLOW,false);
		//gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED,GSLC_COL_BLACK,GSLC_COL_BLACK);
		//gslc_ElemXGaugeSetStyle(&m_gui,pElemRef,GSLCX_GAUGE_STYLE_RAMP);
  //Memory usage
  //pElemRef = gslc_ElemXGaugeCreate(&m_gui,E_ELEM_MEM,E_PG_MAIN,&m_sXGauge10,(gslc_tsRect){382,390,200,10},0,(getMemoryTotal() / 1024),(getMemoryUsage() / 1024),GSLC_COL_ORANGE,false);
  //gslc_ElemSetCol(&m_gui,pElemRef,(gslc_tsColor) {217, 46, 10},GSLC_COL_BLACK,GSLC_COL_BLACK);

  //SLIDER {15,550,70,35}
  pElemRef = gslc_ElemXSliderCreate(&m_gui,E_ELEM_SLIDER,E_PG_MAIN,&m_sXSlider,(gslc_tsRect){200,550,200,20},0,100,0,5,false);
  gslc_ElemXSliderSetStyle(&m_gui,pElemRef,true,(gslc_tsColor){0,0,128},10,5,(gslc_tsColor){64,64,64});
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);

  //SLIDER2
  pElemRef = gslc_ElemXSliderCreate(&m_gui,E_ELEM_SLIDER2,E_PG_MAIN,&m_sXSlider2,(gslc_tsRect){200,575,200,20},0,100,0,5,false);
  gslc_ElemXSliderSetStyle(&m_gui,pElemRef,true,(gslc_tsColor){0,0,128},10,5,(gslc_tsColor){64,64,64});
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);

  // Create textbox
  pElemRef = gslc_ElemXTextboxCreate(&m_gui,E_ELEM_TEXTBOX,E_PG_MAIN,&m_sTextbox,(gslc_tsRect){644,20,375,220},E_FONT_TEMP,(char*)&m_acTextboxBuf,TBOX_ROWS,TBOX_COLS);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  gslc_ElemXTextboxWrapSet(&m_gui,pElemRef,false);
  gslc_ElemSetCol(&m_gui,pElemRef,(gslc_tsColor){181,200,245},(gslc_tsColor){59,58,120},GSLC_COL_BLACK);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_ORANGE);
  //gslc_ElemSetTxtMargin(&m_gui,pElemRef,3);
  


  // Create vertical scrollbar for textbox
  //pElemRef = gslc_ElemXSliderCreate(&m_gui,E_SCROLLBAR,E_PG_MAIN,&m_sXSliderText,(gslc_tsRect){989,20,30,160},0,100,100,5,true);
  //gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK4,GSLC_COL_BLACK,GSLC_COL_BLACK);
  //gslc_ElemXSliderSetPosFunc(&m_gui,pElemRef,&CbControls);



  // Create Extra button with text label
	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_EXTRA,E_PG_MAIN,(gslc_tsRect){15,550,70,35},"Extra",0,E_FONT_BTN,&FUNCTIONAL_BUTTONS);
	gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GREEN,GSLC_COL_GREEN_LT1,GSLC_COL_GREEN_LT2);
  // Create OPTIONS button with text label
	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_OPTIONS,E_PG_MAIN,(gslc_tsRect){105,550,70,35},"Ustawienia",0,E_FONT_BTN,&FUNCTIONAL_BUTTONS);
	//gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GREEN,GSLC_COL_GREEN_LT1,GSLC_COL_GREEN_LT2);
  // Create Quit button with text label
	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_QUIT,E_PG_MAIN,(gslc_tsRect){760,550,70,35},"Zamknij",0,E_FONT_BTN,&FUNCTIONAL_BUTTONS);
	gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED,GSLC_COL_RED,GSLC_COL_RED);
	gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  // Create Reboot button
	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_REBOOT,E_PG_MAIN,(gslc_tsRect){850,550,70,35},"Reboot",0,E_FONT_DEJAVU_SANS_BOLD,&FUNCTIONAL_BUTTONS);
	gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED,GSLC_COL_RED,GSLC_COL_RED);
	gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  // Create Poweroff button
	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_POWEROFF,E_PG_MAIN,(gslc_tsRect){940,550,90,35},"Wyłącz",0,E_FONT_TEMP,&FUNCTIONAL_BUTTONS);
	gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
	gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED,GSLC_COL_RED,GSLC_COL_RED);
	gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  // Create Back button with text label
	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_BACK_OPTIONS,E_PG_OPTIONS,(gslc_tsRect){105,550,70,35},"Wstecz",0,E_FONT_BTN,&FUNCTIONAL_BUTTONS);
  // Create Options save button with text label
	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_SAVE_OPTIONS,E_PG_OPTIONS,(gslc_tsRect){15,550,70,35},"Zapisz",0,E_FONT_BTN,&FUNCTIONAL_BUTTONS);
  /*
  // Create dividers
  
	//pElemRef = gslc_ElemCreateLine(&m_gui,GSLC_ID_AUTO,E_PG_MAIN,235,60,235,95);
  	//gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_DK3,GSLC_COL_GRAY_DK3);

	//pElemRef = gslc_ElemCreateLine(&m_gui,GSLC_ID_AUTO,E_PG_MAIN,10,480,1000,10);
  	//gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_DK3,GSLC_COL_GRAY_DK3);

  // Create counter
  pElemRef = gslc_ElemCreateTxt(&m_gui,GSLC_ID_AUTO,E_PG_MAIN,(gslc_tsRect){60,60,50,10},"Count:",0,E_FONT_TXT);
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TXT_COUNT,E_PG_MAIN,(gslc_tsRect){80,60,50,10},"",0,E_FONT_TXT);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_YELLOW);

  // Create progress bar (horizontal)
  pElemRef = gslc_ElemCreateTxt(&m_gui,GSLC_ID_AUTO,E_PG_MAIN,(gslc_tsRect){20,80,50,10},"Progress:",0,E_FONT_TXT);
  pElemRef = gslc_ElemXGaugeCreate(&m_gui,E_ELEM_PROGRESS,E_PG_MAIN,&m_sXGauge,(gslc_tsRect){5,5,200,10},0,200,0,GSLC_COL_GREEN,false);
  */
  /*
     Second progress bar (vertical)
   - Demonstration of vertical bar with offset zero-pt showing both positive and negative range
     pElemRef = gslc_ElemXGaugeCreate(&m_gui,E_ELEM_PROGRESS1,E_PG_MAIN,&m_sXGauge1,(gslc_tsRect){280,80,10,100},-25,75,-15,GSLC_COL_RED,true);
     gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3,GSLC_COL_BLACK,GSLC_COL_BLACK);
  */
  /*
  // Create checkbox 1
  pElemRef = gslc_ElemCreateTxt(&m_gui,GSLC_ID_AUTO,E_PG_MAIN,(gslc_tsRect){20,100,20,20},"Check1:",0,E_FONT_TXT);
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_CHECK1,E_PG_MAIN,&m_asXCheck[0],(gslc_tsRect){80,100,30,30},false,GSLCX_CHECKBOX_STYLE_X,GSLC_COL_BLUE_LT2,false);

  // Create radio 1
  pElemRef = gslc_ElemCreateTxt(&m_gui,GSLC_ID_AUTO,E_PG_MAIN,(gslc_tsRect){130,160,40,40},"Radio1:",0,E_FONT_TXT);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_RADIO1,E_PG_MAIN,&m_asXCheck[1],(gslc_tsRect){160,160,40,40},true,GSLCX_CHECKBOX_STYLE_ROUND,GSLC_COL_ORANGE,false);
  gslc_ElemSetGroup(&m_gui,pElemRef,E_GROUP1);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);

  // Create radio 2
  pElemRef = gslc_ElemCreateTxt(&m_gui,GSLC_ID_AUTO,E_PG_MAIN,(gslc_tsRect){780,160,40,40},"Radio2:",0,E_FONT_TXT);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_RADIO2,E_PG_MAIN,&m_asXCheck[2],(gslc_tsRect){820,160,40,40},true,GSLCX_CHECKBOX_STYLE_ROUND,GSLC_COL_ORANGE,false);
  gslc_ElemSetGroup(&m_gui,pElemRef,E_GROUP1);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  */
  // -----------------------------------
  // PAGE: EXTRA

  // Create background box
  pElemRef = gslc_ElemCreateBox(&m_gui,GSLC_ID_AUTO,E_PG_EXTRA,(gslc_tsRect){5,5,1010,590});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_BLACK);

	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_BACK,E_PG_EXTRA,(gslc_tsRect){105,550,70,35},"Wstecz",0,E_FONT_BTN,&FUNCTIONAL_BUTTONS);

    pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_GPA0,E_PG_EXTRA,
    (gslc_tsRect){200,20,90,40},"Enable GPA0",0,E_FONT_BTN,&MCP_ENABLE_PIN);
    //gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLUE,GSLC_COL_BLUE);

    pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_GPA1,E_PG_EXTRA,
    (gslc_tsRect){300,20,90,40},"Enable GPA1",0,E_FONT_BTN,&MCP_ENABLE_PIN);
    //gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GREEN,GSLC_COL_GREEN,GSLC_COL_GREEN);

    pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_GPA2,E_PG_EXTRA,
    (gslc_tsRect){400,20,90,40},"Enable GPA2",0,E_FONT_BTN,&MCP_ENABLE_PIN);
    //gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_YELLOW,GSLC_COL_YELLOW,GSLC_COL_YELLOW);

    pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_GPA3,E_PG_EXTRA,
    (gslc_tsRect){500,20,90,40},"Enable GPA3",0,E_FONT_BTN,&MCP_ENABLE_PIN);
    //gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_PURPLE,GSLC_COL_PURPLE,GSLC_COL_PURPLE);

    pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_GPA4,E_PG_EXTRA,
    (gslc_tsRect){600,20,90,40},"Enable GPA4",0,E_FONT_BTN,&MCP_ENABLE_PIN);
    //gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_CYAN,GSLC_COL_CYAN,GSLC_COL_CYAN);

    pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_GPA5,E_PG_EXTRA,
    (gslc_tsRect){700,20,90,40},"Enable GPA5",0,E_FONT_BTN,&MCP_ENABLE_PIN);
    //gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_MAGENTA,GSLC_COL_MAGENTA,GSLC_COL_MAGENTA);

    pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_GPA6,E_PG_EXTRA,
    (gslc_tsRect){800,20,90,40},"Enable GPA6",0,E_FONT_BTN,&MCP_ENABLE_PIN);
    //gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_TEAL,GSLC_COL_TEAL,GSLC_COL_TEAL);

    pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_GPA7,E_PG_EXTRA,
    (gslc_tsRect){900,20,90,40},"Enable GPA7",0,E_FONT_BTN,&MCP_ENABLE_PIN);
    //gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_ORANGE,GSLC_COL_ORANGE,GSLC_COL_ORANGE);

    pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_GPB0,E_PG_EXTRA,
    (gslc_tsRect){200,80,90,40},"Enable GPB0",0,E_FONT_BTN,&MCP_ENABLE_PIN);
    //gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLUE,GSLC_COL_BLUE);

    pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_GPB1,E_PG_EXTRA,
    (gslc_tsRect){300,80,90,40},"Enable GPB1",0,E_FONT_BTN,&MCP_ENABLE_PIN);
    //gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GREEN,GSLC_COL_GREEN,GSLC_COL_GREEN);

    pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_GPB2,E_PG_EXTRA,
    (gslc_tsRect){400,80,90,40},"Enable GPB2",0,E_FONT_BTN,&MCP_ENABLE_PIN);
    //gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_YELLOW,GSLC_COL_YELLOW,GSLC_COL_YELLOW);

    pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_GPB3,E_PG_EXTRA,
    (gslc_tsRect){500,80,90,40},"Enable GPB3",0,E_FONT_BTN,&MCP_ENABLE_PIN);
    //gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_PURPLE,GSLC_COL_PURPLE,GSLC_COL_PURPLE);

    pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_GPB4,E_PG_EXTRA,
    (gslc_tsRect){600,80,90,40},"Enable GPB4",0,E_FONT_BTN,&MCP_ENABLE_PIN);
    //gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_CYAN,GSLC_COL_CYAN,GSLC_COL_CYAN);

    pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_GPB5,E_PG_EXTRA,
    (gslc_tsRect){700,80,90,40},"Enable GPB5",0,E_FONT_BTN,&MCP_ENABLE_PIN);
    //gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_MAGENTA,GSLC_COL_MAGENTA,GSLC_COL_MAGENTA);

    pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_GPB6,E_PG_EXTRA,
    (gslc_tsRect){800,80,90,40},"Enable GPB6",0,E_FONT_BTN,&MCP_ENABLE_PIN);
    //gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_TEAL,GSLC_COL_TEAL,GSLC_COL_TEAL);

    pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_GPB7,E_PG_EXTRA,
    (gslc_tsRect){900,80,90,40},"Enable GPB7",0,E_FONT_BTN,&MCP_ENABLE_PIN);
    //gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_ORANGE,GSLC_COL_ORANGE,GSLC_COL_ORANGE);

    //Przekazniki
	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_PRZ1,E_PG_EXTRA,(gslc_tsRect){200,330,90,40},"Relay 1",0,E_FONT_BTN,&CbBtnPRZ);
	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_PRZ2,E_PG_EXTRA,(gslc_tsRect){300,330,90,40},"Relay 2",0,E_FONT_BTN,&CbBtnPRZ);
	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_PRZ3,E_PG_EXTRA,(gslc_tsRect){400,330,90,40},"Relay 3",0,E_FONT_BTN,&CbBtnPRZ);
	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_PRZ4,E_PG_EXTRA,(gslc_tsRect){500,330,90,40},"Relay 4",0,E_FONT_BTN,&CbBtnPRZ);
	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_PRZ5,E_PG_EXTRA,(gslc_tsRect){600,330,90,40},"Relay 5",0,E_FONT_BTN,&CbBtnPRZ);
	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_PRZ6,E_PG_EXTRA,(gslc_tsRect){700,330,90,40},"Relay 6",0,E_FONT_BTN,&CbBtnPRZ);
	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_PRZ7,E_PG_EXTRA,(gslc_tsRect){800,330,90,40},"Relay 7",0,E_FONT_BTN,&CbBtnPRZ);
	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_PRZ8,E_PG_EXTRA,(gslc_tsRect){900,330,90,40},"Relay 8",0,E_FONT_BTN,&CbBtnPRZ);

    //Zdalne gniazdka

	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_REMOTE_RELAY_E1,E_PG_EXTRA,(gslc_tsRect){100,380,90,40},"Remote Relay 1",0,E_FONT_BTN,&RemoteRelay);
	gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GREEN,GSLC_COL_GREEN,GSLC_COL_ORANGE);	
	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_REMOTE_RELAY_E2,E_PG_EXTRA,(gslc_tsRect){200,380,90,40},"Remote Relay 2",0,E_FONT_BTN,&RemoteRelay);
	gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GREEN,GSLC_COL_GREEN,GSLC_COL_ORANGE);
	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_REMOTE_RELAY_E3,E_PG_EXTRA,(gslc_tsRect){300,380,90,40},"Remote Relay 3",0,E_FONT_BTN,&RemoteRelay);
	gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GREEN,GSLC_COL_GREEN,GSLC_COL_ORANGE);
	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_REMOTE_RELAY_D1,E_PG_EXTRA,(gslc_tsRect){100,430,90,40},"Remote Relay 1",0,E_FONT_BTN,&RemoteRelay);
	gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED,GSLC_COL_RED,GSLC_COL_YELLOW);
	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_REMOTE_RELAY_D2,E_PG_EXTRA,(gslc_tsRect){200,430,90,40},"Remote Relay 2",0,E_FONT_BTN,&RemoteRelay);
	gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED,GSLC_COL_RED,GSLC_COL_YELLOW);
	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_REMOTE_RELAY_D3,E_PG_EXTRA,(gslc_tsRect){300,430,90,40},"Remote Relay 3",0,E_FONT_BTN,&RemoteRelay);
	gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED,GSLC_COL_RED,GSLC_COL_YELLOW);

    //Create MCP
	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_MCPENABLE,E_PG_EXTRA,(gslc_tsRect){700,540,90,40},"MCP Enable",0,E_FONT_BTN,&CbBtnCommon);

    //Create MCP
	pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_MCPDISABLE,E_PG_EXTRA,(gslc_tsRect){600,540,90,40},"MCP Disable",0,E_FONT_BTN,&CbBtnMcpDisable);

  return true;
}
int pinex_conf() {

	static const char *output_file = "pinex.cfg";
	config_t cfg;
	config_setting_t *root;
	config_setting_t *pinex;
	config_setting_t *onewire;
	config_setting_t *group; 
	config_setting_t *setting;
	config_setting_t *fonts;

  	config_init(&cfg);
  	root = config_root_setting(&cfg);

  	/* Add some settings to the configuration. */
  	pinex = config_setting_add(root, "pinex", CONFIG_TYPE_GROUP);
	{
		group = config_setting_add(pinex,"gui",CONFIG_TYPE_GROUP);
		{
			setting = config_setting_add(group, "WindowH", CONFIG_TYPE_STRING);
			config_setting_set_string(setting, "1024");

			setting = config_setting_add(group, "WindowW", CONFIG_TYPE_STRING);
			config_setting_set_string(setting, "600");

		}

		group = config_setting_add(pinex,"app",CONFIG_TYPE_GROUP);
		{
			setting = config_setting_add(group, "AppName", CONFIG_TYPE_STRING);
			config_setting_set_string(setting, "Pi-nex");

			setting = config_setting_add(group, "Version", CONFIG_TYPE_STRING);
			config_setting_set_string(setting, "1.0");

			setting = config_setting_add(group, "Desc", CONFIG_TYPE_STRING);
			config_setting_set_string(setting, "Sterownik C.O");
		}
	}
	onewire = config_setting_add(root, "onewire", CONFIG_TYPE_GROUP);
	{
		onewire = config_setting_add(onewire,"tempsensors",CONFIG_TYPE_GROUP);
		{
			group = config_setting_add(onewire,"SENSOR1",CONFIG_TYPE_GROUP);
			{
				setting = config_setting_add(group, "name", CONFIG_TYPE_STRING);
				config_setting_set_string(setting, "T.Z C.O");

				setting = config_setting_add(group, "id", CONFIG_TYPE_STRING);
				config_setting_set_string(setting, "28-000009ecfead");

				setting = config_setting_add(group, "path", CONFIG_TYPE_STRING);
				config_setting_set_string(setting, "/sys/bus/w1/devices/28-000009ecfead/w1_slave");
			}
			group = config_setting_add(onewire,"SENSOR2",CONFIG_TYPE_GROUP);
			{
				setting = config_setting_add(group, "name", CONFIG_TYPE_STRING);
				config_setting_set_string(setting, "T.P C.O");

				setting = config_setting_add(group, "id", CONFIG_TYPE_STRING);
				config_setting_set_string(setting, "28-000009edd921");

				setting = config_setting_add(group, "path", CONFIG_TYPE_STRING);
				config_setting_set_string(setting, "/sys/bus/w1/devices/28-000009edd921/w1_slave");
			}
			group = config_setting_add(onewire,"SENSOR3",CONFIG_TYPE_GROUP);
			{
				setting = config_setting_add(group, "name", CONFIG_TYPE_STRING);
				config_setting_set_string(setting, "T.Z Podlogowego");

				setting = config_setting_add(group, "id", CONFIG_TYPE_STRING);
				config_setting_set_string(setting, "28-000009ee0441");

				setting = config_setting_add(group, "path", CONFIG_TYPE_STRING);
				config_setting_set_string(setting, "/sys/bus/w1/devices/28-000009ee0441/w1_slave");
			}
			group = config_setting_add(onewire,"SENSOR4",CONFIG_TYPE_GROUP);
			{
				setting = config_setting_add(group, "name", CONFIG_TYPE_STRING);
				config_setting_set_string(setting, "T.P Podlogowego");

				setting = config_setting_add(group, "id", CONFIG_TYPE_STRING);
				config_setting_set_string(setting, "28-000009edbff6");

				setting = config_setting_add(group, "path", CONFIG_TYPE_STRING);
				config_setting_set_string(setting, "/sys/bus/w1/devices/28-000009edbff6/w1_slave");
			}
			group = config_setting_add(onewire,"SENSOR5",CONFIG_TYPE_GROUP);
			{
				setting = config_setting_add(group, "name", CONFIG_TYPE_STRING);
				config_setting_set_string(setting, "T.Z Zasobnika");

				setting = config_setting_add(group, "id", CONFIG_TYPE_STRING);
				config_setting_set_string(setting, "28-000009eddf78");

				setting = config_setting_add(group, "path", CONFIG_TYPE_STRING);
				config_setting_set_string(setting, "/sys/bus/w1/devices/28-000009eddf78/w1_slave");
			}
			group = config_setting_add(onewire,"SENSOR6",CONFIG_TYPE_GROUP);
			{
				setting = config_setting_add(group, "name", CONFIG_TYPE_STRING);
				config_setting_set_string(setting, "T.P Zasobnika");

				setting = config_setting_add(group, "id", CONFIG_TYPE_STRING);
				config_setting_set_string(setting, "28-000009ee2891");

				setting = config_setting_add(group, "path", CONFIG_TYPE_STRING);
				config_setting_set_string(setting, "/sys/bus/w1/devices/28-000009ee2891/w1_slave");
			}

		}
	}
	fonts = config_setting_add(root, "fonts", CONFIG_TYPE_GROUP);
	{
		fonts = config_setting_add(fonts,"Fontconfig",CONFIG_TYPE_GROUP);
		{
			group = config_setting_add(fonts,"FONT_TEMP",CONFIG_TYPE_GROUP);
			{
				setting = config_setting_add(group, "path", CONFIG_TYPE_STRING);
				config_setting_set_string(setting, "fonts/AlfaSlabOne-Regular.ttf");

				setting = config_setting_add(group, "size", CONFIG_TYPE_INT);
				config_setting_set_int(setting, 20);
			}
			group = config_setting_add(fonts,"FONT_TITLE",CONFIG_TYPE_GROUP);
			{
				setting = config_setting_add(group, "path", CONFIG_TYPE_STRING);
				config_setting_set_string(setting, "fonts/Pro-Display-tfb.ttf");

				setting = config_setting_add(group, "size", CONFIG_TYPE_INT);
				config_setting_set_int(setting, 32);
			}
		}
	}
  	/* Write out the new configuration. */
  
	if(! config_write_file(&cfg, output_file))
	{
    		fprintf(stderr, "Error while writing file.\n");
    		config_destroy(&cfg);
    		return 0;
  	}
  	//printf("D %s\n",config_lookup_string(&cfg, "onewire.tempsensors.SENSOR1.name"));
  	fprintf(stderr, "New configuration successfully written to: %s\n",output_file);

  	config_destroy(&cfg);
  
	return 1;
}
void * CPUUSAGE() {
	double cpuusage;

	gslc_tsElemRef*  pElemRef;
	  //CPU Usage								
  	pElemRef = gslc_ElemXGaugeCreate(&m_gui,E_ELEM_CPU,E_PG_MAIN,&m_sXGauge11,(gslc_tsRect){540,580,200,10},0,100,0,GSLC_COL_ORANGE,false);
  	gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3,GSLC_COL_BLACK,GSLC_COL_BLACK);	
	
	gslc_tsElemRef*  pElemCpuUsage   = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_CPU);
	
	while(1) {
		init();
		sleep(1);
		cpuusage = getCurrentValue();
		gslc_ElemXGaugeUpdate(&m_gui,pElemCpuUsage,(double)(cpuusage));
		
		
	}
	pthread_exit(NULL);
}

void * ds3231() {
	int ds3231_fd;
	int retval;
	char                temper[100];
	
	enum {
		E_ELEM_TXT_APP_TEMP
	};

	
	
	gslc_tsElemRef*  pElemRef;
	
	pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TXT_APP_TEMP,E_PG_MAIN,(gslc_tsRect){20,60,310,40},"",0,E_FONT_TITLE_TEMP);
	//gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
	gslc_ElemSetFillEn(&m_gui,pElemRef,false);
	gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
        
	gslc_tsElemRef* pElemTextapptemp = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_TXT_APP_TEMP);
	
	while(1) {
		ds3231_fd = DS3231_open(I2C_BUS);

		if(ds3231_fd < 0) {
			exit(EXIT_FAILURE);
		}

		retval = DS3231_read_temperature(ds3231_fd, &ds3231_temperature);
	
		if(retval != 0) {
			exit(EXIT_FAILURE);
		}
		snprintf(temper,MAX_STR,(char*)"DS3231: %+3.2lf 'C\n",ds3231_temperature);
    		gslc_ElemSetTxtStr(&m_gui,pElemTextapptemp,(char*)temper);

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
	char                temper[100];
	
	char *SENSOR1 = "/sys/bus/w1/devices/28-000009ecfead/w1_slave";
	char *SENSOR2 = "/sys/bus/w1/devices/28-000009ee0441/w1_slave";
	char *SENSOR3 = "/sys/bus/w1/devices/28-0317316b1eff/w1_slave";
	char *SENSOR4 = "/sys/bus/w1/devices/28-000009edbff6/w1_slave";  
	char *SENSOR5 = "/sys/bus/w1/devices/28-000009ee2891/w1_slave";  
	char *SENSOR6 = "/sys/bus/w1/devices/28-0317316c9aff/w1_slave";
	char *SENSOR7 = "/sys/bus/w1/devices/28-000009edd921/w1_slave";  
	char *SENSOR8 = "/sys/bus/w1/devices/28-0317310a1cff/w1_slave";

	gslc_tsElemRef* pElemTextbox = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_TEXTBOX);
	gslc_tsElemRef*  pElemRef;
	//pElemRef = gslc_ElemXGaugeCreate(&m_gui,E_RADIAL,E_PG_MAIN,&m_sXRadial,(gslc_tsRect){210,140,180,180},0,100,0,GSLC_COL_YELLOW,false);
	pElemRef = gslc_ElemXGaugeCreate(&m_gui,E_RADIAL,E_PG_MAIN,&m_sXRadial,(gslc_tsRect){210,140,180,180},0,120,0,GSLC_COL_WHITE,true);	
	gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_BLACK);
	gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  	gslc_ElemXGaugeSetStyle(&m_gui,pElemRef,GSLCX_GAUGE_STYLE_RADIAL);
  	gslc_ElemXGaugeSetIndicator(&m_gui,pElemRef,GSLC_COL_YELLOW,70,3,true);
  	gslc_ElemXGaugeSetTicks(&m_gui,pElemRef,GSLC_COL_GRAY_LT1,24,10);

	gslc_tsElemRef* pElemRad = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_RADIAL);

	while(1) {
  					
		gslc_ElemXTextboxReset(&m_gui,pElemTextbox);
		
		temp1=read_temp(SENSOR1);
		snprintf(temper,MAX_STR,"T.Z 1:       %.1fC\n",temp1 / 1000);
		gslc_ElemXTextboxAdd(&m_gui,pElemTextbox,temper);
		gslc_ElemXGaugeUpdate(&m_gui,pElemRad,temp1 / 1000);
		usleep(10 * 100000); // s * microseconds

		temp2=read_temp(SENSOR2);
    		snprintf(temper,MAX_STR,"T.P 2:       %.1fC\n",temp2 / 1000);
		gslc_ElemXTextboxAdd(&m_gui,pElemTextbox,temper);
		usleep(10 * 100000); // s * microseconds

		temp3=read_temp(SENSOR3);		
		snprintf(temper,MAX_STR,"T.Z 3:       %.1fC\n",temp3 / 1000);
		gslc_ElemXTextboxAdd(&m_gui,pElemTextbox,temper);
		gslc_ElemSetTxtEnc(&m_gui,pElemTextbox,GSLC_TXT_ENC_UTF8);
		usleep(10 * 100000); // s * microseconds

		temp4=read_temp(SENSOR4);
    		snprintf(temper,MAX_STR,"T.P 4:       %.1fC\n",temp4 / 1000);
		gslc_ElemXTextboxAdd(&m_gui,pElemTextbox,temper);
		usleep(10 * 100000); // s * microseconds
		
		temp5=read_temp(SENSOR5);		
    		snprintf(temper,MAX_STR,"T.Z 5        %.1fC\n",temp5 / 1000);
		gslc_ElemXTextboxAdd(&m_gui,pElemTextbox,temper);
		usleep(10 * 100000); // s * microseconds
		
		temp6=read_temp(SENSOR6);
   		snprintf(temper,MAX_STR,"T.P 6        %.1fC\n",temp6 / 1000);
		gslc_ElemXTextboxAdd(&m_gui,pElemTextbox,temper);
		usleep(10 * 100000); // s * microseconds

		temp7=read_temp(SENSOR7);
   		snprintf(temper,MAX_STR,"T. New 1:    %.1fC\n",temp7 / 1000);
		gslc_ElemXTextboxAdd(&m_gui,pElemTextbox,temper);
		usleep(10 * 100000); // s * microseconds

		temp8=read_temp(SENSOR8);
   		snprintf(temper,MAX_STR,"T. New 2:    %.1fC\n",temp8 / 1000);
		gslc_ElemXTextboxAdd(&m_gui,pElemTextbox,temper);
		usleep(10 * 100000); // s * microseconds

	}
	pthread_exit(NULL);
}

void * ADC_VOLTS()
{
	FILE* fadc0; 
	FILE* fadc1;
	FILE* fadc2;
	FILE* fadc3; 
	FILE* fadc4;
	FILE* fadc5;
	FILE* fadc6; 
	FILE* fadc7;
	int 		volt[8];
	double 		frmv[8];
	//char		temper[100];
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
	} ;

	gslc_tsElemRef*  pElemRef;

  	pElemRef = gslc_ElemCreateBox(&m_gui,GSLC_ID_AUTO,E_PG_MAIN,(gslc_tsRect){644,250,375,220});
  	gslc_ElemSetCol(&m_gui,pElemRef,(gslc_tsColor){181,200,245},(gslc_tsColor){59,58,120},GSLC_COL_BLACK);
  	gslc_ElemSetFrameEn(&m_gui,pElemRef,true);

  	pElemRef = gslc_ElemCreateBox(&m_gui,GSLC_ID_AUTO,E_PG_MAIN,(gslc_tsRect){644,283,375,1});
  	gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2,GSLC_COL_GRAY_LT2);
  	gslc_ElemSetFrameEn(&m_gui,pElemRef,false);

  	pElemRef = gslc_ElemCreateTxt(&m_gui,GSLC_ID_AUTO,E_PG_MAIN,(gslc_tsRect){644,253,375,80-57},"ADC Sensors",0,E_FONT_HEAD);
  	gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  	gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  	gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_LT3);
  	gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
	/*
	pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TXT_ADC0,E_PG_MAIN,(gslc_tsRect){644+5,290,160,40},"",0,E_FONT_TXT_ADC);
  	gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_TOP_LEFT);
  	gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  	gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);

	pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TXT_ADC1,E_PG_MAIN,(gslc_tsRect){644+5,310,160,40},"",0,E_FONT_TXT_ADC);
  	gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_TOP_LEFT);
  	gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  	gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);

	pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TXT_ADC2,E_PG_MAIN,(gslc_tsRect){644+5,330,160,40},"",0,E_FONT_TXT_ADC);
  	gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_TOP_LEFT);
  	gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  	gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);

	pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TXT_ADC3,E_PG_MAIN,(gslc_tsRect){644+5,350,160,40},"",0,E_FONT_TXT_ADC);
  	gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_TOP_LEFT);
  	gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  	gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);

	pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TXT_ADC4,E_PG_MAIN,(gslc_tsRect){644+5,370,160,40},"",0,E_FONT_TXT_ADC);
  	gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_TOP_LEFT);
  	gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  	gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);

	pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TXT_ADC5,E_PG_MAIN,(gslc_tsRect){644+5,390,160,40},"",0,E_FONT_TXT_ADC);
  	gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_TOP_LEFT);
  	gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  	gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);

	pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TXT_ADC6,E_PG_MAIN,(gslc_tsRect){644+5,410,160,40},"",0,E_FONT_TXT_ADC);
  	gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_TOP_LEFT);
  	gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  	gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);

	pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TXT_ADC7,E_PG_MAIN,(gslc_tsRect){644+5,430,160,40},"",0,E_FONT_TXT_ADC);
  	gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_TOP_LEFT);
  	gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  	gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
	*/

	pElemRef = gslc_ElemXGaugeCreate(&m_gui,E_ELEM_ADC0,E_PG_MAIN,&m_sXADC0,(gslc_tsRect){644+165,290,200,20},0,1024,0,GSLC_COL_RED,false);
	gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3,GSLC_COL_BLACK,GSLC_COL_BLACK);

	pElemRef = gslc_ElemXGaugeCreate(&m_gui,E_ELEM_ADC1,E_PG_MAIN,&m_sXADC1,(gslc_tsRect){644+165,310,200,20},0,1024,0,GSLC_COL_RED,false);
	gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3,GSLC_COL_BLACK,GSLC_COL_BLACK);

	pElemRef = gslc_ElemXGaugeCreate(&m_gui,E_ELEM_ADC2,E_PG_MAIN,&m_sXADC2,(gslc_tsRect){644+165,330,200,20},0,1024,0,GSLC_COL_RED,false);
	gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3,GSLC_COL_BLACK,GSLC_COL_BLACK);
  
	pElemRef = gslc_ElemXGaugeCreate(&m_gui,E_ELEM_ADC3,E_PG_MAIN,&m_sXADC3,(gslc_tsRect){644+165,350,200,20},0,1024,0,GSLC_COL_RED,false);
	gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3,GSLC_COL_BLACK,GSLC_COL_BLACK);

	pElemRef = gslc_ElemXGaugeCreate(&m_gui,E_ELEM_ADC4,E_PG_MAIN,&m_sXADC4,(gslc_tsRect){644+165,370,200,20},0,1024,0,GSLC_COL_RED,false);
	gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3,GSLC_COL_BLACK,GSLC_COL_BLACK);

	pElemRef = gslc_ElemXGaugeCreate(&m_gui,E_ELEM_ADC5,E_PG_MAIN,&m_sXADC5,(gslc_tsRect){644+165,390,200,20},0,1024,0,GSLC_COL_RED,false);
	gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3,GSLC_COL_BLACK,GSLC_COL_BLACK);

	pElemRef = gslc_ElemXGaugeCreate(&m_gui,E_ELEM_ADC6,E_PG_MAIN,&m_sXADC6,(gslc_tsRect){644+165,410,200,20},0,1024,0,GSLC_COL_RED,false);
	gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3,GSLC_COL_BLACK,GSLC_COL_BLACK);

	pElemRef = gslc_ElemXGaugeCreate(&m_gui,E_ELEM_ADC7,E_PG_MAIN,&m_sXADC7,(gslc_tsRect){644+165,430,200,20},0,1024,0,GSLC_COL_RED,false);
	gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK3,GSLC_COL_BLACK,GSLC_COL_BLACK);

	gslc_tsElemRef*  pElemAdc0   = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_ADC0);
	gslc_tsElemRef*  pElemAdc1   = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_ADC1);
	gslc_tsElemRef*  pElemAdc2   = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_ADC2);
	gslc_tsElemRef*  pElemAdc3   = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_ADC3);
	gslc_tsElemRef*  pElemAdc4   = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_ADC4);
	gslc_tsElemRef*  pElemAdc5   = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_ADC5);
	gslc_tsElemRef*  pElemAdc6   = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_ADC6);
	gslc_tsElemRef*  pElemAdc7   = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_ADC7);
	
	/*
	gslc_tsElemRef*  pElemAdcText0   = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_TXT_ADC0);
	gslc_tsElemRef*  pElemAdcText1   = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_TXT_ADC1);
	gslc_tsElemRef*  pElemAdcText2   = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_TXT_ADC2);
	gslc_tsElemRef*  pElemAdcText3   = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_TXT_ADC3);
	gslc_tsElemRef*  pElemAdcText4   = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_TXT_ADC4);
	gslc_tsElemRef*  pElemAdcText5   = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_TXT_ADC5);
	gslc_tsElemRef*  pElemAdcText6   = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_TXT_ADC6);
	gslc_tsElemRef*  pElemAdcText7   = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_TXT_ADC7);
	*/
	//

	
	while(1) {
		fadc0 = fopen(adc[0], "r"); 
		assert(fadc0 != NULL);
		fscanf(fadc0, "%d", &volt[0]);
		frmv[0] = (volt[0] / 1023.0) * 3.600;
		gslc_ElemXGaugeUpdate(&m_gui,pElemAdc0,volt[0]);
		
		fclose(fadc0);
		//snprintf(temper,MAX_STR,"Voltage %.1f V",frmv[0]);
		//gslc_ElemSetTxtStr(&m_gui,pElemAdcText0,temper);
		
		fadc1 = fopen(adc[1], "r");
		assert(fadc1 != NULL); 
		fscanf(fadc1, "%d", &volt[1]);
		frmv[1] = (volt[1] / 1023.0) * 3.600;
		gslc_ElemXGaugeUpdate(&m_gui,pElemAdc1,volt[1]);
		
		fclose(fadc1);
		//snprintf(temper,MAX_STR,"Voltage %.1f V",frmv[1]);
		//gslc_ElemSetTxtStr(&m_gui,pElemAdcText1,temper);
		
		fadc2 = fopen(adc[2], "r");
		assert(fadc2 != NULL);
		fscanf(fadc2, "%d", &volt[2]);
		frmv[2] = (volt[2] / 1023.0) * 3.600;
		gslc_ElemXGaugeUpdate(&m_gui,pElemAdc2,volt[2]);
		
		fclose(fadc2);
		//snprintf(temper,MAX_STR,"Voltage %.1f V",frmv[2]);
		//gslc_ElemSetTxtStr(&m_gui,pElemAdcText2,temper);

		fadc3 = fopen(adc[3], "r"); 
		assert(fadc3 != NULL);
		fscanf(fadc3, "%d", &volt[3]);
		frmv[3] = (volt[3] / 1023.0) * 3.600;
		gslc_ElemXGaugeUpdate(&m_gui,pElemAdc3,volt[3]);
		fclose(fadc3);
		//snprintf(temper,MAX_STR,"Voltage %.1f V",frmv[3]);
		//gslc_ElemSetTxtStr(&m_gui,pElemAdcText3,temper);
		
		//usleep(10 * 1000); // s * microseconds

		fadc4 = fopen(adc[4], "r"); 
		assert(fadc4 != NULL); 
		fscanf(fadc4, "%d", &volt[4]);
		frmv[4] = (volt[4] / 1023.0) * 3.600;
		gslc_ElemXGaugeUpdate(&m_gui,pElemAdc4,volt[4]);
		fclose(fadc4);
		
		//snprintf(temper,MAX_STR,"Voltage %.1f V",frmv[4]);
		//gslc_ElemSetTxtStr(&m_gui,pElemAdcText4,temper);

		fadc5 = fopen(adc[5], "r"); 
		assert(fadc5 != NULL);
		fscanf(fadc5, "%d", &volt[5]);
		frmv[5] = (volt[5] / 1023.0) * 3.600;
		gslc_ElemXGaugeUpdate(&m_gui,pElemAdc5,volt[5]);
		fclose(fadc5);
		//snprintf(temper,MAX_STR,"Voltage %.1f V",frmv[5]);
		//gslc_ElemSetTxtStr(&m_gui,pElemAdcText5,temper);

		fadc6 = fopen(adc[6], "r"); 
		assert(fadc6 != NULL);
		fscanf(fadc6, "%d", &volt[6]);
		frmv[6] = (volt[6] / 1023.0) * 3.600;
		gslc_ElemXGaugeUpdate(&m_gui,pElemAdc6,volt[6]);
		fclose(fadc6);
		//snprintf(temper,MAX_STR,"Voltage %.1f V",frmv[6]);
		//gslc_ElemSetTxtStr(&m_gui,pElemAdcText6,temper);

		fadc7 = fopen(adc[7], "r"); 
		assert(fadc7 != NULL);		
		fscanf(fadc7, "%d", &volt[7]);
		frmv[7] = (volt[7] / 1023.0) * 3.600;
		gslc_ElemXGaugeUpdate(&m_gui,pElemAdc7,volt[7]);
		fclose(fadc7);
		//snprintf(temper,MAX_STR,"Voltage %.1f V",frmv[7]);
		//gslc_ElemSetTxtStr(&m_gui,pElemAdcText7,temper);
		//usleep(10 * 100000); // s * microseconds
		
	}
	pthread_exit(NULL);
}

void INThandler(){
        exit(0);
}

void * keypad()
{
        char devname[] = "/dev/input/event0";
        int device = open(devname, O_RDONLY);
        struct input_event ev;

	gslc_tsElemRef*  pElemSlider     = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_SLIDER);
	gslc_tsElemRef*  pElemSlider2     = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_SLIDER2);

        while(1)
        {	
		int nPos = gslc_ElemXSliderGetPos(&m_gui,pElemSlider);
		int nPos2 = gslc_ElemXSliderGetPos(&m_gui,pElemSlider2);
		int CurrentPage = gslc_GetPageCur(&m_gui);
		int step = 5;
		char response[80];
		VCHI_INSTANCE_T vchi_instance;
		VCHI_CONNECTION_T *vchi_connection = NULL;

                read(device,&ev, sizeof(ev));
		printf("Code: %d Value: %d Type: %d\n",ev.code,ev.value,ev.type);         
		if(ev.type >=1 && ev.value >=1) {
			if (ev.code == 358) {
				pinex_conf();
			//Strony
			} else if (ev.code == 398) {
				gslc_SetPageCur(&m_gui,E_PG_MAIN); //Przełącza na stronę główną (Przycisk czerwony)
			} else if (ev.code == 399) {
				gslc_SetPageCur(&m_gui,E_PG_EXTRA); //Przełącza na stronę ekstra (Przycisk zielony)
			} else if (ev.code == 400) {
				gslc_SetPageCur(&m_gui,E_PG_OPTIONS); //Przełącza na stronę ustawień (Przycisk żółty)
			//End			
			} else if (ev.code == 115 && CurrentPage == 0) {
				gslc_ElemXSliderSetPos(&m_gui,pElemSlider, nPos + step);
			} else if (ev.code == 114 && CurrentPage == 0) {
				gslc_ElemXSliderSetPos(&m_gui,pElemSlider, nPos - step);
			} else if (ev.code == 402 && CurrentPage == 0) {
				gslc_ElemXSliderSetPos(&m_gui,pElemSlider2, nPos2 + step);
			} else if (ev.code == 403 && CurrentPage == 0) {
				gslc_ElemXSliderSetPos(&m_gui,pElemSlider2, nPos2 - step);
			} else if (ev.code == 388 && ev.value == 1) {
				vcos_init();

				if ( vchi_initialise( &vchi_instance ) != 0)
				{
					printf( "VCHI initialization failed\n" );
				}

				//create a vchi connection
				if ( vchi_connect( NULL, 0, vchi_instance ) != 0)
				{
					printf( "VCHI connection failed\n" );
				}
				vc_vchi_gencmd_init(vchi_instance, &vchi_connection, 1 );
				vc_gencmd(response, sizeof response, "display_power");
				response[sizeof(response) - 1] = '\n';						
				
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
				
				vc_gencmd_stop();

    				//close the vchi connection
    				if ( vchi_disconnect( vchi_instance ) != 0)
    				{
        				printf( "VCHI disconnect failed\n" );
    				}

			} else if (ev.code == 116) {
				switch (CurrentPage) 
				{
					case E_PG_MAIN:
						m_bQuit = true;
					case E_PG_EXTRA:
						m_bQuit = true;
					case E_PG_OPTIONS:
						m_bQuit = true;
				}				
			}
			if (ev.code == 4 && ev.value == 48) {
				gslc_ElemXSliderSetPos(&m_gui,pElemSlider2, 0);
				gslc_ElemXSliderSetPos(&m_gui,pElemSlider, 0);
			}
                }
        }

	pthread_exit(NULL);
}
void * Czas()
{
	time_t timer;
	char buffer[26];
	struct tm* tm_info;
	
	gslc_tsElemRef*  pElemRef;

	pElemRef = gslc_ElemCreateBox(&m_gui,GSLC_ID_AUTO,E_PG_MAIN,(gslc_tsRect){644,480,375,45});
  	gslc_ElemSetCol(&m_gui,pElemRef,(gslc_tsColor){181,200,245},(gslc_tsColor){59,58,120},GSLC_COL_BLACK);
  	gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
	//Zegarek
  	pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TXT_TIME,E_PG_MAIN,(gslc_tsRect){644+10,482,375,40},"",0,E_FONT_LIQUID_CRYSTAL_BOLD);
  	gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_TOP_LEFT);
  	gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  	gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);

	gslc_tsElemRef*  pElemTime   = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_TXT_TIME);
	while(1)
	{
	time(&timer);
	tm_info = localtime(&timer);

	strftime(buffer, 26, "%Y:%m:%d %H:%M:%S", tm_info);
	gslc_ElemSetTxtStr(&m_gui,pElemTime,buffer);	
	}

	pthread_exit(NULL);
}

void * rampa() 
{
	FILE* mq7;

	int 		volt[0];
	double 		frmv[0];
	char *adc [] =
  	{
		"/sys/bus/iio/devices/iio:device0/in_voltage0_raw"
	};
	//MQ-7
		gslc_tsElemRef*  pElemRef;
		
		pElemRef = gslc_ElemXGaugeCreate(&m_gui,E_RAMP,E_PG_MAIN,&m_sXRamp,(gslc_tsRect){15,400,500,100},0,1024,1024,GSLC_COL_YELLOW,false);
		gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_RED,GSLC_COL_BLACK,GSLC_COL_BLACK);
		gslc_ElemXGaugeSetStyle(&m_gui,pElemRef,GSLCX_GAUGE_STYLE_RAMP);

		gslc_tsElemRef* pElemRamp = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_RAMP);

	while(1) {
		
		mq7 = fopen(adc[0], "r"); 
		assert(mq7 != NULL);
		fscanf(mq7, "%d", &volt[0]);
		frmv[0] = (volt[0] / 1023.0) * 3.600;

		gslc_ElemXGaugeUpdate(&m_gui,pElemRamp,volt[0]);
		fclose(mq7);
		usleep(10 * 100000); // s * microseconds

	}

	pthread_exit(NULL);
}

int main( int argc, char *argv[] )
{
	char                temper[100];
	
	bcm_host_init();

        VCOS_STATUS_T sthread1;
	VCOS_STATUS_T sthread2;
	VCOS_STATUS_T sthread3;
	VCOS_STATUS_T sthread4;
	VCOS_STATUS_T sthread5;
	VCOS_STATUS_T sthread6;
	VCOS_STATUS_T sthread7;
	VCOS_THREAD_T thread1;
	VCOS_THREAD_T thread2;
	VCOS_THREAD_T thread3;
	VCOS_THREAD_T thread4;
	VCOS_THREAD_T thread5;
	VCOS_THREAD_T thread6;
	VCOS_THREAD_T thread7;
   	VCOS_THREAD_ATTR_T attrs;
   	vcos_thread_attr_init(&attrs);
   	vcos_thread_attr_settimeslice(&attrs,1);	
	
	wiringPiSetup();
	mcp23017Setup(AF_BASE, 0x27);
	opts_init();
	printf("D %s\n",opts_appname());
	// Initialize
	gslc_InitDebug(&DebugOut);
	UserInitEnv();
	if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { exit(1); }
//Load Fonts

	gslc_FontAdd(&m_gui,E_FONT_BTN,GSLC_FONTREF_FNAME,"fonts/Roboto-Black.ttf",12);
	gslc_FontAdd(&m_gui,E_FONT_TXT,GSLC_FONTREF_FNAME,"fonts/Roboto-Black.ttf",8);
	gslc_FontAdd(&m_gui,E_FONT_TITLE,GSLC_FONTREF_FNAME,"fonts/Pro-Display-tfb.ttf",32);
	gslc_FontAdd(&m_gui,E_FONT_CPUTEMP,GSLC_FONTREF_FNAME,"fonts/Roboto-Black.ttf",32);
	gslc_FontAdd(&m_gui,E_FONT_TEMP,GSLC_FONTREF_FNAME,"fonts/Amiko-Regular.ttf",20);
	gslc_FontAdd(&m_gui,E_FONT_DEJAVU_SANS_BOLD,GSLC_FONTREF_FNAME,"fonts/Roboto-Bold.ttf",14);
	gslc_FontAdd(&m_gui,E_FONT_HEAD,GSLC_FONTREF_FNAME,"fonts/Roboto-Black.ttf",20);
	gslc_FontAdd(&m_gui,E_FONT_TXT_ADC,GSLC_FONTREF_FNAME,"fonts/Roboto-Black.ttf",16);
	gslc_FontAdd(&m_gui,E_FONT_ALARM_CLOCK,GSLC_FONTREF_FNAME,"fonts/alarm-clock.ttf",32);
	gslc_FontAdd(&m_gui,E_FONT_LIQUID_CRYSTAL_NORMAL,GSLC_FONTREF_FNAME,"fonts/LiquidCrystal-Normal.ttf",32);
	gslc_FontAdd(&m_gui,E_FONT_LIQUID_CRYSTAL_BOLD,GSLC_FONTREF_FNAME,"fonts/LiquidCrystal-Bold.ttf",42);
	gslc_FontAdd(&m_gui,E_FONT_TITLE_TEMP,GSLC_FONTREF_FNAME,"fonts/BowlbyOneSC-Regular.ttf",22);

	
//---------------------------------------------------------------------------------------------------
  	InitOverlays(dirname(argv[0])); // Start display

	gslc_SetPageCur(&m_gui,E_PG_MAIN); // Start up display on main page
	// Save some element references for quick access
	//gslc_tsElemRef*  pElemCnt        = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_TXT_COUNT);
	//gslc_tsElemRef*  pElemProgress   = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_PROGRESS);

	gslc_tsElemRef*  pElemAppTitle	= gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_TXT_APP_TITLE);

	snprintf(temper,MAX_STR,"%s %s %s",opts_appname(), opts_desc(), opts_version());
	gslc_ElemSetTxtStr(&m_gui,pElemAppTitle,temper);
	
	sthread1 = vcos_thread_create(&thread1, "thread1", &attrs, Monitor, (void*)0);
   	vcos_assert(sthread1 == VCOS_SUCCESS);

	sthread2 = vcos_thread_create(&thread2, "thread2", &attrs, CPUUSAGE, (void*)0);
   	vcos_assert(sthread2 == VCOS_SUCCESS);

	sthread3 = vcos_thread_create(&thread3, "thread3", &attrs, ADC_VOLTS, (void*)0);
   	vcos_assert(sthread3 == VCOS_SUCCESS);

	sthread4 = vcos_thread_create(&thread4, "thread4", &attrs, keypad, (void*)0);
   	vcos_assert(sthread4 == VCOS_SUCCESS);

	sthread5 = vcos_thread_create(&thread5, "thread5", &attrs, Czas, (void*)0);
   	vcos_assert(sthread5 == VCOS_SUCCESS);

	sthread6 = vcos_thread_create(&thread6, "thread6", &attrs, ds3231, (void*)0);
   	vcos_assert(sthread6 == VCOS_SUCCESS);

	sthread7 = vcos_thread_create(&thread7, "thread7", &attrs, rampa, (void*)0);
   	vcos_assert(sthread7 == VCOS_SUCCESS);
	
	/*
	pthread_detach(thread1);
	pthread_detach(thread2);
	pthread_detach(thread3);
	pthread_detach(thread4);
	pthread_detach(thread5);
	pthread_detach(thread6);
	pthread_detach(thread7);*/

//---------------------------------------------------------------------------------------------------
  // Main event loop
  /*
  #if (TEST_UPDATE_RATE)
  uint32_t  nNumUpdates = 0;
  clock_t   sClkStart,sClkEnd;
  sClkStart = clock();
  #endif
  */
  signal(SIGINT, INThandler);
  m_bQuit = false;
  while (!m_bQuit) {

    // General counter
    //m_nCount++;

    // -----------------------------------

    // Update elements on active page
    //snprintf(acTxt,MAX_STR,"%u",m_nCount);
    //gslc_ElemSetTxtStr(&m_gui,pElemCnt,acTxt);
    //gslc_ElemXGaugeUpdate(&m_gui,pElemProgress,((m_nCount/200)%200));
    setlocale(LC_ALL, "pl_PL" );

  
    
    // Periodically call GUIslice update function
    gslc_Update(&m_gui);
    
    /* Simple update rate reporting
    #if (TEST_UPDATE_RATE)
    nNumUpdates++;
    sClkEnd = clock();

    if ((sClkEnd - sClkStart) > 10*200000) {
      // Reached end of interval, report average
      //printf("DBG: Update rate = [%6u per 10 sec]\n",nNumUpdates)
      // Reset interval
	
      nNumUpdates = 0;
      sClkStart = sClkEnd;

    }
    #endif
    */
  } 
  
  // bQuit

  // Read checkbox state
  // - Either read individual checkboxes
  //   bool bCheck = gslc_ElemXCheckboxGetState(&m_gui,E_ELEM_CHECK1);
  // - Or find one in the group that was checked (eg. for radio buttons)
  //   gslc_tsElem* pElem = gslc_ElemXCheckboxFindChecked(&m_gui,GSLC_GROUP_ID_NONE);

  // -----------------------------------
  // Close down display
  bcm_host_deinit();
  gslc_Quit(&m_gui);

  return 0;
}
