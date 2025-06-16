#include <iostream>
#include <ctime>
#include <thread>
#include <unistd.h>
#include <termios.h>

#include "environment.h"
#include "controller.h"
#include "gameObjectFactory.h"


Controller::Controller(View& view) : _view(view){
    GameObjectFactory object;
	_objs.push_back(object.createRedPlayer(0,0));//原點
	//下列為障礙物
	_objs.push_back(object.createBlueBox(2,2));
	_objs.push_back(object.createBlueBox(2,1));
	_objs.push_back(object.createBlueBox(2,0));
	_objs.push_back(object.createBlueBox(0,1));
	_objs.push_back(object.createBlueBox(0,2));
	_objs.push_back(object.createBlueBox(6,5));
	_objs.push_back(object.createBlueBox(8,9));
	_objs.push_back(object.createBlueBox(17,2));
	_objs.push_back(object.createBlueBox(16,2));
	_objs.push_back(object.createBlueBox(5,5));
	_objs.push_back(object.createBlueBox(5,6));
	_objs.push_back(object.createBlueBox(5,7));
	_objs.push_back(object.createBlueBox(1,7));
	_objs.push_back(object.createBlueBox(2,8));
	_objs.push_back(object.createBlueBox(3,9));
	_objs.push_back(object.createBlueBox(3,14));
	_objs.push_back(object.createBlueBox(4,15));
	_objs.push_back(object.createBlueBox(5,16));
	_objs.push_back(object.createBlueBox(5,17));
	_objs.push_back(object.createBlueBox(6,18));
	_objs.push_back(object.createBlueBox(6,19));
    _objs.push_back(object.createBlueBox(6,11));
	_objs.push_back(object.createBlueBox(5,12));
    _objs.push_back(object.createBlueBox(15,1));
	_objs.push_back(object.createBlueBox(14,2));
	_objs.push_back(object.createBlueBox(13,3));
	_objs.push_back(object.createBlueBox(12,4));
	_objs.push_back(object.createBlueBox(11,5));
	_objs.push_back(object.createBlueBox(6,0));
	_objs.push_back(object.createBlueBox(7,1));
	_objs.push_back(object.createBlueBox(8,2));
	_objs.push_back(object.createBlueBox(9,2));
    _objs.push_back(object.createBlueBox(16,9));
	_objs.push_back(object.createBlueBox(16,8));
	_objs.push_back(object.createBlueBox(16,10));
	_objs.push_back(object.createBlueBox(15,9));
	_objs.push_back(object.createBlueBox(17,9));
	_objs.push_back(object.createBlueBox(18,9));
	_objs.push_back(object.createBlueBox(19,9));
	_objs.push_back(object.createBlueBox(9,15));
	_objs.push_back(object.createBlueBox(9,14));
	_objs.push_back(object.createBlueBox(9,16));
	_objs.push_back(object.createBlueBox(8,15));
	_objs.push_back(object.createBlueBox(10,15));
	_objs.push_back(object.createBlueBox(11,15));
	_objs.push_back(object.createBlueBox(12,15));
	_objs.push_back(object.createBlueBox(12,10));
    _objs.push_back(object.createBlueBox(13,11));
	_objs.push_back(object.createBlueBox(14,12));
	_objs.push_back(object.createBlueBox(15,13));
	_objs.push_back(object.createBlueBox(16,14));
	_objs.push_back(object.createBlueBox(17,15));
	_objs.push_back(object.createBlueBox(18,16));
	_objs.push_back(object.createBlueBox(17,13));
	_objs.push_back(object.createBlueBox(18,12));
	_objs.push_back(object.createBlueBox(15,15));
	_objs.push_back(object.createBlueBox(14,16));
}

void Controller::run() {
    // initial setup
    std::cin.tie(0);
    std::ios::sync_with_stdio(0);
    configure_terminal();

    // init state
    int input = -1;
    clock_t start, end;
    
    // Main loop
    while (true) {
        start = clock();
        // game loop goes here
        input = read_input();

        // ESC to exit program
        if(input==27)break;

        this->handleInput(input);

        _view.resetLatest();
        for(GameObject* obj : _objs) 
        {

            obj->update();

            _view.updateGameObject(obj);
        }

        _view.render();
        
		GameObject* obj = _objs[0];  // 紅色是第一個物件
           if (!obj->getIcon().empty() && !obj->getIcon()[0].empty()) {
              if (obj->getIcon()[0][0].color == Color::RED &&
                   obj->getPosition().x() == 19 &&
                   obj->getPosition().y() == 19) {
                  std::cout << "You Win!" << std::endl;
                  break; // 退出遊戲
           }
    }


        end = clock();

        // frame rate normalization
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        if (time_taken > SPF) continue;
        int frameDelay = int((SPF - time_taken) * 1000); // 0.1 seconds
        if(frameDelay > 0) std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay)); // frame delay
    }

}

std::vector<GameObject*>& Controller::getObjects() {
    return _objs;
}

void Controller::handleInput(int keyInput){

    // If there is no input, do nothing.
    if(keyInput==-1)return;
	if(_objs.empty()) return;

    auto obj = _objs[0]; // 控制第一個物件
    Position pos = obj->getPosition();
	Position _prevPos = pos;       // 記錄移動前的位置

    switch (keyInput) {
        case 'w':
        case 'W':
            if (pos.y() > 0)
				pos.setY(pos.y() - 1);      
                obj->setPosition(pos);
            for (size_t i = 0; i < _objs.size(); ++i) {
                for (size_t j = i + 1; j < _objs.size(); ++j) {
                     if (_objs[i]->intersects(_objs[j])) {
                         _objs[i]->onCollision(_objs[j]);
                         _objs[j]->onCollision(_objs[i]);
                     }
                }
            }
			// 檢查紅色是否碰撞超過3次
           if (_objs[0]->getCollisionCount() >= 3) {
               std::cout << "You Lose!" << std::endl;
               exit(0);
           }
            break;
        case 's':
        case 'S':
            if (pos.y() < GAME_WINDOW_HEIGHT - 1)
				pos.setY(pos.y() + 1);
			    obj->setPosition(pos);
            for (size_t i = 0; i < _objs.size(); ++i) {
                for (size_t j = i + 1; j < _objs.size(); ++j) {
                     if (_objs[i]->intersects(_objs[j])) {
                         _objs[i]->onCollision(_objs[j]);
                          _objs[j]->onCollision(_objs[i]);
                     }
                }
			}
			// 檢查紅色是否碰撞超過3次
           if (_objs[0]->getCollisionCount() >= 3) {
               std::cout << "You Lose!" << std::endl;
               exit(0);
           }
            break;
        case 'a':
        case 'A':
            if (pos.x() > 0)
				pos.setX(pos.x() - 1);
			    obj->setPosition(pos);
            for (size_t i = 0; i < _objs.size(); ++i) {
                for (size_t j = i + 1; j < _objs.size(); ++j) {
                     if (_objs[i]->intersects(_objs[j])) {
                         _objs[i]->onCollision(_objs[j]);
                         _objs[j]->onCollision(_objs[i]);
                     }
                }
            }
			// 檢查紅色是否碰撞超過3次
           if (_objs[0]->getCollisionCount() >= 3) {
               std::cout << "You Lose!" << std::endl;
               exit(0);
           }
		   // 檢查紅色是否碰撞超過3次
          if (_objs[0]->getCollisionCount() >= 3) {
              std::cout << "You Lose!" << std::endl;
              exit(0);
          }
            break;
        case 'd':
        case 'D':
            if (pos.x() < GAME_WINDOW_WIDTH - 1)
				pos.setX(pos.x() + 1);
			    obj->setPosition(pos);
            for (size_t i = 0; i < _objs.size(); ++i) {
                for (size_t j = i + 1; j < _objs.size(); ++j) {
                    if (_objs[i]->intersects(_objs[j])) {
                        _objs[i]->onCollision(_objs[j]);
                        _objs[j]->onCollision(_objs[i]);
                    }
                }
            }
			// 檢查紅色是否碰撞超過3次
            if (_objs[0]->getCollisionCount() >= 3) {
                std::cout << "You Lose!" << std::endl;
                exit(0);
            }
            break;
        default:
            break;
	}
    // TODO 
    // handle key events.
}

void Controller::update(){

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

