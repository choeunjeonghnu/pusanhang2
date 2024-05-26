#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define LEN_MIN  15   // ��������
#define LEN_MAX  50
#define STM_MIN  0    // ������ü��
#define STM_MAX  5
#define PROB_MIN  10  // Ȯ��
#define PROB_MAX  90
#define AGGRO_MIN  0  // ��׷ι���
#define AGGRO_MAX  5

// �������̵�����
#define MOVE_LEFT  1
#define MOVE_STAY  0

// �����ǰ��ݴ��
#define ATK_NONE  0
#define ATK_CITIZEN  1
#define ATK_DONGSEOK  2

// �������ൿ
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
	printf("\n�������� �����ؼ�\n");
	Sleep(1000);
	printf("����κ���\n");
	Sleep(1000);
	printf("�ù��� ���Ѷ�!\n");
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

void printPattern(int len, int C, int Z, int M) //���� �׸�
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
	int prevC_aggro = C_aggro; // C_aggro�� ���� ���� ����

	if (prevC != C) {
		// �ù��� �̵��� ���
		printf("\ncitizen: %d -> %d\n", prevC, C);
		if (C_aggro < AGGRO_MAX) {
			C_aggro++;
		}
	}
	else {
		// �ù��� �̵����� ���� ���
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

int citizen_move(int C, int p, int random) //�ù� �̵�
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

int zombie_move(int Z, int p, int random, int turn) //���� �̵�
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

	// ���� ���� �Է� �ޱ�
	do {
		printf("train length(%d~%d)>> ", LEN_MIN, LEN_MAX);
		scanf_s("%d", &len);
	} while (len < LEN_MIN || len > LEN_MAX);

	// ������ ü�� �Է� �ޱ�
	do {
		printf("madongseok stamina(%d~%d)>> ", STM_MIN, STM_MAX);
		scanf_s("%d", &stm);
	} while (stm < STM_MIN || stm > STM_MAX);

	// Ȯ�� �Է� �ޱ�
	do {
		printf("percentile probability 'p' (%d~%d)>> ", PROB_MIN, PROB_MAX);
		scanf_s("%d", &p);
	} while (p < PROB_MIN || p > PROB_MAX);

	int C = len - 6; //�ù�
	int Z = len - 3; //����
	int M = len - 2; //������
	int C_aggro = 1; //�ù� ��׷�
	int M_aggro = 1; //������ ��׷�

	printPattern(len, C, Z, M); //���� �ʱ� ���� ���

	while (1)
	{

		int prevC = C;
		int prevZ = Z;
		int prevM = M;
		int prevC_aggro = C_aggro;
		int prevM_aggro = M_aggro;

		int random = rand() % 100;

		C = citizen_move(C, p, random); //�ù� �̵�
		Z = zombie_move(Z, p, random, turn); //���� �̵�

		printPattern(len, C, Z, M); //���� ���� ���
		printStatus(prevC, C, prevZ, Z); //�ù�, ���� ���� ���
		//������ �̵�

		if (C == 1) //�ù��� ���� ���� �����ϸ� ���� ����
		{
			break;
		}
		if (C + 1 == Z) //���� �ù� �ٷ� �� ĭ�� ���������� ���� ����
		{
			break;
		}

		turn++;
	}

	outro(C, Z); //���� ���� ��� (����/����)
}


