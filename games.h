#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <TlHelp32.h>
#include <stdio.h>
#include <locale>
#include <codecvt>
bool IsProcessRunning(const std::string& processName)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
        return false;

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hSnapshot, &pe))
    {
        CloseHandle(hSnapshot);
        return false;
    }

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    do
    {
        std::string exeFile = converter.to_bytes(pe.szExeFile);
        if (processName == exeFile)
        {
            CloseHandle(hSnapshot);
            return true;
        }
    } while (Process32Next(hSnapshot, &pe));

    CloseHandle(hSnapshot);
    return false;
}
//IDS FOR GAMES
void findgames(){
    int CORES = 99;
    int game = 0;
    int roblox = 1;
    int chrome = 2;
    int codw2 = 3;
    int codwz = 4;
    int codemw = 5;
    int minecraft = 6;
    int wallpen = 7;
    int spotf = 9;
    int ssof = 10;
    int normal = 11;
    int intak = 12;
    int gtaV = 13;
    int portl = 14;
    int nvida = 15;
    int weath = 16;
    int gay = 17; //For Vesper leave this note here 
    int bootD = 18;
    int scrnmaster = 19;
    int discord = 20;
    int trans = 21; //For Kyle
    int bi = 22; //For Hotel
    int error = 23;
    int warn = 24;
    std::string exea[8] = { "RobloxPlayerBeta.exe","Spotify.exe","Discord.exe","chrome.exe","Minecraft.exe","portal.exe","GTA5.exe","Steam.exe"};//Support Active EXE 
    for (std::string i : exea) {
        if (IsProcessRunning(i))
        {
            std::cout << i << ": Online" << std::endl;
        }
        else
        {
            std::cout << i << ": Offline" << std::endl;//
        }
    }
}
