#pragma once

template <class T>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool HasNext() const = 0;
    virtual T Next() = 0;
    virtual void Reset() = 0;
    virtual T operator*() const = 0;
};