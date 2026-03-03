#ifndef CORE
#define CORE

#include "../hal/HAL.h"

/**
 * @brief 밀도가 높은 컴포넌트
 * @note 해당 자료형은 UUID가 Entity ID입니다.
 * @code
```
class SparseComponent{
    private:

    public:
    int UUID;
    T data;
};
```
 */
template <typename T>
class SparseComponent{
    private:

    public:
    int UUID;
    T data;
};

/**
 * @brief 밀도가 높은 컴포넌트
 * @note 해당 자료형은 index가 Entity ID입니다.
 * @code
```
template <typename T>
class DenseComponent{
    private:

    public:
    T data;
};
```
 */
template <typename T>
class DenseComponent{
    private:

    public:
    T data;
};



template <typename T>
class ComponentPool{
    private:
    std::unique_ptr<std::vector<T>> Data;

    public:
    ComponentPool() : Data(std::make_unique<std::vector<T>>()) {}

    /**
     * @brief 소유권 이전 오퍼레이터 함수
     * @note  왼쪽 스마트 포인터로 소유권이 이전 됨
     * @note  단, 타입이 동일해야 함.
     */
    void operator=(ComponentPool B){
        Data = std::move(B.Data);
    }

    /**
     * @brief Data 삽입 함수
     */
    template <typename A>
    void push_back(A data){
        T input;
        input.data = data;
        Data->push_back(input);
    }

    T operator[](int index){
        T r = Data->at(index);
        return r;
    }
};

#endif
