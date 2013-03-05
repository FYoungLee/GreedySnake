/* ��� ʵ�� �� Ӧ��*/
#include <windows.h> 
#include <ctime> 
#include <iostream> 
#include "snake.h" 
using namespace std; 

//���Գɹ� 
void Csnake::InitInstance() { 
	// snakeMap[������][������] 
	snakeMap.resize(line); 
	// ����world�ı߽�����߿����ƶ��ĵ�ͼ
	for(int i = 0; i < line; i++) { 
		snakeMap[i].resize(row); 
		for(int j = 0; j < row; j++) { 
			if( i == 0 || i == line-1 || j == 0 || j == row-1)
				snakeMap[i][j] = '=';
			else
				snakeMap[i][j] = ' '; 
		} 
	}

	for(int m = 1;m < maxSize+1; m++) { 
		//��ʼ���� 
		snakeMap[line/2][m] = 'X'; 
		//����������ѹ����� 
		MySnake.push(Cmap(m,(line/2))); 
		//snakeBody[������][������] 
	}

	//����ͷβ 
	firstSign = MySnake.back(); 
	secondSign.setPoint(maxSize-1,line/2); 
} 
//���Գɹ� 
int Csnake::GetDirections()const { 
	if(GetKeyState(VK_UP)<0)        //1��ʾ�����ϼ� 
		return 1; 
	if(GetKeyState(VK_DOWN)<0)		//2��ʾ�����¼� 
		return 2; 
	if(GetKeyState(VK_LEFT)<0)		//3��ʾ������� 
		return 3; 
	if(GetKeyState(VK_RIGHT)<0)		//4��ʾ�����Ҽ�
		return 4;  
	return 0; 
} 

bool Csnake::UpdataGame() { 
	//��ʼ���÷�0 
	static int score = 0; 
	//��ȡ�û�������Ϣ 
	int choice; 
	choice = GetDirections(); 
	cout << " Total score: " << score << endl; 
	//�������ʳ���������� 
	int r,l; 
	//��ʼ��ʼ�Ѿ���ʳ������һ��ʳ�� 
	static bool eatFood = true; 
	//�������һ�������ٳ��ֵ�2��ʳ�� 
	if( eatFood ) { 
		do { 
			//���귶Χ�����ڣ�1��1������line-2,row-2���Ե����֮�� 
			srand(time(0));

			r = (rand()%(row-2))+1; //������ 
			l = (rand()%(line-2))+1;//������ 
			//���������������겻����������� 
			//�������²������� 
			if(snakeMap[l][r] != 'X') {	
				snakeMap[l][r] = '*';
			} 
		}while (snakeMap[l][r] == 'X'); 
	}

	switch (choice) { 
		case 1://���� 
		//�����ͷ���߾��ĺ����겻��ͬ��ִ��������� 
		if(firstSign.rSign != secondSign.rSign)
			nextSign.setPoint(firstSign.rSign,firstSign.lSign-1); 
		//����������ԭ�������ϼ����ƶ� 
		else 
			nextSign = firstSign + (firstSign-secondSign); break; 
	
		case 2://���� 
		if(firstSign.rSign != secondSign.rSign)
			nextSign.setPoint(firstSign.rSign,firstSign.lSign+1); 
		else 
			nextSign = firstSign + (firstSign-secondSign); break; 

		case 3://���� 
		if(firstSign.lSign != secondSign.lSign)
			nextSign.setPoint(firstSign.rSign-1,firstSign.lSign); 
		else 
			nextSign = firstSign + (firstSign-secondSign); 
		break; 

		case 4://���� 
		if(firstSign.lSign != secondSign.lSign)
			nextSign.setPoint(firstSign.rSign+1,firstSign.lSign); 
		else 
			nextSign = firstSign + (firstSign-secondSign); 
		break; 

		default: 
		nextSign = firstSign + (firstSign-secondSign); 
	}
	//���û������ʳ��(��û�������������)��ɾ����β��ѹ���µ���ͷ
	if(getSymbol(nextSign)!='*' && !isDead(nextSign)) {    
		//ɾ����β 
		lastSign = MySnake.front(); 
		snakeMap[lastSign.lSign][lastSign.rSign] = ' '; 
		MySnake.pop(); 
		//������ͷ 
		secondSign = firstSign; 
		//ѹ����ͷ 
		MySnake.push(nextSign); 
		firstSign = MySnake.back(); 
		snakeMap[firstSign.lSign][firstSign.rSign] = 'X'; 
		//û�г�ʳ 
		eatFood = false; 
		return true; 
	}

	//-----��ʳ----- 
	else if(getSymbol(nextSign)=='*' && !isDead(nextSign)) { 
		secondSign = firstSign; 
		snakeMap[nextSign.lSign][nextSign.rSign] = 'X'; 
		//ֻѹ����ͷ 
		MySnake.push(nextSign); 
		firstSign = MySnake.back(); 
		eatFood = true; 
		//�ӷ� 
		score += 10; 
		return true; 
	}

	//-----����----- 
	else {
		cout << " Game Over! Your snake is Dead!" << endl;
		cout << " Your total score is " << score << endl; 
		return false;
	} 
} 

void Csnake::ShowGame() { 
	for(int i = 0; i < line; i++) { 
		for(int j = 0;j < row; j++) 
			cout << snakeMap[i][j]; 
		cout << endl; 
	}
	//����һ��ʱ�䣬��λ����
	//Sleep(100); 
	system("cls"); 
} 