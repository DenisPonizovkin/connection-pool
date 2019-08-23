#ifndef PSQL_CONNECTION_FACTORY_H
#define PSQL_CONNECTION_FACTORY_H

#include <memory>
#include <string>

#include <psqlConnection.h>

namespace connection_pool
{

class PsqlConnectionFactory : public ConnectionFactory
{
private:
	std::string _host;
	std::string _username;
	std::string _password;
	std::string _dbname;

private:
	// Any exceptions thrown here should be caught elsewhere
	ConnPtr _create()
	{
		std::ostringstream connString("");
		connString << "host=" << _host
       		<< " user=" << _username
       		<< " password=" << _password
       		<< " dbname=" << _dbname;

		PsqlConnection * c = new PsqlConnection();
		pqxx::connection *conn = new pqxx::connection(connString.str());
		c->conn(conn);
		return ConnPtr(c);
	}

public:
	PsqlConnectionFactory(
			  const std::string & host
			, const std::string & username
			, const std::string & password
			, const std::string & dbname
			):
		  ConnectionFactory()
		, _host(host)
		, _username(username)
		, _password(password)
		, _dbname(dbname)
	{

	}
};

} // namespace connection_pool

#endif // PSQL_CONNECTION_FACTORY_H
