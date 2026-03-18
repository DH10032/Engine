#pragma once

// 엔진 전체에서 공통으로 사용할 추상화된 키 코드
enum class KeyCode {
    W, A, S, D, Space, Escape, 
    Left, Right, Up, Down,
    Mouse_Left, Mouse_Right,
    Unknown
};

class HAL {
public:
    virtual ~HAL() {}

    // 하드웨어 초기화 및 종료
    virtual bool Initialize() = 0;
    virtual void Shutdown() = 0;

    // 매 프레임마다 하드웨어 신호(이벤트)를 갱신
    virtual void PollEvents() = 0;

    // 물리적 키 상태 확인 (InputManager가 호출할 함수)
    virtual bool IsKeyDown(KeyCode key) const = 0;

    // 윈도우 종료 이벤트 발생 여부 (엔진 루프 제어용)
    virtual bool ShouldQuit() const = 0;
};
