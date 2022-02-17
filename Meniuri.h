#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "Joaca.h"
void Menu2();
//Meniul 3 unde alegi dificultatea impotriva calculatorului.
void Menu3()
{
    int m5,m6;
    if(s.limba==0)
        readimagefile("menu3e.jpg",0,0,800,800);
    else readimagefile("menu3r.jpg",0,0,800,800);
    int click5=false;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            m5=mousex();
            m6=mousey();
            if(m5>=250 && m5<=460 && m6>=340 && m6 <=380)
                Play_Computer_easy();
            if(m5>=250 && m5<=490 && m6>=410 && m6 <=450)
                Play_Computer_medium();
            if(m5>=250 && m5<=460 && m6>=480 && m6 <=510)
                Play_Computer_hard();
            if(m5<=120 && m6<=100)
                Menu2();
        }
    }
    while(!click5);

}
void Menu();
//Meniul 2 unde alegi daca joci jucator vs jucator sau vs calculator.
void Menu2()
{
    int m3,m4;
    if(s.limba==0)
        readimagefile("menu2e.jpg",0,0,800,800);
    else
        readimagefile("menu2r.jpg",0,0,800,800);
    int click4=false;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            m3=mousex();
            m4=mousey();
            if(m3>=140 && m3<=660 && m4>=360 && m4 <=410)
                Play();
            if(m3>=140 && m3<=690 && m4>=460 && m4 <=530)
                Menu3();
            if(m3<=120 && m4 <=100)
                Menu();
        }
    }
    while(!click4);

}
void Menu();
//Reguli joc
void How()
{
    cleardevice();
    int m1,m2;
    if(s.limba==0)
        readimagefile("how1.bmp",0,0,800,800);
    else readimagefile("how1r.bmp",0,0,800,800);
    readimagefile("sageata.bmp",0,0,80,40);
    int click1=false;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            m1=mousex();
            m2=mousey();
            if(m1<=80 && m2<=40)
                Menu();
        }
    }
    while(!click1);

}
//Meniul principal
void Menu()
{
    if(s.limba==0)
        readimagefile("menu.jpg",0,0,800,800);
    else readimagefile("menur.jpg",0,0,800,800);
    int x,y;
    int x1=0, y1=0;
    int click=false;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            click=true;
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(x>=310 && x<=490 && y>=310 && y<=390)
                Menu2();
            else if(x>=280 && x<=540 && y>=410 && y<=460)
                How();
            else if(x>=300 && x<=500 && y>=520 && y<=540)
                closegraph();
            else if(x>=90 && x<=300 && y>=630 && y<=720)
            {
                s.limba=0;
                Menu();
            }
            else if(x>=560 && x<=720 && y>=630 && y<=720)
            {
                s.limba=1;
                Menu();
            }
            else Menu();

        }
    while (!click);
}
