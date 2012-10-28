//
//  OnlineConnector.cpp
//  BillardOnline3D
//
//  Created by Dracks on 10/28/12.
//
//

#include "OnlineConnector.h"

namespace Utils{
	
	//template<class Type>
	//class OnlineConnectorListener{
	OnlineConnectorListener::OnlineConnectorListener(Menus::MenuInterface* instance, void (Menus::MenuInterface::*method)(ResponseStatus,void*)){
		_instance=instance;
		_method=method;
	}
	OnlineConnectorListener::~OnlineConnectorListener(){
		
	}
		
	void OnlineConnectorListener::call(ResponseStatus response, void* data){
		(_instance->*_method)(response, data);
	}
	
	//class OnlineConnector{
	OnlineConnector::OnlineConnector(){
		_token="";
		_renewToken="";
	}
	OnlineConnector::~OnlineConnector(){
		
	}
	
	bool OnlineConnector::getIsConnected(){
		return _token.size()!=0;
	}
	
	void OnlineConnector::loginWithUserPassword(std::string user, std::string passwd, OnlineConnectorListener* listener){
		ResponseStatus r=ERROR;
		std::string text="User and password incorrect";
		
		
		
		if (user.compare("hola")==0 && passwd.compare("test")==0){
			r=OK;
			text="Eickot";
		}
		
		listener->call(r,(void*) text.c_str());
		delete listener;
	}

}
