//
//  ThreeBandGame.cpp
//  BillardOnline3D
//
//  Created by Dracks on 02/10/12.
//
//

#include "ThreeBandGame.h"


namespace Game{
	//class ThreeBandGame: public AbstractGameController{
		
	ThreeBandGame::ThreeBandGame():AbstractGameController("res/models/ThreeBandGame.scene"){
		Node* ballBase=_ballsList[0];
		
		Node* yellowBall=_scene->addNode();
		yellowBall->setModel(Model::create(ballBase->getModel()->getMesh()));
		yellowBall->setScale(0.061f);
		yellowBall->getModel()->setMaterial("res/models/ThreeBandGame.material#YellowBall");
		yellowBall->setTranslation(-1, -1, 0);
		yellowBall->setCollisionObject("res/models/ThreeBandGame.physics#Ball");
		PhysicsRigidBody* rb=(PhysicsRigidBody*) yellowBall->getCollisionObject();
		//rb->setKinematic(true);
		//rb->setKinematic(false);
		_ballsList.push_back(yellowBall);
	}
	
	ThreeBandGame::~ThreeBandGame(){
		
	}
	
	Node* ThreeBandGame::getPlayerBall(){
		return _ballsList[0];
	}
		
	void ThreeBandGame::collisionEvent(gameplay::PhysicsCollisionObject::CollisionListener::EventType type,
                                    const gameplay::PhysicsCollisionObject::CollisionPair& collisionPair,
                                    const gameplay::Vector3& contactPointA,
									   const gameplay::Vector3& contactPointB){
		AbstractGameController::collisionEvent(type, collisionPair, contactPointA, contactPointB);
		
		
		
	}
}
