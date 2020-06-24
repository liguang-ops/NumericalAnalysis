/*
 * @Description: 变步长积分公式
 * @Author: liguang-ops
 * @Github: https://github.com/liguang-ops
 * @Date: 2020-06-23 17:27:27
 * @LastEditors: liguang-ops
 * @LastEditTime: 2020-06-24 09:19:41
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double func(double x)
{
    if(x == 0)
        return 1;
    return sin(x)/x;
}

/**
 * @Description: 递推复化梯形公式
 * @param lower {double} 积分下限 
 * @param upper {double} 积分上限
 * @param n {int} 变长复化梯形公式的阶数 , 必须为2的整数幂
 * @return: 
 */
double RecursionCompInTrapezoid(double lower,double upper, int n)
{
    if((n & (n-1)) != 0 )
        return -1.0;
    if( n == 1)
        return 0.5*(upper - lower)*(func(upper) + func(lower));
    else
    {
        double s =0.0;
        double h =  (upper - lower) / (n/2) ;   //h 是上一个的步长，比如求T8，h = (b-a)/(8/2)
        int i ;
        for(i = 0; i<n*0.5 ;i++)   //n*0.5 是由公式得出，点的个数为n/2,
            s+=func(lower + i*h + h/2);   //这边的步长也是上一个的步长
        return 0.5 * RecursionCompInTrapezoid(lower,upper,n/2) + 0.5 * h * s;
    }  
}

/**
 * @Description: 变长复化梯形公式
 * @param lower {double} 积分下限 
 * @param upper {double} 积分上限
 * @param error {double} 误差容忍值
 * @param T {double} 递归所需参数，初始调用时随意设置
 * @param n {int} 递归所需参数，初始调用时必须为1
 * @return: 
 */
double StepChangeCompInTrapezoid(double lower,double upper, double error, double T, int n )
{
    double T1;
    if( n==1 )
        T1 = (upper -lower) * 0.5 *(func(upper) + func(lower));
    else
        T1 = T;
    double h = (upper - lower) / n;
    double s = 0.0;
    int i ;
    for(i = 0; i<n ;i++)
        s+=func(lower + i*h + h/2);
    double T2 = T1*0.5 + h*0.5*s;
    printf("T[%d] = %lf     error = %lf\n",n,T1,T2 - T1);
    if (fabs(T2 - T1) <= error)
        return T2;
    else
        return StepChangeCompInTrapezoid(lower,upper,error,T2,2*n);
    
}

/**
 * @Description: 变长复化梯形公式改版，之前写的那个内容很丑，不够好看，函数参数设计太傻，把两个功能合到一块去了
 * @param lower {double} 积分下限 
 * @param upper {double} 积分上限
 * @param error {double} 误差容忍值
 * @return: 
 */
double StepChangeCompInTrapezoidNew(double lower,double upper, double error)
{
    if(error <= 0)
        return -1.0;
    double _T = RecursionCompInTrapezoid(lower,upper,1);
    printf("T[1] = %lf     error = #INF\n",_T);
    double T ;
    int i = 2;
    while (1)
    {
        T = RecursionCompInTrapezoid(lower,upper,i);
        printf("T[%d] = %lf     error = %lf\n",i,T,T - _T);
        if(fabs(T - _T) <= error)
            break;
        else
            _T = T;
        i *=2;
    }
    printf("%lf",T);
    return T;
}

/**
 * @Description: 隆贝格积分
 * @param {type} 
 * @return: 
 */
double CompInRomberg(double lower, double upper ,double error)
{
    /*变长复化辛普森公式不知到，S2n = f(Sn)
     *边长复化Cotes积分不知道，C2n = g(Cn)
     *能推出来，时间来不及
     */
}

/**
 * @Description: 自适应辛普森积分
 * @param {type} 
 * @return: 
 */
double AutoCompInSimpson()
{
    /*
     *没时间，后面再打算
     */
}
void main(void)
{
    //printf("%d",6%5 ==0);
    // printf("%lf",RecursionCompInTrapezoid(0,1,1));
    // printf("%lf",StepChangeCompInTrapezoid(0,1,0.00001,0,1));
    printf("%lf",StepChangeCompInTrapezoidNew(0,1,0.0001));
    system("pause");
}