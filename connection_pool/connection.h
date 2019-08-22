#ifndef CONNECTION_POOL_CONNECTION_H
#define CONNECTION_POOL_CONNECTION_H

namespace connection_pool
{

// The class represents base class of a connection to a database.
class Connection
{
private:
	virtual int _read(const std::string & q) const = 0;

public:
	virtual ~Connection() = default;

	template<typename ... Args>
	void write(Args&& ... args) { /*TODO: throw exception */; }

	int read(const std::string & q) const { return _read(q); }
};

} // namespace connection_pool

#endif // CONNECTION_POOL_CONNECTION_H 
