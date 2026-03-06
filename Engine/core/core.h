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
*/

/*
EntityManager class가 필요한 이유
Component에 id로 정의되는 Entity들을 관리하기 위해 필요
Entity는 필요적으로 Sparse와 Dense가 혼합된 Componet들로 관리가 됨
이를 유지하기 위해 Entity 내부에서 관리가 필요

근데 이렇게 할려면 기본 컴포넌트 클래스를 생성
컴포넌트 풀에 상속 시킴
Entity에서 기본 컴포너틑를 이들 클래스를 다운, 업 캐스팅으로 관리
*/

/**
 * @brief 밀도가 높은 컴포넌트의 원소
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

class BaseComponent{
    BaseComponent() = default;
};

/**
 * @brief 밀도가 높은 컴포넌트의 원소
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
class DenseComponent : public BaseComponent{
    public:
    T data;
};

template <typename T>
class DenseComponentPool{
    private:
    std::unique_ptr<std::vector<DenseComponent<T>>> Data;
    
    public:
    DenseComponentPool() : Data(std::make_unique<std::vector<DenseComponent<T>>>()) {}

    /**
     * @brief 소유권 이전 오퍼레이터 함수
     * @note  왼쪽 스마트 포인터로 소유권이 이전 됨
     * @note  단, 타입이 동일해야 함.
     */
    void operator=(const DenseComponentPool<T>& B){
        Data = std::make_unique<std::vector<DenseComponent<T>>>(*B.Data);
    }

    /**
     * @brief Data 삽입 함수
     * @넣는 순서대로 index 증가
     */
    template <typename A>
    void add(const A data){
        DenseComponent<T> input;
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

/**
 * @brief CoponnetPool들을 관리할 개체
 */
class Entity : public BaseComponent{
    private:
        std::map<std::type_index, BaseComponent&> Components;

    public:
        /**
         * @brief 반환 연산 함수
         */
        void operator[](std::string name){
            
        }
};

#endif
