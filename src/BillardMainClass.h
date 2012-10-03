#ifndef TEMPLATEGAME_H_
#define TEMPLATEGAME_H_


class BillardMainClass;


#include "gameplay.h"
#include "MenuAbstract.h"

using namespace gameplay;

/**
 * Main game class.
 */
class BillardMainClass: public gameplay::Game
{
public:

    /**
     * Constructor.
     */
    BillardMainClass();

    /**
     * @see Game::keyEvent
     */
	void keyEvent(Keyboard::KeyEvent evt, int key);
	
    /**
     * @see Game::touchEvent
     */
    void touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);
	
	void changeToScreen(Menus::MenuInterface* newScreen);

protected:

    /**
     * @see Game::initialize
     */
    void initialize();

    /**
     * @see Game::finalize
     */
    void finalize();

    /**
     * @see Game::update
     */
    void update(float elapsedTime);

    /**
     * @see Game::render
     */
    void render(float elapsedTime);

private:

    /**
     * Draws the scene each frame.
     */
    bool drawScene(Node* node);

    Scene* _scene;
	Node* _cameraParent;
	Menus::MenuInterface* _screen, *_oldScreen, *_newScreen;
};


#endif
