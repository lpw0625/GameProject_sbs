#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// 직업 열거형
enum Role { MAFIA, CITTZEN, DOCTOR };

// 전역 변수
int roleGamePlayers[10], IsAlive[10], totalPlayers;
int killTarget = 0, saveTarget = 0, playerVotes[10];

// 마피아에게 살해된 경우 나오는 대사.
const char* killMessages[] = {
    "어둠 속에서 짓눌린 비명이 터져 나왔습니다. 차가운 흉기가 살점을 파고드는 감촉이 그의 마지막 감각이었습니다.",

    "바닥을 적시는 것은 쏟아진 와인이 아니었습니다. 뿜어져 나온 선혈이 기괴한 무늬를 그리며 번져 나갑니다.",

    "찢겨진 옷가지와 사방에 흩뿌려진 붉은 흔적만이 그곳에서 일어난 참혹한 학살을 증명하고 있습니다.",

    "그의 목소리는 끊어지는 숨결과 함께 잦아들었습니다. 마피아는 피 묻은 손을 닦으며 유유히 사라졌습니다.",

    "차갑게 식어가는 육신 위로 죽음의 그림자가 드리웁니다. 도시는 이제 누군가의 비릿한 피 냄새로 가득합니다.",

    "그의 눈동자는 공포로 뒤틀린 채 굳어버렸습니다. 마지막 순간 마주한 절망은 영원히 침묵 속에 잠겼습니다.",

    "무자비한 타격 소리가 멈추고, 광장에는 오직 뚝뚝 떨어지는 핏방울 소리만이 정적을 깨우고 있습니다.",

    "도려내진 영혼의 흔적이 방 안을 가득 채웁니다. 그는 살려달라는 애원조차 허락받지 못한 채 도살되었습니다."
};
int totalKillMessages = 8;

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

void dramaticTyping(const char* message, int speed, int colorCode) 

{
    if (message == NULL || message[0] == '\0') 
        
      return;
    setColor(colorCode);

    for (int i = 0; message[i] != '\0'; i++) 
    
    {
        printf("%c", message[i]);
        fflush(stdout);

        // 아주 낮고 불쾌한 소리 (150Hz)로 심리적 압박감 부여
        if (message[i] != ' ' && message[i] != '.') 
        
        {
            Beep(150, 40);
        }

        Sleep(speed); // 추천 속도: 100ms
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

    if (scanf_s("%d", &totalPlayers) != 1)

    {
        totalPlayers = 4;
    }
    clearBuffer();

    if (totalPlayers < 3) totalPlayers = 3;
    if (totalPlayers > 10) totalPlayers = 10;

    // 초기화
    for (int i = 0; i < totalPlayers; i++) 
    {
        roleGamePlayers[i] = CITTZEN;
        IsAlive[i] = 1;
    }

    // 마피아 및 의사 설정
    int mafiaCount = 1;

    if (totalPlayers >= 10)
    {
        mafiaCount = 3; // 10명이면 3명
    }
    else if (totalPlayers >= 7) {
        mafiaCount = 2; // 7~9명이면 2명.
    }

    for (int i = 0; i < mafiaCount;)
    { 

        int r = rand() % totalPlayers;

        if (roleGamePlayers[r] == CITTZEN)
        {

            roleGamePlayers[r] = MAFIA;
            i++;
        }
    }

    int doctorPlaced = 0;
    while (doctorPlaced < 1)
    {
        int r = rand() % totalPlayers;
        if (roleGamePlayers[r] == CITTZEN)
        {
            roleGamePlayers[r] = DOCTOR;
            doctorPlaced = 1;
        }
    }
        
     
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

    for (int i = totalPlayers - 1; i > 0; i--) 
    {
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
void mafiaPlayer() 
{
    // 마피아가 모두 죽었는지 먼저 체크

    int mafiaAlive = 0;

    for (int i = 0; i < totalPlayers; i++)
    {
        if (roleGamePlayers[i] == MAFIA && IsAlive[i] == 1)
            mafiaAlive = 1;
    }
    if (!mafiaAlive)

        return;// 


    printf("\n[ 어두운 밤, 마피아가 타겟을 고릅니다. ]\n");
    if (roleGamePlayers[0] == MAFIA && IsAlive[0] == 1) 
    {
        while (1) 
        
        {
            printf("제거할 번호: ");
            if (scanf_s("%d", &killTarget) == 1 && killTarget > 0 && killTarget <= totalPlayers && IsAlive[killTarget - 1] == 1) 
            
            {
                clearBuffer(); 
                
                break;
            }
            clearBuffer();
        }
    }
    else {
        int att = 0;
        while (att++ < 100) 
        
        {
            killTarget = (rand() % totalPlayers) + 1;

            if (IsAlive[killTarget - 1] == 1 && roleGamePlayers[killTarget - 1] != MAFIA) 
                
                break;
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
void playerVote()
{
    for (int i = 0; i < totalPlayers; i++)

    {
        playerVotes[i] = 0;
    }

        printf("\n[모든 생존자가 광장에 모여 서로를 의심하기 시작합니다...] \n\n ");

    Sleep(1200);



    for (int i = 0; i < totalPlayers; i++)

    {
        if (IsAlive[i] == 1)

        {
            if (i == 0)

            {
                int v;
                while (1) {
                    printf("당신은 누구를 처형대로 보내겠습니까? [투표 대상 번호]: ");
                    setColor(7);
                    if (scanf_s("%d", &v) == 1 && v > 0 && v <= totalPlayers && IsAlive[v - 1])

                    {
                        playerVotes[v - 1]++;
                        clearBuffer();
                        break;
                    }
                    printf("잘못된 입력이거나 이미 사망한 플레이어입니다.\n");
                    clearBuffer();
                }
            }
            else  // 컴퓨터끼리 투표 (무한루프 방지)
            {
                int av;

                do
                {

                    av = rand() % totalPlayers;

                }

                while (IsAlive[av] == 0); // 살아있는 플레이어를 찾을때까지 루프.

                playerVotes[av]++;
            }
        }
    }

    printf("\n[개표 진행 중... 광장에서는 무거운 정적이 흐릅니다... ] \n");

    for (int i = 0; i < 3; i++)

    {
        printf(" . "); Sleep(800);
    }

    printf("\n\n");


    int max = -1,
        target = -1,
        tie = 0;

    for (int i = 0; i < totalPlayers; i++)
    {
        if (IsAlive[i])

        {
            printf("[%d번 플레이어] : %d 표\n", i + 1, playerVotes[i]);
            Sleep(800);

            if (playerVotes[i] > max)
            {
                max = playerVotes[i];
                target = i;
                tie = 0; // 더 높은 득표자가 나오면 동프 상태 해제 
            }
            else if (playerVotes[i] == max && max > 0)
            {
                tie = 1;
            }
        }
    }

    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    Sleep(1000);

    if (tie)
    {
        typingEffect("[!] 시민들의 분노가 분산이 되었습니다. 아무도 처형대로 끌려가지 않았습니다.", 50, 14);

    }
    else if (target != -1)
    {
        IsAlive[target] = 0;

       
        setColor(12); // 진한 빨간색
        printf("[!] 중요사항....! 최종 판결이 내려졌습니다.", 100, 12);
        Sleep(800);


        setColor(14);
        printf("교수형을 집행할 집행관들이 % d번 플레이어를 억류합니다.\n", target + 1);
        Sleep(1500);

        setColor(8);
        printf("   \"난 아니야! 제발! 살려줘!!\"\n");
        Sleep(1000);
        printf("그의 절규가 광장에 울려 퍼집니다.\n");
        Sleep(2000);

        setColor(12);
        typingEffect("   [!] 차가운 바람이 부는 광장 한가운데... 밧줄이 팽팽해지며, 그는 밧줄에 목이 메인 채 숨을 거두었습니다.", 70, 12);
        Sleep(1500);

        printf(" 광장 바닥은 그의 ");
        setColor(4);

        printf("검붉은 핏물");
        setColor(12);
        printf("로 서서히 젖어갑니다....\n");

        Sleep(2000);

        printf("\n   ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        if (roleGamePlayers[target] == MAFIA)
        { 

        setColor(11);
        printf("   [ 확인 ] 죽은 자의 소지품에서 마피아의 표식이 발견되었습니다.\n");
        printf("   그는 사악한 [ 마피아 ] 였습니다.\n");

        } 
        
        else

        {

            setColor(8);
            printf("   [ 확인 ] 그의 소지품에는 가족사진 한 장뿐이었습니다.\n");
            printf("   그는 무고한 [ 시민 ] 이었습니다.\n");
        }

    }

    printf("   ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    setColor(7);
}



void showGameResult()
{
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("         [ 게 임  결 과  공 개 ]\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

    for (int i = 0; i < totalPlayers; i++)
    {
        printf(" [%d번 플레이어] : ", i + 1);

        if (roleGamePlayers[i] == MAFIA)
        {
            setColor(12); printf("마피아 (MAFIA)\n");
        }
        else if (roleGamePlayers[i] == DOCTOR)
        {
            setColor(10); printf("의사 (DOCTOR)\n");
        }
        else {
            setColor(11); printf("시민 (CITIZEN)\n");
        }
        setColor(7); // 색상 초기화
        Sleep(500);  // 한 명씩 천천히 공개되는 연출
    }
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}

   

int main() 
{
    srand((unsigned int)time(NULL));
    while (!menuScreen());
    gamePlayer(); 

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
            typingEffect("★ 암살은 실패를 했고 의사가 살려주는데 성공하였습니다. 사망자가 없습니다.", 60, 10);
        }
        else if (killTarget > 0) 
        
        {
            IsAlive[killTarget - 1] = 0;

            printf("\n   [!] 사건 발생: %d번 플레이어가 ", killTarget);
            setColor(4); // 진한 피색
            printf("처참하게 살해된 채");
            setColor(12); // 밝은 빨강
            printf(" 발견되었습니다.\n");

            Sleep(1200);

            int randomIndex = rand() % totalKillMessages;
            dramaticTyping(killMessages[randomIndex], 110, 8); // 어두운 회색으로 아주 느리게
        }

        if (checkVictory()) break;
        pause();

        clear();
        discussionPhase();

        clear();
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n          낮 의 투 표 시 간\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        playerVote();
        if (checkVictory()) 
        
        {
            break;
        }
        pause();
    }

    showGameResult();
    printf("\n게임을 종료합니다. 이용해 주셔서 감사합니다.\n");
    pause();

    return 0;
}