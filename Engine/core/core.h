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

class Registry{
    private:
    enum flag{
        Dense,
        Sparse
    };
    public:
    std::map<std::type_index, void*> Components;
    template <typename T>
    void CreateComponent(flag f){
        switch(f){
            case Dense:
                Components[typeid(T)] = new std::vector<DenseComponent<T>>();
                break;

            case Sparse:
                Components[typeid(T)] = new std::vector<SparseComponent<T>>();
                break;
        }
    };

};


#endif
