//
//  AbstractPlayerController.cpp
//  BillardOnline3D
//
//  Created by Dracks on 30/09/12.
//
//

#include "AbstractPlayerController.h"


namespace Game{
//	class AbstractPlayerController{

	AbstractPlayerController::AbstractPlayerController(AbstractGameController* gameController, int player){
		_player=player;
		_gameController=gameController;
	}
	AbstractPlayerController::~AbstractPlayerController(){
		
	}
		
	char AbstractPlayerController::getPlayer(){
		return _player;
	}
}