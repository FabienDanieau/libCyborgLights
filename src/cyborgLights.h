#ifndef CYBORGLIGHTS_H__INCLUDE
#define CYBORGLIGHTS_H__INCLUDE

#include <libusb-1.0/libusb.h>

class cyborgLight{
public:
	cyborgLight(int index = 0);
	~cyborgLight();
	static int getDeviceCount();
	bool setLights(unsigned char red, unsigned char green, unsigned char blue); //0 <= color <= 255
	bool setIntensity(unsigned char intensity); // 0 <= intensity <= 100

private:
	static bool initUSB(libusb_context *& usbContext);
	void close();
	void getReport();

private:
	libusb_device_handle* m_cyborgLightDevice;
};


#endif
