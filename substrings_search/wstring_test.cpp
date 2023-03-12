#include <iostream>
#include <string>
 
int main()
{
 std::wstring wstr = L"aa也池施地土人aaёёё";
 std::cout << "sometext" << std::endl;
 std::wcout << wstr << std::endl;
 std::cout << "sometext" << std::endl;
 std::cout << "sometext " << sizeof(wstr[0]) << " " << sizeof(wstr[4]) << std::endl;
 std::cout << "sizeof coomon char: " << sizeof('q') << std::endl;
 std::cout << "sizeof this: 地 " << sizeof('地') << std::endl;
 
 return 0;
}

//some chinese letters
// 也 池 施 地 土 人 