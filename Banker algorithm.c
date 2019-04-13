#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100//本次宏设置用于调整MAX的大小
int resource_num,progress_num;//前者是资源数，后者表示进程数
int need[MAX][MAX];//P[i]尚需j类资源的数量
int avalable[MAX];//某类资源的可用量
int max[MAX][MAX];//P[i]对资源j类的最大需求量
int allocate[MAX][MAX]= {0}; //p[i]在j类资源已分配的资源量
int finish[MAX]= {0}; //P[i]进程是否执行结束
int request[MAX][MAX]={0};//进程对某类资源的申请量
int flag[MAX]= {0};//P[i]进程是否已经满足全部所需资源
int s[MAX]={0};//记录安全序列数组
int numberOfFinish=0;//已完成的进程数

int safe()
{
	int i, j, k=0, work[MAX], count1;
	for (j = 0; j < resource_num; j++)
	{
		work[j] = avalable[j];
		//printf("%d\t",work[j]);
	}
	for (i = 0; i < progress_num; i++)
	{
		count1 = 0;
		for (j = 0; j < resource_num; j++)
		{
			//printf("work[%d]=%d \t",j,work[j]);
            if (finish[i]==0&&need[i][j] <= work[j])//判断是否能够满足需要的各种资源
			{
				count1++;
				//printf("c=%d ",count1);
			}
		}
        if (count1 == resource_num)//若满足则
        {
            //printf("%d",count);
            for(j = 0; j < resource_num; j++)
            {
                //printf("work[%d]=%d \t",j,work[j]);
                if(flag[i]==1)
                    break;
                else
                    work[j] += allocate[i][j];
                //printf("work[%d]=%d \t",j,work[j]);
            }
            finish[i] = 1;
            //printf("%d ",finish[i]);
            s[k] = i;

            k++;
            i=-1;
            //printf("%d ",s[k]);
        }
       printf("%d ",i);
	}
	printf("\n");
	for(k=0;k<progress_num;k++)
    {
        printf("s[%d]=%d ",k,s[k]);
    }
	printf("\n");
	for (i = 0; i < progress_num; i++)
	{
		if (finish[i] == 0)
		{
			return 0;
		}
	}
	return 1;
}

void first_request()
{
    char c;
    int a,i,j,k,l;
    printf("请输入%d个进程的：\n进程名\t\t第一次的申请量：\n",progress_num);
    printf("\t\t\t");
    for(i=0,c='A';i<resource_num;i++,c++)
    {
        printf("%c ",c);
    }
    printf("\n");
    for(k=0;k<progress_num;k++)
    {
        printf("进程p[%d]\t\t",k);
        for(j=0;j<resource_num;j++)
        {
            scanf("%d",&request[k][j]);
            if(request[k][j]>need[k][j]||request[k][j]>avalable[j])
            {
                printf("申请失败！请重新输入进程p[%d]的申请量",k);
                return;
            }
            need[k][j]-=request[k][j];
            avalable[j]-=request[k][j];
            allocate[k][j]+=request[k][j];
        }
        a=safe();
        for(i=0;i<progress_num;i++)
        {
            finish[i]=0;
        }
		if( a )
    	{
            	//printf("%d",a);
				printf("申请成功！安全序列为：");
				for(i=0,l=0;i<progress_num-1;i++,l++)
				{
					printf("p[%d]-->",s[l]) ;
				}
				printf("p[%d]\n",s[l]) ;
    	}
        else
		{
				printf("无安全序列，申请不成功！\n");
				need[k][j]+=request[k][j];
            	avalable[j]+=request[k][j];
            	allocate[k][j]-=request[k][j];
		}
    }
    printf("\n");
    situation();
}

void input()
{
    char c;
    int i,j;
    printf("请输入资源种类：");
    scanf("%d",&resource_num);
    printf("请输入进程数：");
    scanf("%d",&progress_num);
    printf("请输入%d类资源初始化的资源数：",resource_num);
    for(i=0;i<resource_num;i++)
    {
        finish[i]=0;
		scanf("%d",&avalable[i]);
    }
    printf("请输入%d个进程的：\n进程名\t\t最大需求量：\n",progress_num);
    printf("\t\t\t");
    for(i=0,c='A';i<resource_num;i++,c++)
    {
        printf("%c ",c);
    }
    printf("\n");
    for(i=0;i<progress_num;i++)
    {
        printf("进程p[%d]\t\t",i);
        for(j=0;j<resource_num;j++)
        {
            scanf("%d",&max[i][j]);
            need[i][j]=max[i][j];
        }
    }
}

void situation()
{
    char c;
    int i,j,k;
	printf("进程名\t\t最大需求量\t尚需求量\t已分配量\t执行结束否\n");
	printf("\t\t");
	for(k=0;k<resource_num;k++)
	{
		for(i=0,c='A';i<resource_num;i++,c++)
    	{
        	printf("%c ",c);
    	}
    	printf("\t\t");
	}
	printf("\n");
	for(i=0;i<progress_num;i++)
	{
        printf("进程p[%d]\t",i);
        for(j=0;j<resource_num;j++)
        {
            printf("%d ",max[i][j]);
        }
        printf("\t\t");
        for(j=0;j<resource_num;j++)
        {
            printf("%d ",need[i][j]);
        }
        printf("\t\t");
        for(j=0;j<resource_num;j++)
        {
            printf("%d ",allocate[i][j]);
        }
        printf("\t\t");
        if(flag[i]==1)
        {
            printf("finished\n");
        }
        else
        {
            printf("working\n");
        }
	}
	printf("剩余资源数：\t");
	for(j=0;j<resource_num;j++)
	{
		printf("%d ",avalable[j]);
	}
	printf("\n");
}

int requestornot()
{
    char c;
    //situation();
	printf("\n是否需要再申请资源？ （Y/N）：");
	//c=getchar();
	getchar();
	scanf("%c",&c);
	if(c=='y'||c=='Y')
	{
        return 1;
	}
	else
    {
        printf("进程资源分配结束！");
        return 0;
    }
}

void request_again()
{
	char c='A';
	int a,count1,count2,i,j,k,l;
	printf("请输入进程编号（1-progress_num):");
	scanf("%d",&i);
	printf("请输入进程p[%d]对%d类资源的申请:",i,resource_num);
	a:for(j=0,count1=0,count2=0;j<resource_num;j++)
	{
		scanf("%d",&request[i][j]);
		if(request[i][j]>need[i][j])
        {
            //printf("%d",count1);
            count1++;
        }
        if(request[i][j]>avalable[j])
        {
            //printf("%d",count2);
            count2++;
        }
	}
	if(count1!=0)
	{
		printf("%d",count1);
		printf("\n申请资源数超过进程p[%d]现需资源,进程p[%d]现需资源为：",i,i);
		for(k=0;k<resource_num;k++)
		{
			printf("%d ",need[i][k]);
		}
		printf("\n请重新输入进程p[%d]对%d类资源的申请:",i,resource_num);
		goto a;
	}
	else
    {
        if(count2!=0)
        {
            //printf("%d",count2);
            printf("\n申请资源数超过系统可用资源,系统可用资源为：");
            for(k=0;k<resource_num;k++)
            {
                printf("%d ",avalable[k]);
            }
            printf("\n请重新输入进程p[%d]对%d类资源的申请:",i,resource_num);
            goto a;
        }
        else
        {
            for(j=0;j<resource_num;j++)
            {
                need[i][j]-=request[i][j];
                avalable[j]-=request[i][j];
                printf("%d ",avalable[j]);
                allocate[i][j]+=request[i][j];
            }
            printf("\n");
            for(l=0;l<progress_num;l++)
            {
                printf("%d ",finish[l]);
            }
            printf("\n");
            a=safe();
            for(l=0;l<progress_num;l++)
            {
                printf("%d ",finish[l]);
                finish[l]=0;
            }
            if(a)
            {
                for(j=0,k=0;j<resource_num;j++)
                {
                    k+=need[i][j];
                }
                if(k==0)
                {
                    flag[i]=1;
                    numberOfFinish++;

                    for(j=0;j<resource_num;j++)
                    {
                        avalable[j]+=allocate[i][j];
                    }
                }
                printf("number=%d",numberOfFinish);
                printf("申请成功！安全序列为：");
				for(j=0;j<progress_num-1;j++)
				{
					if(flag[s[j]]==1)
                        continue;
                    else
                        printf("p[%d]-->",s[j]) ;
				}
				printf("p[%d]\n",s[j]) ;
				situation();
            }
            else
            {
                for(j=0;j<resource_num;j++)
                {
                    need[i][j]+=request[i][j];
                    avalable[j]+=request[i][j];
                    allocate[i][j]-=request[i][j];
                }
                printf("无安全序列，申请不成功！\n");
                //situation();
            }
        }
    }
	if(requestornot())
    {
        request_again();
    }
}

void main()
{
    input();
    first_request();
    if(requestornot())
    {
        request_again();
    }
}


