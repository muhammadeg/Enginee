#include <ctime>

static signed int(__cdecl *IsPlayerCheck)() = (signed int(__cdecl*)())0x006C8C20;
static signed int(__cdecl *IsPlayerAttack)() = (signed int(__cdecl*)())0x006C56C0;
static int(__thiscall *EndDashSkill)(int Player) = (int(__thiscall*)(int))0x00437460;
static void *(__thiscall *SetTip)(int pTarget, LPCTSTR pString, COLORREF color, int dwLife, int bShowName) = (void *(__thiscall*)(int, LPCTSTR, COLORREF, int, int))0x004339D0;
static int(__thiscall *PlayerTick)(int pTarget, unsigned int Value) = (int(__thiscall*)(int, unsigned int))0x0041F130;
static signed int(__cdecl *SkillButton)(int Value) = (signed int(__cdecl*)(int))0x0042DCF0;
LONG Delay = 0;

signed int __cdecl MySkillButton(int Value)
{
	if (Value == 93 && *(DWORD*)(*Engine::CGame_Character::m_Master + 20672) == 4)
	{
		Interface<IPackets> Packets;
		Packets->Send(117, "b", Value);
		return 0;
	}
	  
	if (Value == 95)
	{   
		Interface<IPackets> Packets;
		Packets->Send(117, "b", Value);
		return 0;
	}

	return SkillButton(Value);
}

signed int __cdecl MyIsPlayerCheck()
{
	
	if (*(DWORD*)(*Engine::CGame_Character::m_Master + 18328) & 256 || *(DWORD*)(*Engine::CGame_Character::m_Master + 18328) & 268435456)
		return 0;

	if (*(DWORD*)(*Engine::CGame_Character::m_Master + 18284) & 4194304)
		return 0;

	return IsPlayerCheck();
}

void UpdateSlots(signed int Amount) {
	Engine::KGameSys::SetInvSlots(Amount);

	int Window = Engine::KGameSys::WindowCheck("inventory");
	if (Window)
		Engine::KGameSys::UpdateInvSlots((void*)Window);
}

int IsPlayingSound = 0;
int __fastcall MyPlayerTick(int pTarget, void *edx, unsigned int Value)
{
	int Check = PlayerTick(pTarget, Value);
	
	if (*Engine::CGame_Character::m_Master) {
		int V1 = *(DWORD*)(*Engine::CGame_Character::m_Master + 18144) / 0x2000;
		int V2 = *(DWORD*)(*Engine::CGame_Character::m_Master + 18152) / 0x2000;
		if (V1 == 26 && V2 == 34) {
			if (!Engine::KGameSys::WindowCheck("deathmatchtournamentpopup") && !Engine::KGameSys::WindowCheck("deathmatchtournamentpopup_sub") && !Engine::KGameSys::WindowCheck("deathmatchtournament"))
				Engine::KGameSys::OpenWindow("deathmatchtournamentpopup", 0, 0, 0, 0, 0);
		}

		if (InvTime3 && InvTime3 <= (int)time(0)) {
			UpdateSlots(72);
			InvTime3 = 0;
		}
		if (InvTime2 && InvTime2 <= (int)time(0)) {
			UpdateSlots(36);
			InvTime2 = 0;
		}
		if (InvTime1 && InvTime1 <= (int)time(0)) {
			UpdateSlots(0);
			InvTime1 = 0;
		}

		bool found = false;

		auto itArea = SoundMaps.find((V1 * 1000) + V2);
		if (itArea != SoundMaps.end()) {
			POINT pt = POINT();
			pt.x = *(DWORD*)(*Engine::CGame_Character::m_Master + 18144) / 32;
			pt.y = *(DWORD*)(*Engine::CGame_Character::m_Master + 18152) / 32;

			std::vector<SoundCheck> Rects = itArea->second;
			for (auto x = Rects.begin(); x != Rects.end(); x++) {
				if (PtInRect(&x->rectangle, pt)) {
					found = true;
					int Sound = sha256(x->sound);
					if (IsPlayingSound != Sound) {
						IsPlayingSound = Sound; 
						Engine::KGameSys::PlaySoundK((char*)x->sound.c_str()); 
						if (!x->effect.empty())
							Engine::CFxEntityManager::AddFxToTarget(Engine::AddFx, x->effect.c_str(), *(DWORD *)(*Engine::CGame_Character::m_Master + 17476), 0, 0, 0, 0);
					}
					break;
				}
			}
		}

		if (!found) {
			auto itSounds = SoundKSMs.find((V1 * 1000) + V2);
			if (itSounds != SoundKSMs.end()) {
				std::string soundStr = itSounds->second;
				int Sound = sha256(soundStr);
				if (IsPlayingSound != Sound) {
					IsPlayingSound = Sound;
					Engine::KGameSys::PlaySoundK((char*)soundStr.c_str());
				}
			}
			else
				if (IsPlayingSound) {
					IsPlayingSound = 0;
					Engine::KGameSys::PlaySoundK("bgm003");
				}
		}
	}
	

	if (InterlockedExchangeAdd(&Delay, 0) <= (LONG)GetTickCount()) {
		InterlockedExchange(&Delay, GetTickCount() + 1000);
		buffTimer();
	}
	
	if (*(int*)((int)pTarget + 19580) == 1 && *(int*)((int)pTarget + 20672) == 0 && *(DWORD*)((int)pTarget + 19588))
	{
		if (GetTickCount() > (*(DWORD*)((int)pTarget + 19588) + 1500))
			EndDashSkill((int)pTarget);
	}

	if (*(DWORD*)(pTarget + 18272) & 262144)
	{
		if (*(DWORD *)(pTarget + 19848) == 0)
			SetTip(pTarget, *(const char**)((int)pTarget + 17608), RGB(0, 128, 255), 10000, false);
	}

	if (*(DWORD*)(pTarget + 18272) & 524288)
	{
		if (*(DWORD *)(pTarget + 19848) == 0)
			SetTip(pTarget, *(const char**)((int)pTarget + 17608), RGB(255, 0, 0), 10000, false);
	}

	return Check;
}

signed int __cdecl MyIsPlayerAttack()
{
	int Check = IsPlayerAttack();

	if (*(DWORD*)(*Engine::CGame_Character::m_Master + 18272) & 262144 || *(DWORD*)(*Engine::CGame_Character::m_Master + 18272) & 524288)
		Check = 1;

	return Check;
}

void *__fastcall MySetTip(int pTarget, void *edx, LPCTSTR pString, COLORREF color, int dwLife, int bShowName)
{
	if (*(DWORD*)(pTarget + 18272) & 262144)
		return SetTip(pTarget, pString, RGB(0, 128, 255), dwLife, bShowName);

	if (*(DWORD*)(pTarget + 18272) & 524288)
		return SetTip(pTarget, pString, RGB(255, 0, 0), dwLife, bShowName);

	return SetTip(pTarget, pString, color, dwLife, bShowName);
}