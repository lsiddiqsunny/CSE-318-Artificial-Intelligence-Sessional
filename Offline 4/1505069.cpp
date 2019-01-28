#include<bits/stdc++.h>
using namespace std;

int turn;
int addmove1,addmove2;
int aqu1,aqu2;

struct Board
{
    int b[2][8];
    void Initialize()
    {
        for(int i=1; i<=6; i++)
        {
            b[1][i]=b[0][i]=4;

        }
        b[0][7]=b[1][7]=0;

    }
    void play(int pos)
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
                        aqu1+=b[1][i+1];
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



    }
    void Print()
    {
        printf("\n--------------------------------------------------\n");
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
        printf("\n--------------------------------------------------\n");

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

} Mancala;





int main()
{
    turn=1;
    Mancala.Initialize();
    srand(time(NULL));
    //  Mancala.play(6);
    // cout<<turn<<endl;
    // Mancala.Print();
    while(true)
    {
        if(turn==1)
        {
            printf("Now turn from the player 1 \n");
            int pos=Mancala.getPos();
            if(pos==-1)
            {
                printf("No position to play!\n");
                Mancala.Finish();
                printf("Game finished.\n");
                printf("Board situation : ");
                Mancala.Print();
                break;
            }
            printf("Player 1 played for the position : %d\n",pos);
            Mancala.play(pos);
            Mancala.Print();

        }
        else
        {
            printf("Now turn from the player 2 \n");
            int pos=Mancala.getPos();
            if(pos==-1)
            {
                printf("No position to play!\n");
                Mancala.Finish();
                printf("Game finished.\n");
                printf("Board situation : ");
                Mancala.Print();
                break;
            }
            printf("Player 2 played for the position : %d\n",pos);
            Mancala.play(pos);
            Mancala.Print();

        }
        turn =1-turn;
    }

}
