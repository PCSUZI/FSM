#include "Owner_call.h"

bool Owner_call::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void Owner_call::Update()
{
	//set text color to ³ë¶û
	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}