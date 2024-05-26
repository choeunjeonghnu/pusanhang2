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
#define ACTION_PULL  2

C_aggro = 1;

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
	int prevC_aggro = C_aggro; // C_aggro의 이전 값을 저장

	if (prevC != C) {
		// 시민이 이동한 경우
		printf("\ncitizen: %d -> %d\n", prevC, C);
		if (C_aggro < AGGRO_MAX) {
			C_aggro++;
		}
	}
	else {
		// 시민이 이동하지 않은 경우
		printf("\ncitizen: %d -> %d\n", prevC, C);
		if (C_aggro > AGGRO_MIN) {
			C_aggro--;
		}
	}
	printf("(aggro: %d -> %d)\n", prevC_aggro, C_aggro);

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
	srand((unsigned int)time(NULL));

	int len = 0;
	int stm = 0; 
	int p = 0;
	int turn = 1;

	intro();

	// 기차 길이 입력 받기
	do {
		printf("train length(%d~%d)>> ", LEN_MIN, LEN_MAX);
		scanf_s("%d", &len);
	} while (len < LEN_MIN || len > LEN_MAX);

	// 마동석 체력 입력 받기
	do {
		printf("madongseok stamina(%d~%d)>> ", STM_MIN, STM_MAX);
		scanf_s("%d", &stm);
	} while (stm < STM_MIN || stm > STM_MAX);

	// 확률 입력 받기
	do {
		printf("percentile probability 'p' (%d~%d)>> ", PROB_MIN, PROB_MAX);
		scanf_s("%d", &p);
	} while (p < PROB_MIN || p > PROB_MAX);

	int C = len - 6; //시민
	int Z = len - 3; //좀비
	int M = len - 2; //마동석
	int C_aggro = 1; //시민 어그로
	int M_aggro = 1; //마동석 어그로

	printPattern(len, C, Z, M); //열차 초기 상태 출력

	while (1)
	{

		int prevC = C;
		int prevZ = Z;
		int prevM = M;
		int prevC_aggro = C_aggro;
		int prevM_aggro = M_aggro;

		int random = rand() % 100;

		C = citizen_move(C, p, random); //시민 이동
		Z = zombie_move(Z, p, random, turn); //좀비 이동

		printPattern(len, C, Z, M); //열차 상태 출력
		printStatus(prevC, C, prevZ, Z); //시민, 좀비 상태 출력
		//마동석 이동

		if (C == 1) //시민이 왼쪽 끝에 도달하면 구출 성공
		{
			break;
		}
		if (C + 1 == Z) //좀비가 시민 바로 옆 칸에 도착했으면 구출 실패
		{
			break;
		}

		turn++;
	}

	outro(C, Z); //종료 상태 출력 (성공/실패)
}


