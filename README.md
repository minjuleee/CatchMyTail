🎮 Catch My Tail 

콘솔 기반 2인 대전 게임 Catch My Tail 는 제한된 공간 안에서 플레이어가 상대의 꼬리를 잡으면 승리하는 게임입니다.
라운드가 진행될수록 맵과 장애물이 증가해 더욱 전략적인 플레이가 요구됩니다.

📌 1. 프로젝트 소개

Catch My Tail 는 2명의 플레이어가 콘솔 화면에서 서로를 피하고 공격하며 승부를 내는 대전 액션 게임입니다.

🕹️ 2. 게임 주요 기능

2인 플레이: P1(WASD), P2(방향키)

초기 생명 5개

아이템 시스템

♥ : 하트 +1

■ : 하트 -1 (장애물)

충돌 승리 조건: 상대 꼬리 또는 몸통과 충돌 시 즉시 라운드 승리(상대 하트 -5)

라운드 시간 제한 60초

총 3라운드, 라운드를 많이 이긴 플레이어가 최종 승리

라운드가 올라갈수록 장애물 증가 / 맵 구조 복잡

🖼️ 3. 실행 화면
✔ 초기 화면
<img width="1435" height="840" alt="image" src="https://github.com/user-attachments/assets/c1fbce94-1123-420e-8094-ed2a5eeb7568" />
게임 시작 / BGM 토글 / 게임 종료 메뉴

✔ 라운드 로딩 화면
<img width="1432" height="841" alt="image" src="https://github.com/user-attachments/assets/5b75f75a-4fe5-4d33-8954-216cb625c5c3" />
각 라운드 시작 전 표시되는 화면

✔ 라운드 게임 화면
<img width="1440" height="841" alt="image" src="https://github.com/user-attachments/assets/ddf4ca79-6262-4fd8-93a6-bcb9e9fe1588" />
<img width="1440" height="840" alt="image" src="https://github.com/user-attachments/assets/7ecf90a5-88c5-43aa-a3d1-1e90d5cd3f5d" />
<img width="1438" height="846" alt="image" src="https://github.com/user-attachments/assets/cef02809-39b3-4514-bc9d-7c041c5623ae" />
아이템이 움직이며, 두 플레이어가 공격하는 주요 화면
라운드 별로 맵과 장애물 개수 증가

✔ 라운드 승리 화면
<img width="1435" height="838" alt="image" src="https://github.com/user-attachments/assets/de7beb41-5e2e-4177-940d-d98af3473351" />
각 라운드 종료 후 승자 표시

✔ 최종 결과 화면
<img width="1441" height="847" alt="image" src="https://github.com/user-attachments/assets/65bb33bd-5f37-4e75-9b90-3b306188029f" />
3라운드 전체 승패를 합산한 최종 결과

(첨부된 스크린샷 참고)

📹 4. 시연 영상

👉 https://github.com/user-attachments/assets/d92c4821-1223-4e92-b656-33df6332e36d

🎮 5. 조작 방법
플레이어	조작 키
P1	W A S D
P2	← ↑ → ↓
메뉴 키	S(시작), 0(BGM 토글), Q(종료)

🧩 6. 게임 구조 설명

라운드 구조: 1 → 2 → 3라운드

난이도 상승: 라운드가 진행될수록 장애물/맵 변화

충돌 판정: 꼬리 또는 몸체와 접촉 시 상대 즉시 패배

아이템 스폰: 라운드별 등장 규칙 존재

📁 7. 프로젝트 구조
CatchMyTail/
├─ src/
│  ├─ main.c
│  ├─ game.c
│  ├─ screen.c
│  ├─ map.c
│  ├─ item.c
│  ├─ player.c
│  ├─ sound.c
│  └─ *.h
└─ assets/
   ├─ bgm1.wav
   ├─ bgm2.wav
   ├─ bgm3.wav
   └─ bgm4.wav

⚙️ 8. 빌드 & 실행 방법
✔ Visual Studio

콘솔 프로젝트 생성

모든 .c/.h 파일 추가

Project → Properties → Linker → Input → Additional Dependencies

Winmm.lib 추가

빌드 후 실행

✔ MinGW (gcc)
gcc -o CatchMyTail.exe main.c game.c screen.c map.c item.c sound.c -lwinmm

🛠️ 9. 사용 기술

C 언어

Windows.h 콘솔 API

PlaySound (WinMM)

콘솔 기반 UI/게임 구현

📄 10. 라이선스 & 개발자

Developer: minjuleee

License: MIT License

Contact: lmj26106058@gmail.com
