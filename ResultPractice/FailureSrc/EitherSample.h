#pragma once
// ‚±‚ê‚Íƒ{ƒc

template <class L, class R>
class Either
{
    virtual bool isLeft();
    virtual bool isRight();

    virtual bool matchLeft(L& x);
    virtual bool matchRight(R& x);
};

template <class L, class R>
class Left : public Either<L, R> {
public:
    L left;

    Left(L left) : left(left) {}
    constexpr bool isLeft() { return true; }
    constexpr bool isRight() { return false; }

    bool matchLeft(L& x)
    {
        x = left;
        return true;
    }
    bool matchRight(R& x) { return false; }
};

template <class L, class R>
class Right : public Either<L, R> {
public:
    R right;

    Right(R right) : right(right) {}
    constexpr bool isLeft() { return false; }
    constexpr bool isRight() { return true; }

    bool matchLeft(L& x) { return false; }

    bool matchRight(R& x) {
        x = right;
        return true;
    }
};