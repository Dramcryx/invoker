#ifndef INVOKER_HPP
#define INVOKER_HPP

// till stack do you part

#include "std_macros.h"

template <typename T>
class invoker
{
public:
    invoker(T & t): t_(t)
    {}

    template <typename U>
    struct pair
    {
        U ret;
        invoker<T>& inv;
        operator U&&()
        {
            return std::move(ret);
        }
        operator invoker<T>&()
        {
            return inv;
        }
        template <typename F, typename ... Args>
        invoke_result_t<invoker<T>, F, Args...> operator()(F && f, Args && ... args)
        {
            return inv(f, args...);
        }
    };

    template <typename F, typename ... Args>
    enable_if_t<!is_void<F,add_lvalue_reference_t<T>, Args...>::value,
                pair<invoke_result_t<F,add_lvalue_reference_t<T>, Args...>>> operator()(F && f, Args && ... args)
    {
#if __cplusplus >= 201703L
        return {std::invoke(f, t_, args...), *this};
#else
        return {std::move(std::function<invoke_result_t<F,add_lvalue_reference_t<T>, Args...>(add_lvalue_reference_t<T>, Args...)>{f}(t_, args...)), *this};
#endif
    }

    template <typename F, typename ... Args>
    enable_if_t<is_void<F, add_lvalue_reference_t<T>, Args...>::value,
                            invoker<T>&> operator()(F && f, Args && ... args)
    {
#if __cplusplus >= 201703L
        std::invoke(f, t_, args...);
#else
        std::function<void(add_lvalue_reference_t<T>, Args...)>{f}(t_, args...);
#endif
        return * this;
    }

private:
    T & t_;
};


#endif // INVOKER_HPP
