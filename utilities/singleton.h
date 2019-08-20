#ifndef DATA_ELEMENTS_COMMON_SINGLETON
#define DATA_ELEMENTS_COMMON_SINGLETON

#include <memory>

template<typename T>
class Singleton
{
protected:
	Singleton() {}

private:
	static std::shared_ptr<T> _inst;

private:
	Singleton(Singleton const&) = delete;
	Singleton& operator=(Singleton const&) = delete;

public:
	virtual ~Singleton() {_inst.reset();}

	static std::shared_ptr<T> instance()
	{
		if (not _inst) {
			_inst = std::shared_ptr<T>(new T());
			return _inst;
		}
		return _inst;
	}
};

template<typename T>
std::shared_ptr<T> Singleton<T>::_inst(reinterpret_cast<T*>(0));

#endif // DATA_ELEMENTS_COMMON_SINGLETON

