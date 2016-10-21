#include "GameState.h"
#include "Input.h"

int CGameState::State = 0;
int CGameState::OldState = 0;

CGameState::CGameState(void)
{
}


CGameState::~CGameState(void)
{
}

void CGameState::Update()
{
	State++;
	
	State %= STATE_MAX;
	
}