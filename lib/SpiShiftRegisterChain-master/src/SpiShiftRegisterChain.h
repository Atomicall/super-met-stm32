#ifndef _SpiShiftRegisterChain_h
#define _SpiShiftRegisterChain_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "SPI.h"

class SpiShiftRegisterChain {
public: // constructor/ destructor
	SpiShiftRegisterChain(unsigned int latchPin, unsigned int dataLengthBytes);
	~SpiShiftRegisterChain();

public: // functions
	void setBitOff(unsigned int bitNumber, bool writeData = true);
	void setBitOn(unsigned int bitNumber, bool writeData = true);
	void setDataToZeros();
	void toggleBit(unsigned int bitNumber, bool writeData = true);
	void writeData() const;
    uint8_t geByteArrayLength(){
        return _dataLengthBytes;
    }
    byte* getDataByteArray(){
        return _dataArray;
    }
    // возможна утечка памяти, записывать только указатель, который получили из get метода
    void setDataByteArray(byte* newArr){
        _dataArray = newArr;
    };

private: // functions
	void allocateMemory();
	void setPinModes() const;

private: // variables
	byte* _dataArray;
	unsigned int _dataLengthBytes;
	unsigned int _latchPin;
	SPISettings _spiSettings;
};


#endif