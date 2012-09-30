//
//  AbstractPlayerController.h
//  BillardOnline3D
//
//  Created by Dracks on 30/09/12.
//
//

#ifndef __BillardOnline3D__AbstractPlayerController__
#define __BillardOnline3D__AbstractPlayerController__

namespace Game{
	class AbstractPlayerController;
}

#include <iostream>
#include "AbstractGameController.h"

class Game::AbstractPlayerController{
public:
	AbstractPlayerController(Game::AbstractGameController*);
	virtual ~AbstractPlayerController();
protected:
	Game::AbstractGameController* gameController;
};

#endif /* defined(__BillardOnline3D__AbstractPlayerController__) */
