#ifndef XSI0_H_INCLUDED
#define XSI0_H_INCLUDED

#include <iostream>
#include <graphics.h>
#include <winbgim.h>
using namespace std;

int a[3][3],turn = 0,computer = 0;

void desenareTerenXsiO()
{
    settextstyle(10,0,6);
    setlinestyle(0,0,3);
    int x1,x2,y1,y2;
    int w=textwidth("Tic Tac Toe"),h;
    outtextxy((1200-w)/2,80,"Tic Tac Toe");
    x1=390;
    x2=810;
    y1=165;
    y2=585;

    rectangle(x1,y1,x2,y2);

    x1 = x1 + 140;
    x2 = x1;
	line(x1,y1,x2,y2);

	x1 = x1 + 140;
	x2 = x1;
	line(x1,y1,x2,y2);

    y1 = y1 + 140;
    y2 = y1;
    x1 = 390;
    x2 = 810;
	line(x1,y1,x2,y2);

    y1 = y1 + 140;
    y2 = y1;
	line(x1,y1,x2,y2);
}
void deseneazaX(int x, int y)
{
    line(x-50,y-50,x+50,y+50);
    line(x+50,y-50,x-50,y+50);
}
void deseneazaO(int x, int y)
{
    circle(x,y,50);
}
void deseneazaXsiO()
{
    int i,j;
    int x1,x2,y1,y2;
    x1=390;
    x2=810;
    y1=165;
    y2=585;
    for(i=0;i<=2;i++)
        for(j=0;j<=2;j++)
            {
                if(a[i][j]==1)
                    deseneazaX(x1+j*140+70,y1+i*140+70);
                if(a[i][j]==2)
                    deseneazaO(x1+j*140+70,y1+i*140+70);
            }
}
int meciTerminat()
{
    int i,j,X=0,O=0;
    for(i=0;i<=2;i++)
    {
        X=0;O=0;
        for(j=0;j<=2;j++)
            if(a[i][j] != 0)
                if(a[i][j] == 1)
                    X++;
                else
                    O++;
        if(X == 3)
            return 1;
        if(O == 3)
            return 2;
    }
    for(j=0;j<=2;j++)
    {
        X=0;O=0;
        for(i=0;i<=2;i++)
            if(a[i][j] != 0)
                if(a[i][j] == 1)
                    X++;
                else
                    O++;
        if(X == 3)
            return 1;
        if(O == 3)
            return 2;
    }
    X=0;O=0;
    for(i=0;i<=2;i++)
        if(a[i][i] != 0)
            if(a[i][i] == 1)
                X++;
            else
                O++;
    if(X == 3)
        return 1;
    if(O == 3)
        return 2;
    X=0;O=0;
    for(i=0;i<=2;i++)
        if(a[i][2-i] != 0)
            if(a[i][2-i] == 1)
                X++;
            else
                O++;
    if(X == 3)
        return 1;
    if(O == 3)
        return 2;
    return 0;
}
void butoaneMatrice()
{
    int i,j;
    int x1,x2,y1,y2;
    int w,my=600;
    int px,py;
    x1=390;
    x2=810;
    y1=165;
    y2=585;
    while(1)
    {
        px = mousex();
        py = mousey();
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            for(i=0;i<=2;i++)
                for(j=0;j<=2;j++)
                     if(px >= x1+140*j && px <= x1+140*(j+1) && py >= y1+140*i && py <= y1+140*(i+1) && a[i][j] == 0)
                        {
                            turn++;
                            if(turn%2==0)
                                a[i][j] = 2;
                            else
                                a[i][j] = 1;
                        }
            deseneazaXsiO();
            if(meciTerminat()==1)
            {
                w = textwidth("Meciul a fost castigat de X");
                outtextxy(600-w/2,my,"Meciul a fost castigat de X");
                break;
            }
            if(meciTerminat()==2)
            {
                w = textwidth("Meciul a fost castigat de O");
                outtextxy(600-w/2,my,"Meciul a fost castigat de O");
                break;
            }
            if(turn == 9)
            {
                w = textwidth("Meciul s-a terminat la egalitate");
                outtextxy(600-w/2,my,"Meciul s-a terminat la egalitate");
                break;
            }

        }
    }
}
void initializareXsiO()
{
    int i,j;
    desenareTerenXsiO();
    desenareTerenXsiO();
    butoaneMatrice();
    for(i=0;i<=2;i++)
        for(j=0;j<=2;j++)
            a[i][j] = 0;
    turn = 0;
    Sleep(3000);
}

#endif

