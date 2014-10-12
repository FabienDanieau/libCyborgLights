#ifndef CONSTANTS__H__INCLUDE
#define CONSTANTS__H__INCLUDE

namespace cyborgLightsConstants{
	static constexpr unsigned int CYBORGLIGHTS_VENDOR = 0x06a3;
	static constexpr unsigned int CYBORGLIGHTS_PRODUCT = 0x0dc5;

	//Commands
	static constexpr unsigned char CYBORGLIGHTS_COMMAND_ENABLE = 0xa1;
	static constexpr unsigned char CYBORGLIGHTS_COMMAND_COLOR = 0xa2;
	static constexpr unsigned char CYBORGLIGHTS_COMMAND_POSITION = 0xa4;
	static constexpr unsigned char CYBORGLIGHTS_COMMAND_V_POSITION = 0xa5;
	static constexpr unsigned char CYBORGLIGHTS_COMMAND_INTENSITY = 0xa6;
	static constexpr unsigned char CYBORGLIGHTS_COMMAND_RESET = 0xa7;

	//Positions
	static constexpr unsigned char CYBORGLIGHTS_POSITION_CENTER[2] = {0x00,0x01};
	static constexpr unsigned char CYBORGLIGHTS_POSITION_N[2] = {0x01,0x00};
	static constexpr unsigned char CYBORGLIGHTS_POSITION_NE[2] = {0x02,0x00};
	static constexpr unsigned char CYBORGLIGHTS_POSITION_E[2] = {0x04,0x00};
	static constexpr unsigned char CYBORGLIGHTS_POSITION_SE[2] = {0x08,0x00};
	static constexpr unsigned char CYBORGLIGHTS_POSITION_S[2] = {0x10,0x00};
	static constexpr unsigned char CYBORGLIGHTS_POSITION_SW[2] = {0x20,0x00};
	static constexpr unsigned char CYBORGLIGHTS_POSITION_W[2] = {0x40,0x00};
	static constexpr unsigned char CYBORGLIGHTS_POSITION_NW[2] = {0x80,0x00};

	//Vertical Positions
	static constexpr unsigned char CYBORGLIGHTS_VPOSITION_ANY = 0x00;
	static constexpr unsigned char CYBORGLIGHTS_VPOSITION_HIGH = 0x02;
	static constexpr unsigned char CYBORGLIGHTS_VPOSITION_MIDDLE = 0x04;
	static constexpr unsigned char CYBORGLIGHTS_VPOSITION_LOW = 0x08;
}


#endif
