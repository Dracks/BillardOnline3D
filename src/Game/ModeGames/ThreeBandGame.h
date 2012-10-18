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
	enum GamePointStatus {NONE, FIRST, CUSHION, END};
	class ThreeBandGame: public AbstractGameController{
	public:
		ThreeBandGame(int minFrameCount);
		~ThreeBandGame();
		
		void endRound();
		
		Node* getPlayerBall();
		
		virtual void collisionEvent(gameplay::PhysicsCollisionObject::CollisionListener::EventType type,
                                    const gameplay::PhysicsCollisionObject::CollisionPair& collisionPair,
                                    const gameplay::Vector3& contactPointA = gameplay::Vector3::zero(),
                                    const gameplay::Vector3& contactPointB = gameplay::Vector3::zero());
	private:
		GamePointStatus _pointStatus;
		//std::vector<Node*> _listOtherBalls;
		Node* _firstBallTouch;
		char _frameCount;
		char _minFrameCount;
		std::vector<int> userPoints;
	};

}


#endif /* defined(__BillardOnline3D__ThreeBandGame__) */
