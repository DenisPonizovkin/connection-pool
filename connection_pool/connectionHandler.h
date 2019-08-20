#ifndef CONNECTION_POOL_CONNETION_HANDLER_H
#define CONNECTION_POOL_CONNETION_HANDLER_H

#include <connectionPool.h>
#include <factoryConnectionDriver.h>
#include <iostream>

namespace connection_pool
{

template<typename ConnType>
class ConnectionHandler
{
private:
	ConnPtr _conn;

private:
	ConnectionHandler(ConnectionHandler const&) = delete;
	ConnectionHandler& operator=(ConnectionHandler const&) = delete;

public:
	//----------------------------------------------------------------------------
	ConnectionHandler()
	{
		try {
			_conn = cp::ConnectionPool::instance()->getConnection();
		} catch(const std::exception & e) {
			std::cout << e.what();
			throw e;
		}
	}
	//----------------------------------------------------------------------------
	virtual ~ConnectionHandler()
	{
		cp::ConnectionPool::instance()->putConnection(_conn);
	}
	//----------------------------------------------------------------------------
	int read(const std::string & q) const
	{
		ConnType *conn = dynamic_cast<ConnType*>(_conn.get());
  		return conn->read(q);
	}
	//----------------------------------------------------------------------------
	template<typename ... Args>
	void write(const std::string & q, Args&& ... args)
	{
		ConnType *conn = dynamic_cast<ConnType*>(_conn.get());
  		conn->write(q, std::forward<Args>(args)...);
	}
};

} // namespace connection_pool

#endif // CONNECTION_POOL_CONNETION_HANDLER_H 
