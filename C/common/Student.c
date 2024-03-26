#include <stdio.h>
#include <stdlib.h>

#define MAX 100
struct student
{
    int num;
    char name[20];
    int score[3];
} stu[MAX];

int main()
{
    int i, sum, aver, choice, n = 0;
    while (1)
    {
        printf("\n\n\n\t\t**************学生成绩管理系统**************\n\n");
        printf("\t\t      =>1、查询所有学生信息\n\n");
        printf("\t\t      =>2、添加学生信息\n\n");
        printf("\t\t      =>3、修改学生信息\n\n");
        printf("\t\t      =>4、查询学生总分及平均分\n\n");
        printf("\t\t      =>0、退出\n\n");
        printf("请输入你的选择：");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf(" 学号   姓名   语文   数学   英语\n");
            for (i = 0; i < n; i++)
                printf("%ld  %s  %d  %d  %d\n", // 输出所有学生信息
                       stu[i].num,
                       stu[i].name,
                       stu[i].score[0],
                       stu[i].score[1],
                       stu[i].score[2]);
            break;

        case 2:
            printf("编号为%d的学生信息如下：\n", n + 1);
            printf("学号：");
            scanf("%d%*c", &stu[n].num);
            printf("姓名：");
            scanf("%[^\n]%*c", stu[n].name);
            printf("语文：");
            scanf("%d", &stu[n].score[0]);
            printf("数学：");
            scanf("%d", &stu[n].score[1]);
            printf("英语：");
            scanf("%d", &stu[n].score[2]);
            n++;
            break;

        case 3:
            printf("请输入要修改的学生编号：");
            scanf("%d", &i);
            if (i > n)
            {
                printf("无此学生！\n");
                continue;
            }
            else
            {
                printf("学号：");
                scanf("%ld", &stu[i - 1].num);
                printf("姓名：");
                scanf("%s", stu[i - 1].name);
                printf("语文：");
                scanf("%d", &stu[i - 1].score[0]);
                printf("数学：");
                scanf("%d", &stu[i - 1].score[1]);
                printf("英语：");
                scanf("%d", &stu[i - 1].score[2]);
            }
            break;

        case 4:
            printf("请输入要查询的学生编号：");
            scanf("%d", &i);
            if (i > n)
            {
                printf("无此学生！\n");
                continue;
            }
            else
            {
                sum = stu[i - 1].score[0] +
                      stu[i - 1].score[1] +
                      stu[i - 1].score[2];
                aver = sum / 3;
                printf("%s的总分：%d,平均分：%.2f\n",
                       stu[i - 1].name, sum, aver * 1.0);
            }
            break;

        case 0:
            exit(0);
            break;

        default:
            printf("输入有误！\n");
        }
    }
    return 0;
}
