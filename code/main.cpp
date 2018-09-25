#include <iostream>
#include <map>
#include <time.h>

std::map<short, std::map<short, bool>> maze; //true - wall, false - space
short sizeX=11, sizeY=14; //have to be odd

char dx(char direction)
{
    if (direction == 1) return 1;
    else if (direction == 3) return -1;
    else return 0;
}

char dy(char direction)
{
    if (direction == 0) return -1;
    else if (direction == 2) return 1;
    else return 0;
}

//check if a closed room will be created
bool check(short x, short y, char direction, short s_x, short s_y)
{
    if (maze[x][y] == 0 || x == 0 || x == sizeX-1 || y == 0 || y == sizeY-1) return false;
    if (x == s_x && y == s_y) return true;
    if (maze[x+dx((direction+3)%4)][y+dy((direction+3)%4)] == 1)
    {
        if (check(x+dx((direction+3)%4), y+dy((direction+3)%4), (direction+3)%4, s_x, s_y)) return true;
    }
    if (maze[x+dx(direction)][y+dy(direction)] == 1)
    {
        if (check(x+dx(direction), y+dy(direction), direction, s_x, s_y)) return true;
    }
    if (maze[x+dx((direction+1)%4)][y+dy((direction+1)%4)] == 1)
    {
        if (check(x+dx((direction+1)%4), y+dy((direction+1)%4), (direction+1)%4, s_x, s_y)) return true;
    }
    return false;
}

int main()
{
    srand(time(NULL));
    //fill map with zeros
    for (short y=0; y<sizeY; ++y)
    {
        for (short x=0; x<sizeX; ++x)
        {
            maze[x][y]=0;
        }
    }
    //make walls on edges
    for (short y=0; y<sizeY; ++y)
    {
        maze[0][y]=1;
    }
    for (short x=1; x<sizeX; ++x)
    {
        maze[x][0]=1;
    }
    for (short y=1; y<sizeY; ++y)
    {
        maze[sizeX-1][y]=1;
    }
    for (short x=1; x<sizeX; ++x)
    {
        maze[x][sizeY-1]=1;
    }
    //generate
    for (short y=2; y<sizeY-2; y+=2)
    {
        for (short x=2; x<sizeX-2; x+=2)
        {
            char direction=rand()%4; //choose a random direction
            maze[x][y]=1; //make wall on the starting point
            while (maze[x+dx(direction)][y+dy(direction)] == 1 || check(x+2*dx(direction), y+2*dy(direction), direction, x, y)) //change direction until it will be possible to make a wall
            {
                ++direction;
                direction=direction%4;
            }
            maze[x+dx(direction)][y+dy(direction)]=1;
        }
    }
    //draw
    for (short y=0; y<sizeY; ++y)
    {
        for (short x=0; x<sizeX; ++x)
        {
            (short)maze[x][y] ? std::cout<<char(219) : std::cout<<' ';
        }
        std::cout<<std::endl;
    }

    return 0;
}
