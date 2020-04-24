#ifndef STD_MACROS_H
#define STD_MACROS_H

#include <utility>
#include <functional>
#include <type_traits>

#if __cplusplus >= 201703L

template <typename F, typename ... Args>
using is_void = std::is_void<std::invoke_result_t<F, Args...>>;


using std::add_lvalue_reference_t;
using std::invoke_result_t;
using std::enable_if_t;

#elif __cplusplus >= 201402L

using std::add_lvalue_reference_t;
using std::enable_if_t;

template <typename F, typename ... Args>
using is_void = std::is_void<typename std::result_of<F(Args...)>::type>;


template <typename F, typename ... Args>
using invoke_result_t = typename std::result_of<F(Args...)>::type;

#else

template <typename F, typename ... Args>
using is_void = std::is_void<typename std::result_of<F(Args...)>::type>;

template< class T >
using add_lvalue_reference_t = typename std::add_lvalue_reference<T>::type;

template <typename F, typename ... Args>
using invoke_result_t = typename std::result_of<F(Args...)>::type;

template< bool B, class T = void >
using enable_if_t = typename std::enable_if<B,T>::type;

#endif

#endif // STD_MACROS_H
