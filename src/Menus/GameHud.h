//
//  GameHub.h
//  BillardOnline3D
//
//  Created by Dracks on 01/10/12.
//
//

#ifndef __BillardOnline3D__GameHub__
#define __BillardOnline3D__GameHub__

namespace Menus{
	class GameHub;
}

#include <iostream>
#include "MenuAbstract.h"
#include "AbstractGameController.h"
#include "DevicePlayer.h"

namespace Menus{
	enum GameStatus {PAUSE, WAIT, RUNING,LOOK, SHOT, DIRECT, MOVE};
	
	class GameHud: public Menus::MenuInterface{
	public:
		GameHud(::BillardMainClass*, ::Game::AbstractGameController*);
		~GameHud();
		
		void update(float timeElapsed);
		void render(gameplay::Scene*);
		bool drawScene(gameplay::Node*);
		void disable();
		
		/**
		 * @brief register the user as the actual user controlling the game (checking that)
		 */
		void registerPlayerRound(Players::DevicePlayer*);
		/*
		 * AskExitMethods
		 */
		void exit(gameplay::Control::Listener::EventType);
		void cancelPause(gameplay::Control::Listener::EventType);
		
		/*
		 * Views
		 */
		void lookTop(gameplay::Control::Listener::EventType);
		void lookFree(gameplay::Control::Listener::EventType);
		void lookOverCue(gameplay::Control::Listener::EventType);
		
		/*
		 * Game Methods
		 */
		void pause(gameplay::Control::Listener::EventType);
		
		
		/**
		 * @brief disable user actions and show the actions.
    	 */
		void startRuning();
		
	private:
		GameStatus _status, _oldStatus;
		Players::DevicePlayer* _playerController;
		
		::Game::AbstractGameController* _gameController;
		
		gameplay::Form* _hud;
		gameplay::Form* _exit;
		
		gameplay::Camera* _freeCamera;
		gameplay::Camera* _topCamera;
		
	};
}

#endif /* defined(__BillardOnline3D__GameHub__) */
