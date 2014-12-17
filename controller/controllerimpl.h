//Author: Bogdan Shkola
//Representing main controller implementation of the application.

#ifndef CONTROLLERIMPL_H
#define CONTROLLERIMPL_H

#include "icontroller.h"
#include "blockingqueue.h"
#include "../common/events/ievent.h"
#include "strategies/istrategy.h"
#include "../model/imodel.h"
#include "../view/iview.h"

class ControllerImpl : public IController
{
public:
    ControllerImpl(IModel* model, IView* view);
    virtual ~ControllerImpl();

    void start();
    void finish();

private:
    bool finish_;
    std::map<std::string, IStrategy*> map; // strategy maps which defines reaction on different events
};

#endif // CONTROLLERIMPL_H
