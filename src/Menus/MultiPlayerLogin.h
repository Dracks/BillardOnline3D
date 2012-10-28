//
//  MultiPlayerLogin.h
//  BillardOnline3D
//
//  Created by Dracks on 10/26/12.
//
//

#ifndef __BillardOnline3D__MultiPlayerLogin__
#define __BillardOnline3D__MultiPlayerLogin__
namespace Menus{
	class MultiPlayerLogin;
}

#include <iostream>
#include "MenuAbstract.h"
#include "MultiPlayerDashboard.h"

namespace Menus{
	class MultiPlayerLogin: public Menus::MenuInterface{
	public:
		MultiPlayerLogin(::BillardMainClass*, MultiPlayerDashboard*);
		~MultiPlayerLogin();
		
		void actionLogin(gameplay::Control::Listener::EventType);
		void actionCancel(gameplay::Control::Listener::EventType);
		void userChangeText(gameplay::Control::Listener::EventType);
		void passwordChangeText(gameplay::Control::Listener::EventType);
		
		
		virtual void update(float elapsedTime);
		virtual void render(gameplay::Scene*);
		
		virtual void disable();
		
	private:
		gameplay::Form* _login;
		MultiPlayerDashboard* _delegate;
		
		gameplay::TextBox* _loginInput;
		gameplay::TextBox* _passwordInput;
		
		std::string _userName;
		std::string _password;
	};
}

#endif /* defined(__BillardOnline3D__MultiPlayerLogin__) */
