#include "JinGoo.h"

bool JinGoo::HandleMessage(const Telegram& msg) //�޽��� �޾Ҵ�?
{
  return m_pStateMachine->HandleMessage(msg);
}


void JinGoo::Update() //���� ������Ʈ
{
  SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);

  
  m_pStateMachine->Update(); //���� ���� �ӽ� ������Ʈ 

}


bool JinGoo::StressOver()const
{
  if (m_stress > MaxStress)
  {
    return true;
  }

  return false;
}

bool JinGoo::BoringOver()const
{
	if (m_boaring > MaxBoring)
	{
		return true;
	}

	return false;
}