//entering student data
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//char tolower(char);
void display(FILE *);
void append(FILE*);
void delete(FILE*);

struct student{
	
	char name[30];
	int age,roll;
	float cgpa;
	};

int main()
{
	FILE *fbin;
	int choice;
	char again;
	fbin = fopen("student.dat","ab+");
	
	if(fbin == NULL)
	{
		printf("Error while accessing file!\n");
		return 0;
	}
	printf("\n1.display data\n2.Append new record\n3.Delete record\n0.Exit\nYour Choice:");
	scanf("%d",&choice);
	
	switch(choice)
	{
		case 0:
			break;
		case 1:
			display(fbin);
			break;
		case 2:
			do{
				append(fbin);
				printf("\nAppend Another Record?(y/n):");
				scanf("\n%c",&again);
			}while(again=='y');
			display(fbin);
			break;
		case 3:
			do{
				delete(fbin);
				printf("\nDelete Another Record?(y/n):");
				scanf("\n%c",&again);
			}while(again=='y');

			fbin = fopen("student.dat","ab+");
			display(fbin);
			break;

		default: printf("Invalid Choice\n");
	}
	
	fclose(fbin);
	return 0;
}

void display(FILE *fbin)
{
	printf("\n================================================================\n");
	struct student stu;
	
	rewind(fbin);
	printf("%-20s%-10s%-10s%s\n","NAME","AGE","ROLL","CGPA");
	
	while( fread(&stu,sizeof(stu),1,fbin) == 1 )
		printf("%-20s%-10d%-10d%f\n",stu.name,stu.age,stu.roll,stu.cgpa);
		
	printf("================================================================\n");	
}

void append(FILE *fbin)
{
	struct student stu;
	printf("\nName: "); scanf("\n%[^\n]s",stu.name);
	printf("Age: "); scanf("%d",&stu.age);
	printf("Roll: "); scanf("%d",&stu.roll);
	printf("CGPA: "); scanf("%f",&stu.cgpa);
	
	fseek(fbin,0,SEEK_END);
	fwrite(&stu,sizeof(stu),1,fbin);
}

void delete(FILE *fbin)
{
	struct student stu;
	int xroll;
	FILE *fnew = fopen("temp.dat","ab+");
	
	printf("Roll: ");
	scanf("%d",&xroll);
	rewind(fbin);
	
	while(fread(&stu,sizeof(stu),1,fbin) == 1)
		if(stu.roll != xroll)
			fwrite(&stu,sizeof(stu),1,fnew);

	fclose(fnew);
	fclose(fbin);
	remove("student.dat");
	rename("temp.dat","student.dat");
}
