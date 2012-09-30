//
//  MainMenu.cpp
//  BillardOnline3D
//
//  Created by Dracks on 28/09/12.
//
//

#include "MainMenu.h"
#include "SelectGame.h"

using namespace gameplay;

//class MainMenu{
namespace Menus {
	MainMenu::MainMenu(::BillardMainClass* main): Menus::MenuInterface(main){
		// Create a font for drawing the framerate.
		//Font* _font = Font::create("res/arial18.gpb");
		//std::cout << main << std::endl;
		_form=NULL;
		
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
		}
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
			_form->draw();
	}

	void MainMenu::singlePlayer(gameplay::Control::Listener::EventType evt){
		std::cout << "SinglePlayer button " << this->_controller << std::endl;
		//_newMenu=0;
		this->_controller->changeToScreen(new SelectGame(this->_controller));
		
	}
	
	void MainMenu::disable(){
		_form->disable();
	}
	//void MainMenu::setForeground(bool b){
	//}
}
