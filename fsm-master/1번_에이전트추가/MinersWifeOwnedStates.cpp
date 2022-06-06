#include "MinersWifeOwnedStates.h"
#include "MinerOwnedStates.h"
#include "MinersWife.h"
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

WifesGlobalState* WifesGlobalState::Instance()
{
  static WifesGlobalState instance;

  return &instance;
}


void WifesGlobalState::Execute(MinersWife* wife) //���� 
{
  //1 in 10 chance of needing the bathroom (provided she is not already
  //in the bathroom)
  if ( (RandFloat() < 0.1) &&  ////ȭ��� �� Ȯ��
       !wife->GetFSM()->isInState(*VisitBathroom::Instance()) ) //ȭ��� ���°� �ƴϸ�
  {
    wife->GetFSM()->ChangeState(VisitBathroom::Instance()); //ȭ��Ƿ� ����! 
  }
}

bool WifesGlobalState::OnMessage(MinersWife* wife, const Telegram& msg) //���� �޽��� �޴� ��
{
  //SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

  switch(msg.Msg)
  {
  case Msg_HiHoneyImHome: //���� ���� �޽��� ( ���� �� �Ծ� ! )
   {
      /* cout << "\nMessage handled by " << GetNameOfEntity(wife->ID()) << " at time: " 
       << Clock->GetCurrentTime();*/

     SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);

     cout << "\n" << GetNameOfEntity(wife->ID()) << 
          ": ��Ϳ�~ ���ִ� ��Ʃ�� ����� �ٲ��� ^^ ";

     wife->GetFSM()->ChangeState(CookStew::Instance()); //�丮���·� ��ȯ

	 return true;
   }

  case Msg_IamHungry: //�������� ���� �޽��� ����� 
  {
	  /*cout << "\nMessage handled by " << GetNameOfEntity(wife->ID()) << " at time: "
		  << Clock->GetCurrentTime();
*/
	    SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);

	  cout << "\n" << GetNameOfEntity(wife->ID()) <<
		  ": �츮 ������~~~ �谡 �����ٱ� ~~?~~? ";

	  wife->GetFSM()->ChangeState(CookPet::Instance()); //�丮���·� ��ȯ

	  return true;
  }

  return true;
 


  }//end switch

  return false;
}

//-------------------------------------------------------------------------DoHouseWork ������

DoHouseWork* DoHouseWork::Instance()
{
  static DoHouseWork instance;

  return &instance;
}


void DoHouseWork::Enter(MinersWife* wife)
{
  cout << "\n" << GetNameOfEntity(wife->ID()) << ": �������� �� �� �ð��̱�!";
}


void DoHouseWork::Execute(MinersWife* wife)
{
  switch(RandInt(0,2))
  {
  case 0:

    cout << "\n" << GetNameOfEntity(wife->ID()) << ": �ٴ��� ���� - ";

    break;

  case 1:

    cout << "\n" << GetNameOfEntity(wife->ID()) << ": �������� �Ѵ� - ";

    break;

  case 2:

    cout << "\n" << GetNameOfEntity(wife->ID()) << ": ħ�븦 �����Ѵ� - ";

    break;
  }
}

void DoHouseWork::Exit(MinersWife* wife)
{
}

bool DoHouseWork::OnMessage(MinersWife* wife, const Telegram& msg)
{
  return false;
}

//------------------------------------------------------------------------VisitBathroom ȭ���

VisitBathroom* VisitBathroom::Instance()
{
  static VisitBathroom instance;

  return &instance;
}


void VisitBathroom::Enter(MinersWife* wife)
{  
  cout << "\n" << GetNameOfEntity(wife->ID()) << ": ������ �ɾ��. ������ �Һ��� ���߰ڱ���. "; 
}


void VisitBathroom::Execute(MinersWife* wife)
{
  cout << "\n" << GetNameOfEntity(wife->ID()) << ": �ƾ� ~ ! �ÿ��ϴ�!";

  wife->GetFSM()->RevertToPreviousState();
}

void VisitBathroom::Exit(MinersWife* wife)
{
  cout << "\n" << GetNameOfEntity(wife->ID()) << ":ȭ��ǿ��� ���´�.";
}


bool VisitBathroom::OnMessage(MinersWife* wife, const Telegram& msg)
{
  return false;
}


//------------------------------------------------------------------------CookStew �丮

CookStew* CookStew::Instance()
{
  static CookStew instance;

  return &instance;
}


void CookStew::Enter(MinersWife* wife)
{
  //if not already cooking put the stew in the oven
  if (!wife->Cooking()) //�丮���� �ƴ϶��
  {
    cout << "\n" << GetNameOfEntity(wife->ID()) << ": ��Ʃ�� ���쿡 �ִ´�. ";
  
    //send a delayed message myself so that I know when to take the stew
    //out of the oven
    Dispatch->DispatchMessage(1.5,                  //time delay ��� �ð�
                              wife->ID(),           //sender ID �ڽ���
                              wife->ID(),           //receiver ID  �ڽ�����
                              Msg_StewReady,        //msg ��Ʃ �� �ƴ�
                              NO_ADDITIONAL_INFO); 

    wife->SetCooking(true); //�丮�� true
  }
}


void CookStew::Execute(MinersWife* wife)
{
  cout << "\n" << GetNameOfEntity(wife->ID()) << ": ������� ���� ���� �ȴ޺����Ѵ�.";
}

void CookStew::Exit(MinersWife* wife)
{
  SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
  
  cout << "\n" << GetNameOfEntity(wife->ID()) << ": ��Ź ���� ���� �÷� ���´�.";
}


bool CookStew::OnMessage(MinersWife* wife, const Telegram& msg)
{
 // SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

  switch(msg.Msg)
  {
    case Msg_StewReady:
    {
     /* cout << "\nMessage received by " << GetNameOfEntity(wife->ID()) <<
           " at time: " << Clock->GetCurrentTime();*/

      SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
      cout << "\n" << GetNameOfEntity(wife->ID()) << ": ���� �غ�Ʊ���! ��ô�.";

      //let hubby know the stew is ready
      Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
                                wife->ID(), //��������
                                ent_Miner_Bob, //������
                                Msg_StewReady, //�� �� �ƾ�~~
                                NO_ADDITIONAL_INFO);

      wife->SetCooking(false); //�丮 ����

      wife->GetFSM()->ChangeState(DoHouseWork::Instance());               
    }

    return true;

  }//end switch

  return false;
}



//---------------------------------------------------------- ������ ��� �ֱ� 
CookPet* CookPet::Instance()
{
	static CookPet instance;

	return &instance;
}


void CookPet::Enter(MinersWife* wife)
{
	//if not already cooking put the stew in the oven
	if (!wife->Dog_Cooking()) //�丮���� �ƴ϶��
	{
		cout << "\n" << GetNameOfEntity(wife->ID()) << ": ��Ḧ ã�´� . ";

		//send a delayed message myself so that I know when to take the stew
		//out of the oven
		Dispatch->DispatchMessage(1.0,                  //time delay ��� �ð�
			wife->ID(),           //sender ID �ڽ���
			wife->ID(),           //receiver ID  �ڽ�����
			Msg_StewReady,        //msg ��Ʃ �� �ƴ�
			NO_ADDITIONAL_INFO);

		wife->Dog_SetCooking(true); //�丮�� true
	}
}


void CookPet::Execute(MinersWife* wife)
{
	cout << "\n" << GetNameOfEntity(wife->ID()) << ": ��� �״��� ...........";
}

void CookPet::Exit(MinersWife* wife)
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "\n" << GetNameOfEntity(wife->ID()) << ": �۸۾�~~~~~  ( ���������� ��Ḧ �ش�.) ";
}


bool CookPet::OnMessage(MinersWife* wife, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_StewReady:
	{
		/*cout << "\nMessage received by " << GetNameOfEntity(wife->ID()) <<
			" at time: " << Clock->GetCurrentTime();*/

		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(wife->ID()) << ": ���ְ� ������~~.";

		//let hubby know the stew is ready
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
			wife->ID(), //��������
			ent_Dog, //������
			Msg_PetReady, //�� �� �ƾ�~~
			NO_ADDITIONAL_INFO);

		wife->Dog_SetCooking(false); //�丮 ����

		wife->GetFSM()->ChangeState(DoHouseWork::Instance());
	}

	return true;

	}//end switch

	return false;
}