#include "DoraemonOwnedStates.h"
#include "JinGooOwnedStates.h"
#include "Doraemon.h"
#include "Locations.h"
#include "CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//-----------------------------------------------------------------------Global state

DoraemonGlobalState* DoraemonGlobalState::Instance()
{
  static DoraemonGlobalState instance;

  return &instance;
}


void DoraemonGlobalState::Execute(Doraemon* dora) //���� 
{

  if ( (RandFloat() < 0.1) &&  ////���󿡸� ȭ��� �� Ȯ��
       !dora->GetFSM()->isInState(*VisitBathroom::Instance()) ) //ȭ��� ���°� �ƴϸ�
  {
    dora->GetFSM()->ChangeState(VisitBathroom::Instance()); //ȭ��Ƿ� ����! 
  }
}

bool DoraemonGlobalState::OnMessage(Doraemon* dora, const Telegram& msg) //���� �޽��� �޴� ��
{
  //SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

  switch(msg.Msg)
  {
  case Msg_Dora_I_helpMe: //���󿡸� ������!!
   {
      /* cout << "\nMessage handled by " << GetNameOfEntity(dora->ID()) << " at time: " 
       << Clock->GetCurrentTime();*/

     SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);

     cout << "\n" << GetNameOfEntity(dora->ID()) << 
          ": �� �����̰� ��������?! ��ٷ� ������ ������ ã�ƺ��� ";

     dora->GetFSM()->ChangeState(GiveItem::Instance()); //�ָӴ� ����

	 return true;
   }
 

  }//end switch

  return false;
}

//-------------------------------------------------------------------------DoHouse ���󿡸��� ������ ����

DoHouse* DoHouse::Instance()
{
  static DoHouse instance;

  return &instance;
}


void DoHouse::Enter(Doraemon* dora)
{
  cout << "\n" << GetNameOfEntity(dora->ID()) << ": ������ �ð��̱� !";
}


void DoHouse::Execute(Doraemon* dora)
{
  switch(RandInt(0,2))
  {
  case 0:

    cout << "\n" << GetNameOfEntity(dora->ID()) << ": �ϻ��� �Դ´�. ";

    break;

  case 1:

    cout << "\n" << GetNameOfEntity(dora->ID()) << ": ��ȭå�� ����. ";

    break;

  case 2:

    cout << "\n" << GetNameOfEntity(dora->ID()) << ": ����� ���. ";

    break;
  }
}

void DoHouse::Exit(Doraemon* dora)
{
}

bool DoHouse::OnMessage(Doraemon* dora, const Telegram& msg)
{
  return false;
}

//------------------------------------------------------------------------VisitBathroom ȭ���

VisitBathroom* VisitBathroom::Instance()
{
  static VisitBathroom instance;

  return &instance;
}


void VisitBathroom::Enter(Doraemon* dora)
{  
  cout << "\n" << GetNameOfEntity(dora->ID()) << ": ��.. ��� �־����� ȭ�����... "; 
}


void VisitBathroom::Execute(Doraemon* dora)
{
  cout << "\n" << GetNameOfEntity(dora->ID()) << ": �ƾ� ~ ! �ÿ��ϴ�!";

  dora->GetFSM()->RevertToPreviousState();
}

void VisitBathroom::Exit(Doraemon* dora)
{
  cout << "\n" << GetNameOfEntity(dora->ID()) << ":ȭ��ǿ��� ���´�.";
}


bool VisitBathroom::OnMessage(Doraemon* dora, const Telegram& msg)
{
  return false;
}


//------------------------------------------------------------------------GiveItem �丮

GiveItem* GiveItem::Instance()
{
  static GiveItem instance;

  return &instance;
}


void GiveItem::Enter(Doraemon* dora)
{
  //if not already cooking put the stew in the oven
  if (!dora->Cooking()) //�丮���� �ƴ϶��
  {
    cout << "\n" << GetNameOfEntity(dora->ID()) << ": �ָӴϿ� ���� �ִ´� . ";
  
    //send a delayed message myself so that I know when to take the stew
    //out of the oven
    Dispatch->DispatchMessage(1.5,                  //time delay ��� �ð�
                              dora->ID(),           //sender ID �ڽ���
                              dora->ID(),           //receiver ID  �ڽ�����
                              Msg_Dora_GiveItem,        //msg ���� ã�Ҵ�.
                              NO_ADDITIONAL_INFO); 

    dora->SetCooking(true); // ���� ã���� 
  }
}


void GiveItem::Execute(Doraemon* dora)
{
  cout << "\n" << GetNameOfEntity(dora->ID()) << ":���� ������ ... �̰͵� �ƴϰ� �̰͵� �ƴϰ� .... ( ���� ���� )";
}

void GiveItem::Exit(Doraemon* dora)
{
  SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
  
}


bool GiveItem::OnMessage(Doraemon* dora, const Telegram& msg)
{
 // SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

  switch(msg.Msg)
  {
    case Msg_Dora_GiveItem:
    {
     /* cout << "\nMessage received by " << GetNameOfEntity(dora->ID()) <<
           " at time: " << Clock->GetCurrentTime();*/

      SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
      cout << "\n" << GetNameOfEntity(dora->ID()) << ": �� �̰ɷ� ! �����̸� ȥ���ְ� ��!! ";

      //let hubby know the stew is ready
      Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
                                dora->ID(), //���󿡸���
                                ent_JinGoo, //��������
		                        Msg_Dora_GiveItem, //���� ��
                                NO_ADDITIONAL_INFO);

      dora->SetCooking(false); //�İ� ������ ����

      dora->GetFSM()->ChangeState(DoHouse::Instance());               
    }

    return true;

  }//end switch

  return false;
}

