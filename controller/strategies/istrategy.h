//Author: Bogdan Shkola
//Representing strategy interface. Every strategy implementation must inherit this interface.

#ifndef ISTRATEGY_H
#define ISTRATEGY_H

#include <iostream>
#include <memory>
#include "../../common/events/ievent.h"
#include "../../model/imodel.h"
#include "../../view/iview.h"

class IStrategy
{
public:
    IStrategy();
    virtual ~IStrategy() {}
    virtual void perform(std::shared_ptr<IEvent> event) = 0; // defines how strategy should react when it is launched
};

#endif // ISTRATEGY_H
