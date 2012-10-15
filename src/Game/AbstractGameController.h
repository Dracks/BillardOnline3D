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
	class AbstractGameController: public gameplay::PhysicsCollisionObject::CollisionListener{
	public:
		AbstractGameController(std::string);
		void initializeMaterial(Node* node, Material* material);
		virtual ~AbstractGameController();
		
		void start();
		
		void setGameHud(Menus::GameHud*);
		void setPlayer(AbstractPlayerController*);
		
		gameplay::Scene* getScene();
		
		char getPlayerActive();
		
		virtual gameplay::Node* getPlayerBall()=0;
		
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
		
	private:
		char _playerActive;
		char _statusGame;
		std::vector<AbstractPlayerController*> _players;
		
		
	};
}


#endif /* defined(__BillardOnline3D__AbstractGameController__) */
