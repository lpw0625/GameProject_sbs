#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define UP 72
#define LEFT 75
#define RIGHT 77 
#define DOWN 80

void position(int x, int y)
{
	COORD position = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

int main()
{


	char key = 0;

	int x = 0;
	int y = 0;

	//position(x,y);
	//printf("¡Ú");

	while (1)
	{
		
		key = _getch();

		if (key == -32 || key == 0)
		{
			key = _getch();


			//if (key == 72)
			//{
			//	printf("¡è");
			//}

			//else if (key == 80)
			//{
			//	printf("¡é");
			//}

			//else if (key == 77)
			//{
			//	printf("¡æ");
			//}

			//else if (key == 75)
			//{
			//	printf("¡ç");
			//}

			switch (key)
			{
			case UP:  y--;
				break;

			case DOWN:  y++;
				break;

			case RIGHT:  x += 2;;
				break;

			case LEFT:  x -= 2;;
				break;

			default:  printf("exception\n");
				break;
			}

		}

		system("cls");

		position(x,y);

		printf("¡Ú");

	}

	return 0;

}