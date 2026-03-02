#ifndef CORE
#define CORE

/*
컴포넌틑 매니저 정리 중
*/

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

/*
    복사자 생성 금지 코드 필요
*/
template <typename T>
class SmartPointer{
    private:

    public:
    ~SmartPointer(){
        delete(Data)
    }
    
    SmartPointer(){
        new std::vector<T> Data;
    }

    SmartPointer(const SmartPointer&) = delete;
    SmartPointer& operater=const SmartPointer& = delete;
}

class Registry{
    private:

    enum flag{
        Dense,
        Sparse
    };

    public:
    std::map<std::type_index, SmartPointer> Components;
    template <typename T>
    void CreateComponent(flag f){
        switch(f){
            case Dense:
                Components[typeid(T)] = SmartPointer<DenseComponent<T>>();
                break;

            case Sparse:
                Components[typeid(T)] = SmartPointer<SparseComponent<T>>();
                break;
        }
    };
};

#endif
