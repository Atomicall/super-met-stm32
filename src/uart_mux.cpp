#include "uart_mux.h"

Uart_multiplexer::Uart_multiplexer()
{
    switchDevice(SIM800);
}

Uart_multiplexer::~Uart_multiplexer()
{
}

CONNECTED_DEVICE Uart_multiplexer::getCurrentlySelecteDevice()
{
    return CONNECTED_DEVICE();
}

void Uart_multiplexer::switchDevice(CONNECTED_DEVICE switchTo)
{
    switch (switchTo)
    {
    case SIM800:
    {
        s0 = 0;
        s1 = 0;
        current_device = SIM800;
        break;
    }
    case GPS:
    {
        s0 = 1;
        s1 = 1;
        current_device = GPS;
        break;
    }
    case SDS011:
    {
        s0 = 1;
        s1 = 0;
        current_device = SDS011;
        break;
    }

    default:
    {
        break;
    }
    digitalWrite(MUX_S0, s0);
    digitalWrite(MUX_S1, s1);
    // delay?
    }
}

void Uart_multiplexer::setBusy(bool state)
{
    this->busyFlag = state;
}

bool Uart_multiplexer::isBusy()
{
    return busyFlag;
}
