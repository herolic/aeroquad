/*
  AeroQuad v3.0 - May 2011
  www.AeroQuad.com
  Copyright (c) 2011 Ted Carancho.  All rights reserved.
  An Open Source Arduino based multicopter.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _AQ_BATTERY_MONITOR_BASE_
#define _AQ_BATTERY_MONITOR_BASE_

#include "BatteryMonitor.h"


#define BATTERY_MOBITOR_OK 0
#define BATTERY_MOBITOR_WARNING 1
#define BATTERY_MOBITOR_ALARM 2

#define BATTERYPIN 0      // Ain 0 (universal to every Arduino), pin 55 on Mega (1280)

float lowVoltageWarning = 10.2; //10.8;  // Pack voltage at which to trigger alarm (first alarm)
float lowVoltageAlarm = 9.5; //10.2;     // Pack voltage at which to trigger alarm (critical alarm)
float batteryVoltage = 0.0;
float diode = 0.0; // raw voltage goes through diode on Arduino
float batteryScaleFactor = 0.0;
byte batteryStatus = BATTERY_MOBITOR_OK;
  
void initializeBatteryMonitor(float diodeValue = 0.0);
const float readBatteryVoltage(byte); // defined as virtual in case future hardware has custom way to read battery voltage

void measureBatteryVoltage(boolean armed) {
  batteryVoltage = filterSmooth(readBatteryVoltage(BATTERYPIN), batteryVoltage, 0.1);
  if (batteryVoltage < lowVoltageWarning) {
    batteryStatus = BATTERY_MOBITOR_WARNING;
  }
  else if (batteryVoltage < lowVoltageAlarm) {
	batteryStatus = BATTERY_MOBITOR_ALARM;
  }
  else {
    batteryStatus = BATTERY_MOBITOR_OK;
  }
}
  

#endif