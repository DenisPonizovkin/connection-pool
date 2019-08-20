#ifndef CONNECTION_POOL_FACTORY_CONNECTION_DRIVER_H
#define CONNECTION_POOL_FACTORY_CONNECTION_DRIVER_H

#include <connectionPool.h>
#include <factory.h>

namespace cp = connection_pool;

class FactoryConnectionDriverFactory: public factory::Factory<cp::ConnectionFactory>
{
};

#endif // CONNECTION_POOL_FACTORY_CONNECTION_DRIVER_H
