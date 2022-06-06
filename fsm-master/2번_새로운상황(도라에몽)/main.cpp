#include <fstream>
#include <time.h>
#include <Windows.h>

#include "Locations.h"
#include "JinGoo.h"
#include "Doraemon.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "ConsoleUtils.h"
#include "EntityNames.h"
#include "Tong.h"


std::ofstream os;

int main()
{
//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
  os.open("output.txt");
#endif

  //seed random number generator
  srand((unsigned) time(NULL));

  //create a JinGoo
  JinGoo* jingoo = new JinGoo(ent_JinGoo);

  //create his dora
  Doraemon* dora = new Doraemon(ent_Dora);

  TongTong *tongtong = new TongTong(ent_TongTong);


  //register them with the entity manager
  EntityMgr->RegisterEntity(jingoo);
  EntityMgr->RegisterEntity(dora);
  EntityMgr->RegisterEntity(tongtong);

  //run jingoo and dora through a few Update calls
  for (int i=0; i<30; ++i)
  { 
    jingoo->Update();
    dora->Update();
	tongtong->Update();

    //dispatch any delayed messages
    Dispatch->DispatchDelayedMessages();

    Sleep(1500);
  }

  //tidy up
  delete jingoo;
  delete dora;
  delete tongtong;

  //wait for a keypress before exiting
  PressAnyKeyToContinue();


  return 0;
}






