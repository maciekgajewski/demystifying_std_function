#pragma once

#include <utility>

namespace presentation { namespace detail {

	
// Functor-wrapper interface, functor type erased
template<typename Ret, typename... Args>
struct wrapper_iface
{
	virtual ~wrapper_iface() {}
	virtual Ret invoke(Args&& ... args) = 0;
};


// Implementation for concrete function type
template<typename Functor, typename Ret, typename... Args>
struct functor_wrapper : public wrapper_iface<Ret, Args...>
{
	Functor functor_;
	
	functor_wrapper(Functor f) : functor_(f) {}
	
	virtual Ret invoke(Args&& ... args)
	{
		return functor_(std::forward<Args>(args)...);
	}
};


	
}}

