#include "JinGooOwnedStates.h"
#include "State.h"
#include "JinGoo.h"
#include "Locations.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif


//------------------------------------------------------------------------methods for EnterPlayGround
EnterPlayGround* EnterPlayGround::Instance()
{
  static EnterPlayGround instance;

  return &instance;
}


void EnterPlayGround::Enter(JinGoo* pJinGoo)
{
  if (pJinGoo->Location() != PlayGround) //���Ͱ� �ƴ϶��
  {
    cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": " << "���Ϳ� �Դ�.";


	if (!pJinGoo->m_revenge) 
	{
		//���������� �޽��� ���� 
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay ������ Ÿ�� 0 
			pJinGoo->ID(),
			ent_TongTong,
			Msg_IgoPlayGround,   //the message �޽��� 
			NO_ADDITIONAL_INFO);   //�߰����� ���� ���� 
	}

	pJinGoo->DecreaseBoring(); //������ �ʱ�ȭ
    pJinGoo->ChangeLocation(PlayGround); //���ͷ�
  }
}


void EnterPlayGround::Execute(JinGoo* pJinGoo)
{  

	if (pJinGoo->m_revenge) //����
	{
	 cout << "\n" << GetNameOfEntity(pJinGoo->ID())
	  << " ��!!!!!!! ������ !!!!!!!!!!!!!!!! ( ���󿡸� ���� �� )  ";

	 Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay ������ Ÿ�� 0 
	  pJinGoo->ID(),
	  ent_TongTong,
	  Msg_jinGoo_revenge,   //������ ����
	  NO_ADDITIONAL_INFO);   //�߰����� ���� ���� 

	}

	else if (!pJinGoo->m_revenge) //�������� �ƴҶ�
	{
	 cout << "\n" << GetNameOfEntity(pJinGoo->ID())
	  << " ���Ϳ��� �� ��~  "; 
	 pJinGoo->GetFSM()->ChangeState(GoJinGooHouse::Instance());
	}

 
}


void EnterPlayGround::Exit(JinGoo* pJinGoo)
{
 
	if (pJinGoo->m_revenge) //���ϰ� ���� ��
	{
		cout << "\n" << GetNameOfEntity(pJinGoo->ID())
			<< ": �ΰ�� .. ���� �����Ҳ��� ...  ";
	}

	else if (!pJinGoo->m_revenge) //�����ϰ� ���� ��
	{
		cout << "\n" << GetNameOfEntity(pJinGoo->ID())
			<< ": ��� ���� ������ ����!  ";
	}
}


bool EnterPlayGround::OnMessage(JinGoo* pJinGoo, const Telegram& msg)
{

	switch (msg.Msg)
	{
	case Msg_Tong_FuckYou: //���������� ������

						//�޽��� ���� �ð� ��� 
	/*	cout << "\nMessage handled by " << GetNameOfEntity(pJinGoo->ID())
			<< " at time: " << Clock->GetCurrentTime();*/
		if (!pJinGoo->m_revenge)
		{
			SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

			cout << "\n" << GetNameOfEntity(pJinGoo->ID())
				<< ": ���ƾƾƾƾ� ~~~~~~~~~~~~~~~~~~~~~ �ФФФФ� �����̰� ������ �ФФФФФФФФФФФФФФФФФ� ( ��Ʈ���� ���� + 1 ) ";

			pJinGoo->IncreaseFatigue();

			pJinGoo->m_revenge = true; //���� ����
			pJinGoo->GetFSM()->ChangeState(GoJinGooHouse::Instance());

		}
		return true;

	case Msg_Tong_OhhNo: //�����̰� �����

						//�޽��� ���� �ð� ��� 
						/*	cout << "\nMessage handled by " << GetNameOfEntity(pJinGoo->ID())
						<< " at time: " << Clock->GetCurrentTime();*/

		if (pJinGoo->m_revenge)
		{
			SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

			cout << "\n" << GetNameOfEntity(pJinGoo->ID())
				<< ": ���������� ������ �����ߴ� !!!!!!!!!!!!!!!!!!! ���� ���󿡸� ~~! ";

			pJinGoo->m_revenge = false;
			pJinGoo->GetFSM()->ChangeState(GoJinGooHouse::Instance());
		}

		return true;

	}//end switch
  //send msg to global message handler
  return false;
}



//------------------------------------------------------------------------

GoJinGooHouse* GoJinGooHouse::Instance() //�� , �� ��Ŭ��
{
  static GoJinGooHouse instance;

  return &instance;
}

void GoJinGooHouse::Enter(JinGoo* pJinGoo) //�� ����
{
  if (pJinGoo->Location() != JinGooHouse) //������ ��ġ�� ���� �ƴϸ� ����
  {

	  if (pJinGoo->m_revenge)
	  {
		  SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

		  cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": " << "���󿡸� �� �� ������ �ФФФФФФФ� �����̰� ������ �ФФФФФФФФФФ� �����ϰ� ����  ";

	
		  Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay ������ Ÿ�� 0 
			  pJinGoo->ID(),        //ID of sender 
			  ent_Dora,            //ID of recipient
			  Msg_Dora_I_helpMe,   //the message �޽��� ���󿡸� �� ������
			  NO_ADDITIONAL_INFO);   //�߰����� ���� ���� 
	  }
	  else
	  {
		  cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": " << " ���� �����ߴ� ! ";
	  }




	  pJinGoo->ChangeLocation(JinGooHouse);  // ��ġ ������ �ٲ� 
  }
}

void GoJinGooHouse::Execute(JinGoo* pJinGoo) //���� ��
{ 

	if (pJinGoo->m_revenge ==false) //������ ���� ���°� �ƴҶ�
	{

		if (pJinGoo->BoringOver()) // �����ϸ� ���ͷ� ����
		{
			cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": "
				<< "���� �ʹ� �߱� �ŷȴ��� �ɽ��ϱ�! ���Ϳ� ����߰ڴ� ";

			pJinGoo->GetFSM()->ChangeState(EnterPlayGround::Instance()); //���ͷ�
		}
		else
		{

			pJinGoo->IncreaseBoring(); //���ܿ� ����

			switch (RandInt(0, 2))
			{
			case 0:

				cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": ��ȭå ���鼭 �߱� �߱�~~ ";

				break;

			case 1:

				cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": ���ӱ� ������ ����� ~~~~ ";

				break;

			case 2:

				cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": ����~~~~~~ ���ϰ� ������ ���� ~~~ ";

				break;
			}
		}
	}
	else if (pJinGoo->m_revenge)
	{
		cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": "
			<< "������ �������� ���󿡸� ���� ��ٸ����� .. ";
	}
}

void GoJinGooHouse::Exit(JinGoo* pJinGoo) 
{ 

}


bool GoJinGooHouse::OnMessage(JinGoo* pJinGoo, const Telegram& msg) //���� ������ �޴� �޼���
{

   switch(msg.Msg)
   {
   case Msg_Dora_GiveItem: //���󿡸��� ���� ��

	   //�޽��� ���� �ð� ��� 
    /* cout << "\nMessage handled by " << GetNameOfEntity(pJinGoo->ID()) 
     << " at time: " << Clock->GetCurrentTime();*/

     SetTextColor(FOREGROUND_RED|FOREGROUND_INTENSITY);

     cout << "\n" << GetNameOfEntity(pJinGoo->ID()) 
          << ": ���� ���󿡸� !! ���� �����̾� �����Ϸ� ���ھ�. ";

     pJinGoo->GetFSM()->ChangeState(EnterPlayGround::Instance());
      
     return true;

   }//end switch

   return false; //send message to global message handler
}
