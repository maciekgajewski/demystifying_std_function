#pragma once

#include <utility>
#include <memory>

namespace presentation { namespace detail {

	
// Functor-wrapper interface, functor type erased
template<typename Ret, typename... Args>
struct wrapper_iface
{
	virtual ~wrapper_iface() {}
	virtual Ret invoke(Args&& ... args) = 0;
	virtual std::unique_ptr<wrapper_iface> copy() const = 0;
};


// Implementation for concrete function type
template<typename Functor, typename Ret, typename... Args>
struct functor_wrapper : public wrapper_iface<Ret, Args...>
{
	Functor functor_;
	using ThisType = functor_wrapper<Functor, Ret, Args...>;
	
	functor_wrapper(Functor f) : functor_(f) {}
	
	virtual Ret invoke(Args&& ... args) override
	{
		return functor_(std::forward<Args>(args)...);
	}
	
	std::unique_ptr<wrapper_iface<Ret, Args...>> copy() const override
	{
		return std::make_unique<ThisType>(*this);
	}
};


	
}}

