//
//  GameHub.cpp
//  BillardOnline3D
//
//  Created by Dracks on 01/10/12.
//
//

#include "GameHud.h"
#include "MainMenu.h"
#include "String_extras.h"

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
	float getMovement(float diff);
	
	float getMovement(float diff){
		return diff/50.0f;
	}
	
	GameHud::GameHud(::BillardMainClass* base, ::Game::AbstractGameController* gameController):Menus::MenuInterface(base) {
		_hudActions=NULL;
		_hudViews=NULL;
		_gameController=gameController;
		_status=WAIT;
		
		_activeCamera=_gameController->getScene()->getActiveCamera();
		_drawStatus=0;
		
		
		_gameController->setGameHud(this);
		
		_optionShowing=-1;
		_newOptionShowing=-1;
		
		//Scene* scena=_gameController->getScene();
		//_topCamera=scena->findNode("CameraTop")->getCamera();
		//_freeCamera=scena->findNode("CameraFree")->getCamera();
		//scena->setActiveCamera(_topCamera);
	}
	
	GameHud::~GameHud(){
		if (_hudActions!=NULL){
			SAFE_RELEASE(_hudActions);
			SAFE_RELEASE(_hudViews);
			SAFE_RELEASE(_hudEndGame);
			SAFE_RELEASE(_hudScore);
			SAFE_RELEASE(_exit);
			
			for (unsigned int i=0; i<_listActionsButton.size(); i++){
				SAFE_RELEASE(_listActionsButton[i]);
			}
		}
	}
	
	void GameHud::keyEvent(Keyboard::KeyEvent evt, int key){
		if (evt==Keyboard::KEY_PRESS){
			bool match=true;
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
					match=false;
					break;
			}
			/*if ((_status==LOOK || _status==SHOT || _status==EFFECT || _status==POINT) && not match){
				switch (key) {
					case Keyboard::KEY_S:
						_status=SHOT;
						break;
					case Keyboard::KEY_P:
						_status=POINT;
						break;
					case Keyboard::KEY_E:
						_status=EFFECT;
						break;
					case Keyboard::KEY_L:
						_status=LOOK;
						break;
						
					default:
						break;
				}
			}*/
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
							break;
						case PLACE_BALL:
							this->onMoveBall(difX, difY);
							break;
						default:
							break;
					}
					_oldX=x;
					_oldY=y;
					break;
				case Touch::TOUCH_PRESS:
					_oldX=x;
					_oldY=y;
					_oldTimeMove=_controller->getAbsoluteTime();
					break;

				default:
					break;
			}
		}
	}
	
	void GameHud::update(float timeElapsed){
		if (_hudViews==NULL){
			_hudActions = Form::create("res/menus/GameHud.form#ActionButtons");
			_hudActions->setConsumeInputEvents(false);
			
			((Button*) _hudActions->getControl("look"))->addListener(kNewSelector(&GameHud::actionLook), Control::Listener::CLICK);
			((Button*) _hudActions->getControl("point"))->addListener(kNewSelector(&GameHud::actionPoint), Control::Listener::CLICK);
			((Button*) _hudActions->getControl("effect"))->addListener(kNewSelector(&GameHud::actionEffect), Control::Listener::CLICK);
			((Button*) _hudActions->getControl("shoot"))->addListener(kNewSelector(&GameHud::actionShoot), Control::Listener::CLICK);
			
			_listActionsButton.push_back((Button*)_hudActions->getControl("placeBall"));
			_listActionsButton.push_back((Button*)_hudActions->getControl("look"));
			_listActionsButton.push_back((Button*)_hudActions->getControl("point"));
			_listActionsButton.push_back((Button*)_hudActions->getControl("effect"));
			_listActionsButton.push_back((Button*)_hudActions->getControl("shoot"));
			
			
			_hudHidden = Form::create("res/menus/GameHud.form#ActionButtons");
			_hudHidden->setConsumeInputEvents(false);
			_hudHidden->disable();
			/*//_hudHidden->setAutoWidth(false);
			_hudHidden->setAutoWidth(false);
			_hudHidden->setAutoHeight(false);
			_hudHidden->setSize(0, 0);
			*/
			for (unsigned int i=0; i<_listActionsButton.size(); i++){
				_listActionsButton[i]->addRef();
				_hudActions->removeControl(_listActionsButton[i]);
				_hudHidden->removeControl((unsigned int)0);
			}
			
			//_listActionsButton.push_back((Button*)_hudActions->getControl("placeBall"));
			
			
			//((Button*) _hud->getControl("pause"))->addListener(kNewSelector(&GameHud::pause), Control::Listener::CLICK);
			
			/*_hudPlaceBall = Form::create("res/menus/GameHud.form#PlaceBall");
			_hudPlaceBall->setConsumeInputEvents(false);
			
			((Button*) _hudActions->getControl("pause"))->addListener(kNewSelector(&GameHud::pause), Control::Listener::CLICK);
			((Button*) _hudPlaceBall->getControl("placeBallOk"))->addListener(kNewSelector(&GameHud::actionPlaceBall), Control::Listener::CLICK);*/
			
			_hudViews = Form::create("res/menus/GameHud.form#ViewButtons");
			_hudViews->setConsumeInputEvents(false);
			
			((Button*) _hudViews->getControl("free"))->addListener(kNewSelector(&GameHud::lookFree), Control::Listener::CLICK);
			((Button*) _hudViews->getControl("top"))->addListener(kNewSelector(&GameHud::lookTop), Control::Listener::CLICK);
			((Button*) _hudViews->getControl("cue"))->addListener(kNewSelector(&GameHud::lookOverCue), Control::Listener::CLICK);
			((Button*) _hudViews->getControl("pause"))->addListener(kNewSelector(&GameHud::pause), Control::Listener::CLICK);
			
			_hudScore = Form::create("res/menus/GameHud.form#ScoreView");
			_hudScore->setConsumeInputEvents(false);
			_scorePlayer1=(Label*)_hudScore->getControl("scorePlayer1");
			_scorePlayer2=(Label*)_hudScore->getControl("scorePlayer2");
			
			_hudEndGame = Form::create("res/menus/GameHud.form#EndGame");
			_hudEndGame->setConsumeInputEvents(false);
			_hudEndGame->disable();
			
			((Button*) _hudEndGame->getControl("exit"))->addListener(kNewSelector(&GameHud::exit), Control::Listener::CLICK);
			((Button*) _hudEndGame->getControl("replay"))->addListener(kNewSelector(&GameHud::replay), Control::Listener::CLICK);
			
			_exit = Form::create("res/menus/ExitAsk.form");
			_exit->setConsumeInputEvents(false);
			_exit->disable();
			
			((Button*) _exit->getControl("exit"))->addListener(kNewSelector(&GameHud::exit), Control::Listener::CLICK);
			((Button*) _exit->getControl("cancel"))->addListener(kNewSelector(&GameHud::cancelPause), Control::Listener::CLICK);
			
			_newOptionShowing=1;

			/*if (_status==PLACE_BALL){
				_hudActions->disable();
			} else {
				_hudPlaceBall->disable();
			}*/
		}
		/*if (!_isMoving){
			_oldTimeMove=_controller->getAbsoluteTime();
		} else {
			_isMoving=false;
		}*/
		
		if (_newOptionShowing!=_optionShowing){
			printf("status: %d newOption: %d\n", _status, _newOptionShowing);
			this->refreshActionButtons(_newOptionShowing);
		}
		
		
		_hudViews->update(timeElapsed);
		_hudActions->update(timeElapsed);
		//_hudPlaceBall->update(timeElapsed);
		_hudHidden->update(timeElapsed);
		_hudScore->update(timeElapsed);
		_exit->update(timeElapsed);
		_gameController->update(timeElapsed);
		_hudEndGame->update(timeElapsed);

		
	}
	
	void GameHud::render(gameplay::Scene*){
		if (_gameController!=NULL){
			if (_drawStatus<2)
				_gameController->getScene()->visit(this, &GameHud::drawScene);
			if (_drawStatus>0)
				_controller->getPhysicsController()->drawDebug(_gameController->getScene()->getActiveCamera()->getViewProjectionMatrix());
			Vector3 p=_gameController->getPlayerBall()->getTranslation();
			//std::cout << p.x << "," << p.y << "," << p.z << std::endl;
			//p=_playerController->getCue()->getTranslation();
			//std::cout << "Cue: " << p.x << "," << p.y << "," << p.z << std::endl;
			
		}
		
		if (_status==PAUSE){
			_exit->draw();
		} else {
			_hudViews->draw();
			_hudScore->draw();
			_hudHidden->draw();
			_hudActions->draw();
			/*if (_status==LOOK || _status==SHOT || _status==EFFECT || _status==POINT || _status==PLACE_BALL){
				_hudActions->draw();
			} else*/
			if (_status==END){
				_hudEndGame->draw();
			}
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
		float mx=getMovement((float) difX);
		//std::cout << mx << ", " << my << std::endl;
		Node* cueGroup=_gameController->getScene()->findNode("CueGroup");
		if (cueGroup!=NULL){
			cueGroup->rotateZ(mx);
			//cueGroup->rotateX(my);
		}
	}
	void GameHud::onMoveEffect(int difX,int difY){
		float mx=getMovement(difX);
		float my=getMovement(difY);
		
		Node* cueGroup=_gameController->getScene()->findNode("CueGroup");
		if (cueGroup!=NULL){
			cueGroup->translateUp(mx);
			cueGroup->translateForward(my);
		}
	}
	void GameHud::onMoveShot(int difX,int difY){
		Node* cueGroup=_gameController->getScene()->findNode("Cue");
		if (cueGroup!=NULL){
			float my=getMovement(difY);
			_isMoving=true;
			double time=_controller->getAbsoluteTime();
			
			_playerController->setCueVelocity(my/(time-_oldTimeMove));
			_oldTimeMove=time;
			
			Vector3 direction=cueGroup->getBackVector()*my;
			cueGroup->translate(direction);
		}
	}
	
	void GameHud::onMoveBall(int difX,int difY){
		_ballOut->translate(difX/500.0f, -difY/500.0f, 0);
	}
	
	void GameHud::disable(){
		_hudActions->disable();
		_hudViews->disable();
		//_hudPlaceBall->disable();
		_exit->disable();
	}
	
	/**
	 * @brief register the user as the actual user controlling the game (checking that)
	 */
	void GameHud::registerPlayerRound(Players::DevicePlayer* player){
		if (_gameController->getPlayerActive()==player->getPlayer()){
			if (player==_playerController){
				Label* score=NULL;
				std::string playerStr;
				if (player->getPlayer()==0){
					playerStr="Player 1: ";
					score=_scorePlayer1;
				} else {
					score=_scorePlayer2;
					playerStr="Player 2: ";
				}
				std::string result=playerStr+utils::NumberToString<int>(player->getPoints());
				score->setText(result.c_str());
			} else {
				_playerController=player;
			}
			this->nextStepPlayer();
			if (_status==LOOK){
				_newOptionShowing=1;
			} else {
				_newOptionShowing=0;
			}
		}
	}
	
	void GameHud::nextStepPlayer(){
		Node* ballOut=_gameController->getOutBall();
		if (ballOut!=NULL){
			PhysicsRigidBody* body=((PhysicsRigidBody*)ballOut->getCollisionObject());
			body->setKinematic(true);
			body->setLinearVelocity(0, 0, 0);
			body->setAngularVelocity(0, 0, 0);
			ballOut->setTranslation(0, 0, 0);
			_ballOut=ballOut;
			
			_status=PLACE_BALL;
		} else {
			Vector3 ballPosition=_gameController->getPlayerBall()->getTranslation();
			if (_status!=END){
				Node* cueGroup=_playerController->getCue();
				cueGroup->setTranslation(ballPosition);
				//std::cout << cue << std::endl;
				//std::cout << cue->getId() << std::endl;
				_gameController->getScene()->addNode(cueGroup);
				//if (cue->getCollisionObject()!=NULL)
				cueGroup->findNode("Cue")->getCollisionObject()->setEnabled(true);
				_status=LOOK;
			if (_hudActions!=NULL)
				_hudActions->enable();
			} else {
				_hudEndGame->enable();
			}
		}

	}
	
	void GameHud::startRuning(){
		if (strcmp(_activeCamera->getNode()->getId(), "CameraCue")==0){
			this->lookTop(Control::Listener::CLICK);
		}
		_status=RUNING;
		_newOptionShowing=-1;
	}
	
	void GameHud::endGame(){
		_status=END;
		std::string title;
		std::string text;
		if (dynamic_cast<Players::DevicePlayer*>(_playerController)){
			title="Winner!";
		} else {
			title="GameOver!";
		}
		text="Player ";
		text+=utils::NumberToString<int>(_playerController->getPlayer()+1)+" win the match!";
		((Label*)_hudEndGame->getControl("title"))->setText(title.c_str());
		((Label*)_hudEndGame->getControl("text"))->setText(text.c_str());
	}
	
	/*
	 * Interface Action administration
	 */
	void GameHud::refreshActionButtons(int option){
		if (_optionShowing>-1){
			_hudActions->update(0.001f);
			if (_optionShowing==0){
				_listActionsButton[0]->setAlignment(Control::ALIGN_TOP_RIGHT);
				_listActionsButton[1]->setAlignment(Control::ALIGN_TOP_RIGHT);
				_hudActions->removeControl(_listActionsButton[0]);
				_hudActions->removeControl(_listActionsButton[1]);
				_listActionsButton[0]->disable();
				_listActionsButton[1]->disable();
				//_hudHidden->addControl(_listActionsButton[0]);
				//_hudHidden->addControl(_listActionsButton[1]);
			} else {
				int ini=_optionShowing-1;
				int end=_optionShowing+2;
				if (ini==0){
					ini=1;
				}
				if (end>_listActionsButton.size()){
					end=_listActionsButton.size();
				}
				for (int i=ini; i<end; i++){
					_listActionsButton[i]->setAlignment(Control::ALIGN_TOP_RIGHT);
					_listActionsButton[i]->disable();
					_hudActions->removeControl(_listActionsButton[i]);
					//_hudHidden->addControl(_listActionsButton[i]);
				}
			}
		}
		//assert(option>=0);
		if (_hudActions!=NULL && option>0){
			_optionShowing=option;
			if (option==0){
				_hudActions->addControl(_listActionsButton[0]);
				_listActionsButton[0]->setAlignment(Control::ALIGN_BOTTOM_HCENTER);
				
				_hudActions->addControl(_listActionsButton[1]);
				_listActionsButton[1]->setAlignment(Control::ALIGN_BOTTOM_RIGHT);
				_listActionsButton[0]->enable();
				_listActionsButton[1]->enable();
			} else if (option==1){
				_hudActions->addControl(_listActionsButton[1]);
				_listActionsButton[1]->setAlignment(Control::ALIGN_BOTTOM_HCENTER);
				
				_hudActions->addControl(_listActionsButton[2]);
				_listActionsButton[2]->setAlignment(Control::ALIGN_BOTTOM_RIGHT);
				
				_listActionsButton[1]->enable();
				_listActionsButton[2]->enable();
			} else if (option==_listActionsButton.size()-1){
				_hudActions->addControl(_listActionsButton[option-1]);
				_listActionsButton[option-1]->setAlignment(Control::ALIGN_BOTTOM_LEFT);
				
				_hudActions->addControl(_listActionsButton[option]);
				_listActionsButton[option]->setAlignment(Control::ALIGN_BOTTOM_HCENTER);
				
				_listActionsButton[option-1]->enable();
				_listActionsButton[option]->enable();
			} else {
				_hudActions->addControl(_listActionsButton[option-1]);
				_listActionsButton[option-1]->setAlignment(Control::ALIGN_BOTTOM_LEFT);
				
				_hudActions->addControl(_listActionsButton[option]);
				_listActionsButton[option]->setAlignment(Control::ALIGN_BOTTOM_HCENTER);
				
				_hudActions->addControl(_listActionsButton[option+1]);
				_listActionsButton[option+1]->setAlignment(Control::ALIGN_BOTTOM_RIGHT);
				
				_listActionsButton[option-1]->enable();
				_listActionsButton[option]->enable();
				_listActionsButton[option+1]->enable();
			}
		}
		//_newOptionShowing=option;
		std::vector<gameplay::Control*> listControls=_hudActions->getControls();
		for (unsigned int i=0; i<listControls.size(); i++){
			printf("Controlador: %s \n", listControls[i]->getId());
		}
	}
	/*void GameHud::showPreviousAction(){
		
	}//*/
	
	/*
	 * Ask Exit Methods and End Methods
	 */
	
	void GameHud::exit(gameplay::Control::Listener::EventType){
		_controller->changeToScreen(new MainMenu(this->_controller));
	}
	
	void GameHud::cancelPause(gameplay::Control::Listener::EventType){
		_status=_oldStatus;
		_exit->disable();
		_hudViews->enable();
		if (_status==LOOK || _status==SHOT || _status==EFFECT || _status==POINT || _status==PLACE_BALL){
			_hudActions->enable();
		}
	}
	
	void GameHud::replay(gameplay::Control::Listener::EventType){
		
	}
	
	/*
	 * Actions
	 */
	void GameHud::actionLook(gameplay::Control::Listener::EventType){
		if (_status==PLACE_BALL){
			((PhysicsRigidBody*)_ballOut->getCollisionObject())->setKinematic(false);
			_ballOut=NULL;
			//_hudPlaceBall->disable();
			this->nextStepPlayer();
		}
		_newOptionShowing=1;
		_status=LOOK;
	}
	void GameHud::actionPoint(gameplay::Control::Listener::EventType){
		_newOptionShowing=2;
		_status=POINT;
	}
	void GameHud::actionEffect(gameplay::Control::Listener::EventType){
		_newOptionShowing=3;
		_status=EFFECT;
	}
	void GameHud::actionShoot(gameplay::Control::Listener::EventType){
		_newOptionShowing=4;
		_status=SHOT;
	}
	void GameHud::actionPlaceBall(gameplay::Control::Listener::EventType){}
	
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
		_hudViews->disable();
		//_hudPlaceBall->disable();
		_hudViews->disable();
	}
	
}
