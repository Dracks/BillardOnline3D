//
//  MainMenu.h
//  BillardOnline3D
//
//  Created by Dracks on 28/09/12.
//
//

#ifndef __BillardOnline3D__MainMenu__
#define __BillardOnline3D__MainMenu__
namespace Menus{
	class MainMenu;
	class ClickListener;
}

#include <iostream>
#include "gameplay.h"
#include "MenuAbstract.h"
#include "BillardMainClass.h"

namespace Menus{
	class MainMenu: public Menus::MenuInterface{
	private:
		gameplay::Form* _form;
		gameplay::Node* _background;
		
		int _newMenu;
		
		//gameplay::Button* _singlePlayer;
		
	public:
		MainMenu(::BillardMainClass*);
		~MainMenu();
		virtual void update(float elapsedTime);
		void render(gameplay::Scene*);
		void disable();
		
		void singlePlayer(gameplay::Control::Listener::EventType evt);
	};
}


#endif /* defined(__BillardOnline3D__MainMenu__) */
