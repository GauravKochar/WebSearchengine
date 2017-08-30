#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>


typedef struct indexernode indexernode;
struct indexernode
{
indexernode* prev;
char* word;
char* url;
int noOfTimes;
indexernode* next;
};

	

int isUniqueInIndexerList(char * url,int index,indexernode**HashArray,indexernode *NEXTADDRESS,char*str)
{
int status;
if(HashArray[index]==0)
return 1;
else
{
	indexernode*ptr=HashArray[index];
	while(ptr!=NEXTADDRESS)
	{	

		
		if(!strcmp(ptr->url,url)&&!strcmp(ptr->word,str))
		{
			(ptr->noOfTimes)++;
			return 0;
		}
	ptr=ptr->next;
	}
}
return 1;
}



void addtoIndexerHashArray(int index,indexernode**HashArray,indexernode**ADDRESS,indexernode*NODE)
{

if(HashArray[index]==0)
{
HashArray[index]=NODE;
}
*ADDRESS=HashArray[index];
}





indexernode* GetNextAddressIndexerHash(int index,int arraySize,indexernode**indexer_HashArray)
{

indexernode* NEXTADDRESS=NULL;
int i;
	for(i=index+1;i<arraySize;i++)
	{
			if(indexer_HashArray[i]!=0)
		{

			NEXTADDRESS=indexer_HashArray[i];
			break;
		}
	}
	return NEXTADDRESS;
	}


void stringcopy(char* path1,char*path)
{
int i;
for(i=0;path[i]!='\0';i++)
{
path1[i]=path[i];

}
path1[i]='\0';
}


void stringlower(char*result)
{
int i;
for(i=0;result[i]!='\0';i++)
{
if(result[i]>=65&&result[i]<=90)
result[i]=result[i]+32;
}

}

indexernode* getPrevAddressIndexerHash(int index,int arraySize,indexernode**HashArray)
{
int i;
indexernode* PREVADDRESS=NULL;

		for(i=index-1;i>=0;i--)
		{
			if(HashArray[i]!=0)
		{
			PREVADDRESS=HashArray[i];
			break;
		}

		}
		
return PREVADDRESS;
}





void addToIndexerList(char * url,char * word,indexernode** start,int index,indexernode**HashArray,int arraySize)
{
	indexernode* ptr;
indexernode* NODE=(indexernode*)malloc(sizeof(indexernode));

	NODE->url=url;
	NODE->word=word;
	NODE->noOfTimes=1;
	
indexernode*NEXTADDRESS;

indexernode*ADDRESS;
indexernode*PREVADDRESS;
addtoIndexerHashArray(index,HashArray,&ADDRESS,NODE);
NEXTADDRESS=GetNextAddressIndexerHash(index,arraySize,HashArray);
if(*start==NULL||NEXTADDRESS==NULL)
{
NODE->next=NULL;

	if(*start==NULL)
	{
	*start=NODE;
	NODE->prev=NULL;
	

	}
	else 
	{
	PREVADDRESS=getPrevAddressIndexerHash(index,arraySize,HashArray);
		ptr=PREVADDRESS;
	
		while(ptr->next!=NULL)
		{
		ptr=ptr->next;
		}
		ptr->next=NODE;
		NODE->prev=ptr;
	

	}
	
	
}
else if(NEXTADDRESS->prev==NULL)
{
NODE->next=*start;
NEXTADDRESS->prev=NODE;
NODE->prev=NULL;
*start=NODE;
}else
{
indexernode*ptr1;
	if(ADDRESS!=NODE)
	ptr1=ADDRESS;
	else
	ptr1=NEXTADDRESS->prev;

	while(ptr1!=NEXTADDRESS)
	ptr1=ptr1->next;
		

		
		ptr1->prev->next=NODE;
		NODE->prev=ptr1->prev;
		NODE->next=ptr1;
		ptr1->prev=NODE;
}


}


int generateHashFunction(char *result,int arraySize)
{
int len=strlen(result);
return((len)%arraySize);
}


char* getUrl(char * str,int len)
{
int i,k=0;
char * result=(char*)malloc(sizeof(char)*500);

for(i=0;i<len;i++)
{
	if(str[i]=='=')
	{
		i++;
		while(str[i]!=',')
		{
		result[k]=str[i];
		k++;
		i++;
		}
		i=len;
	}


}
 result[k]='\0';
return result;

}


char * findTitle(char* str)
{
	long len=strlen(str);
	char check[]="<title>";
	long i;
int x=0,j=0;
char *null="\0\0";
	
	char *result=(char*)malloc(sizeof(char)*200);
	for(i=0;i<len;i++)
	{
		while((str[i]!=check[0]||str[i+1]!=check[1]||str[i+2]!=check[2]||str[i+3]!=check[3]||str[i+4]!=check[4]||str[i+5]!=check[5]||str[i+6]!=check[6])&&i<len)
		{
		i++;
		}

		while(str[i]==check[x]&&check[x]!='\0')
		{
		i++;
		x++;

		}
		if(check[x]=='\0')
		{
		while(str[i]!='<')
		{

			result[j]=str[i];
			j++;
			i++;
		}
		result[j]='\0';
		stringlower(result);
		i=len;
		}
		else
			{
				sprintf(result,"%s",null);
				free(result);
			}
		

	}
return result;

}

void getFunctionForIndexer(char * url,indexernode** start,char *title,indexernode**indexer_HashArray,int arraySize)
{
int j,index,i;
for(i=0;title[i]!='\0';)
{
j=0;
char * result=(char*)malloc(sizeof(char)*30); 
	while((title[i]>=32&&title[i]<=63)||(title[i]>=90&&title[i]<=96)||(title[i]>=123))
	{
	i++;
	}
		if(title[i]!=32&&title[i]!='\0')
		{
			while(title[i]!=32&&title[i]!=','&&title[i]!='-'&&title[i]!='\0'&&title[i]!='.'&&title[i]!='='&&title[i]!='/'&&title[i]!=';'&&title[i]!='_'&&title[i]!='&'&&title[i]!=':'&&title[i]!='"'&&title[i]!='|')
			{
				result[j]=title[i];
					j++;
					i++;		
				
			}
		result[j]='\0';
		index=generateHashFunction(result,arraySize);
		indexernode*NEXTADDRESS;
	NEXTADDRESS=GetNextAddressIndexerHash(index,arraySize,indexer_HashArray);

	if(isUniqueInIndexerList(url,index,indexer_HashArray,NEXTADDRESS,result))
			{		
	addToIndexerList(url,result, start,index,indexer_HashArray, arraySize);
			}
		}

}

}
void traverseSpaces(long int *i,int len,char *str)
{
while(*i<len&&str[*i]==32)
{
(*i)++;
}

}


void getMetaContentForIndexer(char *url,indexernode**indexerStart,char*str,indexernode**indexer_HashArray,int arrSize)
{

long len=strlen(str);
	char check[]="<meta";
	char check1[]="content";
	long i;
int x=0,j=0;
char * null="\0\0";

	
	
	for(i=0;i<len;i++)
	{
		while((str[i]!=check[0]||str[i+1]!=check[1]||str[i+2]!=check[2]||str[i+3]!=check[3]||str[i+4]!=check[4])&&i<len)
		{
		i++;
		}
while(str[i]==check[x]&&check[x]!='\0')
		{
		i++;
		x++;

		}
		if(check[x]=='\0')
	{
		while((str[i]!=check1[0]||str[i+1]!=check1[1]||str[i+2]!=check1[2]||str[i+3]!=check1[3]||str[i+4]!=check1[4]||str[i+5]!=check1[5]||str[i+6]!=check1[6])&&i<len)
		{
			i++;
		}
		x=0;
		while(str[i]==check1[x]&&check1[x]!='\0')
		{
		i++;
		x++;

		}
		if(check1[x]=='\0')
		{
			traverseSpaces(&i,len,str);
			if(str[i]=='=')
			{
				i++;
				traverseSpaces(&i,len,str);
				if(str[i]=='"')
				{
				i++;
				
				while(str[i]!='"')
					{
			char *result=(char*)malloc(sizeof(char)*300);
				
while(str[i]==32||(str[i]>=35&&str[i]<=63)||(str[i]>=90&&str[i]<=96)||(str[i]>=123))
					{
					i++;
					}
	j=0;
while(str[i]!=32&&str[i]!=','&&str[i]!='-'&&str[i]!='"'&&str[i]!='.'&&str[i]!='='&&str[i]!='/'&&str[i]!=';'&&str[i]!='_'&&str[i]!='&'&&str[i]!=':'&&str[i]!='|')
						{
							result[j]=str[i];
								j++;
								i++;		
				
						}
							
					
				result[j]='\0';
				stringlower(result);
				int index;
	if(strlen(result)>0)
	{
	index=generateHashFunction(result,arrSize);
	indexernode*NEXTADDRESS;
	NEXTADDRESS=GetNextAddressIndexerHash(index,arrSize,indexer_HashArray);

	if(isUniqueInIndexerList			(url,index,indexer_HashArray,NEXTADDRESS,result))		
	addToIndexerList(url,result,indexerStart,index,indexer_HashArray, arrSize);
	}else
	free(result);
	

					}
				}
				
			}
		
		
		}
		
}

}

}


void  getContentFromFile(char*str,indexernode**indexerStart,indexernode**indexer_HashArray,int arrSize)
	{	
char * url;
char * title;
int len=strlen(str);
url=getUrl(str,len);
title=findTitle(str);
printf("URL=%sTitle=%s\n",url,title);
getFunctionForIndexer(url,indexerStart,title,indexer_HashArray,arrSize);
getMetaContentForIndexer(url,indexerStart,str,indexer_HashArray,arrSize);

}

void pickTheFile(int varFileNo,char * dir,indexernode**indexerStart,indexernode**indexer_HashArray,int arrSize)
{
FILE *fp;
char itostring[10];
sprintf(itostring,"%d",varFileNo);
printf("%d",varFileNo);
char file[]="/temp";
char f[]=".html";
char path1[40];

stringcopy(path1,dir);
strcat(path1,file);
strcat(path1,itostring);
strcat(path1,f);
printf("%s\n",path1);

fp = fopen(path1, "r");

if(fp)
{

fseek(fp, 0, SEEK_END);
long fsize = ftell(fp);

fseek(fp, 0, SEEK_SET);  

char *string = malloc(fsize + 1);
fread(string, fsize, 1, fp);
printf("%s\n",path1);
getContentFromFile(string,indexerStart,indexer_HashArray,arrSize);

}
}


void indexer(int fileno,char* dir,indexernode**indexerStart,indexernode**indexer_HashArray,int arrSize)
{
int i;
for(i=1;i<=fileno;i++)
{

pickTheFile(i,dir,indexerStart,indexer_HashArray,arrSize);
}

}



int isValidDir(char *dir){

	struct stat statbuf;
	if ( stat(dir, &statbuf) == -1 ){
		fprintf(stderr, "-----------------\n");
		fprintf(stderr, "Invalid directory\n");
		fprintf(stderr, "-----------------\n");
		return 0;
	}

	//Both check if there's a directory and if it's writable
	if ( !S_ISDIR(statbuf.st_mode) ){
		fprintf(stderr, "-----------------------------------------------------\n");
		fprintf(stderr, "Invalid directory entry. Your input isn't a directory\n");
		fprintf(stderr, "-----------------------------------------------------\n");
		return 0;
	}

	if ( (statbuf.st_mode & S_IWUSR) != S_IWUSR ){
		fprintf(stderr, "------------------------------------------\n");
		fprintf(stderr, "Invalid directory entry. It isn't writable\n");
		fprintf(stderr, "------------------------------------------\n");
		return 0;
	}
	return 1;

	
}

void storeListToFile(indexernode** indexerStart)
{

FILE* fp;
fp=fopen("storeIndexerData.txt","w");

indexernode* ptr=*indexerStart;
while(ptr)
{

fprintf(fp,"%s\t%d\t%s\n",ptr->word,ptr->noOfTimes,ptr->url);
ptr=ptr->next;
}
fclose(fp);

}

void main(int argc,char *argv[])
{	
	
indexernode *indexerStart=NULL;
int arrSize=100;
int fileno=1;
char dir[30];
int i;
	
	indexernode* indexer_HashArray[100] ;
	for(i=0;i<arrSize;i++)
	indexer_HashArray[i]=0;
	

	
	strcpy(dir,argv[1]);
	dir[strlen(dir)] = '\0';


	
		
	if(isValidDir(dir))
	{

		  struct dirent *de;  
		 int count=0;
		   
		  DIR *dr = opendir(dir);
		 
		    if (dr == NULL)  
		    {
			printf("Could not open current directory" );
		       return ;
		    }
		 
		   
			    while ((de = readdir(dr)) != NULL)
			{
				count++;
			// printf("%s\n", de->d_name);
			}
		 
		   	 closedir(dr);   
			count=count-2;


	indexer(count,dir,&indexerStart,indexer_HashArray,arrSize);

		indexernode*ptr;
		ptr=indexerStart;
		count=0;
		while(ptr!=NULL)
		{
		printf("%s\t%d\t%s\n",ptr->word,ptr->noOfTimes,ptr->url);
		ptr=ptr->next;
		count++;
		}
		printf("%d",count);
	storeListToFile(&indexerStart);
		
	}
	else
		printf("\ninvalid directory");
	
}
