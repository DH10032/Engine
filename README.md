# Engine - Game Architecture

## 📊 프로젝트 구조 다이어그램
```
project/
├── engine/              # C++ (성능 핵심)
│   ├── core.cpp         # ECS 및 메모리 관리 코어
│   │
│   ├── rendering/       # 렌더링
│   │   ├── renderer.h          // 외부로 노출시킬 API (모드 떄문)
│   │   ├── renderer.cpp        // 내부 동작
│   │   └── camera.cpp          // 카메라 조작 라이브러리
│   │
│   ├── systems/
│   │   ├── hive_system.cpp
│   │   ├── ai_system.cpp        # AI도 C++
│   │   ├── save_system.cpp
│   │   ├── gather_system.cpp
│   │   └── combat_system.cpp
│   │
│   └── ai_data/                 # AI 엔진
│       ├── decision.cpp 
│       ├── evaluator.cpp
│       └── action_loader.cpp    # JSON 읽기
│
├── character/
│   └── image.jpg
│
├── data/                        # 게임 데이터 (쉬운 수정)
│   ├── actions.json
│   ├── unit_types.json
│   ├── hive_config.json
│   └── balance.json
│
├── mods/                        # Lua
│   └── custom_ai/
│       └── ai.lua
│
├── tools/                       # Python 도구들 (엔진 디버깅용)
│   ├── data_editor.py           # 데이터 편집기
│   ├── balance_test.py          # 밸런스 테스트
│   └── replay_viewer.py         # 리플레이 분석
│
└── main.cpp
```