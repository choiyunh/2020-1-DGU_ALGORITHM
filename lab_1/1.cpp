#include <iostream>

class  InputNum
{
public: // 외부 접근 가능
	InputNum() // InputNum 클래스의 생성자
	{		   
		std::cout << "Enter number "; // 값을 입력받아 멤버변수 _num에 저장
		std::cin >> _num;
	}

	int GetValue() const { return _num; } // 멤버변수를 반환하는 메소드(getter)

	void AddInput() // 새 객체를 생성하여 새 객체의 멤버변수값을 현재 객체의 멤버변수에 더해주는 메소드
	{
		InputNum aNum;  // get a number from user
		_num = _num + aNum.GetValue();
	}

private: // 외부 접근 불가능
	int _num;
};
int main()
{
	InputNum num;
	std::cout << "The value is " << num.GetValue() << "\n";
	num.AddInput();
	std::cout << "Now the value is " << num.GetValue() << "\n";
}
