#pragma once

template <class T1, class T2>
class Result
{
	bool isOk;
	union
	{
		T1 ok_;
		T2 err_;
	};

	//template <class T1_, class T2_> 
	//friend Result<T1_, T2_> Ok(T1_ x);
	////{
	////	Result<T1_, T2_> e;
	////	e.isOk = true;
	////	e.ok_ = x;
	////	return e;
	////}
	//
	//template <class T1_, class T2_> 
	//friend Result<T1_, T2_> Error(T2_ x);
	////{
	////	Result<T1_, T2_> e;
	////	e.isOk = false;
	////	e.err_ = x;
	////	return e;
	////}

public:
	bool Valid()
	{
		return isOk;
	}

	const T1& Get()
	{
		if (!isOk) throw("Invalid get operation");
		return ok_;
	}

	const T2& GetError()
	{
		if (isOk) throw("Invalid get error operation");
		return err_;
	}

	Result(T1 const& r)
	{
		isOk = true;
		ok_ = r;
	}

	Result(T2 const& r)
	{
		isOk = false;
		err_ = r;
	}

	~Result()
	{
		if (isOk)
			ok_.~T1();
		else
			err_.~T2();
	}
};

template <class T1, class T2>
Result<T1, T2> Ok(T1 x)
{
	Result<T1, T1> e(x);
	//e.isOk = true;
	//e.ok_ = x;
	return e;
}

template <class T1, class T2>
Result<T1, T2> Error(T2 x)
{
	Result<T1, T2> e(x);
	//e.isOk = false;
	//e.err_ = x;
	return e;
}

