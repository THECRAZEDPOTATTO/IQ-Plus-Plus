#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#ifdef __APPLE__
#include <CUESDK/CUESDK.h>
#else
#include <CUESDK.h>
#endif
#include "games.h"
#include <atomic>
#include <thread>
#include <vector>
#include <unordered_set>
#include <cmath>
//Lightrender.h
std::vector<CorsairLedColor> GTA5WgetAvailableKeys()
{
    std::unordered_set<int> colorsSet;
    for (int deviceIndex = 0, size = CorsairGetDeviceCount(); deviceIndex < size; deviceIndex++)
    {
        if (const auto ledPositions = CorsairGetLedPositionsByDeviceIndex(deviceIndex))
        {
            for (auto i = 0; i < ledPositions->numberOfLed; i++)
            {
                const auto ledId = ledPositions->pLedPosition[i].ledId;
                colorsSet.insert(ledId);
            }
        }
    }

    std::vector<CorsairLedColor> colorsVector;
    colorsVector.reserve(colorsSet.size());
    int colorChoice = rand() % 2;
    for (const auto& ledId : colorsSet)
    {
        if (colorChoice == 0)
        {
            colorsVector.push_back({ static_cast<CorsairLedId>(ledId), 0, 0, 255 });
        }
        else
        {
            colorsVector.push_back({ static_cast<CorsairLedId>(ledId), 0, 0, 255 });//LEFT OVER JUNK DONT DEL IT WILL BRAKE LEDS AND RGB 
        }
    }
    return colorsVector;
}

void GTA5WperformPulseEffect(int waveDuration, std::vector<CorsairLedColor>& ledColorsVec,int frames)
{
    const auto timePerFrame = frames;
    bool isBlue = true;
    for (auto x = .0; x < 2; x += static_cast<double>(timePerFrame) / waveDuration)
    {
        if (isBlue)
        {
            for (auto& ledColor : ledColorsVec)
                ledColor.g = ledColor.b = 255, ledColor.r = 0;
        }
        else
        {
            for (auto& ledColor : ledColorsVec)
                ledColor.r = 255, ledColor.b = 0, ledColor.g = 0;
        }
        isBlue = !isBlue;
        CorsairSetLedsColorsAsync(static_cast<int>(ledColorsVec.size()), ledColorsVec.data(), nullptr, nullptr);
        std::this_thread::sleep_for(std::chrono::milliseconds(timePerFrame));
    }
}
void GTA5WPULSERUNNER(int ms) {
    std::atomic_int waveDuration{ 500 };
    std::atomic_bool continueExecution{ true };

    auto colorsVector = GTA5WgetAvailableKeys();
    if (colorsVector.empty()) {
        exit(1);
    }
    std::thread lightingThread([&waveDuration, &continueExecution, &colorsVector] {
        while (continueExecution) {
            GTA5WperformPulseEffect(waveDuration.load(), colorsVector,255);
        }
        });
    while (continueExecution) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        continueExecution = false;
    }
    lightingThread.join();
}
//END OF GTAWANTEDLEVEL

//END OF LOADING
void GTA5wanted() {
    std::vector<CorsairLedColor> ledColorsVec = GTA5WgetAvailableKeys();
    GTA5WperformPulseEffect(2000, ledColorsVec,225);
    GTA5WPULSERUNNER(10);
}
//END OF LOADING
void Loading() {
   
}
void GTA5(int status) {
    GTA5wanted();
}

void roblox(int status) {

}

void PC(int status) {
    
}
void rendergame(int gameid) {
	
}
