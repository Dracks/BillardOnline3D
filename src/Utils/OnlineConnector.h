//
//  OnlineConnector.h
//  BillardOnline3D
//
//  Created by Dracks on 10/28/12.
//
//

#ifndef __BillardOnline3D__OnlineConnector__
#define __BillardOnline3D__OnlineConnector__

namespace Utils{
	//template<class Type>
	class OnlineConnectorListener;
	//class OnlineConnectorResponse;
	class OnlineConnector;
}

#include <iostream>
#include "MenuAbstract.h"

namespace Utils{
	enum ResponseStatus {OK, ERROR, TIMEOUT};
	
	//template<class Type>
	class OnlineConnectorListener{
	public:
		OnlineConnectorListener(Menus::MenuInterface*, void (Menus::MenuInterface::*method)(ResponseStatus,void*));
		~OnlineConnectorListener();
		
		void call(ResponseStatus, void*);
	private:
		Menus::MenuInterface* _instance;
		void (Menus::MenuInterface::*_method)(ResponseStatus,void*);
	};
	
/*	class OnlineConnectorResponse{
	public:
		OnlineConnectorResponse();
		~OnlineConnectorResponse();
	};*/
	
	class OnlineConnector{
	public:
		OnlineConnector();
		~OnlineConnector();
		
		bool getIsConnected();
		
		void loginWithUserPassword(std::string user, std::string passwd, OnlineConnectorListener* listener);
		
	private:
		OnlineConnectorListener* _listener;
		std::string _token;
		std::string _renewToken;
		
	};
}

#endif /* defined(__BillardOnline3D__OnlineConnector__) */
