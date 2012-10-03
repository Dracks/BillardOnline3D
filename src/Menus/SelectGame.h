//
//  SelectGame.h
//  BillardOnline3D
//
//  Created by Dracks on 29/09/12.
//
//

#ifndef __BillardOnline3D__SelectGame__
#define __BillardOnline3D__SelectGame__

namespace Menus{
	class SelectGame;
}

#include <iostream>
#include "MenuAbstract.h"

namespace Menus{
	class SelectGame: public MenuInterface{
	private:
		gameplay::Form* _form;
	public:
		SelectGame(::BillardMainClass*);
		~SelectGame();
		
		void render(gameplay::Scene*);
		void update(float timeElapsed);
		
		void back(gameplay::Control::Listener::EventType);
		
		void disable();
		
		void createGame(gameplay::Control::Listener::EventType);
	};
}

#endif /* defined(__BillardOnline3D__SelectGame__) */
