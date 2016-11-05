#include "GameState.h"
#include "Input.h"

int CGameState::m_nState = 0;
int CGameState::m_nOldState = 0;

CGameState::CGameState(void)
{
}


CGameState::~CGameState(void)
{
}

void CGameState::StateUpdate(int State)
{
	m_nState = State;
	
}