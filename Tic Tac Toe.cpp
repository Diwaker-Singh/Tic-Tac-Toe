#include<iostream>
using namespace std;

int index1,moving_player;
char board[9] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};

int isFull(){
    for(int i=0;i<9;i++)
        if(board[i]==' ')
            return 0;
    
    return 1;
}

int user_won(){
    for(int i=0;i<9;i+=3)
        if((board[i]==board[i+1])&&(board[i+1]==board[i+2])&&(board[i]=='O'))
            return 1;

    for(int i=0;i<3;i++)
        if((board[i]==board[i+3])&&(board[i+3]==board[i+6])&&(board[i]=='O'))
            return 1;
    
    if((board[0]==board[4])&&(board[4]==board[8])&&(board[0]=='O'))
        return 1;
    
    if((board[2]==board[4])&&(board[4]==board[6])&&(board[2]=='O'))
        return 1;
    
    return 0;
}

int cpu_won(){
    for(int i=0;i<9;i+=3)
        if((board[i]==board[i+1])&&(board[i+1]==board[i+2])&&(board[i]=='X'))
            return 1;
    
    for(int i=0;i<3;i++)
        if((board[i]==board[i+3])&&(board[i+3]==board[i+6])&&(board[i]=='X'))
            return 1;
    
    if((board[0]==board[4])&&(board[4]==board[8])&&(board[0]=='X'))
        return 1;
    
    if((board[2]==board[4])&&(board[4]==board[6])&&(board[2]=='X'))
        return 1;
    
    return 0;
}

int won(){
    if(user_won()){
        cout<<"\n\n\t!! Congratulations !! You Won !!\n\n";
    }
    else if(cpu_won()){
        cout<<"\n\n\t!! Sorry !! Computer Won !!\n\n";
    }
}

void draw_board(){
    cout<<"\n\t\t"<<board[0]<<" | "<<board[1]<<" | "<<board[2]<<"\n\t\t----------";
    cout<<"\n\t\t"<<board[3]<<" | "<<board[4]<<" | "<<board[5]<<"\n\t\t----------";
    cout<<"\n\t\t"<<board[6]<<" | "<<board[7]<<" | "<<board[8]<<"\n\n";
}

int minimax(bool flag){
    int max_val=-1000,min_val=1000;
    int i,j,value = 1;
    if(cpu_won() == 1)
        {return 10;}
    else if(user_won() == 1)
        {return -10;}
    else if(isFull()== 1)
        {return 0;}
    int score[9] = {1,1,1,1,1,1,1,1,1};

    for(i=0;i<9;i++){
        if(board[i] == ' '){
            if(min_val>max_val){
                if(flag == true){
                    board[i] = 'X';
                    value = minimax(false);
                }
                else{
                    board[i] = 'O';
                    value = minimax(true);
                }
                board[i] = ' ';
                score[i] = value;
            }
        }
    }

    if(flag == true){
        max_val = -1000;
        for(j=0;j<9;j++){
            if(score[j] > max_val && score[j] != 1){
                max_val = score[j];
                index1 = j;
            }
        }
        return max_val;
    }
    if(flag == false){
        min_val = 1000;
        for(j=0;j<9;j++){
            if(score[j] < min_val && score[j] != 1){
                min_val = score[j];
                index1 = j;
            }
        }
        return min_val;
    }
}

void human_move(){
    int move;
    again:  
    cout<<endl<<"Enter the move:";
    cin>>move;
    if(board[move-1]==' ')
        board[move-1] = 'O';
    else{
        cout<<endl<<"\n\n\t !! Invalid Move !! Try different move";
        goto again;
    }
}

void cpu_move(){
    cout<<endl<<"CPU MOVE....";
    minimax(true);
    board[index1] = 'X';
}

int main(){
   int choice;
   cout<<"\n\n\t\t\tTIC TAC TOE (Human Vs Computer)";

    while(isFull() + won() ==0)
    {

        if(moving_player)
            human_move();
        else
            cpu_move();
        moving_player=!moving_player;        
         draw_board();
    }
    if(!cpu_won() and !user_won())
        cout<<"\n\n\t!! Match Draw !!\n\n";
    
    cin>>choice;
    return 0;
}