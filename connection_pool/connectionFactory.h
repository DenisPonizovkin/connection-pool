#ifndef CONNECTION_POOL_CONNECTION_FACTORY_H
#define CONNECTION_POOL_CONNECTION_FACTORY_H

#include <memory>

#include <connection.h>

namespace connection_pool
{

using ConnPtr = std::shared_ptr<Connection>;

// The class represents base class of a factory which creates a connection.
class ConnectionFactory
{
private:
	virtual ConnPtr _create() = 0;

public:
	ConnPtr create() {return _create();}
};

} // namespace connection_pool

#endif // CONNECTION_POOL_CONNECTION_FACTORY_H 
