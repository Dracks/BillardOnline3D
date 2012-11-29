//
//  ThreeBandGame.cpp
//  BillardOnline3D
//
//  Created by Dracks on 02/10/12.
//
//

#include "ThreeBandGame.h"

#define kMaxPoints 1


namespace Game{
	//class ThreeBandGame: public AbstractGameController{
		
	ThreeBandGame::ThreeBandGame(int minFrameCount):AbstractGameController("res/models/ThreeBandGame.scene"){
		_minFrameCount=minFrameCount;
		
		Node* ballBase=_ballsList[0];
		
		Node* yellowBall=_scene->addNode();
		yellowBall->setModel(Model::create(ballBase->getModel()->getMesh()));
		yellowBall->setId("Yellow");
		yellowBall->setScale(0.061f);
		yellowBall->getModel()->setMaterial("res/models/ThreeBandGame.material#YellowBall");
		yellowBall->setTranslation(-1, -1, 0);
		yellowBall->setCollisionObject("res/models/ThreeBandGame.physics#Ball");
		this->initializeMaterial(yellowBall, yellowBall->getModel()->getMaterial());
		
		Node* redBall=_scene->addNode();
		redBall->setModel(Model::create(ballBase->getModel()->getMesh()));
		redBall->setId("Red");
		redBall->setScale(0.061f);
		redBall->getModel()->setMaterial("res/models/ThreeBandGame.material#RedBall");
		redBall->setTranslation(-1, 1, 0);
		redBall->setCollisionObject("res/models/ThreeBandGame.physics#Ball");
		this->initializeMaterial(redBall, redBall->getModel()->getMaterial());
		
		//PhysicsRigidBody* rb=(PhysicsRigidBody*) yellowBall->getCollisionObject();
		//rb->setKinematic(true);
		//rb->setKinematic(false);
		_ballsList.push_back(yellowBall);
		_ballsList.push_back(redBall);
		
		_ballsList[1]->getCollisionObject()->addCollisionListener(this);
		_ballsList[2]->getCollisionObject()->addCollisionListener(this);
	}
	
	ThreeBandGame::~ThreeBandGame(){
		
	}
	
	void ThreeBandGame::endRound(){
		if (_pointStatus==END_GAME && this->_ballsOut.empty()){
			//this->_players[this->getPlayerActive()];
			AbstractPlayerController* player=this->getPlayer(this->getPlayerActive());
			player->addPoint();
			if (player->getPoints()==kMaxPoints){
				_gameHud->endGame();
			}
			
		} else {
			this->nextPlayer();
		}
		
		_frameCount=0;
		_pointStatus=NONE;
		
		/*
		for (unsigned int i=0; i<this->_ballsOut.size(); i++){
			Node* ball=this->getBall(this->_ballsOut[i]);
			PhysicsRigidBody* body=(PhysicsRigidBody*) ball->getCollisionObject();
			Vector3 p=body->getLinearVelocity();
			body->setEnabled(true);
			std::cout << p.x << "," << p.y << "," << p.z << std::endl;
			body->setKinematic(true);
			body->setLinearVelocity(0, 0, 0);
			body->setAngularVelocity(0, 0, 0);
			//body->setKinematic(false);
			p=body->getLinearVelocity();
			std::cout << p.x << "," << p.y << "," << p.z << std::endl;
			ball->setTranslation(-1,0.5,0);
		}
		this->ballsOut.clear();
		*/
	}
	
	Node* ThreeBandGame::getPlayerBall(){
		return _ballsList[this->getPlayerActive()];
	}

		
	void ThreeBandGame::collisionEvent(gameplay::PhysicsCollisionObject::CollisionListener::EventType type,
                                    const gameplay::PhysicsCollisionObject::CollisionPair& collisionPair,
                                    const gameplay::Vector3& contactPointA,
									   const gameplay::Vector3& contactPointB){
		AbstractGameController::collisionEvent(type, collisionPair, contactPointA, contactPointB);
		
		Node* nodeA=collisionPair.objectA->getNode();
		Node* nodeB=collisionPair.objectB->getNode();
		
		
		switch (_pointStatus) {
			case NONE:
				if ((nodeA==getPlayerBall() && (nodeB==_ballsList[(getPlayerActive()+1)%2] || nodeB==_ballsList[2])) ||
					(nodeB==getPlayerBall() && (nodeA==_ballsList[(getPlayerActive()+1)%2] || nodeA==_ballsList[2]))){
					_firstBallTouch=nodeB;
					_pointStatus=FIRST;
					_pointStatus=END_GAME;
				}
				break;
			case FIRST:
				if ((nodeA==getPlayerBall() && nodeB==_scene->findNode("frame")) ||
					(nodeB==getPlayerBall() && nodeA==_scene->findNode("frame"))){
					_frameCount++;
					if (_frameCount==_minFrameCount){
						_pointStatus=CUSHION;
					}
				}
				break;
			case CUSHION:
				if ((nodeA==getPlayerBall() && nodeB!=_firstBallTouch && (nodeB==_ballsList[(getPlayerActive()+1)%2] || nodeB==_ballsList[2])) ||
					(nodeB==getPlayerBall() && nodeA!=_firstBallTouch && (nodeA==_ballsList[(getPlayerActive()+1)%2] || nodeA==_ballsList[2]))){
					_pointStatus=END_GAME;
				}
				break;
			case END_GAME:
				break;
		}
		
		
	}
}
