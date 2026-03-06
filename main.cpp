#include "main.h"

struct test{
    int a;
    int b;
};

int main()
{
    Engine::GameManager system;
    system.ShowWindow();
    system.LoadAsset("Game/data/asset.json");
    
    // test 코드입니다.
    // test 타입 변수 d 선언
    test d = {
        .a = 1,
        .b = 2
    };

    // 컴포넌트 A 선언 타입 DenseComponent
    DenseComponentPool<test> A;

    // A에 d삽입
    A.add(d);

    // operator를 통해 배열처럼 접근되는 것처럼 보이게 했습니다.
    // 연사자 []를 통해 접근하면 됩니다.
    test r = A[0];

    // 출력
    std::cout << r.a << std::endl;
    std::cout << r.b << std::endl;

    DenseComponentPool<test> B;


    B=A;

    r = B[0];
    std::cout << r.a << std::endl;
    std::cout << r.b << std::endl;

    for(;;){
        system.DrawObject();
        SDL_Delay(30);
    }

    system.Destroy_Object();
}