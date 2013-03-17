/* ��� ʵ�� �� Ӧ��*/
#include <windows.h> 
#include <ctime> 
#include <iostream> 
#include "snake.h" 
using namespace std; 

int rr;
int ll;
bool isDead;
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

		//������Զ��ߵĳ�ʼ�� 2013-3-8 9:52 xl
		snakeMap[line/3][m] = 'c'; 
		autoSnake.push(Cmap(m,(line/3)));
	}

	//����ͷβ
	firstSign = MySnake.back(); 
	secondSign.setPoint(maxSize-1,line/2); 

	//������Զ��ߵĳ�ʼ�� 2013-3-8 9:52 xl
	firstSign2 = autoSnake.back();
	secondSign2.setPoint(maxSize-1,line/3);
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
// ��������� 2013-3-11 9��15 xl
bool Csnake::autoDecision(int r, int l) {
	bool eatFood = true;
	bool turn1 = false;
	bool turn2 = false;
	if( firstSign2.rSign > r) {
		if( (firstSign2.rSign > secondSign2.rSign) && (secondSign2.rSign > r) ) {
			nextSign2.setPoint(firstSign2.rSign, firstSign2.lSign+1);
			if( getSymbol(nextSign2) == '=' )
				nextSign2.setPoint(firstSign2.rSign,firstSign2.lSign-1);
			turn1 = true;
		}
		if( !turn1 ) {
			if(firstSign2.lSign != secondSign2.lSign)
				nextSign2.setPoint(firstSign2.rSign-1,firstSign2.lSign);
			else
				nextSign2 = firstSign2 + (firstSign2-secondSign2); 
		}
	}
	else if( firstSign2.rSign < r ) {
		if( (firstSign2.rSign < secondSign2.rSign) && (secondSign2.rSign < r) ) {
			nextSign2.setPoint(firstSign2.rSign, firstSign2.lSign+1);
			if( getSymbol(nextSign2) == '=' )
				nextSign2.setPoint(firstSign2.rSign,firstSign2.lSign-1);
			turn2 = true;
		}
		if( !turn2 ) {
			if(firstSign2.lSign != secondSign2.lSign)
				nextSign2.setPoint(firstSign2.rSign+1,firstSign2.lSign); 
			else
				nextSign2 = firstSign2 + (firstSign2-secondSign2); 
		}
	}
	else {
		if( firstSign2.lSign > l ) {
			if(firstSign2.rSign != secondSign2.rSign)
				nextSign2.setPoint(firstSign2.rSign,firstSign2.lSign-1);
			else
				nextSign2 = firstSign2 + (firstSign2-secondSign2); 
		}
		else if( firstSign2.lSign < l ){
			if(firstSign2.rSign != secondSign2.rSign)
				nextSign2.setPoint(firstSign2.rSign,firstSign2.lSign+1);
			else
				nextSign2 = firstSign2 + (firstSign2-secondSign2); 
		}
		else
			nextSign2 = firstSign2 + (firstSign2-secondSign2); 
	}

	//���û������ʳ��(��û�������������)��ɾ����β��ѹ���µ���ͷ
	if(getSymbol(nextSign2)!='*' && !isDead(nextSign2)) {    
		//ɾ����β 
		lastSign2 = autoSnake.front(); 
		snakeMap[lastSign2.lSign][lastSign2.rSign] = ' '; 
		autoSnake.pop(); 
		//������ͷ 
		secondSign2 = firstSign2; 
		//ѹ����ͷ 
		autoSnake.push(nextSign2); 
		firstSign2 = autoSnake.back(); 
		snakeMap[firstSign2.lSign][firstSign2.rSign] = 'c'; 
		//û�г�ʳ 
		eatFood = false; 
		isDead = true;
	}

	//-----��ʳ----- 
	else if(getSymbol(nextSign2)=='*' && !isDead(nextSign2)) { 
		secondSign2 = firstSign2; 
		snakeMap[nextSign2.lSign][nextSign2.rSign] = 'c'; 
		//ֻѹ����ͷ 
		autoSnake.push(nextSign2); 
		firstSign2 = autoSnake.back(); 
		eatFood = true; 
		isDead = true;
		//�ӷ� 
		//score += 10; 
	}
	else
		isDead = false;
	return eatFood;
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
	static bool eatFood2 = true;
	//�������һ�������ٳ��ֵ�2��ʳ�� 
	if( eatFood || eatFood2 ) { 
		do { 
			//���귶Χ�����ڣ�1��1������line-2,row-2���Ե����֮�� 
			srand(time(0));

			rr = r = (rand()%(row-2))+1; //������ 
			ll = l = (rand()%(line-2))+1;//������ 
			//���������������겻����������� 
			//�������²������� 
			// ��������� 2013-3-11 9��15 xl
			if(snakeMap[l][r] != 'X'|| snakeMap[l][r] != 'c') {	
				snakeMap[l][r] = '*';
			} 
		}while (snakeMap[l][r] == 'X' || snakeMap[l][r] == 'c'); 
	}
	// ��������� 2013-3-11 9��15 xl
	eatFood2 = autoDecision(rr,ll);
	if( !isDead )
		return false;
	switch (choice) { 
		case 1://���� 
		//�����ͷ���߾��ĺ����겻��ͬ��ִ��������� 
		if(firstSign.rSign != secondSign.rSign)
			nextSign.setPoint(firstSign.rSign,firstSign.lSign-1); 
		//����������ԭ�������ϼ����ƶ� 
		else 
			nextSign = firstSign + (firstSign-secondSign); 
		break; 
	
		case 2://���� 
		if(firstSign.rSign != secondSign.rSign)
			nextSign.setPoint(firstSign.rSign,firstSign.lSign+1); 
		else 
			nextSign = firstSign + (firstSign-secondSign); 
		break; 

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