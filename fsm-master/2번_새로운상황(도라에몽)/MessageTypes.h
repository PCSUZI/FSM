#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_IgoPlayGround, //������ ���Ͱ�
  Msg_Dora_I_helpMe, //���󿡸� ������ �Ф� 
  Msg_jinGoo_revenge, //���� �����Ϸ� ����.
  Msg_Tong_OhhNo, //������ ����
  Msg_Tong_FuckYou, //�����̰� ���� ������
  Msg_Dora_GiveItem //���󿡸��� ���� ��
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case Msg_IgoPlayGround:
    
    return "Msg_IgoPlayGround"; 

  case Msg_Dora_I_helpMe:
    
    return "Msg_Dora_I_helpMe";

  case Msg_jinGoo_revenge:
	  return "Msg_jinGoo_revenge";

  case Msg_Tong_OhhNo:
	  return "Msg_Tong_OhhNo";

  case Msg_Tong_FuckYou:
	  return "Msg_Tong_FuckYou";

  case Msg_Dora_GiveItem:
	  return "Msg_Dora_GiveItem";

  default:

    return "Not recognized!";
  }
}

#endif