#include "TongOwnedStates.h"
#include "JinGooOwnedStates.h"
#include "Tong.h"
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

TongTongOwnedStates* TongTongOwnedStates::Instance()
{
	static TongTongOwnedStates instance;

	return &instance;
}


void TongTongOwnedStates::Execute(TongTong* tongtong) //���� 
{


}

bool TongTongOwnedStates::OnMessage(TongTong* tongtong, const Telegram& msg) //���� �޽��� �޴� ��
{
	//SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_IgoPlayGround: //������ ���Ϳ� �Դ�
	{
	
			SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

			cout << "\n" << GetNameOfEntity(tongtong->ID()) <<
				": ������ ������ �� ���� �ִ� ���ͷ� ��??? ";

			if (!tongtong->Harassing())
			{
				tongtong->GetFSM()->ChangeState(Harass_JinGoo::Instance()); //������ ����
				tongtong->SetHarassing(true);
			}

			return true;

	}


	}//end switch

	return false;
}


Harass_JinGoo* Harass_JinGoo::Instance()
{
	static Harass_JinGoo instance;

	return &instance;
}


void Harass_JinGoo::Enter(TongTong* tongtong)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	
}


void Harass_JinGoo::Execute(TongTong* tongtong)
{


	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	if (tongtong->Harassing())
	{
		cout << "\n" << GetNameOfEntity(tongtong->ID()) << ": " << "  �� ������ �� ���Ⱑ ����� ��??? �� - ��---- ���������ۤ�����������  ";


		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay ������ Ÿ�� 0 
			tongtong->ID(),        //ID of sender ���� ���̵�
			ent_JinGoo,            //ID of recipient �信��
			Msg_Tong_FuckYou,   //the message �ܼҸ� �޽���
			NO_ADDITIONAL_INFO);   //�߰����� ���� ���� 

	
	}


	tongtong->GetFSM()->ChangeState(Free::Instance());
}

void Harass_JinGoo::Exit(TongTong* tongtong)
{


}

bool Harass_JinGoo::OnMessage(TongTong* tongtong, const Telegram& msg)
{


	return false;
}


//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm ���� ���� �Ÿ��� 

Free* Free::Instance()
{
	static Free instance;

	return &instance;
}


void Free::Enter(TongTong* tongtong)
{


}


void Free::Execute(TongTong* tongtong)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	switch (RandInt(0, 2))
	{
	case 0:

		cout << "\n" << GetNameOfEntity(tongtong->ID()) << ": ( ���Ϳ��� ) ���¾� ������~~ ��� �����̶�� ~~~ ";

		break;

	case 1:

		cout << "\n" << GetNameOfEntity(tongtong->ID()) << ": ( ���Ϳ��� ) ����~~~! ����� �� �޾ƶ�~~~. ";

		break;

	case 2:

		cout << "\n" << GetNameOfEntity(tongtong->ID()) << ": ( ���Ϳ��� ) ��~~~ �ɽ��� ������ �������� �ʹ�~ ";

		break;
	}
}

void Free::Exit(TongTong* tongtong)
{
}

bool Free::OnMessage(TongTong* tongtong, const Telegram& msg)
{
	//SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_jinGoo_revenge:
	{

		SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);


		if (tongtong->Harassing())
		{

			cout << "\n" << GetNameOfEntity(tongtong->ID()) <<
				": ���ƾƾƾ� --- ������ �̻��� ������ �� �������� ������ ���� !!!!!!!!!!!!! ";

			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay ������ Ÿ�� 0 
				tongtong->ID(),        //ID of sender ���� ���̵�
				ent_JinGoo,            //ID of recipient �信��
				Msg_Tong_OhhNo,   //the message �ܼҸ� �޽���
				NO_ADDITIONAL_INFO);   //�߰����� ���� ���� 


			tongtong->SetHarassing(false);
			tongtong->GetFSM()->RevertToPreviousState();
		}

		return true;

	}


	}//end switch

	return false;
	return false;
}
