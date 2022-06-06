#include "Dog.h"

bool Dog::HandleMessage(const Telegram& msg) //메시지 받았니?
{
	return m_pStateMachine->HandleMessage(msg);
}


void Dog::Update() //개 업데이트
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN| FOREGROUND_INTENSITY);

	m_iThirst += 1; //배고픔 주기적으로 올라감

	m_pStateMachine->Update(); //강아지 상태 머신 업데이트 
}



bool Dog::Thirsty()const
{
	if (m_iThirst >= Thirst_MAX) { return true; }

	return false;
}

bool Dog::Fatigued()const
{
	if (m_iFatigue > Thire_MAX)
	{
		return true;
	}

	return false;
}
