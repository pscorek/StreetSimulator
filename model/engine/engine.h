#ifndef ENGINE_H
#define ENGINE_H

#include "objectspositionupdater.h"
#include "../../detection/cameradetectionimpl.h"
#include "../objectsonmap.h"
#include "../../detection/cameranoiseimpl.h"
#include "../database/database.h"
#include <chrono>
#include <thread>

class Engine
{
public:
    Engine(const ObjectsOnMap &ObjectsOnMap, ICameraNoise *iCameraNoise);
    ~Engine();
    
    void finish();//set stop flag

    void run(); //running engine
private:
    ObjectsPositionUpdater objectsPositionUpdater; //updated objects after new update in run
    ICameraDetection *iCameraDetection; //manager cameras
    const ObjectsOnMap &objectsOnMap; //cameras on the map
    Database database; //database
    //TODO referencja na widok
    
    bool finish_; //if true then stop calculations
    std::chrono::milliseconds startTime, endTime;
};

#endif // ENGINE_H
