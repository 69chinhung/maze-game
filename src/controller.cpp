#include "controller.h"
#include "gameObjectFactory.h"
#include "environment.h"
#include "iconFactory.h"
#include "AnsiPrint.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <chrono>  
#include <thread>  



Controller::Controller(View& view) : _view(view), _gameActive(true) {
    
    _player = new GameObject(IconFactory::NxMColor(Size(1,1), BLUE), Position(1, 1));  
    _objs.push_back(_player);
    
    
    _exit = new GameObject(IconFactory::NxMColor(Size(1,1), GREEN), Position(GAME_WINDOW_WIDTH-2, GAME_WINDOW_HEIGHT-2));
    _objs.push_back(_exit);
    
    
    for (int i = 0; i < GAME_WINDOW_WIDTH; i++) {
        _objs.push_back(new GameObject(IconFactory::NxMColor(Size(1,1), RED), Position(i, 0)));  
        _objs.push_back(new GameObject(IconFactory::NxMColor(Size(1,1), RED), Position(i, GAME_WINDOW_HEIGHT-1)));  
    }
    for (int j = 1; j < GAME_WINDOW_HEIGHT-1; j++) {
        _objs.push_back(new GameObject(IconFactory::NxMColor(Size(1,1), RED), Position(0, j)));  
        _objs.push_back(new GameObject(IconFactory::NxMColor(Size(1,1), RED), Position(GAME_WINDOW_WIDTH-1, j)));  
    }
    

    for (int i = 1; i <8; i++) {
        _objs.push_back(new GameObject(IconFactory::NxMColor({1,1}, RED), Position{i, 5}));
    }
    
	 for (int i = 10; i <20; i++) {
         _objs.push_back(new GameObject(IconFactory::NxMColor({1,1}, RED), Position{i, 5}));
      }
 
    for (int j = 1; j < 8; j++) {
        _objs.push_back(new GameObject(IconFactory::NxMColor({1,1}, RED), Position{10, j}));
    }
	for (int j = 10; j < 20; j++) {
         _objs.push_back(new GameObject(IconFactory::NxMColor({1,1}, RED), Position{10, j}));
      }
	 
    
    for (int i = 1; i < 15; i++) {
        _objs.push_back(new GameObject(IconFactory::NxMColor({1,1}, RED), Position{i, 12}));
    }
	 for (int i = 17; i < 20; i++) {
          _objs.push_back(new GameObject(IconFactory::NxMColor({1,1}, RED), Position{i, 12}));
      }
}

void Controller::run() {
    
    std::cin.tie(0);
    std::ios::sync_with_stdio(0);
    configure_terminal();

    
    int input = -1;
    clock_t start, end;
    
    // Main loop
    while (_gameActive) {
        start = clock();
        input = read_input();

        // ESC to exit program
        if(input == 27) break;

        this->handleInput(input);
        this->update();

        _view.resetLatest();
        for(GameObject* obj : _objs) {
            _view.updateGameObject(obj);
        }

        _view.render();
        
    
        if (checkWinCondition()) {
            gameOver(true);
            break;
        }
        
        end = clock();
        // frame rate normalization
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        if (time_taken > SPF) continue;
        int frameDelay = int((SPF - time_taken) * 1000);
        if(frameDelay > 0) std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay));
    }

    reset_terminal();
}

void Controller::handleInput(int keyInput) {
    if(keyInput == -1 || !_gameActive) return;
    
    if(keyInput == 'w' || keyInput == 'W') {
        _player->setDirection(UP);
    } else if(keyInput == 'a' || keyInput == 'A') {
        _player->setDirection(LEFT);
    } else if(keyInput == 's' || keyInput == 'S') {
        _player->setDirection(DOWN);
    } else if(keyInput == 'd' || keyInput == 'D') {
        _player->setDirection(RIGHT);
    }
}

void Controller::update() {
    if (!_gameActive) return;
    
    
    Position oldPos = _player->getPosition();
    
    
    _player->update();
    
    
    Position newPos = _player->getPosition();
    for (auto obj : _objs) {
        if (obj != _player && obj != _exit) {
            Position objPos = obj->getPosition();
            if (newPos.x() == objPos.x() && newPos.y() == objPos.y()) {
                gameOver(false);
                _player->setPosition(oldPos);
                return;
            }
        }
    }
}

bool Controller::checkCollision(const GameObject& obj1, const GameObject& obj2) {
    return obj1.getPosition().x() == obj2.getPosition().x() && 
           obj1.getPosition().y() == obj2.getPosition().y();
}

bool Controller::checkWinCondition() {
    return checkCollision(*_player, *_exit);
}

void Controller::gameOver(bool win) {
    _gameActive = false;
    std::cout << "\033[2J\033[H";
if (win) {
        _view.displayMessage("YOU WIN!", GREEN, BLACK, true, false);
    } else {
        _view.displayMessage("GAME OVER!", RED, BLACK, true, false);
    }

}
void reset_terminal() {
    printf("\e[m"); // reset color changes
    printf("\e[?25h"); // show cursor
    fflush(stdout);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

// terminal initial configuration setup
void configure_terminal() {
    tcgetattr(STDIN_FILENO, &old_termios);
	new_termios = old_termios; // save it to be able to reset on exit
    
    new_termios.c_lflag &= ~(ICANON | ECHO); // turn off echo + non-canonical mode
    new_termios.c_cc[VMIN] = 0;
    new_termios.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    printf("\e[?25l"); // hide cursor
    std::atexit(reset_terminal);
}


int read_input() {
    fflush(stdout);
   	char buf[4096]; // maximum input buffer
	int n = read(STDIN_FILENO, buf, sizeof(buf));
    return n > 0 ? buf[n - 1] : -1;
}

