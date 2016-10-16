#pragma once

#include "function_detail.hh"

#include <memory>
#include <functional>

namespace presentation {

// Primary template
template<typename Sig>
class function;

// Unwrapping specialization
template<typename Ret, typename... Args>
class function<Ret(Args...)>
{
private:
	using WrapperIfaceType = detail::wrapper_iface<Ret, Args...>;
	std::unique_ptr<WrapperIfaceType> wrapper_;
	
public:

	function()
	{
	}
	
	function(const function& other)
	{
		if (other.wrapper_)
			wrapper_ = other.wrapper_->copy();
	}
	
	function(function&& other)
	{
		wrapper_ = std::move(other.wrapper_);
	}
	
	explicit operator bool() const
	{
		return !!wrapper_;
	}
	
	template<typename Ftor>
	function(Ftor f)
	{
		using WrapperType = detail::functor_wrapper<Ftor, Ret, Args...>;
		
		wrapper_ = std::make_unique<WrapperType>(f);
	}
	
	Ret operator()(Args... args)
	{
		if (wrapper_)
			return wrapper_->invoke(std::forward<Args>(args)...);
		else
			throw std::bad_function_call();
	}
	
};
	
}