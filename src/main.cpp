/*
 * Based on Blink_AnalogRead example from: https://github.com/feilipu/Arduino_FreeRTOS_Library
 * Modified by: Frederic Pillon <frederic.pillon (at) st.com>
 */
#include <Arduino.h>
#include <Wire.h>
#include "defines.h"
#include <PowerManager.hpp>
#include <uart_mux.h>

#include <SIM800L.h>
#include <Gpsneo.h>

/*                          s0   |  s1
sim800                      0    |   0
nc                          0    |   1
sds011_particles            1    |   0
gps                         1    |   1
*/


HardwareSerial Serial2(PA3, PA2);
HardwareSerial Serial3(PB11, PB10);
PowerManager powerManager;
Uart_multiplexer uart_mux;
SIM800L *sim800l;
Gpsneo* gps;


void testSim800()
{
      Serial1.println("Start of test protocol");
      // Wait until the module is ready to accept AT commands
      while (!sim800l->isReady())
      {
            Serial1.println(F("Problem to initialize AT command, retry in 1 sec"));
            delay(1000);
      }
      // Active echo mode (for some module, it is required)
      sim800l->enableEchoMode();
      Serial1.println("Module ready");
      // Print version
      Serial1.print("Module ");
      Serial1.println(sim800l->getVersion());
      Serial1.print("Firmware ");
      Serial1.println(sim800l->getFirmware());

      // Print SIM card status
      Serial1.print(F("SIM status "));
      Serial1.println(sim800l->getSimStatus());

      // Print SIM card number
      Serial1.print("SIM card number ");
      Serial1.println(sim800l->getSimCardNumber());

      // Wait for the GSM signal
      uint8_t signal = sim800l->getSignal();
      while (signal <= 0)
      {
            delay(1000);
            signal = sim800l->getSignal();
      }

      if (signal > 5)
      {
            Serial1.print(F("Signal OK (strenght: "));
      }
      else
      {
            Serial1.print(F("Signal low (strenght: "));
      }
      Serial1.print(signal);
      Serial1.println(F(")"));
      delay(1000);

      // Wait for operator network registration (national or roaming network)
      NetworkRegistration network = sim800l->getRegistrationStatus();
      while (network != REGISTERED_HOME && network != REGISTERED_ROAMING)
      {
            delay(1000);
            network = sim800l->getRegistrationStatus();
      }
      Serial1.println(F("Network registration OK"));

      Serial1.println("End of test protocol");
}

void setup()
{
      Serial1.begin(115200);
      Serial2.begin(9600);
      powerManager.diasble_5();
      powerManager.disable_4();
      sim800l = new SIM800L((Stream *)&Serial2, GSM_RST, 200, 512, (Stream *)&Serial1);
}

void loop()
{
      uart_mux.switchDevice(SIM800);
      testSim800();
      while (1);
}

//  byte error, address;
//       int nDevices;

//       Serial.println("Scanning...");

//       nDevices = 0;
//       for (address = 1; address < 127; address++)
//       {
//             // The i2c_scanner uses the return value of
//             // the Write.endTransmisstion to see if
//             // a device did acknowledge to the address.

//             Wire.beginTransmission(address);
//             error = Wire.endTransmission();

//             if (error == 0)
//             {
//                    Serial.print("SDA1");
//                   Serial.print("I2C device found at address 0x");
//                   if (address < 16)
//                         Serial.print("0");
//                   Serial.print(address, HEX);
//                   Serial.println("  !");

//                   nDevices++;
//             }
//             else if (error == 4)
//             {
//                   Serial.print("Unknown error at address 0x");
//                   if (address < 16)
//                         Serial.print("0");
//                   Serial.println(address, HEX);
//             }
//       }
//       if (nDevices == 0)
//             Serial.println("No I2C devices found\n");
//       else
//             Serial.println("done\n");
//      delay(1000);
