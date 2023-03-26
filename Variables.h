#pragma once
#include <string>
#include <vector>
#include <set>
#include <map>
#include <Windows.h>
#include "Lock.h"
#include <stdint.h>

struct BuffConfig {
	DWORD Time;
	int SBKey;
	int SBName;
};

struct HonorStruct {
	int Range;
	int Value;
};

struct SoundCheck
{
	RECT rectangle;
	std::string sound;
	std::string effect;
};

extern int VButton;
extern int MyHonor;
extern int CryptKey;
extern int PressableKey;
extern int numLock;
extern int UniqueKey;
extern int InvTime1;
extern int InvTime2;
extern int InvTime3;
extern int BTime;
extern LONG DelayCheck;
extern LONG MD5Time;
extern LONG CurHash;
extern LONG CurPos;
extern std::string mac;
extern bool StopClient;
extern HINSTANCE hL2;
extern int latestPacket;
extern int sentPacketNum;
extern int numPadClick;
extern LONG MD5TimeToSleep;
extern Lock PacketLock;
extern std::vector<std::string> MD5Files;
extern std::vector<BuffConfig> BuffIcons;
extern void insertBuff(int Key, int Name, int Time);
extern void removeBuff(int Key, int Name);
extern void buffTimer();
extern uint32_t sha256(std::string input);
extern void Console();
extern void LockHonor();
extern void UnlockHonor();
extern std::map<int, std::vector<SoundCheck>> SoundMaps;
extern std::map<int, std::string> SoundKSMs;
extern std::set<int> Costumes;
extern std::map<int, HonorStruct> PlayerHonors;