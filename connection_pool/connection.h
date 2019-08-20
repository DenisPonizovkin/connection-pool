#ifndef CONNECTION_POOL_CONNECTION_H
#define CONNECTION_POOL_CONNECTION_H

namespace connection_pool
{

// The class represents base class of a connection to a database.
class Connection
{

public:
	Connection(){};
	virtual ~Connection(){};

	template<typename ... Args>
	void write(Args&& ... args) { /*TODO: throw exception */; }

	int read(const std::string & q) const { /*TODO: throw exception */; }
};

} // namespace connection_pool

#endif // CONNECTION_POOL_CONNECTION_H 
