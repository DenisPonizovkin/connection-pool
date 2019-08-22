#ifndef FUNCTION_H
#define FUNCTION_H

#include <functional>

namespace factory
{

template<typename BaseReturnedType>
class FunctionBase
{
public:
	virtual ~FunctionBase() = default;
};

template<typename BaseReturnedType, typename ... Args>
class Function : public FunctionBase<BaseReturnedType>
{
public:
	typedef std::function<BaseReturnedType*(Args...)> AFunction;

protected:
	 AFunction _f;

public:
	template<typename T>
	Function(T&& f) : _f(std::forward<T>(f)) {}

	BaseReturnedType* operator() (Args&& ... args) const
	{
		return _f(std::forward<Args>(args)...);
	}

};

} // namespace factory

#endif // FUNCTION_H
