//
//  AbstractGameController.cpp
//  BillardOnline3D
//
//  Created by Dracks on 30/09/12.
//
//

#include "AbstractGameController.h"
using namespace gameplay;

#define kCueBallDistance 1.0f

namespace Game{
	//class AbstractGameController{
	AbstractGameController::AbstractGameController(std::string scene){
		
		_scene=Scene::load(scene.c_str());
		
		//VertexFormat vertexList=_scene->findNode("Table")->getModel()->getMesh()->getVertexFormat();
		
        
		Vector3 color(0.5,0.5,0.5);
		
		//std::cout << color.x << "," << color.y << "," << color.z << std::endl;
		_scene->setAmbientColor(0.5, 0.5, 0.5);
		
		Node* lightNode=_scene->findNode("Lamp");
		lightNode->getLight()->setColor(color);
		this->initializeMaterial(_scene->findNode("Frame"), _scene->findNode("Frame")->getModel()->getMaterial());
		this->initializeMaterial(_scene->findNode("Cue"), _scene->findNode("Cue")->getModel()->getMaterial());
		this->initializeMaterial(_scene->findNode("Ball"), _scene->findNode("Ball")->getModel()->getMaterial());
		
		
		Node* cueBase=_scene->findNode("Cue");
		cueBase->addRef();
		_scene->removeNode(cueBase);
		
		((PhysicsRigidBody*)cueBase->getCollisionObject())->setKinematic(true);
		//((PhysicsRigidBody*)cueBase->getCollisionObject())->set
		
		Node* cueGroupX=_scene->addNode();
		cueGroupX->setId("CueGroupX");
		cueGroupX->setTranslation(0, 0, 0);
		cueBase->setTranslation(kCueBallDistance, 0, 0);
		cueGroupX->addChild(cueBase);
		
		Node* cueGroupZ=_scene->addNode();
		cueGroupZ->addChild(cueGroupX);
		cueGroupZ->setId("CueGroupZ");
		cueGroupZ->setTranslation(0,0,0);
		
		Node* cameraCueNode=_scene->findNode("CameraFree")->clone();
		cameraCueNode->setId("CameraCue");
		cueGroupZ->addChild(cameraCueNode);
		cameraCueNode->setTranslation(1.5, 0.1, 0.2);
		cameraCueNode->setRotation(0.498, 0.502, 0.498, 0.502);
		
		_cueGroup=cueGroupZ;
		
		_cueGroup->addRef();
		_scene->removeNode(cueGroupX);
		_scene->removeNode(cueGroupZ);
		
		std::cout << "enabled" << cueBase->getCollisionObject()->isEnabled() << std::endl;
		std::cout << "kinematic" << cueBase->getCollisionObject()->isKinematic() << std::endl;
		std::cout << "dynamic" << cueBase->getCollisionObject()->isDynamic() << std::endl;
		_ballsList.push_back(_scene->findNode("Ball"));
		
		_ballsList[0]->getCollisionObject()->addCollisionListener(this);
		
		_statusGame=WAIT;
		_round=0;
	}
	
	void AbstractGameController::initializeMaterial(Node* node, Material* material)
	{
		// Bind light shader parameters to dynamic objects only
		if (node->getCollisionObject()->isDynamic())
		{
			Node* lightNode = _scene->findNode("Lamp");
			material->getParameter("u_ambientColor")->bindValue(_scene, &Scene::getAmbientColor);
			material->getParameter("u_lightColor")->bindValue(lightNode->getLight(), &Light::getColor);
			material->getParameter("u_lightDirection")->bindValue(lightNode, &Node::getForwardVectorView);
		}
	}

	bool AbstractGameController::isBallOut(int vi){
		for (unsigned int i=0; i<this->_ballsOut.size();i++){
			if (_ballsOut[i]==vi){
				return true;
			}
		}
		return false;
	}
	
	AbstractGameController::~AbstractGameController(){
		SAFE_RELEASE(_scene);
		SAFE_RELEASE(_cueGroup);
		for (std::vector<AbstractGameObserver*>::iterator iter=_observerList.begin(); iter!=_observerList.end(); iter++){
			delete *iter;
		}
	}
	
	void AbstractGameController::start(){
		_playerActive=0;
		_players[0]->move();
	}
	
	void AbstractGameController::setGameHud(Menus::GameHud* gh){
		_gameHud=gh;
	}
	
	void AbstractGameController::setPlayer(AbstractPlayerController*player){
		_players.push_back(player);
	}
	
	void AbstractGameController::addGameObserver(AbstractGameObserver* observer){
		_observerList.push_back(observer);
	}
		
	gameplay::Scene* AbstractGameController::getScene(){
		return _scene;
	}
	
	char AbstractGameController::getPlayerActive(){
		return _playerActive;
	}
	
	AbstractPlayerController* AbstractGameController::getPlayer(int i){
		assert(this->_players.size()>i);
		return this->_players[i];
	}
	
	void AbstractGameController::nextPlayer(){
		_playerActive++;
		_playerActive=_playerActive % _players.size();
	}
	
	gameplay::Node* AbstractGameController::getBall(int i){
		assert(i<_ballsList.size());
		return _ballsList[i];
	}
	
	gameplay::Node* AbstractGameController::getOutBall(){
		if (_ballsOut.empty())
			return NULL;
		else {
			int i=_ballsOut.front();
			_ballsOut.erase(_ballsOut.begin());
			gameplay::Node* r=_ballsList[i];
			((PhysicsRigidBody*)r->getCollisionObject())->setEnabled(true);
			return r;
		}
	}
	
	gameplay::Node* AbstractGameController::getCue(){
		return _cueGroup;
	}
	
	void AbstractGameController::placeBall(gameplay::Node* ball){
		int i=0;
		while (i<_ballsList.size() && _ballsList[i]!=ball) {
			i++;
		}
		assert(_ballsList[i]==ball);
		ActionInfo info(i, ball->getTranslation());
		for (std::vector<AbstractGameObserver*>::iterator iter=_observerList.begin(); iter!=_observerList.end(); iter++) {
			(*iter)->setAction(_round, &info);
			(*iter)->commit(_round);
		}
		_round++;
	}
	
	void AbstractGameController::shot(const gameplay::Vector3 &contactPoint, const gameplay::Vector3 &cueVelocity){
		((PhysicsRigidBody*) getPlayerBall()->getCollisionObject())->applyImpulse(cueVelocity,&contactPoint);
		ActionInfo info(contactPoint, cueVelocity);
		for (std::vector<AbstractGameObserver*>::iterator iter=_observerList.begin(); iter!=_observerList.end(); iter++) {
			(*iter)->setAction(_round, &info);
		}
		_statusGame=TOUCH;
	}
	
	void AbstractGameController::update(float timeElapsed){
		bool moving=false;
		unsigned int i;
		//std::cout << _statusGame << std::endl;
		for (i=0; i<_ballsList.size() && !moving; i++){
			Vector3 velocity=((PhysicsRigidBody*)_ballsList[i]->getCollisionObject())->getLinearVelocity();
			float vSquare=velocity.x*velocity.x+velocity.y*velocity.y+velocity.y*velocity.z;
			//std::cout << "Velocity Square:" << vSquare << std::endl;
			if (_ballsList[i]->getTranslationZ()<-1.0f){
				if (this->_ballsOut.empty() || !this->isBallOut(i)){
					std::cout << "ball " << i << " is out " << std::endl;
					((PhysicsRigidBody*)_ballsList[i]->getCollisionObject())->setEnabled(false);
					_ballsOut.push_back(i);
				}
			} else {
				if (vSquare>0.00001f){
					moving=true;
				}
			}
		}
		if (_statusGame==MOVE && !moving){
			
			this->endRound();
			_round++;
			for (std::vector<AbstractGameObserver*>::iterator iter=_observerList.begin(); iter!=_observerList.end(); iter++) {
				(*iter)->commit(_round);
			}
			_players[_playerActive]->move();
			Vector3 nullVelocity(0,0,0);
			_statusGame=WAIT;
			for (i=0;i<_ballsList.size(); i++){
				PhysicsRigidBody* co=(PhysicsRigidBody*)_ballsList[i]->getCollisionObject();
				co->setLinearVelocity(nullVelocity);
				co->setAngularVelocity(nullVelocity);
			}
		} else if (_statusGame==TOUCH && moving){
			
			_gameHud->startRuning();
			_cueGroup->findNode("Cue")->setTranslation(kCueBallDistance, 0, 0);
			_scene->removeNode(_cueGroup);
			_cueGroup->setTranslation(0, 0, -10);
			_cueGroup->findNode("Cue")->getCollisionObject()->setEnabled(false);
			_statusGame=MOVE;
		}/* else if (_statusGame==TOUCH){
			_statusGame=WAIT;
		}*/
	}
	
	void AbstractGameController::collisionEvent(gameplay::PhysicsCollisionObject::CollisionListener::EventType type,
						const gameplay::PhysicsCollisionObject::CollisionPair& collisionPair,
						const gameplay::Vector3& contactPointA,
						const gameplay::Vector3& contactPointB){
		
		Node* nodeA=collisionPair.objectA->getNode();
		Node* nodeB=collisionPair.objectB->getNode();
		Node* playerBall=getPlayerBall();
		Node* cue=_cueGroup->findNode("Cue");
		std::cout << "Collision!" << std::endl;
		std::cout << nodeA->getId() << std::endl;
		std::cout << nodeB->getId() << std::endl;
		std::cout << nodeA << ", " << nodeB << std::endl;
		std::cout << cue << ", " << playerBall << std::endl;
		std::cout << _statusGame << std::endl;

		if (_statusGame==WAIT && (
				(nodeA==getPlayerBall() && nodeB==_cueGroup->findNode("Cue")) /*||
				(nodeB==getPlayerBall() && nodeA==_cueGroup->findNode("Cue"))*/)){
			float cueVelocity=_players[_playerActive]->getVelocityCue()*30;
			if (abs(cueVelocity)!=std::numeric_limits<float>::infinity()){
#warning _cueGroup is not correct to use, because we don't have the two axis
				this->shot(contactPointA, _cueGroup->getRightVector().normalize()*cueVelocity);
			} else {
				std::cout << "Infinity" << _players[_playerActive]->getVelocityCue() << std::endl;
			}
		}
	}
}
