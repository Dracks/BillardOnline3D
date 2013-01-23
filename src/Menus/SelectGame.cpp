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
#include "DevicePlayer.h"
#include "ThreeBandGame.h"

using namespace gameplay;
using namespace ::Game;
using namespace Players;

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
			_form = Form::create("res/menus/SelectGame.form#Menu");
			_form->setConsumeInputEvents(false);
			
			((Button*) _form->getControl("back"))->addListener(kNewSelector(&SelectGame::back), Control::Listener::CLICK);
			
			((Button*) _form->getControl("eightBall"))->addListener(kNewSelector(&SelectGame::createGame), Control::Listener::CLICK);
			((Button*) _form->getControl("nineBall"))->addListener(kNewSelector(&SelectGame::createGame), Control::Listener::CLICK);
			((Button*) _form->getControl("threeBand"))->addListener(kNewSelector(&SelectGame::createGame), Control::Listener::CLICK);//*/
			
		}
		_form->update(timeElapsed);
	}
		
	void SelectGame::render(gameplay::Scene*){
		_form->draw();
	}
	
	void SelectGame::back(gameplay::Control::Listener::EventType evt){
		this->_controller->changeToScreen(new MainMenu(this->_controller));
	}
	
	void SelectGame::createGame(gameplay::Control::Listener::EventType){
		AbstractGameController* gc=new ThreeBandGame(1);
		GameHud* gh=new GameHud(this->_controller, gc);
		gc->setPlayer(new DevicePlayer(gc, 0, gh));
		gc->setPlayer(new DevicePlayer(gc, 1, gh));
		
		gc->start();
		this->_controller->changeToScreen(gh);
	}
	
	void SelectGame::disable(){
		_form->setEnabled(false);
	}
}