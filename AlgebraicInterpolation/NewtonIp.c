/*
 * @Description: 牛顿插值公式
 * @Author: liguang-ops
 * @Github: https://github.com/liguang-ops
 * @Date: 2020-06-21 10:53:48
 * @LastEditors: liguang-ops
 * @LastEditTime: 2020-06-21 18:03:23
 */ 
#include <stdio.h>
#include <stdlib.h>
#define N 5
//double nodesArrays[5][2] = {{100.0,9.84},{200,19.32},{400,43.49},{800,102.58},{1500,212.07}};
double nodesArrays[5][2] = {{0.10,15.0},{0.30,18},{0.55,21},{0.70,22.6},{0.80,23.8}};

/**
 * @Description: 递归求解j-i+1个点的差商
 * @param  i {int}  代表第一个点 ,物理序号
 * @param  j {int}  代表最后一个点
 * @return: 差商
 */
double DiffQuotient(int i,int j)
{
    if(i == j)
        return nodesArrays[i][1];
    else
        return (DiffQuotient(i,j-1) - DiffQuotient(i+1,j))/(nodesArrays[i][0] - nodesArrays[j][0]);
    
}
void main(void)
{
    double fina = 0.0;
    double input = 0.4;
    int rank = 4;
    int i,j;
    for(i = 0; i<rank + 1 ;i++)    //外层，求加法
    {
        double temp = 1.0;
        for(j = 0;j<i;j++)     //里层，求乘法
            temp *=input - nodesArrays[j][0];
        temp *= DiffQuotient(0,i);
        fina +=temp;
    }
    printf("%lf",fina);
    system("pause");
}