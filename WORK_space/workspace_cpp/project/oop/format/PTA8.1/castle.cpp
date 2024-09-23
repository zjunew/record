#include "castle.h"

void castle::init()
{
    for(int i = 0 ; i < 5 ;i++)
    {
        for(int j = 0 ; j < 5 ; j++)
        {
            room[i][j] = 1;
        }
    }
    room[0][2] = 2;//lobby
    set(prin.x,prin.y,mon.x,mon.y);
}
void castle::set(int &x1, int &y1 , int &x2 , int &y2)
{
    
    do
    {
        srand(time(0));
        x1 = rand()%5 , y1 = rand()%5;
        x2 = rand()%5 , y2 = rand()%5;
    }while((x1==x2 && y1==y2) || (x1==0&&y1==2)|| (x2==0&&y2==2));
    //cout<<x1<<y1<<x2<<y2<<endl;
}
void castle::judge(int x,int y)
{
    if(x<4 && y<4 && x > 0 &&y > 0)
    {
        cout<<".  There are 4 exits: east, west , up and down;"<<endl;
    }
    else if(x==0 && y==0)
    {
        cout<<".  There are 2 exits: east and up "<<endl;
    }
    else if(x==4 && y == 0)
    {
        cout<<".  There are 2 exits: west and up "<<endl;
    }
    else if(x==0 && y==4)
    {
        cout<<".  There are 2 exits: east and down "<<endl;
    }
    else if(x==4 && y==4)
    {
        cout<<".  There are 2 exits: west and down "<<endl;
    }
    else if(y==0)
    {
        cout<<".  There are 3 exits: east , west and up "<<endl;
    }
    else if(y==4)
    {
        cout<<".  There are 3 exits: east , west and up "<<endl;
    }
    else if(x==0)
    {
        cout<<".  There are 3 exits: east , down and up "<<endl;
    }
    else if(x==4)
    {
        cout<<".  There are 3 exits: west , down and up "<<endl;
    }
}
int castle::whether_safe(int num)
{
    if(num>=5||num<0)
    {
        cout<<"Wrong input , please input again."<<endl;
        getline(cin,commmand);
        return 0;
    }
    return 1;
}
void castle::commmand_analy()
{
    if(commmand == "go east")
    {
        if(whether_safe(x+1))
        {
            x++;
            game_print(x,y);
        }
        else
        {
            commmand_analy();
        }
    }
    else if(commmand == "go west")
    {
        if(whether_safe(x-1))
        {
            x--;
            game_print(x,y);
        }
        else
        {
            commmand_analy();
        }
    }
    else if(commmand == "go up")
    {
        if(whether_safe(y+1))
        {
            y++;
            game_print(x,y);
        }
        else
        {
            commmand_analy();
        }
    }
    else if(commmand == "go down")
    {
        if(whether_safe(y-1))
        {
            y--;
            game_print(x,y);
        }
        else
        {
            commmand_analy();
        }
    }
    else 
    {
        cout<<"Wrong input , please input again.()"<<endl;
        getline(cin,commmand);
        
        
        commmand_analy();
        
    }
}
void castle::isprincess(int posx,int posy)
{
    if(posx == prin.x &&posy == prin.y)
    {
        cout<<"Congratulations! You have find the princess."<<endl;
        cout<<"Now,ready to leave!"<<endl;
        game_cout(posx, posy);
    }
}
void castle::ismonster(int posx,int posy)
{
    if(posx==mon.x&&posy==mon.y)
    {
        cout<<"We meet the monster!"<<endl;
        cout<<"The game is over!"<<endl;
        system("pause");
        exit(0);
    }
}
void castle::commmand_two()
{
    if(commmand == "go east")
    {
        if(whether_safe(x+1))
        {
            x++;
            game_cout(x,y);
        }
        else
        {
            commmand_two();
        }
    }
    else if(commmand == "go west")
    {
        if(whether_safe(x-1))
        {
            x--;
            game_cout(x,y);
        }
        else
        {
            commmand_two();
        }
    }
    else if(commmand == "go up")
    {
        if(whether_safe(y+1))
        {
            y++;
            game_cout(x,y);
        }
        else
        {
            commmand_two();
        }
    }
    else if(commmand == "go down")
    {
        if(whether_safe(y-1))
        {
            y--;
            game_cout(x,y);
        }
        else
        {
            commmand_two();
        }
    }
    else 
    {
        cout<<"Wrong input , please input again.()"<<endl;
        getline(cin,commmand);
        
        
        commmand_two();
        
    }
}
void castle::game_cout(int posx , int posy)
{
    ismonster(posx,posy);
    if(posx == 0 && posy == 2)
    {
        cout<<"Welcome to the lobby."<<endl;
        cout<<"We are victorious!";
        exit(0);
    }
    else 
    {
        cout<<"Welcome to the new room["<<posx<<"]["<<posy<<"]" ;
        judge(posx,posy);
        cout<<"Enter your command:";
        getline(cin,commmand);
    }
    commmand_two();
}

void castle::game_print(int posx,int posy)
{
    isprincess(posx,posy);
    ismonster(posx,posy);
    if(posx == 0 && posy == 2)
    {
        cout<<"Welcome to the lobby. There are 3 exits: east, down and up."<<endl;
        cout<<"Enter your command:";
        getline(cin,commmand);
    }
    else 
    {
        cout<<"Welcome to the new room["<<posx<<"]["<<posy<<"]" ;
        judge(posx,posy);
        cout<<"Enter your command:";
        getline(cin,commmand);
    }
    commmand_analy();
}

void castle::newstart()
{
    x=0 , y =2;
    game_print(x,y);
}