//
//  GameHub.cpp
//  BillardOnline3D
//
//  Created by Dracks on 01/10/12.
//
//

#include "GameHud.h"
#include "MainMenu.h"

using namespace gameplay;
/*
 *vec3 p = entity2->getPosition();
 vec3 r = entity1->getPosition();
 float xdistance = p[0] - r[0];
 float ydistance = p[1] - r[1];
 float zdistance = p[2] - r[2];
 float xzdistance = sqrt(xdistance * xdistance + zdistance * zdistance);
 entitity1->setHeading(atan2(xdistance, zdistance)); // rotation around y
 entitity1->setPitch(-atan2(ydistance, xzdistance)); // rotation around x
 entitity1->setBank(0);
 */
namespace Menus{
	//enum GameStatus {PAUSE, WAIT, RUNING,LOOK, SHOT, DIRECT, MOVE};
	
	//class GameHud: public Menus::MenuInterface{
	
	GameHud::GameHud(::BillardMainClass* base, ::Game::AbstractGameController* gameController):Menus::MenuInterface(base) {
		_hud=NULL;
		_gameController=gameController;
		_status=WAIT;
		
		_activeCamera=_gameController->getScene()->getActiveCamera();
		_drawStatus=0;
		
		//Scene* scena=_gameController->getScene();
		//_topCamera=scena->findNode("CameraTop")->getCamera();
		//_freeCamera=scena->findNode("CameraFree")->getCamera();
		//scena->setActiveCamera(_topCamera);
	}
	
	GameHud::~GameHud(){
		if (_hud!=NULL)
			SAFE_RELEASE(_hud)
	}
	
	void GameHud::keyEvent(Keyboard::KeyEvent evt, int key){
		if (evt==Keyboard::KEY_PRESS){
			switch (key) {
				case Keyboard::KEY_C:
					this->lookOverCue(Control::Listener::CLICK);
					break;
				case Keyboard::KEY_T:
					this->lookTop(Control::Listener::CLICK);
					break;
				case Keyboard::KEY_F:
					this->lookFree(Control::Listener::CLICK);
					break;
				case Keyboard::KEY_D:
					_drawStatus++;
					_drawStatus=_drawStatus%3;
					break;
				default:
					break;
			}
		}
	}
	
	void GameHud::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex){
		int difX, difY;
		float mx, my;
		if (_status!=RUNING){
			switch (evt) {
				case Touch::TOUCH_MOVE:
					difX=x-_oldX;
					difY=y-_oldY;
					switch (_status) {
						case POINT:
							this->onMovePoint(difX, difY);
							break;
						case EFFECT:
							this->onMoveEffect(difX, difY);
							break;
						case SHOT:
							this->onMoveShot(difX, difY);
						default:
							break;
					}// Warning not used BREAK!!!!
				case Touch::TOUCH_PRESS:
					_oldX=x;
					_oldY=y;
					break;

				default:
					break;
			}
		}
	}
	
	void GameHud::update(float timeElapsed){
		if (_hud==NULL){
			_hud = Form::create("res/menus/GameHud.form");
			_hud->setConsumeInputEvents(false);
			
			((Button*) _hud->getControl("pause"))->addListener(kNewSelector(&GameHud::pause), Control::Listener::CLICK);
			((Button*) _hud->getControl("look"))->addListener(kNewSelector(&GameHud::actionLook), Control::Listener::CLICK);
			((Button*) _hud->getControl("point"))->addListener(kNewSelector(&GameHud::actionPoint), Control::Listener::CLICK);
			((Button*) _hud->getControl("effect"))->addListener(kNewSelector(&GameHud::actionEffect), Control::Listener::CLICK);
			((Button*) _hud->getControl("shoot"))->addListener(kNewSelector(&GameHud::actionShoot), Control::Listener::CLICK);
			//((Button*) _hud->getControl("pause"))->addListener(kNewSelector(&GameHud::pause), Control::Listener::CLICK);
			
			
			((Button*) _hud->getControl("free"))->addListener(kNewSelector(&GameHud::lookFree), Control::Listener::CLICK);
			((Button*) _hud->getControl("top"))->addListener(kNewSelector(&GameHud::lookTop), Control::Listener::CLICK);
			((Button*) _hud->getControl("cue"))->addListener(kNewSelector(&GameHud::lookOverCue), Control::Listener::CLICK);
			
			_exit = Form::create("res/menus/ExitAsk.form");
			_exit->setConsumeInputEvents(false);
			_exit->disable();
			
			((Button*) _exit->getControl("exit"))->addListener(kNewSelector(&GameHud::exit), Control::Listener::CLICK);
			((Button*) _exit->getControl("cancel"))->addListener(kNewSelector(&GameHud::cancelPause), Control::Listener::CLICK);
		}
	}
	
	void GameHud::render(gameplay::Scene*){
		if (_gameController!=NULL){
			if (_drawStatus<2)
				_gameController->getScene()->visit(this, &GameHud::drawScene);
			if (_drawStatus>0)
				_controller->getPhysicsController()->drawDebug(_gameController->getScene()->getActiveCamera()->getViewProjectionMatrix());
			//Vector3 p=_gameController->getPlayerBall()->getTranslation();
			//std::cout << p.x << "," << p.y << "," << p.z << std::endl;
			
		}
		
		if (_status==PAUSE){
			_exit->draw();
		} else {
			_hud->draw();
		}
		
	}
	
	bool GameHud::drawScene(gameplay::Node* node){
		// If the node visited contains a model, draw it
		Model* model = node->getModel();
		if (model)
		{
			model->draw();
		}//*/
		return true;
	}
	
	void GameHud::onMovePoint(int difX,int difY){
		float mx=(float)difX/20.0f;
		float my=(float)difY;
		//std::cout << mx << ", " << my << std::endl;
		Node* cueGroup=_gameController->getScene()->findNode("CueGroup");
		if (cueGroup!=NULL){
			cueGroup->rotateZ(mx);
			//cueGroup->rotateX(my);
		}
	}
	void GameHud::onMoveEffect(int difX,int difY){
		
	}
	void GameHud::onMoveShot(int difX,int difY){
		Node* cueGroup=_gameController->getScene()->findNode("CueGroup");
		if (cueGroup!=NULL){
			
		}
	}
	
	void GameHud::disable(){
		_hud->disable();
	}

	
	/**
	 * @brief register the user as the actual user controlling the game (checking that)
	 */
	void GameHud::registerPlayerRound(Players::DevicePlayer* player){
		if (_gameController->getPlayerActive()==player->getPlayer()){
			_playerController=player;
			Vector3 ballPosition=_gameController->getPlayerBall()->getTranslation();
			Node* cue=_playerController->getCue();
			cue->setTranslation(ballPosition);
			std::cout << cue << std::endl;
			std::cout << cue->getId() << std::endl;
			_gameController->getScene()->addNode(cue);
		}
	}
	
	void GameHud::exit(gameplay::Control::Listener::EventType){
		_controller->changeToScreen(new MainMenu(this->_controller));
	}
	
	void GameHud::cancelPause(gameplay::Control::Listener::EventType){
		_status=_oldStatus;
		_exit->disable();
		_hud->enable();
	}
	
	/*
	 * Actions
	 */
	void GameHud::actionLook(gameplay::Control::Listener::EventType){
		_status=LOOK;
	}
	void GameHud::actionPoint(gameplay::Control::Listener::EventType){
		_status=POINT;
	}
	void GameHud::actionEffect(gameplay::Control::Listener::EventType){
		_status=EFFECT;
	}
	void GameHud::actionShoot(gameplay::Control::Listener::EventType){
		_status=SHOT;
	}
	
	/*
	 * Views
	 */
	void GameHud::lookTop(gameplay::Control::Listener::EventType){
		_activeCamera=_gameController->getScene()->findNode("CameraTop")->getCamera();
		_gameController->getScene()->setActiveCamera(_activeCamera);
	}
	void GameHud::lookFree(gameplay::Control::Listener::EventType){
		_activeCamera=_gameController->getScene()->findNode("CameraFree")->getCamera();
		_gameController->getScene()->setActiveCamera(_activeCamera);
	}
	void GameHud::lookOverCue(gameplay::Control::Listener::EventType){
		Node* tmp=_gameController->getScene()->findNode("CameraCue");
		if (tmp!=NULL){
			_activeCamera=tmp->getCamera();
			_gameController->getScene()->setActiveCamera(_activeCamera);
		}
	}
	
	void GameHud::pause(gameplay::Control::Listener::EventType){
		_oldStatus=_status;
		_status=PAUSE;
		_exit->enable();
		_hud->disable();
	}
	
	void GameHud::startRuning(){
		
	}
	
}