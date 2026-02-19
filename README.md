# Engine - Game Architecture

```
engine/
├── graphic/
│   ├── window/
│   │   ├── window.h
│   │   └── window.cpp        # window_info, Create_window, Destroy_window
│   ├── renderer/
│   │   ├── render.h
│   │   ├── render.cpp        # SDL 렌더링 파이프라인, Set_draw_all
│   │   ├── shader.h
│   │   └── shader.cpp        # OpenGL 셰이더
│   ├── camera/
│   │   ├── camera.h
│   │   └── camera.cpp        # 카메라 뷰
│   ├── font/
│   │   ├── font.h
│   │   └── font.cpp          # TTF_start, TTF_Create, TTF_end
│   ├── color/
│   │   └── color.h           # SDL_Color 상수
│   └── animation/
│       ├── animation.h
│       └── animation.cpp     # 각속도 신호 기반 애니메이션
│
├── asset/
│   ├── asset.h
│   └── asset.cpp             # 파일 → SDL_Texture* 변환 (Path_to_Texture)
│
└── core/
    ├── core.h
    ├── core.cpp              # ECS, 게임루프 연결
    ├── memory.h
    └── memory.cpp            # UnitStorage, append_unit, set_memory_unit

game/
├── units/
│   ├── units.h
│   └── units.cpp             # Unit/Tile 구조체, 스탯 정의
├── world/
│   ├── world.h
│   ├── world.cpp             # 타일 맵 생성 및 렌더링
│   └── seed.cpp              # Perlin 노이즈 맵 생성
├── ai/
│   ├── ai.h
│   ├── ai.cpp                # 유닛 제어
│   ├── hive.h
│   └── hive.cpp              # 하이브마인드, 목표 결정
├── action/
│   ├── action.h
│   ├── action.cpp            # 함수 포인터 테이블
│   └── action_loader.cpp     # action.json 파싱
├── asset/
│   ├── game_asset.h
│   └── game_asset.cpp        # buildings/character/tiles 분류 (Load_Asset)
└── data/
    ├── asset.json
    ├── action.json
    ├── balance.json
    └── hive_config.json

tools/
└── action_tool.py

main.cpp
main.h
```
