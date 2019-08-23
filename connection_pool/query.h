
#ifndef CONNECTION_POOL_QUERY_H
#define CONNECTION_POOL_QUERY_H

#include <connectionPool.h>
#include <factoryConnectionDriver.h>

#include <iostream>

namespace connection_pool
{

template<typename ConcreteConnection, typename ... Args>
class Query
{
protected:
	std::shared_ptr<ConcreteConnection> _c;

public:
	Query()
	{
		_c = std::dynamic_pointer_cast<ConcreteConnection>(
				ConnectionPool::instance().getConnection()
			);
	}

	~Query()
	{
		ConnectionPool::instance().putConnection(_c);
	}

	void write(const std::string & q, Args ... args)
	{	
		_c->write(q, args...);
	}

	int read(const std::string & q)
	{
		return _c->read(q);
	}
};

} // namespace connection_pool

#endif // CONNECTION_POOL_QUERY_H 
