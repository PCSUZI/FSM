#include "Dog.h"

bool Dog::HandleMessage(const Telegram& msg) //�޽��� �޾Ҵ�?
{
	return m_pStateMachine->HandleMessage(msg);
}


void Dog::Update() //�� ������Ʈ
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN| FOREGROUND_INTENSITY);

	m_iThirst += 1; //����� �ֱ������� �ö�

	m_pStateMachine->Update(); //������ ���� �ӽ� ������Ʈ 
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
