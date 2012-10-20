//
//  DevicePlayer.cpp
//  BillardOnline3D
//
//  Created by Dracks on 30/09/12.
//
//

#include "DevicePlayer.h"
#include "GameHud.h"

using namespace gameplay;
using namespace ::Game;

namespace Players{
	//class DevicePlayer: public ::Game::AbstractPlayerController{
	DevicePlayer::DevicePlayer(::Game::AbstractGameController* gc, int player, ::Menus::GameHud*gh):AbstractPlayerController(gc, player){
		_gameHud=gh;
	}
	
	DevicePlayer::~DevicePlayer(){
		
	}
		
	void DevicePlayer::move(){
		std::cout << "Moving: " << (int) _player << std::endl;
		_gameHud->registerPlayerRound(this);
	}
	
	gameplay::Node* DevicePlayer::getCue(){
		
		return _gameController->getCue();
	}
	
	float DevicePlayer::getVelocityCue(){
		return _cueVelocity;
	}

	void DevicePlayer::setCueVelocity(float v){
		/**
		 * @todo solucionar el problema del infinit!!!
		 */
		if (abs(v)!=std::numeric_limits<float>::infinity()){
			_cueVelocity=v;
		}
	}

}
