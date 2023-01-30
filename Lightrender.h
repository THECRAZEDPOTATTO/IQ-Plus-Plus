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
class GTAV {       
public:             
    int wantedlevl = 0;//4
    int robbery = 0;//5
    int misson = 0;//2
    int health = 100;//5
};
class Minecraft {
public:
    int cave = 0;//4
    int nether = 0;//4
    int deepdark = 0;//5
    int health = 20;//5
    int rain = 0;//3
};
GTAV GTA;
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
    for (auto i = 0; i < frames; ++i)
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
        if (GTA.wantedlevl > 0) {
            std::cout << "";
        }
        else {
            continueExecution = false;
        }
    }
    lightingThread.join();
}

//END OF GTAWANTEDLEVEL
//START OF GTAMON
std::vector<CorsairLedColor> GTA5MgetAvailableKeys()
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

void GTA5MperformPulseEffect(int waveDuration, std::vector<CorsairLedColor>& ledColorsVec, int frames)
{
    const auto timePerFrame = frames;
    bool isBlue = true;
    for (auto i = 0; i < frames; ++i)
    {
        if (isBlue)
        {
            for (auto& ledColor : ledColorsVec)
                ledColor.g = 225, ledColor.b = 0, ledColor.r = 0;
        }
        else
        {
            for (auto& ledColor : ledColorsVec)
                ledColor.r = 225, ledColor.b = 225, ledColor.g =255;
        }
        isBlue = !isBlue;
        CorsairSetLedsColorsAsync(static_cast<int>(ledColorsVec.size()), ledColorsVec.data(), nullptr, nullptr);
        std::this_thread::sleep_for(std::chrono::milliseconds(timePerFrame));
    }
}
void GTA5MPULSERUNNER(int ms) {
    std::atomic_int waveDuration{ 500 };
    std::atomic_bool continueExecution{ true };

    auto colorsVector = GTA5MgetAvailableKeys();
    if (colorsVector.empty()) {
        exit(1);
    }
    std::thread lightingThread([&waveDuration, &continueExecution, &colorsVector] {
        while (continueExecution) {
            GTA5MperformPulseEffect(waveDuration.load(), colorsVector, 255);
        }
        });
    while (continueExecution) {
        if (GTA.robbery == 1) {
            std::cout << "";
        }
        else {
            continueExecution = false;
        }
    }
    lightingThread.join();
}
//END OF GTANON
//START OF GTADEATH
std::vector<CorsairLedColor> GTA5DgetAvailableKeys(){

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

void GTA5DperformPulseEffect(int waveDuration, std::vector<CorsairLedColor>& ledColorsVec, int frames)
{
    const auto timePerFrame = frames;
    bool isBlue = true;
    for (auto i = 0; i < frames; ++i)
    {
        if (isBlue)
        {
            for (auto& ledColor : ledColorsVec)
                ledColor.g = 0, ledColor.b = 0, ledColor.r = 225;
        }
        else
        {
            for (auto& ledColor : ledColorsVec)
                ledColor.r = 225, ledColor.b = 225, ledColor.g = 255;
        }
        isBlue = !isBlue;
        CorsairSetLedsColorsAsync(static_cast<int>(ledColorsVec.size()), ledColorsVec.data(), nullptr, nullptr);
        std::this_thread::sleep_for(std::chrono::milliseconds(timePerFrame));
    }
}
void GTA5DPULSERUNNER(int ms) {
    std::atomic_int waveDuration{ 500 };
    std::atomic_bool continueExecution{ true };

    auto colorsVector = GTA5DgetAvailableKeys();
    if (colorsVector.empty()) {
        exit(1);
    }
    std::thread lightingThread([&waveDuration, &continueExecution, &colorsVector] {
        while (continueExecution) {
            GTA5DperformPulseEffect(waveDuration.load(), colorsVector, 255);
        }
        });
    while (continueExecution) {
        if (GTA.health < 1) {
            std::cout << "";
        }
        else {
            continueExecution = false;
        }
    }
    lightingThread.join();
}





//END OF LOADING
void GTA5wanted() {
    std::vector<CorsairLedColor> ledColorsVec = GTA5WgetAvailableKeys();
    GTA5WperformPulseEffect(2000, ledColorsVec,225);
    GTA5WPULSERUNNER(10);
}
void GTA5ROB() {
    std::vector<CorsairLedColor> ledColorsVec = GTA5MgetAvailableKeys();
    GTA5MperformPulseEffect(2000, ledColorsVec, 300);
    GTA5MPULSERUNNER(10);
}
void GTA5Death() {
    std::vector<CorsairLedColor> ledColorsVec = GTA5DgetAvailableKeys();
    GTA5DperformPulseEffect(2000, ledColorsVec, 500);
    GTA5DPULSERUNNER(10);
}
void Loading() {
   
}
void GTA5(int status) {
    if (status == 1) {
        GTA5wanted();
    }else if(status == 2) {
        GTA5ROB();
    }else if (status == 3) {
        GTA5Death();
    }
}
void qenderGTA() {
    GTA5ROB();
    GTA5wanted();
    GTA5Death();
}
void roblox(int status) {

}

void PC(int status) {
    
}
void rendergame(int gameid) {
	
}
