class config{
public:
    int moveDepth;
    char cover[7][13][3];
    char waste[54][3];
    char stored[54][3];
    char foundation[4][3];
    char rule[4][15];
    char stock[7][13][3];
    int invalid = 0;
    int i=0;
    char *token =(char*)(malloc(sizeof(char) * 4));
    void copy(config x)
    {
        this->moveDepth = x.moveDepth+1;
        for(int i=0;i<7;i++){for(int j=0;j<13;j++)
            {
                strcpy(cover[i][j],x.cover[i][j]);
                strcpy(stock[i][j],x.stock[i][j]);
            }}
        for(int i =0;i<54;i++)
        {
            strcpy(stored[i],x.stored[i]);
            strcpy(waste[i],x.waste[i]);
            if(i<4)
            {
                strcpy(foundation[i],x.foundation[i]);
                strcpy(rule[i],x.rule[i]);
            }
        }
    }
    void MakeMove(char *token) {
        if (token[0] == 'w') {
            if (isdigit(token[3])) {
                int k = token[3] - '0';
                WasTab(k-1);
                if(invalid==1) {
                    return;
                }
            } else {
                WasFound();
                if(invalid==1) {
                    return;
                }
            }
        } else if (token[0] == 'r') {
            resetStock(atoi(rule[3]));
            int a = atoi(rule[3]); a-=1;
            sprintf(rule[3], "%d", a);
            if(invalid==1) {
                return;
            }
        } else if (token[0] == '.') {
            int a = atoi(rule[1]);
            StockWaste(a);
            if(invalid==1) {
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
                    return;
                }
            } else if (token[3] == 'f')
            {
                int k = token[0] - '0';
                TabFoundation(k-1);
                if(invalid==1) {
                    return;
                }
            }
        }

    }
    int validcheck(char a,char b)
    {
        if(((a =='c' ||a =='s' ) && (b=='c'||b=='s'))|| ((a=='h' ||a=='d' ) && (b=='h'||b=='d')))
        {
            return 0;
        }
        return 1;
    }
    int validcheck1(char a,char b) {
        if (contains(list, a) - 1 != contains(list, b)) {
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
    void WasFound()
    {
        int t = movelast(waste);
        int i = contains(cards,waste[t][1]);
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
        int c1 = contains(cards,stock[a][t][1]);
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
            int ind = contains(list,stock[k1][index][0]);
            int ind1 = contains(list,stock[k2][t][0]);
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
        int t5 = movelast(waste);

        if(t!=0 || t5 == -1){ invalid=1;return;}
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
        int p1 = contains(cards,stock[i][index][1]);
        int j1 = contains(cards,waste[te][1]);

        if(p1!=j1 && j1!=-1)
        {
            int ind = contains(list,stock[i][index][0]);
            int ind1 = contains(list,waste[te][0]);

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
    int movelast(char temp[][3]) {
        int g=0;
        while(strlen(temp[g])>1){
            g++;
        }
        return g-1;
    }
};



