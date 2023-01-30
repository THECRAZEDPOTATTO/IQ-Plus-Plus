
#define CORSAIR_LIGHTING_SDK_DISABLE_DEPRECATION_WARNINGS
#include "games.h"
#ifdef __APPLE__
#include <CUESDK/CUESDK.h>
#else
#include <CUESDK.h>
#endif
#include "Lightrender.h"
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <unordered_set>
#include <cmath>
#include "inject.hpp"
const char* toString(CorsairError error)
{
	switch (error) {
	case CE_Success:
		return "CE_Success";
	case CE_ServerNotFound:
		return "CE_ServerNotFound";
	case CE_NoControl:
		return "CE_NoControl";
	case CE_ProtocolHandshakeMissing:
		return "CE_ProtocolHandshakeMissing";
	case CE_IncompatibleProtocol:
		return "CE_IncompatibleProtocol";
	case CE_InvalidArguments:
		return "CE_InvalidArguments";
	default:
		return "unknown error";
	}
}
int random(int a, int b)
{
	srand(time(NULL));

	int r = rand() % 2;

	if (r == 0)
		return a;
	else
		return b;
}
bool errorCheck(const std::string& msg) {
	auto error = CorsairGetLastError();
	if (error != CorsairError::CE_Success) {
		std::cerr << msg << " (Error: " << toString(error) << ')' << std::endl;
		return true;
	}

	return false;
}
int main()
{
	CorsairPerformProtocolHandshake();
	if (const auto error = CorsairGetLastError()) {
		std::cout << "Handshake failed: " << toString(error) << "\nPress any key to quit." << std::endl;
		getchar();
		return -1;
	}
	while (true) {
		std::cout << "\x1B[2J\x1B[H";
		CorsairPerformProtocolHandshake();
		if (errorCheck("Handshake device error")) {
			getchar();
			return -1;
		}
		const auto devicesCount = CorsairGetDeviceCount();
		for (int i = 0; i < devicesCount; ++i) {
			const auto info = CorsairGetDeviceInfo(i);
			if (!info) {
				errorCheck("Get device info error");
				continue;
			}
			try {
				std::cout << "------------------------------" << "\nDevice:" << info->model << "\nType: " << info->type << "\nProduct ID: " << info->deviceId << "\n------------------------------" << std::endl;
			}
			catch (const std::string& ex) {
				std::cout << "This Divice has an Error:" << info->model << std::endl;
				std::cout << "Error: " << ex << std::endl;
				getchar();
				exit(1);
			}

		}
		std::string input = "NOTSET";
		std::cout << "Do You See All Of Your Devices[Y/n]: ";
		std::cin >> input;
		if (input == "Y" || input == "y") {
			break;
		}
		else if (input == "n" || input == "N") {
			std::cout << "Reloading...";
			std::cout << input;
		}
		else {
			std::cout << "Invalid Input";
			std::cout << "Reloading...";
		}
	}
	std::cout << "Dumping Games" << std::endl;
	findgames();
	std::cout << "\nDone!" << std::endl;
	int gameonpic = 19;
	std::cout << "What Game Would You Like to Connect To[1/20]:";
	std::cin >> gameonpic;
	if (gameonpic == 0) {
		gameonpic = 19;
		std::cout << "Using Default Settings: Screen Capture" << std::endl;
	}
	else if (1 <= gameonpic && gameonpic <= 20) {
		std::cout << "Loading ICUE++ On Game" << std::endl;
	}
	else {
		std::cout << "Not a Valid input!" << std::endl;// OMG WORDS YOUR FORBIDDEN TO SAY ;)
		getchar();
		exit(1);
	}
	int INPUTMEM = 0x118;
	std::cout << "Taking Memory Input Form: " << INPUTMEM << std::endl;
	/*
	GTA[1,2,3] 1 = wantde 2 = robbery 3 = death
	
	*/
	return 0;
}
