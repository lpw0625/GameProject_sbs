#include <stdio.h>
#include <stdlib.h>
#include <time.h>


enum Role
{
	MAFIA,
	CITTZEN,
	DOCTOR
};



void menuScreen()
{
	int menuChoice;
	printf("==========MAFIA GAME=========\n");
	printf("1. 게임 시작\n");
	printf("2. 게임 종료\n");
	printf("선택 : ");

	scanf("%d", &menuChoice);

	switch (menuChoice)
	{
	case 1:
		printf("잠시후 마피아 게임을 시작합니다.... \n");

		break;

	case 2: 
		printf("게임을 종료 합니다... \n");

			break;


	default:

		printf("잘못된 입력입니다....");

			break;





	}


}

void gamePlayer()
{

	int playerCount;
	printf("참여할 인원의 수를 입력하세요: ");
	scanf("%d", &playerCount);

	int rolePlayers[10];

	rolePlayers[0] = MAFIA;
	rolePlayers[1] = DOCTOR;

	int maifaCount = playerCount / 4;
	if (maifaCount < 1) maifaCount = 1;
	if (maifaCount > 3) maifaCount = 3;


	for (int i = 0; i < playerCount; i++)
	{
		rolePlayers[i] = CITTZEN;
	}

	for (int i = 0; i < maifaCount; i++)
	{
		rolePlayers[i] = MAFIA;
	}

	rolePlayers[maifaCount] = DOCTOR;

	// 직업 랜덤으로 배정하기
	for (int i = playerCount - 1; i > 0; i--)
	{

		int j = rand() % (i + 1);
		int temp = rolePlayers[i];
		rolePlayers[i] = rolePlayers[j];
		rolePlayers[j] = temp;


	}
	printf("\n -------------------- 시민들이 잠든 사이 마피아들은 접선을 하였습니다.......  -------------------- ", &maifaCount);
	printf("\n -------------------- 밤은 평안합니다.... 지금은....... --------------------  ");
}
void mafiaPlayer()
{


}

void doctorPlayer()
{

}

void cittzenPlayer()
{

}


int main()
{


	while (menuScreen() != 1)
	
	gamePlayer();

	return 0;

}