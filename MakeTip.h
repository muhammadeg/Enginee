int CheckArmorGrade = 0;

int __fastcall MyArmorGetGrade(int a, void *edx)
{
	int check = Engine::KGameSys::ArmorGrade(a);

	if (check)
		CheckArmorGrade = *(DWORD *)(check + 268);

	return check;
}

int __cdecl MyPetGetGrade(int a)
{
	int check = Engine::KGameSys::ArmorGrade(a);
	if (!check) {
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		printf("Index: %d\n", a);
	}

	while (!check)
		check = Engine::KGameSys::ArmorGrade(a);

	return check;
}

int __cdecl MyPetGetGrade2(int a)
{
	int check = Engine::KGameSys::PetGrading(a);
	if (!check) {
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		printf("Index: %d\n", a);
	}

	while (!check)
		check = Engine::KGameSys::PetGrading(a);

	return check;
}

int __cdecl BofStatFix(int a1, void *edx, const char *a2)
{
	if (CheckArmorGrade && CheckArmorGrade == 85)
		return Engine::KGameSys::AddMsg(a1, "#nStrength 7#nIntelligence 7#nAgility 7#n");

	else if (CheckArmorGrade && CheckArmorGrade == 95)
		return Engine::KGameSys::AddMsg(a1, "#nStrength 8#nIntelligence 8#nAgility 8#n");

	else
		return Engine::KGameSys::AddMsg(a1, "#n");
}
	
void BofFix()
{
	Interface<ITools> Tools;
	Tools->Intercept(ITools::_I_CALL, (void*)0x004CFB0C, MyArmorGetGrade, 5);
	Tools->Intercept(ITools::_I_CALL, (void*)0x004CFC1E, BofStatFix, 5);
}

void __fastcall MakeTip(void *a, void *edx, int a2, int a3, signed int a4, char a5, int a6, int a7)
{
	Engine::KGameSys::MakeTip(a, a2, a3, a4, a5, a6, a7);
}