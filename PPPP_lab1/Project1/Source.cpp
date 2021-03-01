#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void matrixOutput(int** matrix, int n, int m);
int** matrixInitZero(int matrixSize);
int** matrixCreate(int matrixSize);
void matrix�hoiceInit(int** matrix, int n, int m, int inputMethod);
int** submatrixInit(int** mainMatrix, int reducedSize, int shiftI, int shiftJ);


void main()
{
	srand(time(NULL));
	int n1, m1, n2, m2, inputMethod, reducedSize = 2;
	system("chcp 1251");
	cout << "��� ������������ ���������" << endl <<
		"�������� ������������ ������ ������� ���������\n\n";

	////////////////////���� �������� ������� �������������////////////////////////

	do
	{
		cout << "������� ������� ������ �������\n";
		cin >> n1 >> m1;
	} while (n1 <= 0 || m1 <= 0);
	do
	{
		cout << "������� ������� ������ �������\n";
		cin >> n2 >> m2;
	} while (n2 <= 0 || m2 <= 0);

	int** matrix1 = new int* [n1];
	for (int i = 0; i < n1; i++)
		matrix1[i] = new int[m1];

	int** matrix2 = new int* [n2];
	for (int i = 0; i < n2; i++)
		matrix2[i] = new int[m2];

	////////////////����� ������� ���������� � ���������� ������///////////////////

	do
	{
		cout << "�������� ������ ���������� ������\n" <<
			"1 - ������� \n2 - ��������� �������\n";
		cin >> inputMethod;
	} while (inputMethod != 1 && inputMethod != 2);

	cout << "\n������� 1\n\n";
	matrix�hoiceInit(matrix1, n1, m1, inputMethod);

	cout << "\n������� 2\n\n";
	matrix�hoiceInit(matrix2, n2, m2, inputMethod);

	/////////////////���������� ������ � ���������� �������////////////////////////

	while (reducedSize < n1 || reducedSize < n2 || reducedSize < m1 || reducedSize < m2)
		reducedSize *= 2;

	int** reduced_Matrix1 = matrixInitZero(reducedSize);
	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < m1; j++)
			reduced_Matrix1[i][j] = matrix1[i][j];
	}

	int** reduced_Matrix2 = matrixInitZero(reducedSize);
	for (int i = 0; i < n2; i++)
	{
		for (int j = 0; j < m2; j++)
			reduced_Matrix2[i][j] = matrix2[i][j];
	}

	cout << "����������� �������\n";
	cout << "\n������� 1\n\n";
	matrixOutput(reduced_Matrix1, reducedSize, reducedSize);
	cout << "\n������� 2\n\n";
	matrixOutput(reduced_Matrix2, reducedSize, reducedSize);

	///////////////��������� ������ �� ���������� � �� ����������//////////////////

	int** matrix1_1 = submatrixInit(reduced_Matrix1, reducedSize, 0, 0);
	int** matrix1_2 = submatrixInit(reduced_Matrix1, reducedSize, 0, reducedSize / 2);
	int** matrix1_3 = submatrixInit(reduced_Matrix1, reducedSize, reducedSize / 2, 0);
	int** matrix1_4 = submatrixInit(reduced_Matrix1, reducedSize, reducedSize / 2, reducedSize / 2);

	int** matrix2_1 = submatrixInit(reduced_Matrix2, reducedSize, 0, 0);
	int** matrix2_2 = submatrixInit(reduced_Matrix2, reducedSize, 0, reducedSize / 2);
	int** matrix2_3 = submatrixInit(reduced_Matrix2, reducedSize, reducedSize / 2, 0);
	int** matrix2_4 = submatrixInit(reduced_Matrix2, reducedSize, reducedSize / 2, reducedSize / 2);

	////////////////////////�������� ������������� ������ � ���������� ��������//////////////////////////

	int** stepMatrix1 = matrixCreate(reducedSize / 2);
	int** stepMatrix2 = matrixCreate(reducedSize / 2);
	int** stepMatrix3 = matrixCreate(reducedSize / 2);
	int** stepMatrix4 = matrixCreate(reducedSize / 2);
	int** stepMatrix5 = matrixCreate(reducedSize / 2);
	int** stepMatrix6 = matrixCreate(reducedSize / 2);
	int** stepMatrix7 = matrixCreate(reducedSize / 2);

	for (int i = 0; i < reducedSize / 2; i++)
	{
		for (int j = 0; j < reducedSize / 2; j++)
		{
			stepMatrix1[i][j] = 0;
			stepMatrix2[i][j] = 0;
			stepMatrix3[i][j] = 0;
			stepMatrix4[i][j] = 0;
			stepMatrix5[i][j] = 0;
			stepMatrix6[i][j] = 0;
			stepMatrix7[i][j] = 0;
			for (int z = 0; z < reducedSize / 2; z++)
			{
				stepMatrix1[i][j] += (matrix1_1[i][z] + matrix1_4[i][z]) * (matrix2_1[z][j] + matrix2_4[z][j]);
				stepMatrix2[i][j] += (matrix1_3[i][z] + matrix1_4[i][z]) * matrix2_1[z][j];
				stepMatrix3[i][j] += matrix1_1[i][z] * (matrix2_2[z][j] - matrix2_4[z][j]);
				stepMatrix4[i][j] += matrix1_4[i][z] * (matrix2_3[z][j] - matrix2_1[z][j]);
				stepMatrix5[i][j] += (matrix1_1[i][z] + matrix1_2[i][z]) * matrix2_4[z][j];
				stepMatrix6[i][j] += (matrix1_3[i][z] - matrix1_1[i][z]) * (matrix2_1[z][j] + matrix2_2[z][j]);
				stepMatrix7[i][j] += (matrix1_2[i][z] - matrix1_4[i][z]) * (matrix2_3[z][j] + matrix2_4[z][j]);
			}
		}
	}

	///////////////////////�������� ��������������� ������ � ������� �������� �� �������������/////////////////////////

	int** helpMatrix1 = matrixCreate(reducedSize / 2);
	int** helpMatrix2 = matrixCreate(reducedSize / 2);
	int** helpMatrix3 = matrixCreate(reducedSize / 2);
	int** helpMatrix4 = matrixCreate(reducedSize / 2);

	for (int i = 0; i < reducedSize / 2; i++)
	{
		for (int j = 0; j < reducedSize / 2; j++)
		{
			helpMatrix1[i][j] = stepMatrix1[i][j] + stepMatrix4[i][j] - stepMatrix5[i][j] + stepMatrix7[i][j];
			helpMatrix2[i][j] = stepMatrix3[i][j] + stepMatrix5[i][j];
			helpMatrix3[i][j] = stepMatrix2[i][j] + stepMatrix4[i][j];
			helpMatrix4[i][j] = stepMatrix1[i][j] - stepMatrix2[i][j] + stepMatrix3[i][j] + stepMatrix6[i][j];
		}
	}

	///////////////////�������� �������������� ������� � ��������� ���������� �� ��������������� ������/////////////////////////////

	int** resultMatrix = matrixCreate(reducedSize);

	for (int i = 0; i < reducedSize / 2; i++)
	{
		for (int j = 0; j < reducedSize / 2; j++)
		{
			resultMatrix[i][j] = helpMatrix1[i][j];
			resultMatrix[i][j + reducedSize / 2] = helpMatrix2[i][j];
			resultMatrix[i + reducedSize / 2][j] = helpMatrix3[i][j];
			resultMatrix[i + reducedSize / 2][j + reducedSize / 2] = helpMatrix4[i][j];
		}
	}

	////////////////������������ ������ �������������� �������/////////////////////

	int x = 0, f = 100, s = 100;
	for (int i = 0; i < reducedSize; i++)
	{
		x = 0;
		for (int j = 0; j < reducedSize; j++)
		{
			if (resultMatrix[i][j] != 0)
			{
				x++;
				f = 100;
			}
		}
		if (x == 0 && i < f)
		{
			f = i;
		}

		x = 0;
		for (int j = 0; j < reducedSize; j++)
		{
			if (resultMatrix[j][i] != 0)
			{
				x++;
				s = 100;
			}
		}
		if (x == 0 && i < s)
		{
			s = i;
		}
	}

	int** finalMatrix = new int* [f];
	for (int i = 0; i < f; i++)
	{
		finalMatrix[i] = new int[s];
		for (int j = 0; j < s; j++)
			finalMatrix[i][j] = resultMatrix[i][j];
	}

	cout << "\n�������������� �������\n\n";
	matrixOutput(finalMatrix, f, s);

	system("pause");

	for (int i = 0; i < n1; i++)
		delete[] matrix1[i];
	for (int i = 0; i < n2; i++)
		delete[] matrix2[i];
	for (int i = 0; i < reducedSize; i++)
	{
		delete[] reduced_Matrix1[i];
		delete[] reduced_Matrix2[i];
		delete[] resultMatrix[i];
	}
	for (int i = 0; i < f; i++)
		delete[] finalMatrix[i];
	for (int i = 0; i < reducedSize / 2; i++)
	{
		delete[] matrix1_1[i];
		delete[] matrix1_2[i];
		delete[] matrix1_3[i];
		delete[] matrix1_4[i];
		delete[] matrix2_1[i];
		delete[] matrix2_2[i];
		delete[] matrix2_3[i];
		delete[] matrix2_4[i];
		delete[] helpMatrix1[i];
		delete[] helpMatrix2[i];
		delete[] helpMatrix3[i];
		delete[] helpMatrix4[i];
		delete[] stepMatrix1[i];
		delete[] stepMatrix2[i];
		delete[] stepMatrix3[i];
		delete[] stepMatrix4[i];
		delete[] stepMatrix5[i];
		delete[] stepMatrix6[i];
		delete[] stepMatrix7[i];
	}
	delete[] matrix1, matrix2, reduced_Matrix1, reduced_Matrix2, resultMatrix, finalMatrix;
	delete[] matrix1_1, matrix1_2, matrix1_3, matrix1_4, matrix2_1, matrix2_2, matrix2_3, matrix2_4, helpMatrix1, helpMatrix2, helpMatrix3, helpMatrix4;
	delete[] stepMatrix1, stepMatrix2, stepMatrix3, stepMatrix4, stepMatrix5, stepMatrix6, stepMatrix7;
}

void matrixOutput(int** matrix, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
}

int** matrixInitZero(int matrixSize)
{
	int** matrix = new int* [matrixSize];
	for (int i = 0; i < matrixSize; i++)
	{
		matrix[i] = new int[matrixSize];
		for (int j = 0; j < matrixSize; j++)
			matrix[i][j] = 0;
	}
	return matrix;
}

int** matrixCreate(int matrixSize)
{
	int** matrix = new int* [matrixSize];
	for (int i = 0; i < matrixSize; i++)
	{
		matrix[i] = new int[matrixSize];
	}
	return matrix;
}

void matrix�hoiceInit(int** matrix, int n, int m, int inputMethod)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (inputMethod == 1)
				cin >> matrix[i][j];
			else if (inputMethod == 2)
				matrix[i][j] = rand() % 10;
	matrixOutput(matrix, n, m);
}

int** submatrixInit(int** mainMatrix, int reducedSize, int shiftI, int shiftJ)
{
	int** submatrix = new int* [reducedSize / 2];
	for (int i = 0; i < reducedSize / 2; i++)
	{
		submatrix[i] = new int[reducedSize / 2];
		for (int j = 0; j < reducedSize / 2; j++)
			submatrix[i][j] = mainMatrix[i + shiftI][j + shiftJ];
	}
	return submatrix;
}