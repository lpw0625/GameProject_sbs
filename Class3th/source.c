#include <stdio.h>
#include <windows.h>

// 1. 열거형 정의

// 열거형은 값을 따로 설정을 할 수 있으며.

// 따로 설정된 다음의 값은 그 전의 값에서 

// 하나 증가된 값으로 설정.

// 관련된 상수의 값을  이름으로 정의한 유한한 집합의 자료형.
enum State
{
	IDLE,
	ATTACK,
	DIE
};

enum Color
{
	BLACK, DARKBLUE, DARKGREEN, DARKSKYBLUE,
	DARKRED, DARKVIOLET, GRAY, DARKGRAY,
	SKYBLUE, RED, GREEN, VIOLET, YELLOW, WHITE
};

// 2. 상태 선택 함수 (main 밖으로 완전히 분리)
void StateSelect(enum State state)
{
	switch (state)
	{
	case IDLE:
		printf("플레이어가 대기합니다....\n");
		break;
	case ATTACK:
		printf("플레이어가 공격합니다.\n");
		break;
	case DIE:
		printf("플레이어가 사망하였습니다...\n");
		break;
	default:
		printf("잘못된 입력입니다...\n");
		break;
	}
}

// 3. 메인 함수
int main()
{
	// 색상 시스템 테스트
	printf("--- [색상 시스템 확인] ---\n");
	for (int i = 0; i < 16; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);

		// 3의 배수마다 일시 정지 (작성하신 의도 반영)
		if (i != 0 && i % 3 == 0)
		{
			// system("pause"); // 필요 시 주석 해제
		}

		printf("color System : %d\n", i);
	}

	// 색상 초기화 (흰색)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("--------------------------\n");

	// 상태 입력 테스트
	int KeyInput;
	printf("\n플레이어 상태 선택 (0:대기, 1:공격, 2:사망): ");
	scanf_s("%d", &KeyInput);

	// 입력받은 값으로 함수