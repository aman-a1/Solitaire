#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char arr[50][100];
extern char cover[7][13][3];
extern char waste[54][3];
extern char stored[54][3];
extern char foundation[4][3];
extern char rule[4][15];
extern char stock[7][13][3];
int checkList[4][13];
int cov;
int sto;
int was ;
int stor;
char duplicates[54][3];
int dupl=0,mis=0,err=0;
char missing[54][3];
char list[] = {'K','Q','J','T','9','8','7','6','5','4','3','2','A','_'};
char cards[5] ={'c','d','h','s'};
extern FILE *fp;
void ini()
{
    for(int i=0;i<7;i++)
    {
        for(int j=0;j<13;j++)
        {
            strcpy(cover[i][j],"");
            strcpy(stock[i][j],"");
        }
    }
}
char* substr(const char *src, int m, int n)
{

    int len = n - m;
    char *dest = (char*)malloc(sizeof(char) * (len + 1));

    for (int i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }
    *dest = '\0';
    return dest - len;
}
int contains(char a[],char c)
{
    for(int i=0;i<strlen(a);i++)
    {
        if(a[i] == c)return i;
    }

    return -1;
}
void checkarray(char a[54][3],int size)
{

    for(int i=0;i<size;i++)
    {   int p =-1;
        char t[3]; strcpy(t,a[i]);
        if(t[1]=='c'){p=0;} else if (t[1]=='d'){p=1;}else if (t[1]=='h'){p=2;}
        else{   p=3;}
        int temp;
        temp = contains(list, t[0]);
        if(checkList[p][temp])
        {
            err++;
            strcpy(duplicates[dupl],t);
            dupl++;
        } else{
            checkList[p][temp]=1;
        }
    }
}
void checkarray2(char a[7][13][3])
{

    for(int i=0;i<7;i++) {
        int j = 0;
        while (strlen(a[i][j]) == 2) {
            int p = -1;
            char t[3];
            strcpy(t, a[i][j]);
            if (t[1] == 'c') { p = 0; }
            else if (t[1] == 'd') { p = 1; }
            else if (t[1] == 'h') { p = 2; }
            else { p = 3; }
            int temp;
            temp = contains(list, t[0]);
            if (checkList[p][temp]) {
                err++;
                strcpy(duplicates[dupl], t);
                dupl++;
            } else {
                checkList[p][temp] = 1;
            }
            j++;
        }
    }
}
int inputcheck() {

    for(int p=0;p<4;p++)
    {   for(int l=0;l<13;l++)
        {   checkList[p][l] = 0;    }
    }
    //foundations
    for(int i=0;i<4;i++)
    {   char t = foundation[i][0];
        if(t != '_')
        {   int s = contains(list,t);
            for(int j=s;j<13;j++)
            {    checkList[i][j] = 1; }
        }
    }
    checkarray2(cover);
    checkarray2(stock);
    checkarray(stored,stor);
    checkarray(waste,was);
    //missing cards
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<13;j++)
        {
            if(checkList[i][j] == 0)
            {
                char temp[3];
                temp[0] = list[j];
                temp[1] = cards[i];
                strcpy(missing[mis],temp);
                mis++;
                err++;
            }
        }
    }
    return err;
}

int* getuntilMove(char *argv[]) {

    ini();
    cov =0; sto=0;was =0;stor=0;
    int error =0,i=0;
    char line[100];
   fp = stdin;
    if(argv[1]!=NULL) {
        fp = fopen(argv[1], "r");
    }
    int count = 0,count1=0;
    int index = 0,index1 =0;
    while(NULL != fgets(line, 100, fp))
    {
        if('#' != line[0]) {    if (strlen(line) > 1) {
                int d = contains(line, '#');
                if (d != -1) {
                    strcpy(line, substr(line, 0, d));
                    strcat(line, "\n");
                }
                strcpy(arr[i], line);
                if(strstr(arr[i],"MOVES") != NULL || feof(fp))
                {
                    break;
                }
                i++;
            }   }
    }
    char rer[] ="Error!! Rules not specified correctly!!";
    int  j=0;
    int r=0;
    while(j<i) {

        char line[100];
        strcpy(line, arr[j]);
        char *token = strtok(line, " :\n\t\r");
        while (token != NULL) {
            if (strstr(token, "RULES") != 0) {
                while (1) {
                    if(j!=0) {
                        token = strtok(line, " :\n");
                    } else{
                        token = strtok(NULL, " :\n");
                    }
                    while (token != NULL) {
                        if(strstr(token,"FOUNDATIONS") != NULL) {
                            if(r!=4)
                            {
                                fprintf(stderr,"%s\n",rer);
                                exit(0);
                            }
                            r = 0;
                            break;
                        } else if (r==4 && strstr(token,"FOUNDATIONS") == 0 )
                        {
                            fprintf(stderr,"Error at line %d: expecting 'FOUNDATIONS:'",j+1);
                            exit(0);
                        }
                        else {
                            strcpy(rule[r], token);
                            if(r==0 && strcmp(token,"turn")!=0) {fprintf(stderr,"%s\n",rer);exit(0);}
                            else if(r==1 && strcmp(token,"1") != 0 && strcmp(token,"3") != 0){fprintf(stderr,"%s\n",rer);exit(0);}
                            else if(r==2 && strcmp(token,"unlimited")!= 0 && strcmp(token,"limit")!= 0){fprintf(stderr,"%s\n",rer);exit(0);}
                            else if (r==3 && !isdigit(rule[r][0])){fprintf(stderr,"%s\n",rer);exit(0);}

                            //   strcpy(rule[r], token);
                            if(strcmp(rule[r],"unlimited")==0)
                            {
                                r++;
                            }
                            r++;
                            token = strtok(NULL, " :\n");
                        }
                    }
                    if (token!= NULL && strstr(token,"FOUNDATIONS")!=NULL)    {
                        break;
                    }
                    j++;
                    strcpy(line, arr[j]);
                }

            }
            else
            {
                fprintf(stderr,"Unexpected text!! Expecting 'RULES:'\n");
                exit(0);
            }
            int temp = j;
            if (strstr(token,"FOUNDATIONS")!=NULL) {

                while (1) {

                    if (j != temp) {
                        token = strtok(line, " :\n\t\r");
                    } else {
                        token = strtok(NULL, " :\n\t\r");
                    }
                    while (token != NULL) {
                        if (strstr(token,"TABLEAU")!=NULL) {
                            if(r!=4)
                            {
                                fprintf(stderr,"Error ! Foundations not specified correctly!! LINE NO: %d \n",j+1);
                                exit(0);
                            }
                            r = 0;
                            break;
                        } else if (r==4 && strstr(token,"TABLEAU") != NULL)
                        {
                            fprintf(stderr,"Error at line %d: expecting 'TABLEAU:'",j+1);
                            exit(0);
                        }
                        else {

                            strcpy(foundation[r], token);

                            if((contains(list,foundation[r][0])== -1 && foundation[r][0] != '_' ))
                            {
                                fprintf(stderr,"Error ! Foundations not specified correctly!! LINE NO: %d \n",j+1);
                                exit(0);
                            }
                            else if(foundation[r][1] != cards[r])
                            {
                                fprintf(stderr,"Error ! Foundations not specified correctly!! LINE NO: %d \n",j+1);
                                exit(0);
                            }
                            r++;
                            token = strtok(NULL, " :\n");
                        }
                    }
                    if (token!=NULL && strstr(token,"TABLEAU") != NULL){
                        break;
                    }
                    j++;
                    strcpy(line, arr[j]);
                }
            }

            temp =j;
            if (strstr(token,"TABLEAU") != NULL)
            {
                int t_f = 0;

                while (1) {
                    int fchar = 0;

                    if (j != temp) {
                        token = strtok(line, " :\n\t\r");
                        r++;
                        t_f = 0;
                        count++;
                        count1++;
                        index = 0;
                        index1=0;
                    } else {
                        token = strtok(NULL, " :\n\t\r");
                        count--;
                        count1--;
                    }
                    while (token != NULL) {
                        if (strstr(token,"STOCK") != NULL){//strcmp("STOCK:", token) == 0 || strcmp("STOCK:\n", token) == 0) {
                            if(r!=8)
                            {
                                fprintf(stderr,"Error ! TABLEAU not specified correctly!! LINE NO: %d",j);
                                printf("%s",arr[j]);
                                exit(0);
                            }
                            r = 0;
                            break;
                        } else {

                            if(r==8 &&strstr(token,"STOCK") != NULL)
                            {
                                fprintf(stderr,"Error at line %d: expecting 'STOCK:'",j+1);
                                exit(0);
                            }

                            if(strcmp(token,"|") == 0)
                            {
                                t_f=1;
                            }
                            else if(strcmp(token,"\n") == 0){}
                            else if(t_f ==0)
                            {


                                strcpy(cover[count][index], token);
                                if(contains(list,cover[count][index][0]) == -1 || contains(cards,cover[count][index][1]) == -1)
                                {
                                    fprintf(stderr,"Error! TABLEAU not specified correctly!! LINE NO: %d \n",j);
                                    exit(0);
                                }
                                index++;
                                cov++;

                            } else {

                                strcpy(stock[count1][index1], token);
                                if(contains(list,stock[count1][index1][0]) == -1 || contains(cards,stock[count1][index1][1]) == -1)
                                {
                                    fprintf(stderr,"Error! TABLEAU not specified correctly!!LINE NO: %d \n",j);
                                    exit(0);
                                }
                                index1++;
                                sto++;
                                if(fchar ==1)
                                {
                                    char te[3];
                                    strcpy(te,stock[count1][index1-2]);
                                    char te2[3];
                                    strcpy(te2,stock[count1][index1-1]);
                                    if((contains(list,te2[0]) - 1) != contains(list, te[0]) || (contains(list,te2[0]) == -1) ||(contains(list,te[0]) == -1))
                                    {
                                        err++;
                                        fprintf(stderr,"Tableau Line Up error! LINE NO: %d",j);
                                        exit(0);
                                    }
                                    else if(((te2[1]=='c' ||te2[1]=='s' ) && (te[1]=='c'||te[1]=='s')) ||((te2[1]=='h' ||te2[1]=='d' ) && (te[1]=='h'||te[1]=='d')))
                                    {
                                        err++;
                                        fprintf(stderr,"Tableau Line Up error! LINE NO: %d",j);
                                        exit(0);
                                    }
                                }
                                fchar = 1;


                            }
                            token = strtok(NULL, " :\n");
                        }
                    }


                    if (token != NULL && strstr(token,"STOCK") != NULL){
                        break;
                    }
                    j++;
                    strcpy(line, arr[j]);
                }

            }
            temp =j;
            if (strstr(token,"STOCK") != NULL){
                int t_f = 0;
                while (1) {

                    if (j != temp) {
                        token = strtok(line, " :\n\t\r");
                    } else {
                        token = strtok(NULL, " :\n\t\r");
                    }
                    while (token != NULL) {
                        if (strstr(token,"MOVES") != NULL)
                        {
                            r = 0;
                            break;
                        } else {
                            if(strcmp(token,"|") == 0)
                            {
                                t_f=1;
                            }
                            else if(strcmp(token,"\n") == 0){}
                            else if(t_f ==0)
                            {

                                strcpy(waste[was], token);
                                if(contains(list,waste[was][0]) == -1 || contains(cards,waste[was][1]) == -1)
                                {
                                    fprintf(stderr,"Error! STOCK not specified correctly!! LINE NO: %d",j);
                                    exit(0);
                                }
                                was++;

                            } else {

                                strcpy(stored[stor], token);
                                if(contains(list,stored[stor][0]) == -1 || contains(cards,stored[stor][1]) == -1)
                                {
                                    fprintf(stderr,"Error! STOCK not specified correctly!! LINE NO: %d",j);
                                    exit(0);
                                }
                                stor++;

                            }
                            r++;
                            token = strtok(NULL, " :\n\t\r");
                        }
                    }
                    if (token != NULL && strstr(token,"MOVES") != NULL){
                        break;
                    }
                    j++;
                    strcpy(line, arr[j]);
                }
            }
            break;
        }
        break;
    }
    int* ret = (int*)malloc(sizeof(int)*4) ;
    error = inputcheck();
    if(error==0) {

        *ret = cov;
        *(ret+1)= stor;
        *(ret+2)= was;
        *(ret+3)= 0;
        return ret;
       // printf("Valid Input:\n%d covered cards\n%d stock cards\n%d waste cards\n", cov, stor, was);
    }
    else {
        *(ret+3)= error;
        if(dupl != 0)
        {
            fprintf(stderr," Duplicated cards: ");

            for(int i=0;i<dupl;i++)
            {
                fprintf(stderr,"%s ",duplicates[i]);
            }
            fprintf(stderr,"\n");
        }

        if(mis != 0)
        {
            fprintf(stderr," Missing cards: ");
            for(int i=0;i<mis;i++)
            {
                fprintf(stderr,"%s ",missing[i]);

            }
            fprintf(stderr,"\n");
        }
    }
    return ret;
}
