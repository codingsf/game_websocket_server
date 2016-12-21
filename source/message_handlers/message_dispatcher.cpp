#include "source/message_handlers/message_dispatcher.h"
#include "source/data_types/socket_message.h"
#include "source/data_types/message_type.h"
#include "source/message_handlers/message_dispatcher_listeners.h"


MessageDispatcher::MessageDispatcher() : d(new MessageDispatcherListeners()){}
MessageDispatcher::~MessageDispatcher()
{
	delete d;
}

MessageDispatcher::MessageDispatcher(MessageDispatcherListenersBase *base) : d(base) {}

void MessageDispatcher::dispatchMessages(std::vector<SocketMessage> &messages)
{
	for(size_t i=0; i<messages.size(); ++i){
		// call the correct function based on the message type
		uint32_t type =messages[i].getType();
		if(type<MessageType::NumberOfMessageTypes)
			d->listeners[type]->callback(messages[i]);
		else
			d->listeners[MessageType::null]->callback(messages[i]);
	}
}
