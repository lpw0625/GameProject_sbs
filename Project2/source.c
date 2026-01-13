#include <stdio.h>
#include <Windows.h>
#include <stdbool.h> // bool 타입을 위해 추가

#define SIZE 10

const char* dialog[SIZE];
int i = 0;

void Start() {
    dialog[0] = ".......";
    dialog[1] = "사건 현장에 도착을 했습니다";
    dialog[2] = ".......";
    dialog[3] = "의뢰인은 아직 의식은 돌아오지 못한 상태로군요.";
    dialog[4] = "나는 정신을 차리고 자리에서 일어선다...";
    dialog[5] = " 정신이 드십니까?";
    dialog[6] = "누구세요?.";
    dialog[7] = "당신은 여기서 2시간 동안 기절해 있었습니다.";
    dialog[8] = "제가요...?";
    dialog[9] = "그렇습니다.";

    printf(">> [START] 대화 시스템을 초기화했습니다.\n");
    printf(">> [SPACE]를 누르면 대사가 시작됩니다.\n\n");
}

bool Update() {
    if (i < SIZE) {
        // 키가 눌린 순간 한 번만 인식하도록 0x8000과 조합하거나 
        // 0x0001을 사용하되 루프 속도를 조절하는 것이 좋습니다.
        if (GetAsyncKeyState(VK_SPACE) & 0x0001) {
            if (i % 2 == 0) {
                printf("[의뢰인] : %s\n", dialog[i]);
            }
            else {
                printf("[탐정] : %s\n", dialog[i]);
            }
            i++;
        }
        return true;
    }
    return false;
}

void Release() {
    printf("\n--- [RELEASE] 모든 대화가 끝나고 자원을 해제합니다. ---\n");
    printf("--- 게임이 안전하게 종료됩니다. ---\n");
}

int main() {
    Start();

    while (true) {
        if (!Update()) {
            break;
        }
       
    }

    Release();
    return 0;
}