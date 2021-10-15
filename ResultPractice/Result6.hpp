#pragma once
#include <memory>

template<class T>
struct Okay
{
	T value;
};

template <class T>
constexpr Okay<T> Ok(T const& x)
{
	return { x };
}

template<class T>
Okay<T> Ok(T&& x)
{
	return { std::move(x) };
}

template<class E>
struct Error
{
	E value;
};

template <class E>
constexpr Error<E> Err(E const& x)
{
	return { x };
}

template<class E>
Error<E> Err(E&& x)
{
	return { std::move(x) };
}

template<class T, class E>
struct Result
{
	union
	{
		T ok_;
		E err_;
	};
	bool const valid = 0;

	constexpr bool Valid() { return valid; }
	constexpr T Get() 
	{ 
		if (!valid) throw("invalid get operation");
		return ok_; 
	}
	constexpr E GetError() 
	{ 
		if (valid) throw("invalid get error operation");
		return err_;
	}
	
	constexpr Result(Okay<T> const& r) : ok_(r.value), valid(true) {};
	constexpr Result(Error<E> const& r) : err_(r.value), valid(false) {};

	Result(Okay<T>&& t) : ok_(std::move(t.value)), valid(true) {};
	Result(Error<E>&& t) : err_(std::move(t.value)), valid(false) {};
	constexpr Result(Result<T, E> const& e) : valid(e.valid)
	{
		if (valid)
			new (&ok_)T(e.ok_);
		else
			new (&err_)E(e.err_);
	}
	Result(Result<T, E>&& e) :valid(e.valid)
	{
		if (valid)
			new (&ok_)T(std::move(e.ok_));
		else
			new (&err_)E(std::move(e.err_));
	}
	~Result()
	{
		if (valid)
			ok_.~T();
		else
			err_.~E();
	}
};