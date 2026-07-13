#include "SquareMatrix.hpp"
#include "MutableArraySequence.hpp"
#include <iostream>

// Вспомогательная функция для печати матрицы
template <template<typename> class Container, typename T>
void PrintMatrix(const char* name, const SquareMatrix<Container, T>& matrix) {
    std::cout << name << " (" << matrix.GetDimension() << "x" << matrix.GetDimension() << "):\n";
    for (size_t i = 0; i < matrix.GetDimension(); ++i) {
        std::cout << "  [ ";
        for (size_t j = 0; j < matrix.GetDimension(); ++j) {
            std::cout << matrix.Get(i, j) << " ";
        }
        std::cout << "]\n";
    }
    std::cout << "\n";
}

int main() {
    try {
        // 1. Создание матрицы 2x2 из MutableArraySequence
        std::cout << "=== Test 1: Create matrix from container ===\n";
        MutableArraySequence<int>* data1 = new MutableArraySequence<int>();
        data1 = static_cast<MutableArraySequence<int>*>(data1->Append(1));
        data1 = static_cast<MutableArraySequence<int>*>(data1->Append(2));
        data1 = static_cast<MutableArraySequence<int>*>(data1->Append(3));
        data1 = static_cast<MutableArraySequence<int>*>(data1->Append(4));
        
        SquareMatrix<MutableArraySequence, int> mat1(data1, 2);
        PrintMatrix("mat1", mat1);

        // 2. Создание нулевой матрицы 3x3
        std::cout << "=== Test 2: Create zero matrix ===\n";
        SquareMatrix<MutableArraySequence, int> mat2(3);
        PrintMatrix("mat2 (zeros)", mat2);

        // 3. Создание единичной матрицы
        std::cout << "=== Test 3: Create identity matrix ===\n";
        auto mat3 = SquareMatrix<MutableArraySequence, int>::Identity(3);
        PrintMatrix("mat3 (identity)", mat3);

        // 4. Доступ к элементам (Get/Set)
        std::cout << "=== Test 4: Get/Set elements ===\n";
        mat1.Set(0, 1, 99);  // Меняем элемент [0][1] на 99
        std::cout << "After Set(0, 1, 99):\n";
        PrintMatrix("mat1", mat1);
        std::cout << "mat1[1][0] = " << mat1.Get(1, 0) << "\n\n";

        // 5. Сложение матриц
        std::cout << "=== Test 5: Matrix addition ===\n";
        MutableArraySequence<int>* data4 = new MutableArraySequence<int>();
        data4 = static_cast<MutableArraySequence<int>*>(data4->Append(10));
        data4 = static_cast<MutableArraySequence<int>*>(data4->Append(20));
        data4 = static_cast<MutableArraySequence<int>*>(data4->Append(30));
        data4 = static_cast<MutableArraySequence<int>*>(data4->Append(40));
        
        SquareMatrix<MutableArraySequence, int> mat4(data4, 2);
        auto sum = mat1 + mat4;
        PrintMatrix("mat1 + mat4", sum);

        // 6. Умножение на скаляр
        std::cout << "=== Test 6: Scalar multiplication ===\n";
        auto scaled = mat1 * 5;
        PrintMatrix("mat1 * 5", scaled);

        // 7. Матричное умножение
        std::cout << "=== Test 7: Matrix multiplication ===\n";
        MutableArraySequence<int>* data5 = new MutableArraySequence<int>();
        data5 = static_cast<MutableArraySequence<int>*>(data5->Append(2));
        data5 = static_cast<MutableArraySequence<int>*>(data5->Append(0));
        data5 = static_cast<MutableArraySequence<int>*>(data5->Append(0));
        data5 = static_cast<MutableArraySequence<int>*>(data5->Append(3));
        
        SquareMatrix<MutableArraySequence, int> mat5(data5, 2);
        auto product = mat1 * mat5;
        PrintMatrix("mat1 * mat5", product);

        // 8. Проверка исключений
        std::cout << "=== Test 8: Exception handling ===\n";
        try {
            auto bad_sum = mat1 + mat3;  // Разные размерности (2x2 + 3x3)
        } catch (const std::exception& e) {
            std::cout << "Caught expected exception: " << e.what() << "\n";
        }

        try {
            mat1.Get(5, 0);  // Выход за границы
        } catch (const std::exception& e) {
            std::cout << "Caught expected exception: " << e.what() << "\n";
        }

        std::cout << "\nAll tests passed!\n";
    } 
    catch (const std::exception& e) {
        std::cerr << "Unexpected exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}