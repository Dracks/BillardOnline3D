//
//  GameHub.cpp
//  BillardOnline3D
//
//  Created by Dracks on 01/10/12.
//
//

#include "GameHud.h"
#include "MainMenu.h"

using namespace gameplay;

namespace Menus{
	//enum GameStatus {PAUSE, WAIT, RUNING,LOOK, SHOT, DIRECT, MOVE};
	
	//class GameHud: public Menus::MenuInterface{
	
	GameHud::GameHud(::BillardMainClass* base, ::Game::AbstractGameController* gameController):Menus::MenuInterface(base) {
		_hud=NULL;
		_gameController=gameController;
		_status=WAIT;
		
		//Scene* scena=_gameController->getScene();
		//_topCamera=scena->findNode("CameraTop")->getCamera();
		//_freeCamera=scena->findNode("CameraFree")->getCamera();
		//scena->setActiveCamera(_topCamera);
	}
	
	GameHud::~GameHud(){
		if (_hud!=NULL)
			SAFE_RELEASE(_hud)
	}
	
	void GameHud::update(float timeElapsed){
		if (_hud==NULL){
			_hud = Form::create("res/menus/GameHud.form");
			_hud->setConsumeInputEvents(false);
			
			_exit = Form::create("res/menus/ExitAsk.form");
			_exit->setConsumeInputEvents(false);
			_exit->disable();
			
			((Button*) _exit->getControl("exit"))->addListener(kNewSelector(&GameHud::exit), Control::Listener::CLICK);
			((Button*) _exit->getControl("cancel"))->addListener(kNewSelector(&GameHud::cancelPause), Control::Listener::CLICK);
			
			
			((Button*) _hud->getControl("pause"))->addListener(kNewSelector(&GameHud::pause), Control::Listener::CLICK);
			
			((Button*) _hud->getControl("free"))->addListener(kNewSelector(&GameHud::lookFree), Control::Listener::CLICK);
			((Button*) _hud->getControl("top"))->addListener(kNewSelector(&GameHud::lookTop), Control::Listener::CLICK);
			((Button*) _hud->getControl("cue"))->addListener(kNewSelector(&GameHud::lookOverCue), Control::Listener::CLICK);
			
			Container* c=((Container*) _hud->getControl("containerPause"));
			
			/*std::cout << c->getX() << "," << c->getY() << "," << c->getWidth() << "," << c->getHeight() << std::endl;
			
			c=((Container*) _hud->getControl("views"));
			std::cout << c->getX() << "," << c->getY() << std::endl;*/
		}
	}
	void GameHud::render(gameplay::Scene*){
		if (_gameController!=NULL){
			_gameController->getScene()->visit(this, &GameHud::drawScene);
		}
		
		if (_status==PAUSE){
			_exit->draw();
		} else {
			_hud->draw();
		}
		
	}
	
	bool GameHud::drawScene(gameplay::Node* node){
		// If the node visited contains a model, draw it
		Model* model = node->getModel();
		if (model)
		{
			model->draw();
		}//*/
		return true;
	}
	
	void GameHud::disable(){
		_hud->disable();
	}

	
	/**
	 * @brief register the user as the actual user controlling the game (checking that)
	 */
	void GameHud::registerPlayerRound(Players::DevicePlayer*){
		
	}
	
	void GameHud::exit(gameplay::Control::Listener::EventType){
		_controller->changeToScreen(new MainMenu(this->_controller));
	}
	
	void GameHud::cancelPause(gameplay::Control::Listener::EventType){
		_status=_oldStatus;
		_exit->disable();
		_hud->enable();
	}
	
	
	/*
	 * Views
	 */
	void GameHud::lookTop(gameplay::Control::Listener::EventType){
		_gameController->getScene()->setActiveCamera(_gameController->getScene()->findNode("CameraTop")->getCamera());
	}
	void GameHud::lookFree(gameplay::Control::Listener::EventType){
		_gameController->getScene()->setActiveCamera(_gameController->getScene()->findNode("CameraFree")->getCamera());
	}
	void GameHud::lookOverCue(gameplay::Control::Listener::EventType){
		
	}
	
	void GameHud::pause(gameplay::Control::Listener::EventType){
		_oldStatus=_status;
		_status=PAUSE;
		_exit->enable();
		_hud->disable();
	}
	
	void GameHud::startRuning(){
		
	}
	
}