#pragma once
#include <base_iter.hpp>
#include <cstddef>
#include <stdexcept>

template <class T>
class ArraySequenceIterator : public Iterator<T> {
private:
    const T* data_;
    size_t index_;

public:
    ArraySequenceIterator(const T* data)
        : data_(data), index_(0){}

    ArraySequenceIterator(const T* data, size_t index)
        : data_(data), index_(index){}

    bool HasNext() const override {
        return index_ < data_->GetLength();
    }

    T Next() override {
        if (!HasNext()) {
            throw std::out_of_range("No next element");
        }
        return data_[index_++];
    }

    void Reset() override {
        index_ = 0;
    }

    T operator*() const {
        return data_->Get(index_);
    }
};