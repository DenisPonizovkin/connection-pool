#ifndef CONNECTION_POOL_CONNECTION_FACTORY_H
#define CONNECTION_POOL_CONNECTION_FACTORY_H

#include <memory>

#include <connection.h>

namespace connection_pool
{
// The class represents base class of a factory which creates a connection.
class ConnectionFactory
{
private:
	virtual std::shared_ptr<Connection> _create() = 0;

public:
	// NVI
	std::shared_ptr<Connection> create() {return _create();}
};

} // namespace connection_pool

#endif // CONNECTION_POOL_CONNECTION_FACTORY_H 
