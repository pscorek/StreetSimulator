#ifndef CLOSEWINDOWSTRATEGY_H
#define CLOSEWINDOWSTRATEGY_H

#include "istrategy.h"
#include <string>
#include "../../controller/controllerimpl.h"

class CloseWindowStrategy : public IStrategy
{
public:
    CloseWindowStrategy(IController& controller);
    void perform(IEvent* event);

private:
    IController* controller_;
};

#endif // CLOSEWINDOWSTRATEGY_H