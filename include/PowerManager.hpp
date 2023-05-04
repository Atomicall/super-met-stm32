#ifndef __PowerManager_H__
#define __PowerManager_H__
#include <Arduino.h>
#include "defines.h"

class PowerManager
{

private:
bool state_4;
bool state_5;

public:
	PowerManager();
	~PowerManager();
	void enable_5();
	void diasble_5();
	void enable_4();
	void disable_4();
	bool is5_Enabled();
	bool is4_Enabled();
};

#endif // __PowerManager_H__