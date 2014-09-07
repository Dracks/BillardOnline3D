//
//  MultiPlayerLogin.cpp
//  BillardOnline3D
//
//  Created by Dracks on 10/26/12.
//
//

#include "MultiPlayerLogin.h"
#include "MainMenu.h"

//class MultiPlayerLogin: public Menus::MenuInterface{
//public:
using namespace gameplay;

namespace Menus{
	MultiPlayerLogin::MultiPlayerLogin(::BillardMainClass*billard, MultiPlayerDashboard* delegate):Menus::MenuInterface(billard){
		_login=NULL;
		_delegate=delegate;
		
	}
	MultiPlayerLogin::~MultiPlayerLogin(){
		if (_login!=NULL)
			SAFE_RELEASE(_login);
	}
		
	void MultiPlayerLogin::actionLogin(gameplay::Control::Listener::EventType){
		_delegate->loginWithUserAndPassword(_loginInput->getText(), _password);
	}
	
	void MultiPlayerLogin::actionCancel(gameplay::Control::Listener::EventType){
		this->_controller->changeToScreen(new MainMenu(this->_controller));
	}
	
	void MultiPlayerLogin::userChangeText(gameplay::Control::Listener::EventType){
		std::cout << "userChangeText " <<_loginInput->getLastKeypress() << ":" << _loginInput->getText() << std::endl;
		
	}
	
	void MultiPlayerLogin::passwordChangeText(gameplay::Control::Listener::EventType){
		/*int hidenSize=_password.size();
		std::string password=_passwordInput->getText();
		int publishSize=password.size();
		//int index=_passwordInput->getFocusIndex();
		//_passwordInput->
		if (hidenSize<publishSize){
			std::string append=password.substr(hidenSize, publishSize-hidenSize);
			_password.append(append);
			password="";
			for (int i=0; i<hidenSize; i++){
				password.append("*");
			}
			password.append(append);
			_passwordInput->setText(password.c_str());
		} else if(publishSize<hidenSize) {
			_password=_password.substr(0,publishSize);
		}//*/
		_password=_passwordInput->getText();
		//_passwordInput->setFocusIndex(index);
	}
		
	void MultiPlayerLogin::update(float elapsedTime){
		if (_login==NULL){
			_login=Form::create("res/menus/MultiPlayerDashboard.form#Login");
			_login->setConsumeInputEvents(false);
			
			_loginInput=((TextBox*) _login->getControl("user"));
			//_loginInput->addListener(kNewSelector(&MultiPlayerLogin::userChangeText), Control::Listener::TEXT_CHANGED);
			
			_passwordInput=((TextBox*) _login->getControl("password"));
			//_passwordInput->addListener(kNewSelector(&MultiPlayerLogin::passwordChangeText), Control::Listener::TEXT_CHANGED);
			//_passwordInput->setPassword(true);
			

			((Button*) _login->getControl("cancel"))->addListener(kNewSelector(&MultiPlayerLogin::actionCancel), Control::Listener::CLICK);
			((Button*) _login->getControl("login"))->addListener(kNewSelector(&MultiPlayerLogin::actionLogin), Control::Listener::CLICK);
		}
		_login->update(elapsedTime);
	}
	
	void MultiPlayerLogin::render(gameplay::Scene*){
		_login->draw();
	}
		
	void MultiPlayerLogin::disable(){
		_login->setEnabled(false);
	}
}
