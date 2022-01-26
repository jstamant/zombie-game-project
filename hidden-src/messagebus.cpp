//******************************************************************************
// messagebus.cpp
//******************************************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include dependencies
#include "message.h"
#include "messagebus.h"

//******************************************************************************
// Constructors
//******************************************************************************

MessageBus::MessageBus() {
    ;
}

//******************************************************************************
// Access functions
//******************************************************************************

void MessageBus::pushMessage(Message* msg) {
    bus_.push_back(msg);
}

void MessageBus::registerSystem(System* system) {
    systems_.push_back(system);
}

//******************************************************************************
// Functions
//******************************************************************************

void MessageBus::processMessage(void) {
    ;
}

