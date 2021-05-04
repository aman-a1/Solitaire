#include <iostream>
#include "check.h"
#include "config.hh"
#include "/share/cs327/include/termbox.h"
#include <unistd.h>
struct tb_cell cell;
void dot();
void reset();
void Tab(char a,char b);
char card[4] ={'c','d','h','s'};
void updateFoundation();
void printAll(FILE *fp, config a);
using namespace std;
void FillRest();
char cover[7][13][3];
char waste[54][3];
char stored[54][3];
char foundation[4][3];
char rule[4][15];
char stock[7][13][3];
int index(char a)
{
    for(int i=0;i<4;i++)
    {
        if(card[i] == a)
        {
            return i;
        }
    }
}
short suits[]={0x02660,0x02662,0x02661,0x02663};
FILE *fp;

void fillInstructionBox();

void updateWaste();

void updateTab();

bool switchf= false;
int seed = -1;
char sseed[5]="";
int turn = 1;
int Limit = -1;
int movelast(char temp[][3]) {
    int g=0;
    while(strlen(temp[g])>1){
        g++;
    }
    return g-1;
}
char pArray[9][80] ={ " q: quit  "," R: restart "," n: new game    u: undo move",""," '.': next card    r: reset stock"
                      ," To move, press the source and "," then destination (one of w, f, "," 1, 2, 3, 4, 5, 6, 7) " };
void generateRandomGame(int seed, int turn) {
    //rules

strcpy(rule[0],"turn");
    sprintf(rule[1], "%d", turn);
if(Limit== -1)strcpy(rule[2],"unlimited");
else{
    strcpy(rule[2],"limit");
    sprintf(rule[3], "%d", Limit);
}
// Foundations
strcpy(foundation[0],"_c");
strcpy(foundation[1],"_d");
strcpy(foundation[2],"_h");
strcpy(foundation[3],"_s");
// covered cards
FillRest();
}
int checkL[4][13];
char lst[] = {'K','Q','J','T','9','8','7','6','5','4','3','2','A'};

void FillRest(){
    srand(seed);
    for(int p=0;p<4;p++)
    {   for(int l=0;l<13;l++)
        {   checkL[p][l] = 0;    }
    }
    //covered
    for(int i=6;i>=0;i--){
        for(int j=0;j<i;j++){
           bool state = false;
           while(!state) {
               int a = rand() % 13;
               int b = rand() % 4;
           if(checkL[b][a]==0){
               checkL[b][a]=1;
               state = true;
               char C[3]="";
               C[0] = lst[a];
               C[1] = card[b];
               strcpy(cover[abs(i-6)][j],C);

           }

           }

        }
    }
    //Stock
    for(int i=0;i<7;i++){
        bool state = false;
        while(!state) {
            int a = rand() % 13;
            int b = rand() % 4;
            if(checkL[b][a]==0){
                checkL[b][a]=1;
                state = true;
                char C[3]="";
                C[0] = lst[a];
                C[1] = card[b];
                strcpy(stock[i][0],C);

            }

        }
    }
    // Stored
    for(int i=0;i<24;i++){
        bool state = false;
        while(!state) {
            int a = rand() % 13;
            int b = rand() % 4;
            if(checkL[b][a]==0){
                checkL[b][a]=1;
                state = true;
                char C[3]="";
                C[0] = lst[a];
                C[1] = card[b];
                strcpy(stored[i],C);
            }

        }
    }
}
config mainclass;
config previousclass;
char filename[20]=" ";
void Basic(int argc, char* argv[])
{

    int i=0;
    while(*(argv+i))
    {
        if(strcmp(*(argv+i),"-f") == 0){switchf= true;i+=1;if(*(argv+i)!=NULL){ strcpy(filename,*(argv+i));}}
        else if(strcmp(*(argv+i),"-s") == 0){i+=1; seed += atoi(*(argv+i)); strcpy(sseed,*(argv+i));}
        else if(strcmp(*(argv+i),"-1") == 0){
            turn = 1;
        }else if(strcmp(*(argv+i),"-3") == 0){
            turn = 3;
        }
        else if(strcmp(*(argv+i),"-l") == 0){
            i++;
            Limit = atoi(*(argv+i));
        }
        i++;
    }
    if(switchf) {
        if(strcmp(filename,"")==0)
        {
            cerr<<"Please provide a filename! \n";
            exit(0);
        }
        argv[1] = filename;
        getuntilMove(argv);
    }else{
        if(turn == -1){
            cerr<<"turn switch is not defined properly!\n";
            exit(0);
        }else if(seed == -1)
        {
            cerr<<"seed value missing or  not defined properly!\n";
            exit(0);

        }
               generateRandomGame(seed,turn);
    }
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
    turn = atoi(rule[1]);
}
char msg[100]="";
char ar[] = {'w','1','2','3','4','5','6','7'};
bool contains(char a)
{
    for(int i=0;i<strlen(ar);i++)
    {
        if(ar[i]==a)return true;
    }
    return false;
}
int main(int argc, char* argv[]) {
    restart:
    Basic(argc,argv);
    tb_init();
    fillInstructionBox();
    tb_present();
    for(;;) {
        struct tb_event event;
        tb_poll_event(&event);
        if(event.ch == 'q')
        {
            tb_clear();
            tb_present();
            break;
        }else if(event.ch =='R')
        {
            tb_clear();
            tb_present();
            goto restart;

        }else if(event.ch =='n')
        {
            tb_clear();
            tb_present();
            seed+=7;
            goto restart;
        }
        else if(event.ch == '.'){
            tb_clear();
            tb_present();
            dot();
            fillInstructionBox();
            tb_present();
        }else if(event.ch == 'r')
        {

                tb_clear();
                tb_present();
                reset();
                fillInstructionBox();
                tb_present();

        }else if(contains(event.ch))
        {
            struct tb_event event2;
            tb_poll_event(&event2);
            tb_clear();
            tb_present();
            Tab(event.ch,event2.ch);
            fillInstructionBox();
            tb_present();
        }else if(event.ch == 'u')
        {
            tb_clear();
            tb_present();
            mainclass.copy(previousclass);
            fillInstructionBox();
            tb_present();
        }
    }
    tb_shutdown();
}

void fillInstructionBox() {
cell.ch =0;
cell.fg =0;
cell.bg = TB_RED;
for(int i=0;i<12;i++){
 tb_put_cell(0,i,&cell);
    tb_put_cell(35,i,&cell);
 tb_present();
}
    for(int i=1;i<35;i++){
        tb_put_cell(i,0,&cell);
        tb_put_cell(i,11,&cell);
        tb_present();
    }
    cell.bg = NULL;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<strlen(pArray[i]);j++)
        {
            cell.ch = pArray[i][j];
            tb_put_cell(j+1,i+2,&cell);
            tb_present();
        }
    }
    if(switchf){
       int i = 17 - strlen(filename)/2;
        cell.bg = TB_RED;
        for(int p=0;p<strlen(filename);p++)
        {   cell.ch = filename[p];
            tb_put_cell(i,0,&cell);
            tb_present();
            i++;
        }
    } else{
        char w[11] ="Seed:";
        strcat(w,sseed);
        int i=0;
        cell.bg = TB_WHITE;
        cell.fg = TB_BLACK;
        for(int p=0;p<strlen(w);p++)
        {   cell.ch = w[p];
            tb_put_cell(14+i,0,&cell);
            tb_present();
            i++;
        }
    }
    updateFoundation(); updateWaste(); updateTab();
}

void updateTab() {
    char arr[] = "1234567 ";
    cell.ch =0;
    cell.bg = TB_BLUE;
    cell.fg = TB_BLACK;
    int c = 0;
    for(int i=0;i<7;i++)
    {
        cell.ch = arr[i];
        tb_put_cell(45+c,0,&cell);
        cell.ch =arr[7];
        tb_put_cell(44+c,0,&cell);
        tb_put_cell(46+c,0,&cell);

        tb_present();
        c+=5;
    }
    c=0;
    cell.ch= '#';
    for(int i=6;i>=0;i--)
    {
        for(int j=0;j<movelast(mainclass.cover[i])+1;j++)
        {
            if(j%2 == 0){
                cell.bg = TB_GREEN;
                cell.fg = TB_CYAN;
            }else{
                cell.bg = TB_GREEN;
                cell.fg = TB_RED;
            }
            tb_put_cell(44+c,j+1,&cell);
            tb_put_cell(45+c,j+1,&cell);
            tb_put_cell(46+c,j+1,&cell);
            tb_present();
        }
        c+=5;
    }
    c=0;
    int height =0;
    for(int i=6;i>=0;i--)
    {
        for(int j=0;j<movelast(mainclass.stock[i])+1;j++)
        {   cell.bg = TB_WHITE;
            cell.fg = TB_BLACK;
            cell.ch = 0;
            tb_put_cell(45+c,j+movelast(mainclass.cover[i])+2+height,&cell);
            tb_put_cell(45+c,j+movelast(mainclass.cover[i])+2+1+height,&cell);
            cell.ch = mainclass.stock[i][j][0];
            tb_put_cell(44+c,j+movelast(mainclass.cover[i])+2+height,&cell);
            tb_put_cell(46+c,j+movelast(mainclass.cover[i])+2+1+height,&cell);
            cell.ch = suits[index(mainclass.stock[i][j][1])];
            tb_put_cell(46+c,j+movelast(mainclass.cover[i])+2+height,&cell);
            tb_put_cell(44+c,j+movelast(mainclass.cover[i])+2+1+height,&cell);
            tb_present();
            height+=1;
        }
        height = 0;
        c+=5;

    }

}

void Tab(char a,char b){
    char arr[5] = { a  , '-' , '>' , b ,'\0'};
    config temp;
    temp.copy(mainclass);
    temp.MakeMove(arr);
    if(!temp.invalid){
        cout<<arr;
        previousclass.copy(mainclass);
        mainclass.MakeMove(arr);
        strcpy(msg,"");
    } else {
        strcpy(msg,"Move ");
        strcat(msg,arr);
        strcat(msg," is a invalid Move!");
    }

}
void dot(){
    config temp;
    temp.copy(mainclass);
   temp.MakeMove(".");
    if(!temp.invalid){
        previousclass.copy(mainclass);
        mainclass.MakeMove(".");
        strcpy(msg,"");
    } else {
        strcpy(msg,"Move '.' is a invalid Move!");
    }
}
void reset()
{
    config temp;
    temp.copy(mainclass);
    temp.MakeMove("r");
    if(!temp.invalid){
        previousclass.copy(mainclass);
        mainclass.MakeMove("r");
        strcpy(msg,"");
    } else {
        strcpy(msg,"Move 'r' is a invalid Move!");
    }

}

void updateFoundation(){
   cell.ch =0;
    char f[] = "Foundations";
    cell.bg = TB_BLUE;
    cell.fg = TB_BLACK;
    for(int i=0;i<strlen(f);i++)
    {
        cell.ch = f[i];
        tb_put_cell(14+i,13,&cell);
        tb_present();
    }
    int c = 0;
    for(int i=0;i<4;i++) {
            cell.bg = TB_WHITE;
            cell.fg = TB_BLACK;

        cell.ch = 0;
        tb_put_cell(12 + c, 15, &cell);
        tb_put_cell(12 + c, 16, &cell);
        cell.ch = mainclass.foundation[i][0];
        tb_put_cell(11 + c, 15, &cell);
        tb_put_cell(13 + c, 16, &cell);
        cell.ch = suits[i];
        tb_put_cell(13 + c, 15, &cell);
        tb_put_cell(11 + c, 16, &cell);
        tb_present();
        c+=5;
    }
}

void updateWaste(){
char w[] = "Waste";
char rp[100] = "Resets:";
if(strcmp(mainclass.rule[2],"unlimited")==0)
{
    strcat(rp,"unlimited");
}else{
    strcat(rp,mainclass.rule[3]);
}
    cell.ch=0;
    cell.bg = TB_BLUE;
    cell.fg = TB_BLACK;
    for(int i=0;i<strlen(w);i++)
    {
        cell.ch = w[i];
        tb_put_cell(10+i,19,&cell);
        tb_present();
    }
    for(int i=0;i<strlen(rp);i++)
    {
        cell.ch = rp[i];
        tb_put_cell(18+i,19,&cell);
        tb_present();
    }
    cell.bg = TB_WHITE;
    cell.fg = TB_BLACK;

    if(turn == 1)
    {
        cell.ch = 0;
        tb_put_cell(12, 21, &cell);
        tb_put_cell(12, 22, &cell);
        if(movelast(mainclass.waste) != -1){cell.ch = mainclass.waste[movelast(mainclass.waste)][0];}

        tb_put_cell(11, 21, &cell);
        tb_put_cell(13, 22, &cell);
        if(movelast(mainclass.waste) != -1){ cell.ch = suits[index(mainclass.waste[movelast(mainclass.waste)][1])];}
        tb_put_cell(13, 21, &cell);
        tb_put_cell(11, 22, &cell);
        tb_present();
        cell.ch = '*';
        tb_put_cell(20, 21, &cell);
        tb_put_cell(20, 22, &cell);
        tb_put_cell(19, 21, &cell);
        tb_put_cell(21, 22, &cell);
        tb_put_cell(21, 21, &cell);
        tb_put_cell(19, 22, &cell);
        char a[2];
        cell.bg = 0;
        cell.fg = 0;
        sprintf(a,"%d",(movelast(mainclass.stored)+1));
        cell.ch = a[0];
        tb_put_cell(20, 23, &cell);
        cell.ch = a[1];
        tb_put_cell(21, 23, &cell);
        tb_present();
    }else if(turn == 3)
    {
        cell.ch =0;
        // work needed

        for(int i=2;i>=0;i--) {

            if ((movelast(mainclass.waste) - i) > -1 || i == 0) {

                    cell.ch = 0;
                    tb_put_cell(12 + i, 21, &cell);
                    tb_put_cell(12 + i, 22, &cell);

                if (movelast(mainclass.waste) - i > -1) {
                    cell.ch = mainclass.waste[movelast(mainclass.waste) - i][0];
                }
                tb_put_cell(11 + i, 21, &cell);
                tb_put_cell(13 + i, 22, &cell);

                if (movelast(mainclass.waste) - i > -1) {
                    cell.ch = suits[index(mainclass.waste[movelast(mainclass.waste) - i][1])];
                }

                tb_put_cell(13 + i, 21, &cell);
                tb_put_cell(11 + i, 22, &cell);
                tb_present();
            }
        }
        }

        cell.bg = TB_WHITE;
        cell.fg = TB_BLACK;
        cell.ch = '*';
        tb_put_cell(20, 21, &cell);
        tb_put_cell(20, 22, &cell);
        tb_put_cell(19, 21, &cell);
        tb_put_cell(21, 22, &cell);
        tb_put_cell(21, 21, &cell);
        tb_put_cell(19, 22, &cell);
        char a[2];
        cell.bg = 0;
        cell.fg = 0;
        sprintf(a,"%d",(movelast(mainclass.stored)+1));
        cell.ch = a[0];
        tb_put_cell(20, 23, &cell);
        cell.ch = a[1];
        tb_put_cell(21, 23, &cell);
        tb_present();
    }


