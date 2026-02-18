# Engine - Game Architecture

```
project/
├── main.cpp
│
├── core/                        # 순수 데이터/로직 (렌더링 무관)
│   ├── core.h
│   ├── core.cpp                 # 메모리 관리, ECS
│   ├── types.h                  # 구조체 정의 (Unit, Tile 등)
│   │
│   ├── systems/                 # 게임 로직
│   │   ├── combat_system.cpp    # 전투
│   │   ├── save_system.cpp      # 저장/로드
│   │   └── physics_system.cpp   # 충돌, 이동
│   │
│   └── ai/                      # 하이브마인드
│       ├── hive_system.cpp      # 목표 결정
│       ├── ai_system.cpp        # 유닛 제어
│       ├── decision.cpp         # 의사결정
│       └── action_loader.cpp    # JSON 파싱
│
├── render/                      # 렌더링만 담당
│   ├── render.h                 # 외부 API
│   ├── render.cpp               # 렌더링 파이프라인
│   ├── camera.cpp               # 카메라
│   ├── animation.cpp            # 애니메이션
│   ├── font.cpp                 # 폰트
│   └── shader/                  # 쉐이더
│       └── ...
│
├── world/                       # 맵/월드 관련
│   ├── world.h
│   ├── world.cpp
│   ├── seed.cpp                 # 맵 생성 (Perlin)
│   └── tile.cpp                 # 타일 관리
│
├── asset/                       # 리소스 관리
│   ├── asset_manager.h
│   ├── asset_manager.cpp        # 텍스처/사운드 로드
│   └── texture/
│       └── ...
│
├── data/                        # JSON 데이터
│   ├── actions.json
│   ├── unit_types.json
│   ├── hive_config.json
│   └── balance.json
│
├── mods/                        # 모드 지원
│   └── ...
│
├── save/                        # 세이브 파일
│   └── ...
│
└── tools/                       # 개발 도구 (Python)
    └── ...
```
