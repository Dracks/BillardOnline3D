//
//  MultiPlayerDashboard.cpp
//  BillardOnline3D
//
//  Created by Dracks on 10/26/12.
//
//

#include "MultiPlayerDashboard.h"
#include "MultiPlayerLogin.h"
#include "MainMenu.h"

namespace Menus{
	//class MultiPlayerDashboard: public Menus::MenuInterface{
	MultiPlayerDashboard::MultiPlayerDashboard(::BillardMainClass* controller):Menus::MenuInterface(controller){
		_connector=controller->getConnector();
		
		_popup=NULL;
		_options=NULL;
		
		if (!_connector->getIsConnected()){
			_popup=new MultiPlayerLogin(controller, this);
			//_options->disable();
		}
	}
	MultiPlayerDashboard::~MultiPlayerDashboard(){
		if (_options!=NULL)
			SAFE_RELEASE(_options);
		if (_popup!=NULL)
			delete _popup;
	}
		
		/*
		 actions
		 */
	void MultiPlayerDashboard::actionBack(gameplay::Control::Listener::EventType){
		this->_controller->changeToScreen(new MainMenu(this->_controller));
	}
		
		/*
		 Popup Response
		 */
	void MultiPlayerDashboard::loginWithUserAndPassword(std::string user, std::string password){
		_connector->loginWithUserPassword(user, password, new Utils::OnlineConnectorListener(this, (void (MenuInterface::*)(Utils::ResponseStatus,void*)) &MultiPlayerDashboard::loginResponse));
	}
	
	/*
	 ConnectionResponses
	 */
	void MultiPlayerDashboard::loginResponse(Utils::ResponseStatus rCode, void* data){
		std::cout << "loginResponse:" << rCode << "," << (char*) data << std::endl;
		if (rCode==Utils::OK){
			_options->enable();
			_popup->disable();
			delete _popup;
			_popup=NULL;
		}
	}
		
		/*
		 MenuInterface Herence
		 */
	void MultiPlayerDashboard::update(float elapsedTime){
		if (_options==NULL){
			_options=Form::create("res/menus/MultiPlayerDashboard.form#ListOptions");
			_options->setConsumeInputEvents(false);
			
			((Button*) _options->getControl("back"))->addListener(kNewSelector(&MultiPlayerDashboard::actionBack), Control::Listener::CLICK);
			
			if (_popup!=NULL){
				_options->disable();
			}
		}
		_options->update(elapsedTime);
		if (_popup!=NULL){
			_popup->update(elapsedTime);
		}
	}
	void MultiPlayerDashboard::render(gameplay::Scene* s){
		_options->draw();
		if (_popup!=NULL){
			_popup->render(s);
		}
	}
	void MultiPlayerDashboard::disable(){
		_options->disable();
		if (_popup!=NULL){
			_popup->disable();
		}
	}
}
