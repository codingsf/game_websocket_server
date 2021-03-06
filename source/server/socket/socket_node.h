#ifndef SERVER_SOCKET_SOCKET_NODE
#define SERVER_SOCKET_SOCKET_NODE
//#include "source/server/socket/socket_node.h"

#include <thread>
#include <string>
#include <memory>
#include <atomic>

class SocketMessage;
class SystemWrapper;
class SetOfFileDescriptors;
class SocketReader;
class SocketWriter;
class SocketServerConnector;
class ClientValidatorInterface;

class SocketInterface{
public:
	virtual SocketMessage getNextMessage() =0;
	virtual void setClientValidator(ClientValidatorInterface * validator) =0;
	virtual void sendMessage(SocketMessage &message) =0;
	virtual void disconnectClient(int FD) =0;
	virtual void shutdown() =0;
	virtual bool isRunning() =0;
	virtual ~SocketInterface();
protected:
	SocketInterface(){}
};


struct ServerConfig {
	std::string port = std::string();
	int64_t loopSpeed = 100;
	int MAXEVENTS = 200;
	size_t MaxReaderSocketBufferSize = 32760;
	size_t MaxWebsocketReadBufferSize = 262144;
	int maxWaitTime = 1000;
	size_t maxHandshakeSize = 2048;
	ServerConfig() {}
};


class Socket : public SocketInterface{ ///class starts new threads to handle socket io and cleans up on destruction

public:
	Socket(const ServerConfig &config);
	SocketMessage getNextMessage();
	void setClientValidator(ClientValidatorInterface * validator);

	void sendMessage(SocketMessage &message);
	void disconnectClient(int FD);
	void shutdown();

	bool isRunning();
	~Socket();

private:
	void startReader();
	void startWriter();
	void startConnector();

	Socket& operator=(const Socket&)=delete;
	Socket(const Socket&)=delete;

	std::atomic<bool> shouldContinueRunning; //flag to tell the thread to end looping and exit //TODO  make sure access to this is atomic
	std::unique_ptr<SystemWrapper> systemWrap;
	std::unique_ptr<SetOfFileDescriptors> FDs;
	std::unique_ptr<SocketReader> reader;
	std::unique_ptr<SocketWriter> writer;
	std::unique_ptr<SocketServerConnector> connector;
	std::thread readerThread;
	std::thread writerThread;
	std::thread connectorThread;
};



#endif /* SERVER_SOCKET_SOCKET_NODE */
