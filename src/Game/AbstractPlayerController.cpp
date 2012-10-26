//
//  AbstractPlayerController.cpp
//  BillardOnline3D
//
//  Created by Dracks on 30/09/12.
//
//

#include "DevicePlayer.h" // Trencar el deadlock
#include "AbstractPlayerController.h"


namespace Game{
//	class AbstractPlayerController{

	AbstractPlayerController::AbstractPlayerController(AbstractGameController* gameController, int player){
		_player=player;
		_gameController=gameController;
		
		this->resetPoints();
		assert(gameController!=NULL);
	}
	AbstractPlayerController::~AbstractPlayerController(){
		
	}
		
	char AbstractPlayerController::getPlayer(){
		return _player;
	}
	
	int AbstractPlayerController::getPoints(){
		return this->points;
	}
	
	void AbstractPlayerController::addPoint(int p){
		points+=p;
	}
	
	void AbstractPlayerController::resetPoints(){
		this->points=0;
	}
	
}