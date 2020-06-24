/*
 * @Description: 复化梯形公式和复化辛普森公式
 * @Author: liguang-ops
 * @Github: https://github.com/liguang-ops
 * @Date: 2020-06-23 16:17:13
 * @LastEditors: liguang-ops
 * @LastEditTime: 2020-06-23 22:34:57
 */ 
#include <stdio.h>
#include <stdlib.h>
double func(double x)
{
    return 4.0/(1.0 + x*x);
}

/**
 * @Description: 复化梯形公式
 * @param lower {double} 积分下限 
 * @param upper {double} 积分上限
 * @param n {int} 区间切分块数（这样是比较简单的理解，）
 * @return: 
 */
double CompositeInTrapezoid(double lower ,double upper,int n)
{
    int i ;
    double Tn = func(lower) + func(upper);
    double h = (upper - lower)/n;  //步长
    for(i= 1;i<n;i++)
        Tn += 2.0*func(lower + i*h);
    Tn = h/2.0 * Tn;
    return Tn;
}

/**
 * @Description: 复合辛普森公式
 * @param lower {double} 积分下限 
 * @param upper {double} 积分上限
 * @param n {int} 区间切分块数（这样是比较简单的理解，）
 * @return: 
 */
double CompositeInSimpson(double lower,double upper,int n)
{
    int i;
    double Sn = func(lower) + func(upper);
    double h = (upper - lower)/n;  //步长
    for(i = 1; i<n;i++)
        /*
         *lower + i*h - h/2.0 
         *lower + i*h - 1/2*h
         *二者结果不一样，第一个正确，第二个错误，第二个1/2*h = 0，不知道为什么
         */
        Sn += 4*func(lower + i*h - h/2.0) + 2*func(lower + i*h);
    Sn += 4*func(lower + n*h - h/2.0);
    Sn = h/6.0 * Sn;
    return Sn;
}

void main(void)
{
    //printf("%lf",CompositeTrapezoid(0,1,8));
    printf("%lf",CompositeInSimpson(0,1,4));
    system("pause");
}
