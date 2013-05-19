//
//  AbstractGameObserver.cpp
//  BillardOnline3D
//
//  Created by Dracks on 5/19/13.
//
//

#include "AbstractGameObserver.h"


namespace Game{
	
	//class BallInfo{
	
	BallInfo::BallInfo(int keyBall, BallStatus status, gameplay::Vector3 position){
		_keyBall=keyBall;
		_status=status;
		_position=position;
	}
	int BallInfo::getKey(){
		return _keyBall;
	}
	BallStatus BallInfo::getStatus(){
		return _status;
	}
	gameplay::Vector3 BallInfo::getPosition(){
		return _position;
	}
	
	//class ActionInfo{
	
	ActionInfo::ActionInfo(int keyBall, gameplay::Vector3 position){
		_action=AT_Place;
		_keyBall=keyBall;
		_position=position;
	}
	ActionInfo::ActionInfo(gameplay::Vector3 position, gameplay::Vector3 vectorShot){
		_action=AT_Shoot;
		_position=position;
		_velocityShot=vectorShot;
	}
	ActionType ActionInfo::getAction(){
		return _action;
	}
	int ActionInfo::getKey(){
		return _keyBall;
	}
	gameplay::Vector3 ActionInfo::getPosition(){
		return _position;
	}
	gameplay::Vector3 ActionInfo::getVelocityShot(){
		return _velocityShot;
	}
	
}