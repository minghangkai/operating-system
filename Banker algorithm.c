#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100//���κ��������ڵ���MAX�Ĵ�С
int resource_num,progress_num;//ǰ������Դ�������߱�ʾ������
int need[MAX][MAX];//P[i]����j����Դ������
int avalable[MAX];//ĳ����Դ�Ŀ�����
int max[MAX][MAX];//P[i]����Դj������������
int allocate[MAX][MAX]= {0}; //p[i]��j����Դ�ѷ������Դ��
int finish[MAX]= {0}; //P[i]�����Ƿ�ִ�н���
int request[MAX][MAX]={0};//���̶�ĳ����Դ��������
int flag[MAX]= {0};//P[i]�����Ƿ��Ѿ�����ȫ��������Դ
int s[MAX]={0};//��¼��ȫ��������
int numberOfFinish=0;//����ɵĽ�����

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
            if (finish[i]==0&&need[i][j] <= work[j])//�ж��Ƿ��ܹ�������Ҫ�ĸ�����Դ
			{
				count1++;
				//printf("c=%d ",count1);
			}
		}
        if (count1 == resource_num)//��������
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
    printf("������%d�����̵ģ�\n������\t\t��һ�ε���������\n",progress_num);
    printf("\t\t\t");
    for(i=0,c='A';i<resource_num;i++,c++)
    {
        printf("%c ",c);
    }
    printf("\n");
    for(k=0;k<progress_num;k++)
    {
        printf("����p[%d]\t\t",k);
        for(j=0;j<resource_num;j++)
        {
            scanf("%d",&request[k][j]);
            if(request[k][j]>need[k][j]||request[k][j]>avalable[j])
            {
                printf("����ʧ�ܣ��������������p[%d]��������",k);
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
				printf("����ɹ�����ȫ����Ϊ��");
				for(i=0,l=0;i<progress_num-1;i++,l++)
				{
					printf("p[%d]-->",s[l]) ;
				}
				printf("p[%d]\n",s[l]) ;
    	}
        else
		{
				printf("�ް�ȫ���У����벻�ɹ���\n");
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
    printf("��������Դ���ࣺ");
    scanf("%d",&resource_num);
    printf("�������������");
    scanf("%d",&progress_num);
    printf("������%d����Դ��ʼ������Դ����",resource_num);
    for(i=0;i<resource_num;i++)
    {
        finish[i]=0;
		scanf("%d",&avalable[i]);
    }
    printf("������%d�����̵ģ�\n������\t\t�����������\n",progress_num);
    printf("\t\t\t");
    for(i=0,c='A';i<resource_num;i++,c++)
    {
        printf("%c ",c);
    }
    printf("\n");
    for(i=0;i<progress_num;i++)
    {
        printf("����p[%d]\t\t",i);
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
	printf("������\t\t���������\t��������\t�ѷ�����\tִ�н�����\n");
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
        printf("����p[%d]\t",i);
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
	printf("ʣ����Դ����\t");
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
	printf("\n�Ƿ���Ҫ��������Դ�� ��Y/N����");
	//c=getchar();
	getchar();
	scanf("%c",&c);
	if(c=='y'||c=='Y')
	{
        return 1;
	}
	else
    {
        printf("������Դ���������");
        return 0;
    }
}

void request_again()
{
	char c='A';
	int a,count1,count2,i,j,k,l;
	printf("��������̱�ţ�1-progress_num):");
	scanf("%d",&i);
	printf("���������p[%d]��%d����Դ������:",i,resource_num);
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
		printf("\n������Դ����������p[%d]������Դ,����p[%d]������ԴΪ��",i,i);
		for(k=0;k<resource_num;k++)
		{
			printf("%d ",need[i][k]);
		}
		printf("\n�������������p[%d]��%d����Դ������:",i,resource_num);
		goto a;
	}
	else
    {
        if(count2!=0)
        {
            //printf("%d",count2);
            printf("\n������Դ������ϵͳ������Դ,ϵͳ������ԴΪ��");
            for(k=0;k<resource_num;k++)
            {
                printf("%d ",avalable[k]);
            }
            printf("\n�������������p[%d]��%d����Դ������:",i,resource_num);
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
                printf("����ɹ�����ȫ����Ϊ��");
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
                printf("�ް�ȫ���У����벻�ɹ���\n");
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


