#pragma once
#include "Sequence.hpp"
#include "Iterator.hpp"

template<typename T, typename Func>
Sequence<T>* map(const Sequence<T>& seq, Func f) {
    Sequence<T>* res = seq.CreateEmpty();
    for (auto it = seq.begin(); it != seq.end(); ++it) {
        res->Append(f(*it));
    }
    return res;
}

template<typename T, typename Func>
auto mapWithIndex(const Sequence<T>& seq, Func f) {
    Sequence<std::decay_t<decltype(f(seq.Get(0), 0))>>* res = seq.CreateEmpty();
    int idx = 0;
    for (auto it = seq.begin(); it != seq.end(); ++it, ++idx) {
        res->Append(f(*it, idx));
    }
    return res;
}

template<typename T, typename Pred>
Sequence<T>* where(const Sequence<T>& seq, Pred predicate) {
    Sequence<T>* res = seq.CreateEmpty();
    for (auto it = seq.begin(); it != seq.end(); ++it) {
        if (predicate(*it)) {
            res->Append(*it);
        }
    }
    return res;
}

template<typename T, typename Func, typename U>
U reduce(const Sequence<T>& seq, Func f, U starter) {
    U result = starter;
    for (auto it = seq.begin(); it != seq.end(); ++it) {
        result = f(result, *it);
    }
    return result;
}