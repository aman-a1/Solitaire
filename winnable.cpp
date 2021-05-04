#include <iostream>
#include "check.h"
#include <string.h>
#include "config.hh"
using namespace std;

bool CheckWinnable(class config a);
int Dfs(class config a);
long int hash(class config a);
int compare(class config config,class config config1);
using namespace std;
long long int n;
char cover[7][13][3];
char waste[54][3];
char stored[54][3];
char foundation[4][3];
char rule[4][15];
char stock[7][13][3];
FILE *fp;
char *tmoves[42] ={
        "2->1","3->1","4->1","5->1","6->1","7->1",
        "1->2","3->2","4->2","5->2","6->2","7->2",
        "2->3","1->3","4->3","5->3","6->3","7->3",
        "2->4","1->4","3->4","5->4","6->4","7->4",
        "2->5","1->5","4->5","3->5","6->5","7->5",
        "2->6","1->6","4->6","5->6","3->6","7->6",
        "2->7","1->7","4->7","5->7","6->7","3->7"
};

char *wmoves[10] ={
      "w->f","w->1","w->2","w->3","w->4","w->5","w->6","w->7",".","r"
};
char *fmoves[8] ={ "w->f","1->f","2->f","3->f","4->f","5->f","6->f","7->f"};

int movelast(char temp[][3]) {
    int g=0;
    while(strlen(temp[g])>1){
        g++;
    }
    return g-1;
}
int switchm = 1000;
int switchc = -1;
int switchf = -1;
int switchv = -1;
config mainclass;
char mr[1000][5];
int mrCount =0;

struct hashtable{
    unsigned int size;
    struct node **n;
    long int s;
};
struct node{
    struct node* next;
    class config a;
};
struct hashtable *h;
void init_table(){
    h->s = 0;
    h->size = 1000000;
    h->n = (struct node**) malloc(sizeof(struct node*) * 1000000);
    for(int i =0;i<1000000;i++)
    {
        h->n[i] = 0;
    }
}
long int hash(class config a)
{
    long int ret=1;
    ret = ret*(movelast(a.cover[0])*7+movelast(a.cover[1])*6+movelast(a.cover[2])*5+movelast(a.cover[3])*4+movelast(a.cover[4])*3+movelast(a.cover[5])*2+movelast(a.cover[6]));
    ret = ret*(movelast(a.stock[0])*7+movelast(a.stock[1])*6+movelast(a.stock[2])*5+movelast(a.stock[3])*4+movelast(a.stock[4])*3+movelast(a.stock[5])*2+movelast(a.stock[6]));
    ret = ret*(ret+(movelast(a.waste)+movelast(a.stored))*(movelast(a.waste)-movelast(a.stored)+1));
    return abs(ret);
}

int add_to_table(class config str){

    long int hashcode = ::hash(str);
    unsigned long index = hashcode % (h->size);
    struct node *nNode = (struct node*) malloc(sizeof(struct node));
    struct node *temp = h->n[index];
    while(temp)
    {    if(compare(temp->a,str) == 0){
            free(nNode);
            return 1;
        }
        temp = temp->next;
    }
    nNode->a = str;
    nNode->next = h->n[index];
    h->n[index] = nNode;
    h->s++;
    return 0;
}

int compare(class config config1, class config config2) {
    int j=0;
        if(config1.moveDepth>config2.moveDepth) {
        return 1;
    }
    while(j<54)
    {
        if(strcmp(config1.waste[j],config2.waste[j])!=0 || strcmp(config1.stored[j],config2.stored[j])!=0) {
            return 1;
        }
        if(j<4) {
            if (strcmp(config1.foundation[j], config2.foundation[j]) != 0) {
                return 1;
            }
        }
        j++;
    }
    for(int i=0;i<7;i++){
        for(j=0;j<13;j++)
        {
            if(strcmp(config1.cover[i][j],config2.cover[i][j])!=0 || strcmp(config1.stock[i][j],config2.stock[i][j])!=0) {
                return 1;
            }
        }}
    return 0;
}

int main(int argc, char* argv[]) {
  h = (hashtable*)malloc(sizeof(struct hashtable));
    init_table();
    n=0;
    int i=1;
    char filename[20]=" ";
    while(*(argv+i))
    {
        if(strcmp(*(argv+i),"-m") == 0){i+=1;if(*(argv+i)!=NULL){ switchm = atoi(*(argv+i));}}
        else if(strcmp(*(argv+i),"-c") == 0){switchc = 1;}
        else if (strcmp(*(argv+i),"-f") == 0){switchf = 1;}
        else if(strcmp(*(argv+i),"-v") == 0){switchv =1;}
        else{
            strcpy(filename,*(argv+i));
        }
        i++;
    }

    if(strcmp(filename," ")!=0){
       argv[1] = filename;
    } else{
        argv[1]=NULL;
    }
    getuntilMove(argv);

    for(int i=0;i<7;i++){for(int j=0;j<13;j++)
        {
            strcpy(mainclass.cover[i][j],cover[i][j]);
            strcpy(mainclass.stock[i][j],stock[i][j]);
        }}
    for(int i =0;i<54;i++)
    {
        strcpy(mainclass.stored[i],stored[i]);
        strcpy(mainclass.waste[i],waste[i]);
        if(i<4)
        {
            strcpy(mainclass.foundation[i],foundation[i]);
            strcpy(mainclass.rule[i],rule[i]);
        }
    }
    strcpy(mainclass.token,"");
    mainclass.moveDepth =0;
    cout<< mainclass.invalid;
    mainclass.MakeMove("w->f");
    cout<< mainclass.invalid;
//    if(switchv != -1)
//    {
//        cerr<<"Using DFS search\n";
//    }
//   int a =  Dfs(mainclass);
//   if(a==1)
//   {
//       while(mrCount>0)
//       {
//          mrCount--;
//          cout<<mr[mrCount]<<"\n";
//       }
//   }else{
//       if(switchv!=-1)
//       {
//           cerr<<n<<" configurations checked.\n";
//       }
//       if(switchc != -1)
//       {
//           cerr<<"Cache had "<<h->s<<" entries.\n";
//       }
//       if(switchm!=-1)
//       {
//           cout<<"# Game is not winnable within "<<switchm<<" moves\n";
//       } else
//       {
//           cout<<"# Game is not winnable!\n";
//       }
//
//   }
    return 0;
}
bool check(char *a, char *b, config pString)
{

    int k1 = abs((int)b[0]-7-'0');
    int k2 = abs((int)b[3]-7-'0');
    int k1a = abs((int)a[0]-7-'0');
    int k2a= abs((int)a[3]-7-'0');
    if(k1a==k2&&k2a==k1){return false;}
    else if(isdigit(b[0]) && isdigit(b[3]) && movelast(pString.stock[k1]) == -1)
    {
        return false;
    }
    else if(isdigit(b[0]) && isdigit(b[3]) && movelast(pString.cover[k1]) == -1 && movelast(pString.stock[k2]) == -1) {
        return false;
    }
    return true;
}
int Dfs(config a) {

        if (CheckWinnable(a)) {
            if(switchv!=-1)
            {
                cerr<<n<<" configurations checked.\n";
            }
            if(switchc != -1)
            {
                cerr<<"Cache had "<<h->s<<" entries.\n";
            }
            cout << "# Winnable in "<<a.moveDepth<<" moves:";
            strcpy(mr[mrCount],a.token);
            mrCount++;
            return 1;
        }
        if(a.moveDepth == switchm || (switchc != -1 && add_to_table(a)==1) )
        {
            return 0;
        }
        int i=0;
        if(strcmp(a.token,".")!=0 &&strcmp(a.token,"r")!=0)
        {
            while(i<8)
            {
                if(switchv!=-1 && n%1000000 == 0 && n!=0 ){
                    cerr<<n<<" configurations checked so far"<<"\n";
                }
                n++;
                if (check(a.token, fmoves[i],  a)) {
                    config temp;
                    temp.copy(a);
                    temp.MakeMove(fmoves[i]);
                    if (!temp.invalid) {
                        strcpy(temp.token, fmoves[i]);
                        if (1 == Dfs(temp)) {
                            strcpy(mr[mrCount],a.token);
                            mrCount++;
                            return 1;
                        }
                    }
                   free(temp.token);
                }
                i++;
            } // TAB to found
            i=0;
            while(i<42)
            {
                if(switchv!=-1 && n%1000000 == 0 && n!=0 ){
                    cerr<<n<<" configurations checked so far"<<"\n";
                }
                n++;
                if (check(a.token, tmoves[i],  a)) {
                    config temp;
                    temp.copy(a);
                    temp.MakeMove(tmoves[i]);
                    if (!temp.invalid) {
                        strcpy(temp.token, tmoves[i]);
                        if (1 == Dfs(temp)) {
                            strcpy(mr[mrCount],a.token);
                            mrCount++;
                            return 1;
                        }
                    }
                    free(temp.token);
                }
                i++;
            } // TAB to TAB
        }
        i=0;
        // Waste moves
        while(i<10) {
            if(switchv!=-1 && n%1000000 == 0 && n!=0 ){
                cerr<<n<<" configurations checked so far"<<"\n";
            }
            n++;
                config temp;
                temp.copy(a);
                temp.MakeMove(wmoves[i]);
                if (!temp.invalid) {
                    strcpy(temp.token, wmoves[i]);
                    if (1 == Dfs(temp)) {
                        strcpy(mr[mrCount],a.token);
                        mrCount++;
                        return 1;
                    }
                }
                free(temp.token);
            i++;
        }

        return 0;
}


bool CheckWinnable(config temp)
{
        for(auto & i : temp.cover) {
            if (movelast(i) != -1)return false;
        }
        if (movelast(temp.stored) != -1) {
            return false;
        }else if(movelast(temp.waste) != -1 && movelast(temp.waste) != 0) {
            return false;
        }

    return true;
}
