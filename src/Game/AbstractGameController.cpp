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
		//Node* cue=_scene->findNode("Cue");
		Node* cueBase=_scene->findNode("Cue");
		cueBase->addRef();
		//_scene->removeNode(_scene->findNode("Cue"));
		_scene->removeNode(cueBase);
		//cueBase->getParent()->removeChild(cueBase);
		
		Node* cueGroup=_scene->addNode();
		cueGroup->addChild(cueBase);
		cueBase->setTranslation(1, 0, 0);
		cueGroup->setId("CueGroup");
		cueGroup->setTranslation(0,0,0);
		
		Node* cameraCueNode=_scene->findNode("CameraFree")->clone();
		//_scene->removeNode(cameraCueNode);
		cameraCueNode->setId("CameraCue");
		//cameraCueNode->getParent()->removeChild(cameraCueNode);
		cueGroup->addChild(cameraCueNode);
		cameraCueNode->setTranslation(1.5, 0.1, 0.2);
		cameraCueNode->setRotation(0.498, 0.502, 0.498, 0.502);
		
		//_scene->addNode(cueGroup);
		
		_cueGroup=cueGroup;
		
		_cueGroup->addRef();
		//cue->addRef();
		
		//cueBase->setCollisionObject(cue->getCollisionObject());
		
		//_scene->removeNode(cue);
		_scene->removeNode(cueGroup);
		
		_scene->findNode("Ball")->setTranslationZ(0.0829773f);
		
		//Quaternion quaternion=_scene->findNode("CameraTop")->getRotation();
		//std::cout << quaternion.x << ","<< quaternion.y <<","<< quaternion.z <<","<< quaternion.w<< std::endl;
		
		//quaternion=cueBase->getRotation();
		//std::cout << quaternion.x << ","<< quaternion.y <<","<< quaternion.z <<","<< quaternion.w<< std::endl;
		
		//std::cout << cueGroup->getScene() << std::endl;
		//_scene->removeNode(cue);
	}
	
	AbstractGameController::~AbstractGameController(){
		SAFE_RELEASE(_scene);
		SAFE_RELEASE(_cueGroup);
	}
	
	void AbstractGameController::start(){
		_players[0]->move();
	}
		
	void AbstractGameController::setPlayer(AbstractPlayerController*player){
		_players.push_back(player);
	}
		
	gameplay::Scene* AbstractGameController::getScene(){
		return _scene;
	}
	
	char AbstractGameController::getPlayerActive(){
		return _playerActive;
	}
	
	Node* AbstractGameController::getPlayerBall(){
		return _scene->findNode("Ball");
	}
	
	gameplay::Node* AbstractGameController::getCue(){
		return _cueGroup;
	}
		
}