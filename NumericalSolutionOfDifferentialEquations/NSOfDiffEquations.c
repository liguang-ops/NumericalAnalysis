/*
 * @Description: 常微分方程数值解
 * @Author: liguang-ops
 * @Github: https://github.com/liguang-ops
 * @Date: 2020-06-26 20:42:36
 * @LastEditors: liguang-ops
 * @LastEditTime: 2020-06-26 22:04:03
 */ 

#include<stdio.h>
#include<stdlib.h>
/**
 * @Description: y的导函数，y' = f(x,y)
 * @param {type} 
 * @return: 
 */
double func(double x,double y)
{
    return x*x -y;
}

/**
 * @Description:欧拉公式
 * @param lower {double} 积分下限 
 * @param upper {double} 积分上限
 * @param x0 {double} 初值 
 * @param y0 {double} 初值
 * @param n {int} 区间切分块数
 * @return: 
 */
double Euler(double lower,double upper,double x0,double y0 ,int n)
{
    int i = 0;
    double _y = y0;
    double y;
    double h = (upper - lower) / n;
    while (i<n)
    {
        y = _y + h * func(x0 + i * h,_y);
        printf("%d,    %lf\n",i +1 ,y);
        _y = y;
        i++;
    }
    //printf("%lf",y);
    return y;
}

/**
 * @Description: 改进的欧拉公式
 * @param lower {double} 积分下限 
 * @param upper {double} 积分上限
 * @param x0 {double} 初值 
 * @param y0 {double} 初值
 * @param n {int} 区间切分块数
 * @return: 
 */
double BetterEuler(double lower,double upper,double x0,double y0 ,int n)
{
    int i = 0;
    double _y = y0;
    double y;
    double h = (upper - lower) / n;
    while (i<n)
    {
        double y_ = _y + h * func(x0 + i * h,_y);
        y = _y + h/2 *(func(x0 + i * h,_y) + func(x0 + (i+1)*h,y_));
        printf("%d,    %lf\n",i +1 ,y);
        _y = y;
        i++;
    }
    //printf("%lf",y);
    return y;
}

/**
 * @Description: 4阶龙格库塔法
 * @param lower {double} 积分下限 
 * @param upper {double} 积分上限
 * @param x0 {double} 初值 
 * @param y0 {double} 初值
 * @param n {int} 区间切分块数
 * @return: 
 */
double FourStepsRungeKutta(double lower,double upper,double x0,double y0 ,int n)
{
    int i = 0;
    double _y = y0;
    double y;
    double h = (upper - lower) / n;
    while (i<n)
    {
        double k1 = func(x0 + i * h,_y);
        double k2 = func(x0 + i * h + h/2,_y + h/2 *k1);
        double k3 = func(x0 + i * h + h/2,_y + h/2 *k2);
        double k4 = func(x0 + i * h + h,_y + h *k3);
        y = _y + h/6 *(k1 + 2*k2 + 2*k3 +k4);
        printf("%d,    %lf\n",i +1 ,y);
        _y = y;
        i++;
    }
    //printf("%lf",y);
    return y;
}
void main(void)
{
    //printf("%lf",BetterEuler(0,1.5,0,1,15));
    printf("%lf",FourStepsRungeKutta(0,1,0,1,10));
    system("pause");
}
