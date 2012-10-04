//
//  DevicePlayer.h
//  BillardOnline3D
//
//  Created by Dracks on 30/09/12.
//
//

#ifndef __BillardOnline3D__DevicePlayer__
#define __BillardOnline3D__DevicePlayer__
namespace Players{
	class DevicePlayer;
}
#include <iostream>
#include "AbstractPlayerController.h"
#include "AbstractGameController.h"
#include "GameHud.h"

namespace Players{
	class DevicePlayer: public ::Game::AbstractPlayerController{
	public:
		DevicePlayer(::Game::AbstractGameController*, int player, ::Menus::GameHud*);
		~DevicePlayer();
		
		void move();
		
		gameplay::Node* getCue();
	protected:
		::Menus::GameHud* _gameHud;
	};
}

#endif /* defined(__BillardOnline3D__DevicePlayer__) */