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
		
		void setPlayer(AbstractPlayerController*);
		
		gameplay::Scene* getScene();
		
	protected:
		gameplay::Scene* _scene;
		
	private:
		char _playerActive;
		char _statusGame;
		std::vector<AbstractPlayerController*> _players;
		
	};
}


#endif /* defined(__BillardOnline3D__AbstractGameController__) */
