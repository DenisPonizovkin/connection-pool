#ifndef FACTORY_H
#define FACTORY_H

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <type_traits>

#include "function.h"

namespace factory
{

struct UnknownKey: public std::exception
{
	const char * what () const throw () { return "Unknown key"; }
};

//-------------------------------------------------------------------
// Factory class declaration
//-------------------------------------------------------------------
template<typename Base, typename Key = std::string>
class Factory
{
public:
	typedef std::shared_ptr<Base> ReturnType;

public:
	template<typename ... Args>
	ReturnType create(Key const& key, Args&& ... args);

	/// registers function pointer
	template<typename Return, typename ... Args>
	void reg(
			Key const& key,
			Return (*creator) (Args ... args)
			);

protected:
	typedef std::shared_ptr< FunctionBase<Base> > Value;

	std::map<Key, Value> _map;
};

//-------------------------------------------------------------------
// Factory class methods implementation
//-------------------------------------------------------------------
template<typename Base, typename Key>
template<typename ... Args>
typename Factory<Base, Key>::ReturnType
Factory<Base, Key>::create(const Key & key, Args&& ... args)
{
	auto ret = _map.find(key);
	if (ret == _map.end())
		throw UnknownKey();
	
	typedef Function<Base, Args...> FType;

	const FType & creator =
		dynamic_cast<const FType &>(*(ret->second));

	return ReturnType(creator(std::forward<Args>(args)...));
}
//-------------------------------------------------------------------
template<typename Base, typename Key>
template<typename Return, typename ... Args>
void Factory<Base, Key>::reg(
		const Key & key,
		Return (*creator) (Args ... args)
		)
{
	_map[key] = Value(new Function<Base, Args...>(creator));
}
//-------------------------------------------------------------------
template<typename T, typename Base>
T& cast(std::shared_ptr<Base>& ptr)
{
	return dynamic_cast<T&>(*ptr);
}
//-------------------------------------------------------------------
template<typename T, typename Base>
T const& cast(std::shared_ptr<Base> const& ptr)
{
	return dynamic_cast<T const&>(*ptr);
}
//-------------------------------------------------------------------


} // namespace factory

#endif // FACTORY_H
