#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// 직업 열거형
enum Role { MAFIA, CITTZEN, DOCTOR };

// 전역 변수
int roleGamePlayers[10], IsAlive[10], totalPlayers;
int killTarget = 0, saveTarget = 0, playerVotes[10];

// --- 유틸리티 함수 ---
void clear() { system("cls"); }
void clearBuffer() { while (getchar() != '\n'); }
void pause() { printf("\n계속하려면 엔터를 누르세요...."); getchar(); }
void setColor(int color) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); }

// 타이핑 효과 (버퍼 오버플로우 방지)
void typingEffect(const char* message, int speed, int colorCode) {
    if (message == NULL || message[0] == '\0') return;
    setColor(colorCode);
    for (int i = 0; message[i] != '\0'; i++) {
        printf("%c", message[i]);
        fflush(stdout);
        Sleep(speed);
    }
    setColor(7);
    printf("\n");
}

// --- 승리 조건 체크 ---
int checkVictory() {
    int mafiaCount = 0, citizenCount = 0;
    for (int i = 0; i < totalPlayers; i++) {
        if (IsAlive[i] == 1) {
            if (roleGamePlayers[i] == MAFIA) mafiaCount++;
            else citizenCount++;
        }
    }
    if (mafiaCount == 0) {
        typingEffect("\n[시민 승리!] 모든 마피아를 소탕했습니다.", 50, 11);
        return 1;
    }
    if (mafiaCount >= citizenCount) {
        typingEffect("\n[마피아 승리!] 도시가 어둠에 잠겼습니다.", 50, 12);
        return 1;
    }
    return 0;
}

// --- 메인 메뉴 (깨짐 방지 ASCII 타이틀) ---
int menuScreen() {
    clear();
    int menuChoice = 0;

    printf("\n\n\n");
    setColor(12); // 빨간색 테두리
    printf("      ==================================================      \n");
    printf("     |                                                  |     \n");
    printf("     |    __  __   _    ___   ___    _      _           |     \n");
    printf("     |   |  \\/  | /_\\  | __| |_ _|  /_\\    | |          |     \n");
    setColor(15);
    printf("     |   | |\\/| |/ _ \\ | _|   | |  / _ \\   | |__        |     \n");
    printf("     |   |_|  |_/_/ \\_\\|_|   |___|/_/ \\_\\  |____|       |     \n");
    setColor(12);
    printf("     |                                                  |     \n");
    printf("     |            - G A M E  S T A R T -                |     \n");
    printf("      ==================================================      \n");

    printf("\n\n");
    setColor(14); // 노란색 메뉴
    printf("                       1. 게임 시작\n");
    printf("                       2. 게임 종료\n");

    printf("\n\n");
    setColor(11); // 하늘색
    printf("                선택 : ");
    setColor(7);

    if (scanf_s("%d", &menuChoice) != 1) { clearBuffer(); return 0; }
    clearBuffer();
    if (menuChoice == 2) exit(0);
    return (menuChoice == 1);
}

// --- [중요] 게임 설정 함수 (오류 해결 지점) ---
void gamePlayer() {
    printf("\n참여 인원 입력 (3~10): ");
    if (scanf_s("%d", &totalPlayers) != 1) totalPlayers = 4;
    clearBuffer();

    if (totalPlayers < 3) totalPlayers = 3;
    if (totalPlayers > 10) totalPlayers = 10;

    // 초기화
    for (int i = 0; i < totalPlayers; i++) {
        roleGamePlayers[i] = CITTZEN;
        IsAlive[i] = 1;
    }

    // 마피아 및 의사 설정
    int mafiaCount = (totalPlayers / 4 < 1) ? 1 : totalPlayers / 4;
    for (int i = 0; i < mafiaCount; i++) roleGamePlayers[i] = MAFIA;
    roleGamePlayers[mafiaCount] = DOCTOR;

    // 셔플 연출
    clear();
    printf("\n\n\n\n");
    printf("              [ 카드를 섞고 있습니다... ]\n");
    printf("              ");
    for (int i = 0; i < 10; i++) {
        printf("■ ");
        fflush(stdout);
        Sleep(200);
    }
    printf("\n");

    // 실제 데이터 셔플
    srand((unsigned int)time(NULL));
    for (int i = totalPlayers - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = roleGamePlayers[i];
        roleGamePlayers[i] = roleGamePlayers[j];
        roleGamePlayers[j] = temp;
    }

    // 직업 확인 연출
    clear();
    printf("\n\n\n\n");
    typingEffect("       당신의 운명이 결정되었습니다...", 80, 15);
    Sleep(1000);

    printf("\n       당신의 번호는 [ 1번 ] 입니다.\n");
    printf("       당신의 직업은... ");

    // 긴장감 조성 (점 3개)
    for (int i = 0; i < 3; i++) {
        Sleep(600);
        printf(". ");
        fflush(stdout);
    }
    Sleep(1000);

    // 직업에 따른 색상 및 텍스트 연출
    if (roleGamePlayers[0] == MAFIA) {
        typingEffect("[ 마피아 ]", 150, 12); // 빨간색
        printf("\n       다른 시민들 몰래 도시를 장악하세요.\n");
    }
    else if (roleGamePlayers[0] == DOCTOR) {
        typingEffect("[ 의사 ]", 150, 10); // 초록색
        printf("\n       매일 밤 죽음의 위기에서 시민을 구하세요.\n");
    }
    else {
        typingEffect("[ 시민 ]", 150, 11); // 하늘색
        printf("\n       마피아를 찾아내어 도시의 평화를 지키세요.\n");
    }

    printf("\n");
    pause();
}

// --- 밤의 단계 ---
void mafiaPlayer() {
    printf("\n[ 어두운 밤, 마피아가 타겟을 고릅니다. ]\n");
    if (roleGamePlayers[0] == MAFIA) {
        while (1) {
            printf("제거할 번호: ");
            if (scanf_s("%d", &killTarget) == 1 && killTarget > 0 && killTarget <= totalPlayers && IsAlive[killTarget - 1] == 1) {
                clearBuffer(); break;
            }
            clearBuffer();
        }
    }
    else {
        int att = 0;
        while (att++ < 100) {
            killTarget = (rand() % totalPlayers) + 1;
            if (IsAlive[killTarget - 1] == 1 && roleGamePlayers[killTarget - 1] != MAFIA) break;
        }
        Sleep(1000);
    }
}

void doctorPlayer() {
    printf("\n[ 의사가 조용히 가방을 챙깁니다. ]\n");
    if (roleGamePlayers[0] == DOCTOR) {
        printf("치료할 번호: ");
        scanf_s("%d", &saveTarget); clearBuffer();
    }
    else {
        int att = 0;
        while (att++ < 100) {
            saveTarget = (rand() % totalPlayers) + 1;
            if (IsAlive[saveTarget - 1] == 1) break;
        }
        Sleep(1000);
    }
}

// --- 토론 단계 ---
void discussionPhase() {
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("        자 유 토 론 시 간 (추리)\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    const char* lines[] = { "누가 마피아일까?", "나는 진짜 시민이야!", "의사가 날 살려주겠지?", "말 없는 사람이 수상해." };
    int talkCount = 0;
    for (int i = 0; i < totalPlayers && talkCount < 3; i++) {
        if (IsAlive[i] == 1 && (rand() % 2 == 0)) {
            char buf[512];
            sprintf_s(buf, sizeof(buf), "[%d번 플레이어]: %s", i + 1, lines[rand() % 4]);
            typingEffect(buf, 40, (i == 0 ? 15 : 11));
            Sleep(500); talkCount++;
        }
    }
    pause();
}

// --- 투표 단계 ---
void playerVote() {
    for (int i = 0; i < totalPlayers; i++) playerVotes[i] = 0;
    for (int i = 0; i < totalPlayers; i++) {
        if (IsAlive[i]) {
            if (i == 0) {
                int v;
                while (1) {
                    printf("투표 대상 번호: ");
                    if (scanf_s("%d", &v) == 1 && v > 0 && v <= totalPlayers && IsAlive[v - 1]) {
                        playerVotes[v - 1]++; clearBuffer(); break;
                    }
                    clearBuffer();
                }
            }
            else {
                int av; do { av = rand() % totalPlayers; } while (!IsAlive[av]);
                playerVotes[av]++;
            }
        }
    }
    int max = -1, target = -1, tie = 0;
    for (int i = 0; i < totalPlayers; i++) {
        if (playerVotes[i] > max) { max = playerVotes[i]; target = i; tie = 0; }
        else if (playerVotes[i] == max && max > 0) tie = 1;
    }
    if (tie) typingEffect("동표로 인해 아무도 처형되지 않았습니다.", 50, 14);
    else if (target != -1) {
        char m[512]; sprintf_s(m, sizeof(m), "투표 결과 [%d번] 플레이어가 처형되었습니다.", target + 1);
        typingEffect(m, 60, 12);
        IsAlive[target] = 0;
    }
}

// --- 메인 로직 ---
int main() {
    while (!menuScreen());
    gamePlayer(); // 이제 오류 없이 작동합니다
    pause();

    while (1) {
        clear();
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n          밤 이 되 었 습 니 다\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        killTarget = 0; saveTarget = 0;
        mafiaPlayer();
        doctorPlayer();
        pause();

        clear();
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n          아 침 이 밝 았 습 니 다\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        if (killTarget > 0 && killTarget == saveTarget) {
            typingEffect("★ 의사가 마피아의 공격을 저지했습니다! 사망자가 없습니다.", 60, 10);
        }
        else if (killTarget > 0) {
            IsAlive[killTarget - 1] = 0;
            char msg[512]; sprintf_s(msg, sizeof(msg), "안타깝게도 밤 사이 [%d번]이 희생되었습니다.", killTarget);
            typingEffect(msg, 60, 12);
        }

        if (checkVictory()) break;
        pause();

        clear();
        discussionPhase();

        clear();
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n          낮 의 투 표 시 간\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        playerVote();
        if (checkVictory()) break;
        pause();
    }
    return 0;
}