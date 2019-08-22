#ifndef PSQL_CONNECTION_H
#define PSQL_CONNECTION_H


#include <memory>
#include <pqxx/pqxx>
#include <pqxx/connection>
#include <pqxx/transaction>
#include <string>
#include <tuple>
#include <vector>
#include <connectionPool.h>

#include <iostream>

using namespace std;

namespace connection_pool
{

class PsqlConnection : public Connection
{
private:
	pqxx::connection * _conn;

private:
	virtual int _read(const std::string & q) const
	{
		pqxx::work txn{*_conn};
		pqxx::result r = txn.exec(q);
		int rslt = 0;
		for (auto row: r) {
			rslt = row[0].as<int>();
			break;
		}
		return rslt;
	}

public:
	~PsqlConnection() { _conn->disconnect(); }

	void conn(pqxx::connection * c) {_conn = c;}

	template<typename ... Args>
	void write(const std::string & q, Args ... args)
	{
		pqxx::work w(*_conn);
		w.exec(q);
		w.commit();
	}
};

} // namespace connection_pool

#endif // PSQL_CONNECTION_H
