#ifndef MYSQL_CONNECTION_H
#define MYSQL_CONNECTION_H

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include <connectionPool.h>
#include <writer.h>

using namespace std;

namespace connection_pool
{
template<int index, typename... Ts>
struct SetParams
{
	void operator() (std::shared_ptr<sql::PreparedStatement> & stmt, tuple<Ts...>& t)
	{
		if (typeid(get<index>(t)).name() == std::string("i")) {
			stmt->setInt(index, get<index>(t));
		}
		SetParams<index - 1, Ts...>{}(stmt, t);
	}
};

template<typename ... Ts>
struct SetParams<0, Ts...>
{
	void operator() (std::shared_ptr<sql::PreparedStatement> & stmt, tuple<Ts...>& t)
	{
		if (typeid(get<0>(t)).name() == std::string("i")) {
			stmt->setInt(1, get<0>(t));
		}
	}
};

template<typename... Ts>
void setParams(std::shared_ptr<sql::PreparedStatement> & stmt, tuple<Ts...>& t)
{
	const auto size = tuple_size<tuple<Ts...>>::value;
	SetParams<size - 1, Ts...>{}(stmt, t);
}

using SqlConnPtr = std::shared_ptr<sql::Connection>;

class MySQLConnection : public Connection
{
private:
	SqlConnPtr _conn;

private:
	virtual int _read(const std::string & q) const
	{
		_conn->setSchema("test");
		std::shared_ptr<sql::Statement> stmt(_conn->createStatement());
		std::shared_ptr<sql::ResultSet> res(stmt->executeQuery(q));
		int rslt = 0;
		while (res->next()) {
			rslt = res->getInt(1);
			break;
		}
		return rslt;
	}

public:
	~MySQLConnection()
	{
		if(this->_conn) {
			this->_conn->close();
			this->_conn.reset(); 	// Release and destruct
		}
	};

	void conn(SqlConnPtr c) {_conn = c;}

	template<typename ... Args>
	void write(const std::string & q, Args ... args)
	{
		_conn->setSchema("test");
		std::shared_ptr<sql::PreparedStatement> stmt(_conn->prepareStatement(q.c_str()));
		std::tuple<Args...> store(args...);
		setParams(stmt, store);
		try {
			stmt->executeQuery();
		} catch(const std::exception & e) {
			std::cout << e.what() << endl;
		}
	}
};

} // namespace connection_pool

#endif // MYSQL_CONNECTION_H
