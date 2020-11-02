#pragma once
#include "UI.h"
#include "DelayManager.h"
class EscMenuUI : public UI
{
private:
	bool isOpen = false;
	int currentSelectPosition = 1;

	DelayManager delay;
public:
	EscMenuUI();
	void ClearEscSelectMenu();
	void ClearAllMenu();
	const int OpenEscMenu();
	const int SelectEscMenu();
};

enum ESCMenu
{
	NOTHING = 20,
	EXIT_ESC_MENU
};