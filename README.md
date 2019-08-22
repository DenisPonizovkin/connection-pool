# Connection pool
This is a connection pool which can be used with different databases.
It creates pool of connections (which stored in std::dequeue) by the abstract factory.

## Getting Started
You can see examples of usage in unit tests.

### Prerequisites
[Catch2](https://github.com/catchorg/Catch2) must be install
[Mysql Connector](https://dev.mysql.com/doc/connector-cpp/8.0/en/connector-cpp-installation-binary.html)
[Psql Connector](http://pqxx.org/development/libpqxx)


### Installing
mkdir build
cd build
cmake ..
make

static connection pool library will be in build/connection_pool/directory

## Running the tests
cd build
ctest
after last command you can see build/test/report.xml file which can be used with Jenkins
