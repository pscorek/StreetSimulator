#include "../model/objectsonmap.h"
#include <iostream>

ObjectsOnMap::ObjectsOnMap() : board(8)
{   //empty

}

ObjectsOnMap::~ObjectsOnMap()
{
    for(TrafficParticipant *obj: objects)
    {
        delete obj;
    }
    for(Camera *obj: cameras)
    {
        delete obj;
    }
}

void ObjectsOnMap::addPedestrian(Coordinates location, Position source, Position destination, float speed)
{   //done
    objects.push_back(new Pedestrian(location.first, location.second, speed, destination, source));
}

void ObjectsOnMap::addCar(Coordinates location, Position source, Position destination, float speed)
{   //done
    objects.push_back(new Car(location.first, location.second, speed, destination, source));
}

void ObjectsOnMap::addTruck(Coordinates location, Position source, Position destination, float speed)
{   //done
    objects.push_back(new Truck(location.first, location.second, speed, destination, source));
}

void ObjectsOnMap::addCamera(Coordinates location, float azimuth, float angle, float range)
{   //done
    cameras.push_back(new Camera(location.first, location.second, azimuth, angle, range));
    for (Camera* camera : cameras) {
        std::cout << camera->x_ << " " << camera->y_ << " " << camera->angle_ << std::endl;
    }
}

void ObjectsOnMap::setCellOnField(int i, int j, bool isStreet)
{
    board.boardMap_[i][j] = isStreet;
}

void ObjectsOnMap::deleteObject(Coordinates location, Position source, Position destinatios, float speed)
{
    //TODO
}

void ObjectsOnMap::replaceCamera(Coordinates oldCordinates, Coordinates newCordinates) {
    std::list<Camera*>::iterator i = cameras.begin();
    while (i != cameras.end())
    {
        //std::cout << (location.first - (*i)->x_) + (location.second - (*i)->y_) << std::endl;
        if (abs(oldCordinates.first - (*i)->x_) + (oldCordinates.second - (*i)->y_) < 0.01) {
            //std::cout << "Erasing " << (*i)->x_ << " " << (*i)->y_ << std::endl;
            (*i)->x_ = newCordinates.first;
            (*i)->y_ = newCordinates.second;
            break;
        }
        i++;
    }
    for (Camera* camera : cameras) {
        std::cout << camera->x_ << " " << camera->y_ << " " << camera->angle_ << std::endl;
    }
}


void ObjectsOnMap::deleteCamera(Coordinates location, float azimuth, float angle, float range)
{
    //cameras.push_back(new Camera(location.first, location.second, azimuth, angle, range));
    /*std::cout << "was " << cameras.empty() << std::endl;
    for (Camera* camera : cameras) {
        std::cout << camera->x_ << " " << camera->y_ << " " << camera->angle_ << std::endl;
    }*/

    //std::cout << "location" << location.first << " " << location.second << std::endl;

    std::list<Camera*>::iterator i = cameras.begin();
    while (i != cameras.end())
    {
        //std::cout << (location.first - (*i)->x_) + (location.second - (*i)->y_) << std::endl;
        if (abs(location.first - (*i)->x_) + (location.second - (*i)->y_) < 0.01) {
            //std::cout << "Erasing " << (*i)->x_ << " " << (*i)->y_ << std::endl;
            cameras.erase(i++);
        }
        else {
            i++;
        }
    }
    //for (Camera* camera : cameras) {

    //}
    //std::cout << "is" << std::endl;
    for (Camera* camera : cameras) {
        std::cout << camera->x_ << " " << camera->y_ << " " << camera->angle_ << std::endl;
    }
    //TODO
}

list<TrafficParticipant*> ObjectsOnMap::getObjects()
{
      return objects;
}

list<Camera*> ObjectsOnMap::getCameras()
{
    return cameras;
}

Board& ObjectsOnMap::getBoard()
{
    return board;
}
