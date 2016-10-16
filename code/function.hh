#pragma once


namespace presentation {


template<typename Sig>
class function;

template<typename Ret, typename... Args>
class function<Ret(Args...)>
{
};
	
}