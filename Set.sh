#!/bin/bash

# Lock 파일 제거
rm -f /tmp/.X99-lock /tmp/.X11-unix/X99 2>/dev/null

# 이미 실행 중인지 확인
if pgrep -x "Xvfb" > /dev/null; then
    echo "VNC가 이미 실행 중입니다."
else
    # 패키지가 없으면 설치
    if ! command -v x11vnc &> /dev/null; then
        sudo apt-get update
        sudo apt-get install -y xvfb x11vnc novnc websockify libsdl2-image-dev libsdl2-dev
    fi
    
    # 서비스 시작
    Xvfb :99 -screen 0 1280x720x24 > /dev/null 2>&1 &
    sleep 1
    
    x11vnc -display :99 -nopw -listen 0.0.0.0 -xkb -forever > /dev/null 2>&1 &
    sleep 1
    
    # noVNC 경로 확인 후 실행
    if [ -d "/usr/share/novnc" ]; then
        websockify -D --web=/usr/share/novnc/ 6080 localhost:5900
    else
        # noVNC 없으면 web 옵션 없이 실행
        websockify 6080 localhost:5900 > /dev/null 2>&1 &
    fi
    
    echo "VNC 서버 시작 완료!"
fi

# DISPLAY 설정 (중요: source로 실행해야 적용됨)
# 아래 실행하기
: '
export DISPLAY=:99
export XDG_RUNTIME_DIR=/tmp/runtime-codespace
export SDL_VIDEODRIVER=x11
mkdir -p $XDG_RUNTIME_DIR
chmod 700 $XDG_RUNTIME_DIR
'