/*
 * @Description: 最佳一致逼近
 * @Author: liguang-ops
 * @Github: https://github.com/liguang-ops
 * @Date: 2020-06-22 15:30:13
 * @LastEditors: liguang-ops
 * @LastEditTime: 2020-06-22 20:28:14
 */ 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
/**
 * @Description: e^x函数
 * @param x {double} 横坐标 
 * @return: 纵坐标
 */
double func(double x)
{
    return exp(x);
}

/**
 * @Description: 求导数
 * @param x {double} 横坐标 
 * @return: 
 */
double GetDerivative(double x)
{
    double dx = 1e-6;
    double dy = func(x + dx) - func(x);
    return dy/dx;
}

/**
 * @Description: 二分法求函数零点，前提是保证函数单调
 * @param lower {double} 区间下限
 * @param upper {double} 区间上限 
 * @param a 函数值 ，即f'(x1) = a,求x1
 * @return: 零点
 */
double FindXi(double lower,double upper ,double a)
{
    double mid = (upper + lower)/2.0;
    if((upper - lower) <= 1e-6)
        return (upper + lower)/2.0;
    if((GetDerivative(lower) - a) * (GetDerivative(mid) - a) < 0)
        return FindXi(lower,mid,a);
    else if((GetDerivative(mid) - a) * (GetDerivative(upper) - a) < 0)
        return FindXi(mid,upper,a);
    return mid;
}

void main(void)
{
    double nodesArrays[2] = {0.0,1.0};  //函数区间[0,1]
    //需要拟合的函数 y = a0 + a1 * x
    double a1 = (func(nodesArrays[0]) - func(nodesArrays[1]))/(nodesArrays[0] - nodesArrays[1]);
    double x1 = FindXi(nodesArrays[0],nodesArrays[1],a1);
    double a0 = (func(nodesArrays[0]) + func(x1))/2 - a1 * (nodesArrays[0] + x1)/2;
    printf("%lf",a0);
    system("pause");
}
