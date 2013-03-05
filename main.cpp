/*主函数部分 */
#include <iostream> 
#include "snake.h" 
#include <windows.h> 
using namespace std; 

int main() 
{ 
	Csnake s(20); 
	s.InitInstance(); 
//s.ShowGame(); 
	int noDead; 
	do { 
		s.ShowGame(); 
		noDead=s.UpdataGame(); 
	}while (noDead);

	system("pause"); 
	return 0; 
}