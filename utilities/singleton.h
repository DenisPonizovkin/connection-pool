#ifndef DATA_ELEMENTS_COMMON_SINGLETON
#define DATA_ELEMENTS_COMMON_SINGLETON

#include <memory>

template<typename T>
class Singleton
{
protected:
	Singleton() = default;

private:
	Singleton(Singleton const&) = delete;
	Singleton& operator=(Singleton const&) = delete;

public:
	virtual ~Singleton() = default;

	static T& instance()
	{
		static T _inst;
		return _inst;
	}
};

#endif // DATA_ELEMENTS_COMMON_SINGLETON

