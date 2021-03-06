#include "BillardMainClass.h"

#include "MainMenu.h"
#include "SelectGame.h"

// Declare our game instance
BillardMainClass game;

BillardMainClass::BillardMainClass()
    : _scene(NULL)
{
}

void BillardMainClass::initialize()
{
	/*_scene=Scene::create();
	
    Node* cameraNode = _scene->addNode("Camera");
    _cameraParent = _scene->addNode("CameraParent");
    _cameraParent->addChild(cameraNode);
    Camera* camera = Camera::createPerspective(45.0f, (float)getWidth() / (float)getHeight(), 0.25f, 1000.0f);
    cameraNode->setCamera(camera);
    cameraNode->setTranslation(0.0f, 0.0f, 40.0f);
    _scene->setActiveCamera(camera);
    SAFE_RELEASE(camera);//*/
	
	_scene = Scene::create();
    Node* cameraNode = _scene->addNode("Camera");
    _cameraParent = _scene->addNode("CameraParent");
    _cameraParent->addChild(cameraNode);
    Camera* camera = Camera::createPerspective(45.0f, (float)getWidth() / (float)getHeight(), 0.25f, 1000.0f);
    cameraNode->setCamera(camera);
    cameraNode->setTranslation(0.0f, 0.0f, 40.0f);
    _scene->setActiveCamera(camera);
    SAFE_RELEASE(camera);
	
	_screen= new Menus::MainMenu(this);
	
	_connector=new Utils::OnlineConnector();
}

void BillardMainClass::finalize()
{
    //SAFE_RELEASE(_scene);
	delete _screen;
	if (_oldScreen!=NULL)
		delete _oldScreen;
	
	delete _connector;
}

void BillardMainClass::update(float elapsedTime)
{
    // Rotate model
    //_scene->findNode("box")->rotateY(MATH_DEG_TO_RAD((float)elapsedTime / 1000.0f * 180.0f));
	_screen->update(elapsedTime);
}

void BillardMainClass::render(float elapsedTime)
{
    // Clear the color and depth buffers
    clear(CLEAR_COLOR_DEPTH, Vector4::zero(), 1.0f, 0);

	_screen->render(_scene);

    // Visit all the nodes in the scene for drawing
    //_scene->visit(this, &BillardMainClass::drawScene);
}

bool BillardMainClass::drawScene(Node* node)
{
    // If the node visited contains a model, draw it
    Model* model = node->getModel();
    if (model)
    {
        model->draw();
    }//*/
    return true;
}

void BillardMainClass::keyEvent(Keyboard::KeyEvent evt, int key)
{
	_screen->keyEvent(evt, key);
    if (evt == Keyboard::KEY_PRESS)
    {
        switch (key)
        {
        case Keyboard::KEY_ESCAPE:
            exit();
            break;
        }
    }
}

void BillardMainClass::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)
{
	_screen->touchEvent(evt, x, y, contactIndex);
    switch (evt)
    {
    case Touch::TOUCH_PRESS:
        break;
    case Touch::TOUCH_RELEASE:
        break;
    case Touch::TOUCH_MOVE:
        break;
    };
}

void BillardMainClass::changeToScreen(Menus::MenuInterface* newScreen){
	//std::cout << this << std::endl;
	//std::cout << _screen << std::endl;
	//delete _screen;
	if (_oldScreen!=NULL){
		delete _oldScreen;
	}
	_oldScreen=_screen;
	_oldScreen->disable();
	//delete _screen;
	//_screen->setForeground(false);
	_screen=newScreen;
	//_screen->setForeground(true);
	//_newScreen=newScreen;
}

Utils::OnlineConnector* BillardMainClass::getConnector(){
	return this->_connector;
}

