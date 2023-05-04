#include <Arduino.h>
#include "defines.h"

/*               s0   |  s1
sim800           0    |   0
nc               0    |   1
sds011_particles 1    |   0
gps              1    |   1   
*/

enum CONNECTED_DEVICE {
    SIM800, 
    GPS,
    SDS011
};


// только мультиплексирует, без общения
class Uart_multiplexer
{
private:
CONNECTED_DEVICE current_device;

uint8_t s0;
uint8_t s1;
bool busyFlag = 0;

void initPins(){
    pinMode(EN_4_2, OUTPUT);
    pinMode(MUX_S0, OUTPUT);
    pinMode(MUX_S1, OUTPUT);
    pinMode(MUX_RX, OUTPUT);
    pinMode(MUX_TX, OUTPUT);
}

public:
    Uart_multiplexer ();
    ~Uart_multiplexer();
    CONNECTED_DEVICE getCurrentlySelecteDevice();
    void switchDevice(CONNECTED_DEVICE switchTo);
    void setBusy(bool state);
    bool isBusy();

};