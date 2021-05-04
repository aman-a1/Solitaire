#include "check.h"
#include <string.h>
char* Remove(char temp[54][3]);
void MakeMove(char *token);
void WasTab(int i);
int movelast(char temp[][3]);
void resetStock(int count);
void StockWaste(int i);
void WasFound();
void MoveTab(int k1, int k2);
void printAll(FILE *fp, int state);
void TabFoundation(int a);
void covtoun(int a);
void writeFile(FILE *f);
FILE *fp;
char cover[7][13][3];
char waste[54][3];
char stored[54][3];
 char foundation[4][3];
char rule[4][15];
 char stock[7][13][3];
char invalidMove[5];
int invalid = -1,fn = -1;
char line[100] ="";
int i=0,j;
 char lst[] = {'K','Q','J','T','9','8','7','6','5','4','3','2','A','_'};
 char card[5] ={'c','d','h','s'};
int validcheck(char a,char b)
{
    if(((a =='c' ||a =='s' ) && (b=='c'||b=='s'))|| ((a=='h' ||a=='d' ) && (b=='h'||b=='d')))
    {
    return 0;
    }
    return 1;
}
int validcheck1(char a,char b) {
    if (contains(lst, a) - 1 != contains(lst, b)) {
        return 0;
    }
    return 1;
}
char* Remove(char temp[54][3])
{
    int t = movelast(temp);t++;
    char *ret = (char*)malloc(sizeof(char)*3);
    strcpy(ret,temp[0]);
    for(i=0; i<t; i++)
    {
        strcpy(temp[i],temp[i + 1]);
    }
    return ret;
}
char* Remove1(char temp[7][13][3],int i)
{
    int t = movelast(temp[i]);t++;
    char *ret = (char*)malloc(sizeof(char)*3);
    strcpy(ret,temp[i][t-1]);
    strcpy(temp[i][t-1],temp[i][t]);
    return ret;
}
int adv(char *argv[])
{

    int state = 0;
    int move = -99;
    int moveact =0;
    char outfile[25] = "";
    char infile[25] ="";
    int i =1;

    while(*(argv+i))
    {
    if(strcmp(*(argv+i),"-m") == 0){ moveact = 1;i+=1;if(*(argv+i)!=NULL){move = atoi(*(argv+i));}}
    else if(strcmp(*(argv+i),"-o") == 0){i+=1; strcpy(outfile,*(argv+i));}
    else if (strcmp(*(argv+i),"-x") == 0){state += 1;}
    else{ strcpy(infile,*(argv+i));  }
        i++;
    }
    if(moveact == 1 && move == -99)
    {
        fprintf(stderr,"-m switch should be defined with a positive number!");
        exit(0);
    } else if (move<0 && move!= -99)
    {
        fprintf(stderr,"No of moves with -m switch can not be less than zero!");
        exit(0);
    }
    if(strcmp(infile,"")!=0)
    {
        argv[1] = infile;
    } else{
        argv[1] = NULL;
    }
   int* check1 = getuntilMove(argv);
    if(*(check1+3) == 0) {
        j = 0;
        FILE *out = stdout;
        if (strcmp(outfile, "") != 0) {
            out = fopen(outfile, "w+");
        }
        while ((move == -99 || j < move) && NULL != fgets(line, 100, fp)) {
            printAll(out, state);
            char *token = strtok(line, " :\n\t\r");
            while (token != NULL) {
                if (strcmp(token, "#") == 0)break;

                if (strlen(token) == 1 || strlen(token) == 4) {
                    if(strlen(token) == 4 && strstr(token,"->") == NULL)
                    {
                        fn = 1;
                        strcpy(invalidMove, token);
                        break;
                    }
                    j++;
                    MakeMove(token);
                } else {
                 fn=1;
                }
                if (invalid == 1 || fn == 1) {
                    strcpy(invalidMove, token);
                    break;
                }
                token = strtok(NULL, " :\n\t\r");
            }
            if (invalid == 1 || fn == 1) {
                break;
            }
        }
        if(fn == 1)
        {
            fprintf(stderr,"Undefined Move!! Move: %s",invalidMove);
            exit(0);
        }
        printAll(out, state);
    }
return invalid;
}

void MakeMove(char *token) {
    if (token[0] == 'w') {
        if (isdigit(token[3])) {
            int k = token[3] - '0';
            WasTab(k-1);
            if(invalid==1) {
                strcpy(invalidMove, token);
                return;
            }
        } else {
            WasFound();
            if(invalid==1) {
                strcpy(invalidMove, token);
                return;
            }
        }
    } else if (token[0] == 'r') {
        resetStock(atoi(rule[3]));
        int a = atoi(rule[3]); a-=1;
        sprintf(rule[3], "%d", a);
        if(invalid==1) {
            strcpy(invalidMove, token);
            return;
        }
    } else if (token[0] == '.') {
        int a = atoi(rule[1]);
        StockWaste(a);
        if(invalid==1) {
            strcpy(invalidMove, token);
            return;
        }
    } else if (isdigit(token[0]))
    {

        if(isdigit(token[3]))
        {
            int k = token[0] - '0';
            int k1 = token[3] - '0';
            if(k>7 || k<0 ||k1>7 ||k1<0)
            {   invalid=1;
            }else {
                MoveTab(k - 1, k1 - 1);
            }
            if(invalid==1) {
                strcpy(invalidMove, token);
                return;
            }
        } else if (token[3] == 'f')
        {
            int k = token[0] - '0';
            TabFoundation(k-1);
            if(invalid==1) {
                strcpy(invalidMove, token);
                return;
            }
        }
    } else
    {
       fn =1;
       return;
    }

}  // MAKE MOVE

void WasFound()
{
    int t = movelast(waste);
    int i = contains(card,waste[t][1]);
    if(validcheck1(foundation[i][0],waste[t][0]) == 1)
    {
        strcpy(foundation[i],waste[t]);
    } else{
        invalid = 1;
        return;
    }
    strcpy(waste[t],waste[t+1]);
} //Was found

void TabFoundation(int a) {
    a = abs(a-6);
        int t =movelast(stock[a]);
    int c1 = contains(card,stock[a][t][1]);
        if(c1 == -1){
            invalid = 1;
            return;
        }
    if(validcheck1(foundation[c1][0],stock[a][t][0]) == 1)
    {
        strcpy(foundation[c1],stock[a][t]);
        strcpy(stock[a][t],stock[a][t+1]);

    } else{
       invalid = 1;
       return;
    }
    if(strcmp(stock[a][0],"")==0) {
        covtoun(a);
    }
}

void covtoun(int a) {
    char* temp = Remove1(cover,a);
    if(temp != NULL)
    {
    strcpy(stock[a][0],temp);}
}

char *Remove2(char temp[7][13][3], int k1, int index) {

    char *ret =(char*) malloc(sizeof(char)*3);
    strcpy(ret,temp[k1][index]);
    int l=index;
    while(strlen(temp[k1][l])>1) {
        strcpy(temp[k1][l], temp[k1][l + 1]);
        l++;
    }
    return ret;
}

int movelast(char temp[][3]) {
   int g=0;
    while(strlen(temp[g])>1){
        g++;
    }
    return g-1;
}

void MoveTab(int k1, int k2) {
    if(k1 == k2)return ;
   k1 = abs(k1-6);
   k2 = abs(k2-6);
   int st = 0;
    int index=0;
    int t = movelast(stock[k2]);
    char a = stock[k2][t][0];
    while(!validcheck1(stock[k1][index][0],a) && strlen(stock[k1][index+1]) >1)
    {
        index++;
        st =1;
    }
    if(st== 0 && !validcheck1(stock[k1][index][0],a)){
        invalid = 1;
        return;
    }
//    int i = contains(card,stock[k1][index][1]);
    if(validcheck(stock[k2][t][1],stock[k1][index][1]))
    {
        int ind = contains(lst,stock[k1][index][0]);
        int ind1 = contains(lst,stock[k2][t][0]);
        if(ind1 == ind-1)
        {
            while(strlen(stock[k1][index])>0) {
                char *temp = Remove2(stock,k1,index);
                t+=1;
                strcpy(stock[k2][t], temp);
            }
        } else{
            invalid = 1;
            return;
        }
    } else{
       invalid = 1;
        return;
    }
if(strlen(stock[k1][0])<1) {
    covtoun(k1);
}
} // MOve TAbe

void StockWaste(int i1) {
    int t = movelast(waste);
    t+=1;


     if(strlen(stored[0])>0) {
         for (int i = 0; i < i1; i++) {
             if(strlen(stored[0])>0) {
                 strcpy(waste[t], stored[0]);
                 t++;
                 Remove(stored);
             } else{
                 break;
             }
     }

     } else{
         invalid = 1;
     }

} // StockWaste

void resetStock(int count) {
    int t = movelast(stored);t+=1;
    if(t!=0){ invalid=1;return;}
    if( count > 0 || strcmp(rule[2],"unlimited") == 0) {

        while (strlen(waste[0]) > 1) {
            strcpy(stored[t],Remove(waste));
            t++;
        }
    } else{
       invalid = 1;
    }
} // reset Stock

void WasTab(int i) {
i = abs(i-6);
int te = movelast(waste);
char* T = waste[te];
    int index = movelast(stock[i]);
    int p1 = contains(card,stock[i][index][1]);
    int j1 = contains(card,waste[te][1]);

    if(p1!=j1 && j1!=-1)
    {
        int ind = contains(lst,stock[i][index][0]);
        int ind1 = contains(lst,waste[te][0]);

        if(validcheck(waste[te][1],stock[i][index][1]) && validcheck1(waste[te][0],stock[i][index][0]))
        {
                strcpy(stock[i][index+1],T);
        }
        else if(ind == -1 && ind1 == 0)
        {
               strcpy(stock[i][0],T);
        } else
        {
            invalid =1;
            return;
        }
    } else
    {
       invalid = 1;
       return;
    }
    strcpy(waste[te],waste[te+1]);

}
void printAll(FILE *fp, int state)
{
if(state == 0) {
    if (invalid != -1) {
        fprintf(stdout, "Move %d is illegal: %s\n", j, invalidMove);
    } else {
        fprintf(stdout, "Processed %d move, all valid\n", j);
    }
    fprintf(fp, "Foundations\n");
    fprintf(fp, "%s %s %s %s\n", foundation[0], foundation[1], foundation[2], foundation[3]);

    fprintf(fp, "Tableau:\n");
    int index[] = {0, 0, 0, 0, 0, 0, 0};
    int max = 0;
    for(int c=0;c<7;c++)
    {
        int t = movelast(cover[c])+1;
        t+=movelast(stock[c])+1;
        if(t>max)
        {
            max = t;
        }
    }

    for (int i = max-1; i >= 0; i--) {
        for (int j1 = 6; j1 >= 0; j1--) {
            if (strlen(cover[j1][abs(i - max + 1)]) > 1) {
                fprintf(fp, "##");
            } else if (strlen(stock[j1][index[j1]]) > 1) {
                fprintf(fp, "%s", stock[j1][index[j1]]);
                index[j1] += 1;
            } else {
                fprintf(fp, "..");
            }
            fprintf(fp, " ");
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "Waste Top\n");
    if (strlen(waste[0]) > 1) {
        int t = movelast(waste);
        int a5 = atoi(rule[1]);
        t-=a5-1;
        for(int i8=0;i8<a5;i8++) {
            if(strlen(waste[t])>0) {
                fprintf(fp, "%s ", waste[t]);
                t += 1;
            } else
            {
                break;
            }
        }
        fprintf(fp,"\n");
    } else {
        fprintf(fp, "(empty)\n");
    }
} else
{
    writeFile(fp);
}
}
void writeFile(FILE *f)
{
    if (invalid != -1) {
        fprintf(stdout, "Move %d is illegal: %s\n", j, invalidMove);
    } else {
        fprintf(stdout, "Processed %d move, all valid\n", j);
    }
    fprintf(f,"RULES :\n");
    fprintf(f,"%s %s\n%s ",rule[0],rule[1],rule[2]);
    if(strcmp(rule[2],"unlimited")==0){ fprintf(f,"\n");}
    else {fprintf(f,"%s\n",rule[3]); }
    fprintf(f,"FOUNDATIONS :\n");
    fprintf(f,"%s\n%s\n%s\n%s\n",foundation[0],foundation[1],foundation[2],foundation[3]);
    fprintf(f,"TABLEAU :\n");
    for(int row=0;row<7;row++)
    {
        int col =0;
        while(strlen(cover[row][col])>1)
        {
            fprintf(f,"%s ",cover[row][col]);
            col++;
        }
        fprintf(f,"| ");
        col =0;
        while(strlen(stock[row][col])>1)
        {
            fprintf(f,"%s ",stock[row][col]);
            col++;
        }
        fprintf(f,"\n");

    }
    fprintf(f,"STOCK :\n");
    int w =0;
    while(strlen(waste[w])>1)
    {
        fprintf(f,"%s ",waste[w]);
        w++;
    }
    fprintf(f,"| ");
    w = 0;
    while(strlen(stored[w])>1)
    {
        fprintf(f,"%s ",stored[w]);
        w++;
    }
    fprintf(f,"\n");
    fprintf(f,"MOVES : ");
}
