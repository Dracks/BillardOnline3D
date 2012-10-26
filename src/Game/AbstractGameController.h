//
//  AbstractGameController.h
//  BillardOnline3D
//
//  Created by Dracks on 30/09/12.
//
//

#ifndef __BillardOnline3D__AbstractGameController__
#define __BillardOnline3D__AbstractGameController__
namespace Game{
	class AbstractGameController;
}
#include <iostream>
#include "gameplay.h"
#include "AbstractPlayerController.h"
// Aquest ens crea el deadlock
#include "GameHud.h"
#include <vector>

namespace Game{
	enum GameStatus {WAIT, MOVE, TOUCH};
	
	class AbstractGameController: public gameplay::PhysicsCollisionObject::CollisionListener{
	public:
		AbstractGameController(std::string);
		void initializeMaterial(Node* node, Material* material);
		bool isBallOut(int);
		virtual ~AbstractGameController();
		
		void start();
		
		void setGameHud(Menus::GameHud*);
		void setPlayer(AbstractPlayerController*);
		virtual void endRound()=0;
		
		gameplay::Scene* getScene();
		
		char getPlayerActive();
		AbstractPlayerController* getPlayer(int);
		void nextPlayer();
		
		virtual gameplay::Node* getPlayerBall()=0;
		virtual gameplay::Node* getBall(int i);
		
		virtual gameplay::Node* getOutBall();
		
		virtual gameplay::Node* getCue();
		
		virtual void update(float timeElapsed);
		
		virtual void collisionEvent(gameplay::PhysicsCollisionObject::CollisionListener::EventType type,
                                    const gameplay::PhysicsCollisionObject::CollisionPair& collisionPair,
                                    const gameplay::Vector3& contactPointA = gameplay::Vector3::zero(),
                                    const gameplay::Vector3& contactPointB = gameplay::Vector3::zero());
		
	protected:
		gameplay::Scene* _scene;
		std::vector<gameplay::Node*> _ballsList;
		
		gameplay::Node* _cueGroup;
		Menus::GameHud* _gameHud;
		
		std::vector<int> _ballsOut;
		
	private:
		char _playerActive;
		GameStatus _statusGame;
		std::vector<AbstractPlayerController*> _players;
		
		
	};
}


#endif /* defined(__BillardOnline3D__AbstractGameController__) */
