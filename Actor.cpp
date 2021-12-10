#include "Actor.h"
#include <string>
#include <iostream>
using namespace std;

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp


Actor::Actor(StudentWorld* sw, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) : GraphObject(imageID, startX, startY, dir, size, depth) {
    m_world = sw;
    m_isAlive = true;
}

Actor::~Actor() {

}
bool Actor::isAlive() {
    return m_isAlive;
}
void Actor::setDead() {
    m_isAlive = false;
}


StudentWorld* Actor::getWorld() {
    return m_world;
}
//void Actor::setWorld(StudentWorld *world) {
//    m_world = world;
//}

Earth::Earth(StudentWorld* sw, int startX, int startY) : Actor(sw, TID_EARTH, startX, startY, right, .25, 3) {
    setVisible(true);
}
void Earth::doSomething() {
    return;
}
Earth::~Earth() {

}


Tunnelman::Tunnelman(StudentWorld* sw) : Actor(sw, TID_PLAYER, 30, 60, right, 1, 0) {
    setVisible(true);
    m_hp = 10;
    m_waterUnits = 5;
    m_numSonar = 1;
    m_numGold = 0;

}
Tunnelman::~Tunnelman() {

}

int Tunnelman::hp() const {
    return m_hp;
}
int Tunnelman::numWater() const {
    return m_waterUnits;
}
int Tunnelman::numSonar() const {
    return m_numSonar;
}
int Tunnelman::numGold() const {
    return m_numGold;
}

Boulder::Boulder(StudentWorld* sw, int startX, int startY) : Actor(sw, TID_BOULDER, startX, startY, down, 1, 1) {
    setVisible(true);
    m_state = stable;
    waitingNum = 30;
    //ID = TID_BOULDER;

}

Boulder::~Boulder() {
}

void Boulder::setState(string state) {
    m_state = state;
}

void Boulder::doSomething() {
    if (!isAlive()) {
        return;
    }
    int x = getX();
    int y = getY();
    //if it's stable, set to waiting.
    if (getState() == stable) {
        if (!getWorld()->isthereEarth(x, y - 1)) {
            setState(waiting);
        }
    }
    if (waitingNum == 0) {
        setState(falling);
        getWorld()->playSound(SOUND_FALLING_ROCK);
        waitingNum = -1;
    }

    if (getState() == falling) {
        // As long as there isn't earth below and y is valid we can move down
        // TODO: check for a bolder
        if (getWorld()->isBoulderthere(x, y - 1)) {
            getWorld()->unsetLocation(getX(), getY());
            getWorld()->setLocation(x, y - 1);
            setState(stable);
        }
        if (y == -1 || getWorld()->isthereEarth(x, y - 1)) {
            setDead();
        }
        if (!getWorld()->isthereEarth(x, y - 1)) {
            moveTo(x, y - 1);
        }
        getWorld()->unsetLocation(getX(), getY()); // made change here trying to unset the location when the thing moves
        // Need to figure out how to not run into other boulders. I think something like we had in Zion like nRobotsAt?? like a function to check if a boulder/object is at that location. Maybe it could take in a class type so we can template it for other classess???

    }
    // TODO: check if it's near a Protestor or Tunnelman & annoy them.
    // Decrement each tick if waiting to fall
    if (getState() == waiting) {
        waitingNum--;
    }
}
Goodies::Goodies(StudentWorld* sw, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) : Actor(sw, imageID, startX, startY, dir, size, depth) {

}
Goodies::~Goodies() {

}

Barrel::Barrel(StudentWorld* sw, int startX, int startY, Tunnelman* p) : Goodies(sw, TID_BARREL, startX, startY, right, 1, 2) {
    m_x = startX;
    m_y = startY;
    playerInGame = p;
    //count++;
}

void Barrel::doSomething() {
    if (!isAlive()) {
        return;
    }
    int x = playerInGame->getX();
    int y = playerInGame->getY();


    // If not foudn yet, if it's within 4 of tunnelman, found it
    if (found != true) {
        if (getX() - 4 <= x && x <= getX() + 4) {
            if (getY() - 4 <= y && y <= getY() + 4) {
                setVisible(true);
                found = true;
                return;
            }

        }
    }


    // If found, set Dead, play sound, increase score, decrement barrels
    else {
        if (m_x - 1 <= x && x <= m_x + 1) {
            if (m_y - 1 <= y && y <= m_y + 1) {
               
                getWorld()->playSound(SOUND_FOUND_OIL);
                getWorld()->increaseScore(1000);
                getWorld()->decrementBarrelCount();
                getWorld()->unsetLocationGoodies(m_x, m_y);
                setDead();
            }

        }
    }



}
void Barrel::makeVisible() {
    found = true;

}
Barrel::~Barrel() {
}
void Barrel::setState(string state) {
    m_state = state;
}

void Tunnelman::doSomething() {

    int ch;
    int x = getX();
    int y = getY();

    if (getWorld()->getKey(ch) == true)
    {
        // user hit a key this tick!
        switch (ch)
        {
        case KEY_PRESS_LEFT:
            if (this->getDirection() != left) {
                this->setDirection(left);
                break;
            }
            if (x != 0) {
                if (!getWorld()->isBoulderthere(x - 1, y)) {
                    moveTo(x - 1, y);
                }
            }

            break;
        case KEY_PRESS_RIGHT:
            if (this->getDirection() != right) {
                this->setDirection(right);
                break;
            }
            if (x != 60) {
                if (!getWorld()->isBoulderthere(x + 1, y)) {
                    moveTo(x + 1, y);
                }
               
                
            }
            break;
        case KEY_PRESS_UP:
            if (this->getDirection() != up) {
                this->setDirection(up);
                break;
            }

            if (y != 60) {
                if (!getWorld()->isBoulderthere(x, y + 1)) {
                    moveTo(x, y + 1);
                }
            }

            break;
        case KEY_PRESS_DOWN:
            if (this->getDirection() != down) {
                this->setDirection(down);
                break;
            }
            if (y != 0) {
                if (!getWorld()->isBoulderthere(x, y - 1)) {
                    moveTo(x, y - 1);
                }
            }
            break;
        case KEY_PRESS_SPACE:

            break;
        case KEY_PRESS_ESCAPE:
            setDead();
            break;
        case none:
            return;
            // etcÖ
        }
        //        Direction d = getDirection();
        //        int x = getX();
        //        int y = getY();

        if (getWorld()->isthereEarth(getX(), getY())) {
            getWorld()->digField(getX(), getY());
            getWorld()->playSound(SOUND_DIG);

        }

    }
}
//void Tunnelman::getLocation() {
//    x = getX();
//    y = getY();
//}