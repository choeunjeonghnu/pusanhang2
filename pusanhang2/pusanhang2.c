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

int C_aggro = 1;
int M_aggro = 1;
int stm;
int zombie_cannot_move_next_turn = 0; 


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


void outro(end)
{
	if (end == 0)
	{
		printf("YOU WIN!\n");
	}
	else if (end == 1)
	{
		printf("citizen does noting.\n");
		printf("GAME OVER! citizen dead...\n");
	}
	else if (end == 2)
	{
		printf("GAME OVER! madongseok dead...\n");
	}
}

void printPattern(int len, int C, int Z, int M) //���� �׸�
{
	printf("\n");

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

void printStatus(int prevC, int C, int prevZ, int Z, int turn) //�ùΰ� ������ ���� ���
{
	int prevC_aggro = C_aggro; 

	if (prevC != C) {
		// �ù� �̵�
		printf("\ncitizen: %d -> %d ", prevC, C);
		if (C_aggro < AGGRO_MAX) {
			C_aggro++;
		}
	}
	else {
		printf("\ncitizen: %d -> %d ", prevC, C);
		if (C_aggro > AGGRO_MIN) {
			C_aggro--;
		}
	}
	printf("(aggro: %d -> %d)\n", prevC_aggro, C_aggro);

	if (turn % 2 == 1) { //���� �̵�
		if (prevZ != Z) {printf("zombie: %d -> %d\n\n", prevZ, Z);}
		else {printf("zombie: stay %d (cannot move)\n\n", Z);}
	}
	else {printf("zombie: stay %d (cannot move this turn)\n\n", Z);} 
}

void printStatus2(int prevM, int M, int stm) //������ ���� ���
{
	int prevM_aggro = M_aggro;
	//������ �̵�
	if (prevM != M)
	{
		if (M_aggro < AGGRO_MAX)
		{
			M_aggro++;
			printf("\nmadongseok: %d -> %d (aggro : % d -> % d, stamina: %d)\n\n", prevM, M, prevM_aggro, M_aggro, stm);
		}
		else
		{
			printf("\nmadongseok: %d -> %d (aggro : % d -> % d, stamina: %d)\n\n", prevM, M, prevM_aggro, M_aggro, stm);
		}
	}
	else if (prevM == M)
	{
		if (M_aggro > AGGRO_MIN)
		{
			M_aggro--;
			printf("\nmadongseock: stay %d (aggro: %d -> %d, stamina: %d)\n\n", M, prevM_aggro, M_aggro, stm);
		}
		else
		{
			printf("\nmadongseock: stay %d (aggro: %d -> %d, stamina: %d)\n\n", M, prevM_aggro, M_aggro, stm);
		}
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


int zombie_move(int Z, int p, int random, int turn, int C, int M)  //���� �̵�
{
	if (zombie_cannot_move_next_turn) {
		zombie_cannot_move_next_turn = 0; // ���� �Ͽ� �ٽ� �̵� ����
		printf("\nzombie: cannot move this turn due to pull effect\n\n");
		return Z;
	}

	if (turn % 2 == 1) { // ���� �̵� ��
		if (random < p) {
			if (C_aggro > M_aggro) {
				if (Z - 1 != C) { // �ùΰ� �������� ���� ��쿡�� �̵�
					Z = Z - 1;
				}
			}
			else if (M_aggro > C_aggro) {
				if (Z + 1 != M) { // �������� �������� ���� ��쿡�� �̵�
					Z = Z + 1;
				}
			}
			else {
				if (Z - 1 != C) { // �ùΰ� �������� ���� ��쿡�� �̵�
					Z = Z - 1;
				}
			}
		}
	}
	return Z;
}

int madongseok_move(int M, int Z) //������ �̵�
{
	int choice;

	if (M - 1 == Z)
	{
		while (1) {
			printf("madongseock move (0: stay)>> ");
			scanf_s("%d", &choice);
			if (choice != 0)
			{
				printf("You can only enter 0\n");
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		printf("madongseok move(0: stay, 1:left) >> ");
		scanf_s("%d", &choice);

		if (choice == 1)
		{
			M = M - 1;
		}
	}

	return M;
}

int zombie_action(int C, int Z, int M, int prevM_stm, int stm) {
	int end = -1;

	if (Z - 1 == C && Z + 1 == M) {
		if (C_aggro > M_aggro) {
			end = 1; // �ù� �������� ���� ����
		}
		else {
			prevM_stm = stm;
			stm--; // �������� ü�� ����
			printf("Zombie attacked madongseock (aggro: %d vs %d, madongseok stamina: %d -> %d)\n\n", C_aggro, M_aggro, prevM_stm, stm);
			if (stm <= STM_MIN) {
				printf("GAME OVER! madongseok dead...\n");
				exit(2); // ������ �������� ������ ü���� STM_MIN�Ǿ� ���� ����
			}
		}
	}
	else if (Z - 1 == C) {
		end = 1; // �ù� �������� ���� ����
	}
	else if (Z + 1 == M) {
		prevM_stm = stm;
		stm--; // �������� ü�� ����
		printf("Zombie attacked madongseock (aggro: %d vs %d, madongseok stamina: %d -> %d)\n\n", C_aggro, M_aggro, prevM_stm, stm);
		if (stm <= STM_MIN) {
			printf("GAME OVER! madongseok dead...\n");
			exit(2); // ������ �������� ������ ü���� STM_MIN�Ǿ� ���� ����
		}
	}
	else {
		printf("citizen does nothing.\n");
		printf("zombie attacked nobody.\n\n");
	}

	return stm;
}

void madongseok_action(int M, int Z, int p) {
	int choice;
	int prevM_stm = stm;
	int prevM_aggro = M_aggro;

	if (M - 1 != Z) {
		printf("madongseok action(0. rest, 1.provoke)>> ");
		scanf_s("%d", &choice);

		if (choice == ACTION_REST) {
			stm++;
			if (stm > STM_MAX) {
				stm = STM_MAX;
			}

			M_aggro--;
			if (M_aggro < AGGRO_MIN) {
				M_aggro = AGGRO_MIN;
			}

			printf("madongseok rests... \n");
			printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", M, prevM_aggro, M_aggro, prevM_stm, stm);
		}
		else if (choice == ACTION_PROVOKE) {
			M_aggro = AGGRO_MAX;
			printf("madongseock provoked zombie...\n");
			printf("madongseock: %d (aggro: %d -> %d, stamina: %d)\n", M, prevM_aggro, M_aggro, stm);
		}
	}
	else {
		printf("madongseok action(0. rest, 1.provoke, 2.pull)>> ");
		scanf_s("%d", &choice);

		if (choice == ACTION_REST) {
			stm++;
			if (stm > STM_MAX) {
				stm = STM_MAX;
			}

			M_aggro--;
			if (M_aggro < AGGRO_MIN) {
				M_aggro = AGGRO_MIN;
			}

			printf("\nmadongseok rests... \n");
			printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", M, prevM_aggro, M_aggro, prevM_stm, stm);
		}
		else if (choice == ACTION_PROVOKE) {
			M_aggro = AGGRO_MAX;
			printf("\nmadongseock provoked zombie...\n");
			printf("madongseock: %d (aggro: %d -> %d, stamina: %d)\n", M, prevM_aggro, M_aggro, stm);
		}
		else if (choice == ACTION_PULL) {
			M_aggro += 2;
			if (M_aggro > AGGRO_MAX) {
				M_aggro = AGGRO_MAX;
			}
			stm--;
			if (stm < STM_MIN) {
				stm = STM_MIN;
			}

			int success_chance = rand() % 100;
			if (success_chance >= p) {
				zombie_cannot_move_next_turn = 1;
				printf("\nmadongseok pulled zombie... Next turn, it can't move\n");
				printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", M, prevM_aggro, M_aggro, prevM_stm, stm);
			}
			else {
				printf("\nmadongseok failed to pull zombie\n");
				printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", M, prevM_aggro, M_aggro, prevM_stm, stm);
			}
		}
	}
}

int main(void) 
{
	srand((unsigned int)time(NULL));

	int len = 0;
	int p = 0;
	int turn = 1;
	int end;


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


	printPattern(len, C, Z, M); //���� �ʱ� ���� ���

	while (1)
	{

		int prevC = C;
		int prevZ = Z;
		int prevM = M;
		int prevC_aggro = C_aggro;
		int prevM_aggro = M_aggro;
		int prevM_stm = stm;

		int random = rand() % 100;

		C = citizen_move(C, p, random); //�ù� �̵�
		Z = zombie_move(Z, p, random, turn, C, M); //���� �̵�
		

		printPattern(len, C, Z, M); //���� ���� ���
		printStatus(prevC, C, prevZ, Z, turn); //�ù�, ���� ���� ���

		M = madongseok_move(M, Z); //������ �̵�

		printPattern(len, C, Z, M); //���� ���� ���
		printStatus2(prevM, M, stm); //������ ���� ���

		stm = zombie_action(C, Z, M, prevM_stm, stm); //���� �ൿ
		madongseok_action(M, Z, p); //������ �ൿ


		//���� ���� ����
		if (C == 1) 
		{
			end = 0;
			break;
		}
		if (Z - 1 == C && Z + 1 == M) 
		{
			if (C_aggro > M_aggro) 
			{
				end = 1;
				break;
			}
			else 
			{
				if (stm <= STM_MIN)
				{
					end = 2; // ������ �������� ������ ü���� STM_MIN�Ǿ� ���� ����
					break;
				}
			}
		}
		else if (Z - 1 == C) 
		{
			end = 1; // �ù� �������� ���� ����
			break;
		}
		else if (Z + 1 == M)
		{
			if (stm <= STM_MIN)
			{
				end = 2; // ������ �������� ������ ü���� STM_MIN�Ǿ� ���� ����
				break;
			}

		}
		

		turn++;
	}

	outro(end); //���� ���� ��� 
}


