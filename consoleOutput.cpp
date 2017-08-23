/*
ENG:
Created by Rafał Majewski (GHPL) in 2017

Condition of use:
If this code (modified or not) is distributed in uncompiled form then there must be information about original author.


PL:
Stworzone przez Rafała Majewskiego (GHPL) in 2017

Warunek używania:
Jeżeli ten kod (zmodyfikowany lub nie) jest rozprowadzany ze zmianami lub bez w postaci nieskompilowanej to trzeba podać informację o oryginalnym autorze.
*/

#include <iostream>
#include <map>
#include <stdlib.h>


long double mod(long double liczba1,long double liczba2)
{
    return liczba1-liczba2*(unsigned long long)(liczba1/liczba2);
}

unsigned int xSize=51;
unsigned int ySize=51;
unsigned int seed=4;
int los;

int dx(int p)
{
    if (p==0) return 1;
    if (p==1) return 0;
    if (p==2) return -1;
    if (p==3) return 0;
}

int dy(int p)
{
    if (p==0) return 0;
    if (p==1) return 1;
    if (p==2) return 0;
    if (p==3) return -1;
}

std::map<int,std::map<int,int> >mapa;
//std::map<int,std::map<int,int> >kierunki;

bool flaga=false;

bool check(int cX,int cY,int stX,int stY,int dir,int iter,int a)
{
    if (iter==0) flaga=false;
    bool ret=true;
    int i=0;

    while (mapa[stX+i*dx(dir)][stY+i*dy(dir)]==-1)
    {
        if (flaga==true) break;
        //std::cout<<cX<<"."<<cY<<" "<<a<<" iter"<<iter<<" "<<stX+i*dx(dir)<<"."<<stY+i*dy(dir)<<std::endl;
        if (iter==3)
        {
            if (stX+i*dx(dir)==cX&&stY+i*dy(dir)==cY)
            {
                //std::cout<<"falsz"<<std::endl;
                flaga=true;
                return false;
            }
        }
        if (iter<3)
        {
            if (mapa[stX+i*dx(dir)+dx(mod(dir+a,4))][stY+i*dy(dir)+dy(mod(dir+a,4))]==-1)
            {
               ret=check(cX,cY,stX+i*dx(dir)+dx(mod(dir+a,4)),stY+i*dy(dir)+dy(mod(dir+a,4)),mod(dir+a,4),iter+1,a);
            }
        }
        i++;
    }
    return ret;
}

main()
{
    srand(seed);
    for (int iy=0;iy<=ySize+1;iy++)
    {
        mapa[-1][iy-1]=-1;
        mapa[xSize][iy-1]=-1;
    }
    for (int ix=0;ix<=xSize-1;ix++)
    {
        mapa[ix][-1]=-1;
        mapa[ix][ySize]=-1;
    }

    for (int iy=0;iy<ySize;iy++)
    {
        for (int ix=0;ix<xSize;ix++)
        {
            mapa[ix][iy]=0;
        }
    }

    for (int iy=1;iy<ySize;iy+=2)
    {
        for (int ix=1;ix<xSize;ix+=2)
        {
            mapa[ix][iy]=-1;
            los=rand()%4;
            for (int i=0;i<4;i++)
            {
                if (mapa[ix+dx(los)][iy+dy(los)]==0&&check(ix,iy,ix+2*dx(los),iy+2*dy(los),los,0,1)&&check(ix,iy,ix+2*dx(los),iy+2*dy(los),los,0,-1))
                {
                    mapa[ix+dx(los)][iy+dy(los)]=-1;
                    break;
                }
                else
                {
                    los=mod(los+1,4);
                }
            }
        }
    }

    for (int iy=0;iy<=ySize+1;iy++)
    {
        for (int ix=0;ix<=xSize+1;ix++)
        {
            if (mapa[ix-1][iy-1]==-1)
            {
                std::cout<<"#";
            }
            else
            {
                std::cout<<" ";

            }
        }
        std::cout<<std::endl;
    }
}
