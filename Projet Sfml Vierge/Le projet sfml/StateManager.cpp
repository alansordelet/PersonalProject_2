#include "stateManager.h"

enumState stateManager::state;
float stateManager::timerState = 0;
stateManager::stateManager()
{

}

stateManager::~stateManager()
{

}

void stateManager::updateState()
{
	timerState += tools::GetTimeDelta();

}

void stateManager::changeState(enumState _state)
{
	state = _state;
}