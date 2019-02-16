#include<bits/stdc++.h>
using namespace std;

int turn;
int random=1;
int h1,h2;

struct Board
{
    int b[2][8];
    void Initialize()
    {
        for(int i=1; i<=6; i++)
        {
            b[1][i]=b[0][i]=4;

        }
        b[0][0]=b[1][7]=0;

    }
    vector<int> play(int pos,int addmove1,int addmove2,int aqu1,int aqu2)
    {
        ///  int aqu=0;
        if(turn==1)
        {
            int stone=b[1][pos];
            b[1][pos]=0;
            int i=pos+1;
            for( ; i<=7; i++)
            {
                if(stone==0)
                {
                    break;
                }
                b[1][i]++;
                stone--;
            }
            if(stone==0 and i==8)
            {
                turn=1-turn;
                addmove1++;
                // return;
            }
            if(stone==0 and b[1][i-1]==1)
            {
                b[1][7]+=b[0][i-1];
                aqu1+=b[0][i-1];
                b[0][i-1]=0;
                //return;
            }
            int ok=-1;
            while(stone)
            {

                if(ok==-1)
                {
                    for(int i=6; i>=1; i--)
                    {
                        if(stone==0)
                        {
                            break;
                        }
                        b[0][i]++;
                        stone--;
                    }
                    if(stone==0)
                    {
                        break;
                    }
                    else
                    {
                        ok*=-1;
                    }
                }
                else
                {
                    int i=1;
                    for(; i<=7; i++)
                    {
                        if(stone==0)
                        {
                            break;
                        }
                        b[1][i]++;
                        stone--;
                    }
                    if(stone==0 and i==8)
                    {
                        turn =1-turn;
                        addmove1++;
                        break;
                    }
                    else if(stone==0 and b[1][i-1]==0)
                    {
                        b[1][7]+=b[0][i-1];
                        aqu1+=b[0][i-1];
                        b[0][i-1]=0;
                        break;
                    }
                    else
                    {
                        ok*=-1;
                    }


                }
            }



        }
        else
        {


            int stone=b[0][pos];
            b[0][pos]=0;
            int i=pos-1;
            for( ; i>=0; i--)
            {
                if(stone==0)
                {
                    break;
                }
                b[0][i]++;
                stone--;
            }
            if(stone==0 and i==-1)
            {
                turn=1-turn;
                addmove2++;
                // return;
            }
            if(stone==0 and b[0][i+1]==1)
            {
                b[0][0]+=b[1][i+1];
                aqu2+=b[1][i+1];
                b[1][i+1]=0;
                //return;
            }
            int ok=-1;
            while(stone)
            {

                if(ok==-1)
                {
                    for(int i=1; i<=6; i++)
                    {
                        if(stone==0)
                        {
                            break;
                        }
                        b[1][i]++;
                        stone--;
                    }
                    if(stone==0)
                    {
                        break;
                    }
                    else
                    {
                        ok*=-1;
                    }
                }
                else
                {
                    int i=6;
                    for(; i>=0; i--)
                    {
                        if(stone==0)
                        {
                            break;
                        }
                        b[0][i]++;
                        stone--;
                    }
                    if(stone==0 and i==-1)
                    {
                        turn =1-turn;
                        addmove2++;
                        break;
                    }
                    else if(stone==0 and b[0][i+1]==0)
                    {
                        b[0][0]+=b[1][i+1];
                        aqu2+=b[1][i+1];
                        b[1][i+1]=0;
                        break;
                    }
                    else
                    {
                        ok*=-1;
                    }


                }
            }



        }

vector<int>v;
v.push_back(addmove1);
v.push_back(addmove2);
v.push_back(aqu1);
v.push_back(aqu2);
return v;

    }
    void Print()
    {
        printf("\n-----------------------------------------------------------\n");
        printf("%d",b[0][0]);
        for(int i=1; i<=6; i++)
        {
            printf("\t%d",b[0][i]);
        }
        printf("\n ");
        for(int i=1; i<=6; i++)
        {
            printf("\t%d",b[1][i]);
        }
        printf("\t%d",b[1][7]);
        printf("\n-----------------------------------------------------------\n");

    }
    int getPos()
    {
        if(turn==1)
        {
            for(int i=1; i<=6; i++)
            {
                if(b[1][i]!=0)
                {
                    return i;
                }
            }

        }
        else
        {

            for(int i=6; i>=1; i--)
            {
                if(b[0][i]!=0)
                {
                    return i;
                }
            }


        }

        return -1;
    }

    void Finish()
    {
        for(int i=1; i<=6; i++)
        {
            b[1][7]+=b[1][i];
            b[0][0]+=b[0][i];
            b[0][i]=b[1][i]=0;
        }
    }
    int hueristic1()
    {
        if(turn==1)
        {
            return b[1][7]-b[0][0];
        }
        else
            return b[0][0]-b[1][7];
    }
    int hueristic2()
    {
        return  50*(b[1][7]-b[0][0])+ 100*(b[0][0]-b[1][7]);

    }
    int hueristic3(int addmove1,int addmove2,int aqu1,int aqu2)
    {
        int val= 50*(b[1][7]-b[0][0])+ 100*(b[0][0]-b[1][7]);
        if(turn==1)
        {
            val+=addmove1;
        }
        else
            val+=addmove2;
        return val;
    }
    int hueristic4(int addmove1,int addmove2,int aqu1,int aqu2)
    {
        int val= 50*(b[1][7]-b[0][0])+ 100*(b[0][0]-b[1][7]);
        if(turn==1)
        {
            val+=150*addmove1;
        }
        else
            val+=150*addmove2;
        if(turn==1)
        {
            val+=200*aqu1;
        }
        else
            val+=200*aqu2;

        return val;
    }


} Mancala;

int getheuval(int val,Board board,int addmove1,int addmove2,int aqu1,int aqu2)
{
    if(val==1)
    {
        val=board.hueristic1();
    }
    else if(val==2)
    {
        val=board.hueristic2();
    }
    else if(val==3)
    {
        val=board.hueristic3(addmove1,addmove2,aqu1,aqu2);
    }
    else
    {
        val=board.hueristic4(addmove1,addmove2,aqu1,aqu2);
    }
    return val;
}

pair<int,int> MiniMax(Board board,bool player,int Alpha,int Beta,int co,int addmove1,int addmove2,int aqu1,int aqu2)
{



    if(board.getPos()==-1)
    {
        turn =player;
        int val;
        if(random)
        {
            val=rand()%4+1;
            val =getheuval(val,board,addmove1,addmove2,aqu1,aqu2);

        }
        else
        {

            if(turn==1)
            {
                val=getheuval(h1,board,addmove1,addmove2,aqu1,aqu2);

            }
            else
                val=getheuval(h2,board,addmove1,addmove2,aqu1,aqu2);

        }
        return make_pair(val,-1);

    }
    if(co>=20)
    {
        turn =player;
        int val;
        if(random)
        {
            val=rand()%4+1;
            val =getheuval(val,board,addmove1,addmove2,aqu1,aqu2);

        }
        else
        {

            if(turn==1)
            {
                val=getheuval(h1,board,addmove1,addmove2,aqu1,aqu2);

            }
            else
                val=getheuval(h2,board,addmove1,addmove2,aqu1,aqu2);

        }
        return make_pair(val,-1);
    }

    if(player)
    {
        int Max=INT_MIN;
        int pos=-1;

        for(int i=1; i<=6; i++)
        {
            if(board.b[1][i]!=0)
            {


                int x[2][8];
                for(int j=0; j<2; j++)
                {
                    for(int k=0; k<8; k++)
                    {
                        x[j][k]=board.b[j][k];
                    }
                }
                turn=player;
                vector<int>v=board.play(i,addmove1,addmove2,aqu1,aqu2);
                addmove1=v[0];
                addmove2=v[1];
                aqu1=v[2];
                aqu2=v[3];

                int val;
                if(turn!=player)
                    val= MiniMax(board, !player, Alpha, Beta,++co,addmove1,addmove2,aqu1,aqu2).first;
                else
                {
                    val= MiniMax(board, player, Alpha, Beta,++co,addmove1,addmove2,aqu1,aqu2).first;

                }
                for(int j=0; j<2; j++)
                {
                    for(int k=0; k<8; k++)
                    {
                        board.b[j][k]=x[j][k];
                    }
                }
                if(Max<val)
                {
                    Max=max(Max,val);
                    pos=i;
                }

                Alpha=max(Alpha, Max);
                if(Beta<=Alpha)
                    break;
            }
            if(Beta<=Alpha)
                break;
        }
        return make_pair(Max,pos);
    }
    else
    {
        int Min=INT_MAX;
        int pos=-1;
        for(int i=1; i<=6; i++)
        {

            if(board.b[0][i]!=0)
            {

                int x[2][8];
                for(int j=0; j<2; j++)
                {
                    for(int k=0; k<8; k++)
                    {
                        x[j][k]=board.b[j][k];
                    }
                }
                turn=player;
                vector<int>v=board.play(i,addmove1,addmove2,aqu1,aqu2);
                addmove1=v[0];
                addmove2=v[1];
                aqu1=v[2];
                aqu2=v[3];


                int val;
                if(turn!=player)
                    val= MiniMax(board, !player, Alpha, Beta,++co,addmove1,addmove2,aqu1,aqu2).first;
                else
                {
                    val= MiniMax(board, player, Alpha, Beta,++co,addmove1,addmove2,aqu1,aqu2).first;

                }
                for(int j=0; j<2; j++)
                {
                    for(int k=0; k<8; k++)
                    {
                        board.b[j][k]=x[j][k];
                    }
                }
                if(Min>val)
                {
                    Min=min(Min,val);
                    pos=i;
                }

                Beta=min(Beta, Min);
                if(Beta<=Alpha)
                    break;
            }

            if(Beta<=Alpha)
                break;
        }
        return make_pair(Min,pos);
    }

}



int main()
{
    turn=1;
    Mancala.Initialize();
    srand(time(NULL));
    //  Mancala.play(6);
    // cout<<turn<<endl;
    // Mancala.Print();
    printf("Choose heuristic randomly? 0. No 1. Yes\n");
    scanf("%d",&random);
    if(!random)
    {
        printf("Choose heuristic for player 1 : (input 1-4) ");
        scanf("%d",&h1);;
        printf("Choose heuristic for player 2 : (input 1-4) ");
        scanf("%d",&h2);;

    }
    int addmove1=0, addmove2=0, aqu1=0,aqu2=0;
    while(true)
    {
        //cout<<"here"<<endl;
        if(turn==1)
        {
            printf("Turn from the player 1 \n");
            int x=turn;

          //  addmove1=addmove2=aqu1=aqu2=0;
            int pos=MiniMax(Mancala,turn,INT_MIN,INT_MAX,0,addmove1,addmove2,aqu1,aqu2).second;

            if(pos==-1)
            {
                printf("No position to play!\n\n");
                Mancala.Finish();
                printf("Game finished.\n");
                printf("Board situation : ");
                Mancala.Print();
                break;
            }



            printf("Player 1 played for the position : %d\n",pos);
            turn=x;
            Mancala.play(pos,addmove1,addmove2,aqu1,aqu2);
            Mancala.Print();

        }
        else
        {
            printf("Turn from the player 2 \n");
            int x=turn;

            //addmove1=addmove2=aqu1=aqu2=0;
            int pos=MiniMax(Mancala,turn,INT_MIN,INT_MAX,0,addmove1,addmove2,aqu1,aqu2).second;

            if(pos==-1)
            {
                printf("No position to play!\n\n");
                Mancala.Finish();
                printf("Game finished.\n");
                printf("Board situation : ");
                Mancala.Print();
                break;
            }
            printf("Player 2 played for the position : %d\n",pos);
            turn=x;
            Mancala.play(pos,addmove1,addmove2,aqu1,aqu2);
            Mancala.Print();

        }
        turn =1-turn;
    }

}
