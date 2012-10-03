//
//  AbstractGameController.cpp
//  BillardOnline3D
//
//  Created by Dracks on 30/09/12.
//
//

#include "AbstractGameController.h"
using namespace gameplay;

namespace Game{
	//class AbstractGameController{
	AbstractGameController::AbstractGameController(std::string scene){
		_scene=Scene::load(scene.c_str());
	}
	AbstractGameController::~AbstractGameController(){
		SAFE_RELEASE(_scene);
	}
		
	void AbstractGameController::setPlayer(AbstractPlayerController*){
		
	}
		
	gameplay::Scene* AbstractGameController::getScene(){
		return _scene;
	}
		
}