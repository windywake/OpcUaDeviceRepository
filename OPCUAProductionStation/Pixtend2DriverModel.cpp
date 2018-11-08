//===================================================================================
//
//  Copyright (C) 2018 Alex Lotz, Vineet Nagrath
//
//        lotz@hs-ulm.de
//        nagrath@hs-ulm.de
//
//        Servicerobotik Ulm
//        Christian Schlegel
//        Ulm University of Applied Sciences
//        Prittwitzstr. 10
//        89075 Ulm
//        Germany
//
//  Redistribution and use in source and binary forms, with or without modification,
//  are permitted provided that the following conditions are met:
//
//  1. Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//  2. Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//  3. Neither the name of the copyright holder nor the names of its contributors
//     may be used to endorse or promote products derived from this software
//     without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
//  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
//  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
//  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
//  OF THE POSSIBILITY OF SUCH DAMAGE.
//
//===================================================================================

#include "Pixtend2DriverModel.h"

#include <iostream>

namespace Smart {

//PiXtend Usage related items
#define BY_MODEL 83
#define UPDATE_DELAY 30
#define MAX_RETRY 100

Pixtend2DriverModel::Pixtend2DriverModel(const bool &startInternalThread)
:	OutputData(),	InputData()
{
	// Initializing Pixtend driver
	// Reset uC on start of application, in case user activated the uC SafeState
	Spi_uC_Reset();
	// Setup SPI using wiringPi
	Spi_SetupV2(0); //use SPI device 0.0 (PiXtend V2 -S-)
	Spi_SetupV2(1); //use SPI device 0.1 (PiXtend V2 -S- DAC)
	OutputData.byModelOut = BY_MODEL;
}

Pixtend2DriverModel::~Pixtend2DriverModel() {}

void Pixtend2DriverModel::Sync()
{
	bool retry = true;
	for(int i=0;i<MAX_RETRY && retry;i++)
	{
		retry = false;
		OutputData.byModelOut = BY_MODEL;
		if(Spi_AutoModeV2S(&OutputData, &InputData) != 0)
		{
			std::cout<<"Error in Spi_AutoModeV2S, trying again. Try Number "<<(i+2)<<" of Maximum "<<MAX_RETRY<<std::endl;
			retry = true;	
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(UPDATE_DELAY));
	}
}
void Pixtend2DriverModel::SetNBit(uint8_t &i, const uint8_t &n, const bool &v)
{
	if(v)		i |= (1u << n);
	else		i &= ~(1u << n);
}
void Pixtend2DriverModel::setDigitalOutput(const uint8_t &number, const bool &value)
{	
	if(number < 4)
	{
		SetNBit(OutputData.byDigitalOut, number, value);
		Sync();
	}
}
void Pixtend2DriverModel::setDigitalOutput(const uint8_t &value)
{	
	if(value < 16)
	{
		OutputData.byDigitalOut = value;
		Sync();
	}
}
bool Pixtend2DriverModel::getDigitalOutput(const uint8_t &number)
{	
	if(number < 4) {
		return OutputData.byDigitalOut & (1<<number);
	}
	return false;
}
uint8_t Pixtend2DriverModel::getDigitalOutput()
{	
	return OutputData.byDigitalOut;
}

void Pixtend2DriverModel::setRelayOutput(const uint8_t &number, const bool &value)
{	
	if(number < 4)
	{
		SetNBit(OutputData.byRelayOut, number, value);
		Sync();
	}
}
void Pixtend2DriverModel::setRelayOutput(const uint8_t &value)
{	
	if(value < 16)
	{
		OutputData.byRelayOut = value;
		Sync();
	}
}
bool Pixtend2DriverModel::getRelayOutput(const uint8_t &number)
{
	
	if(number < 4) {
		return OutputData.byRelayOut & (1<<number);
	}
	return false;
}
uint8_t Pixtend2DriverModel::getRelayOutput()
{	
	return OutputData.byRelayOut;
}

bool Pixtend2DriverModel::getDigitalInput(const uint8_t &number)
{	
	if(number < 4) {
		Sync();
		return InputData.byDigitalIn & (1<<number);
	}
	return false;
}
uint8_t Pixtend2DriverModel::getDigitalInput()
{	
	Sync();
	return InputData.byDigitalIn;
}
int Pixtend2DriverModel::waitOnDigitalInput(const uint8_t &number, const bool &value, const std::chrono::steady_clock::duration &timeout)
{
	int result = 0;
	std::chrono::time_point<std::chrono::system_clock> Start = std::chrono::system_clock::now();
	while((getDigitalInput(number) != value) 
	  &&  (timeout > std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - Start)))
	{		
		Sync();
	}
	return result;
}
int Pixtend2DriverModel::waitOnDigitalInput(const uint8_t &value, const std::chrono::steady_clock::duration &timeout)
{
	int result = 0;
	std::chrono::time_point<std::chrono::system_clock> Start = std::chrono::system_clock::now();
	while((getDigitalInput() != value)
	  &&  (timeout > std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - Start)))
	{
		Sync();
	}
	return result;
}
void Pixtend2DriverModel::setGPIOCtrl(const uint8_t &number, const bool &value)
{	
	if(number < 4)
	{
		SetNBit(OutputData.byGPIOCtrl, number, value);
		Sync();
	}
}
void Pixtend2DriverModel::setGPIOCtrl(const uint8_t &value)
{	
	if(value < 16)
	{
		OutputData.byGPIOCtrl = value;
		Sync();
	}
}
bool Pixtend2DriverModel::getGPIOCtrl(const uint8_t &number)
{	
	if(number < 4) {
		return OutputData.byGPIOCtrl & (1<<number);
	}
	return false;
}
uint8_t Pixtend2DriverModel::getGPIOCtrl()
{	
	return OutputData.byGPIOCtrl;
}
void Pixtend2DriverModel::setGPIO(const uint8_t &number, const bool &value)
{	
	if(number < 4)
	{
		SetNBit(OutputData.byGPIOOut, number, value);
		Sync();
	}
}
void Pixtend2DriverModel::setGPIO(const uint8_t &value)
{	
	if(value < 16)
	{
		OutputData.byGPIOOut = value;
		Sync();
	}
}
bool Pixtend2DriverModel::getGPIO(const uint8_t &number)
{	
	if(number < 4) {
		return OutputData.byGPIOOut & (1<<number);
	}
	return false;
}
uint8_t Pixtend2DriverModel::getGPIO()
{	
	return OutputData.byGPIOOut;
}
} /* namespace Smart */
