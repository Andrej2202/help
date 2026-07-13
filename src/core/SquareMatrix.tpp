template <template<typename> class Container, typename T>
SquareMatrix<Container, T>::SquareMatrix(Container<T>* elements, size_t dimension) 
    : dimension_(dimension) {
    if (!elements) {
        throw std::invalid_argument("Elements container cannot be null");
    }
    if (elements->GetLength() != dimension * dimension) {
        throw std::invalid_argument("Container size does not match dimension^2");
    }
    data_ = elements; // Принимаем владение указателем
}

template <template<typename> class Container, typename T>
SquareMatrix<Container, T>::SquareMatrix(size_t dimension) 
    : dimension_(dimension) {
    size_t total_size = dimension * dimension;
    data_ = new Container<T>(total_size);
    for (size_t i = 0; i < total_size; ++i) {
        data_->Set(i, T(0)); // Инициализация нулями
    }
}

template <template<typename> class Container, typename T>
SquareMatrix<Container, T>::SquareMatrix(const SquareMatrix& other) 
    : dimension_(other.dimension_) {
    data_ = cloneData(other.data_);
}

template <template<typename> class Container, typename T>
SquareMatrix<Container, T>& SquareMatrix<Container, T>::operator=(const SquareMatrix& other) {
    if (this != &other) {
        delete data_;
        dimension_ = other.dimension_;
        data_ = cloneData(other.data_);
    }
    return *this;
}

template <template<typename> class Container, typename T>
SquareMatrix<Container, T>::~SquareMatrix() {
    delete data_;
}

template <template<typename> class Container, typename T>
T SquareMatrix<Container, T>::Get(size_t row, size_t col) const {
    if (row >= dimension_ || col >= dimension_) {
        throw std::out_of_range("Matrix index out of bounds");
    }
    return data_->Get(row * dimension_ + col);
}

template <template<typename> class Container, typename T>
void SquareMatrix<Container, T>::Set(size_t row, size_t col, const T& value) {
    if (row >= dimension_ || col >= dimension_) {
        throw std::out_of_range("Matrix index out of bounds");
    }
    data_->Set(row * dimension_ + col, value);
}

template <template<typename> class Container, typename T>
size_t SquareMatrix<Container, T>::GetDimension() const {
    return dimension_;
}

template <template<typename> class Container, typename T>
const Container<T>& SquareMatrix<Container, T>::GetData() const {
    return *data_;
}

template <template<typename> class Container, typename T>
SquareMatrix<Container, T> SquareMatrix<Container, T>::operator+(const SquareMatrix& other) const {
    if (dimension_ != other.dimension_) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }
    
    SquareMatrix result(dimension_);
    size_t total = dimension_ * dimension_;
    for (size_t i = 0; i < total; ++i) {
        result.data_->Set(i, this->data_->Get(i) + other.data_->Get(i));
    }
    return result;
}

template <template<typename> class Container, typename T>
SquareMatrix<Container, T> SquareMatrix<Container, T>::operator-(const SquareMatrix& other) const {
    if (dimension_ != other.dimension_) {
        throw std::invalid_argument("Matrix dimensions must match for subtraction");
    }
    
    SquareMatrix result(dimension_);
    size_t total = dimension_ * dimension_;
    for (size_t i = 0; i < total; ++i) {
        result.data_->Set(i, this->data_->Get(i) - other.data_->Get(i));
    }
    return result;
}

template <template<typename> class Container, typename T>
SquareMatrix<Container, T> SquareMatrix<Container, T>::operator*(const T& scalar) const {
    SquareMatrix result(dimension_);
    size_t total = dimension_ * dimension_;
    for (size_t i = 0; i < total; ++i) {
        result.data_->Set(i, this->data_->Get(i) * scalar);
    }
    return result;
}

template <template<typename> class Container, typename T>
SquareMatrix<Container, T> SquareMatrix<Container, T>::operator*(const SquareMatrix& other) const {
    if (dimension_ != other.dimension_) {
        throw std::invalid_argument("Matrix dimensions must match for multiplication");
    }
    
    SquareMatrix result(dimension_);
    for (size_t i = 0; i < dimension_; ++i) {
        for (size_t j = 0; j < dimension_; ++j) {
            T sum = T(0);
            for (size_t k = 0; k < dimension_; ++k) {
                sum = sum + this->Get(i, k) * other.Get(k, j);
            }
            result.Set(i, j, sum);
        }
    }
    return result;
}

template <template<typename> class Container, typename T>
SquareMatrix<Container, T> SquareMatrix<Container, T>::Identity(size_t dimension) {
    SquareMatrix result(dimension);
    for (size_t i = 0; i < dimension; ++i) {
        result.Set(i, i, T(1));
    }
    return result;
}