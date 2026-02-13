#include <iostream>

using namespace std;

class Sprite
{
private:
    int* pixels = nullptr;

public:

    Sprite()
    {
        if (pixels == nullptr)
        {
            pixels = new int(1024);
        }
    }

    Sprite(const Sprite & clone)
    {
        int* c_pixels = clone.pixels;
    }
};

//class Soldier
//{
//public:
//
//    static int count;
//
//    Soldier()
//    {
//        cout << "Created Soldier" << endl;
//    }
//
//
//    ~Soldier()
//    {
//        count++;
//
//        cout << "Destroy Solider" << count << endl;
//    }
//};
//
//int Soldier::count = 0;

int main()
{
#pragma region 생성자
    // 클래스의 인스턴스가 생성되는 시점에 자동으로
    // 호출되는 특수한 멤버 함수입니다.

  /*  Soldier soldier;*/

    // 생성자의 경우 객체가 생성될 때 단 한 번만 호출되며,
    // 생성자는 반환형이 존재하지 않기 때문에 생성자가 호출되기
    // 전에는 객체에 대한 메모리가 할당되지 않습니다.
#pragma endregion

#pragma region 소멸자
// 객체가 소명될 때 자동으로 실행되는 클래스의 
// 특수한 매버 함수 


  /*  Soldier* pointer = new Soldier;

    delete pointer;

    pointer = new Soldier;

    delete pointer;*/

// 소멸자는 갹체가 메모리에서 해체될 때 단 한번만 
// 호출되며, 소멸자에는 매개 변수를 생상하여 사용할 수 없다.


#pragma endregion


#pragma region 얕은 복사
    // 객체를 복사할 때 주소 값을 복사하여 같은 
    // 메모리 공간을 가리키게 하는 복사

    //int* address = new int;
    //int* share = address;

    //*address = 20;

    //cout << "Adrress 변수 값: " << *address << endl;
    //cout << "Share 변수 값: " << * share << endl;

    //cout << "Adrress가 가리키는 값 값: " << *address << endl;
    //cout << "Share기 가리키는 값: " << *share << endl;

    Sprite original;

    Sprite copied(original);

    // 얕은 복사의 경우 같은 객체가 서로 같은 메모리 공간을
    // 참조하고 있기 때문에 하나의 객체로 값을 변경하게 되면
    // 서로 참조된 객체도 함께 영향을 받는다.

#pragma endregion

#pragma region 깊은 복사
    // 객체를 복사할 때, 참조 값이 아닌 객체 자체로 새로
    // 복사하여 서로 다른 메모리를 생성하는 복사
#pragma endregion



    return 0;
}