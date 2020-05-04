#include "stdafx.h"
#include "time.h"
#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <limits.h>
#define N 8
#define M 8

using namespace std;
void first_task();
void second_task();

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	int i;
	char str;
	do
	{
		do
		{
			cout << "\nВведите номер программы программы:";
			cin >> i;
			if (i == 1) first_task();
			if (i == 2) second_task();
		} while (i < 0 || i > 2);
		cout << "\nВы хотите повторить выполнение программы? (Y/N)";
		cin >> str;
	} while (str == 'Y');
	system("pause");
	return 0;
}

void first_task()
{
	int k, max, min, mas[N], *ukz1, *ukz2,*mi,*ma;
	cout << "Расстановка массива по убыванию\n\n";
	for (ukz1 = mas; ukz1 <&mas[N - 1]; ukz1++)
	{
		*ukz1 = rand() % 100;
	}
	for (ukz1 = mas; ukz1 <&mas[N - 1]; ukz1++)
	{
		cout << *ukz1 << "\t";
	}
	/////////////////////////////////////////////////////////////////////////
	cout << "\n";
	max = mas[0];
	min = mas[0];
	for (ukz1 = mas; ukz1 <&mas[N - 1]; ukz1++)
	{
		if (max < *ukz1)
		{
			ma = ukz1;
			max = *ukz1;
		}
		if (min > *ukz1)
		{
			mi = ukz1;
			min = *ukz1;
		}
	}
	cout << "\nМаксимальный элемент:\t" << *ma;
	cout << "\nМинимальный элемент:\t" << *mi;
	/////////////////////////////////////////////////////////////////////////////
	cout << "\n\n";
	for (ukz1 = mi; ukz1 < ma; ukz1++)
	{
		for (ukz2 = ukz1 + 1; ukz2 <= ma; ukz2++)
		{
			if (*ukz2 > *ukz1)
			{
				k = *ukz1;
				*ukz1 = *ukz2;
				*ukz2 = k;
			}
		}
	}
	for (ukz1 = mi; ukz1 > ma; ukz1--)
	{
		for (ukz2 = ukz1- 1 ; ukz2 >= ma; ukz2--)
		{
			if (ukz2 > ukz1)
			{
				k = *ukz1;
				*ukz1 = *ukz2;
				*ukz2 = k;
			}
		}
	}
	cout << "\n";
	for (ukz1 = mas; ukz1 <&mas[N - 1]; ukz1++)
	{
		cout << *ukz1 << "\t";
	}
	cout << "\n";
	//////////////////////////////////////////////////////////
	cout << "\nКонец работы программы\n\n";
}

void second_task()
{
	int sum = 0, mas[N][M], max[N];
	/////////////////////Заполнение массива/////////////////////////
	cout << "Заполнение массива\n\n";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			mas[i][j] = rand() % 100 - 50;
			cout << mas[i][j] << "\t";
		}
		cout << "\n";
	}
	//////////Подсчет количества положительных элементов////////////////
	for (int i = 0; i < N; i++)
	{
		for (int j = M - 1; i + j >= M - 1; j--)
		{
			if (mas[i][j] >= 0)
				sum++;
		}
	}
	cout << "\n";
	cout << "\nКоличество четных элементов:\t" << sum;
	///////////Максимальное значение четных строк//////////////////
	cout << "\n";
	cout << "Массив из максимальных значений четных строк:\n\n";
	for (int i = 0; i < N; i++)
	{
		if (i % 2 == 0)
		{
			for (int j = 0; j < M; j++)
			{
				if (max[i] < mas[i][j])
					max[i] = mas[i][j];
			}
			cout << max[i] << "\t";
		}
	}
	cout << "\n";
	/////////////////////////////////////////////////////////////
	cout << "\nКонец работы программы\n\n";
}

