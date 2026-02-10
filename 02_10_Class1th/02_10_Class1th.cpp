// 02_10_Class1th.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
int packet = 1;

void swap(int& argument, int & number)
{

	int temp = argument;
	argument = number;
	number = temp;

}
int main()
{
#pragma region 스트림


	//std::cout << "반갑습네다" << std::endl;

	//int count = 5;

	//std::cin >> count;

	//for (int i = 1; i <= count; i++)
	//{
	//	std::cout << "PlayStation" << i << std::endl;
	//}

	//return 0;

	// 시간의 흐름에 따라 연속적으로 발생하는 데이터의 흐름

	// 스트림은 운영 체제에 의해 생성되며, 스트림 자체에 버퍼라는
	// 임시 메모리 공간이 존재.
#pragma endregion

#pragma region  범위 지정 연산자
	// 여러 범위에서 사용되는 식별자를 구분하는데
	// 사용하는 연산자.

	int packet = 100;

	std::cout << "packet 지역 변수의 값 : " << packet << std::endl;
	std::cout << "packet 전역 변수의 값 : " << ::packet << std::endl;

	// 범위 지정 연산자는전역 변수와 같은 이름의 지역 변수가 
	// 선언 되었을 때 가장 가까운 범위에 선언된 변수의 이름을
	// 사용하는 범위 규칙이 존재하기 때문에 전역 변수가 호출되지 않는다.

#pragma endregion

#pragma region 참조자

#pragma endregion

#pragma region 동적 할당 

	int* pointer = new int;

	*pointer = 8;

	std::cout << *pointer << std::endl;

	delete pointer;
#pragma endregion



}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
