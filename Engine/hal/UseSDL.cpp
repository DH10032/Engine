#include "HAL.h"
#include <SDL2/SDL.h>
#include <unordered_map>

class UseSDL : public HAL {
private:
    const Uint8* m_KeyboardState = nullptr;
    bool m_QuitRequested = false;
    std::unordered_map<KeyCode, SDL_Scancode> m_KeyMap;

public:
    UseSDL() {
        // 엔진 KeyCode와 SDL 스캔코드를 1:1 대응시킵니다.
        m_KeyMap[KeyCode::W] = SDL_SCANCODE_W;
        m_KeyMap[KeyCode::A] = SDL_SCANCODE_A;
        m_KeyMap[KeyCode::S] = SDL_SCANCODE_S;
        m_KeyMap[KeyCode::D] = SDL_SCANCODE_D;
        m_KeyMap[KeyCode::Space] = SDL_SCANCODE_SPACE;
        m_KeyMap[KeyCode::Escape] = SDL_SCANCODE_ESCAPE;
    }

    bool Initialize() override {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) return false;
        return true;
    }

    void Shutdown() override {
        SDL_Quit();
    }

    void PollEvents() override {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                m_QuitRequested = true;
            }
        }
        // 키보드 전체 상태를 한 번에 캡처 (가장 효율적인 방식)
        m_KeyboardState = SDL_GetKeyboardState(NULL);
    }

    bool IsKeyDown(KeyCode key) const override {
        if (!m_KeyboardState) return false;
        
        auto it = m_KeyMap.find(key);
        if (it != m_KeyMap.end()) {
            // SDL 상태 배열에서 해당 키가 1(눌림)인지 확인
            return m_KeyboardState[it->second];
        }
        return false;
    }

    bool ShouldQuit() const override { return m_QuitRequested; }
};
