#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#define MAX 100
#define MAX_NAME 10
#define MAX_SEX 4
#define MAX_TELE 12
#define MAX_ADDRESS 30

//定义结构体
//姓名 性别 年龄 电话 地址
struct TXL
{
	char name[MAX_NAME];
	char sex[MAX_SEX];
	int  age;
	char tele[MAX_TELE];
	char address[MAX_ADDRESS];
}contacts[MAX];

//定义全局变量
int count=0;
int t=0;
int iscls=1;

//定义函数声明
char *s_gets(char *st,int n);
void showmenu(void);
void add(void);
void show(void);
void menu_search(void);
int  name_search(void);
int  tele_search(void);
void search(void);
void change(void);
void dele(void);
void cls(void);
void save(void);

//主函数main
int main()
{
	int button;
	FILE *fp;
	//打开文件
	if((fp=fopen("contacts","ab+"))==NULL)
	{
		printf("无法打文件！\n");
		exit(1);
	}
	//读取文件内容，得出count的值
	while(!feof(fp))
	{
		while(fread(&contacts[count],sizeof(struct TXL),1,fp))
			count++;
	}
	fclose(fp);//关闭文件
	while(1)
	{
		showmenu();
		scanf("%d",&button);
		fflush(stdin);
		switch(button)
		{
		case 1:
			add();
			break;
		case 2:
			show();
			break;
		case 3:
			iscls=1;
			search();
			break;
		case 4:
			iscls=0;
			change();
			break;
		case 5:
			iscls=0;
			dele();
			break;
		case 6:
			cls();
			break;
		case 7:
			save();
			break;
		case 0:
			printf("欢迎下次使用！");
			exit(0);
		default :
			printf("输入错误！\n");
			system("pause");
			system("cls");
		}
	}
}

//自定义输入函数
char *s_gets(char *st,int n)
{
	char *ret_val;
	char *find;
	ret_val=fgets(st,n,stdin);
	if(ret_val)
	{
		//查找换行符
		find=strchr(st,'\n');
		if(find)//如果地址不是NULL
			*find='\0';//在此处放置一个空字符
		else
			while(getchar()!='\n')
				continue;
	}
	return ret_val;
}

//显示菜单
void showmenu()
{
	printf("\n\n\n");
	printf("\t\t ____________________\n");
	printf("\t\t|                    |\n");
	printf("\t\t|   1、增加联系人    |\n");
	printf("\t\t|   2、显示联系人    |\n");
	printf("\t\t|   3、查找联系人    |\n");
	printf("\t\t|   4、修改联系人    |\n");
	printf("\t\t|   5、删除联系人    |\n");
	printf("\t\t|   6、清空联系人    |\n");
	printf("\t\t|   7、保存联系人    |\n");
	printf("\t\t|   0、退出系统      |\n");
	printf("\t\t|____________________|\n");
	printf("\t\t   请输入0~7：");
}

//1、增加联系人
void add()
{
	printf("\n");
	printf("请输入姓名：");
	s_gets(contacts[count].name,MAX_NAME);
	printf("请输入性别：");
	s_gets(contacts[count].sex,MAX_SEX);
	printf("请输入年龄：");
	scanf("%d",&contacts[count].age);
	fflush(stdin);
	printf("请输入电话：");
	s_gets(contacts[count].tele,MAX_TELE);
	printf("请输入地址：");
	s_gets(contacts[count].address,MAX_ADDRESS);
	count++;
	printf("添加成功!\n");
	system("pause");
	system("cls");
}

//2、显示联系人
void show()
{
	int i;
	if(!count)
	{
		printf("联系人为空！\n");
		system("pause");
		system("cls");
		return;
	}
	printf("________________________________________________\n\n");
	printf("姓名  性别 年龄   电话         地址\n");
	for(i=0;i<count;i++)
	{
		printf("%-6s %-2s   %-2d %-10s %-20s\n",contacts[i].name,
		contacts[i].sex,contacts[i].age,contacts[i].tele,
		contacts[i].address);
	}
	printf("________________________________________________\n");
	system("pause");
	system("cls");
}

//3、查找联系人
void menu_search()
{
	printf("\n\n\n");
	printf("\t\t ____________________\n");
	printf("\t\t|                    |\n");
	printf("\t\t|    0、退出界面     |\n");
	printf("\t\t|                    |\n");
	printf("\t\t|    1、姓名查询     |\n");
	printf("\t\t|                    |\n");
	printf("\t\t|    2、电话查询     |\n");
	printf("\t\t|____________________|\n");
	printf("\t\t  请输入0~2：");
}

//按名字查询
int name_search()
{
	char search_name[MAX_NAME];
	int i;
	printf("请输入待查询姓名：");
	s_gets(search_name,MAX_NAME);
	for(i=0;i<count;i++)
	{
		if(strcmp(search_name,contacts[i].name)==0)
		{
			printf("查询成功！\n\n");
			printf("________________________________________________\n");
			printf("姓名  性别 年龄   电话         地址\n");
			printf("%-6s %-2s   %-2d %-10s %-20s\n",contacts[i].name,
			contacts[i].sex,contacts[i].age,contacts[i].tele,
			contacts[i].address);
			printf("________________________________________________\n");
			t=i;
			if(iscls)
			{
				system("pause");
				system("cls");
			}
			return 1;
		}
	}
	printf("查无此人！\n");
	if(iscls)
	{
		system("pause");
		system("cls");
	}
	return 0;
}

//按电话查询
int tele_search()
{
	char search_tele[MAX_TELE];
	int i;
	printf("请输入待查询电话：");
	s_gets(search_tele,MAX_TELE);
	for(i=0;i<count;i++)
	{
		if(strcmp(search_tele,contacts[i].tele)==0)
		{
			printf("查询成功！\n\n");
			printf("________________________________________________\n");
			printf("姓名  性别 年龄   电话         地址\n");
			printf("%-6s %-2s   %-2d %-10s %-20s\n",contacts[i].name,
			contacts[i].sex,contacts[i].age,contacts[i].tele,
			contacts[i].address);
			printf("________________________________________________\n");
			t=i;
			if(iscls)
			{
				system("pause");
				system("cls");
			}
			return 1;
		}
	}
	printf("查无此人！\n");
	if(iscls)
	{
		system("pause");
		system("cls");
	}
	return 0;
}

//查询函数
void search()
{
	int search_button;
	printf("正在进入查询界面。\n");
	system("pause");
	system("cls");
	while(1)
	{
		menu_search();
		scanf("%d",&search_button);
		while(getchar()!='\n')
			continue;
		switch(search_button)
		{
		case 0:
			printf("正在退出查询界面。\n");
			system("pause");
			system("cls");
			return;
		case 1:
			name_search();
			break;
		case 2:
			tele_search();
			break;
		default:
			printf("请输入0~2的数字！\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

//4、修改联系人
void change(void)
{
	int search=0;
	printf("请选择你要查询的方式（1--姓名，2--电话）：");
	scanf("%d",&search);
	while(getchar()!='\n')
		continue;
	if(search==1)
	{
		if(name_search())
		{
			printf("请输入姓名：");
			s_gets(contacts[t].name,MAX_NAME);
			printf("请输入性别：");
			s_gets(contacts[t].sex,MAX_SEX);
			printf("请输入年龄：");
			scanf("%d",&contacts[t].age);
			fflush(stdin);
			printf("请输入电话：");
			s_gets(contacts[t].tele,MAX_TELE);
			printf("请输入地址：");
			s_gets(contacts[t].address,MAX_ADDRESS);
			printf("修改成功！\n");
			system("pause");
			system("cls");
			return;
		}
		else 
			system("pause");
			system("cls");
			return;
	}
	if(search==2)
	{
		if(tele_search())
		{
			printf("请输入姓名：");
			s_gets(contacts[t].name,MAX_NAME);
			printf("请输入性别：");
			s_gets(contacts[t].sex,MAX_SEX);
			printf("请输入年龄：");
			scanf("%d",&contacts[t].age);
			fflush(stdin);
			printf("请输入电话：");
			s_gets(contacts[t].tele,MAX_TELE);
			printf("请输入地址：");
			s_gets(contacts[t].address,MAX_ADDRESS);
			printf("修改成功！\n");
			system("pause");
			system("cls");
			return;
		}
		else 
			system("pause");
			system("cls");
			return;
	}
	else 
		printf("输入错误！");
	system("pause");
	system("cls");
}

//5、删除联系人
void dele()
{
	int i;
	int search=0;
	printf("请选择你要查询的方式（1--姓名，2--电话）：");
	scanf("%d",&search);
	while(getchar()!='\n')
		continue;
	if(search==1)
	{
		if(name_search())
		{
			for(i=t;i<count;i++)
				contacts[i]=contacts[i+1];
			count--;
			printf("\n成功删除联系人！\n");
		}
	}
	if(search==2)
	{
		if(tele_search())
		{
			for(i=t;i<count;i++)
				contacts[i]=contacts[i+1];
			count--;
			printf("\n成功删除联系人！\n");
		}
	}
	system("pause");
	system("cls");
}

//6、清空联系人
void cls()
{
	FILE *fp;
	if((fp=fopen("contacts","w+"))==NULL)
	{
		printf("无法打开文件！\n");
		exit(1);
	}
	printf("清空成功！\n");
	fclose(fp);
	count=0;
	system("pause");
	system("cls");

}

//7、保存联系人
void save()
{
	FILE *fp;
	int i;
	if((fp=fopen("contacts","wb"))==NULL)
	{
		printf("无法打文件！\n");
		exit(1);
	}
	for(i=0;i<count;i++)
		if(fwrite(&contacts[i],sizeof(struct TXL),1,fp)!=1)
			printf("写入文件失败！\n");
	fclose(fp);
	printf("保存成功！\n");
	system("pause");
	system("cls");
}
