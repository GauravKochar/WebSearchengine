#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
typedef struct indexernode indexernode;
typedef struct arraynode arraynode;
struct indexernode
{
indexernode* prev;
char *word;
char *url;
int noOfTimes;
indexernode* next;
};

struct arraynode
{
char *url;
int noOfTimes;
int status;
};

void getIndexerDataFromFile(indexernode**indexerStart,char * path)
{
	FILE *fp;

	fp=fopen(path,"r");
	char ch;
int count=0;
indexernode* temp;
int t=10;

count=0;
int m=9;
int frequency;

	while(m!=EOF)
	{
char* url=(char*)malloc(sizeof(char)*500);
char* word=(char*)malloc(sizeof(char)*30);
m=fscanf(fp,"%s\t%d\t%s\n",word,&frequency,url);
if(m!=EOF)
{

	indexernode* NODE=(indexernode*)malloc(sizeof(indexernode));

	NODE->next=NULL;
	NODE->word=word;
	NODE->noOfTimes=frequency;
	NODE->url=url;
	
	if(*indexerStart==NULL)
	{
	NODE->prev=NULL;
	temp=NODE;
	*indexerStart=NODE;
	}
	else
	{

	temp->next=NODE;
	NODE->prev=temp;
	temp=NODE;

	}
}



	}

}


void storeListToFile(indexernode** indexerStart)
{

FILE* fp;
fp=fopen("storesecondIndexerData.txt","w");

indexernode* ptr=*indexerStart;
while(ptr)
{

fprintf(fp,"%s\t%d\t%s\n",ptr->word,ptr->noOfTimes,ptr->url);
ptr=ptr->next;
}
fclose(fp);

}


long FileSize(FILE*fp)
{
fseek(fp,0,SEEK_END);
long fsize=ftell(fp);

return fsize;
}



int  comparefiles(char * path,char * path1)
{
FILE *fp;
FILE *fp1;

fp=fopen(path,"r");
fp1=fopen(path1,"r");


long size1=0,size2=0;
size1=FileSize(fp);
size2=FileSize(fp1);


fseek(fp,0,SEEK_SET);
fseek(fp1,0,SEEK_SET);

char * string=(char *)malloc(sizeof(char)*size1+1);
char * string1=(char *)malloc(sizeof(char)*size2+1);
string[size1+1]='\0';
string1[size2+1]='\0';

while(fgets(string,20,fp)!=NULL)
{}

while(fgets(string1,20,fp1)!=NULL)
{}

int cmp;

if((cmp=strcmp(string,string1))==0)
return 1;
else
return 0;

}

void Display(indexernode**indexerStart)
{

indexernode*ptr;
		ptr=*indexerStart;
		int count=0;
		while(ptr!=NULL)
		{
		//printf("%s\t\t%d\t\t%s\n",ptr->word,ptr->noOfTimes,ptr->url);
		ptr=ptr->next;
		count++;
		}
		printf("count=%d",count);
}


int* rankingAccordingToFrequency(indexernode** indexerStart,int argc,char *argv[],arraynode arraynodeResult[10][100])
{
int i,count;
int *array=(int *)malloc(sizeof(int)*20);
for(i=1;i<argc;i++)
{
indexernode* ptr;
ptr=*indexerStart;
count=0;
while(ptr)
{


	if((strcmp(ptr->word,argv[i]))==0)
	{

	arraynodeResult[i][count].url=ptr->url;
	arraynodeResult[i][count].noOfTimes=ptr->noOfTimes;
	(count)++;
	}

ptr=ptr->next;
}
array[i]=count;
	
}
return array;


}
void SortAnArray(arraynode arraynodeResult[10][100],int *arrayCount,int argc)
{
int i,j;
arraynode arraynodetemp;
for(int k=1;k<argc;k++)
{
for(i=0;i<arrayCount[k]-1;i++)
{
for(j=0;j<(arrayCount[k]-1-i);j++)
{
	if(arraynodeResult[k][j].noOfTimes<arraynodeResult[k][j+1].noOfTimes)
	{
	arraynodetemp=arraynodeResult[k][j];
	arraynodeResult[k][j]=arraynodeResult[k][j+1];
	arraynodeResult[k][j+1]=arraynodetemp;
	}

}


}
}
}

void Displayarray(arraynode arraynodeResult[10][100],int *arrayCount,int argc)
{
int k,i,count;
for(int k=1;k<argc;k++)
{
	count=0;
	for(i=0;i<arrayCount[k];i++)
	{
printf("%d\t%s\n",arraynodeResult[k][i].status,arraynodeResult[k][i].url);

	}
printf("\n\n%d\n\n\n\n\n",arrayCount[k]);

}
}
int isUniqueInArray(arraynode*array,int length,arraynode tempnode)
{
int i;
for(i=0;i<length;i++)
{

	if((strcmp(array[i].url,tempnode.url))==0)
	{
		if(tempnode.noOfTimes>array[i].noOfTimes)
			array[i].noOfTimes=tempnode.noOfTimes;
	return 0;
	}
}

return 1;
}


arraynode* FinalQueryOutput(arraynode arraynodeResult[10][100],int *arrayCount,int argc,int *p)
{
arraynode *array=(arraynode*)malloc(sizeof(arraynode)*100);

int k,l,q,count=1,i=1;
  if(argc>=3)
  {
for(int i=1;i<3;i++)
{
	for(k=0;k<arrayCount[i];k++)
	{
	
	   for(l=i+1;l<argc;l++)
	   {

		for(q=0;q<arrayCount[l];q++)
		{
		if(!(strcmp(arraynodeResult[i][k].url,arraynodeResult[l][q].url)))
			{
arraynodeResult[i][k].noOfTimes=(arraynodeResult[i][k].noOfTimes*10)+arraynodeResult[l][q].noOfTimes;
if(isUniqueInArray(array,*p,arraynodeResult[i][k]))
{

array[*p]=arraynodeResult[i][k];
(*p)++;


		
}
arraynodeResult[l][q].status=1;
arraynodeResult[i][k].status=1;

break;	
			}


		}

	   }
		


	} 

 }

	for(l=1;l<argc;l++)
	   {
		for(k=0;k<arrayCount[l];k++)
		{
			if(arraynodeResult[l][k].status!=1)
			{
			array[*p]=arraynodeResult[l][k];
			(*p)++;
			}
		}
	}
 	
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
  
}

return array;
}


void Sort1DArrayResult(arraynode*Arrayresult,int length)
{
arraynode temp;
int i,j;
for(i=0;i<length-1;i++)
{
for(j=0;j<(length-1-i);j++)
{
	if(Arrayresult[j].noOfTimes<Arrayresult[j+1].noOfTimes)
	{
	temp=Arrayresult[j];
	Arrayresult[j]=Arrayresult[j+1];
	Arrayresult[j+1]=temp;
	}

}


}
}


void main(int argc,char *argv[])
{	
	
indexernode *indexerStart=NULL;
arraynode arraynodeResult[10][100];
int *arrayCount;
		char path[]="storeIndexerData.txt";
		getIndexerDataFromFile(&indexerStart,path);
		Display(&indexerStart);
		
		storeListToFile(&indexerStart);
		char path1[]="storesecondIndexerData.txt";
		indexerStart=NULL;
		getIndexerDataFromFile(&indexerStart,path1);
		Display(&indexerStart);

		int result=comparefiles(path,path1);
		printf("\n%d",result);
		if(result==1)
		printf("\nFiles are Same\n");
		else
		printf("\nFiles are not Same\n");

int p=0,i;
arraynode* Arrayresult;	
arrayCount=rankingAccordingToFrequency(&indexerStart,argc,argv,arraynodeResult);
SortAnArray(arraynodeResult,arrayCount,argc);
Displayarray( arraynodeResult,arrayCount,argc);
Arrayresult=FinalQueryOutput(arraynodeResult,arrayCount,argc,&p);
Sort1DArrayResult(Arrayresult,p);
for(i=0;i<p;i++)
{
printf("string\t%s\t%d\n",Arrayresult[i].url,Arrayresult[i].noOfTimes);
}
printf("\n%d",p);
//Displayarray( arraynodeResult,arrayCount,argc);
}
