#include "DogOwnStates.h"
#include "State.h"
#include "Dog.h"
#include "Locations.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "CrudeTimer.h"
#include "EntityNames.h"
#include "utils.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif


//------------------------------------------------------------------------methods for GoHomeAndSleepTilRested

HomeAndSleepTilRested* HomeAndSleepTilRested::Instance() //�� , �� ��Ŭ��
{
	static HomeAndSleepTilRested instance;

	return &instance;
}

void HomeAndSleepTilRested::Enter(Dog* dog) //�� ����
{

}

void HomeAndSleepTilRested::Execute(Dog* dog) //���� ��
{
	//���ǰ� �ϸ� ���
	if (!dog->Fatigued()) 
	{
		switch (RandInt(0, 2))
		{
		case 0:

			cout << "\n" << GetNameOfEntity(dog->ID()) << ": �� ������ ����� ";

			break;

		case 1:

			cout << "\n" << GetNameOfEntity(dog->ID()) << ": �տ�~~!!! ( �뷡�θ��� �� ) ";

			break;

		case 2:

			cout << "\n" << GetNameOfEntity(dog->ID()) << ": �޸��� ����� ";

			break;
		}

		dog->IncreaseFatigue(); //�ǰ��� ����
	}
	else if(dog->Thirsty())
	{
		dog->GetFSM()->ChangeState(QuenchHungry::Instance());
	}

	else
	{
		//sleep
		dog->DecreaseFatigue(); //�ܴ�. �ǰ��� ����

		cout << "\n" << GetNameOfEntity(dog->ID()) << ": " << ".. �۸� ...ZZZ";
	}
}

void HomeAndSleepTilRested::Exit(Dog* dog)
{

}


bool HomeAndSleepTilRested::OnMessage(Dog* dog, const Telegram& msg) //���� ������ �޴� �޼���
{
//	SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_PetReady: //��� �޽���

						//�޽��� ���� �ð� ��� 
		cout << "\nMessage handled by " << GetNameOfEntity(dog->ID())
			<< " at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(dog->ID())
			<< ": �۸� ! ( ������ ��Ḧ �̴ּ� ������ ����! ) ";

		dog->GetFSM()->ChangeState(Eat::Instance());

		return true;


	case Msg_HiHoneyImHome: //�ƺ��Դ�

					   //�޽��� ���� �ð� ��� 
	/*	cout << "\nMessage handled by " << GetNameOfEntity(dog->ID())
			<< " at time: " << Clock->GetCurrentTime();*/

		SetTextColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(dog->ID())
			<< ": �۸۸ظ۸۸�!!!!!!!!!!!!!!!! �۸۸ظ۸۸� ( �ƺ��� ���� �Դ� !!!!!!!! ) ���� ����!!!!!!!!!";

		dog->GetFSM()->ChangeState(HomeAndSleepTilRested::Instance());

		return true;

	}//end switch

	return false; //send message to global message handler
}

//------------------------------------------------------------------------QuenchThirst

QuenchHungry* QuenchHungry::Instance() //�񸶸�
{
	static QuenchHungry instance;

	return &instance;
}

void QuenchHungry::Enter(Dog* dog)
{
	if (dog->Thirsty())
	{
		dog->ChangeLocation(saloon); //��� �ٲ�

		cout << "\n" << GetNameOfEntity(dog->ID()) << ": " << " '�谡 ������ !! �������� �� �޶��ؾ߰ھ�' ";

		cout << "\n" << GetNameOfEntity(dog->ID()) << ": " << " �۸� !!! �۸۸۸� !! ( ���� �� ����Ŀ� ! )  ";

		//dog->ChangeLocation(shack);  // ��ġ ������ �ٲ� 

		//let the wife know I'm home �Ƴ����� �޽��� ����
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay ������ Ÿ�� 0 
			dog->ID(),        //ID of sender ���� ���̵�
			ent_Elsa,            //ID of recipient �Ƴ����� ����
			Msg_IamHungry,   //the message �޽��� ���� ����� 
			NO_ADDITIONAL_INFO);   //�߰����� ���� ���� 


	}
}

void QuenchHungry::Execute(Dog* dog)
{
	dog->GetFSM()->ChangeState(HomeAndSleepTilRested::Instance());
}


void QuenchHungry::Exit(Dog* dog)
{

}


bool QuenchHungry::OnMessage(Dog* dog, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}

//------------------------------------------------------------------------EatStew

Eat* Eat::Instance() //��Ʃ �Դ°�
{
	static Eat instance;

	return &instance;
}


void Eat::Enter(Dog* dog)
{
	cout << "\n" << GetNameOfEntity(dog->ID()) << ": " << "ůĲ ůĲ ! (���� �ñ� )  ";
}

void Eat::Execute(Dog* dog)
{

	cout << "\n" << GetNameOfEntity(dog->ID()) << ": " << "�ͱ� �ͱ� ~~~ ( ��Դ� �� )";
	dog->BuyAndDrinkAWhiskey(); //��� �����

	dog->GetFSM()->RevertToPreviousState(); //���� ���·� ���ư���
}

void Eat::Exit(Dog* dog)
{
	cout << "\n" << GetNameOfEntity(dog->ID()) << ": " << "�۸� !!!!!! ( �߸Ծ����ϴ�. ) ";
}


bool Eat::OnMessage(Dog* dog, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}


