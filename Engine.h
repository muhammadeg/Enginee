#ifndef __ENGINE_H
#define __ENGINE_H

#include <Windows.h>
int __cdecl ReadDatFile(int FileName, int Type);
namespace Engine
{
	static int numLock = 0;

	struct Packet
	{
		unsigned short Size;
		unsigned char Type;
		char Data[8000];
	};

	namespace CEditor
	{
		static int(__cdecl *Click)(int _this) = (int(__cdecl*)(int))0x006CE6E0;
		static int(__stdcall *GetCursorPos)(LPPOINT lpPoint) = (int(__stdcall*)(LPPOINT))0x00831478;
		static int (__cdecl *AddPKPWD)() = (int (__cdecl*)())0x008173C0;
		static int (__cdecl *PWDPK)(int a1, signed int a2, signed int a3, signed int a4, const char *a5) = (int (__cdecl*)(int, signed int, signed int, signed int,const char*))0x007E4E30;
		static void (__thiscall *Clear)(void* _this) = (void (__thiscall*)(void*))0x00749470;
		static void(__thiscall *Load)(void* _this, const char* Text) = (void(__thiscall*)(void*, const char*))0x0074A560;
	}

	namespace KGameSys
	{
		static int(__thiscall *CreateItem)(int Item, int Packet) = (int(__thiscall*)(int,int))0x00544770;
		static void(__thiscall *MapReadFile)(int Object) = (void(__thiscall*)(int))0x0053A170;
		static void(__thiscall *MapLoader)(int Object, int Item, int a3) = (void(__thiscall*)(int,int,int))0x00534A50;
		static int(__thiscall *FileReader)(int Item, LPCSTR lpFileName) = (int(__thiscall*)(int, LPCSTR))0x0049C0A0;
		static int(__cdecl *CanAttack)() = (int(__cdecl*)())0x006C56C0;
		static int(__thiscall *UpdateItemEffect)(int Player, int a2, __int16 a3, int a4, __int16 a5, unsigned __int8 a6) = (int(__thiscall*)(int Player, int a2, __int16 a3, int a4, __int16 a5, unsigned __int8 a6))0x00467070;
		static void(__thiscall *SetAncientItemEffect)(int Item, int Type) = (void(__thiscall*)(int, int))0x0047CEE0;
		static int(__thiscall *CreateAncientEffect)(int Effect) = (int(__thiscall*)(int))0x0047CCC0;
		static int(__thiscall *WearAncientEffect)(int Effect, int a2, float a3, float a4, float a5) = (int(__thiscall*)(int Effect, int a2, float a3, float a4, float a5))0x0047D120;
		static int(__thiscall *UnWearAncientEffect)(int Effect) = (int(__thiscall*)(int Effect))0x0047CDB0;
		static int(__thiscall *SetNPCBuff)(int Player) = (int(__thiscall*)(int))0x00454790;
		static void(__thiscall *SetTriangularTime)(int window, unsigned __int8 Type) = (void(__thiscall*)(int, unsigned __int8))0x0058BD10;
		static void(__thiscall *SetFishTime)(int window, unsigned __int8 Type) = (void(__thiscall*)(int, unsigned __int8))0x005EF310;
		static int(__cdecl *ShowNames)(int YesNo) = (int(__cdecl*)(int))0x006EAAB0;
		static int(__fastcall *UpdatePlayerName)(int Player, int Type) = (int(__fastcall*)(int, int))0x00437EA0;
		static void(__thiscall *SetCharName)(int Player, BYTE *a2, COLORREF a3, int a4, int a5) = (void(__thiscall*)(int Player, BYTE *a2, COLORREF a3, int a4, int a5))0x00467690;
		static void(__thiscall *ClearOldName)(int window) = (void(__thiscall*)(int))0x0049EB50;
		static int(__cdecl *SetNameWithGuildTag)(BYTE *Src, int a2, COLORREF color, int a3, int a4) = (int(__cdecl*)(BYTE *Src, int a2, COLORREF color, int a3, int a4))0x0049CBD0;
		static int(__cdecl *SetName)(BYTE *Src, COLORREF color, int a3) = (int(__cdecl*)(BYTE *Src, COLORREF color, int a3))0x0049CAE0;
		static int(__cdecl *GetItem)(int Index) = (int(__cdecl*)(int))0x00696390;
		static int(__cdecl *Skillbar)(int _this) = (int(__cdecl*)(int))0x006CF560;
		static int(__thiscall *PressKeyState)(void *_this, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) = (int(__thiscall*)(void *_this, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam))0x007CB010;
		static void(__thiscall *ModelChange)(void *a, int a1, signed int a2, char a4) = (void(__thiscall*)(void*, int, signed int, char))0x0045F6C0;
		static void(__thiscall *LoadLogo)(int window) = (void(__thiscall*)(int))0x007868A0;
		static void *(__thiscall *SkillCheck)(DWORD *a) = (void *(__thiscall*)(DWORD*))0x005A0430;
		static int(__cdecl *SkillPress)(unsigned __int8 Type, unsigned __int8 Index) = (int(__cdecl*)(unsigned __int8, unsigned __int8))0x0042E2D0;
		static int(__cdecl *IndexItem)(unsigned __int8 Type, int Index) = (int(__cdecl*)(unsigned __int8, int))0x004D50A0;
		static void(__cdecl *NoticeMsg)(char* Msg, int Color) = (void(__cdecl*)(char*, int))0x006CA8F0;
		static int(__cdecl *SkillShow)(void* Pack) = (int(__cdecl*)(void*))0x0069B8E0;
		static char *(__cdecl *__RTDynamicCast)(int a1, int a2, void *a3, void *a4, int a5) = (char*(__cdecl*)(int a1, int a2, void *a3, void *a4, int a5))0x007E612E;
		static char *(__cdecl *RTDynamicCast)(int a1, int a2, struct _s_RTTICompleteObjectLocator *a3, struct TypeDescriptor *a4, int a5) = (char*(__cdecl*)(int a1, int a2, struct _s_RTTICompleteObjectLocator *a3, struct TypeDescriptor *a4, int a5))0x007E612E;
		static int(__cdecl *Blabla)(int ID) = (int(__cdecl*)(int))0x00696450;
		static char (__cdecl *Blabla2)(char ID) = (char (__cdecl*)(char))0x005EF830;
		static int(__cdecl *RidingEnable)(int ID, int Type) = (int(__cdecl*)(int, int))0x0067AE30;
		static int (__cdecl *RidingDisable)(int ID, int Type) = (int (__cdecl*)(int,int))0x0067AFA0;
		static int (__cdecl *ShowPet)(int Value, int Argument, char Packet) = (int (__cdecl*)(int,int,char))0x0066B2C0;
		static int (__cdecl *AddMsg)(int a1, const char *a2) = (int (__cdecl*)(int,const char*))0x004079E0;
		static int(__cdecl *ArmorGrade)(int a1) = (int(__cdecl*)(int))0x004D5910;
		static int(__cdecl *PetGrading)(int a1) = (int(__cdecl*)(int))0x004B1710;
		static void *(__thiscall *ItemMsg)(void *a, const char *a1) = (void *(__thiscall*)(void*,const char*))0x00403900;
		static int (__cdecl *RebirthTalisman)(int Argument, int Value, char Data) = (int (__cdecl*)(int,int,char))0x00661E70;
		static int (__cdecl *Scenario3_3)(unsigned int Value, int Data) = (int (__cdecl*)(unsigned int,int))0x006D7900;
		static int(__thiscall *LatestScreenMsg)(void *Argument, const char *a2) = (int(__thiscall*)(void*, const char*))0x0061E8A0;
		static int(__thiscall *FishEdit)(DWORD *Argument, int a2) = (int(__thiscall*)(DWORD*, int))0x005EF7B0;
		static int (__thiscall *HellTime)(int Argument, int Value) = (int (__thiscall*)(int,int))0x00656E60;
		static char(__cdecl *SetHellTime)(int Time, char Value) = (char(__cdecl*)(int, char))0x00689D60;
		static float*(__cdecl *SetProductionBar)(char a1, char a2, void* Src) = (float*(__cdecl*)(char a1, char a2, void* Src))0x006D4A30;
		static DWORD(__thiscall *RefreshHellTime)(int Window) = (DWORD(__thiscall*)(int))0x00689D20;
		static unsigned int *(__thiscall *ColorName)(unsigned int *Player, void *Src, COLORREF color, int a4, int a5, int a6) = (unsigned int *(__thiscall*)(unsigned int *Player, void *Src, COLORREF color, int a4, int a5, int a6))0x0049CD20;
		static char (__thiscall *ScreenOverlay)(int a, int a2, int a3, int a4, char a5) = (char (__thiscall*)(int,int,int,int,char))0x00443F20;
		static int (__cdecl *MBox)(int pText, int nType, int nAction, int nDest, int nDest2) = (int (__cdecl*)(int, int, int, int, int))0x006C3280;
		static int (__thiscall *OnCancel)(void *Argument) = (int (__thiscall*)(void*))0x005BEF30;
		static int (__thiscall *OnOk)(void *Argument) = (int (__thiscall*)(void*))0x005BF500; 
		static int(__thiscall *OnFish)(int Window) = (int(__thiscall*)(int))0x005EDF20;
		static unsigned long *m_pChattingControl = (unsigned long*)0x009C961C;
		static void (__cdecl *SetScreenInfo)(char Type, void *msg, char value) = (void (__cdecl*)(char, void*, char))0x006D4D40;
		static void (__cdecl *AddChattingMessage)(char Type, const char* Message, int Color) = (void (__cdecl*)(char, const char*, int))0x006CC890;
		static void (__cdecl *AddInfoMessage)(const char* Message, int Color, int type) = (void (__cdecl*)(const char*, int, int))0x006CC8C0;
		static int (__cdecl *OpenWindow)(const char *name, int Argument, int Value, int Type, int nForce, int x) = (int (__cdecl*)(const char*,int,int,int,int,int))0x006C0310;
		static int (__cdecl *OtherOpenWindow)(const char *name, int Argument, int Value, int Type, int nForce) = (int (__cdecl*)(const char*,int,int,int,int))0x006C2DF0;
		static int(__cdecl *DismissWindow)(int Window) = (int(__cdecl*)(int))0x006C2E40;
		static int (__cdecl *CloseWindow)(char *name) = (int (__cdecl*)(char*))0x006C2A50;
		static int (__cdecl *WindowCheck)(const char *name) = (int (__cdecl*)(const char*))0x006C2B50; 
		static signed __int64(__thiscall *GetBuffTime)(DWORD* Buff) = (signed __int64(__thiscall*)(DWORD*))0x004C5050;
		static int (__thiscall *SetBuff)(void *a, int a2, int a3, signed __int64 a4, char a5, int a6, int a7, int a8, int a9, signed int a10, int a11) = (int (__thiscall*)(void*,int,int,signed __int64,char,int,int,int,int,signed int,int))0x0076DB00;
		static int (__thiscall *SetIcon)(void *a, int Key, int Time, int a4, int nMsg) = (int (__thiscall*)(void*,int,int,int,int))0x007792C0;
		static int (__thiscall *RemoveIcon)(void *a, int Key, int nMsg) = (int (__thiscall*)(void*,int,int))0x00779040;
		static int (__cdecl *CallBuff)(int a1, int a2, signed __int64 a3, char a4, int a5, int a6, int a7, int a8, int a9) = (int (__cdecl*)(int,int,signed __int64,char,int,int,int,int,int))0x006CA580;
		static int(__thiscall *ShowBuffIcon)(int a) = (int(__thiscall*)(int))0x0042D380;
		static int(__thiscall *WalkCheck)(int Place) = (int(__thiscall*)(int))0x0052FDB0;
		static int(__thiscall *MapOverlay)(DWORD* Place, int Map) = (int(__thiscall*)(DWORD*,int))0x005322C0;
		static int (__thiscall *MakeTip)(void *a, int a2, int a3, signed int a4, char a5, int a6, int a7) = (int (__thiscall*)(void*,int,int,signed int,char,int,int))0x004C50D0;
		static int (__cdecl *FindItemFromIID)(int a2) = (int (__cdecl*)(int))0x00696150;
		static int (__cdecl *FindItemFromIIDEx)(int a2) = (int (__cdecl*)(int))0x00696210;
		static signed int (__cdecl *PressKey)(int a1) = (signed int (__cdecl*)(int))0x006CBF50;
		static int PressedKey = (int)0x009C96A0;
		static char zipCheck[512] = "UXzq_s#^s-P#f87a-W4pQJyStVD8FPudU+Bzvbpn&amp;9kfZSZMK6&amp;8BQTf5PtE7H4#m^NtVLg?XdjKyQH_nLN$6d+dq=L7c7qJUYFA@WKQhgfRvhw2Jc$qV@q?aE5n859vt7URX=Q^cW!5wzdRzdS&amp;%A#AXDGYLcw=GTZ7BJM@P9ehQ2^s%pFC7#!b-tu=cW#s9nnNBfwANM4-C9WVYdvb@6NcxG2wMFBtdm!$eNXM*z?r%@TX485^yrVE7yaw?7rm";
		static void(__cdecl *PlaySoundK)(char* Sound) = (void(__cdecl*)(char*))0x00520DC0;
		static int(__cdecl *Check)() = (int(__cdecl*)())0x00747CE0;
		static signed int(__cdecl *ReadSound)(int a1) = (signed int(__cdecl*)(int))0x00520290;
		static char*(__thiscall *UpdateHonorType)(void* Player, int Type) = (char*(__thiscall*)(void*, int))0x00438320;
		static int (__thiscall *CheckForDss)(int Item) = (int (__thiscall*)(int))0x00593D50;
		static signed int(__thiscall *ReadDat)(const char* DatFile) = (signed int(__thiscall*)(const char*))0x005145C0;
		static signed int(__thiscall *ReadConfigPk)(DWORD* Text) = (signed int(__thiscall*)(DWORD*))0x00518E50;
		static signed int(__cdecl *ReadConfigDatFile)(int FileName, int Type) = (signed int(__cdecl*)(int, int))0x005147B0;
		static int(__thiscall *ItemName)(int Item, char Type) = (int(__thiscall*)(int, char))0x004BF800;
		static int (__thiscall *CheckDssType)(void *Item, int Packet) = (int (__thiscall*)(void*,int))0x00594510;
		static int (__thiscall *DssConfirmButton)(void *Item, const char *Word, int Value) = (int (__thiscall*)(void*,const char*,int))0x005949B0;
		static int (__cdecl *KMsgGet)(int SysMsgIndex) = (int (__cdecl*)(int))0x004B2480;
		static int (__thiscall *SetChangedText)(int Item, int TextName, int NewMsg) = (int (__thiscall*)(int,int,int))0x0075F720;
		static int (__thiscall *SetDssWindow)(void *Window, int Packet) = (int (__thiscall*)(void*,int))0x00594B40;
		static int (__thiscall *SetQigoong)(int Window, int Packet) = (int (__thiscall*)(int,int))0x00595740;
		static void(__cdecl *DemonGongStone)(int Value, int Argument, int Packet) = (void(__cdecl*)(int, int, int))0x0066DA10;
		static void(__cdecl *RefreshAppearance)() = (void(__cdecl*)())0x004BEED0;
		static int (__thiscall *SetDemonGongWindow)(void *Window, int Packet) = (int (__thiscall*)(void*,int))0x005BA730;
		static void (__thiscall *SendIdle)(int Object) = (void (__thiscall*)(int))0x0041E400;
		static int(__cdecl *WriteInItem)(int a1, int a2, char a3) = (int(__cdecl*)(int, int, char))0x004B2900;
		static void(__cdecl *Pocket)(int a1, int a2, char a3) = (void(__cdecl*)(int, int, char))0x0067B1F0;
		static void(__cdecl *SpawnNPC)(int a1, int a2, char a3) = (void(__cdecl*)(int, int, char))0x00668080;
		static void(__cdecl *Auction)(int a1, int a2, char a3) = (void(__cdecl*)(int, int, char))0x00662590;
		static void(__cdecl *NamePad)(int a1, int a2, char a3) = (void(__cdecl*)(int, int, char))0x00677B20;
		static void(__cdecl *NamePad2)(int a1, int a2, char a3) = (void(__cdecl*)(int, int, char))0x00677D20;
		static int(__thiscall *NamePadChoice)(int Type, char a2) = (int(__thiscall*)(int, char))0x007579A0;
		static void(__cdecl *Rental)(int a1, int a2, char a3) = (void(__cdecl*)(int, int, char))0x00678050;
		static void(__thiscall *RefreshTrainingWindow)(int a1,int a2) = (void(__thiscall*)(int, int))0x0062C410;
		static int(__thiscall *RenewRental)(int Window, int IID) = (int(__thiscall*)(int, int))0x0060A2E0;
		static void(__cdecl *Sasiety)(int a1, int a2, char a3) = (void(__cdecl*)(int, int, char))0x0066D590;
		static void(__cdecl *SasietyUpdate)(int a1, int a2, char a3) = (void(__cdecl*)(int, int, char))0x0066D860;
		static int(__thiscall *UpdateRent)(int Item) = (int(__thiscall*)(int))0x0060A980;
		static int(__thiscall *RefreshSatiety)(int Type, int a2, DWORD *a3) = (int(__thiscall*)(int, int, DWORD *))0x0055F160;
		static void*(__thiscall *AuctionAdd)(void* Type, void* Packet) = (void*(__thiscall*)(void*, void*))0x00543960;
		static char*(__cdecl *HonorName)(int Type) = (char*(__cdecl*)(int))0x004B2480;
		static int(__thiscall *IconWindow)(int Type, int a2) = (int(__thiscall*)(int, int))0x00693180;
		static int(__thiscall *AuctionEnable2)(int Type, int a2) = (int(__thiscall*)(int, int))0x00757900;
		static int(__thiscall *AuctionSetWindow)(int Type, int a2) = (int(__thiscall*)(int, int))0x005468B0;
		static DWORD *(__cdecl *SummonedNPC)(int a1, int a2, char a3) = (DWORD *(__cdecl*)(int, int, char))0x00666C80;
		static void(__cdecl *MasterEnchant)(int a1, int a2, char a3) = (void(__cdecl*)(int, int, char))0x0066DC80;
		static void(__cdecl *SendCreate)(int a1, int a2, char a3) = (void(__cdecl*)(int, int, char))0x0066B5B0;
		static void(__cdecl *PetBuff)(int a1, int a2, char a3) = (void(__cdecl*)(int, int, char))0x00677E90;
		static DWORD*(__cdecl *ArrayEquals)(DWORD *a1, DWORD* a2) = (DWORD*(__cdecl*)(DWORD* a1, DWORD* a2))0x0061BCC0;
		static char*(__thiscall *SpecialtySet)(int a1, unsigned __int8 a2) = (char*(__thiscall*)(int, unsigned __int8))0x004DC310;
		static void(__cdecl *TriangularBattle)(int a1, int a2, char a3) = (void(__cdecl*)(int, int, char))0x006656F0;
		static void(__cdecl *TriangularBattle2)(int a1, int a2, char a3) = (void(__cdecl*)(int, int, char))0x00662D50;
		static void(__cdecl *SufferingValley)(int a1, int a2, char a3) = (void(__cdecl*)(int, int, char))0x0065D190;
		static void(__cdecl *OnDamage)(int a1, int a2, int a3, int a4, int a5, char a6, char a7, int a8, int a9) = (void(__cdecl*)(int, int, int, int, int, char, char, int, int))0x006CFCE0;
		static void(__thiscall *DamageBox)(int Box, int a2, unsigned int a3, char *a4) = (void(__thiscall*)(int, int, unsigned int, char*))0x00404860;
		static int(__thiscall *Login)(void* Log) = (int(__thiscall*)(void*))0x005B5960;
		static void*(__cdecl *FList)(void* Packet) = (void*(__cdecl*)(void*))0x006F6DB0;
		static int(__thiscall *DuelTournament)(void* Window, void* Packet) = (int(__thiscall*)(void*, void*))0x00571FD0; 
		static void(__cdecl *Enchant)(int a1, int a2, char a3) = (void(__cdecl*)(int, int, char))0x0066FE40;
		static signed int(__cdecl *SetInvSlots)(signed int Amount) = (signed int(__cdecl*)(signed int))0x0069D210;
		static int(__thiscall *UpdateInvSlots)(void* Window) = (int(__thiscall*)(void*))0x00591380;
	}

	namespace XTrap
	{
		static signed int(__thiscall *Load)(void* Window, int Packet) = (int(__thiscall*)(void*, int))0x00820ED0;
		static signed int(__thiscall *LoadOther)(void* Window, int Packet) = (int(__thiscall*)(void*, int))0x00821ED0;
		static void*(__cdecl *CompleteLoad)() = (void*(__cdecl*)())0x00823980;
		static int(__cdecl* XTrapLaunch)(int a1, int a2, BYTE* a3) = (int(__cdecl*)(int a1, int a2, BYTE * a3))0x00822090;
		static int(__thiscall *LoadNextDLL)(DWORD *Window, int a2) = (int(__thiscall*)(DWORD *, int))0x00823A20;

		static HMODULE *hModule = (HMODULE*)0x009EBFEC;
		static DWORD *Code = (DWORD*)0x009EC018;
	}

	namespace CSkill
	{
		static int(__cdecl *Execute)(unsigned __int8 a1, unsigned __int8 a2) = (int(__cdecl*)(unsigned __int8 a1, unsigned __int8 a2))0x0042E2D0;
		static int(__cdecl *Reset)(int a1) = (int(__cdecl*)(int))0x0042DCF0;
		static int(__cdecl *Clear)() = (int(__cdecl*)())0x0042DDB0;
	}

	namespace KWindowCollector
	{
		static void (__cdecl *ProcessDestroy)() = (void (__cdecl*)())0x006C2E60;
	}

	namespace CD3DApplication
	{
		static HRESULT (__thiscall *Render3DEnvironment)(void* _this) = (HRESULT (__thiscall*)(void*))0x00480810;
	}

	namespace KCommand
	{
		static int *m_bShowFrame = (int*)0x009CB5A4;
		static int *m_bHideUI = (int*)0x009CB5AC;
		static int *m_bHideMe = (int*)0x009CB5B0;
		static int *m_bHideTerrain = (int*)0x009CB5B4;
		static int *m_bHideModel = (int*)0x009CB5B8;
		static int *m_bHideFog = (int*)0x009CB5BC;
		static int *m_fFogEnd = (int*)0x009CB5D0;
		static int *m_bHideWater = (int*)0x009CB5D8;
		static bool (__cdecl *ProcessCommand)(const char* Text) = (bool (__cdecl*)(const char*))0x006E4620;
	}
	
	namespace KSunLight
	{
		static unsigned long *m_dwTime = (unsigned long*)0x008B2C68;
	}
	
	namespace KSocket
	{
		static int *g_lpClient = (int*)0x009B5C58;
		static int (__thiscall *SendPacket)(void* _this, const char* Buffer, int Length) = (int (__thiscall*)(void*, const char*, int))0x00659FC0;
		static int(__cdecl *OnRecv)(Packet *Data) = (int(__cdecl*)(Packet*))0x0063DCF0;
		static int(__thiscall *Disconnect)(void *Data) = (int(__thiscall*)(void*))0x00659DC0;
		static void*(__thiscall *Destroy)(void *Data) = (void*(__thiscall*)(void*))0x00659CA0;
		static float *m_fWriteTime = (float*)0x009B5C60;
		static __int16 *items = (__int16*)0x009C8240;

		static int *TrainingTime = (int*)0x009C9704;
		static int(__cdecl *PacketReader)(int Type, const char *Text, ...) = (int(__cdecl*)(int, const char*, ...))0x00488BA0;
		static void*(__stdcall *PacketParser)(void * a1, int a2) = (void*(__stdcall*)(void*, int))0x00488880;
		static void*(__stdcall *PacketParser2)(void * a1, int a2) = (void*(__stdcall*)(void*, int))0x00488600;
		static char*(__cdecl *PacketParser3)(int a1, void * a2, int a3) = (char*(__cdecl*)(int, void*, int))0x0065DA00;
	}

	namespace CGame_Character
	{

		static __int64 *PlayerEXP = (__int64*)0x009C96A8;

		static int(__thiscall *FindPlayer)(int Player) = (int(__thiscall*)(int))0x004ED920;
		static int(__thiscall *Iterate)(int Player) = (int(__thiscall*)(int))0x00797D40;
		static unsigned long *m_Master = (unsigned long*)0x008E05E4;
		static unsigned long (__cdecl *FindCharacter)(unsigned int nID, int) = (unsigned long (__cdecl*)(unsigned int, int))0x00428430;
		static char(__cdecl *X)(char nID, int) = (char(__cdecl*)(char, int))0x006D3890;
		static char(__cdecl *Y)(int) = (char(__cdecl*)(int))0x005267A0;
		static int(__cdecl *InsertChar)(DWORD* ID, int Type) = (int(__cdecl*)(DWORD *a1,int))0x0042A690;

		static int(__thiscall *FreeCharMemory)(int Player) = (int(__thiscall*)(int))0x00436CE0;

		static int(__thiscall *DeleteChar)(int ID, int) = (int(__thiscall*)(int ID, int))0x007BE990;
		static int(__thiscall *CleanChar)(DWORD* ID) = (int(__thiscall*)(DWORD* ID))0x007C1590;
		static DWORD*(__fastcall *InitCharacter)(int Character, unsigned int type) = (DWORD*(__fastcall*)(int Character, unsigned int type))0x006D23A0;
		static int(__thiscall *Refresh)() = (int(__thiscall*)())0x0066BA50;
		static int(__thiscall *Refresh2)() = (int(__thiscall*)())0x0069A600;
		static int(__thiscall *Wipe2)(int Player) = (int(__thiscall*)(int))0x00436D40;
		static int(__thiscall *Wipe3)(int Player, __int64 Value) = (int(__thiscall*)(int, __int64))0x00436E60;
		static int(__thiscall *Wipe4)(int Player, signed int Value) = (int(__thiscall*)(int, signed int))0x00436F60;
		static int(__thiscall *Wipe5)(int Player) = (int(__thiscall*)(int))0x00467010;
		static int(__thiscall *Wipe6)(DWORD* Player) = (int(__thiscall*)(DWORD*))0x00468600;
		static int(__cdecl *Wipe7)(int ID, int) = (int(__cdecl*)(int ID, int))0x00428E00;
		static int(__cdecl *CleanAll)() = (int(__cdecl*)())0x00433780;
		static int(__cdecl *WipeAll)() = (int(__cdecl*)())0x0082F2A0;

	}
	
	namespace KBattle_UI
	{
		static void (__thiscall *DrawOnCharacter)(void *_this, unsigned char Type, int Number, int CharacterID) = (void (__thiscall*)(void*, unsigned char, int, int))0x007850B0;
	}
	
	namespace CGameMonster
	{
		static signed int (__thiscall *OnChangeGState)(int a) = (signed int (__thiscall*)(int))0x004518A0;
		static char (__thiscall *ModelSkill)(int a, char a2, int a3, unsigned __int8 a4, unsigned __int16 a5, unsigned __int16 a6, char a7, char a8) = (char (__thiscall*)(int, char, int, unsigned __int8, unsigned __int16, unsigned __int16, char, char))0x004511C0;
	}
	
	namespace CFxEntityManager
	{
		static signed int(__thiscall *AddFxToBoneRaw)(void *a1, char *a2, int a3, int a4, char a5, int a6, char a7, int a8, char a9, char a10, int a11, int a12, int a13, int a14, int a15, int a16, int a17, int a18, int a19, int a20, int a21, int a22, int a23, int a24, int a25, char a26, float a27, int a28, char a29) = (signed int(__thiscall*)(void *a1, char *a2, int a3, int a4, char a5, int a6, char a7, int a8, char a9, char a10, int a11, int a12, int a13, int a14, int a15, int a16, int a17, int a18, int a19, int a20, int a21, int a22, int a23, int a24, int a25, char a26, float a27, int a28, char a29))0x007BD870;
		static signed int(__thiscall *AddFxToBone)(void *player, int targetID, const char* name) = (signed int(__thiscall*)(void*, int, const char*))0x00779F20;
		static void(__stdcall *RemoveBoneFx)(int ID, char* Type) = (void(__stdcall*)(int,char*))0x00779FF0;
		static signed int(__thiscall *AddFxToTarget)(void *player, const char* name, int targetID, char autoRemove, char continued, signed int nForced, int nTargetType) = (signed int(__thiscall*)(void*, const char*, int, char, char, signed int, int))0x007C0E50;
		static void(__thiscall *RemoveFx)(void *player, int Fx, int Type) = (void(__thiscall*)(void*, int, int))0x007C1190;
	}

	namespace CharacterBar
	{
		static DWORD *CharBarCurrent = (DWORD*)0x009C9600;
		static DWORD *CharBarSize = (DWORD*)0x009C9768;
		static int(__thiscall *UpdateBar)(void* CharBar, char* Name, int Level) = (int(__thiscall*)(void*, char*, int))0x007624D0;
	}
	namespace Honor
	{
		static int *Range = (int*)0x009C97CC;
		static int *PrevRange = (int*)0x009C97D8;
		static int *Point = (int*)0x009C97C4;
		static int *Kill = (int*)0x009C97DC;
		static int *Die = (int*)0x009C97E0;
		static int *DKPWin = (int*)0x009C97E8;
		static int *DKPFull = (int*)0x009C97E4;
		static int *PLWin = (int*)0x009C97F0;
		static int *PLFull = (int*)0x009C97EC;
		static int *SVWin = (int*)0x009C97F8;
		static int *SVFull = (int*)0x009C97F4;
		static int *Reward = (int*)0x009C97C8;
	}

	static float *g_fCurrentTime = (float*)0x009EA140;
	static int *DuelMatch = (int*)0x009B5C7C;
	static int *CheckType = (int*)0x009C94CA;
	static int *MailTime = (int*)0x009CB284;

	static DWORD *Name = (DWORD*)0x009C821C;
	static BYTE *Face = (BYTE*)0x009C948F;
	static BYTE *Hair = (BYTE*)0x009C9496;
	static BYTE *Level = (BYTE*)0x009C948E;
	static DWORD *ID = (DWORD*)0x008AF200;
	static DWORD *CharName = (DWORD*)0x009C9754;
	static DWORD *Settings = (DWORD*)0x008CE220;
	static DWORD *Click = (DWORD*)0x009C9674;
	static DWORD *Target = (DWORD*)0x008CE1FC;
	static DWORD *NameShow = (DWORD*)0x009CC6BC;
	static DWORD *FishingTime = (DWORD*)0x009C9504;
	static void *IDs = (void*)0x008E0614;
	static DWORD *IDsEnd = (DWORD*)0x008E0618;
	static DWORD *OS = (DWORD*)0x009B37A8;
	static DWORD *MAPFolder = (DWORD*)0x009B3794;

	static void *AddFx = (void*)0x009E8AA8;
	static int *NameColor = (int*)0x0080FFFD;
	static void *BoneFx = (void*)0x009C9630;
}

#endif