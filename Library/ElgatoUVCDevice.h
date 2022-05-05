/*
MIT License

Copyright (c) 2022 Corsair Memory, Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <memory>

#include "EGAVResult.h"
#include "EGAVDevice.h"
#include "HDMIInfoFramesAPI.h"

#ifdef _MSC_VER
#include "win/EGAVHIDImplementation.h"
#else
#include "mac/EGAVHIDImplementation.h"
#endif


const EGAVDeviceID deviceIDHD60SPlus (EGAVBusType::USB, 0x0FD9, 0x06A); //!< HD60 S+
const EGAVDeviceID deviceIDHD60X     (EGAVBusType::USB, 0x0FD9, 0x082); //!< HD60 X

inline bool IsNewDeviceType(const EGAVDeviceID& inDeviceID) { return (inDeviceID == deviceIDHD60X); }



//==============================================================================
// # Class ElgatoUVCDevice
//==============================================================================

class ElgatoUVCDevice
{

public:
	ElgatoUVCDevice(std::shared_ptr<EGAVHIDInterface> hid, bool isNewDeviceType);

	//! @brief Works with HD60 S+ and HD60 X
	void SetHDRTonemappingEnabled(bool inEnable);

	//! @brief Works with HD60 S+ and HD60 X
	EGAVResult GetHDMIHDRStatusPacket(HDMI_GENERIC_INFOFRAME& outFrame);

	//! @brief Works with HD60 S+ and HD60 X
	EGAVResult IsVideoHDR(bool& outIsHDR);


private:
	EGAVResult WriteI2cData(uint8_t inI2CAddress, uint8_t inRegister, uint8_t* inData, uint8_t inLength);
	EGAVResult ReadI2cData(uint8_t inI2CAddress, uint8_t inRegister, uint8_t* outData, uint8_t inLength);

	bool mNewDeviceType = false; //!< true: HD60 X , false: HD60 S+

	std::shared_ptr<EGAVHIDInterface> mHIDImpl;
	std::recursive_mutex mHIDMutex;
};