#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<math.h>
int a[4][4]={0},D=0,M=2048;void showdata(){int i,j;system("CLS");for(i=0;i<4+2;++i){printf("%5c",'=');}printf("\n");for(i=0;i<4;++i){printf("%5c",'+');for(j=0;j<4;++j)if(a[i][j]){printf("%5d",a[i][j]);}else{printf("%5c",' ');}printf("%5c",'+');printf("\n");}for(i=0;i<4+2;++i){printf("%5c",'=');}printf("\n");}int isNotFull(){for(int i=0;i<4;++i)for(int j=0;j<4;++j)if(!a[i][j])return 1;return 0;}void randomdata(){int r,c;do{r=rand()%4;c=rand()%4;}while(a[r][c]!=0);a[r][c]=pow(2,rand()%2+1);}int getMax(){int max=0;for(int i=0;i<4;++i)for(int j=0;j<4;++j)if(max<a[i][j])max=a[i][j];return max;}int add(){int i,j,cr,w,F=0;switch(D){case 1:for(i=1;i<4;++i)for(j=0;j<4;++j){cr=i;w=0;while(cr>=1&&a[cr][j]!=0){if(a[cr-1][j]==0){a[cr-1][j]=a[cr][j];a[cr][j]=0;F=1;}else{if(a[cr-1][j]==a[cr][j]&&w==0){a[cr-1][j]=a[cr-1][j]*2;a[cr][j]=0;w=F=1;}else break;}cr--;}}break;case 2:for(i=4-2;i>=0;--i)for(j=0;j<4;++j){cr=i;w=0;while(cr<=4-2&&a[cr][j] != 0){if(a[cr+1][j]==0){a[cr+1][j]=a[cr][j];a[cr][j]=0;F=1;}else{if(a[cr+1][j]==a[cr][j]&&w==0){a[cr+1][j]=a[cr+1][j]*2;a[cr][j]=0;w=F=1;}else break;}cr++;}}break;case 3: for(i=0;i<4;++i)for(j=1;j<4;++j){cr=j;w=0;while(cr>=1&&a[i][cr] != 0){if(a[i][cr-1]==0){a[i][cr-1]=a[i][cr];a[i][cr]=0;F=1;}else{if(a[i][cr-1]==a[i][cr]&&w==0){a[i][cr-1]=a[i][cr-1]*2;a[i][cr]=0;w=F=1;}else break;}cr--;}}break;case 4:for(i=0;i<4;++i)for(j=4-2;j>=0;--j){cr=j;w=0;while(cr<=4-2&&a[i][cr] != 0){if(a[i][cr+1]==0){a[i][cr+1]=a[i][cr];a[i][cr]=0;F=1;}else{if(a[i][cr+1]==a[i][cr]&&w==0){a[i][cr+1]=a[i][cr+1]*2;a[i][cr]=0;w=F=1;}else break;}cr++;}}break;}return F;}int getKey(){char ch=getch();if(ch<0){switch(getch()){case 72:D=1;return 1;case 80:D=2;return 1;case 75:D=3;return 1;case 77:D=4;return 1;}}return 0;}int canAdd(){for(int i=0;i<4;++i)for(int j=0;j<4-1;++j)if(a[i][j]==a[i][j+1]&&a[i][j]==a[i+1][j]){return 1;}return 0;}int main(){int mov,isf;printf("请输入游戏要拼凑的最大数字，例如32，64，128，...，2048：");scanf("%d",&M);srand(time(NULL));randomdata();randomdata();showdata();do{while(!getKey());mov=add();if(mov){showdata();}if(getMax()>=M){printf("你赢了！\n");break;}isf=isNotFull();if(isf){if(mov){randomdata();showdata();}}else if(!canAdd())break;}while(1);}
