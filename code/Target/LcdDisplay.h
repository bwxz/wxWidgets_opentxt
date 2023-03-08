#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include "ToPSyncInterfaceTypes.h"

typedef struct LcdStruct
{
	LcdScreenBitMask	defaultScreenMask; //this is the initialised screen mask or one set by api call
	LcdScreenBitMask	screenMask;
	uint8				numScreensToDisplay;
	uint8				screensToDisplay[LCD_MAX_NUMBER_OF_SCREENS];
	float				displayPeriod;
	uint8				currentscreen;
	Bool				freezeDisplay;
	Bool				freezeDisplayFromSwitch;
	Bool				switchesFitted;
#ifdef USE_ACS1790
	char				userData[LCD_USER_DATA_LENGTH];
#endif
} Lcd;

//void LCDPrint(void);
void LCDPrint();
void LCDPrint952x(Lcd *lcdData);
void InitialiseLCD952x(Lcd *lcdData);
void ResetLCD952x(Lcd *lcdData);
Bool SetLCDBitMask(Lcd *lcdData, LcdScreenBitMask mask);
Bool SetDisplayPeriod(Lcd *lcdData, float period);
void SetFreezeDisplay(Lcd *lcdData, Bool enable);

Bool GetLCDBitMask(Lcd *lcdData, LcdScreenBitMask *mask);
Bool GetDisplayPeriod(Lcd *lcdData, float *period);
void GetFreezeDisplay(Lcd *lcdData, Bool *enable);

#ifdef USE_ACS1790
Bool SetLcdUserData(Lcd *lcdData, uint8 const offset, const uint8 * const data, uint8 const length);
Bool GetLcdUserData(Lcd *lcdData, uint8 const offset, uint8 * data, uint8 const length);
#endif

#endif
