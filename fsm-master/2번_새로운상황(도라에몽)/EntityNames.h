#ifndef NAMES_H
#define NAMES_H

#include <string>

//ĳ����
enum 
{
  ent_JinGoo,

  ent_Dora,

  ent_TongTong,


};

//�̸� ����
inline std::string GetNameOfEntity(int n)
{
  switch(n)
  {
  case ent_JinGoo:

    return "������";

  case ent_Dora:
    
    return "���󿡸�"; 

  case ent_TongTong:
	 return "������";


  default:

    return "UNKNOWN!";
  }
}

#endif