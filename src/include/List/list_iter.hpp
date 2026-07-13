#pragma once
#include <base_iter.hpp>
#include <cstddef>
#include <stdexcept>

template <class T>
struct ListNode {
    T data;
    ListNode* next;
};

template <class T>
class ListSequenceIterator : public Iterator<T> {
private:
    ListNode<T>* current_;
    ListNode<T>* head_;

public:
    ListSequenceIterator(ListNode<T>* head)
        : current_(head) head_(head){}

    bool HasNext() const override {
        return current_ != nullptr;
    }

    T Next() override {
        if (!HasNext()) {
            throw std::out_of_range("No next element");
        }
        T value = current_->data;
        current_ = current_->next;
        return value;
    }

    void Reset() override {
        current_ = head_;
    }

    T operator*() const {
        return data_->Get(index_);
    }
};