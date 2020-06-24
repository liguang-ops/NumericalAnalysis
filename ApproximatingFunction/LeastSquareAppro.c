/*
 * @Description: 最佳平方逼近
 * @Author: liguang-ops
 * @Github: https://github.com/liguang-ops
 * @Date: 2020-06-22 16:05:41
 * @LastEditors: liguang-ops
 * @LastEditTime: 2020-06-23 09:28:01
 */ 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
/**
 * @Description: 切比雪夫正交多项式
 * @param x {double} 横坐标
 * @param rank {int} 多项式的阶数 
 * @return: 
 */
double Chebyshev(double x ,int rank)
{
    if(rank == 0 )
        return 1;
    else if (rank == 1)
        return x;
    else
        return 2*x*Chebyshev(x,rank -1) - Chebyshev(x,rank -2);
}

/**
 * @Description: 勒让德正交多项式
 * @param x {double} 横坐标
 * @param rank {int} 多项式的阶数
 * @return: 
 */
double Legendre(double x, int rank)
{
    if(rank == 0 )
        return 1;
    else if (rank == 1)
        return x;
    else
        return (2.0 - 1.0/rank)*x*Legendre(x,rank-1) - (1.0 - 1.0/rank)*Legendre(x,rank-2);
}

/**
 * @Description: 被逼近函数 y = x^4
 * @param y {int} 无意义，仅参数与勒让德多项式一样，方便写函数指针 
 * @return: 
 */
double func(double x,int y)
{
    return x*x*x*x;
}

/**
 * @Description: 求任意函数的定积分，这里固定成两个函数积组成的函数，方便求勒让德函数系的系数
 * @param lower {double} 积分下限
 * @param upper {double} 积分上限 
 * @param funcA {double} 被积函数A
 * @param funcB {double} 被积函数B
 * @param rankA {int} 勒让德多项式阶数
 * @param funcB {int} 勒让德多项式阶数
 * @return: 定积分
 */
double Integration(double lower,double upper,double (*funcA)(double,int),double (*funcB)(double,int),int rankA,int rankB)
{
    int n = 1e+6;  //区间分割块数
    int i;
    double sum = 0.0;
    double d = (upper - lower)/n;  //小区间长度
    for( i = 0;i<n;i++)
    {
        double mid = ((lower + i*d) + (lower +(i+1)*d))/2;  //取中点
        sum += d*funcA(mid,rankA)*funcB(mid,rankB);
    }
    return sum;
}


void main(void)
{
    double x = 0.5; // x∈[-1,1]
    double s = 0.0;
    //求func在[-1,1]上的最佳平方逼近勒让德多项式的参数ci,此时权函数衡等于1
    int i;
    double c[3];
    for(i = 0 ;i<3;i++)
    {
        //ci = (pi,f)/(pi,pi),函数内积，函数A和函数B:(A,B) = ∫(ρ*A*B)dx,区间为[-1,1]
        c[i] = Integration(-1,1,Legendre,func,i,0)/Integration(-1,1,Legendre,Legendre,i,i);
        printf("c[%d] = %lf\n",i,c[i]);
        s += c[i] * Legendre(x,i);
    }
    printf("s(%lf) = %lf\n",x,s);
    //printf("%lf",Legendre(0.5,2));
    system("pause");
}