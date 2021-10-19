#pragma once
// ‚±‚ê‚Íƒ{ƒc

template <typename T, typename E>
struct Result {

    Result(T const& ok) : t(tag::OK) {
        ok_ = ok;
    }

    Result(E const& e) : t(tag::ERROR) {
        err_ = e;
    }

    ~Result() {
        switch (t) {
        case tag::OK:
            ok_.~T();
            break;
        case tag::ERROR:
            err_.~E();
            break;
        }
    }

    Result(Result const& r) : t(r.t) {
        switch (t) {
        case tag::OK:
            ok_ = r.ok_;
            break;
        case tag::ERROR:
            err_ = r.err_;
            break;
        }
    }

    bool Valid() const {
        return (t == tag::OK);
    }

    T const& Get() const {
        if (t != tag::OK) {
            throw "invalid get operation";
        }
        return ok_;
    }

    E const& GetError() const {
        if (t != tag::ERROR) {
            throw "invalid get error operation";
        }
        return err_;
    }

private:
    enum class tag {
        OK,
        ERROR,
    };
    tag t;
    union {
        T ok_;
        E err_;
    };

};

template <typename T>
struct ok_value {
	explicit ok_value(T t) : t(t) {}

	template <typename V, typename E>
    operator Result<V, E>() const;

private:
	T t;
};

template <typename T>
template <typename V, typename E>
ok_value<T>::operator Result<V, E>() const {
    return Result<V, E>(t);
}

template <typename T>
ok_value<T> Ok(T t) {
	return ok_value<T>(t);
}

template <typename T>
struct error_value {
    explicit error_value(T t) : t(t) {}

    template <typename V, typename E>
    operator Result<V, E>() const;

private:
    T t;
};

template <typename T>
template <typename V, typename E>
error_value<T>::operator Result<V, E>() const {
    return Result<V, E>(t);
}

template <typename T>
error_value<T> Error(T t) {
    return error_value<T>(t);
}