#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define LEN_MIN  15   // 기차길이
#define LEN_MAX  50
#define STM_MIN  0    // 마동석체력
#define STM_MAX  5
#define PROB_MIN  10  // 확률
#define PROB_MAX  90
#define AGGRO_MIN  0  // 어그로범위
#define AGGRO_MAX  5

// 마동석이동방향
#define MOVE_LEFT  1
#define MOVE_STAY  0

// 좀비의공격대상
#define ATK_NONE  0
#define ATK_CITIZEN  1
#define ATK_DONGSEOK  2

// 마동석행동
#define ACTION_REST  0
#define ACTION_PROVOKE  1
#define ACTION_PULL  


void intro(void)
{
	printf("    ....________  ___......     ......___  ________....     _________________\n");
	printf("  __IooI==   = = =   ~~~~~I     I~~~~~   = = =   ==IooI__   I         I   I\n");
	printf("I_I_I__I______GBW____=====I_I_I_I=====____GBW______I__I_I_I I GBW     I   I  \n");
	printf("`-'O==O~=============~O==O`-'~`-'O==O~=============~O==O`-'~~o==o~~~~~~~~~~~~\n");
	printf("\n마동석에 빙의해서\n");
	Sleep(1000);
	printf("좀비로부터\n");
	Sleep(1000);
	printf("시민을 지켜라!\n");
	Sleep(1000);
	system("cls");
}


void outro(int C, int Z)
{
	if (C == 1)
	{
		printf("SUCCESS!\n");
		printf("citizen(s) escaped to the next train\n");
	}
	if (C + 1 == Z)
	{
		printf("GAME OVER!\n");
		printf("Citizen(s) has(have) been attacked by a zombie");
	}

}

int check(int len, int prob) //잘못된 입력인지 채크
{
	if (LEN_MIN > len || LEN_MAX < len)
	{
		return -1;
	}

	if (PROB_MIN > prob || PROB_MAX < prob)
	{
		return -1;
	}

	return 0;
}

void printPattern(int len, int C, int Z, int M) //기차 그림
{

	for (int i = 0; i < len; i++) {printf("#");}
	printf("\n");

	for (int i = 0; i < len; i++) {
		if (i == 0 || i == len - 1) {printf("#");}
		else if (i == M) {printf("M");}
		else if (i == Z) {printf("Z");}
		else if (i == C) {printf("C");}
		else {printf(" ");}
	}
	printf("\n");

	for (int i = 0; i < len; i++) {printf("#");}
	printf("\n");
}

void printStatus(int prevC, int C, int prevZ, int Z)
{
	if (prevC > C) {
		printf("\ncitizen: %d -> %d\n", prevC, C);
	}
	else {
		printf("\ncitizen: stay %d\n", C);
	}

	if (prevZ > Z) {
		printf("zombie: %d -> %d\n\n", prevZ, Z);
	}
	else {
		printf("zombie: stay %d (cannot move)\n\n", Z);
	}
}

int citizen_move(int C, int p, int random) //시민 이동
{
	if (random >= p)
	{
		if (C > 0)
		{
			C = C - 1;
		}
	}

	return C;
}

int zombie_move(int Z, int p, int random, int turn) //좀비 이동
{
	if (turn % 2 == 1)
	{
		if (random < p)
		{
			if (Z > 0)
			{
				Z = Z - 1;
			}
		}
	}

	return Z;
}

int main(void)
{

}
