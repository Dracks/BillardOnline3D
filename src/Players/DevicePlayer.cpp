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

#define kMaxTime 0.05f

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
		float time=0;
		float distance=0;
		for (int i=0; i<_cueVelocity.size(); i++) {
			std::pair<float, float> elem=_cueVelocity[i];
			distance+=elem.first;
			time+=elem.second;
		}
		std::cout << "getVelocityCue()" << distance << "," << time << std::endl;
		return distance/time;
	}

	void DevicePlayer::setCueVelocity(float distance, float time){
		/**
		 * @todo solucionar el problema del infinit!!!
		 *
		if (abs(v)!=std::numeric_limits<float>::infinity()){
			_cueVelocity=v;
		}*/
		std::cout << "setCueVelocity " << distance << "," << time << std::endl;
		float timeToDelete=kMaxTime;
		_cueVelocity.insert(_cueVelocity.begin(), std::pair<float, float>(distance, time));
		for (std::vector<std::pair<float, float> >::iterator iter=_cueVelocity.begin(); iter!=_cueVelocity.end(); iter++){
			timeToDelete-=(*iter).second;
			if (timeToDelete<0){
				_cueVelocity.erase(iter);
				iter--;
			}
		}
	}

}
