#include<stdio.h>
#include<stdlib.h>
#include<string.h>
# define N 5
struct member     //ѧ����������
{
	char name[20];
	char tel [20];
	char kind[20];
	int balance;
};
struct Node    //��������
{
	struct member date;
	struct Node* next;
};
struct Node* createList()   //������ͷ
{
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	headNode->next=NULL;
	return headNode;
}
struct Node* createNode(struct member date)   //�����ڵ�
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->date=date;
	newNode->next=NULL;
	return newNode;
}
void savedata(struct Node* head)   //�浵
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
void initdata(struct Node* head)   //����
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

void insertNode(struct Node* headNode, struct member date)  //����ڵ�
{
    struct Node* newNode = createNode(date);
	newNode->next=headNode->next;
	headNode->next=newNode;
}
void deleteNode(struct Node* headNode,char* name) //ɾ���ڵ�
{
	struct Node* posNode = headNode->next;
	struct Node* posFrontNode = headNode;
	if(posNode == NULL)
	{
		printf("����Ϊ�գ��޷�ɾ����\n");
		return;
	}
	while(strcmp(posNode->date.name,name))
	{
		posFrontNode = posNode;
		posNode = posFrontNode->next;
		if(posNode == NULL)
		{
			printf("δ�ҵ��ƶ�ɾ��λ���޷�ɾ��");
			return;
		}
	}
	posFrontNode->next = posNode->next;
	free(posNode);
}
struct Node* searchName(struct Node* headNode,char*name) // ��������
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
struct Node* searchTel(struct Node* headNode,char*tel) // �����绰
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
void printfList(struct Node* headNode)  //��ӡ����
{
	struct Node* pMove = headNode->next;
	printf("����\t�绰\t\t���\t���\n");
	while(pMove)
	{
		printf("%s\t%-13s\t%s\t%d\n",pMove->date.name,pMove->date.tel,pMove->date.kind,pMove->date.balance);
		pMove = pMove->next;
	}
	printf("\n");

}
int countList(struct Node* headNode);
void swap(struct Node* fristNode,struct Node* secondNode)//����
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
void sortList(struct Node* headNode) //ð�ݺ���
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
void sortListTwo(struct Node* headNode) //����������
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
int countList(struct Node* headNode)  //������
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
int seekList(struct Node* headNode,char* kind)  //����
{
	int i=0;
	struct Node* pMove = headNode->next;
	printf("\n����\t�绰\t\t���\t���\n");
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
void deleteList(struct Node* headNode) //����ɾ��
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
void menu()      //�����˵�
{
	printf("\n---------------����Ա����ϵͳ��---------------\n\n");
	printf("\t\t0.¼���Ա��Ϣ\n\n");
	printf("\t\t1.ɾ����Ա��Ϣ\n\n");
	printf("\t\t2.�޸Ļ�Ա��Ϣ\n\n");
	printf("\t\t3.��ѯ��Ա��Ϣ\n\n");
	printf("\t\t4.�����Ա��Ϣ\n\n");
	printf("\t\t5.��ʾ��Ա��Ϣ\n\n");
	printf("\t\t6.�˳�����ϵͳ\n\n");
	printf("----------------------------------------------\n\n");
}
void menuOne()
{
	printf("\n---------------����ѯ��Ա��Ϣ��---------------\n\n");
    printf("\t\t0.ͨ����������\n\n");
	printf("\t\t1.ͨ���绰����\n\n");
	printf("\t\t2.ͨ����Ա�ȼ�����\n\n");
	printf("\t\t3.�˳�����\n\n");
}
void menuTwo()
{
	printf("\n---------------�������Ա��Ϣ��---------------\n\n");
	printf("\t\t0.������������\n\n");
	printf("\t\t1.���ս�������\n\n");
	printf("\t\t2.����������\n\n");
}
struct Node* list;
struct Node* node;
void keyDown()    //ѡ��˵���
{ 
	char name;
	char key;
	struct member date;
	int choice = 0;
a:	printf("��������ѡ���� ");
	fflush(stdin);
	scanf("%d",&choice); //������ѡ��ѡ��
	while(1)
	{
		if(choice<0||choice>6)//���������Ϣ
		{
		    system("cls");
			menu();
			printf("���������������� %d\n",choice);
			printf("��������ȷ��ѡ�� (���:0 - 6)");
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
		printf("��ѡ��Ĺ�����%d\n",choice);
		printf("\n---------------��¼���Ա��Ϣ��---------------\n\n");
		if(countList(list)<N)
		{
			while(1)
			{
				if(countList(list)<N)
				{
					printf("������....\n��Ա�� �绰 ��� ��");
					printf("  ��Ա�ȼ��� ��ʯ ���� VIP ��ͨ��\n");
					fflush(stdin);
					scanf("%s%s%s%d",&date.name,&date.tel,&date.kind,&date.balance);

				}else
				{
					printf("******************����������******************");
					break;
				}
				if(searchName(list,date.name)==NULL&&searchTel(list,date.tel)==NULL)
				{
					insertNode(list,date);
					printf("\n\t�Ƿ���������?\t�� y / �� n :\t");
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
					printf("\n\t�����ظ����������룡\n");
					printf("\t�Ƿ�������룿  �� y / �� n :\t");
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
					printf("\n\t�绰�ظ����������룡\n");
					printf("\t�Ƿ�������룿  �� y / �� n :\t");
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
		printf("*******************����������*******************");
		break;
	}
	  savedata(list);
				break;
	case 1:while(1)
		   {
				int choice = 0;
				system("cls");
				printf("\n---------------��ɾ����Ա��Ϣ��---------------\n\n");
				printf("\t\t0.ɾ��������Ա��Ϣ\n\n");
				printf("\t\t1.ɾ��ȫ����Ա��Ϣ\n\n");
				printf("\t\t2.����ɾ������\n\n");
				printf("��������ѡ���� ");
				fflush(stdin);
				scanf("%d",&choice);
				switch(choice) 
				{
				case 0:
					while(1)
					   {
							system("cls");
							printf("\n---------------��ɾ����Ա��Ϣ��---------------\n\n");
							fflush(stdin);
							printf("\n�����뱻ɾ�������� ");
							scanf("%s",&date.name);
							if(searchName(list,date.name)==NULL)
							{
								printf("\n\t���󣡣�����û�е����ˣ�\n");
							}	
							else
							{
								searchName(list,date.name);
								printf("\n����\t�绰\t\t���\t���\n");
								printf("%s\t%-13s\t%s\t%d\n",searchName(list,date.name)->date.name,searchName(list,date.name)->date.tel,searchName(list,date.name)->date.kind,searchName(list,date.name)->date.balance);
								printf("\nȷ��ɾ�����ˣ�  �� y / �� n \t");
								fflush(stdin);
								scanf("%s",&key);
								if(key=='y')
								{
									deleteNode(list,date.name);
								}
							}
							printf("\n\t�Ƿ����ɾ����  \n\t�� y / �� n \t");
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
						printf("\n---------------��ɾ����Ա��Ϣ��---------------\n\n");
						deleteList(list);
						printf("\n\t****��ɾ��ȫ����Ϣ!****\n\n");
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
			printf("\n---------------���޸Ļ�Ա��Ϣ��---------------\n\n");
			printfList(list);
			printf("��������Ҫ�޸���Ϣ��\n\t��Ա��: ");
			scanf("%s",date.name);
			if(searchName(list,date.name)==NULL)
			{
				printf("\n\t***û�в�ѯ������!!!***\n");
				printf("\n�Ƿ�������ң� \t�� y / �� n \t");
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
				printf("\n���ҵ�Ŀ����Ϣ\n");
				printf("\t����\t�绰\t\t���\t���\n");
				printf("\t%s\t%-13s\t%s\t%d\n",searchName(list,date.name)->date.name,searchName(list,date.name)->date.tel,searchName(list,date.name)->date.kind,searchName(list,date.name)->date.balance);
				printf("\n��ѡ����Ҫ�޸ĵ����ݡ�������������");
				printf("\n\t\t0.�޸�����\n\n");
				printf("\t\t1.�޸ĵ绰\n\n");
				printf("\t\t2.�޸Ļ�Ա�ȼ�\n\n");
				printf("\t\t3.�޸Ļ����\n\n");
				printf("\t\t4.��������\n\n");
				scanf("%d",&choice);
				switch(choice)
				{
					case 0:
						printf("\n�������޸ĺ������ ���� ");
						scanf("%s",&searchName(list,date.name)->date.name);
						break;
					case 1:
						printf("\n�������޸ĺ������ �绰 ");
						scanf("%s",&searchName(list,date.name)->date.tel);
						break;
					case 2:
						printf("\n�������޸ĺ������ ��Ա�ȼ� ");
						printf("\n��Ա�ȼ� (��ʯ ���� VIP ��ͨ��\n");
						scanf("%s",&searchName(list,date.name)->date.kind);
						break;
					case 3:
						printf("\n�������޸ĺ���������� ");
						scanf("%d",&searchName(list,date.name)->date.balance);
						break;
					case 4:
						printf("\n�������޸ĺ������....\n\t����\t�绰\t\t���\t���\n");
						printf("\t");
			      		fflush(stdin);
						scanf("%s%s%s%d",&searchName(list,date.name)->date.name,&searchName(list,date.name)->date.tel,&searchName(list,date.name)->date.kind,&searchName(list,date.name)->date.balance);
						printf("�޸���ɣ�");
						break;
				}
				printf("\n�Ƿ�����޸ģ� \t�� y / �� n \t");
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
			printf("��������ѡ���� ");
			fflush(stdin);
			scanf("%d",&choice); //������ѡ��ѡ��
			if(choice<0||choice>3)//���������Ϣ
			{
					system("cls");
					menuOne();
					printf("���������������� %d\n",choice);
					printf("��������ȷ��ѡ�� (���:0 - 3)");
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
							printf("\n***************��ѡ����ǰ�����������**************\n");
							printf("\n������������һ�Ա��\n����\t");
							fflush(stdin);
							scanf("%s",&date.name);
							if(searchName(list,date.name)==NULL)
							{
								printf("\nû�в�ѯ�������");
								printf("�Ƿ�������ң� \t�� y / �� n \t");
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
								printf("\n����\t�绰\t\t���\t���\n");
								printf("%s\t%-13s\t%s\t%d\n",searchName(list,date.name)->date.name,searchName(list,date.name)->date.tel,searchName(list,date.name)->date.kind,searchName(list,date.name)->date.balance);
								fflush(stdin);
								printf("\n�Ƿ�������ң� \t�� y / �� n \t");
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
							printf("\n***************��ѡ����ǰ��յ绰����**************\n");
							printf("\n������������һ�Ա��\n�绰\t");
								fflush(stdin);
								scanf("%s",&date.tel);
								if(searchTel(list,date.tel)==NULL)
								{
									printf("\nû�в�ѯ�������");
									printf("�Ƿ�������ң� \t�� y / �� n \t");
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
									printf("\n����\t�绰\t\t���\t���\n");
									printf("%s\t%-13s\t%s\t%d\n",searchTel(list,date.tel)->date.name,searchTel(list,date.tel)->date.tel,searchTel(list,date.tel)->date.kind,searchTel(list,date.tel)->date.balance);
									fflush(stdin);
									printf("\n�Ƿ�������ң� \t�� y / �� n \t");
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
							printf("\n***************��ѡ����ǰ��ջ�Ա�ȼ�����**************\n");
							printf("������������һ�Ա��\n�ȼ�:\t");
							fflush(stdin);
							scanf("%s",&date.kind);
							if(seekList(list,date.kind)==0)
							{
								printf("\n\t��ѯ���Ϊ�գ�����������\n\n");
							}
							printf("**************************�������***********************");
							printf("\n�Ƿ�������ң�\t�� y / �� n \t");
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
			printf("������ѡ��Ĺ��� ");
			scanf("%d",&choice);
			if(choice<0||choice>2)//���������Ϣ
			{	
				system("cls");
				menuTwo();
				printf("���������������� %d\n",choice);
				printf("��������ȷ��ѡ�� (���:0 - 2) ");
				fflush(stdin);
				scanf("%d",&choice);
			}
			else{
				switch(choice)
				{
					case 0:
						system("cls");
						printf("������ҽ������\n\n");
						sortList(list);
						printfList(list);
						system("pause");
						break;
					case 1:
						system("cls");
						printf("������ҽ������\n\n");
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
		printf("\n---------------����ʾ��Ա��Ϣ��---------------\n\n");
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