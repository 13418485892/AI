// AI1_SimpleAdd.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include<iostream>
#include <vector>
using namespace std;

#define v_v_d vector<vector<double>>
#define v_d vector<double>

// �����Է��̡�data[count*(count+1)]�������飻count������Ԫ����
// Answer[count]��������� �����أ�0���ɹ���-1�޽���������

//���صĸ�������
void j_memcpy(v_d::iterator  dat, v_d d, int n)
{
    for (int i = 0; i < n; i++)
    {
        dat[i] = d[i];
    }
}
void j_memcpy(v_d  &dat, v_d d, int n)
{
    for (int i = 0; i < n; i++)
    {
        dat[i] = d[i];
    }
}
void j_memcpy(v_d &dat, v_d::iterator d, int n)
{
    for (int i = 0; i < n; i++)
    {
        dat[i] = d[i];
    }
}
void j_memcpy(v_d::iterator  dat, v_d::iterator d, int n)
{
    for (int i = 0; i < n; i++)
    {
        dat[i] = d[i];
    }
}
void itSum(v_d::iterator &it, int n, v_d &data)
{
    int t = 0;

    while (it != data.end() && t++ < n) it++;
}

//�������汾
int LinearEquationsCjj(vector<double> &data, int count, double *Answer)
{
    int j, m, n;
    vector<double> ::iterator d = data.begin();
    //double *d = data;
    double tmp;
    //double *d = data;
    vector<vector<double>> dat;
    dat = vector<vector<double>>(count);

    //dat = (double**)malloc(count * sizeof(double*));
    for (m = 0; m < count; m++, itSum(d, count + 1, data))
    {
        dat[m] = vector<double>(count + 1);
        //dat[m] = (double*)malloc((count + 1) * sizeof(double));
        j_memcpy(dat[m], d, count + 1);
        //memcpy(dat[m], d, (count + 1) * sizeof(double));
    }

    vector<double> jj = v_d(count + 1);
    d = jj.begin();

    //d = (double*)malloc((count + 1) * sizeof(double));
    for (m = 0; m < count - 1; m++)
    {
        // ������Խ���Ԫ��Ϊ0���н���
        for (n = m + 1; n < count && dat[m][m] == 0.0; n++)
        {
            if (dat[n][m] != 0.0)
            {
                j_memcpy(d, dat[m], (count + 1));
                j_memcpy(dat[m], dat[n], (count + 1));
                j_memcpy(dat[n], d, (count + 1));
                //memcpy(d, dat[m], (count + 1) * sizeof(double));
                //memcpy(dat[m], dat[n], (count + 1) * sizeof(double));
                //memcpy(dat[n], d, (count + 1) * sizeof(double));
            }
        }

        // �н��������Խ���Ԫ����ȻΪ0���޽⣬����-1
        if (dat[m][m] == 0.0)
        {
            //FreeData(dat, d, count);
            return -1;
        }

        // ��Ԫ
        for (n = m + 1; n < count; n++)
        {
            tmp = dat[n][m] / dat[m][m];

            for (j = m; j <= count; j++)
                dat[n][j] -= tmp * dat[m][j];
        }
    }

    for (j = 0; j < count; j++)
        d[j] = 0.0;

    // ���count - 1��Ԫ
    Answer[count - 1] = dat[count - 1][count] / dat[count - 1][count - 1];

    // ���д������Ԫ
    for (m = count - 2; m >= 0; m--)
    {
        for (j = count - 1; j > m; j--)
            d[m] += Answer[j] * dat[m][j];

        Answer[m] = (dat[m][count] - d[m]) / dat[m][m];
    }

    //FreeData(dat, d, count);
    return 0;
}
// ���Ԫ�ع鷽�̣�Y = B0 + B1X1 + B2X2 + ...BnXn
// data[rows*cols]��ά���飻X1i,X2i,...Xni,Yi (i=0 to rows-1)
// rows������������cols����������Answer[cols]�����ػع�ϵ������(B0,B1...Bn)
// ����ֵ��0���ɹ���-1����
//�������汾
int MultipleRegressionCjj(vector<double> &data, int rows, int cols, double *Answer)
{
    int m, n, i, count = cols - 1;
    double a, b;
    vector<double> ::iterator p;
    vector<double>dat;

    if (data.size() == 0 || Answer == 0 || rows < 2 || cols < 2)
        return -1;

    dat = vector<double>(cols * (cols + 1));
    dat[0] = (double)rows;

    for (n = 0; n < count; n++)                     // n = 0 to cols - 2
    {
        if (n == 1)
        {
            int jhasd = 1;
        }

        a = b = 0.0;

        for (p = data.begin() + n, m = 0; m < rows; m++, itSum(p, cols, data))
        {
            int my = *p;
            a += *p;
            b += (*p * *p);
        }

        dat[n + 1] = a;                              // dat[0, n+1] = Sum(Xn)
        dat[(n + 1) * (cols + 1)] = a;               // dat[n+1, 0] = Sum(Xn)
        dat[(n + 1) * (cols + 1) + n + 1] = b;       // dat[n+1,n+1] = Sum(Xn * Xn)

        for (i = n + 1; i < count; i++)             // i = n+1 to cols - 2
        {
            for (a = 0.0, p = data.begin(), m = 0; m < rows; m++, itSum(p, cols, data))
                a += (p[n] * p[i]);

            dat[(n + 1) * (cols + 1) + i + 1] = a;   // dat[n+1, i+1] = Sum(Xn * Xi)
            dat[(i + 1) * (cols + 1) + n + 1] = a;   // dat[i+1, n+1] = Sum(Xn * Xi)
        }
    }

    for (b = 0.0, m = 0, p = data.begin() + n; m < rows; m++, itSum(p, cols, data))
        b += *p;

    dat[cols] = b;                                   // dat[0, cols] = Sum(Y)

    for (n = 0; n < count; n++)
    {
        for (a = 0.0, p = data.begin(), m = 0; m < rows; m++, itSum(p, cols, data))
            a += (p[n] * p[count]);

        dat[(n + 1) * (cols + 1) + cols] = a;        // dat[n+1, cols] = Sum(Xn * Y)
    }

    n = LinearEquationsCjj(dat, cols, Answer);          // ���㷽��ʽ

    return n;
}
void Display(double *dat, double *Answer, double *SquarePoor, int rows, int cols)
{
    double v, *p;
    int i, j;
    printf("�ع鷽��ʽ:    Y = %.5lf", Answer[0]);

    for (i = 1; i < cols; i++)
        printf(" + %.5lf*X%d", Answer[i], i);

    system("pause");
}
double _data[15][5] =
{
    //   X1   X2    X3   X4    Y
    /*
    { 316, 1536, 874, 981, 3894 },
    { 385, 1771, 777, 1386, 4628 },
    { 299, 1565, 678, 1672, 4569 },
    { 326, 1970, 785, 1864, 5340 },
    { 441, 1890, 785, 2143, 5449 },
    { 460, 2050, 709, 2176, 5599 },
    { 470, 1873, 673, 1769, 5010 },
    { 504, 1955, 793, 2207, 5694 },
    { 348, 2016, 968, 2251, 5792 },
    { 400, 2199, 944, 2390, 6126 },
    { 496, 1328, 749, 2287, 5025 },
    { 497, 1920, 952, 2388, 5924 },
    { 533, 1400, 1452, 2093, 5657 },
    { 506, 1612, 1587, 2083, 6019 },
    { 458, 1613, 1485, 2390, 6141 },
    */

    { 316, 1536, 874, 981, 3707 },
    { 385, 1771, 777, 1386, 4319 },
    { 299, 1565, 678, 1672, 4214 },

    { 326, 1970, 785, 1864, 4945 },
    { 441, 1890, 785, 2143, 5259 },
    { 460, 2050, 709, 2176, 5395 },

    { 470, 1873, 673, 1769, 4785 },
    { 504, 1955, 793, 2207, 5459 },
    { 348, 2016, 968, 2251, 5583 },

    { 400, 2199, 944, 2390, 5933 },
    { 496, 1328, 749, 2287, 4860 },
    { 497, 1920, 952, 2388, 5755 },

    { 533, 1400, 1452, 2093, 5487 },
    { 506, 1612, 1587, 2083, 5788 },
    { 458, 1613, 1485, 2390, 5946 },
};


int main()
{
    //������������ݾ��󣬺͸����Ļع�Ԫ����ѵ�������ع鷽��ʽ
    double Answer[5], SquarePoor[4];
    int rows = 15, cols = 5;//��ʾ��15�����ݣ���4Ԫ���Իع飬��������ع鷽��ʽ
    v_d j_data;//data�ɱ�����

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            j_data.push_back(_data[i][j]);
        }
    }

    if (MultipleRegressionCjj(j_data, rows, cols, Answer) == 0)
        Display((double *)_data, Answer, SquarePoor, rows, cols);

    return 0;
}