#include <Arduino.h>
#include "defines.h"

/*               s0   |  s1
sim800           0    |   0
nc               0    |   1
sds011_particles 1    |   0
gps              1    |   1
*/

enum CONNECTED_DEVICE
{
    SIM800,
    GPS,
    SDS011
};

// только мультиплексирует, без общения
class Uart_multiplexer
{
private:
    CONNECTED_DEVICE current_device;
    bool s0;
    bool s1;
    bool busyFlag = 0;

public:
    void init()
    {
        pinMode(MUX_S0, OUTPUT);
        pinMode(MUX_S1, OUTPUT);
        switchDevice(SIM800);
    }
    Uart_multiplexer();
    ~Uart_multiplexer();
    CONNECTED_DEVICE getCurrentlySelecteDevice();
    void switchDevice(CONNECTED_DEVICE switchTo);
    void setBusy(bool state);
    bool isBusy();
};