#include "cyborgLights.h"
#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char ** argv)
{
	cout << "Test CyborgLights library" << endl;

	cout << cyborgLight::getDeviceCount() <<" devices connected" << endl;

	cyborgLight light;
	light.setIntensity(0);
	light.setLights(255,0,0);


	cyborgLight l2(1);
	light.setIntensity(100);
	l2.setLights(0,255,0);

	sleep(1);

	return 0;
}
