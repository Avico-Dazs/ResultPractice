#pragma once

// ‚±‚ê‚Íƒ{ƒc

template<class T, class E>
class Result
{
	(bool)() valid_;
public:
	virtual bool Valid() { throw; };
	virtual const T& Get() { throw; };
	virtual const E& GetError() { throw; };
};

template<class T, class E>
class Ok : public Result<T, E>
{
	T ok_;
public:
	Ok(const T& x) : ok_(x){}
	constexpr bool Valid() override { return true; }
	constexpr const T& Get()  override { return ok_; }
	constexpr const E& GetError()  override { throw("invalid get error operation."); }
};

