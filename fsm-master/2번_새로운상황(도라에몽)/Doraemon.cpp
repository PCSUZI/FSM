#include "Doraemon.h"

bool Doraemon::HandleMessage(const Telegram& msg)
{
  return m_pStateMachine->HandleMessage(msg);
}


void Doraemon::Update()
{
  //set text color to green
  SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
 
  m_pStateMachine->Update();
}