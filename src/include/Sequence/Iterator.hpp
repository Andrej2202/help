#pragma once
#include <base_iter.hpp>
#include <cstddef>
#include <stdexcept>

template<typename T> class Sequence;


template<typename T>
class SequenceIterator : public Iterator<T>{
private:
    const Sequence<T>* data_;
    size_t index_;

public:
    using pointer = const T*;
    using reference = T;

    SequenceIterator(const Sequence<T>* seq, size_t index) : data_(seq), index_(index) {}


    bool HasNext() const override {
        return index_ < data_->GetLength();
    }

    T Next() override {
        if (!HasNext()) {
            throw std::out_of_range("No next element");
        }
        return data_->Get(index_++);
    }

    void Reset() override {
        index_ = 0;
    }
    
    T operator*() const {
        return data_->Get(index_);
    }

    
    SequenceIterator& operator++() {
        ++index_;
        return *this;
    }

    
    SequenceIterator operator++(int) {
        SequenceIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const SequenceIterator& other) const {
        return data_ == other.data_ && index_ == other.index_;
    }
    bool operator!=(const SequenceIterator& other) const {
        return !(*this == other);
    }
};