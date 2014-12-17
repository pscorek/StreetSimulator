//Author: Bogdan Shkola
//Representing blocking queue used between controller and view modules.

#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H

#include "../common/events/ievent.h"
#include <mutex>
#include <condition_variable>
#include <deque>
#include <QObject>

class BlockingEventQueue : public QObject
{
    Q_OBJECT
private:
    BlockingEventQueue();
    BlockingEventQueue(const BlockingEventQueue&);

    std::mutex              d_mutex;
    std::condition_variable d_condition;
    std::deque<IEvent*>       d_queue;

public:
    void push(IEvent* const& value); // puts an event to the queue
    IEvent* pop(); //waits for the new event appears in the queue and gets it

    static BlockingEventQueue& getInstance() {
        static BlockingEventQueue pInstance_;
        return pInstance_;
    }
};

#endif // BLOCKINGQUEUE_H
