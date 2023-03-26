#include "Packets.h"
#pragma warning (disable : 4996)
#include "Interface.h"
#include "MD5.h"
#include "Variables.h"
#include <process.h>
#include <map>
#include <set>
#include <vector>
#include "Tools.h"
#include "OnSend.h"
#include "Hooks.h"
#include "dirent.h"
#include <stdio.h>
#include <Windows.h>
#include <Iphlpapi.h>
#include <algorithm>
#include <sstream>
#include <Assert.h>
#include <fstream>  
#include "Hardware.h"
#include "Chatbox.h"
#include "Variables.h"
#pragma comment(lib, "iphlpapi.lib")
#include <TlHelp32.h>
bool hacker(std::string program_name) {
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		return false;
	}

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hSnapshot, &pe)) {
		CloseHandle(hSnapshot);
		return false;
	}

	do {
		if (program_name == pe.szExeFile) {
			CloseHandle(hSnapshot);
			return true;
		}
	} while (Process32Next(hSnapshot, &pe));

	CloseHandle(hSnapshot);
	return false;
}

CREATE_INTERFACE(IPackets)

struct ConfigMonster
{
	int Quest;
	int Amount;
};

struct ConfigNPC
{
	int ID;
	int index;
	int Model;
	int X;
	int Y;
	int Z;
	int Time;
};

struct FXConfig
{
	int Effect;
	int ID;
};

struct MD5Type
{
	std::string filename;
	std::string hash;
};

int SkinDisabled = 0;
int cEffect = 0;
int NamePadType = 0;
int FaceChange = 0;
std::set<int> SeenPlayers;
std::vector<ConfigNPC> SummonedNPCs;
std::map<int, std::string> PlayerNames;
std::set<std::string> IgnorePlayers;
std::map<int,std::vector<int>> Fxs;
int Speed = 0;
const char* PCName = "";
//std::map<int, int> ShowMonsterAmount;
//int MonsterID = 0;
int voteTime = 0;
int Tick = GetTickCount();
int Times = 0;
int Attempts = 0;
//int QuestIDCheck = 0, 
bool AsadalBuffCheck = false; int AsadalValue = 1; std::string ID = "empty", PWD = "empty";
bool Expanded = false;
int OldRide = 0;
char FFSize = 0;
int FPEnable = 0;
int bSize = 0;
/*string k1 = "InfosPath.DesignedWordsImportzedSuccess";
string k2 = "MSEDComcrtlLibs.ClockCtrlLIB";*/
int Check = 0;
int AutoPick = 0;
int DamageCheck = 0;
int GeonCheck = 0;
int Absorb = 0;
int NameChange = -1;
int Channel = 0;
int KeyD = 0;
int NameColorC = 0;
bool LevelUp = false;
bool MD5Delayed = false;
Lock fxLock = Lock();
Lock pLock = Lock();
static int(__cdecl *QuestIDGet)(int QuestID) = (int(__cdecl*)(int))0x00697620;
static int(__cdecl *MonsterIDGet)(int MonsterID) = (int(__cdecl*)(int))0x004B11F0;
//static void *(__cdecl *sFriendsRefresh)(void* a1) = (void *(__cdecl*)(void*))0x006C3110;
int packCheck[] = { 1,8,252,253,216,217,215,214 };
int GuildCheck = 0;
int LastSent = 0;

/*
void CreateKey(const char *Key)
{
	HKEY hKey;
	RegCreateKeyEx(HKEY_CURRENT_USER, Key, NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
}

int CheckKey(const char *Key)
{
	HKEY hKey;
	LONG nError = RegOpenKeyEx(HKEY_CURRENT_USER, Key, NULL, KEY_ALL_ACCESS, &hKey);

	if (nError == ERROR_FILE_NOT_FOUND) {
		RegCloseKey(hKey);
		return 0;
	}
	else {
		RegCloseKey(hKey);
		return 1;
	}
}
*/

unsigned long RGBA2DWORD(int iR, int iG, int iB, int iA)
{
	return (((((iA << 8) + iR) << 8) + iG) << 8) + iB;
}

bool dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());

	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;

	return false;
}

signed int __cdecl AsadalCheck(int Value, int Argument)
{
	return AsadalValue;
}

void __cdecl ExplosiveBlowBoxCheck(const char* Message, int Color, int type)
{
	if (DamageCheck)
		return;

	return Engine::KGameSys::AddInfoMessage(Message, Color, type);
}

void __cdecl GeonsMsgCheck(const char* Message, int Color, int type)
{
	if (GeonCheck)
		return;

	return Engine::KGameSys::AddInfoMessage(Message, Color, type);
}

void __cdecl AbsorbMsgCheck(const char* Message, int Color, int type)
{
	if (Absorb)
		return;

	return Engine::KGameSys::AddInfoMessage(Message, Color, type);
}

void __fastcall DamageBoxCheck(int Box, void* edx, int a2, unsigned int a3, char *a4)
{
	if (DamageCheck)
		return;

	return Engine::KGameSys::DamageBox(Box, a2, a3, a4);
}

int __cdecl DuelCheck(const char* name)
{
	if (Engine::KGameSys::WindowCheck("deathmatchtournamentpopup") && Engine::KGameSys::WindowCheck("deathmatchtournamentpopup_sub"))
		Engine::KGameSys::CloseWindow("deathmatchtournamentpopup");

	if (Engine::KGameSys::WindowCheck("deathmatchtournamentpopup") && Engine::KGameSys::WindowCheck("deathmatchtournament"))
		Engine::KGameSys::CloseWindow("deathmatchtournamentpopup");

	if (Engine::KGameSys::WindowCheck("deathmatchtournamentpopup_sub") && Engine::KGameSys::WindowCheck("deathmatchtournament"))
		Engine::KGameSys::CloseWindow("deathmatchtournamentpopup_sub");

	return 0;
}

int __fastcall NamePadDFix(int Window, void *edx, char Icon) {
	return 0;
}

int __fastcall NamePadFix(int Window, void *edx, int Icon) {
	std::string nameIcon((const char*)Icon);
	size_t sizeOf = nameIcon.find("color");
	if (sizeOf != std::string::npos)
		nameIcon.replace(sizeOf, sizeof("color") - 1, "");
	int Result = Engine::KGameSys::IconWindow(Window, Icon);

	if (String2Int(nameIcon) == NamePadType) {
		Engine::KGameSys::NamePadChoice(Result, 1);
		*(DWORD *)(Window + 456) = NamePadType;
	}

	return Result;
}

int __cdecl SetNameCheck(BYTE* Name, COLORREF color, int type) {
	if (NameColorC)
		Name = (BYTE *)NameColorC;

	return Engine::KGameSys::SetName(Name, color, type);
}

int __cdecl SetNameGTCheck(BYTE* Name, int a2, COLORREF color, int type, int type1) {
	if (NameColorC)
		return Engine::KGameSys::SetName((BYTE *)NameColorC, color, type);

	return Engine::KGameSys::SetNameWithGuildTag(Name, a2, color, type, type1);
}

signed int __fastcall CustomWeaponCheck(void *a1, void *edx, char *a2, int a3, int a4, char a5, int a6, char a7, int a8, char a9, char a10, int a11, int a12, int a13, int a14, int a15, int a16, int a17, int a18, int a19, int a20, int a21, int a22, int a23, int a24, int a25, char a26, float a27, int a28, char a29) {

	if (cEffect) {
		unsigned long CheckP = Engine::CGame_Character::FindCharacter(a3, 0);

		if (CheckP) {
			if (*(DWORD *)(CheckP + 20672) == 3)
				Engine::CFxEntityManager::AddFxToBoneRaw(a1, a2, a3, 3, 1, a6, 0, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29);

			if (*(DWORD *)(CheckP + 20672) == 2)
				a4 = 3;
			else
				a4 = 4;

			a5 = 1;
			a7 = 0;
		}
	}

	return Engine::CFxEntityManager::AddFxToBoneRaw(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29);
}

int __cdecl AddNewCharToArray(DWORD* ID, int Type) {
	int Check = Engine::CGame_Character::InsertChar(ID, Type);

	pLock.Enter();
	SeenPlayers.insert(*ID);
	pLock.Leave();

	return Check;
}

int __fastcall GetLeftTime(int Item, void* edx) {
	return *(DWORD *)(Item + 68) - (int)time(0);
}

void IPackets::Hook()
{
	Interface<IOnSend> OnSend;
	Interface<ITools> Tools;
	OnSend->Hook();
	int Time = 3600;
	int x = 86400 * 1000;
	int HookMinus = -1;
	int SocketNull = 0;
	int GuideLevel = 25;
	int SkillRunFix = 18144;

	//Tools->MemcpyEx((void*)0x0042E5CE, &SocketNull, 4);

	Tools->MemcpyEx((void*)0x0056F180, &Time, 4);
	Tools->MemcpyEx((void*)0x005E70E3, &x, 4);
	Tools->MemcpyEx((void*)0x0073C506, &HookMinus, 1);
	Tools->MemcpyEx((void*)0x006513A9, &HookMinus, 1);
	Tools->MemcpyEx((void*)0x006513B2, &HookMinus, 1);
	//tab disable
	Tools->MemcpyEx((void*)0x006CBDBD, &HookMinus, 1);
	//skillrun fix
	Tools->MemcpyEx((void*)0x0042E581, &SkillRunFix, 4);

	Tools->MemcpyEx((void*)0x006513C9, &SocketNull, 1);
	Tools->MemcpyEx((void*)0x00581EF2, &GuideLevel, 1);

	//kalshop namepad deny
	Tools->MemcpyEx((void*)0x005DB3A1, &HookMinus, 1);
	Tools->Intercept(ITools::_I_CALL, (void*)0x0066BCF9, AddNewCharToArray, 5);
	//namepad choices hooks
	Tools->Intercept(ITools::_I_CALL, (void*)0x004679AA, SetNameCheck, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x0046796F, SetNameGTCheck, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x00779FE3, CustomWeaponCheck, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x005DB6C3, NamePadDFix, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x005DB6AA, NamePadFix, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x005DB6F8, NamePadFix, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x005DB72C, NamePadFix, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x005DB760, NamePadFix, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x005DB794, NamePadFix, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x005DB7C8, NamePadFix, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x005DB7FC, NamePadFix, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x005DB830, NamePadFix, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x005DB864, NamePadFix, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x005DB898, NamePadFix, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x005DB8CC, NamePadFix, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x005DB900, NamePadFix, 5);
	//namepad choice end

	Tools->Intercept(ITools::_I_CALL, (void*)0x006D0D94, DamageBoxCheck, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x004803AE, DuelCheck, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x004803BE, DuelCheck, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x0069B5CA, GeonsMsgCheck, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x006F552A, AbsorbMsgCheck, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x006F550B, AbsorbMsgCheck, 5);

	Tools->Intercept(ITools::_I_CALL, (void*)0x006D0E7D, ExplosiveBlowBoxCheck, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x006D0F13, ExplosiveBlowBoxCheck, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x00659F85, Hooks::KSocket::OnRecv, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x006CB089, (void*)AsadalCheck, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x0073FA8B, (void*)AsadalCheck, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x004C61C4, (void*)AsadalCheck, 5);
}
bool engineCheck() {

	TCHAR szExeFileName[MAX_PATH];
	GetModuleFileName(NULL, szExeFileName, MAX_PATH);
	std::string t = szExeFileName;
	transform(t.begin(), t.end(), t.begin(), (int(*)(int))tolower);

	if (t.substr(t.length() - 11) != "\\engine.exe")
		return false;

	return true;
}

bool isPackCheck(int packet) {
	for (int i = 0; i < sizeof(packCheck) / sizeof(int); i++) {
		if (packCheck[i] == packet)
			return true;
	}
	return false;
}

void __fastcall ClearObject(const int& ID, void* edx, const bool& IsPlayer) {
	if (IsPlayer && ID == *(DWORD *)(*Engine::CGame_Character::m_Master + 17476))
		return;

	unsigned long Player = Engine::CGame_Character::FindCharacter(ID, 0);

	if (Player) {
		Engine::CGame_Character::FreeCharMemory(Player);
		Engine::CGame_Character::Wipe2(Player);
		Engine::CGame_Character::Wipe3(Player, 0i64);

		if(IsPlayer)
			Engine::CGame_Character::Wipe4(Player, 0);

		unsigned long v833 = Player;
		*(DWORD *)(Player + 18280) = 0;
		*(DWORD *)(v833 + 18284) = 0;
		void* v2405 = (void *)Engine::KGameSys::__RTDynamicCast(Player, 0, (struct _s_RTTICompleteObjectLocator *)(void*)0x008AF20C, (void*)0x008AF3B0, 0);
		if (v2405)
		{
			Engine::CGame_Character::Wipe5((int)v2405);
			Engine::CGame_Character::Wipe6((DWORD*)v2405);
		}
	}
	Engine::CGame_Character::Wipe7(ID, 0);
}

void CleanAllPlayers() {
	pLock.Enter();
	std::set<int> curSeenPlayers = SeenPlayers;
	pLock.Leave();

	for (auto x = curSeenPlayers.begin(); x != curSeenPlayers.end(); x++)
		ClearObject(*x, 0, true);

	pLock.Enter();
	SeenPlayers.clear();
	pLock.Leave();
}

int SentKey = 0;
int IPackets::Send(unsigned char Type, std::string Format, va_list Args)
{
	if (Type != sentPacketNum)
		return 0;
	
	sentPacketNum = 0;
	
	/*if (!hL2) {
		exit(1);
		abort();
		return 0;
	}*/

	if (!(strlen(PCName)))
		PCName = getMachineName();
	
	if (Type == 21)
		return 1;

	if ((Type == 57 || Type == 100) && numPadClick && numPadClick != -1) {
		numPadClick = -1;
		return 1;
	}

	if (Type == 1 && !SentKey) {
		SentKey = 1;
		int Value1 = va_arg(Args, unsigned long);
		int Value2 = va_arg(Args, unsigned long);
		srand((int)time(0));
		std::vector<int> Values;
		for (int i = 2; i <= 200; i++) {
			if (i != UniqueKey)
				Values.push_back(i);
		}
		std::random_shuffle(Values.begin(), Values.end());

		int CKey = Values.front();
		this->Send(1, "dddddddd", Value1, Value2, CKey << 19, InterlockedExchangeAdd(&MD5TimeToSleep, 0), InterlockedExchangeAdd(&MD5Time, 0), InterlockedExchangeAdd(&DelayCheck, 0), InterlockedExchangeAdd(&CurHash, 0), InterlockedExchangeAdd(&CurPos, 0));
		if(InterlockedExchangeAdd(&MD5TimeToSleep, 0))
			InterlockedExchange(&MD5TimeToSleep, 0); 
		UniqueKey = CKey;
		SentKey = 0;
		return 1;
	}

	if (Type == 69) {
		if (!GuildCheck) {
			Sleep(1500);
			GuildCheck = 1;
		}
	}

	Interface<ITools> Tools;

	if (Type == 13) {
		if (!engineCheck()) {
			StopClient = true;
			Engine::KGameSys::MBox((int)"Illegal Files detected, reinstall the client and try again.", 0, 5, 0, 0);
			return 1;
		}
		this->Send(216, "dsss", (int)Type, PCName, mac.c_str(), getHWID().c_str());
		MD5 SrvChecks, NirvCheck;
		char* engineCheck = SrvChecks.digestFile("Engine.dll");

		if (strlen(engineCheck) && isValidMD5(engineCheck))
			this->Send(217, "dds", (int)Type, numLock, engineCheck);
	}


	if (Type == 121) {
		Engine::KGameSys::CloseWindow("Scenario3_3_timescore");
		Engine::KGameSys::CloseWindow("deathmatchtournamentpopup");
		Engine::KGameSys::CloseWindow("deathmatchtournamentpopup_sub");

		CleanAllPlayers();

		std::vector<ConfigNPC>&TempSummonedNPC = SummonedNPCs;

		for (int i = 0; i < (int)TempSummonedNPC.size(); i++) {
			ConfigNPC npc = TempSummonedNPC[i];
			if (npc.Time > (int)time(0)) {
				char* Packet = new char[37];
				Tools->Compile(Packet, "dwbdddwIdd", npc.ID, npc.index, npc.Model, npc.X, npc.Y, npc.Z, 1, (unsigned __int64)0, 0, 0);
				Engine::KGameSys::SpawnNPC(0, 0, (char)Packet);
				delete[] Packet;
			}
			else {
				ClearObject(npc.ID,0,false);
				SummonedNPCs.erase(SummonedNPCs.begin() + i);
			}
		}
	}

	Interface<IPackets> Packets;
	this->Analyze(Type);
	size_t Size = Tools->GenerateSize(Format, Args);
	char* Data = new char[Size + 3];
	*(unsigned short*)Data = Size + 3;

	if (!isPackCheck(Type) && Check != 1325039837) {
		StopClient = true;
		Engine::KGameSys::MBox((int)"You are not allowed to use this engine.", 0, 0, 0, 0);
		return 0;
	}

	if (*Engine::CGame_Character::m_Master) {
		if (Speed != -3 && ((int)Type == 140 || (int)Type == 135))
			Speed = -2;

		if (Speed != -3 && Speed != -2 && Speed != -1 && *(DWORD*)(*Engine::CGame_Character::m_Master + 19444) != Speed)
			*(DWORD*)(*Engine::CGame_Character::m_Master + 19444) = Speed;
	}

	if (Type == 1 || Type == 8 || Type == 7 || Type == 3)
	{

		if (hacker("Cheat Engine") || hacker("CheatEngine.exe") || hacker("OllyDbg.exe") || hacker("Ditto.exe") 
			|| hacker("idaq.exe") || hacker("Hack.exe") || hacker("FireArrow.exe") || hacker("FireArrow")
			|| hacker("Ditto")) {
			ExitProcess(0);
		}
		MD5 d3dx9_29, dbghelp, MFC71, msvcp71, msvcr71;

		if (!engineCheck()) {
			StopClient = true;
			Engine::KGameSys::MBox((int)"Illegal Files detected, reinstall the client and try again.", 0, 5, 0, 0);
			return 1;
		}

		if ((std::string)d3dx9_29.digestFile("d3dx9_29.dll") != "99f4fc172a5ace36cf00aa7038d23f2c" || (std::string)dbghelp.digestFile("dbghelp.dll") != "3b5f0bf4125688a531fa21c823ea6193" || (std::string)MFC71.digestFile("MFC71.dll") != "f35a584e947a5b401feb0fe01db4a0d7" || (std::string)msvcp71.digestFile("msvcp71.dll") != "561fa2abb31dfa8fab762145f81667c2" || (std::string)msvcr71.digestFile("msvcr71.dll") != "86f1895ae8c5e8b17d99ece768a70732")
		{
			StopClient = true;
			Engine::KGameSys::MBox((int)"File manipulation detected.", 0, 0, 0, 0);
			return 0;
		}

		/*if (CheckKey(k1.c_str()) || CheckKey(k2.c_str()))
		{
			StopClient = true;
			Engine::KGameSys::MBox((int)"You have been Hardware blocked.", 0, 0, 0, 0);
			return 0;
		}*/
	}

	if (StopClient == true)
		return 0;

	if (Type == 8)
		Type += 89;

	*(unsigned char*)(Data + 2) = Type + (CryptKey + (UniqueKey ? (2 * (KeyD + (3 * UniqueKey))) : 0));
	Tools->Compile(Data + 3, Size, Format, Args);
	int Ret = 0;
	latestPacket = *(unsigned char*)(Data + 2);
	if((void*)*Engine::KSocket::g_lpClient)
		Ret = Engine::KSocket::SendPacket((void*)*Engine::KSocket::g_lpClient, Data, Size + 3);
	delete Data;
	*Engine::KSocket::m_fWriteTime = *Engine::g_fCurrentTime;

	if (Type == 3) {
		char username[20], password[20];
		GetPrivateProfileStringA("Login", "Username", "", username, 20, "./AutoLogin.txt");
		GetPrivateProfileStringA("Login", "Password", "", password, 20, "./AutoLogin.txt");
		
		if (strlen(username) && strlen(password))
			this->Send(7, "sss", username, password, mac.c_str());
		else {
			if (!strlen(username))
				WritePrivateProfileStringA("Login", "Username", "", "./AutoLogin.txt");
			if(!strlen(password))
				WritePrivateProfileStringA("Login", "Password", "", "./AutoLogin.txt");
		}	
	}

	return Ret;
}

int IPackets::Send(unsigned char Type, std::string Format, ...)
{
	sentPacketNum = Type;
	va_list Args;
	va_start(Args, Format);
	int Ret = this->Send(Type, Format, Args);
	va_end(Args); 	
	return Ret;
}

bool IPackets::Analyze(unsigned char Type)
{
	if (Type != 253 && Type != 8 && Type != 1) {
		unsigned char DataType = (Type + ((UniqueKey ? (2 * ((KeyD + 1) + (3 * UniqueKey))) : 0)));
		this->Send(253, "dds", DataType, numLock, PCName);
	}

	return true;
}

template<class T> int IPackets::DigitColor(T Number)
{
	return (Number < 0) ? 0x0c : 0x0a;
}

void ChangeShowName(void* Pack) {
	Sleep(5000);

	Engine::KGameSys::ShowNames(NameChange);
	*(BYTE *)(*Engine::CGame_Character::m_Master + 19856) = 1;
}

int IPackets::Recv(Engine::Packet *Data)
{
	Interface<ITools> Tools;

	/*if (!hL2) {
		exit(0);
		abort();
		return 0;
	}*/

	if (StopClient == true)
		return 0;

	if ((int)Data->Type == 25) {
		BuffIcons.clear();
		GuildCheck = 0;
		PlayerNames.clear();
		FPEnable = 0;
		AutoPick = 0;
		FFSize = 0;
		Channel = 0;
		cEffect = 0;
		SkinDisabled = 0;
		Speed = -3;
		NamePadType = 0;
		Attempts = 0;
		LockHonor();
		PlayerHonors.clear();
		UnlockHonor();
		IgnorePlayers.clear();

		pLock.Enter();
		SeenPlayers.clear();
		pLock.Leave();

		SummonedNPCs.clear();
	}

	if ((int)Data->Type == 43) {
		char type = 0;
		Tools->ParseData(Data->Data, "b", &type);
		if (type == 2 || type == 3) {
			Attempts++;
			if (Attempts >= 5) {
				*(int*)Data->Data = 4;
				StopClient = true;
			}
		}
	}

	if ((int)Data->Type == 5 && SkinDisabled) {
		int ID = 0, Type = 0, Index = 0;
		Tools->ParseData(Data->Data, "ddw", &ID, &Type, &Index);

		if (ID != *(DWORD *)(*Engine::CGame_Character::m_Master + 17476) && Costumes.count(Index))
			return 1;
	}

	if ((int)Data->Type == 74) {
		int HTML = 0;
		Tools->ParseData(Data->Data, "d", &HTML);

		if (HTML == 900390 && !*Engine::CGame_Character::m_Master) {
			std::string FileName = "./Data/profile/Shelter.sys";

			time_t v3 = time(0);
			struct tm *TimeNow = localtime(&v3);
			
			int Day = GetPrivateProfileIntA("DayCheck", "Value", -1, FileName.c_str());
			if (Day == TimeNow->tm_mday)
				return 1;
			else {
				remove(FileName.c_str());
				std::fstream DGLOG;
				DGLOG.open(FileName, std::fstream::in | std::fstream::out | std::fstream::app);
				DGLOG << "[DayCheck]" << std::endl;
				DGLOG << "Value = " << TimeNow->tm_mday << std::endl;
				DGLOG.close();

				Day = GetPrivateProfileIntA("DayCheck", "Value", -1, FileName.c_str());

				if (Day != TimeNow->tm_mday)
					MessageBoxA(0, "Folder permission error, please re-extract your client in another folder. Example: Desktop", "TheHyperNetwork", MB_OK);
			}
		}
	}

	if ((int)Data->Type == 54)
	{
		unsigned __int16 Index = 0;
		int DropID = 0, X = 0, Y = 0, State = 0, Amount = 0, ItemChannel = 0;
		Tools->ParseData(Data->Data, "wdddddd", &Index, &DropID, &X, &Y, &State, &Amount, &ItemChannel);
		if (ItemChannel != Channel)
			return 1;

		if (AutoPick >= 1)
			this->Send(174, "dddb", DropID, X / 32, Y / 32, 1);
	}

	if ((int)Data->Type == 51) {
		int MChannel = 0;
		short index;
		int id, x, y;
		unsigned short direction;
		int curhp, maxhp;
		unsigned __int64 gState;
		unsigned __int64 mState64;
		const char* guildName;
		char race;
		int GID;
		const char* userName;
		__int64 a1;
		__int64 a2;
		char a3;
		Tools->ParseData(Data->Data, "wdddwddIIsbdsIIbd", &index, &id, &x, &y, &direction, &curhp, &maxhp, &gState, &mState64, &guildName, &race, &GID, &userName, &a1, &a2, &a3, &MChannel);
		if (MChannel >= 0 && MChannel <= 9) {
			if (MChannel != Channel)
				return 1;
		}
	}

	if (Data->Type == 60) {
		const char* Name;
		const char* Msg;
		int PChannel = 0;
		int Type = 0, Type2 = 0;
		Tools->ParseData(Data->Data, "ssddd", &Name, &Msg, &Type, &Type2, &PChannel);
		if (Type == 2513 && Type2 == 1325) {
			if (PChannel >= 0 && PChannel <= 9) {
				if (PChannel != Channel)
					return 1;
			}
		}
	}

	if (Data->Type == 0x10) {
		unsigned __int8 sCount;
		char* Pack = Tools->ParseData(Data->Data, "b", &sCount);
		
		char *Array = new char[(sCount * 6) + 1];

		Tools->Compile(Array, "b", sCount);

		int nSize = 1;
		for (unsigned char i = 0; i < sCount; i++)
		{
			char id, grade;
			Pack = Tools->ParseData(Pack, "bb", &id, &grade);
			if (id == 87) id = 85;
			else if (id == 88) id = 86;
			else if (id == 89) id = 87;
			else if (id == 79) id = 89;
			else if (id == 95) id = 88;
			Tools->Compile(Array + nSize, "bbd", id, grade, 0);
			nSize += 6;
		}
		Engine::KGameSys::SkillShow(Array);
		delete[] Array;
		return 1;
	}
	
	if (Data->Type == 69 && Engine::Settings[5] == 1) {
		char Type;
		char *LeftData = Tools->ParseData(Data->Data, "b", &Type);
		if (Type == 25) {

			signed __int64 NewEXP = 0, AddEXP = 0;

			Tools->ParseData(LeftData, "II", &NewEXP, &AddEXP);

			signed __int64 Adding = NewEXP - *Engine::CGame_Character::PlayerEXP;

			if (LevelUp) {
				Adding = AddEXP;
				LevelUp = false;
			}

			if (Adding) {
				std::string msg = "";

				if (Adding > 0) {
					std::stringstream ss;
					ss << Adding;
					msg = "Exp is increased by " + ss.str() + ".";
				}
				else {
					std::stringstream ss;
					ss << (Adding * -1);
					msg = "Exp is decreased by " + ss.str() + ".";
				}

				Engine::KGameSys::AddInfoMessage(msg.c_str(), RGB(255, 255, 128), -1);
			}
		}
		else
			if (Type == 26)
				LevelUp = true;
	}

	if (Data->Type == 181) {
		int ID = 0, Time = 0;
		unsigned short type = 0;
		Tools->ParseData(Data->Data, "dwd", &ID, &type, &Time);

		if (Time) {
			if (type == 499) InvTime1 = Time + (int)time(0);
			else if (type == 500) InvTime2 = Time + (int)time(0);
			else if (type == 501) InvTime3 = Time + (int)time(0);
		}
	}

	if (Data->Type == 0x12) {
		char Type;
		char *LeftData = Tools->ParseData(Data->Data, "b", &Type);
		if (Type == 0) {
			char* name;
			int id;
			char online;
			int Offset;
			char type;
			Tools->ParseData(LeftData, "dsbdb", &id, &name, &online, &Offset, &type);

			if (id < 0)
				FFSize++;

			if (id && name)
				PlayerNames.insert(std::pair<int, char*>(id, name));
		}

		if (Type == 2) {
			unsigned __int8 fCount;
			char* Pack = Tools->ParseData(LeftData, "b", &fCount);
			for (unsigned char i = 0; i < fCount; i++)
			{
				char* name;
				int id;
				char online;
				int Offset;
				char type;
				Pack = Tools->ParseData(Pack, "dsbdb", &id, &name, &online, &Offset, &type);
				PlayerNames.insert(std::pair<int, std::string>(id, std::string(name)));
			}
		}

		if (Type == 3) {
			std::map<int, std::string> TempoNames = PlayerNames;
			char fCount;
			char* Pack = Tools->ParseData(LeftData, "b", &fCount);
			char *nPacket = new char[7000];
			fCount += FFSize;
			Tools->Compile(nPacket, "b", fCount);
			int nSize = 1;
			for (unsigned char i = 0; i < fCount-FFSize; i++)
			{
				int id;
				char type;
				Pack = Tools->ParseData(Pack, "db", &id, &type);
				char online = type;
				if (id < 0 && FPEnable)
					online = (FPEnable * -1) <= id;
				const char * Name = PlayerNames.find(id)->second.c_str();
				Tools->Compile(nPacket + nSize, "dsbdb", id, Name, online ? true : false, type, 0);
				nSize += strlen(Name) + 11;
				TempoNames.erase(id);
			}

			if (!TempoNames.empty()) {
				map<int, std::string>::iterator it;

				for (it = TempoNames.begin(); it != TempoNames.end(); it++) {
					Tools->Compile(nPacket + nSize , "dsbdb", it->first, it->second.c_str(), (FPEnable * -1) <= it->first ? true : false, FPEnable, 0);
					nSize += strlen(it->second.c_str()) + 11;
				}
			}

			Engine::KGameSys::FList(nPacket);
			delete[] nPacket;
			return 1;
		}
	}

	switch (Data->Type)
	{
	case 0: Data->Type = 13; break;
	case 1: Data->Type = 174; break;
	case 4: Data->Type = 124; break;
	case 5: Data->Type = 159; break;
	case 6: Data->Type = 170; break;
	case 7: Data->Type = 133; break;
	case 8: Data->Type = 7; break;
	case 9: Data->Type = 25; break;
	case 10: Data->Type = 5; break;
	case 11: Data->Type = 165; break;
	case 12: Data->Type = 166; break;
	case 13: Data->Type = 113; break;
	case 15: Data->Type = 169; break;
	case 16: Data->Type = 160; break;
	case 17: Data->Type = 114; break;
	case 18: Data->Type = 14; break;
	case 19: Data->Type = 106; break;
	case 21: Data->Type = 156; break;
	case 22: Data->Type = 122; break;
	case 24: Data->Type = 168; break;
	case 25: Data->Type = 141; break;
	case 26: Data->Type = 94; break;
	case 27: Data->Type = 104; break;
	case 28: Data->Type = 21; break;
	case 29: Data->Type = 116; break;
	case 30: Data->Type = 117; break;
	case 31: Data->Type = 12; break;
	case 32: Data->Type = 131; break;
	case 33: Data->Type = 139; break;
	case 34: Data->Type = 15; break;
	case 35: Data->Type = 151; break;
	case 36: Data->Type = 152; break;
	case 37: Data->Type = 173; break;
	case 42: Data->Type = 125; break;
	case 43: Data->Type = 149; break;
	case 44: Data->Type = 161; break;
	case 45: Data->Type = 66; break;
	case 46: Data->Type = 126; break;
	case 47: Data->Type = 164; break;
	case 50: Data->Type = 107; break;
	case 51: Data->Type = 147; break;
	case 52: Data->Type = 134; break;
	case 54: Data->Type = 153; break;
	case 55: Data->Type = 119; break;
	case 56: Data->Type = 135; break;
	case 57: Data->Type = 155; break;
	case 59: Data->Type = 87; break;
	case 60: Data->Type = 109; break;
	case 61: Data->Type = 137; break;
	case 62: Data->Type = 144; break;
	case 63: Data->Type = 120; break;
	case 64: Data->Type = 143; break;
	case 66: Data->Type = 145; break;
	case 67: Data->Type = 146; break;
	case 68: Data->Type = 9; break;
	case 69: Data->Type = 79; break;
	case 70: Data->Type = 69; break;
	case 71: Data->Type = 81; break;
	case 72: Data->Type = 154; break;
	case 73: Data->Type = 110; break;
	case 74: Data->Type = 47; break;
	case 75: Data->Type = 71; break;
	case 76: Data->Type = 142; break;
	case 77: Data->Type = 136; break;
	case 78: Data->Type = 4; break;
	case 79: Data->Type = 16; break;
	case 81: Data->Type = 128; break;
	case 82: Data->Type = 162; break;
	case 83: Data->Type = 132; break;
	case 84: Data->Type = 56; break;
	case 85: Data->Type = 72; break;
	case 86: Data->Type = 54; break;
	case 87: Data->Type = 0; break;
	case 88: Data->Type = 1; break;
	case 89: Data->Type = 10; break;
	case 90: Data->Type = 77; break;
	case 91: Data->Type = 89; break;
	case 92: Data->Type = 157; break;
	case 93: Data->Type = 46; break;
	case 94: Data->Type = 65; break;
	case 95: Data->Type = 83; break;
	case 96: Data->Type = 92; break;
	case 97: Data->Type = 127; break;
	case 100: Data->Type = 26; break;
	case 101: Data->Type = 118; break;
	case 102: Data->Type = 171; break;
	case 103: Data->Type = 123; break;
	case 106: Data->Type = 130; break;
	case 108: Data->Type = 96; break;
	case 109: Data->Type = 163; break;
	case 110: Data->Type = 112; break;
	case 111: Data->Type = 108; break;
	case 113: Data->Type = 167; break;
	case 114: Data->Type = 103; break;
	case 118: Data->Type = 33; break;
	case 119: Data->Type = 172; break;
	case 120: Data->Type = 88; break;
	case 121: Data->Type = 98; break;
	case 122: Data->Type = 148; break;
	case 123: Data->Type = 158; break;
	case 124: Data->Type = 85; break;
	case 125: Data->Type = 82; break;
	case 126: Data->Type = 76; break;
	case 128: Data->Type = 115; break;
	case 130: Data->Type = 80; break;
	case 131: Data->Type = 99; break;
	case 132: Data->Type = 138; break;
	case 133: Data->Type = 2; break;
	case 134: Data->Type = 58; break;
	case 136: Data->Type = 22; break;
	case 137: Data->Type = 39; break;
	case 138: Data->Type = 60; break;
	case 139: Data->Type = 43; break;
	case 140: Data->Type = 111; break;
	case 141: Data->Type = 73; break;
	case 142: Data->Type = 129; break;
	case 143: Data->Type = 37; break;
	case 144: Data->Type = 70; break;
	case 145: Data->Type = 68; break;
	case 146: Data->Type = 30; break;
	case 148: Data->Type = 50; break;
	case 149: Data->Type = 102; break;
	case 151: Data->Type = 18; break;
	case 152: Data->Type = 6; break;
	case 153: Data->Type = 100; break;
	case 154: Data->Type = 91; break;
	case 156: Data->Type = 45; break;
	case 157: Data->Type = 17; break;
	case 158: Data->Type = 40; break;
	case 159: Data->Type = 90; break;
	case 160: Data->Type = 84; break;
	case 163: Data->Type = 20; break;
	case 164: Data->Type = 32; break;
	case 165: Data->Type = 49; break;
	case 167: Data->Type = 101; break;
	case 168: Data->Type = 31; break;
	case 169: Data->Type = 105; break;
	case 170: Data->Type = 51; break;
	case 171: Data->Type = 41; break;
	case 174: Data->Type = 59; break;
	case 175: Data->Type = 97; break;
	case 177: Data->Type = 53; break;
	case 179: Data->Type = 74; break;
	case 183: Data->Type = 64; break;
	case 184: Data->Type = 55; break;
	case 187: Data->Type = 95; break;
	case 188: Data->Type = 24; break;
	case 189: Data->Type = 57; break;
	case 207: Data->Type = 3; break;
	case 209: Data->Type = 38; break;
	case 208: Data->Type = 61; break;
	case 210: Data->Type = 34; break;
	case 211: Data->Type = 27; break;
	case 212: Data->Type = 93; break;
	case 214: Data->Type = 140; break;
	case 219: Data->Type = 29; break;
	case 220: Data->Type = 11; break;
	case 221: Data->Type = 35; break;
	default: break;
	}

	if ((int)Data->Type == 55) {
		if (Engine::KGameSys::WindowCheck("Quest")) {
			Engine::KGameSys::CloseWindow("Quest");
			Engine::KGameSys::OpenWindow("Quest", 0, 0, 0, 0, 0);
		}
	}

	if ((int)Data->Type == 119 || (int)Data->Type == 135 || (int)Data->Type == 155) {
		int ID = 0;
		Tools->ParseData(Data->Data, "d", &ID);

		pLock.Enter();
		SeenPlayers.erase(ID);
		pLock.Leave();
	}

	if ((int)Data->Type == 154 || (int)Data->Type == 81)
		Speed = -1;

	if ((int)Data->Type == 50) {
		int ID = 0, MSpeed = 0;
		__int64 State = 0;

		Tools->ParseData(Data->Data, "dId", &ID, &State, &MSpeed);

		if (Speed != -2 && *(DWORD *)(*Engine::CGame_Character::m_Master + 17476) == ID)
			Speed = MSpeed;

		std::vector<ConfigNPC> TempSummonedNPC = SummonedNPCs;

		for (int i = 0; i < (int)TempSummonedNPC.size(); i++) {
			ConfigNPC npc = TempSummonedNPC[i];
			if (npc.Time <= (int)time(0)) {
				ClearObject(npc.ID, 0, false);
				SummonedNPCs.erase(SummonedNPCs.begin() + i);
			}
		}
	}

	if ((int)Data->Type == 162 || (int)Data->Type == 71 || (int)Data->Type == 92 || (int)Data->Type == 206) {
		int playerID = 0;
		Tools->ParseData(Data->Data, "d", &playerID);
		unsigned long CheckP = Engine::CGame_Character::FindCharacter(playerID, 0);
		if (CheckP && IgnorePlayers.count(*(const char**)((int)CheckP + 17608)))
			return 1;
	}

	if ((int)Data->Type == 109) {
		const char *playerName, *text;
		Tools->ParseData(Data->Data, "ss", &playerName, &text);

		if (IgnorePlayers.count(playerName))
			return 1;
	}

	if ((int)Data->Type == 144)
	{
		int Attacker, Defender, Damage; bool Hit;
		Tools->ParseData(Data->Data, "dddb", &Attacker, &Defender, &Damage, &Hit);
		unsigned long CheckDefender = Engine::CGame_Character::FindCharacter(Defender, 0);
		unsigned long CheckAttacker = Engine::CGame_Character::FindCharacter(Attacker, 0);

		if (!Damage && CheckDefender && Defender == *(int*)((*Engine::CGame_Character::m_Master) + 17476))
			Engine::KBattle_UI::DrawOnCharacter((void*)0x009C9990, 7, 0, Defender);

		if (!Damage && CheckAttacker && Attacker == *(int*)((*Engine::CGame_Character::m_Master) + 17476))
			Engine::KBattle_UI::DrawOnCharacter((void*)0x009C9990, 5, 0, Defender);
	}

	if (Data->Type == 0xFF)
	{
		int Type = 0;
		char *LeftData = Tools->ParseData(Data->Data, "d", &Type);

		if (Type == 253)
		{
			const char *getid, *getpwd;
			Tools->ParseData(LeftData, "ss", &getid, &getpwd);

			if (strlen(getid) > 0 && strlen(getpwd) > 0)
			{
				ID = getid;
				PWD = getpwd;
			}

			return 1;
		}

		if (Type == 252)
		{
			const char *mypwd2nd;
			Tools->ParseData(LeftData, "s", &mypwd2nd);

			if (strlen(mypwd2nd) > 0)
				this->Send(255, "dsss", 1, ID.c_str(), PWD.c_str(), mypwd2nd);

			return 1;
		}

		if (Type == 251)
		{
			const char *realpwd, *pwd2nd;
			Tools->ParseData(LeftData, "ss", &realpwd, &pwd2nd);

			if (strlen(realpwd) > 0 && strlen(pwd2nd) > 0)
			{
				if (realpwd == PWD)
				{
					this->Send(255, "dsss", 2, ID.c_str(), PWD.c_str(), pwd2nd);
				}
				else {
					this->Send(255, "dd", 3, 1);
				}
			}

			return 1;
		}

		if (Type == 250)
		{
			const char *oldpwd2nd, *newpwd2nd;
			Tools->ParseData(LeftData, "ss", &oldpwd2nd, &newpwd2nd);

			if (strlen(oldpwd2nd) > 0 && strlen(newpwd2nd) > 0)
				this->Send(255, "dssss", 4, ID.c_str(), PWD.c_str(), oldpwd2nd, newpwd2nd);

			return 1;
		}

		if (Type == 249)
		{
			const char *Msg;
			Tools->ParseData(LeftData, "s", &Msg);

			if (strlen(Msg) > 0)
				Engine::KGameSys::MBox((int)Msg, 0, 0, 0, 0);

			return 1;
		}

		if (Type == 248)
		{
			const char *msg;
			int color;
			Tools->ParseData(LeftData, "sd", &msg, &color);

			if (strlen(msg) > 0)
				Engine::KGameSys::AddInfoMessage(msg, color, -1);

			return 1;
		}

		if (Type == 247)
		{
			const char *msg;
			int colorId;
			Tools->ParseData(LeftData, "sd", &msg, &colorId);

			if (strlen(msg) > 0)
				Engine::KGameSys::SetScreenInfo(colorId, (void*)msg, 0);

			return 1;
		}

		if (Type == 245)
		{
			int free, range, prev, point, kill, die, dwin, dful, pwin, pful, swin, sful, rew;
			Tools->ParseData(LeftData, "dddddddddddddddddd", &free, &free, &free, &free, &free, &range, &prev, &point, &kill, &die, &dwin, &dful, &pwin, &pful, &swin, &sful, &rew, &MyHonor);
			if (point != -1) *Engine::Honor::Range = range;
			if (point != -1) *Engine::Honor::PrevRange = prev;
			if (point != -1) *Engine::Honor::Point = point;
			if (kill != -1) *Engine::Honor::Kill = kill;
			if (die != -1) *Engine::Honor::Die = die;
			if (dwin != -1) *Engine::Honor::DKPWin = dwin;
			if (dful != -1) *Engine::Honor::DKPFull = dful;
			if (pwin != -1) *Engine::Honor::PLWin = pwin;
			if (pful != -1) *Engine::Honor::PLFull = pful;
			if (swin != -1) *Engine::Honor::SVWin = swin;
			if (sful != -1) *Engine::Honor::SVFull = sful;
			if (rew != -1) *Engine::Honor::Reward = rew;
			return 1;
		}

		if (Type == 244)
		{
			int nID, Range, Type;
			Tools->ParseData(LeftData, "ddd", &nID, &Range, &Type);
			unsigned long Player = Engine::CGame_Character::FindCharacter(nID, 0);

			if (Player) {
				*(DWORD *)(Player + 19572) = Range;
				if (Type || Range) {
					HonorStruct honor = HonorStruct();
					honor.Value = Type;
					honor.Range = Range;

					LockHonor();
					PlayerHonors[Player] = honor;
					UnlockHonor();
				}
			}
			return 1;
		}

		if (Type == 243)
		{
			int Time, Packet, Type, nMsg, Key;
			Tools->ParseData(LeftData, "ddddd", &Time, &Packet, &Type, &nMsg, &Key);
			if (Packet == 5000 && Time > 0)
				insertBuff(Key, nMsg, Time);

			if (Packet == 6000)
				removeBuff(Key, nMsg);
			
			Engine::KGameSys::CallBuff(0, 0, 0, 0, Type, Time, Packet, Key, nMsg);
			return 1;
		}

		if (Type == 242)
		{
			int Colorx, Colory, Colorz, Overlay;
			Tools->ParseData(LeftData, "dddd", &Overlay, &Colorx, &Colory, &Colorz);
			Engine::KGameSys::ScreenOverlay((int)0x008E06A0, Overlay, 1077936128, RGBA2DWORD(Colorx, Colory, Colorz, 255), 0);
			return 1;
		}

		if (Type == 241)
		{
			Interface<IPackets> Packets;
			int Type = 0, IID = 0, Item = 0;
			Tools->ParseData(LeftData, "db", &IID, &Type);
			Item = Engine::KGameSys::FindItemFromIID(IID);
			int Window = Engine::KGameSys::OpenWindow("Item_Conversion_Ok", 0, 0, 0, 0, 0);
			*(BYTE *)(Item + 79) = Type;

			if (Item)
				Engine::KGameSys::SetDssWindow((void*)Window, (int)LeftData);

			return 1;
		}

		if (Type == 240)
		{
			Interface<IPackets> Packets;

			if (Packets->DssUpdateCheck == false)
				Packets->DssUpdateCheck = true;

			return 1;
		}

		if (Type == 0xFE) {
			Tools->ParseData(LeftData, "d", &Check);
			return 1;
		}

		if (Type == 239)
		{
			int id = 0, nTargetType = 0;
			char *effect;
			char AutoRemove = 0, Continues = 0;
			signed int nForced = 0;
			Tools->ParseData(LeftData, "dsdddd", &id, &effect, &AutoRemove, &Continues, &nForced, &nTargetType);
			
			if (strlen(effect) > 0)
				Engine::CFxEntityManager::AddFxToTarget(Engine::AddFx, effect, id, AutoRemove, Continues, nForced, nTargetType);

			return 1;
		}

		if (Type == 238)
		{
			int Value = 0;
			Tools->ParseData(LeftData, "d", &Value);
			
			if (Value == 0)
				AsadalValue = 1;
			
			if (Value == 128)
				AsadalValue = 0;

			return 1;
		}

		if (Type == 237)
		{
			char *name;
			int Time = 0, Type = 0;
			Tools->ParseData(LeftData, "sdd", &name, &Type, &Time);

			if (strlen(name) > 0 && !Engine::KGameSys::WindowCheck(name))
				Engine::KGameSys::OpenWindow(name, 0, 0, 0, 0, 0);

			return 1;
		}

		if (Type == 236)
		{
			char *name;
			Tools->ParseData(LeftData, "s", &name);

			if (strlen(name) > 0 && Engine::KGameSys::WindowCheck(name))
				Engine::KGameSys::CloseWindow(name);

			return 1;
		}

		if (Type == 235)
		{
			int Type = 0, IID = 0, Item = 0;
			Tools->ParseData(LeftData, "dd", &IID, &Type);
			Item = Engine::KGameSys::FindItemFromIID(IID);
			int Window = Engine::KGameSys::WindowCheck("Item_Qigong_Rates");
			bool wasOpen = true;
			if (!Window) {
				wasOpen = false;
				Window = Engine::KGameSys::OpenWindow("Item_Qigong_Rates", 0, 0, 0, 0, 0);
			}

			if (Item && Window)
				Engine::KGameSys::SetQigoong(Window, (int)LeftData);

			if (!wasOpen)
				Engine::KGameSys::CloseWindow("Item_Qigong_Rates");

			return 1;
		}

		if (Type == 234)
		{
			const char *msg;
			Tools->ParseData(LeftData, "s", &msg);

			if (strlen(msg) > 0)
			{
				int Screen = Engine::KGameSys::OpenWindow("screeninfoedit", 0, 0, 0, 0, 0);
				Engine::KGameSys::LatestScreenMsg((void*)Screen, msg);
			}

			return 1;
		}

		if (Type == 233)
		{
			int time = 0;
			Tools->ParseData(LeftData, "d", &time);
			int Window = Engine::KGameSys::OpenWindow("hell_time", 0, 0, 0, 0, 0);

			if (Window)
			{
				Engine::KGameSys::HellTime(Window, 1);
				Engine::KGameSys::SetHellTime(time, 0);
				Engine::KGameSys::RefreshHellTime(Window);
			}

			return 1;
		}

		if (Type == 232)
		{
			Engine::KGameSys::Scenario3_3(0x40, (int)LeftData);
			return 1;
		}

		if (Type == 231)
		{
			Engine::KGameSys::RebirthTalisman(0, 0, (char)LeftData);
			return 1;
		}

		if (Type == 230)
		{
			int IID = 0, pItem = 0, Value = 0;
			Tools->ParseData(LeftData, "dd", &IID, &Value);
			pItem = Engine::KGameSys::FindItemFromIID(IID);

			if (!pItem)
				pItem = Engine::KGameSys::FindItemFromIIDEx(IID);

			if (pItem)
			{
				*(DWORD*)(pItem + 68) = Value;
				*(DWORD*)(pItem + 72) = 0;
			}

			return 1;
		}

		if (Type == 229)
		{
			Engine::KGameSys::ShowPet(1, 1, (char)LeftData);
			return 1;
		}

		if (Type == 228)
		{
			int Type = 0; const char *Msg = "", *CallerName = "", *Name = "";
			Tools->ParseData(LeftData, "dsss", &Type, &Msg, &CallerName, &Name);

			if (strlen(CallerName) > 0 && strlen(Name) > 0)
			{
				this->RecCaller = CallerName;
				this->Recall = Name;
				Engine::KGameSys::MBox((int)Msg, 4, Type, 0, 0);
			}

			return 1;
		}

		if (Type == 227)
		{
			int ID = 0, Type = 0;
			Tools->ParseData(LeftData, "dd", &ID, &Type);

			if (ID && Type)
				Engine::KGameSys::RidingEnable(ID, Type);

			return 1;
		}

		if (Type == 226)
		{
			int ID = 0, Type = 0;
			Tools->ParseData(LeftData, "dd", &ID, &Type);

			if (ID)
				Engine::KGameSys::RidingDisable(ID, Type);

			return 1;
		}

		if (Type == 225)
		{
			char Type = 0, Prefix = 0; int IID = 0;
			Tools->ParseData(LeftData, "bdb", &Type, &IID, &Prefix);
			Engine::KGameSys::DemonGongStone(0, 0, (int)LeftData);
			return 1;
		}

		if (Type == 224)
		{
			char Type = 0; int Value = 0, IID = 0, Item = 0;
			Tools->ParseData(LeftData, "ddb", &IID, &Value, &Type);
			Item = Engine::KGameSys::FindItemFromIID(IID);
			int Window = Engine::KGameSys::WindowCheck("mstone_socket");

			if (Item && Window)
				Engine::KGameSys::SetDemonGongWindow((void*)Window, (int)LeftData);

			return 1;
		}

		if (Type == 223)
		{
			int MAILID = 0;
			Tools->ParseData(LeftData, "d", &MAILID);

			if (MAILID > 0)
			{
				Interface<IPackets> Packets;
				Packets->Send(56, "bd", 9, MAILID);
			}

			return 1;
		}

		if (Type == 222)
		{
			int MID = 0, Quest = 0, Amount = 0;
			Tools->ParseData(LeftData, "ddd", &MID, &Quest, &Amount);

			if (MID && Quest)
			{
				if (Engine::KGameSys::WindowCheck("Quest")) {
					Engine::KGameSys::CloseWindow("Quest");
					Engine::KGameSys::OpenWindow("Quest", 0, 0, 0, 0, 0);
				}

				//ShowMonsterAmount[(Quest*1000)+MID] = Amount;
			}

			return 1;
		}

		if (Type == 221)
		{
			int Pick = 0;
			Tools->ParseData(LeftData, "d", &Pick);
			AutoPick += Pick;
			return 1;
		}

		if (Type == 220)
		{
			StopClient = true;
			Engine::KGameSys::MBox((int)"Please Restart your client using updater.", 0, 5, 0, 0);
			return 1;
		}

		if (Type == 219)
		{
			StopClient = true;
			Engine::KGameSys::MBox((int)"Packet Hack detected.", 0, 5, 0, 0);
			return 1;
		}

		return 1;
	}

	if (Data->Type == 0xFE)
	{
		int Type = 0;

		char *LeftData = Tools->ParseData(Data->Data, "d", &Type);

		if (Type == 255)
		{
			char *xClient, *xEngine;
			Tools->ParseData(LeftData, "ss", &xClient, &xEngine);
			MD5 Client;
			std::ifstream infile;

			if (strlen(xClient) > 0 && strlen(xEngine) > 0)
			{
				std::ifstream infile(xClient);
				if (infile.good()) {
					std::string digestedMD5 = (std::string)Client.digestFile(xClient);
					std::string ValidatedMD5 = (std::string)xEngine;
					std::transform(digestedMD5.begin(), digestedMD5.end(), digestedMD5.begin(), ::toupper);
					std::transform(ValidatedMD5.begin(), ValidatedMD5.end(), ValidatedMD5.begin(), ::toupper);
					if (!StopClient && digestedMD5 != ValidatedMD5)
					{
						StopClient = true;
						std::string xClientt(xClient);
						std::string Msg = "Outdated file: " + xClientt + ".\nClose and update your client.";

						Engine::KGameSys::MBox((int)Msg.c_str(), 0, 0, 0, 0);
						return 1;
					}

				}
				else {
					StopClient = true;
					std::string xClientt(xClient);
					std::string Msg = "Missing file: " + xClientt + ".\nClose and re-extract Client.";

					Engine::KGameSys::MBox((int)Msg.c_str(), 0, 0, 0, 0);
					return 1;
				}
			}
		}

		/*if (Type == 246)
		{
			CreateKey(k1.c_str());
			CreateKey(k2.c_str());
			return 1;
		}*/

		if (Type == 219)
		{
			StopClient = true;
			Engine::KGameSys::MBox((int)"You have been Hardware blocked.", 0, 0, 0, 0);
			return 1;
		}

		if (Type == 218)
		{
			StopClient = true;
			Engine::KGameSys::MBox((int)"Outdated files detected, Please close and update your client from our Website.", 0, 5, 0, 0);
			return 1;
		}

		if (Type == 217) {
			*Engine::KCommand::m_bShowFrame = !*Engine::KCommand::m_bShowFrame;
			return 1;
		}

		if (Type == 216) {
			Expanded = true;
			return 1;
		}

		if (Type == 215) {
			Expanded = false;
			return 1;
		}

		if (Type == 214) {
			if (voteTime >= (int)GetTickCount())
				return 1;

			voteTime = GetTickCount() + 2000;
			char* Url;
			Tools->ParseData(LeftData, "s", &Url);
			ShellExecuteA(0, "open", Url, 0, 0, 1);
			return 1;
		}

		if (Type == 213) {
			const char *Msg;
			Tools->ParseData(LeftData, "s", &Msg);
			Interface<IChatbox> Chatbox;
			Chatbox->Display(Msg);
			return 1;
		}

		if (Type == 212) {
			int FP;
			Tools->ParseData(LeftData, "d", &FP);
			FPEnable = FP;
			return 1;
		}

		if (Type == 211) {
			int Lock = 0;
			int Key = 0;
			Tools->ParseData(LeftData, "dd", &Lock, &Key);
			UniqueKey = Key >> 13;
			KeyD = Lock % 10;
			CryptKey = sha256(Int2String(Lock)) % 9000;
			if (numLock)
				return 1;

			if (!engineCheck()) {
				StopClient = true;
				Engine::KGameSys::MBox((int)"Illegal Files detected, reinstall the client and try again.", 0, 5, 0, 0);
				return 1;
			}
			numLock = Lock;
			this->Send(216, "dsss", (int)Type, PCName, mac.c_str(), getHWID().c_str());
			MD5 SrvChecke, NirvCheck;
			char* engineCheck = SrvChecke.digestFile("Engine.dll");
			if (strlen(engineCheck) && isValidMD5(engineCheck)) {
				this->Send(217, "dds", (int)Type, numLock, engineCheck);
			}

			return 1;
		}

		if (Type == 210) {
			Engine::KGameSys::Pocket(0, 0, (char)LeftData);
			return 1;
		}

		if (Type == 209) {
			int ID = 0, Color = 0;
			Tools->ParseData(LeftData, "dd", &ID, &Color);
			
			if (*(DWORD *)(*Engine::CGame_Character::m_Master + 17476) == ID)
				NamePadType = Color;

			Engine::KGameSys::NamePad2(0, 0, (char)LeftData);
			return 1;
		}

		if (Type == 208) {
			Engine::KGameSys::NamePad(0, 0, (char)LeftData);
			return 1;
		}

		if (Type == 207)
		{
			int minutes = 0;
			Tools->ParseData(LeftData, "d", &minutes);

			int time = minutes * 60 * 1000;

			*Engine::KSocket::TrainingTime = time;

			int Check = Engine::KGameSys::WindowCheck("TrainingTimeWindow");

			if (!Check)
				Check = Engine::KGameSys::OpenWindow("TrainingTimeWindow", 0, 0, 0, 0, 0);

			Engine::KGameSys::RefreshTrainingWindow(Check, time);

			return 1;
		}

		if (Type == 206) {
			Engine::KGameSys::Auction(0, 0, (char)LeftData);
			return 1;
		}

		if (Type == 205) {
			const char* playerName;
			Tools->ParseData(LeftData, "s", &playerName);
			IgnorePlayers.insert(playerName);
			return 1;
		}

		if (Type == 204) {
			const char* playerName;
			Tools->ParseData(LeftData, "s", &playerName);
			IgnorePlayers.erase(playerName);
			return 1;
		}

		if (Type == 203) {
			Interface<IChatbox> Chatbox;
			if (!IgnorePlayers.empty()) {
				Chatbox->Display("========Ignored Players========");
				for (auto it = IgnorePlayers.begin(); it != IgnorePlayers.end(); it++)
					Chatbox->Display(" " + *it);
			}
			else
				Chatbox->Display(" Your ignored players list is empty.");

			return 1;
		}

		if (Type == 202) {
			Engine::KGameSys::Rental(0, 0, (char)LeftData);
			return 1;
		}

		if (Type == 201) {
			int IID = 0, Type = 0;
			Tools->ParseData(LeftData, "dd", &IID, &Type);

			if (Type) {
				int Item = Engine::KGameSys::FindItemFromIID(IID);
				if (Type == 2)
					*(BYTE *)(Item + 124) = 0;
				else if (Type == 3) {
					*(DWORD*)(Item + 68) = (int)time(0) + 1;
					*(DWORD*)(Item + 72) = 0;
				}
				else
					*(BYTE *)(Item + 124) = 1;
			}

			if (Type != 2) {
				int Window = Engine::KGameSys::OtherOpenWindow("rental_extend_question", 0, 0, 0, 0);
				char* v232 = Engine::KGameSys::__RTDynamicCast((int)Window, 0, (struct _s_RTTICompleteObjectLocator *)(void*)0x008B5040, (void*)0x008D0398, 0);
				if (v232)
					Engine::KGameSys::RenewRental((int)v232, IID);
			}

			return 1;
		}

		if (Type == 200)
		{
			Engine::KGameSys::Sasiety(0, 0, (char)LeftData);
			return 1;
		}

		if (Type == 199)
		{
			Engine::KGameSys::SasietyUpdate(0, 1, (char)LeftData);
			return 1;
		}

		if (Type == 198)
		{
			int IID = 0, pItem = 0, Value = 0;
			Tools->ParseData(LeftData, "dd", &IID, &Value);
			pItem = Engine::KGameSys::FindItemFromIID(IID);

			if (!pItem)
				pItem = Engine::KGameSys::FindItemFromIIDEx(IID);

			if (pItem)
				*(DWORD*)(pItem + 116) = Value;

			return 1;
		}

		if (Type == 197) {
			int ID = 0, X = 0, Y = 0, Z = 0;
			Tools->ParseData(LeftData, "dddd", &ID, &X, &Y, &Z);
			unsigned long Player = Engine::CGame_Character::FindCharacter(ID, 0);

			if (Player) {
				*((DWORD *)Player + 4536) = X;
				*((DWORD *)Player + 4537) = Y;
				*((DWORD *)Player + 4538) = Z;
			}
			return 1;
		}

		if (Type == 196) {
			int Check = Engine::KGameSys::WindowCheck("auction_main");

			if (!Check)
				Check = Engine::KGameSys::OpenWindow("auction_main", 0, 0, 0, 0, 0);

			Engine::KGameSys::AuctionSetWindow(Check, 2);

			Engine::KGameSys::AuctionAdd((void*)Check, (void*)LeftData);
			return 1;
		}

		if (Type == 195) {
			Engine::KGameSys::SummonedNPC(0, 0, (char)LeftData);
			return 1;
		}

		if (Type == 194) {
			int ID = 0, index = 0, X = 0, Y = 0, Z = 0, Time = 0, Model = 0;
			Tools->ParseData(LeftData, "dwddddd", &ID, &index, &Model, &X, &Y, &Z, &Time);

			if (ID < 0 && Time) {
				ConfigNPC npc = ConfigNPC();
				npc.ID = ID;
				npc.index = index;
				npc.X = X;
				npc.Y = Y;
				npc.Z = Z;
				npc.Model = Model;
				npc.Time = (int)time(0) + Time;
				SummonedNPCs.push_back(npc);
			}
			return 1;
		}

		if (Type == 193) {
			Engine::KGameSys::MasterEnchant(0, 0, (char)LeftData);
			return 1;
		}

		if (Type == 192) {
			Engine::KGameSys::PetBuff(0, 0, (char)LeftData);
			return 1;
		}

		if (Type == 191) {
			int Timer = 0;
			Tools->ParseData(LeftData, "dd", &Timer, &PressableKey);
			if (PressableKey) {
				string c;
				c = (char)(PressableKey >> 19);
				string msg = "[AFK Check] Press [" + c + "] within [" + Int2String(Timer) + "] second(s) to continue...";
				Engine::KGameSys::SetScreenInfo(5, (void*)msg.c_str(), 0);
			}
			return 1;
		}

		if (Type == 190) {
			Tools->ParseData(LeftData, "d", &FaceChange);
			return 1;
		}

		if (Type == 189) {
			int a1 = 0, a2 = 0, a3 = 0, a4 = 0;
			char a5 = 0;
			int a6 = 0;

			Tools->ParseData(LeftData, "ddddbd", &a1, &a2, &a3, &a4, &a5, &a6);
			DamageCheck = 1;
			Engine::KGameSys::OnDamage(a2, a3, a4, a6, a1, a5, 1, 0, 0);
			DamageCheck = 0;
			return 1;
		}

		if (Type == 188) {
			char face = 0, hair = 0;
			Tools->ParseData(LeftData, "bb", &face, &hair);
			*Engine::Face = face;
			*Engine::Hair = hair;
			*(BYTE *)(*Engine::CGame_Character::m_Master + 40653) = face;
			*(BYTE *)(*Engine::CGame_Character::m_Master + 40652) = hair;

			Engine::CGame_Character::Refresh2();
			return 1;
		}

		if (Type == 187)
		{
			int id, effect = 0;
			Tools->ParseData(LeftData, "dd", &id, &effect);

			fxLock.Enter();
			if (Fxs.count(id)) {
				std::vector<int> fx = Fxs.find(id)->second;
				for (int i = 0; i < (int)fx.size(); i++)
					Engine::CFxEntityManager::RemoveFx(Engine::AddFx, fx[i], 0);
				Fxs.erase(id);
			}
			fxLock.Leave();
			return 1;
		}

		if (Type == 186)
		{
			int effect = 0, id = 0;
			Tools->ParseData(LeftData, "dd", &id, &effect);

			int num = effect % 1000;

			effect = (effect - num) / 1000;

			if (effect) {
				std::string s = "back_decorate_" + Int2String(effect);
				
				fxLock.Enter();
				Fxs[id].push_back(Engine::CFxEntityManager::AddFxToTarget(Engine::AddFx, s.c_str(), id, 1, 0, 0, 0));
				fxLock.Leave();
			}

			return 1;
		}

		if (Type == 185)
		{
			int effect = 0, id = 0;
			Tools->ParseData(LeftData, "dd", &id, &effect);
			int num = effect % 1000;

			effect = (effect - num) / 1000;

			if (effect) {
				std::string s = "back_decorate_" + Int2String(effect);

				fxLock.Enter();
				if (Fxs.count(id)) {
					std::vector<int> fx = Fxs.find(id)->second;
					for (int i = 0; i < (int)fx.size(); i++)
						Engine::CFxEntityManager::RemoveFx(Engine::AddFx, fx[i], 0);
					Fxs.erase(id);
				}
				for(int i=0;i<num+1;i++)
					Fxs[id].push_back(Engine::CFxEntityManager::AddFxToTarget(Engine::AddFx, s.c_str(), id, 1, 0, 0, 0));
				fxLock.Leave();
			}

			return 1;
		}


		if (Type == 184)
		{
			Tools->ParseData(LeftData, "d", &GeonCheck);
			return 1;
		}

		if (Type == 183)
		{
			Tools->ParseData(LeftData, "d", &Absorb);
			return 1;
		}

		if (Type == 182)
		{
			Tools->ParseData(LeftData, "d", &Channel);
			return 1;
		}
		
		if (Type == 181)
		{
			int ShopLimit = 0, TradeLimit = 0;
			Tools->ParseData(LeftData, "dd", &ShopLimit, &TradeLimit);

			if (ShopLimit != 11) {
				int Check = ShopLimit - 1;
				Tools->MemcpyEx((void*)0x006C8340, &Check, 1);
				Tools->MemcpyEx((void*)0x006C8344, &ShopLimit, 1);
			}

			if (TradeLimit != 11) {
				int Check = TradeLimit - 1;
				Tools->MemcpyEx((void*)0x006C8CA4, &Check, 1);
				Tools->MemcpyEx((void*)0x006C8CB6, &TradeLimit, 1);
				Tools->MemcpyEx((void*)0x0063EFD9, &Check, 1);
				Tools->MemcpyEx((void*)0x0063EFF6, &TradeLimit, 1);
			}

			return 1;
		}

		if (Type == 179)
		{
			int Index = 0, pItem = 0, Amount = 0;
			Tools->ParseData(LeftData, "dd", &Index, &Amount);

			if (Index) {
				int T = Engine::KGameSys::IndexItem(2u, Index);
				int Name = Engine::KGameSys::ItemName(T, 1);
				std::string itemName((const char*)Name);
				std::string msg = "You have lost" + ((Amount > 0) ? " " + Int2String(Amount) : "") + " " + itemName + ((Amount > 1) ? "s." : ".");
				Engine::KGameSys::AddInfoMessage(msg.c_str(), RGB(255, 0, 0), -1);
			}

			return 1;
		}

		if (Type == 178)
		{
			int Type = 0; const char *Msg = "";
			Tools->ParseData(LeftData, "ds", &Type, &Msg);
			std::string Msgs = "[Notice] ";
			Msgs += Msg;
			Engine::KGameSys::NoticeMsg((char*)Msgs.c_str(), Type);
			return 1;
		}

		if (Type == 177)
		{
			int id = 0;
			char *effect;
			Tools->ParseData(LeftData, "dsd", &id, &effect,&cEffect);
			
			if (!cEffect || (cEffect && !SkinDisabled)) {
				if (strlen(effect) > 0)
					Engine::CFxEntityManager::AddFxToBone(Engine::BoneFx, id, effect);
			}

			cEffect = 0;
			return 1;
		}

		if (Type == 176)
		{
			int id = 0;
			char *effect;
			Tools->ParseData(LeftData, "ds", &id, &effect);

			if (strlen(effect) > 0)
				Engine::CFxEntityManager::RemoveBoneFx(id, effect);

			return 1;
		}

		if (Type == 175)
		{
			char* name;
			Tools->ParseData(LeftData, "s", &name);

			*(BYTE *)(*Engine::CGame_Character::m_Master + 19856) = 0;
			*(BYTE *)(*Engine::CGame_Character::m_Master + 19856) = 1;

			sprintf((char *)Engine::CharName, "%s", name);

			Engine::CharacterBar::UpdateBar((void *)*Engine::CharacterBar::CharBarCurrent, name, (unsigned __int8)*Engine::Level);
			return 1;
		}

		if (Type == 174)
		{
			Tools->ParseData(LeftData, "d", &SkinDisabled);

			if (SkinDisabled == -1)
				SkinDisabled = 0;

			return 1;
		}

		if (Type == 173)
		{
			int ID = 0, Type = 0;
			Tools->ParseData(LeftData, "dd", &ID, &Type);
			int Src = Engine::KGameSys::KMsgGet(Type);
			if (Src) {
				unsigned long CheckP = Engine::CGame_Character::FindCharacter(ID, 0);

				COLORREF color = 0xFF8000u;
				if (Type == 3506)
					color = 0xFFu;
				if (Type == 3507)
					color = RGB(255, 255, 0);

				if (CheckP) {
					NameColorC = Src;
					*(DWORD *)(CheckP + 19856) = 1;
					Engine::KGameSys::SetCharName(CheckP, (BYTE*)Src, color, 1, 1);
					NameColorC = 0;
				}
			}
			return 1;
		}

		if (Type == 172) {
			/*
			1 to 9 => error msgs
			10 => "d" minutes left
			11 => "d" seconds left
			12 => System start
			13 => Score/Time
			14 => Reward
			15 => Open "bazaa title etc"
			16 => open mbyesno, result"
			17 => Error "Only one emblem can be picked up"
			18 to 31 => Error msgs
			*/
			Engine::KGameSys::TriangularBattle(0, 0, (char)LeftData);
			return 1;
		}

		if (Type == 171) {
			/*
			1 => "d" players registered to triangular battle
			2 => "b" An emblem is setting up
			3 => Emblem successfully setup
			4 => There is no emblem to be setup
			5 => Another player is setting up
			6 => Another player is pulling out
			7 => An emblem has already been set up
			8 => There is no emblem in your inventory
			9 => "s" => player name
				"d or b" type{
				1 => [ %1 ] has set up [ %2 ]
				2 => [ %1 ] has set up [ %2 ]
				3 => [ %1 ] has set up [ %2 ]
				}
				"d" => ?
			10 => "b" An emblem is being pulled out
			11 => Successfully pulled out
			12 => Pulling out an emblem has been canceled.
			13 => No emblem here
			14 => Another player is pulling out.
			15 => Another player is setting up.
			16 => Insufficient inventory slots.
			17 => Failed to carry off the emblem.
			18 => "s" => player name
				"d or b" type{
				1 => [ %1 ] has obtained [ %2 ]
				2 => [ %1 ] has obtained [ %2 ]
				3 => [ %1 ] has obtained [ %2 ]
				}
				"d" => ?
			19 => score
			20 => "d" (loop) "dbdd" => to verify
			21 => "d" (loop) "dbdd" => to verify
			22 => "d" to verify
			24 => "s" => player name
				"d or b" type{
				1 => [ %2 ] obtained by [ %1 ] has returned to the altar.
				2 => [ %2 ] obtained by [ %1 ] has returned to the altar.
				3 => [ %2 ] obtained by [ %1 ] has returned to the altar.
				}
				"d" => ?
			25 => "b" 1-2-3 The dropped [ %1 ] has been gone back to the altar.
			26 => Time
			27 => "dd" to verify
			28 => "ddd" Triangular Battle Rewards Buff (3400 to 3408) %1!d! seconds later, %2 applies to %3!d! players.
			*/
			Engine::KGameSys::TriangularBattle2(0, 0, (char)LeftData);
			return 1;
		}

		if (Type == 170) {
			int ID = 0, Index = 0;
			Tools->ParseData(LeftData, "dd", &ID, &Index);

			unsigned long CheckP = Engine::CGame_Character::FindCharacter(ID, 0);

			if (CheckP) {
				if (Index) {
					if (!*(DWORD *)(CheckP + 41420))
						Engine::KGameSys::UpdateItemEffect(CheckP, 0, 0, 0, 0x100, 1);
				}
				else {
					if (*(DWORD *)(CheckP + 41420))
						Engine::KGameSys::UpdateItemEffect(CheckP, 0, 0x100, 0, 0, 1);
				}
			}

			return 1;
		}

		if (Type == 169) {
			int ID = 0;
			const char *GuildName, *GuildTile;
			Tools->ParseData(LeftData, "dss", &ID, &GuildTile, &GuildName);
			
			unsigned long CheckP = Engine::CGame_Character::FindCharacter(ID, 0);

			if (CheckP) {
				sprintf((char *)(CheckP + 17612), "%s", GuildName);
				sprintf((char *)(CheckP + 17872), "%s", GuildTile); 
				Engine::KGameSys::UpdatePlayerName(CheckP, 0);
			}

			return 1;
		}

		if (Type == 168) {
			Engine::KGameSys::SufferingValley(0, 0, (char)LeftData);
			return 1;
		}

		if (Type == 167) {
			Engine::KGameSys::Enchant(0, 0, (char)LeftData);
			return 1;
		}
		
		if (Type == 166) {
			const char *PlayerName;
			Tools->ParseData(LeftData, "s", &PlayerName);

			sprintf((char *)(*Engine::CGame_Character::m_Master + 17608), "%s", PlayerName);
			Engine::CGame_Character::Refresh2();
			Engine::CGame_Character::InitCharacter(*Engine::CGame_Character::m_Master, 0);

			return 1;
		}

		return 1;
	}

	Engine::KSocket::OnRecv(Data);

	return 1;
}