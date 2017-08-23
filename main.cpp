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
#include "gyhLib.h"
#include <fstream>
#include <ctime>
#include <cstdio>


unsigned int xSize=27;
unsigned int ySize=25;
unsigned int seed=2.137;
int los;

unsigned long long bajtyW=0;
unsigned long long bajtyZ=0;
unsigned long long dozapis=(xSize+2)*(ySize+2)+(ySize+2);
unsigned long long dowygen=(xSize+2)*(ySize+2)+2*((xSize-1)/2)*((ySize-1)/2);

void clear()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

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

int f1(int p)
{
    return mod(p+1,4);
}

int f2(int p)
{
    return mod(p-1,4);
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

int rind=1;

main()
{
    srand(seed);
    std::fstream plik;
    plik.open("labirynt.txt",std::ios::out);

    for (int iy=0;iy<=ySize+1;iy++)
    {
        mapa[-1][iy-1]=-2;
        bajtyW++;
        //std::cout<<bajtyW*100/dowygen<<"% wygenerowano"<<std::endl;
        //clear();
        mapa[xSize][iy-1]=-2;
        bajtyW++;
        //std::cout<<bajtyW*100/dowygen<<"% wygenerowano"<<std::endl;
        //clear();
        //kierunki[-1][iy-1]=-2;
        //kierunki[xSize][iy-1]=-2;

    }
    for (int ix=0;ix<=xSize-1;ix++)
    {
        mapa[ix][-1]=-2;
        bajtyW++;
        //std::cout<<bajtyW*100/dowygen<<"% wygenerowano"<<std::endl;
        //clear();
        mapa[ix][ySize]=-2;
        bajtyW++;
        //std::cout<<bajtyW*100/dowygen<<"% wygenerowano"<<std::endl;
        //clear();

        //kierunki[ix][-1]=-2;
        //kierunki[ix][ySize]=-2;
    }


    for (int iy=0;iy<ySize;iy++)
    {
        for (int ix=0;ix<xSize;ix++)
        {
            mapa[ix][iy]=0;
            //kierunki[ix][iy]=0;
            bajtyW++;
            //std::cout<<bajtyW*100/dowygen<<"% wygenerowano"<<std::endl;
            //clear();
        }
    }

    for (int iy=1;iy<ySize;iy+=2)
    {
        for (int ix=1;ix<xSize;ix+=2)
        {
            mapa[ix][iy]=-1;
            bajtyW++;
            //std::cout<<bajtyW*100/dowygen<<"% wygenerowano"<<std::endl;
            //clear();
            //kierunki[ix][iy]=-1;
            los=rand()%4;
            //los=random(0,3,rind,seed);
            rind++;
            for (int i=0;i<4;i++)
            {
                //std::cout<<"a dostalem z 1 "<<check(ix,iy,ix+2*dx(los),iy+2*dy(los),los,0,1)<<std::endl;
                //std::cout<<"a dostalem z -1 "<<check(ix,iy,ix+2*dx(los),iy+2*dy(los),los,0,-1)<<std::endl;
                if (mapa[ix+dx(los)][iy+dy(los)]==0&&check(ix,iy,ix+2*dx(los),iy+2*dy(los),los,0,1)&&check(ix,iy,ix+2*dx(los),iy+2*dy(los),los,0,-1))
                {
                    mapa[ix+dx(los)][iy+dy(los)]=-1;
                    //kierunki[ix+dx(los)][iy+dy(los)]=los+1;
                    bajtyW++;
                    //std::cout<<bajtyW*100/dowygen<<"% wygenerowano"<<std::endl;
                    //clear();
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
        bajtyZ++;
        for (int ix=0;ix<=xSize+1;ix++)
        {
            if (mapa[ix-1][iy-1]==-1)
            {
                //std::cout<<"#";
                plik<<"#";
                bajtyZ++;
            }
            else if (mapa[ix-1][iy-1]==-2)
            {
                //std::cout<<"$";
                plik<<"$";
                bajtyZ++;
            }
            else
            {
                //std::cout<<" ";
                plik<<" ";
                bajtyZ++;

            }
            //std::cout<<bajtyZ*100/dozapis<<"% zapisano "<<bajtyZ/1048576<<" megabajtow"<<std::endl;
            //clear();
            //std::cout<<bajtyZ*100/dozapis<<"% zapisano "<<(long double)bajtyZ/1048576<<" megabajtow"<<std::endl;
            //clear();
            //std::cout<<bajtyZ*100/dozapis<<"% zapisano "<<(long double)bajtyZ/1024<<" kilobajtow"<<std::endl;
            //clear();
            //std::cout<<bajtyZ*100/dozapis<<"% zapisano "<<bajtyZ<<" bajtow"<<std::endl;
            //clear();
        }
        //std::cout<<std::endl;
        plik<<std::endl;

    }

    /*
    std::cout<<std::endl;
    for (int iy=0;iy<=ySize+1;iy++)
    {
        for (int ix=0;ix<=xSize+1;ix++)
        {
            if (kierunki[ix-1][iy-1]==-1) std::cout<<"#";
            else if (kierunki[ix-1][iy-1]==-2) std::cout<<"#";
            else if (kierunki[ix-1][iy-1]==0) std::cout<<" ";
            else if (kierunki[ix-1][iy-1]==1) std::cout<<">";
            else if (kierunki[ix-1][iy-1]==2) std::cout<<"v";
            else if (kierunki[ix-1][iy-1]==3) std::cout<<"<";
            else if (kierunki[ix-1][iy-1]==4) std::cout<<"^";
        }
        std::cout<<std::endl;
    }
    */
    plik.close();
}
