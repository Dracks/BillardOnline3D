//
//  MultiPlayerDashboard.h
//  BillardOnline3D
//
//  Created by Dracks on 10/26/12.
//
//

#ifndef __BillardOnline3D__MultiPlayerDashboard__
#define __BillardOnline3D__MultiPlayerDashboard__

namespace Menus{
	class MultiPlayerDashboard;
}


#include <iostream>
#include "MenuAbstract.h"
#include "OnlineConnector.h"

namespace Menus{
	class MultiPlayerDashboard: public Menus::MenuInterface{
	public:
		MultiPlayerDashboard(::BillardMainClass*);
		~MultiPlayerDashboard();
		
		/*
		 actions
		 */
		void actionBack(gameplay::Control::Listener::EventType);
		
		/*
		 Popup Response
		 */
		void loginWithUserAndPassword(std::string user, std::string password);
		
		/*
		 ConnectionResponses
		 */
		void loginResponse(Utils::ResponseStatus, void* );
		
		/* 
		 MenuInterface Herence
		 */
		virtual void update(float elapsedTime);
		virtual void render(gameplay::Scene*);
		virtual void disable();
	private:
		Menus::MenuInterface* _popup;
		gameplay::Form* _options;
		Utils::OnlineConnector* _connector;
	};
}

#endif /* defined(__BillardOnline3D__MultiPlayerDashboard__) */
