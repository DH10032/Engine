#ifndef CORE
#define CORE

#include "../hal/HAL.h"

/*
큰 뼈대 로직만 작성해서 Game에서 sort비교 기준 함수를 전달해주면, 이를 토대로 비교하면 정렬

컴포넌트 배열은 기본적으로 정렬을 유지하며, 삽입, 삭제가 빨라야 한다.
B-Tree로 구현 안됨 => 메모리상 일렬 유지가 아닌 점프가 발생

공통 : 삽입, 삭제 성능 위주 고려

SparseComponent : 정렬 유지 x


DenseComponent  : 정렬 유지 o
탐색 : 이진 탐색

    [컴포넌트 계층]
     기본 컴포넌트
     분류 컴포넌트
     특화 컴포넌트
     특수 컴포넌트
*/


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
    void operator=(const ComponentPool<T>& B){
        Data = std::make_unique<std::vector<T>>(*B.Data);
    }

    /**
     * @brief Data 삽입 함수
     * @넣는 순서대로 index 증가
     */
    template <typename A>
    void add(const A data){
        T input;
        input.data = data;
        Data->push_back(input);
    }

    template <typename A>
    void del(A data){

    }

    /**
     * @brief Data 반환 함수
     * @note 복사가 발생
     */
    auto& operator[](const int index){
        return Data->at(index).data;
    }
};

#endif
