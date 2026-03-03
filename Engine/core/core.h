#ifndef CORE
#define CORE

#include "../hal/HAL.h"
/*
ECS 패턴을 위한 자료형
RAII 패턴 포함
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

class BaseComponent{
    public:
    virtual ~BaseComponent() = default;
};


template <typename T>
class SmartPointer : public BaseComponent{
    private:
    std::unique_ptr<std::vector<T>> Data;

    public:
    SmartPointer() : Data(std::make_unique<std::vector<T>>()) {}

    /**
     * @brief 소유권 이전 오퍼레이터 함수
     * @note  왼쪽 스마트 포인터로 소유권이 이전 됨
     * @note  단, 타입이 동일해야 함.
     */
    void operator=(SmartPointer B){
        Data = std::move(B.Data);
    }

    /**
     * @brief Data 삽입 함수
     */
    void push_back(int id, T data){
        Data.push_back(data);
    }

    T circuit(){

    }
};


enum flag{
    Dense,
    Sparse
};

/**
 * @brief GameObject를 관리하는 저장소 클래스
 * @note  Registry 내분에는 중복된 타입이 존재할 수 없기에 추상화 필요
 */
class Registry{
    private:
    
    public:
    std::map<std::type_index, std::unique_ptr<BaseComponent>> Components;


    template <typename T>
    void CreateComponent(flag f){
        switch(f){
            case Dense:
                Components[typeid(T)] = std::make_unique<SmartPointer<DenseComponent<T>>>();
                break;

            case Sparse:
                Components[typeid(T)] = std::make_unique<SmartPointer<SparseComponent<T>>>();
                break;
        }
    };

    template <typename T>
    void push(T data){
        SmartPointer<T>* Data = &Components[typeid(T)];
        Data.push_back(0, data);
    };
};

#endif
