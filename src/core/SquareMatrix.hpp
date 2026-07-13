#pragma once
#include <Sequence.hpp>
#include <Exceptions.hpp>
#include <algorithm>
#include <concepts>
#include <cstddef>
#include <stdexcept>

// Концепт для контейнера, который будет хранить элементы матрицы
template<typename Seq, typename T>
concept MatrixContainer = requires(Seq s, std::size_t idx, T val) {
    { s.GetLength() } -> std::convertible_to<std::size_t>;
    { s.Get(idx) } -> std::convertible_to<T>;
    { s.Set(idx, val) };
};

template <template<typename> class Container, typename T>
requires MatrixContainer<Container<T>, T>
class SquareMatrix {
private:
    Container<T>* data_;
    size_t dimension_; // Размерность N для матрицы NxN

    // Вспомогательный метод для клонирования контейнера
    Container<T>* cloneData(const Container<T>* src) const {
        if (!src) return nullptr;
        return new Container<T>(*src);
    }

public:
    // Конструктор, принимающий контейнер и размерность
    // (Контейнер должен содержать dimension_^2 элементов)
    SquareMatrix(Container<T>* elements, size_t dimension);
    
    // Конструктор для создания нулевой матрицы заданной размерности
    explicit SquareMatrix(size_t dimension);

    SquareMatrix(const SquareMatrix& other);
    SquareMatrix& operator=(const SquareMatrix& other);
    ~SquareMatrix();

    // Базовые операции над матрицами
    SquareMatrix operator+(const SquareMatrix& other) const;
    SquareMatrix operator-(const SquareMatrix& other) const;
    SquareMatrix operator*(const T& scalar) const;
    SquareMatrix operator*(const SquareMatrix& other) const;

    // Доступ к элементам по координатам
    T Get(size_t row, size_t col) const;
    void Set(size_t row, size_t col, const T& value);

    // Геттеры
    size_t GetDimension() const;
    const Container<T>& GetData() const;
    
    // Создание единичной матрицы
    static SquareMatrix Identity(size_t dimension);
};

#include "SquareMatrix.tpp"