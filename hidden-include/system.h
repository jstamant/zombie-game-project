#ifndef _SYSTEM_H_
#define _SYSTEM_H_
//******************************************************************************
// system.h
//******************************************************************************

//Forward declarations
class Message;
class MessageBus;

class System
{
    public:
        void processMessage(Message*);
    private:
        MessageBus* messageBus_;
};

#endif //_SYSTEM_H_

