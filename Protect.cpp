#include <windows.h>
#include "Protect.h"
#include "Interface.h"
#include "Engine.h"
#include "Tools.h"
#include "Variables.h"
#include "MD5.h"
//#pragma comment(lib,"Detours/enigma_ide.lib")
//#include "Detours/enigma_ide.h"
#include <algorithm>
#include <sstream>
#include <fstream>  
#include <ctime>  
#include "unzip.h"
CREATE_INTERFACE(IProtect)

int IsSound = 0;
int IsInitItem = 0;

std::string Crypt(std::string Key)
{
	std::string output = Key;

	for (int i = 0; i < (int)Key.size(); i++)
		output[i] = Key[i] ^ 250;

	return output;
}
static int(__cdecl *Connection)(int Type, const char *Text, ...) = (int(__cdecl*)(int, const char*, ...))0x00488BA0;

static unsigned int(__thiscall *GetItemCount)(void *Player, unsigned __int8 a2, int Index) = (unsigned int(__thiscall*)(void*, unsigned __int8, int))0x00730C70;

static void(__thiscall *GetMacAddress)(int a1, char a2, rsize_t MaxCount) = (void(__thiscall*)(int, char, rsize_t))0x00404A90;

int __cdecl ConnectionFix(int Type, const char *Text, int Value, int Object, int Argument)
{
	return Connection(Type, "bd", Value, Object);
}

int __cdecl MailFix(void* Type, const char *Text, unsigned __int8 *Value, int *Object)
{
	return Connection((int)Type, "b", Value);
}

DWORD __stdcall FixGetFileAttributesA(LPCSTR lpFileName)
{
	return 0;
}

namespace CGame_Auction
{
	static unsigned long *Auction1 = (unsigned long*)0x009C9800;
	static unsigned long *Auction2 = (unsigned long*)0x009C9804;

}

int __stdcall MyAuction(int a1)
{
	int Item = *CGame_Auction::Auction1 + (0 << 7);
	int i = 1;
	while (*(DWORD *)(a1 + 116) != *(DWORD *)(Item + 28)) {
		Item = *CGame_Auction::Auction1 + (i << 7);
		i++;
	}
	return Item;
}

int __cdecl QuestCheck(int k, int j)
{
	return 1;
}

int __fastcall JewelsChange(void *Player, void* edx, unsigned __int8 a2, int Index) {
	Index = 6321;
	return GetItemCount(Player, a2, Index);
}

void __fastcall PackCheck(unsigned int a1, int a2, int a3)
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	*(DWORD *)(a1 + 8) *= 144;
	int v = (*(DWORD *)(a1 + 8) - *(DWORD *)(a1 + 4)) / 144;
	*(DWORD *)(a1 + 12) /= 144;
	printf("%d\n", v);
}
const std::string forbiddenChars = "\\-/:?\"<>|";
static char ClearForbidden(char toCheck)
{
	if (forbiddenChars.find(toCheck) != std::string::npos)
	{
		return ' ';
	}

	return toCheck;
}
void removeSpaces(char *str)
{
	// To keep track of non-space character count 
	int count = 0;

	// Traverse the given string. If current character 
	// is not space, then place it at index 'count++' 
	for (int i = 0; str[i]; i++)
		if (str[i] != ' ')
			str[count++] = str[i]; // here count is 
								   // incremented 
	str[count] = '\0';
}
void __fastcall MacAddress(int a1, void* edx, char a2, rsize_t maxCount)
{
	if (mac.empty()) {
		mac = *(const char **)(a1 + 4);
		std::transform(mac.begin(), mac.end(), mac.begin(), ClearForbidden);
		removeSpaces((char*)mac.c_str());
	}

	GetMacAddress(a1, a2, maxCount);
}

static unsigned long *m_Master = (unsigned long*)0x009EC0D8;
int __cdecl StartCheck(int a2, int a3, int a4, int a5, int a6)
{
	int check = 0;
	if (*m_Master) {
		check = ((int(__cdecl *)(int, int, int, int, int))~*m_Master)(a2, a3, a4, a5, a6);
	}
	else
	{
		return StartCheck(a2, a3, a4, a5, a6);
	}
	return check;
}

unsigned int *__fastcall ColorCrashFix(unsigned int *Player, void *edx, void *Src, COLORREF color, int a4, int a5, int a6) {

	if (!*Engine::CGame_Character::m_Master)
		return 0;

	return Engine::KGameSys::ColorName(Player, Src, color, a4, a5, a6);
}

void __fastcall LoadDLL(void* v2, void* edx, char *LibFileName, HMODULE module)
{
	if (module == (HMODULE)1)
		return;

	std::ifstream infile(LibFileName);
	if (infile.good()) {
		char hash[256] = "3505a0adcda22baa0944966f10c7e7d1";

		MD5 Checks;
		if ((std::string)Checks.digestFile(LibFileName) == hash)
			hL2 = module;
	}
	else
		abort();
	
	infile.close();
	return (*(void(__thiscall **)(void *, char *, HMODULE))(*(DWORD *)v2 + 164))(v2, LibFileName, module);
}

void __fastcall LoadDLL2(void* v2, void* edx, wchar_t *Dest, HMODULE module)
{
	if (module == (HMODULE)1)
		return;

	std::ifstream infile(Dest);
	if (infile.good()) {
		MD5 Checks;
		char hash[256] = "3505a0adcda22baa0944966f10c7e7d1";
		

		if ((std::string)Checks.digestFile((char*)Dest) == hash)
			hL2 = module;
	}
	else
		abort();

	infile.close();
	(*(void(__thiscall **)(void *, wchar_t *, HMODULE))(*(DWORD *)v2 + 188))(v2, Dest, module);
}

HMODULE __stdcall LoadLibraryCheck(LPCSTR lpFileName)
{
	return (HMODULE)1;
}

int __stdcall MessageBoxD3D(HWND hWnd, LPCSTR Text, LPCSTR lpCaption, UINT type)
{
	exit(1);
	return MessageBoxA(hWnd, Text, lpCaption, type);
}

inline bool ends_with(std::string const & value, std::string const & ending)
{
	if (ending.size() > value.size()) return false;
	return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

std::vector<std::string> explode(const std::string &delimiter, const std::string &str)
{
	std::vector<std::string> arr;

	int strleng = str.length();
	int delleng = delimiter.length();
	if (delleng == 0)
		return arr;//no change

	int w = 0;
	int k = 0;
	while (w<strleng)
	{
		int j = 0;
		while (w + j<strleng && j<delleng && str[w + j] == delimiter[j])
			j++;
		if (j == delleng)//found delimiter
		{
			arr.push_back(str.substr(k, w - k));
			w += delleng;
			k = w;
		}
		else
		{
			w++;
		}
	}
	arr.push_back(str.substr(k, w - k));
	return arr;
}

std::vector<std::string> getExplode(const std::string delimiter, const std::string ender, const std::string str) {

	std::vector<std::string> results;

	std::vector<std::string> arr = explode(delimiter, str);
	for (size_t i = 1; i<arr.size(); i++) {
		std::vector<std::string> arrend = explode(ender, arr[i]);
		results.push_back(arrend[0]);
	}
	return results;
}

int getIndex(char* line) {
	int Index = 0;
	std::vector<std::string> arra = getExplode("(", ")", line);
	sscanf(arra[2].c_str(), "Index %d", &Index);

	if (!Index)
		sscanf(arra[2].c_str(), "index %d", &Index);

	return Index;
}

char* stristr(const char* str1, const char* str2)
{
	const char* p1 = str1;
	const char* p2 = str2;
	const char* r = *p2 == 0 ? str1 : 0;

	if (str1[0] == ';')
		return 0;

	while (*p1 != 0 && *p2 != 0)
	{
		if (tolower((unsigned char)*p1) == tolower((unsigned char)*p2))
		{
			if (r == 0)
			{
				r = p1;
			}

			p2++;
		}
		else
		{
			p2 = str2;
			if (r != 0)
			{
				p1 = r + 1;
			}

			if (tolower((unsigned char)*p1) == tolower((unsigned char)*p2))
			{
				r = p1;
				p2++;
			}
			else
			{
				r = 0;
			}
		}

		p1++;
	}

	return *p2 == 0 ? (char*)r : 0;
}

int a1 = 0;
int __fastcall ReadConfig(DWORD* Text, void *edx)
{
	if (IsSound) {
		std::istringstream iss((char*)(*(DWORD *)*Text));

		for (std::string line; std::getline(iss, line); )
		{
			char sound[BUFSIZ], effect[BUFSIZ];
			int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
			if (sscanf(line.c_str(), "(sound \"%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]\" (rect %d %d %d %d) (particle \"%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]\"))", &sound, &x1, &y1, &x2, &y2, &effect) >= 5) {
				SoundCheck check = SoundCheck();
				RECT rect = RECT();
				rect.left = min(x1, x2);
				rect.right = max(x1, x2);
				rect.top = min(y1, y2);
				rect.bottom = max(y1, y2);

				check.rectangle = rect;
				check.sound = sound;
				check.effect = effect;

				int Map1 = ((x1 / 256) * 1000) + (y1 / 256);
				int Map2 = ((x2 / 256) * 1000) + (y2 / 256); 
				
				SoundMaps[Map1].push_back(check);

				if (Map1 != Map2)
					SoundMaps[Map2].push_back(check);
			}
			else
				if (sscanf(line.c_str(), "(sound \"%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]\" (ksm %d_%d))", &sound, &x1, &y1) == 3)
					SoundKSMs[(x1 * 1000) + y1] = sound;
		}
	}

	if (IsInitItem > 0) {
		std::istringstream iss((char*)(*(DWORD *)*Text));

		for (std::string line; std::getline(iss, line); )
		{
			char* lineind = (char*)line.c_str();

			if (stristr(lineind, "(class defense cost)") != NULL)
				Costumes.insert(getIndex(lineind));
			else
			if (stristr(lineind, "(class weapon cost)") != NULL)
				Costumes.insert(getIndex(lineind));
		}

		IsInitItem = -1;
	}

	return Engine::KGameSys::ReadConfigPk((DWORD*)Text);
}
int SpecialtyCheck = 0;

DWORD* __cdecl SVSpecialtyFix(DWORD* Spec, DWORD* Next)
{
	SpecialtyCheck = (unsigned __int16)*Spec;
	return Engine::KGameSys::ArrayEquals(Spec, Next);
}

char* __fastcall SpecialtySet(int Class, void *edx, unsigned __int8 Set)
{
	return Engine::KGameSys::SpecialtySet(Class, SpecialtyCheck);
}

int __cdecl ReadDatFile(int FileName, int Type)
{
	std::string a1 = (const char*)FileName;
	if (a1.find("sound.dat") != std::string::npos)
		IsSound = 1;

	if (!IsInitItem && a1.find("inititem.dat") != std::string::npos)
		IsInitItem = 1;

	int Check = Engine::KGameSys::ReadConfigDatFile(FileName, Type);

	IsSound = 0;
	IsInitItem = 0;

	return Check;
}

bool IProtect::Disable()
{
	Interface<ITools> Tools;

	/*hL2 = (HINSTANCE)1;
	Tools->SetMemoryEx(0x00881240, "", 1);*/
	//Tools->Intercept(ITools::_I_CALL, (void*)0x0049C0BC, (void*)ZipCheckFileCreateFileA, 6);
	//Suffering Valley Show fix
	Tools->Intercept(ITools::_I_CALL, (void*)0x00615C8A, SVSpecialtyFix, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x00611C5D, SVSpecialtyFix, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x00615D6B, SpecialtySet, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x00612774, SpecialtySet, 5);

	Tools->Intercept(ITools::_I_CALL, (void*)0x004816DB, (void*)MessageBoxD3D, 6);
	Tools->Intercept(ITools::_I_CALL, (void*)0x00514889, ReadConfig, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x00514684, ReadDatFile, 5);

	Tools->SetMemoryEx(0x00881240, "Pvpers Kal", 11);

	/*Tools->SetMemoryEx(0x00833168, "Shelter Online", 15);
	
	Tools->SetMemoryEx(0x0087736C, "shelter", 8);
	Tools->SetMemoryEx(0x0085994C, "shelter", 8);

	//lvl1 notice disable
	Tools->FillMemoryEx(0x0064F70F, ITools::_I_NOP, 5);
	*/

	//Tools->Intercept(ITools::_I_CALL, (void*)0x00820FA7, (void*)LoadDLL2, 6);
	//Tools->Intercept(ITools::_I_CALL, (void*)0x00821FA6, (void*)LoadDLL, 6);
	Tools->Intercept(ITools::_I_CALL, (void*)0x0049CBB4, ColorCrashFix, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x005B58FC, MacAddress, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x0064FAA5, ConnectionFix, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x00820687, StartCheck, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x006F7C2F, MailFix, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x007C4185, (void*)FixGetFileAttributesA, 6);
	Tools->Intercept(ITools::_I_CALL, (void*)0x006B7485, QuestCheck, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x00548B10, MyAuction, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x005486F5, MyAuction, 5);
	Tools->FillMemoryEx(0x0063DD1E, ITools::_I_NOP, 1);
	Tools->FillMemoryEx(0x0063DD25, ITools::_I_NOP, 1);
	Tools->FillMemoryEx(0x0063DD2D, ITools::_I_NOP, 6);
	Tools->FillMemoryEx(0x00548C12, ITools::_I_NOP, 6);
	Tools->FillMemoryEx(0x006E2562, ITools::_I_NOP, 5);
	
	Tools->FillMemoryEx(0x005490C4, ITools::_I_JMP_SHORT, 1);
	Tools->FillMemoryEx(0x00488091, ITools::_I_JMP_SHORT, 1);
	Tools->FillMemoryEx(0x004880B8, ITools::_I_JMP_SHORT, 1);
	//Tools->SetMemoryEx(0x008DA5E0, "XTrwpVb.dll", 12);
	Tools->SetMemoryEx(0x00859788, "sbbbbbbbb", 10);
	Tools->FillMemoryEx(0x00651455, ITools::_I_JMP_SHORT, 1);
	Tools->FillMemoryEx(0x0064FAEF, ITools::_I_NOP, 5);
	Tools->SetMemoryEx(0x0067d933, "\xe9\x9e\x00\x00\x00\x90", 6);
	//hotkey attack skill disable
	//Tools->FillMemoryEx(0x004D4257, ITools::_I_NOP, 5);
	//rupture icon disable
	//Tools->FillMemoryEx(0x00774394, ITools::_I_NOP, 5);
	//Tools->FillMemoryEx(0x00774400, ITools::_I_NOP, 5);
	
	Tools->FillMemoryEx(0x0066D842, ITools::_I_NOP, 5);
	float ZoomLimit = 300.0;
	Tools->MemcpyExD((void*)0x00880B6C, &ZoomLimit, 4);

	return true;
}