# Engine - Game Architecture

```
.
├── DOCS
│   ├── Interface.md
│   ├── memory.md
│   ├── 게임 진행.md
│   ├── 계획.md
│   └── 중요.md
├── Engine
│   ├── Interface
│   │   ├── Interface.cpp
│   │   └── Interface.h
│   ├── core
│   │   ├── assetManager
│   │   │   ├── assetManager.cpp
│   │   │   └── assetManager.h
│   │   ├── core.cpp
│   │   └── core.h
│   ├── graphic
│   │   ├── animation
│   │   │   ├── animation.cpp
│   │   │   └── animation.h
│   │   ├── camera
│   │   │   ├── camera.cpp
│   │   │   └── camera.h
│   │   ├── font
│   │   │   ├── font.cpp
│   │   │   └── font.h
│   │   ├── renderer
│   │   │   ├── render.cpp
│   │   │   ├── render.h
│   │   │   ├── shader.cpp
│   │   │   └── shader.h
│   │   └── window
│   │       ├── window.cpp
│   │       └── window.h
│   └── hal
│       ├── HAL.h
│       └── UseSDL.cpp
├── Game
│   ├── ai
│   │   ├── ai.cpp
│   │   └── ai.h
│   ├── assets
│   │   ├── fonts
│   │   │   └── bitlim.ttf
│   │   └── img
│   │       ├── buildings
│   │       │   └── hive.png
│   │       ├── character
│   │       │   ├── bug1.png
│   │       │   ├── earthworm.png
│   │       │   ├── test.jpg
│   │       │   └── unit_type1
│   │       │       ├── body
│   │       │       │   └── body1.png
│   │       │       ├── chin
│   │       │       │   ├── chin1.png
│   │       │       │   ├── chin2.png
│   │       │       │   └── chin3.png
│   │       │       └── leg
│   │       │           ├── leg1.png
│   │       │           ├── leg2.png
│   │       │           └── leg3.png
│   │       ├── interactives
│   │       │   └── apple.png
│   │       └── tiles
│   │           └── grass.png
│   ├── data
│   │   ├── action.json
│   │   ├── asset.json
│   │   └── terrain.json
│   ├── unit
│   │   ├── unit.cpp
│   │   └── unit.h
│   └── world
│       ├── perlinNoise.cpp
│       ├── world.cpp
│       └── world.h
├── Makefile
├── README.md
├── Set.sh
├── main.cpp
├── main.h
└── tools
    └── action_tool.py
```
