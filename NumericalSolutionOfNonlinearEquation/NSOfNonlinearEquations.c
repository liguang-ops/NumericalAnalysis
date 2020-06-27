/*
 * @Description: 非线性方程的数值解法
 * @Author: liguang-ops
 * @Github: https://github.com/liguang-ops
 * @Date: 2020-06-27 18:12:17
 * @LastEditors: liguang-ops
 * @LastEditTime: 2020-06-27 19:13:36
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double func(double x)
{
    //二分法测试 f(x)
    //return x*x*x + 4*x*x -10;
    //迭代法测试，Aitken加速迭代测试  φ(x)
    //return exp(-x);
    //牛顿迭代法 f(x)
    return x - exp(-x);
}

double DerivativeOffunc(double x)
{
    double dx = 1e-6;
    double dy = func(x + dx) - func(x);
    return dy/dx;
}
/**
 * @Description: 二分法求函数零点，前提是保证函数单调,f(lower)*f(upper) < 0
 * @param lower {double} 区间下限
 * @param upper {double} 区间上限 
 * @param error {double} 误差
 * @return: 零点
 */
double BinarySearch(double lower,double upper,double error)
{
    double mid = (upper + lower)/2.0;
    if((upper - lower) <= error)
        return (upper + lower)/2.0;
    if(func(lower) * func(mid) < 0)
        return BinarySearch(lower,mid,error);
    else if(func(mid) * func(upper) < 0)
        return BinarySearch(mid,upper,error);
    return mid;
}

/**
 * @Description: 普通迭代公式，x = φ(_x),要求 |φ'(x)| <=L<1
 * @param _x {double} 初值
 * @param error {double} 误差 
 * @param iternum {int} 迭代次数
 * @return: 最终迭代结果
 */
double Iteration(double _x,double error,int* iternum)
{
    double x = func(_x);
    while (fabs(x - _x) > error)
    {
        _x = x;
        x = func(_x);
        *iternum += 1;
    }
    return x;
}

/**
 * @Description: Aitken加速迭代公式 
 * @param _x {double} 初值
 * @param error {double} 误差 
 * @param iternum {int} 迭代次数
 * @return: 最终迭代结果
 */
double AitkenIteration(double _x,double error,int* iternum)
{
    double x1 = func(_x);
    double x2 = func(x1);
    double x = x2 - (x2 - x1)*(x2 - x1)/(_x - 2 * x1 + x2);
    while (fabs(x - _x) > error)
    {
        _x = x;
        x1 = func(_x);
        x2 = func(x1);
        x = x2 - (x2 - x1)*(x2 - x1)/(_x - 2 * x1 + x2);
        *iternum +=1;
    }
    return x;
}

/**
 * @Description: 牛顿迭代法,要保证f'(x)和f''(x) ；连续且不变号，另外∀_X∈[a,b],有f(_x)*f''(_X)>0
 * @param _x {double} 初值
 * @param error {double} 误差 
 * @param iternum {int} 迭代次数
 * @return: 最终迭代结果
 */
double NewtonIteration(double _x,double error,int* iternum)
{
    double x = _x - func(_x) / DerivativeOffunc(_x);
    while (fabs(x - _x) > error)
    {
        _x = x;
        x = _x - func(_x) / DerivativeOffunc(_x);
        *iternum +=1;
    }
    return x;
}

/**
 * @Description: 牛顿迭代法,要保证f'(x)和f''(x) ；连续且不变号，另外∀_X∈[a,b],有f(_x)*f''(_X)>0
 * @param _x {double} 初值
 * @param error {double} 误差 
 * @param iternum {int} 迭代次数
 * @return: 最终迭代结果
 */
double NewtondownhillIteration(double _x,double error,int* iternum)
{
    double w = 1.0;
    double x = _x - w * func(_x) / DerivativeOffunc(_x);
    
}
void main(void)
{
    int  iters= 1;
    //printf("%lf",BinarySearch(1.0,2.0,5e-3));
    //printf("iternumbers: %d, x = %lf\n",iters,Iteration(0.5,1e-4,&iters));
    //printf("iternumbers: %d, x = %lf\n",iters,AitkenIteration(0.5,1e-4,&iters));
    printf("iternumbers: %d, x = %lf\n",iters,NewtonIteration(0.5,1e-4,&iters));
    system("pause");
}
