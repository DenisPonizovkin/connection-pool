#ifndef MYSQL_CONNECTION_FACTORY_H
#define MYSQL_CONNECTION_FACTORY_H

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <memory>
#include <string>

#include <mysqlConnection.h>

namespace connection_pool
{

using MySqlConnPtr = std::shared_ptr<MySQLConnection>;

class MySQLConnectionFactory : public ConnectionFactory
{
private:
	std::string _server;
	std::string _username;
	std::string _password;

private:
	// Any exceptions thrown here should be caught elsewhere
	ConnPtr _create()
	{
		// Get the driver
		sql::Driver *driver = get_driver_instance();

		// Create the connection
		MySqlConnPtr c(new MySQLConnection());

		// Connect
		c->conn(SqlConnPtr(
					driver->connect(
						  this->_server
						, this->_username
						, this->_password
					)
				)
		);
		return std::static_pointer_cast<Connection>(c);
	}

public:
	MySQLConnectionFactory(
			  const std::string & server
			, const std::string & username
			, const std::string & password
			):
		  ConnectionFactory()
		, _server(server)
		, _username(username)
		, _password(password)
	{

	}
};

} // namespace connection_pool

#endif // MYSQL_CONNECTION_FACTORY_H
