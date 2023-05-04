#include "PowerManager.hpp"

PowerManager::PowerManager()
{
pinMode (EN_4_2, OUTPUT);
pinMode (EN_5_2, OUTPUT);
digitalWrite(EN_4_2, 0);
digitalWrite(EN_5_2, 0);
state_4=0;
state_5=0;
}

PowerManager::~PowerManager()
{

}

void PowerManager::enable_5()
{
    state_5=1;
    digitalWrite(EN_5_2, state_5);
}

void PowerManager::diasble_5()
{
        state_5=0;
    digitalWrite(EN_5_2, state_5);
}

void PowerManager::enable_4()
{
    state_4=1;
    digitalWrite(EN_4_2, state_4);
}

void PowerManager::disable_4()
{
    state_4=0;
    digitalWrite(EN_4_2, state_4);
}

bool PowerManager::is5_Enabled()
{
    return state_5;
}

bool PowerManager::is4_Enabled()
{
    return state_4;
}
