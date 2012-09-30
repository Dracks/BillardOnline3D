//
//  MenuAbstract.h
//  BillardOnline3D
//
//  Created by Dracks on 29/09/12.
//
//

#ifndef __BillardOnline3D__MenuAbstract__
#define __BillardOnline3D__MenuAbstract__
namespace Menus{
	class MenuInterface;
	class MenuFormListener;
}


#include <iostream>
#include "gameplay.h"
#include "BillardMainClass.h"

#define kNewSelector(selector) this->addListener((void (MenuInterface::*)(Control::Listener::EventType)) selector)

namespace Menus{
	class MenuInterface{
		friend class MenuFormListener;
	private:
		std::vector<MenuFormListener*> _formListenerList;
	protected:
		BillardMainClass* _controller;
		MenuFormListener* addListener(void (MenuInterface::*method)(gameplay::Control::Listener::EventType));
	public:
		MenuInterface(BillardMainClass* controller);
		virtual ~MenuInterface();
		virtual void update(float elapsedTime);
		virtual void render(gameplay::Scene*)=0;
		
		virtual void disable()=0;
		
		//virtual void setForeground(bool b)=0;
	};

	class MenuFormListener : public gameplay::Control::Listener{
		friend class MenuInterface;
	private:
		void (MenuInterface::*_method)(EventType);
		MenuInterface* _obj;
	protected:
		MenuFormListener(MenuInterface* obj, void (MenuInterface::*method)(EventType));
	public:
		~MenuFormListener();
		void controlEvent(gameplay::Control* control, EventType evt);
	};
}

#endif /* defined(__BillardOnline3D__MenuAbstract__) */
