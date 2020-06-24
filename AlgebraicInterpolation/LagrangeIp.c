/*
 * @Description: 拉格朗日线性插值方法
 * @Author: liguang-ops
 * @Github: https://github.com/liguang-ops
 * @Date: 2020-06-20 14:21:32
 * @LastEditors: liguang-ops
 * @LastEditTime: 2020-06-20 21:45:06
 */ 
/**
 * @Description: 获取拉格朗日函数
 * @param Nodes {double} 插值节点，2维，
 * @param n {int} 节点个数
 * @param x {double} 请求节点的值
 * @return: 拉格朗日插值函数
 */
#include <stdio.h>
#include <stdlib.h>
double LagrangeInp(double (*Nodes)[2], int n,double x)
{
    /*
     *拉格朗日插值函数li(x) = Bi/Ai 
     */
    double fina = 0.0;  //最终结果
    double *Bi;  //分子
    if(!(Bi=(double *)calloc(n,sizeof(double)))) 
        exit(1);
    static double *Ai;    //缓存Ai，提高性能,分母
    if(!(Ai=(double *)calloc(n,sizeof(double)))) 
        exit(1);
    //计算Ai
    int i = 0,j = 0;
    for(i = 0 ; i < n ; i++)
    {
        Ai[i] = 1.0;
        for(j = 0 ; j < n; j++)
        {
            if(i != j)
                Ai[i] *=  Nodes[i][0] - Nodes[j][0];
        }    
    }

    //计算Bi和最终结果
    for(i = 0 ; i < n ; i++)
    {
        Bi[i] = 1.0;
        for(j = 0 ; j < n; j++)
        {
            if(i != j)
                Bi[i] *= x- Nodes[j][0];
        }
        fina += Bi[i]/Ai[i] * Nodes[i][1];
    }
    return fina;
}

void main(void)
{
    double nodesArrays[4][2] = {{0.4,-0.916291},{0.5,-0.693147},{0.7,-0.356675},{0.8,-0.223144}};
    double A = LagrangeInp(nodesArrays,4,0.6);
    printf("%lf",A);
    getchar();

    double x =0.6;
    double fina = 0.0;
    int i,j;
    for(i = 0;i<4;i++)
    {
        double a = 1.0,b=1.0;
        for(j=0;j<4;j++)
        {
            if(i != j)
            {
                a *= nodesArrays[i][0] - nodesArrays[j][0];
                b *= x - nodesArrays[j][0];
            }
        }
        fina += b/a * nodesArrays[i][1];
    }
    printf("%lf",fina);
    getchar();
}