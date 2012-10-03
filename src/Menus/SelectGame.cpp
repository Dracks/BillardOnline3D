//
//  SelectGame.cpp
//  BillardOnline3D
//
//  Created by Dracks on 29/09/12.
//
//

#include "SelectGame.h"
#include "MainMenu.h"
#include "GameHud.h"

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
			((Button*) _form->getControl("eightBall"))->addListener(kNewSelector(&SelectGame::createGame), Control::Listener::CLICK);
			((Button*) _form->getControl("nineBall"))->addListener(kNewSelector(&SelectGame::createGame), Control::Listener::CLICK);
			((Button*) _form->getControl("threeBand"))->addListener(kNewSelector(&SelectGame::createGame), Control::Listener::CLICK);
			
		}
	}
		
	void SelectGame::render(gameplay::Scene*){
		_form->draw();
	}
	
	void SelectGame::back(gameplay::Control::Listener::EventType evt){
		this->_controller->changeToScreen(new MainMenu(this->_controller));
	}
	
	void SelectGame::createGame(gameplay::Control::Listener::EventType){
		this->_controller->changeToScreen(new GameHud(this->_controller, new ::Game::AbstractGameController("res/models/ThreeBandGame.scene")));
	}
	
	void SelectGame::disable(){
		_form->disable();
	}
}