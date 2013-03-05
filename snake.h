/*     ͷ�ļ�     */
#include <vector> 
#include <queue> 
using namespace std; 
#ifndef SNAKE_H 
#define SNAKE_H 

class Cmap 
{
		friend class Csnake; 
		int rSign; //������ 
		int lSign; //������ 
	public: 
	    Cmap(int r,int l){
			setPoint(r,l);
		} 
		Cmap(){} 
		void setPoint(int r,int l){
			rSign = r;
			lSign = l;
		} 
		Cmap operator-(const Cmap &m)const { 
			return Cmap(rSign - m.rSign,lSign - m.lSign); 
		} 
		Cmap operator+(const Cmap &m)const { 
			return Cmap(rSign + m.rSign,lSign + m.lSign); 
		} 
}; 

const int maxSize = 5; //��ʼ������ 

class Csnake 
{ 
		Cmap firstSign;     //��ͷ���� 
		Cmap secondSign;    //�߾����� 
		Cmap lastSign;      //��β���� 
		Cmap nextSign;      //Ԥ����ͷ 
		int row;            //���� 
		int line;           //���� 
		int count;          //������ 

		vector<vector<char> > snakeMap;     //������Ϸ���� 
		queue<Cmap> MySnake;                //�ҵ���
		queue<Cmap> autoSnake;				//���Կ��Ƶ��Զ���
	public: 
		//��ȡָ��������ϵ��ַ�
		char getSymbol(const Cmap& c)const{              
			return snakeMap[c.lSign][c.rSign]; 
		} 
		//��ʼ����Ϸ�����С
		Csnake(int n) {                             
			if(n < 20)
				line = 20+2; 
			else if(n > 30)
				line = 30+2; 
			else 
				line = n+2; 
			row = line*3+2; 
		} 
		// �ж��Ƿ񵽴�߽磬����������ж�ʧ��
		bool isDead(const Cmap& cmp) {
			return ( getSymbol(cmp)=='X' || cmp.rSign == row-1 || cmp.rSign== 0 || cmp.lSign == line-1 || cmp.lSign == 0 ); 
		} 
		int GetDirections()const;   //�Ӽ��̻�ȡ��������ֱ�Ϊ���ϡ����¡����󡱡��ҡ���
		void InitInstance();        //��ʼ����Ϸ���� 
		bool UpdataGame();          //������Ϸ���� 
		void ShowGame();            //��ʾ��Ϸ���� 
		void autoDecision();		//�������Զ����Ʒ���
}; 
#endif // SNAKE_H 