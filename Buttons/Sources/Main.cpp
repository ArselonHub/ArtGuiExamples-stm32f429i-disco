/*
 * Main.cpp
 *
 *  Created on: Dec 6, 2017
 *      Author: denizcan
 */

#include <Art/Devices/ILI9341Rgb.h>
#include <Art/Devices/IS42S16400J_7.h>
#include <Art/Devices/Stmpe811I2C.h>
#include <Art/Pmcc.h>
#include <Art/Desktop.h>
#include <Art/Application.h>
#include <Art/Timer.h>
#include <Art/Debug.h>
#include <Art/Ifm.h>
#include <Art/FlashDataStore.h>
#include <Art/DefaultDataStore.h>
#include <MainWindow.h>
#include <Art/Bsp.h>
#include <Art/LevelDetector.h>

using namespace Art;

// DataStore for tagget data storage, such as calibration data etc..
FlashDataStore		dataStore;

IS42S16400J_7		sdram;
ILI9341FbRgb565		display;
Stmpe811I2C 		touchSensor;
MainWindow			mainWindow;
LevelDetector		buttonDetector;

void doButtonPressed(void*)
{
	static const Rotation nextRotation[] = { Rotation90, Rotation180, Rotation270, Rotation0 };
	Display* display = desktop()->display();
	display->setRotation(nextRotation[display->rotation()]);
}

int main()
{
	// Configure PLL using 8MHz cyristal to generate 168Mhz
	pmcc()->setHseFrequency(8000000);
	pmcc()->setProfile(pmccProfile168MhzFromHse());

	led()->configure(PinFunctionOutput0);

	// use ifm (internal flash memory) to store calibration values
	ifm()->open();
	dataStore.setFlash(ifm());
	dataStore.setStartAddress(0x08008000);
	dataStore.setEndAddress(  0x0800FFFF);
	dataStore.erase();
	dataStore.open();
	defaultDataStore()->setTarget(&dataStore);

	sdram.setController(fmc()->sdramController1());
	sdram.open();

	// configure display, it is connected to spi5 and ltdc
	// also needs sdram space to store it's picture
	spi5()->setMisoPin(pf9());
	spi5()->setSckPin(pf7());
	display.setSpiPort(spi5());
	display.setSpiSelectPin(pc2());
	display.setDataSelectPin(pd13());
	display.setDisplayController(ltdc());
	display.setFrameBuffer(sdram.pointer());
	display.open();

	// configure touch sensor, open with defaultDataStore to restore calibration data
	touchSensor.setEventPin(pa15());
	touchSensor.setI2CPort(i2c3());
	touchSensor.openWith(defaultDataStore());

	buttonDetector.onEvent().connect(doButtonPressed);
	buttonDetector.setPin(button());
	buttonDetector.open();

	//TODO Implement a method to update layout before showing
	mainWindow.updateLayout();
	mainWindow.show();

	// run GUI application
	application()->run();
}
