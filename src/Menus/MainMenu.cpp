//
//  MainMenu.cpp
//  BillardOnline3D
//
//  Created by Dracks on 28/09/12.
//
//

#include "MainMenu.h"
#include "SelectGame.h"
#include "MultiPlayerLogin.h"

using namespace gameplay;

//class MainMenu{
namespace Menus {
	MainMenu::MainMenu(::BillardMainClass* main): Menus::MenuInterface(main){
		// Create a font for drawing the framerate.
		//Font* _font = Font::create("res/arial18.gpb");
		//std::cout << main << std::endl;
		_form=NULL;
		
		/*_form = Form::create("res/menus/MainMenu.form");
		_form->setConsumeInputEvents(false);
		
		((Button*)_form->getControl("singlePlayer"))->addListener(kNewSelector(&MainMenu::singlePlayer), Control::Listener::CLICK);
		((Button*)_form->getControl("multiPlayer"))->addListener(kNewSelector(&MainMenu::multiPlayer), Control::Listener::CLICK);*/
		
	}
	MainMenu::~MainMenu(){
		if (_form!=NULL)
		SAFE_RELEASE(_form)
	}
	
	void MainMenu::update(float elapsedTime){
		if (_form==NULL){
			_form = Form::create("res/menus/MainMenu.form");
			_form->setConsumeInputEvents(false);
			
			((Button*)_form->getControl("singlePlayer"))->addListener(kNewSelector(&MainMenu::singlePlayer), Control::Listener::CLICK);
			((Button*)_form->getControl("multiPlayer"))->addListener(kNewSelector(&MainMenu::multiPlayer), Control::Listener::CLICK);
		}
		_form->update(elapsedTime);
		/*if (_newMenu>-1){
			switch (_newMenu){
				case 0:
					this->_controller->changeToScreen(new SelectGame(this->_controller));
				break;
			}
			_newMenu=-1;
		}*/
		
	}

	void MainMenu::render(Scene*){
		//if (_form!=NULL)
		//Control* tst=_form->getControl("presets");
		//std::cout << tst->getX()<< "," << tst->getY() <<"/" << tst->getWidth() << "," << tst->getHeight() << std::endl;
		_form->draw();
	}
	
	void MainMenu::disable(){
		_form->setEnabled(false);
	}
	
	void MainMenu::singlePlayer(gameplay::Control::Listener::EventType evt){
		std::cout << "SinglePlayer button " << this->_controller << std::endl;
		//_newMenu=0;
		this->_controller->changeToScreen(new SelectGame(this->_controller));
		
	}
	
	void MainMenu::multiPlayer(gameplay::Control::Listener::EventType evt){
		std::cout << "multiplayer button " << this->_controller << std::endl;
		//_newMenu=0;
		this->_controller->changeToScreen(new MultiPlayerDashboard(this->_controller));
		
	}
	//void MainMenu::setForeground(bool b){
	//}
}
