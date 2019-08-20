#include <chrono>
#include <catch2/catch.hpp>
#include <vector>
#include <thread>

#include <connectionHandler.h>
#include <factory.h>
#include <factoryConnectionDriver.h>
#include <mysqlConnectionFactory.h>

namespace cp = connection_pool;

FactoryConnectionDriverFactory fcdf;
const int n = 100;
int currentRecordsNumber;
const std::string q = "select count(*) from new_table";

void connect()
{
	try {
		cp::ConnectionHandler<cp::MySQLConnection> ch;
		ch.write<int>(
				std::string("INSERT INTO new_table(id) VALUES (?);"), 1
			);
	}  catch (const std::exception & e) {
		throw e;
	}
}

cp::MySQLConnectionFactory* createMysqlConnectionFactory(
			  const std::string & server
			, const std::string & username
			, const std::string & password
		)
{
	return new cp::MySQLConnectionFactory(server, username, password);
}

TEST_CASE("Mysql connection pool", "[classic]")
{
	fcdf.reg("mysql", &createMysqlConnectionFactory);
	auto cf = fcdf.create<const std::string &
						, const std::string &
						, const std::string &>("mysql", "localhost", "root", "Asdf123!@#");
	cp::ConnectionPool::instance()->init(n, cf);

	SECTION("Check mysql success connections")
	{
		{
			// in section for freeing
			cp::ConnectionHandler<cp::MySQLConnection> ch;
			currentRecordsNumber = ch.read(q);
		}

		std::thread threads[n];
		for (int i = 0; i < n; i++) {
			threads[i] = std::thread(connect);	
		}

		for (int i = 0; i < n; i++) {
			threads[i].join();
		}
		connection_pool::ConnectionPoolStats stats = cp::ConnectionPool::instance()->getStats();
		REQUIRE(stats.freeConnectionsNumber == n);
	}

	SECTION("Check write/read")
	{
		cp::ConnectionHandler<cp::MySQLConnection> ch;
		REQUIRE(ch.read(q) == currentRecordsNumber + n);
	}
}
