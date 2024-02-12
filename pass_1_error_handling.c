# include <stdio.h>
# include <conio.h>
# include <string.h>
#include<stdlib.h>
# define MAX 20
struct estab
{
   char csname[10];
   char extsym[10];
   int address;
   int length;
}es[MAX];

int search(struct estab ES[],char name[10])
{
    int i=0;
    for(i=0;i<3;i++)
    {
        if(strcmp(ES[i].csname,name)==0)
            return 0;
    }
    return 1;
}

int searchSymbol(struct estab ES[],char name[10])
{
    int i=0;
    for(i=0;i<3;i++)
    {
        if(strcmp(ES[i].extsym,name)==0)
            return 0;
    }
    return 1;
}

int main()
{
  char input[10],name[10],symbol[10];
  int count=0,progaddr,csaddr,add,len;
  FILE *fp1,*fp2;
  fp1=fopen("linkinput.txt","r");
  fp2=fopen("loadmap.txt","w");
  printf("\nEnter ADDRESS\n");
  scanf("%x",&progaddr);
  csaddr=progaddr;
  fscanf(fp1,"%s",input);
while(strcmp(input,"END")!=0)
{
   if(strcmp(input,"H")==0)
   {
    fscanf(fp1,"%s",name);
    if(search(es,name)==1){
    strcpy(es[count].csname,name);
    strcpy(es[count].extsym,"**");
    fscanf(fp1,"%x",&add);
    es[count].address=add+csaddr;
    fscanf(fp1,"%x",&len);
    es[count].length=len;
    fprintf(fp2,"%s\t%s\t\t%x\t%x\n",es[count].csname,es[count].extsym,es[count].address,es[count].length);
    count++;
    }
    else
        printf("\nDuplicate External Symbol %s\n",name);
   }
   else if(strcmp(input,"D")==0)
   {
    fscanf(fp1,"%s",input);
    while(strcmp(input,"R")!=0)
    {
      strcpy(es[count].csname,"  ");
      if(searchSymbol(es,input)==1)
      {
      strcpy(es[count].extsym,input);
      fscanf(fp1,"%x",&add);
      es[count].address=add+csaddr;
      es[count].length=0;
      fprintf(fp2,"%s\t%s\t\t%x\t%x\n",es[count].csname,es[count].extsym,es[count].address,es[count].length);
      count++;
      }
      else{
        printf("Duplicate External Symbol %s\n",input);
          break;
      }
      fscanf(fp1,"%s",input);
     }
    csaddr=csaddr+len;
   }
   else if(strcmp(input,"T")==0)
   {
     while(strcmp(input,"E")!=0)
     fscanf(fp1,"%s",input);
   }
   fscanf(fp1,"%s",input);
}
fclose(fp1);
fclose(fp2);
return 0;
}
