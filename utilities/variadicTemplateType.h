#ifndef UTILITIES_VARIADIC_TEMPLATE_TYPE_H
#define UTILITIES_VARIADIC_TEMPLATE_TYPE_H

template<int N, typename... Args> using NthTypeOf =
	typename std::tuple_element<N, std::tuple<Args...>>::type;

#endif // UTILITIES_VARIADIC_TEMPLATE_TYPE_H 
