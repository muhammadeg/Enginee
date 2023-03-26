#include <string>
#include "Variables.h"
#include "Lock.h"
#include "Engine.h"
int PressableKey = 0;
int numLock = 0;
int UniqueKey = 0;
int CryptKey = 0;
int MyHonor = 0;
int VButton = 0;
int sentPacketNum = 0;
int InvTime1 = 0;
int InvTime2 = 0;
int InvTime3 = 0;
int BTime = 0;
LONG DelayCheck = 0;
LONG CurHash = 0;
LONG CurPos = 0;
LONG MD5Time = 0;
bool StopClient = false;
HINSTANCE hL2 = 0;
int latestPacket = 0;
int numPadClick = 0;
LONG MD5TimeToSleep = 0;
std::string mac = "";
Lock buffLock = Lock();
Lock HonorLock = Lock();
Lock PacketLock = Lock();
std::vector<BuffConfig> BuffIcons = std::vector<BuffConfig>();
std::vector<std::string> MD5Files = std::vector<std::string>();
std::map<int, std::vector<SoundCheck>> SoundMaps;
std::map<int, std::string> SoundKSMs;
std::set<int> Costumes;
std::map<int, HonorStruct> PlayerHonors;

void LockHonor() {
	HonorLock.Enter();
}

void UnlockHonor() {
	HonorLock.Leave();
}

void Console() {
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
}

uint32_t hash_string(const char * s)
{
	uint32_t hash = 0;

	for (; *s; ++s)
	{
		hash += *s;
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}

	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	return hash;
}

uint32_t sha256(std::string input) {
	return hash_string(input.c_str());
}

bool modifyBuff(int Key, int Name, int Time) {
	bool result = false;
	buffLock.Enter();
	int Size = BuffIcons.size();
	for (int i = 0; i < Size; i++) {
		BuffConfig x = BuffIcons[i];
		if (x.SBName == Name && x.SBKey == Key) {
			BuffIcons[i].Time = Time;
			result = true;
			break;
		}
	}
	buffLock.Leave();
	return result;
}

bool exists(int Key, int Name) {
	bool result = false;
	buffLock.Enter();
	int Size = BuffIcons.size();
	for (int i = 0; i < Size; i++) {
		BuffConfig x = BuffIcons[i];
		if (x.SBName == Name && x.SBKey == Key) {
			result = true;
			break;
		}
	}
	buffLock.Leave();
	return result;
}

void insertBuff(int Key, int Name, int Time) {
	DWORD t = Time + GetTickCount();
	if (modifyBuff(Key, Name, t))
		return;

	BuffConfig x = BuffConfig();
	x.SBKey = Key;
	x.SBName = Name;
	x.Time = t;

	buffLock.Enter();
	BuffIcons.push_back(x);
	buffLock.Leave();
}

void removeBuff(int Key, int Name) {
	buffLock.Enter();
	std::vector<BuffConfig> buffTemp = BuffIcons;
	buffLock.Leave();
	int Size = buffTemp.size();
	for (int i = 0; i < Size; i++) {
		BuffConfig buff = buffTemp[i];
		if (buff.SBKey == Key && buff.SBName == Name) {
			BuffIcons.erase(BuffIcons.begin() + i);
			break;
		}
	}
}

void buffTimer() {
	buffLock.Enter();
	std::vector<BuffConfig> buffTemp = BuffIcons;
	buffLock.Leave();
	int Size = buffTemp.size();
	for (int i = 0; i < Size; i++) {
		BuffConfig buff = buffTemp[i];
		DWORD Time = buff.Time;
		if (Time && (Time <= GetTickCount())) {
			if (buff.SBKey && buff.SBName) {
				buffLock.Enter();
				BuffIcons.erase(BuffIcons.begin() + i);
				buffLock.Leave();
				Engine::KGameSys::CallBuff(0, 0, 0, 0, 0, 0, 6000, buff.SBKey, buff.SBName);
				return buffTimer();
			}
		}
	}
}