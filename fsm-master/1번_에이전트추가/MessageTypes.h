#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_IamHungry,
  Msg_PetReady,
  Msg_IgoGold, //���� �ݱ� �Դٰ� ������� ����
  Msg_Owner_Bad, //��簡 �ܼҸ� ����
  Msg_Owner_Good //��簡 �ܼҸ���
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case Msg_HiHoneyImHome:
    
    return "HiHoneyImHome"; 

  case Msg_StewReady:
    
    return "StewReady";

  case Msg_IamHungry:

	  return "IamHungry";

  case Msg_PetReady:
	  return "PetReady";

  case Msg_IgoGold:
	  return "IgoGold";

  case Msg_Owner_Bad:
	  return "Owner_Bad";

  case Msg_Owner_Good:
	  return "Owner_Good";

  default:

    return "Not recognized!";
  }
}

#endif