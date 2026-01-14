#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//void shuffle(int array[], int size)
//{
//    for (int i = 0; i < size; i++)
//    {
//        int seed = rand() % size;
//
//        int temporary = array[seed];
//
//        array[seed] = array[i];
//
//        array[i] = temporary;
//    }
//}



int main()
{

   /* int life = 5;
    int CpPower = 0;
    int input = 0;

    srand(time(NULL));

 

    int answer = (rand() % 50) + 1;

    while(life > 0)
    {
        printf("\nLife:");

        for (int i = 0; i < life; i++)
        {
            printf("♥");
        }
        
        printf("\n 숫자를 입력하세요: ");
        scanf_s("%d", &input);

   
        if (input == answer)

        {
            printf("Victory!");
            CpPower++;
            break;
        }

        else if (input > answer)

        {
            printf("[Down!] 입력한 숫자가 정답보다 큽니다.\n");
            life--;
        }

        else if (input < answer)

        {
            printf("[Up!] 입력한 숫자가 정답보다 작습니다.\n");
            life--;
        }

        if (life == 0)
        {
            printf("\n Game over : 정답은 %d였습니다. \n", answer);
       }
    }*/
     
    return 0;
}



#pragma region 의사 난수
    // 0 ~ 32767 사이의 난수 값을 반환하는 함수입니다.

    // UTC 기준으로 1970년 1월 1일 0시 0분 0초부터 경과된
    // 시간을 초(sec)로 반환하는 함수입니다.

    // srand : rand()가 사용할 초기값(seed)을 설정하는 함수

    // srand(time(NULL));
    // 
    // int random = rand() % 10 + 1;
    // 
    // printf("random : %d\n", random);

#pragma endregion

#pragma region 셔플 함수

 /*   srand(time(NULL));

    int list[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    int size = sizeof(list) / sizeof(list[0]);

    shuffle(list, size);

    for (int i = 0; i < size; i++)
    {
        printf("list[%d]의 값 : %d\n", i, list[i]);
    }*/

#pragma endregion




