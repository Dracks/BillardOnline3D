//
//  ThreeBandGame.h
//  BillardOnline3D
//
//  Created by Dracks on 02/10/12.
//
//

#ifndef __BillardOnline3D__ThreeBandGame__
#define __BillardOnline3D__ThreeBandGame__

namespace Game{
	class ThreeBandGame;
}

#include <iostream>
#include "AbstractGameController.h"

namespace Game{
	class ThreeBandGame: public AbstractGameController{
	public:
		ThreeBandGame();
		~ThreeBandGame();
		
		Node* getPlayerBall();
		
		virtual void collisionEvent(gameplay::PhysicsCollisionObject::CollisionListener::EventType type,
                                    const gameplay::PhysicsCollisionObject::CollisionPair& collisionPair,
                                    const gameplay::Vector3& contactPointA = gameplay::Vector3::zero(),
                                    const gameplay::Vector3& contactPointB = gameplay::Vector3::zero());
	};
}


#endif /* defined(__BillardOnline3D__ThreeBandGame__) */
