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
#include "NovaSDS011.h"
#include "SpiShiftRegisterChain.h"

/*                          s0   |  s1
sim800                      0    |   0
nc                          0    |   1
sds011_particles            1    |   0
gps                         1    |   1
*/


HardwareSerial Serial2(PA3, PA2);
PowerManager powerManager;
Uart_multiplexer uartMux;
SIM800L *sim800l;
Gpsneo *gps;
NovaSDS011 sds011;
SpiShiftRegisterChain spiReg(SR_LATCH, 2);


char latitud[11];
char latitudHemisphere[3];
char longitud[11];
char longitudMeridiano[3];
float sdsP25, sdsP10;

void testGps() {
    gps->getDataGPRMC(latitud,
                      latitudHemisphere,
                      longitud,
                      longitudMeridiano);
    Serial.println("fuck gps");
    Serial.println(latitud);
    Serial.println(latitudHemisphere);
    Serial.println(longitud);
    Serial.println(longitudMeridiano);
}
void testSDS011() {
    if (sds011.setWorkingMode(WorkingMode::mode_work)) {
        Serial1.println("SDS011 working mode \"Work\"");
    } else {
        Serial1.println("FAIL: Unable to set working mode \"Work\"");
    }
    if (sds011.setDutyCycle(5)) {
        Serial1.println("SDS011 Duty Cycle set to 5min");
    } else {
        Serial1.println("FAIL: Unable to set Duty Cycle");
    }
    if (sds011.queryData(sdsP25, sdsP10) == QuerryError::no_error) {
        Serial1.println(String(millis() / 1000) + "s:PM2.5=" + String(sdsP25) + ", PM10=" + String(sdsP10));
    }
}
void testSim800() {
    Serial1.println("Start of test protocol");
    // Wait until the module is ready to accept AT commands
    while (!sim800l->isReady()) {
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
}
void testSpiReg(){
    spiReg.setDataToZeros();
    byte* data = spiReg.getDataByteArray();
    uint8_t size = spiReg.geByteArrayLength();
    for (uint8_t i=0; i< size; i++){
        data[i] = 0b11111111;
    }
    spiReg.setDataByteArray(data);
    spiReg.writeData();
    delay(5000);
    for (uint8_t i=0; i< size; i++){
        data[i] = 0b10101010;
    }
    spiReg.writeData();
    delay(10000);
}

void measureAnalog(){};
void measureDigital(){};
void warmSensors(){};
void formJSON(){};
void sendJSON(){};
void getDataFromGPS(){};
void getDataFromSDS(){};

void setup() {
    //esp uart
    Serial1.begin(115200);
    //mux uart
    Serial2.begin(9600);

    powerManager.init();
    uartMux.init();

    powerManager.enable_5();
    powerManager.enable_4();

    sim800l = new SIM800L((Stream *) &Serial2, GSM_RST, 200, 512, (Stream *) &Serial1);
    gps = new Gpsneo(MUX_RX, MUX_TX);
    sds011.begin(MUX_RX, MUX_TX);

    uartMux.switchDevice(GPS);
    testGps();
    uartMux.switchDevice(SDS011);
    testSDS011();
    uartMux.switchDevice(SIM800);
    testSim800();
    testSpiReg();


}

void loop() {

    while (1) {};
}


