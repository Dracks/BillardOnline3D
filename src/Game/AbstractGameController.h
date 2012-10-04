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
#include <vector>

namespace Game{
	class AbstractGameController{
	public:
		AbstractGameController(std::string);
		~AbstractGameController();
		
		void start();
		
		void setPlayer(AbstractPlayerController*);
		
		gameplay::Scene* getScene();
		
		char getPlayerActive();
		
		gameplay::Node* getPlayerBall();
		
		gameplay::Node* getCue();
	protected:
		gameplay::Scene* _scene;
		std::vector<gameplay::Node*> balls;
		
		gameplay::Node* _cueGroup;
		
	private:
		char _playerActive;
		char _statusGame;
		std::vector<AbstractPlayerController*> _players;
		
		
	};
}


#endif /* defined(__BillardOnline3D__AbstractGameController__) */