//Author: Bogdan Shkola
//Implementation of TrafficObjectRemovedStrategy class
#include "../../controller/strategies/trafficobjectremovedstrategy.h"
#include "../../common/events/trafficobjectremovedevent.h"

TrafficObjectRemovedStrategy::TrafficObjectRemovedStrategy(std::shared_ptr<IModel> model, IView* view) : model_(model), view_(view) {
}

TrafficObjectRemovedStrategy::~TrafficObjectRemovedStrategy() {
}

void TrafficObjectRemovedStrategy::perform(std::shared_ptr<IEvent> event) {
    TrafficObjectRemovedEvent* trafficObjectRemovedEvent = static_cast<TrafficObjectRemovedEvent*>(event.get());
    model_->removeTrafficObject(trafficObjectRemovedEvent->getId());
}
