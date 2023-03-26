int __fastcall OnOk(void *Argument, void *edx)
{
	Interface<IPackets> Packets;

	if (*((DWORD *)Argument + 111) == 1000)
		Packets->Send(219, "dss", 1, Packets->RecCaller.c_str(), Packets->Recall.c_str());

	return Engine::KGameSys::OnOk(Argument);
}

int __fastcall OnCancel(void *Argument, void *edx)
{
	Interface<IPackets> Packets;

	if (*((DWORD *)Argument + 111) == 1000)
		Packets->Send(219,"dss",0,Packets->RecCaller.c_str(),Packets->Recall.c_str());

	return Engine::KGameSys::OnCancel(Argument);
}

int i = 0;
signed int __cdecl PressKey(int Word, void *edx)
{
	if ( Engine::KGameSys::PressedKey)
	{
		int ReCheck = Engine::KGameSys::Check();
		if ( ReCheck && ReCheck && (*(int (__thiscall **)(int))(*(DWORD *)ReCheck + 148))(ReCheck) )
		{
			return 0;
		}
		else {
			int MKey = PressableKey >> 19;
			if (MKey && (Word == MKey || Word == MKey - 32)) {
				if (*Engine::CGame_Character::m_Master) {
					PressableKey = 0;
					Interface<IPackets> Packets;
					for(int i=0;i<5;i++)
						Packets->Send(255, "dd", 6, numLock);
					return 1;
				}
			}

			if (Word == 118 || Word == 86)
			{
				if (*Engine::CGame_Character::m_Master) {
					VButton = 1;
					if (!Engine::KGameSys::WindowCheck("Honor"))
						Engine::KGameSys::OpenWindow("Honor", 0, 0, 0, 0, 0);
					else
						Engine::KGameSys::CloseWindow("Honor");
					VButton = 0;
				}
				return 1;
			}

			if (Word == 108 || Word == 76) // L Button
			{
				return 0;
			}

			if (Word == 101 || Word == 69) // E Button
			{
				return 0;
			}

			if (Word == 114 || Word == 82) // R Button
			{
				return 0;
			}
			if (Word == 66 || Word == 98)
			{
				Interface<IPackets> Packets;
				Packets->Send(255, "d", 5);
				/*
				Packets->Send(4, "d", 190);
				Packets->Send(190, "");
				*/
			}
			
			if (Word == 79 || Word == 111)
			{
				if (*Engine::CGame_Character::m_Master) {
					Interface<IPackets> Packets;
					return Packets->Send(255, "d", 7);
				}
			}
		}
	}

	return Engine::KGameSys::PressKey(Word);
}