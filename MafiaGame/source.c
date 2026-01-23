#include <stdio.h>
#include <stdlib.h>
#include <time.h>


enum Role
{
	MAFIA,
	CITTZEN,
	DOCTOR
};


int roleGamePlayers[10];
int IsAlive[10];
int totalPlayers;
int killTarget;


int menuScreen()
{

	int menuChoice;
	printf("==========MAFIA GAME=========\n");
	printf("1. 게임 시작\n");
	printf("2. 게임 종료\n");
	printf("선택 : ");

	scanf_s("%d", &menuChoice);

	switch (menuChoice)
	{
	case 1:
		printf("잠시후 마피아 게임을 시작합니다.... \n");

		return 1;

	case 2: 
		printf("게임을 종료 합니다... \n");

			return 2;


	default:

		printf("잘못된 입력입니다....");

		return 0;





	}


}

void gamePlayer()
{


	printf("참여할 인원의 수를 입력하세요: ");
	scanf_s("%d", &totalPlayers);

	for (int i = 0; i < totalPlayers; i++)
	{
		roleGamePlayers[i] = CITTZEN;
		IsAlive[i] = 1;
	}
	

	int maifaCount = totalPlayers / 4;
	if (maifaCount < 1) maifaCount = 1;




	for (int i = 0; i < maifaCount; i++)
	{
		roleGamePlayers[i] = MAFIA;
	}

	roleGamePlayers[maifaCount] = DOCTOR;

	srand((int)time(NULL));

	// 직업 랜덤으로 배정하기
	for (int i = totalPlayers - 1; i > 0; i--)
	{

		int j = rand() % (i + 1);
		int temp = roleGamePlayers[i];
		roleGamePlayers[i] = roleGamePlayers[j];
		roleGamePlayers[j] = temp;


	}
	printf("\n -------------------- 시민들이 잠든 사이 마피아들은 접선을 하였습니다.......  -------------------- ", &maifaCount);
	printf("\n -------------------- 밤은 평안합니다.... 지금은....... --------------------  ");

	printf("========== 직업 배정 결과 (테스트) ==========\n");
	for (int i = 0; i < totalPlayers; i++)
	{
		printf("[%d번 플레이어]: ", i + 1);
		if (roleGamePlayers[i] == MAFIA)
			printf("마피아\n");
		else if (roleGamePlayers[i] == DOCTOR)
			printf("의사\n");
		else
			printf("시민\n");
	}
	printf("==========================================");
		
}
void mafiaPlayer()
{

	printf("\n[고요한 밤 하늘 아래에... 달이 떴습니다.]");
	printf("\n 고요한 밤 하늘 속에 마피아들은 서로를 확인을 하였고 시민을 죽이기로 결심합니다....\n");

	printf("현재 생존자: ");
	for (int i = 0; i < totalPlayers; i++)
	{
		if (IsAlive[i] == 1)
		{
			printf("[%d번 플레이어]", i + 1);
		}
	}

	printf("\n 제거할 플레이어의 번호를 입력하세요:");
	scanf_s("%d", &killTarget);

	IsAlive[killTarget - 1] = 0;
	printf("\n마피아가 %d번 플레이어를 공격했습니다!\n", killTarget);
}

void doctorPlayer()
{
	printf("\n[의사는 갑작스러운 소리에 놀라 일어납니다.]\n");
	printf("치료를 할 플레이어를 지목하세요.");
	printf("\n의사는 정체를 모른체 누군가를 치료를 하고 있습니다.\n");

}

void cittzenPlayer()
{

}



int main()
{


	while (menuScreen() != 1);
	
	gamePlayer();
	mafiaPlayer();

	printf("\n============= 밤이 지나고 아침이 밝았습니다. 시민들은 다시 광장에 모였습니다. ============= ");

	return 0;

}