#ifndef NAMES_H
#define NAMES_H

#include <string>

//ĳ����
enum 
{
  ent_Miner_Bob,

  ent_Elsa,

  ent_Dog,

  ent_Owner
};

//�̸� ����
inline std::string GetNameOfEntity(int n)
{
  switch(n)
  {
  case ent_Miner_Bob:

    return "Miner Bob";

  case ent_Elsa:
    
    return "Elsa"; 

  case ent_Dog:
	 return "Dog";

  case ent_Owner:
	  return "Owner Phone : ";

  default:

    return "UNKNOWN!";
  }
}

#endif