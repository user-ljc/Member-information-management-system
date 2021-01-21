#include<stdio.h>
#include<stdlib.h>
#include<string.h>
# define N 5
struct member     //学生抽象类型
{
	char name[20];
	char tel [20];
	char kind[20];
	int balance;
};
struct Node    //创建链表
{
	struct member date;
	struct Node* next;
};
struct Node* createList()   //创建表头
{
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	headNode->next=NULL;
	return headNode;
}
struct Node* createNode(struct member date)   //创建节点
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->date=date;
	newNode->next=NULL;
	return newNode;
}
void savedata(struct Node* head)   //存档
{
	FILE *fp=fopen("D:\\book.text","w");
	head=head->next;
	while(head)
	{
		fwrite(&head->date,sizeof(head->date),1,fp);
		head=head->next;
	}
	fclose(fp);
}
void initdata(struct Node* head)   //读档
{
	FILE* fp=fopen("D:\\book.text","rt");
	struct Node* temp=head;
	struct Node* p=(struct Node*)malloc(sizeof(struct Node));
	while(fread(&p->date,sizeof(p->date),1,fp))
	{
		temp->next=p;
		p->next=NULL;
		temp=temp=temp->next;
		p=(struct Node*)malloc(sizeof(struct Node));
	}
	free(p);
	fclose(fp);
}

void insertNode(struct Node* headNode, struct member date)  //插入节点
{
    struct Node* newNode = createNode(date);
	newNode->next=headNode->next;
	headNode->next=newNode;
}
void deleteNode(struct Node* headNode,char* name) //删除节点
{
	struct Node* posNode = headNode->next;
	struct Node* posFrontNode = headNode;
	if(posNode == NULL)
	{
		printf("数据为空，无法删除！\n");
		return;
	}
	while(strcmp(posNode->date.name,name))
	{
		posFrontNode = posNode;
		posNode = posFrontNode->next;
		if(posNode == NULL)
		{
			printf("未找到制定删除位置无法删除");
			return;
		}
	}
	posFrontNode->next = posNode->next;
	free(posNode);
}
struct Node* searchName(struct Node* headNode,char*name) // 姓名查找
{
	struct Node* pMove = headNode->next;
	if(pMove == NULL)
	{
		return NULL;
	}
	while (strcmp(pMove->date.name,name))
	{
		pMove = pMove->next;
		if(pMove==NULL)
		{
			return NULL;
		}
	}
	return pMove;
}
struct Node* searchTel(struct Node* headNode,char*tel) // 姓名电话
{
	struct Node* pMove = headNode->next;
	if(pMove == NULL)
	{
		return NULL;
	}
	while (strcmp(pMove->date.tel,tel))
	{
		pMove = pMove->next;
		if(pMove==NULL)
		{
			return NULL;
		}
	}
	return pMove;
}
void printfList(struct Node* headNode)  //打印链表
{
	struct Node* pMove = headNode->next;
	printf("姓名\t电话\t\t类别\t余额\n");
	while(pMove)
	{
		printf("%s\t%-13s\t%s\t%d\n",pMove->date.name,pMove->date.tel,pMove->date.kind,pMove->date.balance);
		pMove = pMove->next;
	}
	printf("\n");

}
int countList(struct Node* headNode);
void swap(struct Node* fristNode,struct Node* secondNode)//交换
{
	struct Node* swapNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(swapNode->date.name,fristNode->date.name);
	strcpy(swapNode->date.tel,fristNode->date.tel);
	strcpy(swapNode->date.kind,fristNode->date.kind);
	swapNode->date.balance = fristNode->date.balance;

	strcpy(fristNode->date.name,secondNode->date.name);
	strcpy(fristNode->date.tel,secondNode->date.tel);
	strcpy(fristNode->date.kind,secondNode->date.kind);
	fristNode->date.balance=secondNode->date.balance;

	strcpy(secondNode->date.name,swapNode->date.name);
	strcpy(secondNode->date.tel,swapNode->date.tel);
	strcpy(secondNode->date.kind,swapNode->date.kind);
	secondNode->date.balance = swapNode->date.balance;
}
void sortList(struct Node* headNode) //冒泡函数
{
	int j=0;
	int i=countList(headNode);
	struct Node* pMove = headNode->next;
	while(j<i)
	{
		while(pMove->next)
		{
			if(pMove->date.balance > pMove->next->date.balance)
			{
				swap(pMove,pMove->next);
			}
			pMove = pMove->next;
		}
		pMove = headNode->next;
		j++;
	}
}
void sortListTwo(struct Node* headNode) //交换法排序
{
	struct Node* pMove = headNode->next;
	struct Node* sMove;
	while(pMove!=NULL)
	{
		sMove=pMove;
		while(sMove!=NULL)
		{
			if(pMove->date.balance<sMove->date.balance)
			{
				swap(pMove,sMove);
			}
			sMove=sMove->next;
		}
		pMove=pMove->next;
	}
}
int countList(struct Node* headNode)  //数链表
{
	int i=0;
	struct Node* pMove = headNode->next;
	while(pMove)
	{
		i++;
		pMove = pMove->next;
	}
	return i;
}
int seekList(struct Node* headNode,char* kind)  //查找
{
	int i=0;
	struct Node* pMove = headNode->next;
	printf("\n姓名\t电话\t\t类别\t余额\n");
	while(pMove)
	{
		if(strcmp(pMove->date.kind,kind)==0)
		{
			i++;
			printf("%s\t%-13s\t%s\t%d\n",pMove->date.name,pMove->date.tel,pMove->date.kind,pMove->date.balance);
		}
		pMove = pMove->next;
	}
	printf("\n");
	return i;
}
void deleteList(struct Node* headNode) //整表删除
{
	struct Node* pMove = headNode->next;
	struct Node* sMove;
	while(pMove)
	{
		sMove = pMove->next;
		free(pMove);
		pMove=sMove;
	}
	headNode->next = NULL;
}
void menu()      //建立菜单
{
	printf("\n---------------【会员管理系统】---------------\n\n");
	printf("\t\t0.录入会员信息\n\n");
	printf("\t\t1.删除会员信息\n\n");
	printf("\t\t2.修改会员信息\n\n");
	printf("\t\t3.查询会员信息\n\n");
	printf("\t\t4.排序会员信息\n\n");
	printf("\t\t5.显示会员信息\n\n");
	printf("\t\t6.退出管理系统\n\n");
	printf("----------------------------------------------\n\n");
}
void menuOne()
{
	printf("\n---------------【查询会员信息】---------------\n\n");
    printf("\t\t0.通过姓名查找\n\n");
	printf("\t\t1.通过电话查找\n\n");
	printf("\t\t2.通过会员等级查找\n\n");
	printf("\t\t3.退出查找\n\n");
}
void menuTwo()
{
	printf("\n---------------【排序会员信息】---------------\n\n");
	printf("\t\t0.按照升序排列\n\n");
	printf("\t\t1.按照降序排列\n\n");
	printf("\t\t2.结束排序功能\n\n");
}
struct Node* list;
struct Node* node;
void keyDown()    //选择菜单项
{ 
	char name;
	char key;
	struct member date;
	int choice = 0;
a:	printf("请输入所选功能 ");
	fflush(stdin);
	scanf("%d",&choice); //输入所选的选项
	while(1)
	{
		if(choice<0||choice>6)//处理错误信息
		{
		    system("cls");
			menu();
			printf("输入错误！您输入的是 %d\n",choice);
			printf("请输入正确的选项 (标号:0 - 6)");
			fflush(stdin);
			scanf("%d",&choice);
		}else{
			system("cls");
			menu();
			break;
		}
	}
	switch (choice)
	{
	case 0:
		system("cls");
		printf("您选择的功能是%d\n",choice);
		printf("\n---------------【录入会员信息】---------------\n\n");
		if(countList(list)<N)
		{
			while(1)
			{
				if(countList(list)<N)
				{
					printf("请输入....\n会员名 电话 类别 余额：");
					printf("  会员等级（ 钻石 铂金 VIP 普通）\n");
					fflush(stdin);
					scanf("%s%s%s%d",&date.name,&date.tel,&date.kind,&date.balance);

				}else
				{
					printf("******************链表已满！******************");
					break;
				}
				if(searchName(list,date.name)==NULL&&searchTel(list,date.tel)==NULL)
				{
					insertNode(list,date);
					printf("\n\t是否重新输入?\t是 y / 否 n :\t");
					fflush(stdin);
					scanf("%s",&key);
						if(key=='y')
					{
						continue;
					}else
					{
						break;
					}
				}
				else if(searchName(list,date.name)!=NULL)
				{
					printf("\n\t姓名重复请重新输入！\n");
					printf("\t是否继续输入？  是 y / 否 n :\t");
					fflush(stdin);
					scanf("%s",&key);
					if(key=='y')
					{
						continue;
					}else
					{
						break;
					}				
				}
				else if(searchTel(list,date.tel)!=NULL)
				{
					printf("\n\t电话重复请重新输入！\n");
					printf("\t是否继续输入？  是 y / 否 n :\t");
					fflush(stdin);
					scanf("%s",&key);
					if(key=='y')
					{
						continue;
					}else
					{
						break;
					}
				}
				else
				{
				if(key=='n')
				break;
				}
			}

	}else{
		printf("*******************链表已满！*******************");
		break;
	}
	  savedata(list);
				break;
	case 1:while(1)
		   {
				int choice = 0;
				system("cls");
				printf("\n---------------【删除会员信息】---------------\n\n");
				printf("\t\t0.删除单个会员信息\n\n");
				printf("\t\t1.删除全部会员信息\n\n");
				printf("\t\t2.结束删除功能\n\n");
				printf("请输入所选功能 ");
				fflush(stdin);
				scanf("%d",&choice);
				switch(choice) 
				{
				case 0:
					while(1)
					   {
							system("cls");
							printf("\n---------------【删除会员信息】---------------\n\n");
							fflush(stdin);
							printf("\n请输入被删除人姓名 ");
							scanf("%s",&date.name);
							if(searchName(list,date.name)==NULL)
							{
								printf("\n\t错误！！！！没有到此人！\n");
							}	
							else
							{
								searchName(list,date.name);
								printf("\n姓名\t电话\t\t类别\t余额\n");
								printf("%s\t%-13s\t%s\t%d\n",searchName(list,date.name)->date.name,searchName(list,date.name)->date.tel,searchName(list,date.name)->date.kind,searchName(list,date.name)->date.balance);
								printf("\n确认删除此人？  是 y / 否 n \t");
								fflush(stdin);
								scanf("%s",&key);
								if(key=='y')
								{
									deleteNode(list,date.name);
								}
							}
							printf("\n\t是否继续删除？  \n\t是 y / 否 n \t");
							fflush(stdin);
							scanf("%s",&key);
							if(key=='y')
							{
								continue;
							}else
							{
								break;
							}
					}
							break;
					case 1:
						system("cls");
						printf("\n---------------【删除会员信息】---------------\n\n");
						deleteList(list);
						printf("\n\t****已删除全部信息!****\n\n");
						break;
					case 2:
						system("cls");
						menu();
						goto a;
						break;
					}
				break;
			   }
		savedata(list);
		break;
	case 2:
		while(1)
		{
			system("cls");
			printf("\n---------------【修改会员信息】---------------\n\n");
			printfList(list);
			printf("请输入需要修改信息的\n\t会员名: ");
			scanf("%s",date.name);
			if(searchName(list,date.name)==NULL)
			{
				printf("\n\t***没有查询到此人!!!***\n");
				printf("\n是否继续查找？ \t是 y / 否 n \t");
				scanf("%s",&key);
				if(key=='y')
				{
					continue;
				}
				else
				{
					break;
				}
			}
			else
			{
				searchName(list,date.name);
				printf("\n已找到目标信息\n");
				printf("\t姓名\t电话\t\t类别\t余额\n");
				printf("\t%s\t%-13s\t%s\t%d\n",searchName(list,date.name)->date.name,searchName(list,date.name)->date.tel,searchName(list,date.name)->date.kind,searchName(list,date.name)->date.balance);
				printf("\n请选择需要修改的数据。。。。。。。");
				printf("\n\t\t0.修改姓名\n\n");
				printf("\t\t1.修改电话\n\n");
				printf("\t\t2.修改会员等级\n\n");
				printf("\t\t3.修改会余额\n\n");
				printf("\t\t4.重新输入\n\n");
				scanf("%d",&choice);
				switch(choice)
				{
					case 0:
						printf("\n请输入修改后的数据 姓名 ");
						scanf("%s",&searchName(list,date.name)->date.name);
						break;
					case 1:
						printf("\n请输入修改后的数据 电话 ");
						scanf("%s",&searchName(list,date.name)->date.tel);
						break;
					case 2:
						printf("\n请输入修改后的数据 会员等级 ");
						printf("\n会员等级 (钻石 铂金 VIP 普通）\n");
						scanf("%s",&searchName(list,date.name)->date.kind);
						break;
					case 3:
						printf("\n请输入修改后的数据姓名 ");
						scanf("%d",&searchName(list,date.name)->date.balance);
						break;
					case 4:
						printf("\n请输入修改后的数据....\n\t姓名\t电话\t\t类别\t余额\n");
						printf("\t");
			      		fflush(stdin);
						scanf("%s%s%s%d",&searchName(list,date.name)->date.name,&searchName(list,date.name)->date.tel,&searchName(list,date.name)->date.kind,&searchName(list,date.name)->date.balance);
						printf("修改完成！");
						break;
				}
				printf("\n是否继续修改？ \t是 y / 否 n \t");
				scanf("%s",&key);
				if(key=='y')
				{
					continue;
				}
				else
				{
					break;
				}
			}
		}
		savedata(list);
		break;
	case 3:while(1)
		   {
			system("cls");
			menuOne();
			printf("请输入所选功能 ");
			fflush(stdin);
			scanf("%d",&choice); //输入所选的选项
			if(choice<0||choice>3)//处理错误信息
			{
					system("cls");
					menuOne();
					printf("输入错误！您输入的是 %d\n",choice);
					printf("请输入正确的选项 (标号:0 - 3)");
					fflush(stdin);
					scanf("%d",&choice);
			}
			else
			{
				system("cls");
				switch(choice)
				{
					case 0:
						while(1)
						{
							system("cls");
							printf("\n***************您选择的是按照姓名查找**************\n");
							printf("\n请输入您想查找会员的\n姓名\t");
							fflush(stdin);
							scanf("%s",&date.name);
							if(searchName(list,date.name)==NULL)
							{
								printf("\n没有查询到结果！");
								printf("是否继续查找？ \t是 y / 否 n \t");
								scanf("%s",&key);
									if(key=='y')
									{
										continue;
									}else
									{
										break;
									}
							}
							else
							{
								searchName(list,date.name);
								printf("\n姓名\t电话\t\t类别\t余额\n");
								printf("%s\t%-13s\t%s\t%d\n",searchName(list,date.name)->date.name,searchName(list,date.name)->date.tel,searchName(list,date.name)->date.kind,searchName(list,date.name)->date.balance);
								fflush(stdin);
								printf("\n是否继续查找？ \t是 y / 否 n \t");
								scanf("%s",&key);
									if(key=='y')
									{
										continue;
									}else
									{
										break;
									}
							}
						}
						break;
					case 1:
						while(1){
							system("cls");
							printf("\n***************您选择的是按照电话查找**************\n");
							printf("\n请输入您想查找会员的\n电话\t");
								fflush(stdin);
								scanf("%s",&date.tel);
								if(searchTel(list,date.tel)==NULL)
								{
									printf("\n没有查询到结果！");
									printf("是否继续查找？ \t是 y / 否 n \t");
									scanf("%s",&key);
										if(key=='y')
										{
											continue;
										}else
										{
											break;
										}
								}
								else
								{
									searchTel(list,date.tel);
									printf("\n姓名\t电话\t\t类别\t余额\n");
									printf("%s\t%-13s\t%s\t%d\n",searchTel(list,date.tel)->date.name,searchTel(list,date.tel)->date.tel,searchTel(list,date.tel)->date.kind,searchTel(list,date.tel)->date.balance);
									fflush(stdin);
									printf("\n是否继续查找？ \t是 y / 否 n \t");
									scanf("%s",&key);
										if(key=='y')
										{
											continue;
										}else
										{
											break;
										}
								}
						}
						break;
					case 2:
						while(1){
							system("cls");
							printf("\n***************您选择的是按照会员等级查找**************\n");
							printf("请输入您想查找会员的\n等级:\t");
							fflush(stdin);
							scanf("%s",&date.kind);
							if(seekList(list,date.kind)==0)
							{
								printf("\n\t查询结果为空！！！！！！\n\n");
							}
							printf("**************************查找完毕***********************");
							printf("\n是否继续查找？\t是 y / 否 n \t");
							scanf("%s",&key);
							if(key=='y')
							{
								continue;
							}else
							{
							 break;
							}
						}
						break;
					case 3:
						system("cls");
						menu();
						goto a;
				}
			}
		  }
      break;
	case 4:
		while(1)
		{
			system("cls");
			menuTwo();
			printf("请输入选择的功能 ");
			scanf("%d",&choice);
			if(choice<0||choice>2)//处理错误信息
			{	
				system("cls");
				menuTwo();
				printf("输入错误！您输入的是 %d\n",choice);
				printf("请输入正确的选项 (标号:0 - 2) ");
				fflush(stdin);
				scanf("%d",&choice);
			}
			else{
				switch(choice)
				{
					case 0:
						system("cls");
						printf("升序查找结果如下\n\n");
						sortList(list);
						printfList(list);
						system("pause");
						break;
					case 1:
						system("cls");
						printf("降序查找结果如下\n\n");
						sortListTwo(list);
						printfList(list);
						system("pause");
						break;
					case 2:
						system("cls");
						menu();
						goto a;
				}
			}
		}
    case 5:system("cls");
		printf("\n---------------【显示会员信息】---------------\n\n");
	    printfList(list);
		savedata(list);
		break;
	case 6:
		savedata(list);
		exit(0);
	};
}
void main()
{
	list = createList();
	initdata(list);
	while(1)
	{   
		menu();
		keyDown();
		system("pause");
		system("cls");
	}
	return 0;
}