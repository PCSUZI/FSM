#include "Tong.h"

bool TongTong::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void TongTong::Update()
{
	//set text color to ³ë¶û
	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}