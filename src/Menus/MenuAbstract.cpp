//
//  MenuAbstract.cpp
//  BillardOnline3D
//
//  Created by Dracks on 29/09/12.
//
//

#include "MenuAbstract.h"
namespace Menus{
	//class MenuInterface{
	
	
	MenuFormListener* MenuInterface::addListener(void (MenuInterface::*method)(gameplay::Control::Listener::EventType)){
		MenuFormListener* listener=new MenuFormListener(this, method);
		_formListenerList.push_back(listener);
		return listener;
	}
	
	MenuInterface::MenuInterface(::BillardMainClass* controller){
		this->_controller=controller;
	}
	
	MenuInterface::~MenuInterface(){
		for (int i=0; i<_formListenerList.size(); i++){
			delete _formListenerList[i];
		}
	}
	

	void MenuInterface::keyEvent(Keyboard::KeyEvent evt, int key){
		
	}
	

    void MenuInterface::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex){
		
	}
	
	void MenuInterface::update(float elapsedTime){
	}
	
	
	//class MenuFormListener : public gameplay::Control::Listener{
	
	MenuFormListener::MenuFormListener(MenuInterface* obj, void (MenuInterface::*method)(EventType)){
		_method=method;
		//std::cout << obj->_controller << std::endl;
		_obj=obj;
	}
	MenuFormListener::~MenuFormListener(){
			
	}
	void MenuFormListener::controlEvent(gameplay::Control* control, EventType evt){
		//std::cout << _obj->_controller << std::endl;
		(_obj->*_method)(evt);
	}
}