#ifndef MODELIMPL_H
#define MODELIMPL_H

#include "imodel.h"
#include "objectsonmap.h"

class ModelImpl : public IModel
{
public:
    ModelImpl();
    virtual ~ModelImpl();

    Board& getBoard();
    void addCamera(Coordinates coordinates);
    void replaceCamera(Coordinates oldCoordinates, Coordinates newCoordinates);
    void removeCamera(Coordinates coordinates);

    void addTrafficObject(Position coordinates, ObjectType objectType);
    void replaceTrafficObject(Position oldCoordinates, Position newCoordinates);
    void removeTrafficObject(Position coordinates);

    void replaceDestination(Position oldCoordinates, Position newCoordinates, Position trafficObjectCoordinates);

private:
    ObjectsOnMap objectsOnMap_;
};

#endif // MODELIMPL_H
