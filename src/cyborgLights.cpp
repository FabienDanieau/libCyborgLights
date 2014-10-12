#include "cyborgLights.h"
#include "constants.h"
#include <iostream>


int cyborgLight::getDeviceCount()
{
	struct libusb_context* usbContext;
	initUSB(usbContext);

	struct libusb_device **devs = nullptr;
	struct libusb_device *dev = nullptr;
	int count = 0;
	int i = 0;
	int errorCode = libusb_get_device_list(usbContext, &devs);

	if (errorCode < 0)
	{
		std::cerr << "Device list not retrievable" << std::endl;
		return count;
	}

	while ((dev = devs[i++]) != nullptr)
	{
		struct libusb_device_descriptor desc;
		errorCode = libusb_get_device_descriptor(dev, &desc);
		if (errorCode < 0)
		{
			std::cerr << "Device descriptor not retrievable - Device error code " << errorCode << std::endl;
			break;
		}
		if (desc.idVendor == cyborgLightsConstants::CYBORGLIGHTS_VENDOR && desc.idProduct == cyborgLightsConstants::CYBORGLIGHTS_PRODUCT)
		{
			++count;
		}
	}

	libusb_free_device_list(devs, 1);
	return count;
}

bool cyborgLight::initUSB(libusb_context *& usbContext)
{
	int errorCode = 0;
	if((errorCode = libusb_init(&usbContext)) < 0)
	{
		std::cerr << "Failed to initialize - " << errorCode << std::endl;
		return false;
	}

	return true;
}

void cyborgLight::close()
{
	if(m_cyborgLightDevice != nullptr)
	{
		int errorCode = libusb_release_interface(m_cyborgLightDevice, 0);
		if (errorCode < 0)
		{
			std::cerr << "Cannot release device interface - Device error code " << errorCode << std::endl;
			return;
		}
		libusb_close(m_cyborgLightDevice);
		m_cyborgLightDevice = nullptr;
	}
}

cyborgLight::cyborgLight(int index): m_cyborgLightDevice(nullptr)
{
	struct libusb_context* usbContext;
	initUSB(usbContext);

	struct libusb_device **devs = nullptr;
	struct libusb_device *found = nullptr;
	struct libusb_device *dev = nullptr;
	int i = 0;
	int count = 0;
	int errorCode = 0;

	if (libusb_get_device_list(usbContext, &devs) < 0)
	{
		std::cerr << "Device list not retrievable" << std::endl;
		return;
	}

	while ((dev = devs[i++]) != nullptr)
	{
		struct libusb_device_descriptor desc;
		errorCode = libusb_get_device_descriptor(dev, &desc);
		if (errorCode < 0)
		{
			std::cerr << "Device descriptor not retrievable - Device error code " << errorCode<< std::endl;
			libusb_free_device_list(devs, 1);
			return;
		}
		if (desc.idVendor == cyborgLightsConstants::CYBORGLIGHTS_VENDOR && desc.idProduct == cyborgLightsConstants::CYBORGLIGHTS_PRODUCT)
		{
			if(count == index)
			{
				found = dev;
				break;
			}
			++count;
		}
	}

	if (found)
	{
		errorCode = libusb_open(found, &m_cyborgLightDevice);
		if (errorCode < 0)
		{
			std::cerr << "Cannot open device - Device error code " << errorCode << std::endl;
			libusb_free_device_list(devs, 1);
			return;
		}
	}
	else
	{
		std::cerr << "Device index " << index << " out of range" << std::endl;
		return;
	}

	if ((errorCode = libusb_claim_interface(m_cyborgLightDevice, 0)) < 0)
	{
		std::cerr << "Cannot claim device interface - Device error code " << errorCode << std::endl;
		return;
	}
}

cyborgLight::~cyborgLight()
{
	setLights(0,0,0);
	close();
}

bool cyborgLight::setLights(unsigned char red, unsigned char green, unsigned char blue)
{
	if(m_cyborgLightDevice == nullptr)
		return false;

	unsigned char data[9] = {cyborgLightsConstants::CYBORGLIGHTS_COMMAND_COLOR,0x00,red,green,blue,0x00,0x00,0x00,0x00};
	int errorCode = libusb_control_transfer(m_cyborgLightDevice, 0x21, 0x09, 0x03a2, 0, data, sizeof(data), 1000);
	if ( errorCode < 0)
	{
		std::cerr << "Cannot set color - Device error code " << errorCode << std::endl;
		return false;
	}

	return true;
}

bool cyborgLight::setIntensity(unsigned char intensity) //NOT WORKING ?
{
	if(m_cyborgLightDevice == nullptr)
		return false;

	if(intensity > 100)
		intensity = 100;

	unsigned char data[3] = {cyborgLightsConstants::CYBORGLIGHTS_COMMAND_INTENSITY,0x00,intensity};
	int errorCode = libusb_control_transfer(m_cyborgLightDevice, 0x21, 0x09, 0x03a6, 0, data, sizeof(data), 1000);
	if (errorCode < 0)
	{
		std::cerr << "Cannot set intensity - Device error code " << errorCode << std::endl;
		return false;
	}
	return true;
}

/*void cyborgLight::getReport()
{
	int m_deviceErrorCode = 0;
	unsigned char data[9];
	if ((m_deviceErrorCode = libusb_control_transfer(m_cyborgLightDevice, cyborgLightsConstants::CYBORGLIGHTS_COMMAND_ENABLE, 0x01, 0x03b0, 0, data, sizeof(data), 1000)) < 0)
	{
		std::cerr << "Cannot read - Device error code " << m_deviceErrorCode << std::endl;
		return;
	}
}*/
