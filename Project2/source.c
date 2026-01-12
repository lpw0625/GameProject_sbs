#include <stdio.h>
#include <Windows.h>

#define SIZE 10

int main()
{
#pragma region 포인터 함수

	const char* dialog[SIZE];

	dialog[0] = ".......";
	dialog[1] = "... 낯선 공기가 흐른다.";
	dialog[2] = "차가운 바닥과 함께 천장에서는 눈을 비추는 빛이 보인다....";
	dialog[3] = "그리고 잠시후, 귓가에서는 누군가들이 대화를 하는 소리가 들린다...";
	dialog[4] = "나는 정신을 차리고 자리에서 일어선다...";
	dialog[5] = "[탐정] : 정신이 드십니까?";
	dialog[6] = "[탐정] : 당신은 몇 시간 동안 여기서 쓰러진 상태였습니다.";
	dialog[7] = "[플레이어] : ...제가요...?";
	dialog[8] = "[탐정] : 그렇습니다.";
	dialog[9] = "[탐정] : 당신은 이번 사건에 아주 중요한 인물입니다.";

	int i = 0; // 현재 몇 번째 대사인지 기억할 변수

	printf(">> [SPACE]를 누르면 대사가 시작됩니다.\n\n");

	while (i < SIZE) // i가 대사 개수(SIZE)보다 작을 동안 계속 반복
	{
		// 0x0001: 스페이스바가 눌린 순간을 감지
		if (GetAsyncKeyState(VK_SPACE) & 0x0001)
		{
			// 현재 번호(i)의 대사를 출력
			printf("%s\n", dialog[i]);

			// 출력했으니 다음 대사를 위해 번호를 1 증가
			i++;

			// 만약 i가 SIZE와 같아지면, 더 이상 출력할 대사가 없으므로 
			// while문 조건(i < SIZE)에 의해 루프를 자동으로 빠져나갑니다.
		}
	}

	printf("\n--- 모든 대화가 끝나고 게임이 종료됩니다. ---\n");

#pragma endregion

	return 0;
}