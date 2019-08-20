#ifndef CONNECTION_POOL_H
#define CONNECTION_POOL_H

#include <deque>
#include <exception>
#include <mutex>
#include <set>
#include <string>

#include <connection.h>
#include <connectionFactory.h>
#include <singleton.h>

namespace connection_pool
{

using ConnPtr = std::shared_ptr<Connection>;

//----------------------------------------------------------------------------
// The exception thrown when connection can't be done.
struct ConnectionUnavailable : std::exception
{ 
	char const* what() const throw() {
		return "Unable to allocate connection";
	}; 
};
//----------------------------------------------------------------------------
// Statistic of catched and freed connections.
struct ConnectionPoolStats
{
	uint16_t freeConnectionsNumber;
	uint16_t inUsedNumber;
};
//----------------------------------------------------------------------------
// The class represents a pool of connections.
// A connections created with ConnectionFactory.
class ConnectionPool: public Singleton<ConnectionPool>
{
private:
	std::shared_ptr<ConnectionFactory> _factory;
	uint16_t _poolSize;
	std::deque< std::shared_ptr<Connection> > _pool;
	std::set< std::shared_ptr<Connection> > _inUsed;
	std::mutex _mutex;

public:
	//----------------------------------------------------------------------------
	ConnectionPoolStats getStats()
	{
		std::lock_guard<std::mutex> lock(this->_mutex);

		// get stats
		ConnectionPoolStats stats;
		stats.freeConnectionsNumber = this->_pool.size();
		stats.inUsedNumber = this->_inUsed.size();			

		return stats;
	}
	//----------------------------------------------------------------------------
	ConnectionPool() { }
	//----------------------------------------------------------------------------
	void clear()
	{
		this->_pool.clear();
	}
	//----------------------------------------------------------------------------
	void init(uint16_t poolSize, std::shared_ptr<ConnectionFactory> factory)
	{
		this->_poolSize = poolSize;
		this->_factory = factory;

		// fill the pool
		while(this->_pool.size() < this->_poolSize) {
			this->_pool.push_back(this->_factory->create());
		}
	}
	//----------------------------------------------------------------------------
	~ConnectionPool() { };
	//----------------------------------------------------------------------------
	// retrieve connection from pool
	ConnPtr getConnection()
	{
		std::lock_guard<std::mutex> lock(this->_mutex);

		// check for a free connection
		if (!this->_pool.size()) {
			// Nothing available
			throw ConnectionUnavailable();
		}

		// take one off the front
		std::shared_ptr<Connection>conn = this->_pool.front();
		this->_pool.pop_front();

		// add it to the inUsed list
		this->_inUsed.insert(conn);
		return conn;
	}
	//----------------------------------------------------------------------------
	// get back connection
	void putConnection(ConnPtr conn)
	{
		std::lock_guard<std::mutex> lock(this->_mutex);

		// push back the connection onto the pool
		this->_pool.push_back(std::static_pointer_cast<Connection>(conn));

		// remove from used
		this->_inUsed.erase(conn);
	};
};

} // namespace connection_pool

#endif // CONNECTION_POOL_H
