#include<iostream>
#include<fstream>
using namespace std;

int main()
{
	bool isLooping = true;
	// 파일 생성
	ofstream fout("C:\\Users\\방찬웅\\Desktop\\Project\\OOP\\Tetris_midterm\\CustomMap.txt");
	// 맵 생성
	char map[200];
	// 맵 초기화
	for (int i = 0; i < 200; i++)
	{
		map[i] = '0';
	}

	// 예외 처리
	if (!fout)
	{
		cout << "Can not open file!\n";
	}

	// map 쓰기
	fout << map << endl;

	fout.close();
}