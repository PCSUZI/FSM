#include "OwnerOwnedStates.h"
#include "MinerOwnedStates.h"
#include "Owner_call.h"
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

OwnerOwnedStates* OwnerOwnedStates::Instance()
{
	static OwnerOwnedStates instance;

	return &instance;
}


void OwnerOwnedStates::Execute(Owner_call* owner) //���� 
{


}

bool OwnerOwnedStates::OnMessage(Owner_call* owner, const Telegram& msg) //���� �޽��� �޴� ��
{
	//SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_IgoGold: //����� �� ��� �߽��ϴ�.
	{
		/* cout << "\nMessage handled by " << GetNameOfEntity(wife->ID()) << " at time: "
		<< Clock->GetCurrentTime();*/

		SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(owner->ID()) <<
			": �������� �������Դϴ�. ";

		owner->GetFSM()->ChangeState(Call_Bob::Instance()); //��ȭ���·� ��ȯ

		return true;
	}



	}//end switch

	return false;
}


Call_Bob* Call_Bob::Instance()
{
	static Call_Bob instance;

	return &instance;
}


void Call_Bob::Enter(Owner_call* owner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "\n" << GetNameOfEntity(owner->ID()) << ": ���� ��  - �ڳ��ΰ� ";
	owner->SetCalling(true);
	
}


void Call_Bob::Execute(Owner_call* owner)
{


	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);


	if (owner->Calling())
	{
		if ((RandFloat() < 0.5))
		{
			cout << "\n" << GetNameOfEntity(owner->ID()) << ": " << "  �� ��� �ݵ���� �İ� ~~!~!~!@#$#&*@^$*#  ( ���۸� ���۸� )  ";

			//dog->ChangeLocation(shack);  // ��ġ ������ �ٲ� 

			//let the wife know I'm home �信��
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay ������ Ÿ�� 0 
				owner->ID(),        //ID of sender ���� ���̵�
				ent_Miner_Bob,            //ID of recipient �信��
				Msg_Owner_Bad,   //the message �ܼҸ� �޽���
				NO_ADDITIONAL_INFO);   //�߰����� ���� ���� 
		}
		else
		{
			cout << "\n" << GetNameOfEntity(owner->ID()) << ": " << "  ���~~ �� �״�� ������ ��~~! ( ������ )  ";

			//dog->ChangeLocation(shack);  // ��ġ ������ �ٲ� 

			//let the wife know I'm home �信��
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay ������ Ÿ�� 0 
				owner->ID(),        //ID of sender ���� ���̵�
				ent_Miner_Bob,            //ID of recipient �信��
				Msg_Owner_Good,   //the message �ܼҸ� �޽���
				NO_ADDITIONAL_INFO);   //�߰����� ���� ���� 
		}

		owner->SetCalling(false);

	}



	owner->GetFSM()->RevertToPreviousState();
}

void Call_Bob::Exit(Owner_call* owner)
{
}

bool Call_Bob::OnMessage(Owner_call* owner, const Telegram& msg)
{
	return false;
}


//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm ���� ���� �Ÿ��� 

Free* Free::Instance()
{
	static Free instance;

	return &instance;
}


void Free::Enter(Owner_call* owner)
{


}


void Free::Execute(Owner_call* owner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "\n" << GetNameOfEntity(owner->ID()) << ": ���� - ���� - ��ĩ ��ĩ  ";
}

void Free::Exit(Owner_call* owner)
{
}

bool Free::OnMessage(Owner_call* owner, const Telegram& msg)
{
	return false;
}
