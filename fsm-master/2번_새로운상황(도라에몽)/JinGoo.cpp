#include "JinGoo.h"

bool JinGoo::HandleMessage(const Telegram& msg) //메시지 받았니?
{
  return m_pStateMachine->HandleMessage(msg);
}


void JinGoo::Update() //진구 업데이트
{
  SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);

  
  m_pStateMachine->Update(); //진구 상태 머신 업데이트 

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