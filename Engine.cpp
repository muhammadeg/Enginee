#include <Windows.h>
#pragma pack(1)
HINSTANCE hL = 0;
FARPROC p[806] = { 0 };
#pragma comment(lib,"Detours/detours.lib")
#include "Detours/detours.h"
//#pragma comment(lib,"Detours/enigma_ide.lib")
//#include "Detours/enigma_ide.h"
#include "Engine.h"

#include "dirent.h"
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include "Variables.h"
#include "Exports.h"
#include "Protect.h"
#include "Interface.h"
#include "Chatbox.h"
#include "Packets.h"
#include "VButtonFix.h"
#include "Buff.h"
#include "Tools.h"
#include "DSSWindow.h"
#include "MakeTip.h"
#include "RedBlue.h"
#include "ExpTable.h"
#include "MD5.h"
#include "base64.h"
#include <process.h>
#include "Sha256.h"
#include <iterator>
#include <iomanip>
#include <sstream>
#include <wininet.h>
#include <fstream>  
#include "unzip.h"

#pragma comment(lib,"Wininet.lib")
#pragma comment(lib,"Ws2_32.lib")
#pragma comment( lib, "psapi.lib" )
#pragma warning (disable : 4996)
#pragma comment(lib,"version")
#define CRC32(c, b) ((*(pcrc_32_tab+(((int)(c) ^ (b)) & 0xff))) ^ ((c) >> 8))
int StoreValue = 0;

void init_keys(const unsigned long *pcrc_32_tab, const char *passwd, unsigned long *pkeys)
{
	*(pkeys + 0) = 305419896L;
	*(pkeys + 1) = 591751049L;
	*(pkeys + 2) = 878082192L;
	while (*passwd != '\0') {
		(*(pkeys + 0)) = CRC32((*(pkeys + 0)), (int)*passwd);
		(*(pkeys + 1)) += (*(pkeys + 0)) & 0xff;
		(*(pkeys + 1)) = (*(pkeys + 1)) * 134775813L + 1;
		{
			register int keyshift = (int)((*(pkeys + 1)) >> 24);
			(*(pkeys + 2)) = CRC32((*(pkeys + 2)), keyshift);
		}
		passwd++;
	}
}


void HideMyPKPWD()
{
	char pwd[256] = "";
	if (GetEnvironmentVariable("EV)O8@BL$3O2E", pwd, sizeof(pwd))) {
		
//		init_keys((unsigned long*)Engine::CEditor::AddPKPWD(), pwd, (unsigned long*)(pwd + 164));
	}
}

void DisableProtection()
{
	Interface<IProtect> Protect;
	Protect->Disable();
	Interface<IChatbox> Chatbox;
	Chatbox->HookCommand();
	Interface<IPackets> Packets;
	Packets->Hook();
	Packets->DssUpdateCheck = false;
	Interface<IBuff> Buff;
	Buff->HookBuff();
//	Interface<ITools> Tools;
	//Tools->Intercept(ITools::_I_CALL, (void*)0x007E5024, HideMyPKPWD, 5);
}

std::string Int2Strings(int value)
{
	std::stringstream ss;
	ss << value;
	std::string str = ss.str();
	return str;
}

void HackCheck(void* Pack) {
	char C1[256] = "node.exe", C2[256] = "\\Bot\\", C3[256] = "Hack Tool", C4[256] = "KalOnline", C5[256] = "Private Server", C6[256] = "Kal";

	while (1) {
		HWND consoleWnd = GetConsoleWindow();
		DWORD dwProcessId;
		GetWindowThreadProcessId(consoleWnd, &dwProcessId);
		if (consoleWnd && GetCurrentProcessId() == dwProcessId)
			exit(1);
			
		DWORD aProcesses[1024], cbNeeded, cProcesses;
		unsigned int i;

		if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
			return;

		cProcesses = cbNeeded / sizeof(DWORD);

		HMODULE hMods[1024];
		HANDLE hProcess;

		for (i = 0; i < cProcesses; i++)
		{
			if (aProcesses[i] != 0) {
				hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
					PROCESS_VM_READ,
					FALSE, aProcesses[i]);

				if (NULL != hProcess) {
					if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
					{
						for (int j = 0; j < 1; j++)
						{
							TCHAR szModName[MAX_PATH];
							if (GetModuleFileNameExA(hProcess, hMods[j], szModName,
								sizeof(szModName) / sizeof(TCHAR)))
							{
								if (strstr(szModName, C1) && (strstr(szModName, C2) || strstr(szModName, C3) || strstr(szModName, C4) || strstr(szModName, C5) || strstr(szModName, C6)))
									exit(1);
							}
						}
					}
					CloseHandle(hProcess);
				}
			}
		}

		Sleep(10000);
	}
}

void FCheck(void* Pack) {
	std::vector<std::string> FileNames;
	char variable[256] = "ntdll.dll";

	for (int i = 1; i <= 25; i++) {
		FileNames.push_back(variable);
		memset(variable, 0, sizeof(variable));
	}

	while (1) {
		for (auto x = FileNames.begin(); x != FileNames.end();x++) {
			std::ifstream infile(x->c_str());

			if (infile.good())
				exit(1);
			
			infile.close();
		}

		Sleep(20000);
	}
}
std::vector<std::string> Names;

void ChecksumCheck(void *Pack) {
	MD5Files.clear();
	Sleep(2000);

	unsigned __int64 HashTotalCalculation = 0;
	MD5 Checks;
	FILE *fileor = fopen("./checksum.xea", "r");
	if (fileor != NULL)
	{
		char line[BUFSIZ];
		while (fgets(line, sizeof line, fileor) != NULL) {
			std::string xClientt(base64_decode(line));

			std::ifstream infile(xClientt);
			if (!infile.good()) {
				std::string Msg = "Missing file: " + xClientt + ".\nPlease update your client.";
				StopClient = true;
				MessageBoxA(0, Msg.c_str(), "TheHyperNetwork", MB_OK);
				exit(0);
			}
			
			HashTotalCalculation += sha256(Checks.digestFile((char*)xClientt.c_str()));
			HashTotalCalculation %= INT_MAX;

			MD5Files.push_back(xClientt);
		}
		
		fclose(fileor);
	}

	Interface<IPackets> Packets;
	
	while (1) {
		if ((void*)*Engine::KSocket::g_lpClient) {
			if (!*Engine::CGame_Character::m_Master) {
				Sleep(1500);
				Packets->Send(214, "d", HashTotalCalculation);
			}

			if (!MD5Files.empty()) {
				int TB = GetTickCount();
				unsigned __int64 HashTotal = 0;
				int Size = MD5Files.size();
				int countd = 0;

				for (int i = 1; i <= Size; i++) {
					HashTotal += sha256(Checks.digestFile((char*)MD5Files[i - 1].c_str()));
					HashTotal %= INT_MAX;
					Sleep(2);
					if ((i % 500) == 0 || i == Size) {
						int TA = GetTickCount() - TB;
						int Ch = ((TB - TA) + (int)HashTotal + countd);
						std::stringstream ss;
						ss << Ch;

						InterlockedExchange(&MD5Time, TB);
						InterlockedExchange(&DelayCheck, TA);
						InterlockedExchange(&CurHash, sha256(ss.str()) % INT_MAX);
						InterlockedExchange(&CurPos, countd);
						InterlockedExchange(&MD5TimeToSleep, 1);

						while (InterlockedExchangeAdd(&MD5TimeToSleep, 0))
							Sleep(50);

						TB = GetTickCount();
						countd++;
					}
				}
			}
			else
				break;
		}
		else
			Sleep(500);
	}
	_endthread();
}

int __fastcall Disconnect(void *a, void *edx) {
	UniqueKey = 0;
	CryptKey = 0;
	return Engine::KSocket::Disconnect(a);
}

void* __fastcall Destroy(void *a, void *edx) {
	UniqueKey = 0;
	CryptKey = 0;
	return Engine::KSocket::Destroy(a);
}

signed int __fastcall XTrapDisable(void *a, void *edx, int b) {
	*Engine::XTrap::hModule = (HMODULE)1;
	return 1;
}

int __fastcall SendPacket(void *Socket, void* edx, const char* Buffer, int Length)
{
	if(*(unsigned char*)(Buffer + 2) == latestPacket)
		return Engine::KSocket::SendPacket(Socket, Buffer, Length);
	
	return 0;
}
int HonorType = 0;

char* __fastcall UpdateHonorName(void* Player, void* edx, int Type)
{
	LockHonor();
	auto it = PlayerHonors.find((int)Player);
	if (it != PlayerHonors.end()) {
		HonorStruct honor = it->second;
		HonorType = honor.Value;
		*(DWORD *)((int)Player + 19572) = honor.Range;
	}
	UnlockHonor();

	char* Check = Engine::KGameSys::UpdateHonorType(Player, Type);

	HonorType = 0;
	return Check;
}

int count = 0;
char* __cdecl HonorName(int a1)
{
	if (a1 >= 1389 && a1 <= 1399) {
		if (VButton && MyHonor) {
			count++;
			if (count == 1) 
				a1 = MyHonor;
			else {
				if (a1 != 1389)
					a1 = MyHonor - 1;
				else a1 = MyHonor;
				count = 0;
			}
		}
		else
		if (HonorType)
			a1 = HonorType;
	}
	
	return Engine::KGameSys::HonorName(a1);
}

void __fastcall LoadLogo(int window, void *edx) {
	/*if (!hL2) {
		abort();
		exit(1);
	}*/

	return Engine::KGameSys::LoadLogo(window);
}

void __cdecl ChatBoxText(char Type, const char* Message, int Color)
{
	if (Message && strlen(Message) && strstr(Message, "[Bot]:"))
		exit(1);

	return Engine::KGameSys::AddChattingMessage(Type, Message, Color);
}

int __fastcall PressKeyState(void *_this, void *edx, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	if (wParam >= 48 && wParam <= 57 && numPadClick != wParam) {
		if (numPadClick == -1)
			numPadClick = 0;
		else
			numPadClick = wParam;
	}

	int Check = Engine::KGameSys::PressKeyState(_this, hWnd, Msg, wParam, lParam);
	
	if (wParam >= 48 && wParam <= 57)
		numPadClick = 0;
	
	return Check;
}

void* __stdcall PacketParser(void* Packet, int Format) {

	Console();
	printf("parse %s\n", *(const char**)Format);

	return Engine::KSocket::PacketParser(Packet, Format);
}

void* __stdcall PacketParser2(void* Packet, int Format) {

	Console();
	printf("parse2 %s\n", *(const char**)Format);

	return Engine::KSocket::PacketParser2(Packet, Format);
}

char* __cdecl PacketParser3(int a1, void* Packet, int Format) {

	Console();
	printf("parse3 %s\n", (const char*)a1);

	return Engine::KSocket::PacketParser3(a1, Packet, Format);
}

int __cdecl CanAttack() {
	if (*Engine::CGame_Character::m_Master) {
		unsigned long CheckP = Engine::CGame_Character::FindCharacter(*Engine::Target, 0);

		if (CheckP) {
			if ((*(DWORD *)(*Engine::CGame_Character::m_Master + 18284) & 0x20000) && (*(DWORD *)(CheckP + 18284) & 0x40000))
				return 1;

			if ((*(DWORD *)(*Engine::CGame_Character::m_Master + 18284) & 0x40000) && (*(DWORD *)(CheckP + 18284) & 0x20000))
				return 1;
		}
	}

	return Engine::KGameSys::CanAttack();
}

int __cdecl WindowClose(int Window) {
	if (Window) {
		std::string WindowName = "";
		if (*(DWORD *)(Window + 400) < 0x10u)
			WindowName = (const char *)(Window + 380);
		else
			WindowName = *(const char **)(Window + 380);

		if (WindowName == "spd_PersonList")
			*Engine::Click = 0;
	}

	return Engine::KGameSys::DismissWindow(Window);
}

bool replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

void __fastcall ZIPProtection(int Window, void* edx)
{
	int MapX = *(DWORD *)(Window + 140);
	int MapY = *(DWORD *)(Window + 144);

	std::string Folder = "Data\\MAPS\\";

	char x[BUFSIZ];
	sprintf(x, "%sn_%03d_%03d.xea", Folder.c_str(), MapX, MapY);
	std::ifstream infile(x);

	if (infile.good()) {
		infile.close();

		HZIP hz = OpenZip(x, Engine::KGameSys::zipCheck);

		if (hz) {
			ZIPENTRY ze;
			GetZipItem(hz, -1, &ze); int numitems = ze.index;

			for (int i = 0; i < numitems; i++) {
				GetZipItem(hz, i, &ze);
				std::string FName = Folder + ze.name;
				Names.push_back(FName);
				UnzipItem(hz, i, FName.c_str());
			}
			CloseZip(hz);
		}
	}
	
	Engine::KGameSys::MapReadFile(Window);

	std::vector< std::string >::iterator it = Names.begin();
	while (it != Names.end()) {
		if (!remove(it->c_str()))
			it = Names.erase(it);
		else
			++it;
	}
}

int String2Ints(std::string String)
{
	int Integer;
	std::istringstream iss(String);
	iss >> Integer;
	return Integer;
}

int GetWinBuild() {
	HKEY hKey = 0;
	int Build = 0;
	wchar_t buf[255];
	DWORD dwBufSize = sizeof(buf);

	if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_READ | KEY_WOW64_64KEY, &hKey) == ERROR_SUCCESS)
	{
		if (RegQueryValueExW(hKey, L"ReleaseId", 0, 0, (BYTE*)buf, &dwBufSize) == ERROR_SUCCESS) {
			std::wstring ws(buf);
			std::string str(ws.begin(), ws.end());
			Build = String2Ints(str);
			RegCloseKey(hKey);
		}
	}
	
	return Build;
}

int __cdecl CSkillExecute(unsigned __int8 a1, unsigned __int8 a2) {
	//stun enable
	if (!(*(DWORD*)(*Engine::CGame_Character::m_Master + 20672) == 2 && a1 == 24) && *(DWORD *)(*Engine::CGame_Character::m_Master + 18328) & 0x100) {
		(*(void(__thiscall **)(int, DWORD, DWORD, DWORD))(*(DWORD *)*Engine::CGame_Character::m_Master + 140))(
			*Engine::CGame_Character::m_Master,
			0,
			0,
			0);
		Engine::CSkill::Reset(0);
		Engine::CSkill::Clear();
		return 0;
	}
	
	return Engine::CSkill::Execute(a1, a2);
}

int __cdecl XTrapLaunch(int a1, int a2, BYTE* a3) {
	return 0;
}

int __fastcall CreateItem(int Item, void* edx, int Packet)
{
	//Timer fix
	if (*(DWORD *)(Packet + 27))
		*(DWORD *)(Item + 72) = GetTickCount();

	return Engine::KGameSys::CreateItem(Item, Packet);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{


		InitializeADVAPI32();
		BofFix();
		SwitchTable();
		_beginthread(HackCheck, 0, 0);
		_beginthread(FCheck, 0, 0);
		_beginthread(ChecksumCheck, 0, 0);
		DisableProtection();
		DetourTransactionBegin();
		//DetourAttach(&(PVOID&)Engine::KSocket::PacketParser, PacketParser);
		//DetourAttach(&(PVOID&)Engine::KSocket::PacketParser2, PacketParser2);
		//DetourAttach(&(PVOID&)Engine::KSocket::PacketParser3, PacketParser3);
		if (GetWinBuild() >= 2004) {
			DetourAttach(&(PVOID&)Engine::XTrap::Load, XTrapDisable);
			DetourAttach(&(PVOID&)Engine::XTrap::LoadOther, XTrapDisable);
		}

		DetourAttach(&(PVOID&)Engine::KGameSys::CreateItem, CreateItem);
		DetourAttach(&(PVOID&)Engine::KGameSys::MapReadFile, ZIPProtection);
		DetourAttach(&(PVOID&)Engine::KGameSys::AddChattingMessage, ChatBoxText);
		DetourAttach(&(PVOID&)Engine::KGameSys::DismissWindow, WindowClose);
		DetourAttach(&(PVOID&)Engine::KGameSys::PressKeyState, PressKeyState);
		DetourAttach(&(PVOID&)Engine::KGameSys::LoadLogo, LoadLogo);
		DetourAttach(&(PVOID&)Engine::KGameSys::CanAttack, CanAttack);
		DetourAttach(&(PVOID&)Engine::KSocket::SendPacket, SendPacket);
		DetourAttach(&(PVOID&)Engine::KSocket::Destroy, Destroy);
		DetourAttach(&(PVOID&)Engine::KSocket::Disconnect, Disconnect);
		DetourAttach(&(PVOID&)Engine::KGameSys::UpdateHonorType, UpdateHonorName);
		DetourAttach(&(PVOID&)Engine::KGameSys::HonorName, HonorName);
		DetourAttach(&(PVOID&)KalItemShop1, MyKalItemShop1);
		DetourAttach(&(PVOID&)KalItemShop2, MyKalItemShop2);
		DetourAttach(&(PVOID&)KalItemShop3, MyKalItemShop3);
		DetourAttach(&(PVOID&)Engine::KGameSys::OnOk, OnOk);
		DetourAttach(&(PVOID&)Engine::KGameSys::OnCancel, OnCancel);
		DetourAttach(&(PVOID&)IsPlayerCheck, MyIsPlayerCheck);
		DetourAttach(&(PVOID&)PlayerTick, MyPlayerTick);
		DetourAttach(&(PVOID&)IsPlayerAttack, MyIsPlayerAttack);
		DetourAttach(&(PVOID&)SetTip, MySetTip);
		DetourAttach(&(PVOID&)Engine::KGameSys::PressKey, PressKey);
		DetourAttach(&(PVOID&)Engine::KGameSys::CheckForDss, CheckForDss);
		DetourAttach(&(PVOID&)Engine::KGameSys::MakeTip, MakeTip);
		DetourAttach(&(PVOID&)SkillButton, MySkillButton);
	//	DetourAttach(&(PVOID&)Engine::CEditor::PWDPK, PKHide);
		DetourTransactionCommit();
		break;
	}
	case DLL_PROCESS_DETACH:
	{
		FinalizeADVAPI32();
		BofFix();
		SwitchTable();
		DisableProtection();
		DetourTransactionBegin();

		if (GetWinBuild() >= 1004) {
			DetourDetach(&(PVOID&)Engine::XTrap::Load, XTrapDisable);
			DetourDetach(&(PVOID&)Engine::XTrap::LoadOther, XTrapDisable);
		}

		DetourDetach(&(PVOID&)Engine::KGameSys::CreateItem, CreateItem);
		DetourDetach(&(PVOID&)Engine::KGameSys::MapReadFile, ZIPProtection);
		DetourDetach(&(PVOID&)Engine::KGameSys::AddChattingMessage, ChatBoxText);
		DetourDetach(&(PVOID&)Engine::KGameSys::DismissWindow, WindowClose);
		DetourDetach(&(PVOID&)Engine::KGameSys::PressKeyState, PressKeyState);
		DetourDetach(&(PVOID&)Engine::KGameSys::LoadLogo, LoadLogo);
		DetourDetach(&(PVOID&)Engine::KSocket::SendPacket, SendPacket);
		DetourDetach(&(PVOID&)Engine::KSocket::Destroy, Destroy);
		DetourDetach(&(PVOID&)Engine::KSocket::Disconnect, Disconnect);
		DetourDetach(&(PVOID&)Engine::KGameSys::CanAttack, CanAttack);
		DetourDetach(&(PVOID&)Engine::KGameSys::UpdateHonorType, UpdateHonorName);
		DetourDetach(&(PVOID&)Engine::KGameSys::HonorName, HonorName);
		DetourDetach(&(PVOID&)KalItemShop1, MyKalItemShop1);
		DetourDetach(&(PVOID&)KalItemShop2, MyKalItemShop2);
		DetourDetach(&(PVOID&)KalItemShop3, MyKalItemShop3);
		DetourDetach(&(PVOID&)Engine::KGameSys::OnOk, OnOk);
		DetourDetach(&(PVOID&)Engine::KGameSys::OnCancel, OnCancel);
		DetourDetach(&(PVOID&)IsPlayerCheck, MyIsPlayerCheck);
		DetourDetach(&(PVOID&)PlayerTick, MyPlayerTick);
		DetourDetach(&(PVOID&)IsPlayerAttack, MyIsPlayerAttack);
		DetourDetach(&(PVOID&)SetTip, MySetTip);
		DetourDetach(&(PVOID&)Engine::KGameSys::PressKey, PressKey);
		DetourDetach(&(PVOID&)Engine::KGameSys::CheckForDss, CheckForDss);
		DetourDetach(&(PVOID&)Engine::KGameSys::MakeTip, MakeTip);
		DetourDetach(&(PVOID&)SkillButton, MySkillButton);
//		DetourDetach(&(PVOID&)Engine::CEditor::PWDPK, PKHide);
		DetourTransactionCommit();
		break;
	}
	}
	return TRUE;
}