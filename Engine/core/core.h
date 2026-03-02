#ifndef CORE
#define CORE

#include "../hal/HAL.h"

template <typename T>
class SparseComponent{
    private:

    public:
    int UUID;
    T data;
};

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

    void operator=(SmartPointer B){
        Data = std::move(B.Data);
    }
};


enum flag{
    Dense,
    Sparse
};

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
};

#endif
