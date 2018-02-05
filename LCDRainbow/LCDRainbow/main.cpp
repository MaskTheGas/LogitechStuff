#include <LogitechLCDLib.h>
#include <LogitechLEDLib.h>

#pragma comment ( lib, "LogitechLCDLib.lib")
#pragma comment ( lib, "LogitechLEDLib.lib")

#include <algorithm>
#include "rainbow.h"

int WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow) //WinMain so we have a graphical based application (no console)
{
	//Vars
	bool rainbowToggle = false;
	float rainbowSpeed = 0.002f;

	int type = LOGI_LCD_TYPE_MONO | LOGI_LCD_TYPE_COLOR;

	//Init
	LogiLcdInit(_wcsdup(L"RainbowLED"), type);
	LogiLcdUpdate(); //Force Update
	LogiLedInit();

	//Main Loop
	while (!LogiLcdIsButtonPressed(LOGI_LCD_COLOR_BUTTON_CANCEL))
	{
		LogiLcdColorSetTitle(_wcsdup(L"OK for Rainbow"));
		LogiLcdColorSetText(0, _wcsdup(L"Left for slower change"));
		LogiLcdColorSetText(1, _wcsdup(L"Rgith for faster change"));
		LogiLcdColorSetText(7, _wcsdup(L"Cancel to quit"));

		//Check Buttons
		if (LogiLcdIsButtonPressed(LOGI_LCD_COLOR_BUTTON_OK))
			rainbowToggle = !rainbowToggle;

		if (LogiLcdIsButtonPressed(LOGI_LCD_COLOR_BUTTON_LEFT))
			rainbowSpeed = 0.002f;

		if (LogiLcdIsButtonPressed(LOGI_LCD_COLOR_BUTTON_RIGHT))
			rainbowSpeed = 0.004f;

		//Rainbow Toggle
		if (rainbowToggle)
			SetRainbowColor(rainbowSpeed);
		else
			LogiLedRestoreLighting();

		//Update
		LogiLcdUpdate();
	}

	//Shutdown
	LogiLedShutdown();
	LogiLcdShutdown();
}