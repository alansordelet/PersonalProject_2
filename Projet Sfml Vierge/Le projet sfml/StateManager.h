#pragma once
#include"tools.h"

enum enumState
{
	INTRO,
	MENU,
	GAME,
	EDITOR,
	OPTION
};

class stateManager
{
public:
	stateManager();
	~stateManager();
	static void updateState();
	void changeState(enumState _state);
	enumState getState() { return state; }
	static enumState state;

protected:
	static float timerState;

};

