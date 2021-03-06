//Author: Bogdan Shkola
//Implementation of ObjectsOnMap class
#include "../model/objectsonmap.h"
#include <cmath>

ObjectsOnMap::ObjectsOnMap() : board(8) {
}

ObjectsOnMap::~ObjectsOnMap() {
    for(TrafficParticipant *obj: objects)
    {
        delete obj;
    }
    for(Camera *obj: cameras)
    {
        delete obj;
    }
}

void ObjectsOnMap::resizeBoard(int newSize) {
    objects.clear();
    cameras.clear();
    board = Board(newSize);
}

void ObjectsOnMap::addStreet(Position coordinates) {
    board.boardMap_[coordinates.first][coordinates.second] = true;
}

void ObjectsOnMap::removeStreet(Position coordinates) {
    board.boardMap_[coordinates.first][coordinates.second] = false;
}

void ObjectsOnMap::addTrafficObject(int id, Position location, ObjectType objectType) {
    float speed = 1;

    switch (objectType) {
    case PEDESTRIAN:
        objects.push_back(new Pedestrian(id, speed, location, location));
        break;
    case CAR:
        objects.push_back(new Car(id, speed, location, location));
        break;
    case TRUCK:
        objects.push_back(new Truck(id, speed, location, location));
        break;
    default:
        throw WrongIdObjectException("wrong id object on map, the object with this id doesn't exist");
    }
}

void ObjectsOnMap::replaceTrafficObject(int id, Position newLocation) {
    for (TrafficParticipant* trafficParticipant : objects) {
        if (trafficParticipant->id_ == id) {
            trafficParticipant->x_ = newLocation.first;
            trafficParticipant->y_ = newLocation.second;
            //resert target and start points
            trafficParticipant->targetPoint_.first +=  newLocation.first - trafficParticipant->startPoint_.first ;
            trafficParticipant->targetPoint_.second += newLocation.second - trafficParticipant->startPoint_.second;
            trafficParticipant->startPoint_ = newLocation; //resert start point
            return;
        }
    }
    throw WrongIdObjectException("wrong id object on map, the object with this id doesn't exist");
}

void ObjectsOnMap::deleteTrafficObject(int id) {
    for (TrafficParticipant* trafficParticipant : objects) {
        if (trafficParticipant->id_ == id) {
            objects.remove(trafficParticipant);
            return;
        }
    }
    throw WrongIdObjectException("wrong id object on map, the object with this id doesn't exist");
}

void ObjectsOnMap::addCamera(int id, Coordinates location) {
    cameras.push_back(new Camera(id, location.first, location.second, 0.0, 30.0, 1.0));
}

void ObjectsOnMap::replaceCamera(int id, Coordinates newCordinates) {
    for (Camera* camera : cameras) {
        if (camera->id_ == id) {
            camera->x_ = newCordinates.first;
            camera->y_ = newCordinates.second;
            return;
        }
    }
    throw WrongIdObjectException("wrong id object on map, the object with this id doesn't exist");
}

CameraOptions ObjectsOnMap::getCameraOptions(int cameraId) {
    for (Camera* camera : cameras) {
        if (camera->id_ == cameraId) {
            return CameraOptions(camera->angle_, camera->azimuth_, camera->range_);
        }
    }
    throw WrongIdObjectException("wrong id object on map, the object with this id doesn't exist");
}


void ObjectsOnMap::deleteCamera(int id) {
    for (Camera* camera : cameras) {
        if (camera->id_ == id) {
            cameras.remove(camera);
            return;
        }
    }
    throw WrongIdObjectException("wrong id object on map, the object with this id doesn't exist");
}

void ObjectsOnMap::changeCameraOptions(int cameraId, const CameraOptions& cameraOptions) {
    for (Camera* camera : cameras) {
        if (camera->id_ == cameraId) {
            camera->angle_ = cameraOptions.getAngle();
            camera->azimuth_ = cameraOptions.getDirection();
            camera->range_ = cameraOptions.getRange();
            return;
        }
    }
    throw WrongIdObjectException("wrong id object on map, the object with this id doesn't exist");
}


void ObjectsOnMap::replaceDestination(int trafficObjectId, Position newCoordinates) {
    for (TrafficParticipant* trafficParticipant : objects) {
        if (trafficParticipant->id_ == trafficObjectId) {
            trafficParticipant->targetPoint_ = newCoordinates;
            return;
        }
    }
    throw WrongIdObjectException("wrong id object on map, the object with this id doesn't exist");
}

const std::list<TrafficParticipant*> &ObjectsOnMap::getObjects() const {
    return objects;
}

std::list<Camera*> ObjectsOnMap::getCameras() const {
    return cameras;
}

const Board &ObjectsOnMap::getBoard() const {
    return board;
}

Board &ObjectsOnMap::getBoard() {
    return board;
}
