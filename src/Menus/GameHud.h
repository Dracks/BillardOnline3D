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
	class GameHud;
}

#include <iostream>
#include "MenuAbstract.h"
#include "AbstractGameController.h"
#include "DevicePlayer.h"

namespace Menus{
	enum GameStatus {PAUSE, WAIT, RUNING, PLACE_BALL, LOOK, SHOT, EFFECT, POINT, END};
	
	class GameHud: public Menus::MenuInterface{
	public:
		GameHud(::BillardMainClass*, ::Game::AbstractGameController*);
		~GameHud();
		
		void keyEvent(Keyboard::KeyEvent evt, int key);
		void touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);
		void update(float timeElapsed);
		void render(gameplay::Scene*);
		bool drawScene(gameplay::Node*);
		void disable();
		
		
		/**
		 * @brief register the user as the actual user controlling the game (checking that)
		 */
		void registerPlayerRound(Players::DevicePlayer*);
		
		void nextStepPlayer();
		/**
		 * @brief disable user actions and show the actions.
    	 */
		void startRuning();
		void endGame();
		
		/*
		 * Control the Cue
		 */
		void onMovePoint(int difX,int difY);
		void onMoveEffect(int difX,int difY);
		void onMoveShot(int difX,int difY);
		void onMoveBall(int difX, int difY);
		
		/*
		 * Interface Action administration
		 */
		void refreshActionButtons(int);
		//void showPreviousAction();
		
		/*
		 * Ask Exit Methods and End Methods
		 */
		void exit(gameplay::Control::Listener::EventType);
		void cancelPause(gameplay::Control::Listener::EventType);
		void replay(gameplay::Control::Listener::EventType);
		
		/*
		 * Actions
		 */
		void actionLook(gameplay::Control::Listener::EventType);
		void actionPoint(gameplay::Control::Listener::EventType);
		void actionEffect(gameplay::Control::Listener::EventType);
		void actionShoot(gameplay::Control::Listener::EventType);
		void actionPlaceBall(gameplay::Control::Listener::EventType);
		
		/*
		 * Views
		 */
		void pause(gameplay::Control::Listener::EventType);
		void lookTop(gameplay::Control::Listener::EventType);
		void lookFree(gameplay::Control::Listener::EventType);
		void lookOverCue(gameplay::Control::Listener::EventType);

		
	private:
		GameStatus _status, _oldStatus;
		Players::DevicePlayer* _playerController;
		
		::Game::AbstractGameController* _gameController;
		
		gameplay::Form* _hudScore;
		gameplay::Form* _hudViews;
		gameplay::Form* _hudActions;
		gameplay::Form* _hudEndGame;
		
		gameplay::Form* _hudHidden;
		
		gameplay::Label* _scorePlayer1;
		gameplay::Label* _scorePlayer2;
		
		gameplay::Form* _exit;
		
		gameplay::Camera* _activeCamera;
		
		gameplay::Node* _ballOut;
		
		int _oldX, _oldY;
		
		char _drawStatus;
		
		double _oldTimeMove;
		bool _isMoving;
		
		std::vector<gameplay::Button*> _listActionsButton;
		int _newOptionShowing;
		
		int _optionShowing;
	};
}

#endif /* defined(__BillardOnline3D__GameHub__) */
