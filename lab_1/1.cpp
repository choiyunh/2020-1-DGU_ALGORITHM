#include <iostream>

class  InputNum
{
public: // �ܺ� ���� ����
	InputNum() // InputNum Ŭ������ ������
	{		   
		std::cout << "Enter number "; // ���� �Է¹޾� ������� _num�� ����
		std::cin >> _num;
	}

	int GetValue() const { return _num; } // ��������� ��ȯ�ϴ� �޼ҵ�(getter)

	void AddInput() // �� ��ü�� �����Ͽ� �� ��ü�� ����������� ���� ��ü�� ��������� �����ִ� �޼ҵ�
	{
		InputNum aNum;  // get a number from user
		_num = _num + aNum.GetValue();
	}

private: // �ܺ� ���� �Ұ���
	int _num;
};
int main()
{
	InputNum num;
	std::cout << "The value is " << num.GetValue() << "\n";
	num.AddInput();
	std::cout << "Now the value is " << num.GetValue() << "\n";
}
