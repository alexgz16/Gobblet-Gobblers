#ifndef Joaca_H
#define Joaca_H
#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include<fstream>
using namespace std;
struct Table_Game
{
    int win;
    int Game_table[9][9][3];
    int number[7];
    int turn=0;
    int game=0;
    int limba=0;
    int ok1;
    int nr=0;
} s;
//Functie care reseteaza valorile in caz de un meci a fost castigat sau se schimba modul de joc.
void reset()
{
    int i,j,k;
    for(i=1; i<=3; i++)
        for(j=1; j<=3; j++)
            for(k=1; k<=3; k++)
                s.Game_table[i][j][k]=0;
    for(i=1; i<=6; i++)
        s.number[i]=0;
    s.turn=0;
    s.ok1=0;
    s.nr=0;
}
void Play_Computer_easy();
void Play_Computer_medium();
void Play_Computer_hard();
void Play();
void Menu();
//Functie care verifica daca un jucator a castigat si opreste jocul.
void winner()
{
    int v[10];
    int nr=0,i,j,k;
    for(i=1; i<=9; i++)
        v[i]=0;
    for(i=1; i<=3; i++)
        for(j=1; j<=3; j++)
        {
            nr++;
            for(k=3; k>=1; k--)
            {
                if(abs(s.Game_table[i][j][k])==1)
                {
                    v[nr]=s.Game_table[i][j][k];
                    k=0;
                }
            }
        }
    if(( v[1]==1 && v[2]==1 && v[3]==1) || (v[4]==1 && v[5]==1 && v[6]==1)|| (v[7]==1 && v[8]==1 && v[9]==1) || (v[1]==1 && v[4]==1 && v[7]==1) || (v[2]==1 && v[5]==1 && v[8]==1)|| (v[3]==1 && v[6]==1 && v[9]==1) ||(v[1]==1 && v[5]==1 && v[9]==1) ||(v[3]==1 && v[5]==1 && v[7]==1))
    {
        int n1,n2;
        if(s.limba==0)
            readimagefile("player1.jpg",264,48,539,132);
        else readimagefile("player1r.jpg",264,48,539,132);
        s.win=1;
        readimagefile("reset.bmp",740,0,800,40);
        int click3=false;
        do
        {
            if(ismouseclick(WM_LBUTTONDOWN) && !click3)
            {
                click3=true;
                clearmouseclick(WM_LBUTTONDOWN);
                n1=mousex();
                n2=mousey();
                if(n1>=730 && n1<=800 && n2>=0 && n2<=60)
                {
                    reset();
                    if(s.game==1)
                        Play();
                    else if(s.game==2)
                        Play_Computer_easy();
                    else if(s.game==3)
                        Play_Computer_medium();
                    else if(s.game==4)
                        Play_Computer_hard();
                }
                else if(n1>=0 &&n1<= 100 && n2>=0 && n2<=40)
                    Menu();
                else winner();
            }
        }
        while (!click3);
    }
    if(( v[1]==-1 && v[2]==-1 && v[3]==-1) || (v[4]==-1 && v[5]==-1 && v[6]==-1)|| (v[7]==-1 && v[8]==-1 && v[9]==-1) || (v[1]==-1 && v[4]==-1 && v[7]==-1) || (v[2]==-1 && v[5]==-1 && v[8]==-1)|| (v[3]==-1 && v[6]==-1 && v[9]==-1) ||(v[1]==-1 && v[5]==-1 && v[9]==-1) ||(v[3]==-1 && v[5]==-1 && v[7]==-1))
    {
        if(s.limba==0)
            readimagefile("player2.jpg",263,45,528,128);
        else readimagefile("player2r.jpg",264,48,539,132);
        s.win=1;
        int n1,n2;
        readimagefile("reset.bmp",740,0,800,40);
        int click3=false;
        do
        {
            if(ismouseclick(WM_LBUTTONDOWN) && !click3)
            {
                click3=true;
                clearmouseclick(WM_LBUTTONDOWN);
                n1=mousex();
                n2=mousey();
                if(n1>=760 && n1<=800 && n2>=0 && n2<=40)
                {
                    reset();
                    if(s.game==1)
                        Play();
                    else if(s.game==2)
                        Play_Computer_easy();
                    else if(s.game==3)
                        Play_Computer_medium();
                    else if(s.game==4)
                        Play_Computer_hard();
                }
                else
                    if(n1>=0 &&n1<= 100 && n2>=0 && n2<=40)
                     Menu();
                     else winner();
            }
        }
        while (!click3);
    }
}
void Draw_piece(int pozx,int pozy,int p);
void Poz_Table_ij(int i, int j, int &x, int &y);
//Functie care reface tabla de joc daca reaccesezi acelasi joc fara sa il termini si nu incepi alt joc.
void Current_game()
{
    int i,j,k,x,y,aux;
    if(s.win==1)
        reset();
    else
    {
        for(i=1; i<=3; i++)
            for(j=1; j<=3; j++)
                for(k=3; k>=1; k--)
                    if(abs(s.Game_table[i][j][k])==1)
                    {
                        aux=s.Game_table[i][j][k];
                        Poz_Table_ij(i,j,x,y);
                        s.Game_table[i][j][k]=0;
                        if(aux>0)
                            s.number[k]--;
                        else
                            s.number[3+k]--;
                        Draw_piece(x,y,k*aux);
                        k=0;
                    }
    }
}
void Draw_piece(int pozx,int pozy,int p);
//Functie care verifica daca jucatorul trebuie blocat de calculator pentru a nu castiga.
void verify_player()
{
    int nr=0,i,j,k,x,y,c1,c2,v[10];
    for(i=1; i<=9; i++)
        v[i]=0;
    for(i=1; i<=3; i++)
        for(j=1; j<=3; j++)
        {
            nr++;
            for(k=3; k>=1; k--)
            {
                if(abs(s.Game_table[i][j][k])==1)
                {
                    v[nr]=s.Game_table[i][j][k]*k;
                    k=0;
                }
            }
        }
// LINII
    if((v[1] * v[2] >0 || v[1]*v[3]>0 || v[2]*v[3]>0)&&s.ok1==0)
    {
        if(v[1]>0 && v[2]>0&&v[3]==0)
            if(s.number[6]<2)
                Draw_piece(500,200,-3);
            else if(s.number[5]<2)
                Draw_piece(500,200,-2);
        if(v[1]>0 && v[3]>0&&v[2]==0)
            if(s.number[6]<2)
                Draw_piece(380,200,-3);
            else if(s.number[5]<2)
                Draw_piece(380,200,-2);
        if(v[2]>0 && v[3]>0&&v[1]==0)
            if(s.number[6]<2)
                Draw_piece(200,200,-3);
            else if(s.number[5]<2)
                Draw_piece(200,200,-2);
    }
    if((v[4] * v[5] >0 || v[4]*v[6]>0 || v[5]*v[6]>0) && s.ok1==0)
    {
        if(v[4]>0 && v[5]>0&&v[6]==0)
            if(s.number[6]<2)
                Draw_piece(500,380,-3);
            else if(s.number[5]<2)
                Draw_piece(500,380,-2);
        if(v[4]>0 && v[6]>0&&v[5]==0)
            if(s.number[6]<2)
                Draw_piece(380,380,-3);
            else if(s.number[5]<2)
                Draw_piece(380,380,-2);
        if(v[5]>0 && v[6]>0&&v[4]==0)
            if(s.number[6]<2)
                Draw_piece(200,380,-3);
            else if(s.number[5]<2)
                Draw_piece(200,380,-2);
    }
    if((v[7] * v[8] >0 || v[7]*v[9]>0 || v[8]*v[9]>0) && s.ok1==0)
    {
        if(v[7]>0 && v[8]>0&&v[9]==0)
            if(s.number[6]<2)
                Draw_piece(500,500,-3);
            else if(s.number[5]<2)
                Draw_piece(500,500,-2);
        if(v[7]>0 && v[9]>0&&v[8]==0)
            if(s.number[6]<2)
                Draw_piece(380,500,-3);
            else if(s.number[5]<2)
                Draw_piece(380,500,-2);
        if(v[8]>0 && v[9]>0&&v[7]==0)
            if(s.number[6]<2)
                Draw_piece(200,500,-3);
            else if(s.number[5]<2)
                Draw_piece(200,500,-2);
    }
    else

//COLOANE


        if((v[1] * v[4] >0 || v[1]*v[7]>0 || v[4]*v[7]>0)&&s.ok1==0)
        {
            if(v[1]>0 && v[4]>0&&v[7]==0)
                if(s.number[6]<2)
                    Draw_piece(200,500,-3);
                else if(s.number[5]<2)
                    Draw_piece(200,500,-2);
            if(v[1]>0 && v[7]>0&&v[4]==0)
                if(s.number[6]<2)
                    Draw_piece(200,380,-3);
                else if(s.number[5]<2)
                    Draw_piece(200,380,-2);
            if(v[4]>0 && v[7]>0&&v[1]==0)
                if(s.number[6]<2)
                    Draw_piece(200,200,-3);
                else if(s.number[5]<2)
                    Draw_piece(200,200,-2);
        }
    if((v[2] * v[5] >0 || v[2]*v[8]>0 || v[5]*v[8]>0)&& s.ok1==0)
    {
        if(v[2]>0 && v[5]>0 && v[8]==0)
        {
            if(s.number[6]<2)
                Draw_piece(380,500,-3);
            else if(s.number[5]<2)
                Draw_piece(380,500,-2);
        }
        if(v[2]>0 && v[8]>0&&v[5]==0)
            if(s.number[6]<2)
                Draw_piece(380,380,-3);
            else if(s.number[5]<2)
                Draw_piece(380,380,-2);
        if(v[5]>0 && v[8]>0&&v[2]==0)
            if(s.number[6]<2)
                Draw_piece(380,220,-3);
            else if(s.number[5]<2)
                Draw_piece(380,220,-2);
    }
    if((v[3] * v[6] >0 || v[3]*v[9]>0 || v[6]*v[9]>0)&&s.ok1==0)
    {
        if(v[3]>0 && v[6]>0&&v[9]==0)
            if(s.number[6]<2)
                Draw_piece(500,500,-3);
            else if(s.number[5]<2)
                Draw_piece(500,500,-2);
        if(v[3]>0 && v[9]>0&&v[6]==0)
            if(s.number[6]<2)
                Draw_piece(500,380,-3);
            else if(s.number[5]<2)
                Draw_piece(500,380,-2);
        if(v[6]>0 && v[9]>0&&v[3]==0)
            if(s.number[6]<2)
                Draw_piece(500,200,-3);
            else if(s.number[5]<2)
                Draw_piece(500,200,-2);
    }
//DIAG1
    if((v[1] * v[5] >0 || v[1]*v[9]>0 || v[5]*v[9]>0)&&s.ok1==0)
    {
        if(v[1]>0 && v[5]>0&&v[9]==0)
            if(s.number[6]<2)
                Draw_piece(500,500,-3);
            else if(s.number[5]<2)
                Draw_piece(500,500,-2);
        if(v[1]>0 && v[9]>0&&v[5]==0)
            if(s.number[6]<2)
                Draw_piece(380,380,-3);
            else if(s.number[5]<2)
                Draw_piece(380,380,-2);
        if(v[5]>0 && v[9]>0&&v[1]==0)
            if(s.number[6]<2)
                Draw_piece(200,200,-3);
            else if(s.number[5]<2)
                Draw_piece(200,200,-2);
    }
//DIAG2
    if((v[3] * v[5] >0 || v[3]*v[7]>0 || v[5]*v[7]>0)&&s.ok1==0)
    {
        if(v[3]>0 && v[5]>0&&v[7]==0)
        {
            if(s.number[6]<2)
                Draw_piece(200,500,-3);
            else if(s.number[5]<2)
                Draw_piece(200,500,-2);
        }
        if(v[3]>0 && v[7]>0&&v[5]==0)
        {
            if(s.number[6]<2)
                Draw_piece(380,380,-3);
            else if(s.number[5]<2)
                Draw_piece(380,380,-2);
        }
        if(v[5]>0 && v[7]>0&&v[3]==0)
        {
            if(s.number[6]<2)
                Draw_piece(500,200,-3);
            else if(s.number[5]<2)
                Draw_piece(500,200,-2);
        }
    }
}
void Draw_piece(int pozx,int pozy,int p);
//Functie care verifica daca calculatorul poate castiga cu urmatoarea miscare.
void verify_computer()
{
    int nr=0,i,j,k,x,y,c1,c2,v[10];
    for(i=1; i<=9; i++)
        v[i]=0;
    for(i=1; i<=3; i++)
        for(j=1; j<=3; j++)
        {
            nr++;
            for(k=3; k>=1; k--)
            {
                if(abs(s.Game_table[i][j][k])==1)
                {
                    v[nr]=s.Game_table[i][j][k]*k;
                    k=0;
                }
            }
        }
//LINII
    if((v[1] * v[2] >0 || v[1]*v[3]>0 || v[2]*v[3]>0) &&s.ok1==0)
    {
        if(v[1]<0 && v[2]<0)
            if(s.Game_table[1][3][1]==0 && s.Game_table[1][3][2]==0 && s.Game_table[1][3][3]==0)
                if(s.number[4]<2)
                    Draw_piece(500,200,-1);
                else if (s.Game_table[1][3][2]==0 && s.Game_table[1][3][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(500,200,-2);
        if(v[1]<0 && v[3]<0)
            if(s.Game_table[1][2][1]==0 && s.Game_table[1][2][2]==0 && s.Game_table[1][2][3]==0)
                if(s.number[4]<2)
                    Draw_piece(380,200,-1);
                else if (s.Game_table[1][2][2]==0 && s.Game_table[1][2][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(380,200,-2);
        if(v[2]<0 && v[3]<0)
            if(s.Game_table[1][1][1]==0 && s.Game_table[1][1][2]==0 && s.Game_table[1][1][3]==0)
                if(s.number[4]<2)
                    Draw_piece(200,200,-1);
                else if (s.Game_table[1][1][2]==0 && s.Game_table[1][1][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(200,200,-2);
    }

    if((v[4] * v[5] >0 || v[4]*v[6]>0 || v[5]*v[6]>0) && s.ok1==0)

    {
        if(v[4]<0 && v[5]<0)
            if(s.Game_table[2][3][1]==0 && s.Game_table[2][3][2]==0 && s.Game_table[2][3][3]==0)
                if(s.number[4]<2)
                    Draw_piece(500,380,-1);
                else if (s.Game_table[2][3][2]==0 && s.Game_table[2][3][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(500,380,-2);
        if(v[4]<0 && v[6]<0)
            if(s.Game_table[2][2][1]==0 && s.Game_table[2][2][2]==0 && s.Game_table[2][2][3]==0)
                if(s.number[4]<2)
                    Draw_piece(380,380,-1);
                else if (s.Game_table[2][2][2]==0 && s.Game_table[2][2][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(380,380,-2);
        if(v[5]<0 && v[6]<0)
            if(s.Game_table[2][1][1]==0 && s.Game_table[2][1][2]==0 && s.Game_table[2][1][3]==0)
                if(s.number[4]<2)
                    Draw_piece(200,380,-1);
                else if (s.Game_table[2][1][2]==0 && s.Game_table[2][1][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(200,380,-2);
    }

    if((v[7] * v[8] >0 || v[7]*v[9]>0 || v[8]*v[9]>0)&&s.ok1==0)
    {

        if(v[7]<0 && v[8]<0)
            if(s.Game_table[3][3][1]==0 && s.Game_table[3][3][2]==0 && s.Game_table[3][3][3]==0)
                if(s.number[4]<2)
                    Draw_piece(500,500,-1);
                else if (s.Game_table[3][3][2]==0 && s.Game_table[3][3][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(500,500,-2);
        if(v[7]<0 && v[9]<0)
            if(s.Game_table[3][2][1]==0 && s.Game_table[3][2][2]==0 && s.Game_table[3][2][3]==0)
                if(s.number[4]<2)
                    Draw_piece(380,500,-1);
                else if (s.Game_table[3][2][2]==0 && s.Game_table[3][2][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(380,500,-2);
        if(v[8]<0 && v[9]<0)
            if(s.Game_table[3][1][1]==0 && s.Game_table[3][1][2]==0 && s.Game_table[3][1][3]==0)
                if(s.number[4]<2)
                    Draw_piece(200,500,-1);
                else if (s.Game_table[1][1][2]==0 && s.Game_table[1][1][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(200,500,-2);
    }
//COLOANE
    if((v[1] * v[4] >0 || v[1]*v[7]>0 || v[4]*v[7]>0) && s.ok1==0)
    {
        if(v[1]<0 && v[4]<0)
            if(s.Game_table[3][1][1]==0 && s.Game_table[3][1][2]==0 && s.Game_table[3][1][3]==0)
                if(s.number[4]<2)
                    Draw_piece(200,500,-1);
                else if (s.Game_table[3][1][2]==0 && s.Game_table[3][1][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(200,500,-2);
        if(v[1]<0 && v[7]<0)
            if(s.Game_table[2][1][1]==0 && s.Game_table[2][1][2]==0 && s.Game_table[2][1][3]==0)
                if(s.number[4]<2)
                    Draw_piece(200,380,-1);
                else if (s.Game_table[2][1][2]==0 && s.Game_table[2][1][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(200,380,-2);
        if(v[4]<0 && v[7]<0)
            if(s.Game_table[1][1][1]==0 && s.Game_table[1][1][2]==0 && s.Game_table[1][1][3]==0)
                if(s.number[4]<2)
                    Draw_piece(200,200,-1);
                else if (s.Game_table[1][1][2]==0 && s.Game_table[1][1][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(200,200,-2);
    }
    if((v[2] * v[5] >0 || v[2]*v[8]>0 || v[5]*v[8]>0)&& s.ok1==0)

    {

        if(v[2]<0 && v[5]<0)
            if(s.Game_table[3][2][1]==0 && s.Game_table[3][2][2]==0 && s.Game_table[3][2][3]==0)
                if(s.number[4]<2)
                    Draw_piece(380,500,-1);
                else if (s.Game_table[3][2][2]==0 && s.Game_table[3][2][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(380,500,-2);
        if(v[2]<0 && v[8]<0)
            if(s.Game_table[2][2][1]==0 && s.Game_table[2][2][2]==0 && s.Game_table[2][2][3]==0)
                if(s.number[4]<2)
                    Draw_piece(380,380,-1);
                else if (s.Game_table[2][2][2]==0 && s.Game_table[2][2][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(380,380,-2);
        if(v[5]<0 && v[8]<0)
            if(s.Game_table[1][2][1]==0 && s.Game_table[1][2][2]==0 && s.Game_table[1][2][3]==0)
                if(s.number[4]<2)
                    Draw_piece(380,200,-1);
                else if (s.Game_table[1][2][2]==0 && s.Game_table[1][2][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(380,200,-2);
    }
    if((v[3] * v[6] >0 || v[3]*v[9]>0 || v[6]*v[9]>0)&&s.ok1==0)

    {
        if(v[3]<0 && v[6]<0)
            if(s.Game_table[3][3][1]==0 && s.Game_table[3][3][2]==0 && s.Game_table[3][3][3]==0)
                if(s.number[4]<2)
                    Draw_piece(500,500,-1);
                else if (s.Game_table[3][3][2]==0 && s.Game_table[3][3][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(500,500,-2);
        if(v[3]<0 && v[9]<0)
            if(s.Game_table[2][3][1]==0 && s.Game_table[2][3][2]==0 && s.Game_table[2][3][3]==0)
                if(s.number[4]<2)
                    Draw_piece(500,380,-1);
                else if (s.Game_table[2][3][2]==0 && s.Game_table[2][3][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(500,380,-2);
        if(v[6]<0 && v[9]<0)
            if(s.Game_table[1][3][1]==0 && s.Game_table[1][3][2]==0 && s.Game_table[1][3][3]==0)
                if(s.number[4]<2)
                    Draw_piece(200,500,-1);
                else if (s.Game_table[1][3][2]==0 && s.Game_table[1][3][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(500,200,-2);
    }
//DIAG1
    if((v[1] * v[5] >0 || v[1]*v[9]>0 || v[5]*v[9]>0)&&s.ok1==0)
    {
        if(v[1]<0 && v[5]<0)
            if(s.Game_table[3][3][1]==0 && s.Game_table[3][3][2]==0 && s.Game_table[3][3][3]==0)
                if(s.number[4]<2)
                    Draw_piece(500,500,-1);
                else if (s.Game_table[3][3][2]==0 && s.Game_table[3][3][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(500,500,-2);
        if(v[1]<0 && v[9]<0)
            if(s.Game_table[2][2][1]==0 && s.Game_table[2][2][2]==0 && s.Game_table[2][2][3]==0)
                if(s.number[4]<2)
                    Draw_piece(380,380,-1);
                else if (s.Game_table[2][2][2]==0 && s.Game_table[2][2][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(380,380,-2);
        if(v[5]<0 && v[9]<0)
            if(s.Game_table[1][1][1]==0 && s.Game_table[1][1][2]==0 && s.Game_table[1][1][3]==0)
                if(s.number[4]<2)
                    Draw_piece(200,200,-1);
                else if (s.Game_table[1][1][2]==0 && s.Game_table[1][1][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(200,200,-2);
    }
//DIAG2
    if((v[3] * v[5] >0 || v[3]*v[7]>0 || v[5]*v[7]>0)&&s.ok1==0)

    {
        if(v[3]<0 && v[5]<0)
            if(s.Game_table[3][3][1]==0 && s.Game_table[3][3][2]==0 && s.Game_table[3][3][3]==0)
                if(s.number[4]<2)
                    Draw_piece(200,500,-1);
                else if (s.Game_table[3][3][2]==0 && s.Game_table[3][3][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(200,500,-2);
        if(v[3]<0 && v[7]<0)
            if(s.Game_table[2][2][1]==0 && s.Game_table[2][2][2]==0 && s.Game_table[2][2][3]==0)
                if(s.number[4]<2)
                    Draw_piece(380,380,-1);
                else if (s.Game_table[2][2][2]==0 && s.Game_table[2][2][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(380,380,-2);
        if(v[5]<0 && v[7]<0)
            if(s.Game_table[1][3][1]==0 && s.Game_table[1][3][2]==0 && s.Game_table[1][3][3]==0)
                if(s.number[4]<2)
                    Draw_piece(500,200,-1);
                else if (s.Game_table[1][3][2]==0 && s.Game_table[1][3][3]==0)
                    if(s.number[5]<2)
                        Draw_piece(500,200,-2);
    }
}
//Functia care sterge piesa de pe tabla.
void black_square(int i, int j)
{
    int height=595-155,l=(595-155)/3;
    int width=height/3;
    if(i==1 && j==1)
    {
        readimagefile("1.bmp",155+l/2-40,155+width/2-50,155+l-10,155+width-5);
    }
    if(i==1 && j==2)
    {
        readimagefile("2.bmp",155+l+l/2-40,155+width/2-50,155+2*l-10,155+width-5);
    }
    if(i==1 && j==3)
    {
        readimagefile("3.bmp",155+2*l+l/2-40,155+width/2-50,155+3*l-10,155+width-5);
    }
    if(i==2 && j==1)
    {
        readimagefile("4.bmp",155+l/2-40,155+width+width/2-50,155+l-10,155+2*width-5);
    }
    if(i==2 && j==2)
    {
        readimagefile("5.bmp",155+l+l/2-40,155+width+width/2-50,155+2*l-10,155+2*width-5);
    }
    if(i==2 && j==3)
    {
        readimagefile("6.bmp",155+2*l+l/2-40,155+width+width/2-50,155+3*l-10,155+2*width-5);
    }
    if(i==3 && j==1)
    {
        readimagefile("7.bmp",155+l/2-40,155+2*width+width/2-50,155+l-10,155+3*width-5);
    }
    if(i==3 && j==2)
    {
        readimagefile("8.bmp",155+l+l/2-40,155+2*width+width/2-50,155+2*l-10,155+3*width-5);
    }
    if(i==3 && j==3)
    {
        readimagefile("9.bmp",155+2*l+l/2-40,155+2*width+width/2-50,155+3*l-10,155+3*width-5);
    }

}
//Functie care transorma pozitia de pe tabla in coordonate x si y.
void Poz_Table_ij(int i, int j, int &x, int &y)
{
    if(i==1&&j==1)
    {
        x=220;
        y=220;
    }
    if(i==1&&j==2)
    {
        x=380;
        y=220;
    }
    if(i==1&&j==3)
    {
        x=530;
        y=220;
    }
    if(i==2&&j==1)
    {
        x=220;
        y=380;
    }
    if(i==2&&j==2)
    {
        x=380;
        y=380;
    }
    if(i==2&&j==3)
    {
        x=530;
        y=380;
    }
    if(i==3&&j==1)
    {
        x=220;
        y=530;
    }
    if(i==3&&j==2)
    {
        x=380;
        y=530;
    }
    if(i==3&&j==3)
    {
        x=530;
        y=530;
    }
}
//Functie care determina pozitia pe tabla in functie de click.
void Poz_Table(int x1, int y1, int &i, int &j)
{
    int height=595-155,l=(595-155)/3;
    int width=height/3;
    if(x1 >=155 && x1<=155+l-5 && y1>=155 && y1<=155+width-5)
    {
        i=1;
        j=1;
    }
    if(x1 >=155+l+5 && x1<=155+2*l-5 && y1>=155 && y1<=155+width-5)
    {
        i=1;
        j=2;
    }
    if(x1 >=155+2*l && x1<=155+3*l && y1>=155 && y1<=155+width-5)
    {
        i=1;
        j=3;
    }
    if(x1 >=155 && x1<=155+l-5 && y1>=155+width && y1<=155+2*width-5)
    {
        i=2;
        j=1;
    }
    if(x1 >=155+l && y1<=155+2*l-5 && y1>=155+width && y1<=155+2*width-5)
    {
        i=2;
        j=2;
    }
    if(x1 >=155+2*l && x1<=155+3*l-5 && y1>=155+width && y1<=155+2*width-5)
    {
        i=2;
        j=3;
    }
    if(x1 >=155 && x1<=155+l-5 && y1>=155+2*width && y1<=155+3*width-5)
    {
        i=3;
        j=1;
    }
    if(x1 >=155+l && x1<=155+2*l-5 && y1>=155+2*width && y1<=155+3*width-5)
    {
        i=3;
        j=2;
    }
    if(x1 >=155+2*l && x1<=155+3*l-5 && y1>=155+2*width && y1<=155+3*width-5)
    {
        i=3;
        j=3;
    }
}
//Functie care deseneaza piese pe tabla.
void Draw_piece(int pozx,int pozy,int p)
{
    int i,j,x,y;
    int height=595-155,l=(595-155)/3;
    int width=height/3;
    Poz_Table(pozx,pozy,i,j);
    Poz_Table_ij(i,j,x,y);
    //1//
    if(pozx >=155 && pozx<=155+l-5 && pozy>=155 && pozy<=155+width-5)
    {
        if(p==1 && abs(s.Game_table[1][1][1])==0 && abs(s.Game_table[1][1][2])==0 && abs(s.Game_table[1][1][3])==0)
        {
            s.ok1=1;
            s.Game_table[1][1][1]=1;
            readimagefile("portocalie_mica.gif",155+l/2,155+width/2-10,155+l-50,155+width-5);
            s.turn++;
            s.number[1]++;
        }
        if(p==2 && abs(s.Game_table[1][1][2])==0 && abs(s.Game_table[1][1][3])==0)
        {
            s.ok1=1;
            s.Game_table[1][1][2]=1;
            readimagefile("portocalie_mijlocie.gif",155+l/2-20,155+width/2-30,155+l-30,155+width-5);
            s.turn++;
            s.number[2]++;
        }
        if(p==3 && abs(s.Game_table[1][1][3])==0)
        {
            s.ok1=1;
            s.Game_table[1][1][3]=1;
            readimagefile("portocalie_mare.gif",155+l/2-40,155+width/2-50,155+l-10,155+width-5);
            s.turn++;
            s.number[3]++;
        }
        if(p==-1 && abs(s.Game_table[1][1][1])==0 && abs(s.Game_table[1][1][2])==0 && abs(s.Game_table[1][1][3])==0)
        {
            s.ok1=1;
            s.Game_table[1][1][1]=-1;
            readimagefile("albastra_mica.gif",155+l/2,155+width/2-10,155+l-50,155+width-5);
            s.turn++;
            s.number[4]++;
        }
        if(p==-2 && abs(s.Game_table[1][1][2])==0 && abs(s.Game_table[1][1][3])==0)
        {
            s.ok1=1;
            s.Game_table[1][1][2]=-1;
            readimagefile("albastra_mijlocie.gif",155+l/2-20,155+width/2-30,155+l-30,155+width-5);
            s.turn++;
            s.number[5]++;
        }
        if(p==-3 && abs(s.Game_table[1][1][3])==0)
        {
            s.ok1=1;
            s.Game_table[1][1][3]=-1;
            readimagefile("albastra_mare.gif",155+l/2-40,155+width/2-50,155+l-10,155+width-5);
            s.turn++;
            s.number[6]++;
        }
    }
    //2//
    if(pozx >=155+l+5 && pozx<=155+2*l-5 && pozy>=155 && pozy<=155+width-5)
    {
        if(p==1 && abs(s.Game_table[1][2][1])==0 && abs(s.Game_table[1][2][2])==0 && abs(s.Game_table[1][2][3])==0)
        {
            s.ok1=1;
            s.Game_table[1][2][1]=1;
            readimagefile("portocalie_mica.gif",155+l+l/2,155+width/2-10,155+2*l-50,155+width-5);
            s.turn++;
            s.number[1]++;
        }
        if(p==2&& abs(s.Game_table[1][2][2])==0 && abs(s.Game_table[1][2][3])==0)
        {
            s.ok1=1;
            s.Game_table[1][2][2]=1;
            readimagefile("portocalie_mijlocie.gif",155+l+l/2-20,155+width/2-30,155+2*l-30,155+width-5);
            s.turn++;
            s.number[2]++;
        }

        if(p==3&& abs(s.Game_table[1][2][3])==0)
        {
            s.ok1=1;
            s.Game_table[1][2][3]=1;
            readimagefile("portocalie_mare.gif",155+l+l/2-40,155+width/2-50,155+2*l-10,155+width-5);
            s.turn++;
            s.number[3]++;
        }

        if(p==-1&&abs(s.Game_table[1][2][1])==0 && abs(s.Game_table[1][2][2])==0 && abs(s.Game_table[1][2][3])==0)
        {
            s.ok1=1;
            s.Game_table[1][2][1]=-1;
            readimagefile("albastra_mica.gif",155+l+l/2,155+width/2-10,155+2*l-50,155+width-5);
            s.turn++;
            s.number[4]++;
        }

        if(p==-2&& abs(s.Game_table[1][2][2])==0 && abs(s.Game_table[1][2][3])==0)
        {
            s.ok1=1;
            s.Game_table[1][2][2]=-1;
            readimagefile("albastra_mijlocie.gif",155+l+l/2-20,155+width/2-30,155+2*l-30,155+width-5);
            s.turn++;
            s.number[5]++;
        }

        if(p==-3&& abs(s.Game_table[1][2][3])==0)
        {
            s.ok1=1;
            s.Game_table[1][2][3]=-1;
            readimagefile("albastra_mare.gif",155+l+l/2-40,155+width/2-50,155+2*l-10,155+width-5);
            s.turn++;
            s.number[6]++;
        }
    }
    //3//
    if(pozx >=155+2*l && pozx<=155+3*l && pozy>=155 && pozy<=155+width-5)
    {
        if(p==1 && abs(s.Game_table[1][3][1])==0 && abs(s.Game_table[1][3][2])==0 && abs(s.Game_table[1][3][3])==0)
        {
            s.ok1=1;
            s.Game_table[1][3][1]=1;
            readimagefile("portocalie_mica.gif",155+2*l+l/2,155+width/2-10,155+3*l-50,155+width-5);
            s.turn++;
            s.number[1]++;
        }
        if(p==2&& abs(s.Game_table[1][3][2])==0 && abs(s.Game_table[1][3][3])==0)
        {
            s.ok1=1;
            s.Game_table[1][3][2]=1;
            readimagefile("portocalie_mijlocie.gif",155+2*l+l/2-20,155+width/2-30,155+3*l-30,155+width-5);
            s.turn++;
            s.number[2]++;
        }
        if(p==3&& abs(s.Game_table[1][3][3])==0)
        {
            s.ok1=1;
            s.Game_table[1][3][3]=1;
            readimagefile("portocalie_mare.gif",155+2*l+l/2-40,155+width/2-50,155+3*l-10,155+width-5);
            s.turn++;
            s.number[3]++;
        }
        if(p==-1&&abs(s.Game_table[1][3][1])==0 && abs(s.Game_table[1][3][2])==0 && abs(s.Game_table[1][3][3])==0)
        {
            s.ok1=1;
            s.Game_table[1][3][1]=-1;
            readimagefile("albastra_mica.gif",155+2*l+l/2,155+width/2-10,155+3*l-50,155+width-5);
            s.turn++;
            s.number[4]++;
        }
        if(p==-2&& abs(s.Game_table[1][3][2])==0 && abs(s.Game_table[1][3][3])==0)
        {
            s.ok1=1;
            s.Game_table[1][3][2]=-1;
            readimagefile("albastra_mijlocie.gif",155+2*l+l/2-20,155+width/2-30,155+3*l-30,155+width-5);
            s.turn++;
            s.number[5]++;
        }
        if(p==-3&& abs(s.Game_table[1][3][3])==0)
        {
            s.ok1=1;
            s.Game_table[1][3][3]=-1;
            readimagefile("albastra_mare.gif",155+2*l+l/2-40,155+width/2-50,155+3*l-10,155+width-5);
            s.turn++;
            s.number[6]++;
        }
    }
    //4//
    if(pozx >=155 && pozx<=155+l-5 && pozy>=155+width && pozy<=155+2*width-5)
    {
        if(p==1 && abs(s.Game_table[2][1][1])==0 && abs(s.Game_table[2][1][2])==0 && abs(s.Game_table[2][1][3])==0)
        {
            s.ok1=1;
            s.Game_table[2][1][1]=1;
            readimagefile("portocalie_mica.gif",155+l/2,155+width+width/2-10,155+l-50,155+2*width-5);
            s.turn++;
            s.number[1]++;
        }
        if(p==2&& abs(s.Game_table[2][1][2])==0 && abs(s.Game_table[2][1][3])==0)
        {
            s.ok1=1;
            s.Game_table[2][1][2]=1;
            readimagefile("portocalie_mijlocie.gif",155+l/2-20,155+width+width/2-30,155+l-30,155+2*width-5);
            s.turn++;
            s.number[2]++;
        }
        if(p==3&& abs(s.Game_table[2][1][3])==0)
        {
            s.ok1=1;
            s.Game_table[2][1][3]=1;
            readimagefile("portocalie_mare.gif",155+l/2-40,155+width+width/2-50,155+l-10,155+2*width-5);
            s.turn++;
            s.number[3]++;
        }
        if(p==-1 && abs(s.Game_table[2][1][1])==0 && abs(s.Game_table[2][1][2])==0 && abs(s.Game_table[2][1][3])==0)
        {
            s.ok1=1;
            s.Game_table[2][1][1]=-1;
            readimagefile("albastra_mica.gif",155+l/2,155+width+width/2-10,155+l-50,155+2*width-5);
            s.turn++;
            s.number[4]++;
        }
        if(p==-2&& abs(s.Game_table[2][1][2])==0 && abs(s.Game_table[2][1][3])==0)
        {
            s.ok1=1;
            s.Game_table[2][1][2]=-1;
            readimagefile("albastra_mijlocie.gif",155+l/2-20,155+width+width/2-30,155+l-30,155+2*width-5);
            s.turn++;
            s.number[5]++;
        }
        if(p==-3&& abs(s.Game_table[2][1][3])==0)
        {
            s.ok1=1;
            s.Game_table[2][1][3]=-1;
            readimagefile("albastra_mare.gif",155+l/2-40,155+width+width/2-50,155+l-10,155+2*width-5);
            s.turn++;
            s.number[6]++;
        }
    }
    //5//
    if(pozx >=155+l && pozx<=155+2*l-5 && pozy>=155+width && pozy<=155+2*width-5)
    {
        if(p==1 && abs(s.Game_table[2][2][1])==0 && abs(s.Game_table[2][2][2])==0 && abs(s.Game_table[2][2][3])==0)
        {
            s.ok1=1;
            s.Game_table[2][2][1]=1;
            readimagefile("portocalie_mica.gif",155+l+l/2,155+width+width/2-10,155+2*l-50,155+2*width-5);
            s.turn++;
            s.number[1]++;
        }
        if(p==2&& abs(s.Game_table[2][2][2])==0 && abs(s.Game_table[2][2][3])==0)
        {
            s.ok1=1;
            s.Game_table[2][2][2]=1;
            readimagefile("portocalie_mijlocie.gif",155+l+l/2-20,155+width+width/2-30,155+2*l-30,155+2*width-5);
            s.turn++;
            s.number[2]++;
        }
        if(p==3&& abs(s.Game_table[2][2][3])==0)
        {
            s.ok1=1;
            s.Game_table[2][2][3]=1;
            readimagefile("portocalie_mare.gif",155+l+l/2-40,155+width+width/2-50,155+2*l-10,155+2*width-5);
            s.turn++;
            s.number[3]++;
        }
        if(p==-1&& abs(s.Game_table[2][2][1])==0 && abs(s.Game_table[2][2][2])==0 && abs(s.Game_table[2][2][3])==0)
        {
            s.ok1=1;
            s.Game_table[2][2][1]=-1;
            readimagefile("albastra_mica.gif",155+l+l/2,155+width+width/2-10,155+2*l-50,155+2*width-5);
            s.turn++;
            s.number[4]++;
        }
        if(p==-2&& abs(s.Game_table[2][2][2])==0 && abs(s.Game_table[2][2][3])==0)
        {
            s.ok1=1;
            s.Game_table[2][2][2]=-1;
            readimagefile("albastra_mijlocie.gif",155+l+l/2-20,155+width+width/2-30,155+2*l-30,155+2*width-5);
            s.turn++;
            s.number[5]++;
        }
        if(p==-3&& abs(s.Game_table[2][2][3])==0)
        {
            s.ok1=1;
            s.Game_table[2][2][3]=-1;
            readimagefile("albastra_mare.gif",155+l+l/2-40,155+width+width/2-50,155+2*l-10,155+2*width-5);
            s.turn++;
            s.number[6]++;
        }
    }
    //6//
    if(pozx >=155+2*l && pozx<=155+3*l-5 && pozy>=155+width && pozy<=155+2*width-5)
    {
        if(p==1 && abs(s.Game_table[2][3][1])==0 && abs(s.Game_table[2][3][2])==0 && abs(s.Game_table[2][3][3])==0)
        {
            s.ok1=1;
            s.Game_table[2][3][1]=1;
            readimagefile("portocalie_mica.gif",155+2*l+l/2,155+width+width/2-10,155+3*l-50,155+2*width-5);
            s.turn++;
            s.number[1]++;
        }
        if(p==2&& abs(s.Game_table[2][3][2])==0 && abs(s.Game_table[2][3][3])==0)
        {
            s.ok1=1;
            s.Game_table[2][3][2]=1;
            readimagefile("portocalie_mijlocie.gif",155+2*l+l/2-20,155+width+width/2-30,155+3*l-30,155+2*width-5);
            s.turn++;
            s.number[2]++;
        }
        if(p==3&& abs(s.Game_table[2][3][3])==0)
        {
            s.ok1=1;
            s.Game_table[2][3][3]=1;
            readimagefile("portocalie_mare.gif",155+2*l+l/2-40,155+width+width/2-50,155+3*l-10,155+2*width-5);
            s.turn++;
            s.number[3]++;
        }
        if(p==-1&& abs(s.Game_table[2][3][1])==0 && abs(s.Game_table[2][3][2])==0 && abs(s.Game_table[2][3][3])==0)
        {
            s.ok1=1;
            s.Game_table[2][3][1]=-1;
            readimagefile("albastra_mica.gif",155+2*l+l/2,155+width+width/2-10,155+3*l-50,155+2*width-5);
            s.turn++;
            s.number[4]++;
        }
        if(p==-2&& abs(s.Game_table[2][3][2])==0 && abs(s.Game_table[2][3][3])==0)
        {
            s.ok1=1;
            s.Game_table[2][3][2]=-1;
            readimagefile("albastra_mijlocie.gif",155+2*l+l/2-20,155+width+width/2-30,155+3*l-30,155+2*width-5);
            s.turn++;
            s.number[5]++;
        }
        if(p==-3&& abs(s.Game_table[2][3][3])==0)
        {
            s.ok1=1;
            s.Game_table[2][3][3]=-1;
            readimagefile("albastra_mare.gif",155+2*l+l/2-40,155+width+width/2-50,155+3*l-10,155+2*width-5);
            s.turn++;
            s.number[6]++;
        }
    }
    //7//
    if(pozx >=155 && pozx<=155+l-5 && pozy>=155+2*width && pozy<=155+3*width-5)
    {
        if(p==1 && abs(s.Game_table[3][1][1])==0 && abs(s.Game_table[3][1][2])==0 && abs(s.Game_table[3][1][3])==0)
        {
            s.ok1=1;
            s.Game_table[3][1][1]=1;
            readimagefile("portocalie_mica.gif",155+l/2,155+2*width+width/2-10,155+l-50,155+3*width-5);
            s.turn++;
            s.number[1]++;
        }
        if(p==2&& abs(s.Game_table[3][1][2])==0 && abs(s.Game_table[3][1][3])==0)
        {
            s.ok1=1;
            s.Game_table[3][1][2]=1;
            readimagefile("portocalie_mijlocie.gif",155+l/2-20,155+2*width+width/2-30,155+l-30,155+3*width-5);
            s.turn++;
            s.number[2]++;
        }
        if(p==3 && abs(s.Game_table[3][1][3])==0)
        {
            s.ok1=1;
            s.Game_table[3][1][3]=1;
            readimagefile("portocalie_mare.gif",155+l/2-40,155+2*width+width/2-50,155+l-10,155+3*width-5);
            s.turn++;
            s.number[3]++;
        }
        if(p==-1 && abs(s.Game_table[3][1][1])==0 && abs(s.Game_table[3][1][2])==0 && abs(s.Game_table[3][1][3])==0)
        {
            s.ok1=1;
            s.Game_table[3][1][1]=-1;
            readimagefile("albastra_mica.gif",155+l/2,155+2*width+width/2-10,155+l-50,155+3*width-5);
            s.turn++;
            s.number[4]++;
        }
        if(p==-2&& abs(s.Game_table[3][1][2])==0 && abs(s.Game_table[3][1][3])==0)
        {
            s.ok1=1;
            s.Game_table[3][1][2]=-1;
            readimagefile("albastra_mijlocie.gif",155+l/2-20,155+2*width+width/2-30,155+l-30,155+3*width-5);
            s.turn++;
            s.number[5]++;
        }
        if(p==-3 && abs(s.Game_table[3][1][3])==0)
        {
            s.ok1=1;
            s.Game_table[3][1][3]=-1;
            readimagefile("albastra_mare.gif",155+l/2-40,155+2*width+width/2-50,155+l-10,155+3*width-5);
            s.turn++;
            s.number[6]++;
        }
    }
    //8//
    if(pozx >=155+l && pozx<=155+2*l-5 && pozy>=155+2*width && pozy<=155+3*width-5)
    {
        if(p==1 && abs(s.Game_table[3][2][1])==0 && abs(s.Game_table[3][2][2])==0 && abs(s.Game_table[3][2][3])==0)
        {
            s.ok1=1;
            s.Game_table[3][2][1]=1;
            readimagefile("portocalie_mica.gif",155+l+l/2,155+2*width+width/2-10,155+2*l-50,155+3*width-5);
            s.turn++;
            s.number[1]++;
        }
        if(p==2&& abs(s.Game_table[3][2][2])==0 && abs(s.Game_table[3][2][3])==0)
        {
            s.ok1=1;
            s.Game_table[3][2][2]=1;
            readimagefile("portocalie_mijlocie.gif",155+l+l/2-20,155+2*width+width/2-30,155+2*l-30,155+3*width-5);
            s.turn++;
            s.number[2]++;
        }
        if(p==3&& abs(s.Game_table[3][2][3])==0)
        {
            s.ok1=1;
            s.Game_table[3][2][3]=1;
            readimagefile("portocalie_mare.gif",155+l+l/2-40,155+2*width+width/2-50,155+2*l-10,155+3*width-5);
            s.turn++;
            s.number[3]++;
        }
        if(p==-1 && abs(s.Game_table[3][2][1])==0 && abs(s.Game_table[3][2][2])==0 && abs(s.Game_table[3][2][3])==0)
        {
            s.ok1=1;
            s.Game_table[3][2][1]=-1;
            readimagefile("albastra_mica.gif",155+l+l/2,155+2*width+width/2-10,155+2*l-50,155+3*width-5);
            s.turn++;
            s.number[4]++;
        }
        if(p==-2&& abs(s.Game_table[3][2][2])==0 && abs(s.Game_table[3][2][3])==0)
        {
            s.ok1=1;
            s.Game_table[3][2][2]=-1;
            readimagefile("albastra_mijlocie.gif",155+l+l/2-20,155+2*width+width/2-30,155+2*l-30,155+3*width-5);
            s.turn++;
            s.number[5]++;
        }
        if(p==-3&& abs(s.Game_table[3][2][3])==0)
        {
            s.ok1=1;
            s.Game_table[3][2][3]=-1;
            readimagefile("albastra_mare.gif",155+l+l/2-40,155+2*width+width/2-50,155+2*l-10,155+3*width-5);
            s.turn++;
            s.number[6]++;
        }
    }
    //9//
    if(pozx >=155+2*l && pozx<=155+3*l-5 && pozy>=155+2*width && pozy<=155+3*width-5)
    {
        if(p==1 && abs(s.Game_table[3][3][1])==0 && abs(s.Game_table[3][3][2])==0 && abs(s.Game_table[3][3][3])==0)
        {
            s.ok1=1;
            s.Game_table[3][3][1]=1;
            readimagefile("portocalie_mica.gif",155+2*l+l/2,155+2*width+width/2-10,155+3*l-50,155+3*width-5);
            s.turn++;
            s.number[1]++;
        }
        if(p==2&& abs(s.Game_table[3][3][2])==0 && abs(s.Game_table[3][3][3])==0)
        {
            s.ok1=1;
            s.Game_table[3][3][2]=1;
            readimagefile("portocalie_mijlocie.gif",155+2*l+l/2-20,155+2*width+width/2-30,155+3*l-30,155+3*width-5);
            s.turn++;
            s.number[2]++;
        }
        if(p==3&& abs(s.Game_table[3][3][3])==0)
        {
            s.ok1=1;
            s.Game_table[3][3][3]=1;
            readimagefile("portocalie_mare.gif",155+2*l+l/2-40,155+2*width+width/2-50,155+3*l-10,155+3*width-5);
            s.turn++;
            s.number[3]++;
        }
        if(p==-1&& abs(s.Game_table[3][3][1])==0 && abs(s.Game_table[3][3][2])==0 && abs(s.Game_table[3][3][3])==0)
        {
            s.ok1=1;
            s.Game_table[3][3][1]=-1;
            readimagefile("albastra_mica.gif",155+2*l+l/2,155+2*width+width/2-10,155+3*l-50,155+3*width-5);
            s.turn++;
            s.number[4]++;
        }
        if(p==-2&& abs(s.Game_table[3][3][2])==0 && abs(s.Game_table[3][3][3])==0)
        {
            s.ok1=1;
            s.Game_table[3][3][2]=-1;
            readimagefile("albastra_mijlocie.gif",155+2*l+l/2-20,155+2*width+width/2-30,155+3*l-30,155+3*width-5);
            s.turn++;
            s.number[5]++;
        }
        if(p==-3&& abs(s.Game_table[3][3][3])==0)
        {
            s.ok1=1;
            s.Game_table[3][3][3]=-1;
            readimagefile("albastra_mare.gif",155+2*l+l/2-40,155+2*width+width/2-50,155+3*l-10,155+3*width-5);
            s.turn++;
            s.number[6]++;
        }
    }
    winner();
}
//Functie care muta piese de pe tabla in alt loc.
void Draw_piece1(int x1,int y1,int x,int y)
{
    int i,j,p1=0,p2=0;
    Poz_Table(x1,y1,i,j);
    if(abs(s.Game_table[i][j][3])==1 && abs(s.Game_table[i][j][2])==1)
    {
        p1=3*s.Game_table[i][j][3];
        p2=2*s.Game_table[i][j][2];

    }
    else
    {
        if(abs(s.Game_table[i][j][3])==1 && abs(s.Game_table[i][j][1])==1)
        {
            p1=3*s.Game_table[i][j][3];
            p2=1*s.Game_table[i][j][1];

        }
        else
        {
            if(abs(s.Game_table[i][j][3])==1)
                p1=3*s.Game_table[i][j][3];
            else
            {
                if(abs(s.Game_table[i][j][2])==1 && abs(s.Game_table[i][j][1])==1)
                {
                    p1=2*s.Game_table[i][j][2];
                    p2=1*s.Game_table[i][j][1];
                }
                else
                {
                    if(abs(s.Game_table[i][j][2])==1)
                        p1=2*s.Game_table[i][j][2];
                    else
                    {
                        if(abs(s.Game_table[i][j][1])==1)
                        {
                            p1=1*s.Game_table[i][j][1];
                        }
                    }
                }
            }
        }
    }
    if(abs(s.Game_table[i][j][1]==0)&&abs(s.Game_table[i][j][2]==0)&&abs(s.Game_table[i][j][3]==0))
    {
        if(s.limba==0)
            readimagefile("wrong.bmp",28,60,134,95);
        else
            readimagefile("wrongr.bmp",28,60,134,95);
        delay(2000);
        readimagefile("wrong1.bmp",28,60,134,95);
    }
    if( (s.turn%2==0 && p1<0) || (s.turn%2==1 && p1>0))
    {
        if(s.limba==0)
            readimagefile("wrong.bmp",28,60,134,95);
        else
            readimagefile("wrongr.bmp",28,60,134,95);
        delay(2000);
        readimagefile("wrong1.bmp",28,60,134,95);
    }
    else
    {
        int r=0;
        int i1,j1;
        Poz_Table(x,y,i1,j1);
        if(abs(s.Game_table[i1][j1][3])==1)
            r=3;
        else if(abs(s.Game_table[i1][j1][2])==1)
            r=2;
        else if(abs(s.Game_table[i1][j1][1])==1)
            r=1;
        else r=0;
        if(abs(p1)<=r)
        {
            if(s.limba==0)
                readimagefile("wrong.bmp",28,60,134,95);
            else
                readimagefile("wrongr.bmp",28,60,134,95);
            delay(2000);
            readimagefile("wrong1.bmp",28,60,134,95);
        }
        else
        {
            s.Game_table[i][j][abs(p1)]=0;
            if(p1>0)
                s.number[p1]--;
            if(p1<0)
                s.number[3-p1]--;
            black_square(i,j);
            Draw_piece(x,y,p1);
            if(p2!=0)
            {
                s.Game_table[i][j][abs(p2)]=0;
                Draw_piece(x1,y1,p2);
                s.turn--;
                if(p2>0)
                    s.number[p2]--;
                if(p2<0)
                    s.number[3-p2]--;
            }
        }

    }
}
//Functie care geneareaza un loc de pe tabla la intamplare.
void Random(int &i,int &j)
{
    do
    {
        i=rand()%4;
    }
    while(i==0);
    do
    {
        j=rand()%4;
    }
    while(j==0);
}
//Functia pentru calculator sa mute o piesa la dificultatea easy.
void Move_computer_easy()
{
    int i=0,j=0,x,y;
    Random(i,j);
    Poz_Table_ij(i,j,x,y);
    if(s.number[4]<2)
        if(abs(s.Game_table[i][j][1])==0 && abs(s.Game_table[i][j][3])==0 && abs(s.Game_table[i][j][2])==0)
            Draw_piece(x,y,-1);
        else Move_computer_easy();
    else if(s.number[5]<2)
        if(abs(s.Game_table[i][j][3])==0 && abs(s.Game_table[i][j][2])==0)
            Draw_piece(x,y,-2);
        else Move_computer_easy();
    else if(s.number[6]<2)
        if(abs(s.Game_table[i][j][3])==0)
            Draw_piece(x,y,-3);
        else Move_computer_easy();
    else
    {
        Random(i,j);
        Poz_Table_ij(i,j,x,y);
        if(s.Game_table[i][j][3]==-1)
        {
            int i1=0,j1=0,x1,y1;
            Random(i1,j1);
            if(abs(s.Game_table[i1][j1][3])==0)
            {
                Poz_Table_ij(i1,j1,x1,y1);
                Draw_piece1(x,y,x1,y1);
            }
            else Move_computer_easy();
        }
    }
}
//Analog mediu
void Move_computer_medium(int &nr)
{
    int i,j,k,x,y;
    if(s.nr==0)
    {
        if(s.Game_table[2][2][3]==0)
        {
            Draw_piece(380,380,-3);
        }
        else
        {
            do
            {
                i=rand()%4;
            }
            while(!(i==1 || i==3));
            do
            {
                j=rand()%4;
            }
            while(!(j==1|| j==3));
            Poz_Table_ij(i,j,x,y);
            Draw_piece(x,y,-3);
        }
    }
    if (s.nr==1)
    {
        verify_player();
        if(s.number[6]==1)
        {
            int ok=0,i1=0,j1=0,x1,y1;
            do
            {
                Random(i1,j1);
                if(s.Game_table[i1][j1][3]==0)
                {
                    Poz_Table_ij(i1,j1,x1,y1);
                    Draw_piece(x1,y1,-3);
                    ok=1;
                }
            }
            while(ok==0);
        }

    }
    if(s.nr==2 || s.nr==3)
    {
        verify_player();
        verify_computer();
        if(s.ok1==0)
        {
            int ok=0,i1=0,j1=0,x1,y1;
            do
            {
                Random(i1,j1);
                if(s.Game_table[i1][j1][3]==0&& s.Game_table[i1][j1][2]==0)
                {
                    Poz_Table_ij(i1,j1,x1,y1);
                    Draw_piece(x1,y1,-2);
                    ok=1;
                }
            }
            while(ok==0);
        }
    }
    if(s.nr>=4)
    {
        verify_player();
        int i1,j1,x1=0,y1=0,x2=0,y2=0,i2,j2,ok4=0,aux1,aux2;
        for(i1=1; i1<=3; i1++)
            for(j1=1; j1<=3; j1++)
                if(s.Game_table[i1][j1][3]==-1)
                {
                    aux1=i1;
                    aux2=j1;
                    i1=4;
                    j1=4;
                }
        Poz_Table_ij(aux1,aux2,x1,y1);
        for(i2=1; i2<=3; i2++)
            for(j2=1; j2<=3; j2++)
                if(s.Game_table[i2][j2][2]==1 && abs(s.Game_table[i2][j2][3])==0)
                {
                    ok4=1;
                    aux1=i2;
                    aux2=j2;
                    i2=4;
                    j2=4;
                }
        if(ok4==0)
        {
            for(i2=1; i2<=3; i2++)
                for(j2=1; j2<=3; j2++)
                    if(s.Game_table[i2][j2][1]==1&& abs(s.Game_table[i2][j2][2])==1 && abs(s.Game_table[i2][j2][3])==0)
                    {
                        ok4=1;
                        aux1=i2;
                        aux2=j2;
                        i2=4;
                        j2=4;
                    }
        }
        if(ok4==0)
        {
            verify_computer();
            for(i2=1; i2<=3; i2++)
                for(j2=1; j2<=3; j2++)
                    if(s.Game_table[i2][j2][1]==0&& abs(s.Game_table[i2][j2][2])==1 && abs(s.Game_table[i2][j2][3])==0)
                    {
                        ok4=1;
                        aux1=i2;
                        aux2=j2;
                        i2=4;
                        j2=4;
                    }
        }
        Poz_Table_ij(aux1,aux2,x2,y2);
        Draw_piece1(x1,y1,x2,y2);
    }
    if(s.ok1==1)
        s.nr++;
}
// Analog hard
void Move_computer_hard(int &nr)
{
    int i,j,k,x,y;
    if(s.nr==0)
    {
        if(s.Game_table[2][2][3]==0)
        {
            Draw_piece(380,380,-3);
        }
        else
        {
            do
            {
                i=rand()%4;
            }
            while(!(i==1 || i==3));
            do
            {
                j=rand()%4;
            }
            while(!(j==1|| j==3));
            Poz_Table_ij(i,j,x,y);
            Draw_piece(x,y,-3);
        }
    }
    if (s.nr==1)
    {
        verify_player();
        if(s.number[6]==1)
        {
            int ok=0,i1=0,j1=0,x1,y1;
            do
            {
                Random(i1,j1);
                if(s.Game_table[i1][j1][3]==0)
                {
                    Poz_Table_ij(i1,j1,x1,y1);
                    Draw_piece(x1,y1,-3);
                    ok=1;
                }
            }
            while(ok==0);
        }

    }
    if(s.nr==2 || s.nr==3)
    {
        verify_computer();
        verify_player();
        if(s.ok1==0)
        {
            int ok=0,i1=0,j1=0,x1,y1;
            do
            {
                Random(i1,j1);
                if(s.Game_table[i1][j1][3]==0&& s.Game_table[i1][j1][2]==0)
                {
                    Poz_Table_ij(i1,j1,x1,y1);
                    Draw_piece(x1,y1,-2);
                    ok=1;
                }
            }
            while(ok==0);
        }
    }
    if(s.nr>=4)
    {
        int i1,j1,x1=0,y1=0,x2=0,y2=0,i2,j2,ok4=0,aux1,aux2;
        for(i1=1; i1<=3; i1++)
            for(j1=1; j1<=3; j1++)
                if(s.Game_table[i1][j1][3]==-1)
                {
                    aux1=i1;
                    aux2=j1;
                    i1=4;
                    j1=4;
                }
        Poz_Table_ij(aux1,aux2,x1,y1);
        for(i2=1; i2<=3; i2++)
            for(j2=1; j2<=3; j2++)
                if(s.Game_table[i2][j2][2]==1 && abs(s.Game_table[i2][j2][3])==0)
                {
                    ok4=1;
                    aux1=i2;
                    aux2=j2;
                    i2=4;
                    j2=4;
                }
        if(ok4==0)
        {
            for(i2=1; i2<=3; i2++)
                for(j2=1; j2<=3; j2++)
                    if(s.Game_table[i2][j2][1]==1&& abs(s.Game_table[i2][j2][2])==1 && abs(s.Game_table[i2][j2][3])==0)
                    {
                        ok4=1;
                        aux1=i2;
                        aux2=j2;
                        i2=4;
                        j2=4;
                    }
        }
        if(ok4==0)
        {
            verify_computer();
            for(i2=1; i2<=3; i2++)
                for(j2=1; j2<=3; j2++)
                    if(s.Game_table[i2][j2][1]==0&& abs(s.Game_table[i2][j2][2])==1 && abs(s.Game_table[i2][j2][3])==0)
                    {
                        ok4=1;
                        aux1=i2;
                        aux2=j2;
                        i2=4;
                        j2=4;
                    }
        }
        Poz_Table_ij(aux1,aux2,x2,y2);
        Draw_piece1(x1,y1,x2,y2);
    }
    if(s.ok1==1)
        s.nr++;
}
void Menu();
//Functia pentru a muta o piesa
void Move_piece()
{
    int x,y,i,j,ok=0;
    int x1=0, y1=0;
    int click=false;
    int p=0;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            click=true;
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(x>=40 && x<=80 && y>=100 && y<=275)
            {
                if(s.number[1]<2 && s.turn%2==0)
                {
                    p=1;
                    ok=1;
                }
                else
                {
                    if(s.number[1]>=2)
                    {
                        if(s.limba==0)
                            readimagefile("limit.bmp",170,50,585,135);
                        else
                            readimagefile("limitr.bmp",170,50,585,135);
                        delay(2000);
                        readimagefile("limit1.bmp",170,50,585,135);
                    }
                    else
                    {
                        if(s.limba==0)
                            readimagefile("wrong.bmp",28,60,134,95);
                        else
                            readimagefile("wrongr.bmp",28,60,134,95);
                        delay(2000);
                        readimagefile("wrong1.bmp",28,60,134,95);
                    }

                }
            }
            else if(x>=25 && x<=100 && y>=325 && y<=425)
            {
                if(s.number[2]<2 && s.turn%2==0)
                {
                    p=2;
                    ok=1;
                }
                else
                {
                    if(s.number[2]>=2)
                    {
                        if(s.limba==0)
                            readimagefile("limit.bmp",170,50,585,135);
                        else
                            readimagefile("limitr.bmp",170,50,585,135);
                        delay(2000);
                        readimagefile("limit1.bmp",170,50,585,135);
                    }
                    else
                    {
                        if(s.limba==0)
                            readimagefile("wrong.bmp",28,60,134,95);
                        else
                            readimagefile("wrongr.bmp",28,60,134,95);
                        delay(2000);
                        readimagefile("wrong1.bmp",28,60,134,95);
                    }

                }
            }
            else if(x>=25 && x<=100 && y>=460 && y<=610)
            {
                if(s.number[3]<2 && s.turn%2==0)
                {
                    p=3;
                    ok=1;
                }
                else
                {
                    if(s.number[3]>=2)
                    {
                        if(s.limba==0)
                            readimagefile("limit.bmp",170,50,585,135);
                        else
                            readimagefile("limitr.bmp",170,50,585,135);
                        delay(2000);
                        readimagefile("limit1.bmp",170,50,585,135);
                    }
                    else
                    {
                        if(s.limba==0)
                            readimagefile("wrong.bmp",28,60,134,95);
                        else
                            readimagefile("wrongr.bmp",28,60,134,95);
                        delay(2000);
                        readimagefile("wrong1.bmp",28,60,134,95);
                    }
                }
            }
            else if(x>=660 && x<=700 && y>=100 && y<=275)
            {
                if(s.number[4]<2 && s.turn%2==1)
                {
                    p=-1;
                    ok=1;
                }
                else
                {
                    if(s.number[4]>=2)
                    {
                        if(s.limba==0)
                            readimagefile("limit.bmp",170,50,585,135);
                        else
                            readimagefile("limitr.bmp",170,50,585,135);
                        delay(2000);
                        readimagefile("limit1.bmp",170,50,585,135);
                    }
                    else
                    {
                        if(s.limba==0)
                            readimagefile("wrong.bmp",28,60,134,95);
                        else
                            readimagefile("wrongr.bmp",28,60,134,95);
                        delay(2000);
                        readimagefile("wrong1.bmp",28,60,134,95);
                    }
                }
            }
            else if(x>=650 && x<=710 && y>=325 && y<=425)
            {
                if(s.number[5]<2 && s.turn%2==1)
                {
                    p=-2;
                    ok=1;
                }
                else
                {
                    if(s.number[5]>=2)
                    {
                        if(s.limba==0)
                            readimagefile("limit.bmp",170,50,585,135);
                        else
                            readimagefile("limitr.bmp",170,50,585,135);
                        delay(2000);
                        readimagefile("limit1.bmp",170,50,585,135);
                    }
                    else
                    {
                        if(s.limba==0)
                            readimagefile("wrong.bmp",28,60,134,95);
                        else
                            readimagefile("wrongr.bmp",28,60,134,95);
                        delay(2000);
                        readimagefile("wrong1.bmp",28,60,134,95);
                    }
                }
            }
            else if(x>=640 && x<=720 && y>=460 && y<=610)
            {
                if(s.number[6]<2 && s.turn%2==1)
                {
                    p=-3;
                    ok=1;
                }
                else
                {
                    if(s.number[6]>=2)
                    {
                        if(s.limba==0)
                            readimagefile("limit.bmp",170,50,585,135);
                        else
                            readimagefile("limitr.bmp",170,50,585,135);
                        delay(2000);
                        readimagefile("limit1.bmp",170,50,585,135);
                    }
                    else
                    {
                        if(s.limba==0)
                            readimagefile("wrong.bmp",28,60,134,95);
                        else
                            readimagefile("wrongr.bmp",28,60,134,95);
                        delay(2000);
                        readimagefile("wrong1.bmp",28,60,134,95);
                    }
                }
            }
            else if(x>=155 && x<=595 && y>=155 && y<=595)
            {
                if((s.turn%2==0) || (s.turn%2==1))
                {
                    x1=x;
                    y1=y;
                    ok=1;
                }
                else
                {
                    if(s.limba==0)
                        readimagefile("wrong.bmp",28,60,134,95);
                    else
                        readimagefile("wrongr.bmp",28,60,134,95);
                    delay(2000);
                    readimagefile("wrong1.bmp",28,60,134,95);
                }
            }
            else if(x>=0 && x<=80 && y>=0 && y<=40)
                Menu();
            else if(!(x>=155 && x<=595 && y>=155 && y<=595)&& p==0)
            {
                if(s.limba==0)
                    readimagefile("wrong.bmp",28,60,134,95);
                else
                    readimagefile("wrongr.bmp",28,60,134,95);
                delay(2000);
                readimagefile("wrong1.bmp",28,60,134,95);
            }
        }
    while (!click);
    if(ok)
    {
        click=false;
        do
            if(ismouseclick(WM_LBUTTONDOWN) && !click)
            {
                click=true;
                clearmouseclick(WM_LBUTTONDOWN);
                x=mousex();
                y=mousey();

            }
        while (!click);
        if(x1==0 && y1==0)
            Draw_piece(x,y,p);
        else Draw_piece1(x1,y1,x,y);
    }

}
//Functia de desenare a tablei de joc
void Table()
{

    if(s.limba==0)
    {
        readimagefile("fundal12.jpg",0,0,800,800);
        readimagefile("tura1.bmp",36,91,142,131);
    }
    else
    {
        readimagefile("fundal12r.jpg",0,0,800,800);
        readimagefile("tura1r.bmp",36,91,142,131);
    }
    readimagefile("sageata.bmp",0,0,80,40);
    int i=300;
    setcolor(COLOR(210,105,30));
    for(int n=0; n<=5; n++)
    {
        line(155,i,595,i);
        line(155,i+150,595,i+150);
        i++;
    }
    i=i-5;
    setcolor(GREEN);
    for(int n=0; n<=5; n++)
    {
        line(i,155,i,595);
        line(i+150,155,i+150,595);
        i++;
    }
    i=i-5;
    readimagefile("portocalie_mica.gif",40,200,80,275);
    readimagefile("portocalie_mijlocie.gif",25,325,85,425);
    readimagefile("portocalie_mare.gif",25,460,100,610);
    readimagefile("albastra_mica.gif",660,200,700,275);
    readimagefile("albastra_mijlocie.gif",650,325,710,425);
    readimagefile("albastra_mare.gif",640,460,720,610);
}
void Play_Computer_easy()
{
    cleardevice();
    Table();
    s.turn=0;
    if(s.game==2)
        Current_game();
    else reset();
    s.game=2;
    s.win=0;
    do
    {
        s.ok1=0;
        readimagefile("tura.bmp",36,90,142,130);
        if(s.turn%2==0)
        {
            if(s.limba==0)
                readimagefile("tura1.bmp",36,90,142,130);
            else readimagefile("tura1r.bmp",36,90,142,130);
            Move_piece();
        }
        else
        {
            if(s.limba==0)
                readimagefile("computer.jpg",36,90,142,130);
            else readimagefile("computerr.jpg",36,90,142,130);
            delay(1500);
            Move_computer_easy();
        }
    }
    while(s.win==0);
}
void Play_Computer_medium()
{
    cleardevice();
    Table();
    s.turn=0;
    if(s.game==3)
        Current_game();
    else reset();
    s.win=0;
    s.game=3;
    do
    {
        s.ok1=0;
        readimagefile("tura.bmp",36,90,142,130);
        if(s.turn%2==0)
        {
            if(s.limba==0)
                readimagefile("tura1.bmp",36,90,142,130);
            else readimagefile("tura1r.bmp",36,90,142,130);
            Move_piece();
        }
        else
        {
            if(s.limba==0)
                readimagefile("computer.jpg",36,90,142,130);
            else readimagefile("computerr.jpg",36,90,142,130);
            delay(1500);
            Move_computer_medium(s.nr);
        }
    }
    while(s.win==0);
}
void Play_Computer_hard()
{
    cleardevice();
    Table();
    s.turn=0;
    if(s.game==4)
        Current_game();
    else reset();
    s.game=4;
    s.win=0;
    do
    {
        s.ok1=0;
        readimagefile("tura.bmp",36,90,142,130);
        if(s.turn%2==0)
        {
            if(s.limba==0)
                readimagefile("tura1.bmp",36,90,142,130);
            else readimagefile("tura1r.bmp",36,90,142,130);
            Move_piece();
        }
        else
        {
            if(s.limba==0)
                readimagefile("computer.jpg",36,90,142,130);
            else readimagefile("computerr.jpg",36,90,142,130);
            delay(1500);
            Move_computer_hard(s.nr);
        }
    }
    while(s.win==0);
}
// Functia pentru jucator vs jucator
void Play()
{
    cleardevice();
    Table();
    s.turn=0;
    if(s.game==1)
        Current_game();
    else reset();
    s.game=1;
    s.win=0;
    do
    {
        s.ok1=0;
        readimagefile("tura.bmp",36,90,142,130);
        if(s.turn%2==0)
        {
            if(s.limba==0)
                readimagefile("tura1.bmp",36,91,142,131);
            else readimagefile("tura1r.bmp",36,90,142,130);
        }
        else
        {
            if(s.limba==0)
                readimagefile("tura2.bmp",36,91,142,131);
            else readimagefile("tura2r.bmp",36,90,142,130);
        }
        while(s.ok1==0)
            Move_piece();
    }
    while(s.win==0);
}
#endif
