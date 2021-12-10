#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
class GraphObject;
class Earth;
class Tunnelman;
class Actor;
/// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    ~StudentWorld();

    void digField(int x, int y);
    bool isthereEarth(int x, int y);
    virtual int init();
    bool isBoulderthere(int xPos, int yPos);
    void setLocation(int xPos, int yPos);
    void setDisplayText();
    void decrementBarrelCount();
    void unsetLocation(int xPos, int yPos);
    virtual int move();
    void setLocationGoodies(int xPos, int yPos);
    void unsetLocationGoodies(int xPos, int yPos);
    bool isBarrelthere(int xPos, int yPos);
    double eDistance(double x, double y, double x2, double y2);


    virtual void cleanUp();

private:
    Tunnelman* player;
    Earth* earthPtrs[VIEW_WIDTH][VIEW_HEIGHT];
    std::vector<Actor*> actorPtrs;
    bool BoulderPtrs[VIEW_WIDTH][VIEW_HEIGHT];
    bool GoodiePtrs[VIEW_WIDTH][VIEW_HEIGHT];
    //Actor* actorLocation[VIEW_WIDTH][VIEW_HEIGHT];
    int barrelCount = 0;
    int tick = 0;
};

#endif // STUDENTWORLD_H_