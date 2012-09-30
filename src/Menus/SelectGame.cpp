//
//  SelectGame.cpp
//  BillardOnline3D
//
//  Created by Dracks on 29/09/12.
//
//

#include "SelectGame.h"
#include "MainMenu.h"

using namespace gameplay;

namespace Menus{
	//class SelectGame: public MenuInterface{
	SelectGame::SelectGame(::BillardMainClass* control): Menus::MenuInterface(control){
		_form=NULL;
		//_form->disable();
		
	}
	SelectGame::~SelectGame(){
		SAFE_RELEASE(_form)
	}
	
	void SelectGame::update(float timeElapsed){
		if (_form==NULL){
			_form = Form::create("res/menus/SelectGame.form");
			_form->setConsumeInputEvents(false);
			
			((Button*) _form->getControl("back"))->addListener(kNewSelector(&SelectGame::back), Control::Listener::CLICK);
		}
	}
		
	void SelectGame::render(gameplay::Scene*){
		_form->draw();
	}
	
	void SelectGame::back(gameplay::Control::Listener::EventType evt){
		this->_controller->changeToScreen(new MainMenu(this->_controller));
	}
	
	void SelectGame::disable(){
		_form->disable();
	}
}