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

namespace Game{
	class AbstractPlayerController{
	public:
		AbstractPlayerController(AbstractGameController*, int player);
		virtual ~AbstractPlayerController();
		
		virtual void move()=0;
		
		virtual int getPlayer();
	protected:
		int player;
		AbstractGameController* gameController;
	};
}

#endif /* defined(__BillardOnline3D__AbstractPlayerController__) */
