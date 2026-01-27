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
int saveTarget;

int playerVotes[10];


void clearBuffer()
{
	while (getchar() != '\n');
}

int menuScreen()
{

	int menuChoice;
	printf("==========MAFIA GAME=========\n");
	printf("1. 게임 시작\n");
	printf("2. 게임 종료\n");
	printf("선택 : ");

	if (scanf_s("%d", &menuChoice) != 1)

	{
		clearBuffer();
		return 0;
	}
	clearBuffer();

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
	clearBuffer();

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
}

void playerVote()
{
	int voteChoice;

	for (int i = 0; i < totalPlayers; i++)

		playerVotes[i] = 0;

	printf("\n[낮이 되었습니다. 투표를 시작합니다.]\n");
	printf("마피아로 의심되는 사람에게 투표하세요.\n");

	for (int i = 0; i < totalPlayers; i++)
	{
		if (IsAlive[i] == 1)
		{
			while (1)
			{
				printf("%d번 플레이어의 투표(누구를 지목하시겠습니까?):", i + 1);
				scanf_s("%d", &voteChoice);
				clearBuffer();

				if (voteChoice > 0 && voteChoice <= totalPlayers && IsAlive[voteChoice - 1] == 1)
				{
					playerVotes[voteChoice - 1]++; 
					break;
				}
				printf("잘못된 입력입니다. 살아있는 플레이어의 번호를 선택하세요\n");
			}
		}
	}

	int maxVotes = 0;
	int targetIdx = -1;
	int tie = 0;


	for (int i = 0; i < totalPlayers; i++)
	{
		if (playerVotes[i] > maxVotes)
		{
			maxVotes = playerVotes[i];
			targetIdx = i;
			tie = 0;
		}
		else if (playerVotes[i] == maxVotes && maxVotes > 0)
		{
			tie = 1;
		}
	}




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

	while (1)
	{

		printf("\n 제거할 플레이어의 번호를 입력하세요:");
		if (scanf_s("%d", &killTarget) != 1)
		{
			clearBuffer();
			printf("숫자만 입력 가능합니다. \n");
			continue;
		}
		clearBuffer();

		if (killTarget > 0 && killTarget <= totalPlayers && IsAlive[killTarget - 1] == 1)
		{
			break;
		}
		printf("잘못된 입력입니다. 살아있는 플레이어 번호를 입력하세요.\n");
	}
	IsAlive[killTarget - 1] = 0; 
	printf("\n 마피아가 %번 플레이어를 공격했습니다!\n", killTarget);
}

	
	

void doctorPlayer()
{
	printf("\n[의사는 갑작스러운 소리에 놀라 일어납니다.]\n");
	printf("치료를 할 플레이어를 지목하세요.");
	printf("\n의사는 정체를 모른체 누군가를 치료를 하고 있습니다.\n");

	printf("현재 생존자: ");
		for (int i = 0; i < totalPlayers; i++)
		{
			if (IsAlive[i] == 1 || i == (killTarget - 1))
			{

				printf("[%d번]", i + 1);
			}

		}

		printf("\n살릴 플레이어 번호를 입력하세요: ");
		scanf_s("%d", &saveTarget);
		clearBuffer();

		printf("%d번 플레이어를 살리기로 결정했습니다.\n", saveTarget);

}

int main()
{


	while (menuScreen() != 1);
	
	gamePlayer();
	mafiaPlayer();
	doctorPlayer();


	printf("\n============= 밤이 지나고 아침이 밝았습니다. 시민들은 광장에 다시 모였습니다. =============\n");
	if (killTarget == saveTarget) 
	
	{
		IsAlive[killTarget - 1] = 1;
		printf("의사의 활약으로 밤새 아무도 죽지 않았습니다!\n");
	}
	else 
	
	{
		printf("안타깝게도 오늘 밤 %d번 플레이어가 희생되었습니다. \n", killTarget);

	}

	playerVote();

	printf("========================================================\n");


	return 0;

}