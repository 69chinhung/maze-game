#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <termios.h>
#include <vector>
#include "view.h"
#include "gameObject.h"

class Controller{

public:
       
    Controller(View&);
    void run();
private:
 bool checkCollision(const GameObject& obj1, const GameObject& obj2);
    bool checkWinCondition();
    void gameOver(bool win);
    void handleInput(int);
    void update();

    // Model
    std::vector<GameObject*> _objs;
GameObject* _player;
    GameObject* _exit;
    bool _gameActive;
    // View
    View& _view; 
};

static struct termios old_termios, new_termios;
void reset_terminal();
void configure_terminal();
int read_input();

#endif
