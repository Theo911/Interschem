#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include "evaluare_infixat.h"
#include "citireDinFereastraGrafica.h"
#include "Xsi0.h"
#include <cmath>
#include <math.h>

using namespace std;


fstream f("date.txt");

int nrTotalCulori=10;
int red[100]={90,244,255,153,15,246,244,66,44,218};
int green[100]={148,180,167,60,77,182,223,234,95,160};
int blue[100]={149,26,129,223,25,13,78,221,45,61};
int red1[100]={0,20,91,194,94,148,205,0,151,97};
int green1[100]={128,61,14,5,194,147,181,32,188,98};
int blue1[100]={128,89,45,82,124,152,153,63,98,71};
int ExistaStart = 0, schema, nrBlocuri=0;
int r = 90, g = 148, b = 149;
int r1 = 0, g1 = 128, b1 = 128;
int nrCuloare = 0;

struct bloc
{
    int x, y;
    char id;
    int val;
    char numeVar;
    char sirDeAfisat[MAX_STR];
    char decizie[MAX_STR];
    bloc* urm, * Rurm, * Turm;
};

bloc* p = new bloc;
bloc* prim = p;
bloc* ultim = p;


int esteBlocNul(bloc* a)
{
	return (a == NULL);
}

void initBlocuri()
{
    if (!esteBlocNul(p))
	{
		p = NULL;
	}

    if (!esteBlocNul(prim))
	{
		prim = NULL;
	}

    if (!esteBlocNul(ultim))
	{
		ultim = NULL;
	}
}


void init_bgi()
{
    int inaltime = 750, latime = 1200;
    initwindow(latime, inaltime, "Interschem");
}


void fereastraStart()
{
    char s[500];
    int inaltimebuton = 83, latimebuton = 600;
    int xText, yText;
    setbkcolor(COLOR(r1, g1, b1));
    cleardevice();
    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    setbkcolor(COLOR(r, g, b));

    settextstyle(3, HORIZ_DIR, 3);
    bar(300, 83, 900, 166);
    strcpy(s, "SCHEMA NOUA");
    xText = 300 + (latimebuton - textwidth(s)) / 2;
    yText = 83 + (inaltimebuton - textheight(s)) / 2;
    outtextxy(xText, yText, s);

    bar(300, 207, 900, 290);
    strcpy(s, "MAXIMUL DINTRE 2 NUMERE");
    xText = 300 + (latimebuton - textwidth(s)) / 2;
    yText = 207 + (inaltimebuton - textheight(s)) / 2;
    outtextxy(xText, yText, s);

    bar(300, 333, 900, 416);
    strcpy(s, "SUMA PRIMELOR N NUMERE NATURALE");
    xText = 300 + (latimebuton - textwidth(s)) / 2;
    yText = 333 + (inaltimebuton - textheight(s)) / 2;
    outtextxy(xText, yText, s);

    bar(300, 457, 900, 540);
    strcpy(s, "CEVA CREATIV");
    xText = 300 + (latimebuton - textwidth(s)) / 2;
    yText = 457 + (inaltimebuton - textheight(s)) / 2;
    outtextxy(xText, yText, s);

    bar(300, 581, 900, 664);
    strcpy(s, "EXIT");
    xText = 300 + (latimebuton - textwidth(s)) / 2;
    yText = 581 + (inaltimebuton - textheight(s)) / 2;
    outtextxy(xText, yText, s);

    latimebuton = 100;
    inaltimebuton = 100;
    bar(1090,10,1190,110);
    strcpy(s,"THEME");
    xText = 1090 + (latimebuton - textwidth(s)) / 2;
    yText = 10 + (inaltimebuton - textheight(s)) / 2;
    outtextxy(xText,yText, s);
}

bool butonSchemaNouaApasat(int x, int y)
{
    return x >= 300 && x <= 900 && y >= 83 && y <= 166;
}

bool butonMaximulDintreDouaNumereApasat(int x, int y)
{
    return x >= 300 && x <= 900 && y >= 207 && y <= 290;
}

bool butonSumaPrimelorNNumereNaturaleApasat(int x, int y)
{
    return x >= 300 && x <= 900 && y >= 333 && y <= 416;
}

bool butonCevaCreativApasat(int x, int y)
{
    return x >= 300 && x <= 900 && y >= 457 && y <= 540;
}

bool butonExitApasat(int x, int y)
{
    return x >= 300 && x <= 900 && y >= 581 && y <= 664;
}

bool butonThemeApasat(int x, int y)
{
    return x >= 1090 && x <=1190 && y >= 10 && y <= 110;
}

int returneazaFereastraStartNumarulDeOrdineAlButonuluiApasat(int x, int y)
{

    if (butonSchemaNouaApasat(x, y))
        return 1;
    if (butonMaximulDintreDouaNumereApasat(x, y))
        return 2;
    if (butonSumaPrimelorNNumereNaturaleApasat(x, y))
        return 3;
    if (butonCevaCreativApasat(x, y))
        return 4;
    if (butonThemeApasat(x, y))
        return 5;
    if (butonExitApasat(x, y))
        return 0;
    return 6;
}

void sageata(int x, int y, int angle)
{
    int w = 12, h = 24;
    double theta = (double)(angle%360)*M_PI/180.0;
    int dx = w/2;
    int dy = h/2;
    int point[8] = {
        (-dx*cos(theta) - dy*sin(theta) + x),
        (-dx*sin(theta) + dy*cos(theta) + y),
        (dx*cos(theta) - dy*sin(theta) + x),
        (dx*sin(theta) + dy* cos(theta) + y),
        (dx*cos(theta) + dy*sin(theta) + x),
        (dx*sin(theta) - dy*cos(theta) + y),
        (-dx*cos(theta) + dy* sin(theta) + x),
        (-dx*sin(theta) - dy*cos(theta) + y)
    };
    line(x,y,point[4],point[5]);
    line(x,y,point[6],point[7]);
}
void linie(int x1, int y1, int x2, int y2)
{
    int angle = 0;
    angle = atan2(y2 - y1, x2 - x1)*180/M_PI-90;
    line(x1,y1,x2,y2);
    sageata(x2,y2,angle);
}


void afisareVariabile()
{
    setbkcolor(COLOR(r1, g1, b1));
    setfillstyle(SOLID_FILL, COLOR(r1, g1, b1));
    bar(21, 552, 780, 729);

    int nrVariabile = 0;
    bloc* aux = prim;
    while(aux->urm != NULL)
    {
        if(aux->id == 'i')
        {
            nrVariabile++;
        }
        aux = aux->urm;
    }

    if(nrVariabile == 0)
    {
        //outtextxy(30, 565, "A = 0"); etc
        int dx = 0;
        char aux[] = "  = 0";
        for(char i = 'A'; i <= 'I'; i++)
        {
            aux[0] = i;
            outtextxy(60 + dx, 565, aux);
            dx += 80;
        }

        dx = 0;
        int dy = 50;
        for(char i = 'J'; i <= 'R'; i++)
        {
            aux[0] = i;
            outtextxy(60 + dx, 565 + dy, aux);
            dx += 80;
        }

        dx = 0;
        dy = 100;
        for(char i = 'S'; i <= 'Z'; i++)
        {
            aux[0] = i;
            outtextxy(60 + dx, 565 + dy, aux);
            dx += 80;
        }
    }
    else
    {
        int k = 0;
        int dx = 0;
        for(char i = 'A'; i <= 'I'; i++)
        {
            char aux[] = "  = ";
            aux[0] = i;

            aux[4] = 0;
            aux[5] = '\0';
            bloc * q = prim;
            while(q)
            {
                if(q->numeVar == i && q->id != 'o')
                {
                    char val_char[11];
                    itoa(q->val, val_char, 10);
                    strcat(aux + 4, val_char);
                }
                q = q->urm;
            }

            outtextxy(60 + dx, 565, aux);
            dx += 80;
        }

        dx = 0;
        int dy = 50;
        for(char i = 'J'; i <= 'R'; i++)
        {
            char aux[] = "  = ";
            aux[0] = i;

            aux[4] = 0;
            aux[5] = '\0';
            bloc * q = prim;
            while(q)
            {
                if(q->numeVar == i && q->id != 'o')
                {
                    char val_char[11];
                    itoa(q->val, val_char, 10);
                    strcat(aux + 4, val_char);
                }
                q = q->urm;
            }

            outtextxy(60 + dx, 565 + dy, aux);
            dx += 80;
        }

        dx = 0;
        dy = 100;
        for(char i = 'S'; i <= 'Z'; i++)
        {
            char aux[] = "  = ";
            aux[0] = i;

            aux[4] = 0;
            aux[5] = '\0';
            bloc * q = prim;
            while(q)
            {
                if(q->numeVar == i && q->id != 'o')
                {
                    char val_char[11];
                    itoa(q->val, val_char, 10);
                    strcat(aux + 4, val_char);
                }
                q = q->urm;
            }

            outtextxy(60 + dx, 565 + dy, aux);
            dx += 80;
        }
    }

    setbkcolor(COLOR(r, g, b));
    setfillstyle(SOLID_FILL, COLOR(r, g, b));
}


void meniuSchemaNoua();

void citesteCoordonateMouseSchemaNoua();

void stergeLista();

void deseneazaBloc(int Px, int Py, char identificator);

void inputValoriLista(int px, int py, char identificator);

void deseneazaEcran();

void incarcaMaximulDintre2Numere()
{
    ifstream fin("maximulDintre2Numere.txt");
    int i=1;
    int x1, y1,conditie,cnt;
    char identificator;
    bloc *tmp = prim;
    bloc *tmp2 = prim;
    fin >> nrBlocuri;
    for(i=1;i<=nrBlocuri;i++)
    {
        fin >> x1 >> y1 >> identificator;
        inputValoriLista(x1, y1, identificator);
    }
    for(i=1;i<=nrBlocuri;i++)
    {
        fin >> conditie;
        if(conditie)
            {
                fin >> x1 >> y1;
                tmp = prim;
                while(tmp->urm != NULL)
                {
                    if(tmp->x == x1 && tmp->y == y1)
                    {
                        tmp2->Rurm = tmp;
                        break;
                    }
                    tmp = tmp->urm;
                }
            }
        fin >> conditie;
        if(conditie)
            {
                fin >> x1 >> y1;
                tmp = prim;
                while(tmp->urm != NULL)
                {
                    if(tmp->x == x1 && tmp->y == y1)
                    {
                        tmp2->Turm = tmp;
                        break;
                    }
                    tmp = tmp->urm;
                }
            }
        tmp2 = tmp2->urm;
    }
    fin.close();
}


void cppMaximulDintre2Numere()
{
    setfillstyle(SOLID_FILL, COLOR(r1, g1, b1));
    setbkcolor(COLOR(r1, g1, b1));
    char s[101];
    int xText = 801;
    int yText = 301;
    int latimebuton = 378;
    int inaltimebuton = 428;

    strcpy(s, "CODIFICARE C++");
    xText += (latimebuton - textwidth(s)) / 2;
    yText += 10;
    outtextxy(xText, yText, s);

    xText = 801 + 10;
    yText = 301 + 10;

    yText += textheight(s);
    strcpy(s, "#include <iostream>");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "using namespace std;");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "\n");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "int main()");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "{");
    outtextxy(xText, yText, s);

    xText += 20;
    yText += textheight(s);
    strcpy(s, "int a, b, m;");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "cin >> a;");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "cin >> b;");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "if(a > b)");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "{");
    outtextxy(xText, yText, s);

    xText += 20;
    yText += textheight(s);
    strcpy(s, "m = a;");
    outtextxy(xText, yText, s);
    xText -= 20;

    yText += textheight(s);
    strcpy(s, "}");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "else");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "{");
    outtextxy(xText, yText, s);

    xText += 20;
    yText += textheight(s);
    strcpy(s, "m = b;");
    outtextxy(xText, yText, s);
    xText -= 20;

    yText += textheight(s);
    strcpy(s, "}");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "cout << m;");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "return 0;");
    outtextxy(xText, yText, s);

    xText -= 20;
    yText += textheight(s);
    strcpy(s, "}");
    outtextxy(xText, yText, s);

    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    setbkcolor(COLOR(r, g, b));
}


int maxim(int a, int b)
{
    if(a > b)
    {
        return a;
    }
    return b;
}


void rezolvaMaximulDintre2Numere(int a, int b)
{
    int xText = 820;
    int yText = 250;
    if(a > b)
    {
        char aux[101];
        itoa(a, aux, 10);
        outtextxy(xText, yText, aux);
    }
    else
    {
        char aux[101];
        itoa(b, aux, 10);
        outtextxy(xText, yText, aux);
    }
}


void incarcaSumaPrimelorNNumere()
{
    ifstream fin("SumaPrimelorNNumere.txt");
    int i=1;
    int x1, y1,conditie,cnt;
    char identificator;
    bloc *tmp = prim;
    bloc *tmp2 = prim;
    fin >> nrBlocuri;
    for(i=1;i<=nrBlocuri;i++)
    {
        fin >> x1 >> y1 >> identificator;
        inputValoriLista(x1, y1, identificator);
    }
    for(i=1;i<=nrBlocuri;i++)
    {
        fin >> conditie;
        if(conditie)
            {
                fin >> x1 >> y1;
                tmp = prim;
                while(tmp->urm != NULL)
                {
                    if(tmp->x == x1 && tmp->y == y1)
                    {
                        tmp2->Rurm = tmp;
                        break;
                    }
                    tmp = tmp->urm;
                }
            }
        fin >> conditie;
        if(conditie)
            {
                fin >> x1 >> y1;
                tmp = prim;
                while(tmp->urm != NULL)
                {
                    if(tmp->x == x1 && tmp->y == y1)
                    {
                        tmp2->Turm = tmp;
                        break;
                    }
                    tmp = tmp->urm;
                }
            }
        tmp2 = tmp2->urm;
    }
    fin.close();
}


void cppSumaPrimelorNNumere()
{
    setbkcolor(COLOR(r1, g1, b1));
    char s[101];
    int xText = 801;
    int yText = 301;
    int latimebuton = 378;
    int inaltimebuton = 428;

    strcpy(s, "CODIFICARE C++");
    xText += (latimebuton - textwidth(s)) / 2;
    yText += 10;
    outtextxy(xText, yText, s);

    xText = 801 + 10;
    yText = 301 + 10;

    yText += textheight(s);
    strcpy(s, "#include <iostream>");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "using namespace std;");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "\n");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "int main()");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "{");
    outtextxy(xText, yText, s);

    xText += 20;
    yText += textheight(s);
    strcpy(s, "int n, i, s;");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "cin >> n;");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "i = 0;");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "s = 0;");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "while(i < n)");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "{");
    outtextxy(xText, yText, s);

    xText += 20;
    yText += textheight(s);
    strcpy(s, "i++;");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "s += i;");
    outtextxy(xText, yText, s);

    xText -= 20;
    yText += textheight(s);
    strcpy(s, "}");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "cout << s;");
    outtextxy(xText, yText, s);

    yText += textheight(s);
    strcpy(s, "return 0;");
    outtextxy(xText, yText, s);

    xText -= 20;
    yText += textheight(s);
    strcpy(s, "}");
    outtextxy(xText, yText, s);

    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    setbkcolor(COLOR(r, g, b));
}


int sumaPrimelorNNumere(int a)
{
    int s = a + 1;
    s *= a;
    s /= 2;
    return s;
}


void Credits()
{
    bar(0, 0, 1249, 750);
    while(1)
    {
        if (ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_RBUTTONDOWN))
        {
           break;
        }

        settextstyle(10, HORIZ_DIR, 3);

        int xText = 0;
        int yText = 10;
        int latimeEcran = 1200;

        char text[MAX_STR];

        strcpy(text, "Credits");
        xText = (latimeEcran - textwidth(text)) / 2;
        outtextxy(xText, yText, text);
        yText += textheight(text);

        yText += 150;

        strcpy(text, "Membrii echipei: Burca Theodor si Catiru Stefan");
        xText = (latimeEcran - textwidth(text)) / 2;
        outtextxy(xText, yText, text);
        yText += textheight(text);

        strcpy(text, "Structurile de date folosite : Amandoi");
        xText = (latimeEcran - textwidth(text)) / 2;
        outtextxy(xText, yText, text);
        yText += textheight(text);

        strcpy(text, "Fisiere : In principal Stefan, cu ajutorul lui Theodor");
        xText = (latimeEcran - textwidth(text)) / 2;
        outtextxy(xText, yText, text);
        yText += textheight(text);

        strcpy(text, "Rularea schemei : In principal Theodor, cu ajutorul lui Stefan");
        xText = (latimeEcran - textwidth(text)) / 2;
        outtextxy(xText, yText, text);
        yText += textheight(text);

        strcpy(text, "Executia informatiei din interiorul fiecarui bloc : Theodor");
        xText = (latimeEcran - textwidth(text)) / 2;
        outtextxy(xText, yText, text);
        yText += textheight(text);

        strcpy(text, "Editarea continutului blocurilor : Theodor");
        xText = (latimeEcran - textwidth(text)) / 2;
        outtextxy(xText, yText, text);
        yText += textheight(text);

        strcpy(text, "Desenarea legaturilor dintre blocuri : Stefan");
        xText = (latimeEcran - textwidth(text)) / 2;
        outtextxy(xText, yText, text);
        yText += textheight(text);

        strcpy(text, "Mutarea blocurilor : Stefan");
        xText = (latimeEcran - textwidth(text)) / 2;
        outtextxy(xText, yText, text);
        yText += textheight(text);

        strcpy(text, "X si O : Stefan");
        xText = (latimeEcran - textwidth(text)) / 2;
        outtextxy(xText, yText, text);
        yText += textheight(text);

        strcpy(text, "Functia 'Theme' : Stefan");
        xText = (latimeEcran - textwidth(text)) / 2;
        outtextxy(xText, yText, text);
        yText += textheight(text);

        strcpy(text, "Evaluatorul matematic : Theodor");
        xText = (latimeEcran - textwidth(text)) / 2;
        outtextxy(xText, yText, text);
        yText += textheight(text);

        strcpy(text, "Elemente de grafica : Amandoi");
        xText = (latimeEcran - textwidth(text)) / 2;
        outtextxy(xText, yText, text);
        yText += textheight(text);

        strcpy(text, "Functionalitatea butoanelor : Amandoi");
        xText = (latimeEcran - textwidth(text)) / 2;
        outtextxy(xText, yText, text);
        yText += textheight(text);

        strcpy(text, "Codificare C++ (maximul dintre 2 numere, suma primelor n numere naturale) : Theodor");
        xText = (latimeEcran - textwidth(text)) / 2;
        outtextxy(xText, yText, text);
        yText += textheight(text);
    }
    closegraph();
}


void citesteCoordonateMouseFereastraStart()
{
    while (1)
    {
        Sleep(4);
        int x, y;
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x = mousex();
            y = mousey();

            int zona = returneazaFereastraStartNumarulDeOrdineAlButonuluiApasat(x, y);

            if (zona < 1)
            {
                //cout << "Gata\n";
                Credits();
                break;
            }
            else
            {
                //cout << zona << '\n';
                if (zona == 1)
                {
                    schema = 1;
                    meniuSchemaNoua();
                    afisareVariabile();
                    citesteCoordonateMouseSchemaNoua();
                    break;
                }
                if(zona == 2)
                {
                    //maximul dintre 2 numere
                    meniuSchemaNoua();
                    afisareVariabile();
                    incarcaMaximulDintre2Numere();
                    cppMaximulDintre2Numere();
                    deseneazaEcran();
                    ExistaStart = 1;
                    schema = 2;
                    citesteCoordonateMouseSchemaNoua();
                    break;
                }
                if(zona == 3)
                {
                    //suma primelor n numere naturale
                    meniuSchemaNoua();
                    afisareVariabile();
                    incarcaSumaPrimelorNNumere();
                    cppSumaPrimelorNNumere();
                    deseneazaEcran();
                    ExistaStart = 1;
                    schema = 3;
                    citesteCoordonateMouseSchemaNoua();
                    break;
                }
                if(zona == 4)
                {
                    setbkcolor(COLOR(r1, g1, b1));
                    cleardevice();
                    initializareXsiO();
                    fereastraStart();
                    citesteCoordonateMouseFereastraStart();
                    break;
                }
                if(zona == 5)
                {
                    nrCuloare++;
                    r = red[nrCuloare%(nrTotalCulori)];
                    g = green[nrCuloare%(nrTotalCulori)];
                    b = blue[nrCuloare%(nrTotalCulori)];
                    r1 = red1[nrCuloare%(nrTotalCulori)];
                    g1 = green1[nrCuloare%(nrTotalCulori)];
                    b1 = blue1[nrCuloare%(nrTotalCulori)];
                    cleardevice();
                    fereastraStart();
                }
            }
        }
        if(ismouseclick(WM_RBUTTONDOWN))
        {
            x = mousex();
            y = mousey();
            int zona = returneazaFereastraStartNumarulDeOrdineAlButonuluiApasat(x, y);
            if(zona == 5)
            {
                if(nrCuloare == 0)
                    nrCuloare = nrTotalCulori;
                nrCuloare--;
                r = red[nrCuloare%(nrTotalCulori)];
                g = green[nrCuloare%(nrTotalCulori)];
                b = blue[nrCuloare%(nrTotalCulori)];
                r1 = red1[nrCuloare%(nrTotalCulori)];
                g1 = green1[nrCuloare%(nrTotalCulori)];
                b1 = blue1[nrCuloare%(nrTotalCulori)];
                cleardevice();
                fereastraStart();
            }
            clearmouseclick(WM_RBUTTONDOWN);
        }
    }
}


void desenareSchemaNoua()
{
    setcolor(WHITE);

    rectangle(20, 20, 780, 530);        /// sus stanga
    rectangle(801, 20, 1179, 279);      /// sus dreapta
    rectangle(20, 551, 780, 729);       /// jos stanga
    rectangle(801, 301, 1179, 729);     /// jos dreapta

    /* Fill colours */
    setfillstyle(SOLID_FILL, COLOR(r1, g1, b1));
    floodfill(100, 100, WHITE);         /// sus stanga
    floodfill(1000, 200, WHITE);        /// sus dreapta
    floodfill(100, 700, WHITE);         /// jos stanga
    floodfill(1000, 500, WHITE);        /// jos dreapta
}


void deseneazaBloc(int Px, int Py, char identificator)
{
    int inaltimebuton = 40, latimebuton = 100;
    int xText, yText;
    int x1, y1, x2, y2;
    x1 = Px - latimebuton / 2;
    y1 = Py - inaltimebuton / 2;
    x2 = Px + latimebuton / 2;
    y2 = Py + inaltimebuton / 2;
    char s[20];
    bar(x1, y1, x2, y2);
    switch (identificator)
    {
    case 'S':
        strcpy(s, "START");
        break;
    case 'i':
        strcpy(s, "INPUT");
        break;
    case 'o':
        strcpy(s, "OUTPUT");
        break;
    case 'd':
        strcpy(s, "IF");
        break;
    case 'a':
        strcpy(s, "ASSIGN");
        break;
    case 's':
        strcpy(s, "STOP");
        break;
    }
    xText = x1 + (latimebuton - textwidth(s)) / 2;
    yText = y1 + (inaltimebuton - textheight(s)) / 2 - 10;
    outtextxy(xText, yText, s);
}


void adaugaButoaneDesenareSchemaNoua()
{
    char s[500];

    int xText, yText;

    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    setbkcolor(COLOR(r, g, b));

    settextstyle(3, HORIZ_DIR, 1);

    deseneazaBloc(100, 50, 'S');
    deseneazaBloc(220, 50, 'i');
    deseneazaBloc(340, 50, 'o');
    deseneazaBloc(460, 50, 'd');
    deseneazaBloc(580, 50, 'a');
    deseneazaBloc(700, 50, 's');

    int latimebuton = 150, inaltimebuton = 45;

    bar(827, 30, 977, 75);
    strcpy(s, "DRAWING");
    xText = 827 + (latimebuton - textwidth(s)) / 2;
    yText = 30 + (inaltimebuton - textheight(s)) / 2 - textheight(s) / 2;
    outtextxy(xText, yText, s);
    strcpy(s, "FINISHED");
    xText = 827 + (latimebuton - textwidth(s)) / 2;
    yText = 30 + (inaltimebuton - textheight(s)) / 2 + textheight(s) / 2;
    outtextxy(xText, yText, s);

    bar(1003, 30, 1153, 75);
    strcpy(s, "GO");
    xText = 1003 + (latimebuton - textwidth(s)) / 2;
    yText = 30 + (inaltimebuton - textheight(s)) / 2 - textheight(s) / 2;
    outtextxy(xText, yText, s);
    strcpy(s, "BACK");
    xText = 1003 + (latimebuton - textwidth(s)) / 2;
    yText = 30 + (inaltimebuton - textheight(s)) / 2 + textheight(s) / 2;
    outtextxy(xText, yText, s);

    bar(1003, 100, 1153, 145);
    strcpy(s, "OPEN");
    xText = 1003 + (latimebuton - textwidth(s)) / 2;
    yText = 100 + (inaltimebuton - textheight(s)) / 2 - textheight(s) / 2;
    outtextxy(xText, yText, s);
    strcpy(s, "FILE");
    xText = 1003 + (latimebuton - textwidth(s)) / 2;
    yText = 100 + (inaltimebuton - textheight(s)) / 2 + textheight(s) / 2;
    outtextxy(xText, yText, s);

    bar(827, 100, 977, 145);
    strcpy(s, "SAVE");
    xText = 827 + (latimebuton - textwidth(s)) / 2;
    yText = 100 + (inaltimebuton - textheight(s)) / 2 - textheight(s) / 2;
    outtextxy(xText, yText, s);
    strcpy(s, "FILE");
    xText = 827 + (latimebuton - textwidth(s)) / 2;
    yText = 100 + (inaltimebuton - textheight(s)) / 2 + textheight(s) / 2;
    outtextxy(xText, yText, s);
}


void meniuSchemaNoua()
{
    setbkcolor(BLACK);
    cleardevice();
    desenareSchemaNoua();
    setbkcolor(COLOR(r, g, b));
    adaugaButoaneDesenareSchemaNoua();
    //afisareVariabile();
}


bool butonStartApasat(int x, int y)
{
    return x >= 50 && x <= 150 && y >= 30 && y <= 70;
}

bool butonInputApasat(int x, int y)
{
    return x >= 170 && x <= 270 && y >= 30 && y <= 70;
}

bool butonOutputApasat(int x, int y)
{
    return x >= 290 && x <= 390 && y >= 30 && y <= 70;
}

bool butonIfApasat(int x, int y)
{
    return x >= 410 && x <= 510 && y >= 30 && y <= 70;
}

bool butonAssignApasat(int x, int y)
{
    return x >= 530 && x <= 630 && y >= 30 && y <= 70;
}

bool butonStopApasat(int x, int y)
{
    return x >= 650 && x <= 750 && y >= 30 && y <= 70;
}

bool butonDrawingFinishedApasat(int x, int y)
{
    return x >= 827 && x <= 977 && y >= 30 && y <= 75;
}

bool butonSaveFileApasat(int x, int y)
{
    return x >= 827 && x <= 977 && y >= 100 && y <= 145;
}

bool butonGoBackApasat(int x, int y)
{
    return x >= 1003 && x <= 1153 && y >= 30 && y <= 75;
}

bool butonOpenFileApasat(int x, int y)
{
    return x >= 1003 && x <= 1153 && y >= 100 && y <= 145;
}

bool butonDinSchemaApasat(int &x, int &y)
{
    bloc* tmp = prim;
    while (tmp->urm != NULL)
    {
        if((x >= tmp->x - 50) && (x <= tmp->x + 50) && (y >= tmp->y - 20) && (y <= tmp->y + 20))
        {
            x = tmp->x;
            y = tmp->y;
            return 1;
        }
        tmp = tmp->urm;
    }
    return 0;
}


void desenareSchema()
{
    bloc* tmp = prim;
    while (tmp->urm != NULL)
    {
        deseneazaBloc(tmp->x, tmp->y, tmp->id);
        tmp = tmp->urm;
    }
}


void deseneazaLiniiExistente()
{
    bloc* tmp = prim;
    while (tmp->urm != NULL)
    {
        if(tmp->Rurm || tmp->Turm)
            if(tmp->id == 'd')
            {
                if(tmp->Rurm != NULL)
                    linie(tmp->x-50,tmp->y+20,tmp->Rurm->x,tmp->Rurm->y-20);
                if(tmp->Turm != NULL)
                    linie(tmp->x+50,tmp->y+20,tmp->Turm->x,tmp->Turm->y-20);
            }
            else
                linie(tmp->x,tmp->y+20,tmp->Rurm->x,tmp->Rurm->y-20);

        tmp = tmp->urm;
    }
}


void deseneazaEcran()
{
    setbkcolor(BLACK);
    cleardevice();
    desenareSchemaNoua();
    adaugaButoaneDesenareSchemaNoua();
    afisareVariabile();
    desenareSchema();
    deseneazaLiniiExistente();
    if(schema == 2)
    {
        cppMaximulDintre2Numere();
    }
    else
        if(schema == 3)
        {
            cppSumaPrimelorNNumere();
        }
}


void stergeLista()
{
    for(int i = 1; i <= nrBlocuri; i++)
    {
        bloc* tmp = prim;
        prim = prim->urm;
        free (tmp);
    }
    nrBlocuri = 0;
}


void inputValoriLista(int px, int py, char identificator)
{
    p = ultim;
    p->x = px;
    p->y = py;
    p->id = identificator;
    p->Rurm = NULL;
    p->Turm = NULL;
    p->val = 0;
    memset(p->decizie, 0, MAX_STR);
    bloc* q = new bloc;
    q->urm = NULL;
    p->urm = q;
    p = q;
    ultim = p;
}


void citesteLista()
{
    int i=1;
    int x1, y1,conditie,cnt;
    char identificator;
    bloc *tmp = prim;
    bloc *tmp2 = prim;
    f >> nrBlocuri;
    for(i=1;i<=nrBlocuri;i++)
    {
        f >> x1 >> y1 >> identificator;
        inputValoriLista(x1, y1, identificator);
    }
    for(i=1;i<=nrBlocuri;i++)
    {
        f >> conditie;
        if(conditie)
            {
                f >> x1 >> y1;
                tmp = prim;
                while(tmp->urm != NULL)
                {
                    if(tmp->x == x1 && tmp->y == y1)
                    {
                        tmp2->Rurm = tmp;
                        break;
                    }
                    tmp = tmp->urm;
                }
            }
        f >> conditie;
        if(conditie)
            {
                f >> x1 >> y1;
                tmp = prim;
                while(tmp->urm != NULL)
                {
                    if(tmp->x == x1 && tmp->y == y1)
                    {
                        tmp2->Turm = tmp;
                        break;
                    }
                    tmp = tmp->urm;
                }
            }
        tmp2 = tmp2->urm;
    }
    f.clear();
    f.close();
}



void salveazaFisier()
{
    bloc* tmp = prim;
    f << nrBlocuri << '\n';
    while (tmp->urm != NULL)
    {
        f << tmp->x << ' ' << tmp->y << ' ' << tmp->id << '\n';
        tmp = tmp->urm;
    }
    tmp = prim;
    while (tmp->urm != NULL)
    {
        if(tmp->Rurm != NULL)
            f << 1 << ' ' << tmp->Rurm->x << ' ' << tmp->Rurm->y << ' ';
        else
            f << 0 << ' ';
        if(tmp->Turm != NULL)
            f << 1 << ' ' << tmp->Turm->x << ' ' << tmp->Turm->y << ' ';
        else
            f << 0 << ' ';
        f << '\n';
        tmp = tmp->urm;
    }
    f.close();
}


void deseneaza(char identificator)
{
    int px, py, page = 0;
    while (1)
    {
        px = mousex();
        py = mousey();
        if (px > 70 && py > 40 && px < 730 && py < 510)
        {
            setactivepage(page);
            setvisualpage(1 - page);

            deseneazaEcran();
            deseneazaBloc(px, py, identificator);
            if (py > 100)
                if (ismouseclick(WM_LBUTTONDOWN))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    inputValoriLista(px, py, identificator);
                    nrBlocuri++;
                    return;
                }
            page = 1 - page;
        }
    }
}


void leagaBlocuri(int x1,int y1, int x2, int y2)
{
    bloc* q;
    bloc* r;
    bloc* tmp = prim;
    //cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
    while (tmp->urm != NULL)
    {
        if(tmp->x == x1 && tmp->y == y1)
            q = tmp;
        if(tmp->x == x2 && tmp->y == y2)
            r = tmp;
        tmp = tmp->urm;
    }
    if(q->id != 's')
        if(q->id == 'd')
            if(q->Turm == NULL)
                q->Turm = r;
            else
                q->Rurm = r;
        else
            q->Rurm = r;

}


void deseneazaLinii(int x, int y)
{
    //clearmouseclick(WM_LBUTTONDOWN);
    int px, py, page = 0;
    while (1)
    {
        px = mousex();
        py = mousey();
        if (px > 70 && py > 40 && px < 730 && py < 510)
        {
            setactivepage(page);
            setvisualpage(1 - page);

            deseneazaEcran();

            linie(x,y+20,px,py);
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                if(butonDinSchemaApasat(px,py))
                {
                    leagaBlocuri(x,y,px,py);
                    afisareVariabile();
                    deseneazaLiniiExistente();
                    deseneazaEcran();
                    page = 1 - page;
                    setactivepage(page);
                    setvisualpage(1 - page);
                    return;
                }
            }
            page = 1 - page;
        }
    }
    return;
}


int returneazaSchemaNouaNumarulDeOrdineAlButonuluiApasat(int x, int y)
{
    char s[100];
    int xText, yText;
    if (ExistaStart == 1)
    {
        if (butonStartApasat(x, y))
        {
            setvisualpage(0);
            setactivepage(0);
            strcpy(s, "EXISTA DEJA UN BLOC DE TIPUL START INSERAT");
            xText = 20 + (760 - textwidth(s)) / 2;
            yText = 20 + (510 - textheight(s)) / 2;
            outtextxy(xText, yText, s);
        }
        if (butonInputApasat(x, y))
            deseneaza('i');
        if (butonOutputApasat(x, y))
            deseneaza('o');
        if (butonIfApasat(x, y))
            deseneaza('d');
        if (butonAssignApasat(x, y))
            deseneaza('a');
        if (butonStopApasat(x, y))
            deseneaza('s');
        if (butonDinSchemaApasat(x, y))
            deseneazaLinii(x, y);
    }
    else
        if (butonStartApasat(x, y))
        {
            deseneaza('S');
            ExistaStart = 1;
        }
        else
        {
            strcpy(s, "INSEREAZA UN BLOC DE TIPUL START PENTRU A INCEPE");
            xText = 20 + (760 - textwidth(s)) / 2;
            yText = 20 + (510 - textheight(s)) / 2;
            outtextxy(xText, yText, s);
        }

    if (butonDrawingFinishedApasat(x, y))
    {
        return 1;
    }
    if (butonGoBackApasat(x, y))
    {
        return 2;
    }
    if (butonSaveFileApasat(x, y))
    {
        salveazaFisier();
        return 3;
    }
    if (butonOpenFileApasat(x, y))
    {
        citesteLista();
        ExistaStart = 1;
        deseneazaEcran();
        afisareVariabile();
        f.open("date.txt");
        return 4;
    }
    return -1;
}


void mutareBloc(int x, int y)
{
    bloc *tmp = prim;
    int px,py,page = 0;
    while (tmp->urm != NULL)
    {
        if(tmp->x == x && tmp->y == y)
            while(1)
            {
                px = mousex();
                py = mousey();
                if (px > 70 && py > 40 && px < 730 && py < 510)
                {
                    setactivepage(page);
                    setvisualpage(1 - page);
                    tmp->x = px;
                    tmp->y = py;
                    deseneazaEcran();
                    if(py > 100)
                        if(ismouseclick(WM_RBUTTONDOWN))
                        {
                            clearmouseclick(WM_RBUTTONDOWN);
                            return;
                        }
                    page = 1 - page;
                }
            }
        tmp = tmp->urm;
    }
}


void citesteCoordonateMouseSchemaNoua()
{
    while (1)
    {
        Sleep(4);
        int x, y;
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x = mousex();
            y = mousey();

            int zona = returneazaSchemaNouaNumarulDeOrdineAlButonuluiApasat(x, y);

            int xText = 820, yText = 158;

            if (butonGoBackApasat(x, y))
            {
                setactivepage(0);
                setvisualpage(0);
                stergeLista();
                ExistaStart = 0;
                fereastraStart();
                citesteCoordonateMouseFereastraStart();
                break;
            }
            else
            {
                if(zona == 1) /// butonDrawingFinishedApasat
                {
                    deseneazaEcran();
                    setvisualpage(0);
                    setactivepage(0);

                    char mesaj_initial[MAX_STR];
                    strcpy(mesaj_initial, "Desenare finalizata. Puteti completa blocurile.");
                    outtextxy(xText, yText, mesaj_initial);
                    yText += textheight(mesaj_initial);

                    char cereVar[MAX_STR];
                    strcpy(cereVar, "Introdu valoarea lui  : ");

                    while(1)
                    {
                        Sleep(4);

                        if(yText >= 270)
                        {
                            setfillstyle(SOLID_FILL, COLOR(r1, g1, b1));
                            yText = 158;
                            bar(803, 158, 1178, 277);
                            setbkcolor(COLOR(r, g, b));
                            setfillstyle(SOLID_FILL, COLOR(r, g, b));
                        }

                        if (ismouseclick(WM_LBUTTONDOWN))
                        {
                            clearmouseclick(WM_LBUTTONDOWN);
                            int x = mousex();
                            int y = mousey();

                            int ok = 0;
                            bloc * bloc_gasit;
                            bloc* tmp = prim;
                            while (tmp->urm != NULL && ok == 0)
                            {
                                if((x >= tmp->x - 50) && (x <= tmp->x + 50) && (y >= tmp->y - 20) && (y <= tmp->y + 20))
                                {
                                    x = tmp->x;
                                    y = tmp->y;
                                    ok = 1;
                                    bloc_gasit = tmp;
                                }
                                tmp = tmp->urm;
                            }

                            if(ok)
                            {
                                setbkcolor(COLOR(r, g, b));
                                setfillstyle(SOLID_FILL, COLOR(r, g, b));
                                if(bloc_gasit->id != 's')
                                {
                                    bar(bloc_gasit->x - 50, bloc_gasit->y, bloc_gasit->x + 50, bloc_gasit->y + 20);
                                }

                                if(bloc_gasit->id == 's')
                                {
                                    char mesaj_oprire[MAX_STR];
                                    strcpy(mesaj_oprire, "Editarea blocurilor oprita.");
                                    outtextxy(xText, yText, mesaj_oprire);
                                    yText += textheight(mesaj_oprire);
                                    xText = 820;
                                    break;
                                }
                                else
                                    if(bloc_gasit->id == 'i')
                                    {
                                        char lit, lit_str[MAX_STR];
                                        char cereVar[MAX_STR];
                                        strcpy(cereVar, "Introdu numele variabilei: ");
                                        CitesteSir(xText, yText, cereVar, lit_str);
                                        xText += textwidth(cereVar);

                                        if(strlen(lit_str) == 1)
                                        {
                                            outtextxy(xText, yText, lit_str);
                                            xText += textwidth(lit_str);
                                            outtextxy(xText, yText, "=");
                                            xText += textwidth("=");

                                            lit = lit_str[0];
                                            if(lit >= 'A' && lit <= 'Z')
                                            {
                                                char s[MAX_STR];
                                                strcpy(s, " =");
                                                //s[0] = aux->numeVar;

                                                int gasit = 0;
                                                bloc * q = prim;
                                                bloc * bloc_cautat;
                                                while(q)
                                                {
                                                    if(q->id == 'i')
                                                    {
                                                        if(q->numeVar == lit)
                                                        {
                                                            gasit = 1;
                                                            bloc_cautat = q;
                                                        }
                                                    }
                                                    q = q->urm;
                                                }

                                                if(!gasit)
                                                {
                                                    bloc_gasit->numeVar = lit;
                                                    s[0] = bloc_gasit->numeVar;

                                                    char exprInfix[MAX_STR];
                                                    cereVar[0] = NULL;
                                                    CitesteSir(xText, yText, cereVar, exprInfix);
                                                    xText += textwidth(cereVar);
                                                    char exprPostfix[101][101];
                                                    char numeVariabila;
                                                    int flag = 0, lgCoada = 0;
                                                    if((strlen(exprInfix) == 1 && exprInfix[0] >= 'A' && exprInfix[0] <= 'Z') || (exprInfix[0] >= 'A' && exprInfix[0] <= 'Z'))
                                                    {
                                                        flag = 1;
                                                        numeVariabila = exprInfix[0];
                                                    }

                                                    tranformareInfixInPostfix(exprInfix, exprPostfix, lgCoada, flag, numeVariabila);
                                                    if(flag == 0)
                                                    {
                                                        int valoare = valoareaExpresieiPostfixate(exprPostfix, lgCoada);
                                                        bloc_gasit->val = valoare;
                                                        char foo[10];
                                                        itoa(valoare, foo, 10);
                                                        //outtextxy(xText, yText, foo);
                                                        xText = 820;
                                                        yText += textheight(cereVar);
                                                        strcat(s, foo);
                                                    }
                                                    else
                                                    {
                                                        int i, existaVar = 0;
                                                        bloc * q;
                                                        q = prim;
                                                        while(q)
                                                        {
                                                            if(q->id == 'i' && q->numeVar == numeVariabila)
                                                            {
                                                                for(i = 0; i < strlen(exprInfix); i++)
                                                                {
                                                                    if(exprInfix[i] == numeVariabila)
                                                                    {
                                                                        break;
                                                                    }
                                                                }
                                                                char var_in_char[101];
                                                                itoa(q->val, var_in_char, 10);

                                                                char sir_aux[101];
                                                                strcpy(sir_aux, exprInfix);
                                                                sir_aux[i] = '\0';
                                                                strcat(sir_aux, var_in_char);
                                                                strcat(sir_aux, exprInfix + i + 1);
                                                                strcpy(exprInfix, sir_aux);

                                                                break;

                                                            }
                                                            q = q->urm;
                                                        }

                                                        if(!existaVar)
                                                        {
                                                            for(int i = 0; i < strlen(exprInfix); i++)
                                                            {
                                                                if(exprInfix[i] >= 'A' && exprInfix[i] <= 'Z')
                                                                {
                                                                    exprInfix[i] = '0';
                                                                    break;
                                                                }
                                                            }
                                                        }
                                                    }


                                                    if(flag == 1)
                                                    {
                                                        //cout << exprInfix << '\n';
                                                        tranformareInfixInPostfix(exprInfix, exprPostfix, lgCoada, flag, numeVariabila);
                                                        int valoare = valoareaExpresieiPostfixate(exprPostfix, lgCoada);
                                                        bloc_gasit->val = valoare;
                                                        char foo[10];
                                                        itoa(valoare, foo, 10);
                                                        //outtextxy(xText, yText, foo);
                                                        xText = 820;
                                                        yText += textheight(cereVar);
                                                        strcat(s, foo);
                                                    }

                                                    int inaltimebuton = 40, latimebuton = 100;
                                                    int x1 = bloc_gasit->x - latimebuton / 2;
                                                    int y1 = bloc_gasit->y - inaltimebuton / 2;
                                                    int xText = x1 + (latimebuton - textwidth(s)) / 2;
                                                    int yText = y1 + (inaltimebuton - textheight(s)) / 2 + 10;
                                                    outtextxy(xText, yText, s);

                                                    strcpy(bloc_gasit->sirDeAfisat, s);
                                                }
                                                else
                                                {
        //                                            char egal[MAX_STR];
        //                                            strcpy(egal, "  = ");
        //                                            egal[0] = lit;
        //                                            outtextxy(xText, yText, egal);
        //                                            xText += textwidth(egal);

                                                    char exprInfix[MAX_STR];
                                                    cereVar[0] = NULL;
                                                    CitesteSir(xText, yText, cereVar, exprInfix);
                                                    //cout << exprInfix << '\n';

                                                    char s[MAX_STR];
                                                    //s[0] = '\0';
                                                    s[0] = lit;
                                                    s[1] = '=';
                                                    s[2] = '\0';
                                                    char exprPostfix[101][101];
                                                    char numeVariabila;
                                                    int flag = 0, lgCoada = 0;
                                                    if((strlen(exprInfix) == 1 && exprInfix[0] >= 'A' && exprInfix[0] <= 'Z') || (exprInfix[0] >= 'A' && exprInfix[0] <= 'Z'))
                                                    {
                                                        flag = 1;
                                                        numeVariabila = exprInfix[0];
                                                    }

                                                    tranformareInfixInPostfix(exprInfix, exprPostfix, lgCoada, flag, numeVariabila);
                                                    if(flag == 0)
                                                    {
                                                        int valoare = valoareaExpresieiPostfixate(exprPostfix, lgCoada);
                                                        bloc_cautat->val = valoare;
                                                        char foo[10];
                                                        itoa(valoare, foo, 10);
                                                        //outtextxy(xText, yText, foo);
                                                        xText = 820;
                                                        yText += textheight(cereVar);
                                                        strcat(s, foo);
                                                    }
                                                    else
                                                    {
                                                        int i, existaVar = 0;
                                                        bloc * q;
                                                        q = prim;
                                                        while(q)
                                                        {
                                                            if(q->id == 'i' && q->numeVar == numeVariabila)
                                                            {
                                                                for(i = 0; i < strlen(exprInfix); i++)
                                                                {
                                                                    if(exprInfix[i] == numeVariabila)
                                                                    {
                                                                        break;
                                                                    }
                                                                }
                                                                char var_in_char[101];
                                                                itoa(q->val, var_in_char, 10);

                                                                char sir_aux[101];
                                                                strcpy(sir_aux, exprInfix);
                                                                sir_aux[i] = '\0';
                                                                strcat(sir_aux, var_in_char);
                                                                strcat(sir_aux, exprInfix + i + 1);
                                                                strcpy(exprInfix, sir_aux);

                                                                break;

                                                            }
                                                            q = q->urm;
                                                        }

                                                        if(!existaVar)
                                                        {
                                                            for(int i = 0; i < strlen(exprInfix); i++)
                                                            {
                                                                if(exprInfix[i] >= 'A' && exprInfix[i] <= 'Z')
                                                                {
                                                                    exprInfix[i] = '0';
                                                                    break;
                                                                }
                                                            }
                                                        }
                                                    }


                                                    if(flag == 1)
                                                    {
                                                        //cout << exprInfix << '\n';
                                                        tranformareInfixInPostfix(exprInfix, exprPostfix, lgCoada, flag, numeVariabila);
                                                        int valoare = valoareaExpresieiPostfixate(exprPostfix, lgCoada);
                                                        bloc_cautat->val = valoare;
                                                        char foo[10];
                                                        itoa(valoare, foo, 10);
                                                        //outtextxy(xText, yText, foo);
                                                        xText = 820;
                                                        yText += textheight(cereVar);
                                                        strcat(s, foo);
                                                    }

                                                    int inaltimebuton = 40, latimebuton = 100;
                                                    int x1 = bloc_gasit->x - latimebuton / 2;
                                                    int y1 = bloc_gasit->y - inaltimebuton / 2;
                                                    int xText = x1 + (latimebuton - textwidth(s)) / 2;
                                                    int yText = y1 + (inaltimebuton - textheight(s)) / 2 + 10;
                                                    outtextxy(xText, yText, s);

                                                    strcpy(bloc_gasit->sirDeAfisat, s);
                                                }
                                            }
                                            else
                                            {
                                                char eroare[MAX_STR];
                                                strcpy(eroare, "Variabila inexistenta!");
                                                outtextxy(xText, yText, eroare);
                                            }
                                        }
                                        else
                                        {
                                            char eroare[MAX_STR];
                                            strcpy(eroare, "Nume variabila gresit!");
                                            outtextxy(xText, yText, eroare);
                                        }

                                        yText += textheight("Introdu valoarea variabilei: ");
                                        xText = 820;

                                    }
                                    else
                                        if(bloc_gasit->id == 'a')
                                        {
                                            char lit, lit_str[MAX_STR];
                                            char cereVar[MAX_STR];
                                            strcpy(cereVar, "Introdu valoarea variabilei: ");
                                            CitesteSir(xText, yText, cereVar, lit_str);
                                            xText += textwidth(cereVar);

                                            if(strlen(lit_str) == 1)
                                            {
                                                outtextxy(xText, yText, lit_str);
                                                xText += textwidth(lit_str);
                                                outtextxy(xText, yText, "=");
                                                xText += textwidth("=");

                                                lit = lit_str[0];
                                                if(lit >= 'A' && lit <= 'Z')
                                                {
                                                    char s[MAX_STR];
                                                    strcpy(s, " =");
                                                    //s[0] = aux->numeVar;

                                                    int gasit = 0;
                                                    bloc * q = prim;
                                                    bloc * bloc_cautat;
                                                    while(q)
                                                    {
                                                        if(q->id == 'i' || q->id == 'a')
                                                        {
                                                            if(q->numeVar == lit)
                                                            {
                                                                gasit = 1;
                                                                bloc_cautat = q;
                                                            }
                                                        }
                                                        q = q->urm;
                                                    }

                                                    if(!gasit)
                                                    {
                                                        bloc_gasit->numeVar = lit;
                                                        s[0] = bloc_gasit->numeVar;

                                                        char exprInfix[MAX_STR];
                                                        cereVar[0] = NULL;
                                                        CitesteSir(xText, yText, cereVar, exprInfix);
                                                        xText += textwidth(cereVar);
                                                        char exprPostfix[101][101];
                                                        char numeVariabila;
                                                        int flag = 0, lgCoada = 0;
                                                        if((strlen(exprInfix) == 1 && exprInfix[0] >= 'A' && exprInfix[0] <= 'Z') || (exprInfix[0] >= 'A' && exprInfix[0] <= 'Z'))
                                                        {
                                                            flag = 1;
                                                            numeVariabila = exprInfix[0];
                                                        }

                                                        tranformareInfixInPostfix(exprInfix, exprPostfix, lgCoada, flag, numeVariabila);
                                                        if(flag == 0)
                                                        {
                                                            int valoare = valoareaExpresieiPostfixate(exprPostfix, lgCoada);
                                                            bloc_gasit->val = valoare;
                                                            char foo[10];
                                                            itoa(valoare, foo, 10);
                                                            //outtextxy(xText, yText, foo);
                                                            xText = 820;
                                                            yText += textheight(cereVar);
                                                            //strcat(s, foo);
                                                            strcat(s, exprInfix);
                                                        }
                                                        else
                                                        {
                                                            int i, existaVar = 0;
                                                            bloc * q;
                                                            q = prim;
                                                            while(q)
                                                            {
                                                                if((q->id == 'i' || q->id == 'a') && q->numeVar == numeVariabila)
                                                                {
                                                                    for(i = 0; i < strlen(exprInfix); i++)
                                                                    {
                                                                        if(exprInfix[i] == numeVariabila)
                                                                        {
                                                                            break;
                                                                        }
                                                                    }

                                                                    strcat(s, exprInfix);

                                                                    char var_in_char[101];
                                                                    itoa(q->val, var_in_char, 10);

                                                                    char sir_aux[101];
                                                                    strcpy(sir_aux, exprInfix);
                                                                    sir_aux[i] = '\0';
                                                                    strcat(sir_aux, var_in_char);
                                                                    strcat(sir_aux, exprInfix + i + 1);
                                                                    strcpy(exprInfix, sir_aux);

                                                                    break;

                                                                }
                                                                q = q->urm;
                                                            }

                                                            if(!existaVar)
                                                            {
                                                                for(int i = 0; i < strlen(exprInfix); i++)
                                                                {
                                                                    if(exprInfix[i] >= 'A' && exprInfix[i] <= 'Z')
                                                                    {
                                                                        exprInfix[i] = '0';
                                                                        break;
                                                                    }
                                                                }
                                                            }
                                                        }


                                                        if(flag == 1)
                                                        {
                                                            //cout << exprInfix << '\n';
                                                            tranformareInfixInPostfix(exprInfix, exprPostfix, lgCoada, flag, numeVariabila);
                                                            int valoare = valoareaExpresieiPostfixate(exprPostfix, lgCoada);
                                                            bloc_gasit->val = valoare;
                                                            char foo[10];
                                                            itoa(valoare, foo, 10);
                                                            //outtextxy(xText, yText, foo);
                                                            xText = 820;
                                                            yText += textheight(cereVar);
                                                            //strcat(s, foo);
                                                            //strcat(s, exprInfix);
                                                        }

                                                        int inaltimebuton = 40, latimebuton = 100;
                                                        int x1 = bloc_gasit->x - latimebuton / 2;
                                                        int y1 = bloc_gasit->y - inaltimebuton / 2;
                                                        int xText = x1 + (latimebuton - textwidth(s)) / 2;
                                                        int yText = y1 + (inaltimebuton - textheight(s)) / 2 + 10;
                                                        outtextxy(xText, yText, s);

                                                        strcpy(bloc_gasit->sirDeAfisat, s);
                                                    }
                                                    else
                                                    {
            //                                            char egal[MAX_STR];
            //                                            strcpy(egal, "  = ");
            //                                            egal[0] = lit;
            //                                            outtextxy(xText, yText, egal);
            //                                            xText += textwidth(egal);

                                                        char exprInfix[MAX_STR];
                                                        cereVar[0] = NULL;
                                                        CitesteSir(xText, yText, cereVar, exprInfix);
                                                        //cout << exprInfix << '\n';

                                                        char s[MAX_STR];
                                                        //s[0] = '\0';
                                                        s[0] = lit;
                                                        s[1] = '=';
                                                        s[2] = '\0';
                                                        char exprPostfix[101][101];
                                                        char numeVariabila;
                                                        int flag = 0, lgCoada = 0;
                                                        if((strlen(exprInfix) == 1 && exprInfix[0] >= 'A' && exprInfix[0] <= 'Z') || (exprInfix[0] >= 'A' && exprInfix[0] <= 'Z'))
                                                        {
                                                            flag = 1;
                                                            numeVariabila = exprInfix[0];
                                                        }

                                                        tranformareInfixInPostfix(exprInfix, exprPostfix, lgCoada, flag, numeVariabila);
                                                        if(flag == 0)
                                                        {
                                                            int valoare = valoareaExpresieiPostfixate(exprPostfix, lgCoada);
                                                            bloc_cautat->val = valoare;
                                                            char foo[10];
                                                            itoa(valoare, foo, 10);
                                                            //outtextxy(xText, yText, foo);
                                                            xText = 820;
                                                            yText += textheight(cereVar);
                                                            //strcat(s, foo);
                                                            strcat(s, exprInfix);
                                                        }
                                                        else
                                                        {
                                                            int i, existaVar = 0;
                                                            bloc * q;
                                                            q = prim;
                                                            while(q)
                                                            {
                                                                if((q->id == 'i' || q->id == 'a') && q->numeVar == numeVariabila)
                                                                {
                                                                    for(i = 0; i < strlen(exprInfix); i++)
                                                                    {
                                                                        if(exprInfix[i] == numeVariabila)
                                                                        {
                                                                            break;
                                                                        }
                                                                    }

                                                                    strcat(s, exprInfix);

                                                                    char var_in_char[101];
                                                                    itoa(q->val, var_in_char, 10);

                                                                    char sir_aux[101];
                                                                    strcpy(sir_aux, exprInfix);
                                                                    sir_aux[i] = '\0';
                                                                    strcat(sir_aux, var_in_char);
                                                                    strcat(sir_aux, exprInfix + i + 1);
                                                                    strcpy(exprInfix, sir_aux);

                                                                    break;
                                                                }
                                                                q = q->urm;
                                                            }

                                                            if(!existaVar)
                                                            {
                                                                for(int i = 0; i < strlen(exprInfix); i++)
                                                                {
                                                                    if(exprInfix[i] >= 'A' && exprInfix[i] <= 'Z')
                                                                    {
                                                                        exprInfix[i] = '0';
                                                                        break;
                                                                    }
                                                                }
                                                            }
                                                        }


                                                        if(flag == 1)
                                                        {
                                                            //cout << exprInfix << '\n';
                                                            tranformareInfixInPostfix(exprInfix, exprPostfix, lgCoada, flag, numeVariabila);
                                                            int valoare = valoareaExpresieiPostfixate(exprPostfix, lgCoada);
                                                            bloc_cautat->val = valoare;
                                                            char foo[10];
                                                            itoa(valoare, foo, 10);
                                                            //outtextxy(xText, yText, foo);
                                                            xText = 820;
                                                            yText += textheight(cereVar);
                                                            //strcat(s, foo);
                                                            //strcat(s, exprInfix);
                                                        }

                                                        int inaltimebuton = 40, latimebuton = 100;
                                                        int x1 = bloc_gasit->x - latimebuton / 2;
                                                        int y1 = bloc_gasit->y - inaltimebuton / 2;
                                                        int xText = x1 + (latimebuton - textwidth(s)) / 2;
                                                        int yText = y1 + (inaltimebuton - textheight(s)) / 2 + 10;
                                                        outtextxy(xText, yText, s);

                                                        strcpy(bloc_gasit->sirDeAfisat, s);
                                                    }
                                                }
                                                else
                                                {
                                                    char eroare[MAX_STR];
                                                    strcpy(eroare, "Variabila inexistenta!");
                                                    outtextxy(xText, yText, eroare);
                                                }
                                            }
                                            else
                                            {
                                                char eroare[MAX_STR];
                                                strcpy(eroare, "Nume variabila gresit!");
                                                outtextxy(xText, yText, eroare);
                                            }

                                            yText += textheight("Introdu valorea variabilei: ");
                                            xText = 820;
                                        }
                                        else
                                            if(bloc_gasit->id == 'o')
                                            {
                                                char numeVar, lit_str[MAX_STR];
                                                char cereVar[MAX_STR];
                                                strcpy(cereVar, "Ce variabila sa afisez? ");
                                                CitesteSir(xText, yText, cereVar, lit_str);
                                                xText += textwidth(cereVar);
                                                bloc * bloc_afis;

                                                if(strlen(lit_str) == 1)
                                                {
                                                    numeVar = lit_str[0];
                                                    bloc_gasit->numeVar = numeVar;
                                                    if(numeVar >= 'A' && numeVar <= 'Z')
                                                    {
                                                        char sirDeAfisat[MAX_STR];
                                                        strcpy(sirDeAfisat, lit_str);
                                                        strcat(sirDeAfisat, " = ");

                                                        char val_str[MAX_STR];

                                                        int ok = 0;
                                                        bloc * tmp = prim;
                                                        while(tmp && !ok)
                                                        {
                                                            if(tmp->numeVar == numeVar)
                                                            {
                                                                ok = 1;
                                                                bloc_afis = tmp;
                                                            }
                                                            tmp = tmp->urm;
                                                        }


                                                        if(!ok)
                                                        {
                                                            xText += textwidth(lit_str);
                                                            strcpy(sirDeAfisat, ": Variabila nefolosita!");
                                                        }
                                                        else
                                                        {
                                                            itoa(bloc_afis->val, val_str, 10);
                                                            strcat(sirDeAfisat, val_str);
                                                        }

                                                        outtextxy(xText, yText, sirDeAfisat);

                                                        yText += textheight(sirDeAfisat);
                                                    }
                                                    else
                                                    {
                                                        char eroare[MAX_STR];
                                                        strcpy(eroare, "Variabila inexistenta!");
                                                        outtextxy(xText, yText, eroare);
                                                        yText += textheight(eroare);
                                                    }
                                                }
                                                else
                                                {
                                                    char eroare[MAX_STR];
                                                    strcpy(eroare, "Nume variabila gresit!");
                                                    outtextxy(xText, yText, eroare);
                                                    yText += textheight(eroare);
                                                }

                                                xText = 820;

                                                char s[MAX_STR];
                                                strcpy(s, "PRINT(");
                                                strcat(s, lit_str);
                                                strcat(s, ")");
                                                int inaltimebuton = 40, latimebuton = 100;
                                                int x1 = bloc_gasit->x - latimebuton / 2;
                                                int y1 = bloc_gasit->y - inaltimebuton / 2;
                                                int xText = x1 + (latimebuton - textwidth(s)) / 2;
                                                int yText = y1 + (inaltimebuton - textheight(s)) / 2 + 10;
                                                outtextxy(xText, yText, s);

                                                strcpy(bloc_gasit->sirDeAfisat, s);
                                            }
                                            else
                                                if(bloc_gasit->id == 'd')
                                                {
                                                    char input[MAX_STR];
                                                    char mesaj[MAX_STR];
                                                    strcpy(mesaj, "Instructiunea de decizie: ");
                                                    CitesteSir(xText, yText, mesaj, input);
                                                    xText += textwidth(mesaj);
                                                    xText += textwidth(input);

                                                    strcpy(bloc_gasit->sirDeAfisat, input);

                                                    strcpy(bloc_gasit->decizie, input);
                                                    char var_st = input[0];
                                                    char Operator = input[1];
                                                    char var_dr = input[2];

                                                    if((var_st >= 'A' && var_st <= 'Z') && (var_dr >= 'A' && var_dr <= 'Z') && (Operator == '=' || Operator == '<' || Operator == '>'))
                                                    {
                                                        bloc* tmp, *st, *dr;
                                                        tmp = prim;
                                                        while(tmp)
                                                        {
                                                            if(tmp->numeVar == var_st)
                                                            {
                                                                st = tmp;
                                                            }
                                                            else
                                                                if(tmp->numeVar == var_dr)
                                                                {
                                                                    dr = tmp;
                                                                }
                                                            tmp = tmp->urm;
                                                        }

                                                        int dif = st->val - dr->val;
                                                        if(Operator == '=' && dif == 0)
                                                        {
                                                            ///pe ramura de adevarat
                                                            strcpy(mesaj, "   Conditie adevarata.");
                                                            outtextxy(xText, yText, mesaj);
                                                            xText += textwidth(mesaj);
                                                            //cout << 1 << '\n';
                                                        }
                                                        else
                                                            if(Operator == '=' && dif != 0)
                                                            {
                                                                ///pe ramura de fals
                                                                strcpy(mesaj, "   Conditie falsa.");
                                                                outtextxy(xText, yText, mesaj);
                                                                xText += textwidth(mesaj);
                                                                //cout << 2 << '\n';

                                                                bloc * var_aux;
                                                                var_aux = bloc_gasit->Rurm;
                                                                bloc_gasit->Rurm = bloc_gasit->Turm;
                                                                bloc_gasit->Turm = var_aux;
                                                            }
                                                            else
                                                                if(Operator == '<' && dif < 0)
                                                                {
                                                                    ///pe ramura de Adevarat
                                                                    strcpy(mesaj, "   Conditie adevarata.");
                                                                    outtextxy(xText, yText, mesaj);
                                                                    xText += textwidth(mesaj);
                                                                    //cout << 3 << '\n';
                                                                }
                                                                else
                                                                    if(Operator == '<' && dif >= 0)
                                                                    {
                                                                        ///pe ramura de fals
                                                                        strcpy(mesaj, "   Conditie falsa.");
                                                                        outtextxy(xText, yText, mesaj);
                                                                        xText += textwidth(mesaj);
                                                                        //cout << 4 << '\n';

                                                                        bloc * var_aux;
                                                                        var_aux = bloc_gasit->Rurm;
                                                                        bloc_gasit->Rurm = bloc_gasit->Turm;
                                                                        bloc_gasit->Turm = var_aux;
                                                                    }
                                                                    else
                                                                        if(Operator == '>' && dif > 0)
                                                                        {
                                                                            ///pe ramura de adevarat
                                                                            strcpy(mesaj, "   Conditie adevarata.");
                                                                            outtextxy(xText, yText, mesaj);
                                                                            xText += textwidth(mesaj);
                                                                            //cout << 5 << '\n';
                                                                        }
                                                                        else
                                                                            if(Operator == '>' && dif <= 0)
                                                                            {
                                                                                ///pe ramura de fals
                                                                                strcpy(mesaj, "   Conditie falsa.");
                                                                                outtextxy(xText, yText, mesaj);
                                                                                xText += textwidth(mesaj);
                                                                                //cout << 6 << '\n';

                                                                                bloc * var_aux;
                                                                                var_aux = bloc_gasit->Rurm;
                                                                                bloc_gasit->Rurm = bloc_gasit->Turm;
                                                                                bloc_gasit->Turm = var_aux;
                                                                            }
                                                                            else
                                                                            {
                                                                                strcpy(mesaj, "   Nu stiu sa rezolv... ");
                                                                                outtextxy(xText, yText, mesaj);
                                                                                xText += textwidth(mesaj);
                                                                                //cout << 7 << '\n';
                                                                            }
                                                    }
                                                    else
                                                    {
                                                        strcpy(mesaj, "   Eroare! ");
                                                        outtextxy(xText, yText, mesaj);
                                                        xText += textwidth(mesaj);
                                                    }

                                                    int inaltimebuton = 40, latimebuton = 100;
                                                    int x1 = bloc_gasit->x - latimebuton / 2;
                                                    int y1 = bloc_gasit->y - inaltimebuton / 2;
                                                    int xText1 = x1 + (latimebuton - textwidth(input)) / 2;
                                                    int yText1 = y1 + (inaltimebuton - textheight(input)) / 2 + 10;
                                                    outtextxy(xText1, yText1, input);

                                                    yText += textheight(mesaj);
                                                    xText = 820;


                                                }
                                                else
                                                    if(bloc_gasit->id == 'S')
                                                    {
                                                         if(schema == 2)
                                                        {
                                                            int a = -1, b = - 1;
                                                            bloc * q = prim;
                                                            while(q)
                                                            {
                                                                if(q->id == 'i')
                                                                {
                                                                    if(a == -1)
                                                                    {
                                                                        a = q->val;
                                                                    }
                                                                    else
                                                                        if(b == -1)
                                                                        {
                                                                            b = q->val;
                                                                        }
                                                                        else
                                                                        {
                                                                            break;
                                                                        }
                                                                }
                                                                q = q->urm;
                                                            }
                                                            char a_str[MAX_STR];
                                                            itoa(a, a_str, 10);
                                                            char b_str[MAX_STR];
                                                            itoa(b, b_str, 10);
                                                            int maxi = maxim(a, b);

                                                            q = prim;
                                                            while(q)
                                                            {
                                                                if(q->numeVar == 'M')
                                                                {
                                                                    q->val = maxi;
                                                                }
                                                                q = q->urm;
                                                            }

                                                            char foo[MAX_STR];
                                                            itoa(maxi, foo, 10);

                                                            char s[MAX_STR];
                                                            strcpy(s, "Maximul dintre ");
                                                            strcat(s, a_str);
                                                            strcat(s, " si ");
                                                            strcat(s, b_str);
                                                            strcat(s, " este: ");
                                                            strcat(s, foo);
                                                            outtextxy(xText, yText, s);
                                                            //xText += textwidth(s);
                                                            yText += textheight(s);
                                                        }
                                                        else
                                                            if(schema == 3)
                                                            {
                                                                int a = -1;
                                                                bloc * q = prim;
                                                                while(q)
                                                                {
                                                                    if(q->id == 'i')
                                                                    {
                                                                        if(a == -1)
                                                                        {
                                                                            a = q->val;
                                                                        }
                                                                        else
                                                                        {
                                                                             break;
                                                                        }
                                                                    }
                                                                    q = q->urm;
                                                                }

                                                                char a_str[MAX_STR];
                                                                itoa(a, a_str, 10);

                                                                int suma = sumaPrimelorNNumere(a);

                                                                q = prim;
                                                                while(q)
                                                                {
                                                                    if(q->numeVar == 'S')
                                                                    {
                                                                        q->val = suma;
                                                                    }
                                                                    q = q->urm;
                                                                }

                                                                char foo[MAX_STR];
                                                                itoa(suma, foo, 10);

                                                                char s[MAX_STR];
                                                                strcpy(s, "Suma primelor ");
                                                                strcat(s, a_str);
                                                                strcat(s, " numere este ");
                                                                strcat(s, foo);
                                                                outtextxy(xText, yText, s);
                                                                //xText += textwidth(s);
                                                                yText += textheight(s);
                                                            }
                                                            else
                                                            {
                                                                bloc * tmp = prim;
                                                                while(tmp)
                                                                {
                                                                    if(tmp->id == 'o')
                                                                    {
                                                                        char sir[MAX_STR];
                                                                        strcpy(sir, "  = ");
                                                                        sir[0] = tmp->numeVar;

                                                                        int val = 0;
                                                                        bloc * aux = prim;
                                                                        while(aux)
                                                                        {
                                                                            if(aux->id == 'i' || aux->id == 'a')
                                                                            {
                                                                                if(aux->numeVar == tmp->numeVar)
                                                                                {
                                                                                    val = aux->val;
                                                                                }
                                                                            }
                                                                            aux = aux->urm;
                                                                        }

                                                                        char val_str[MAX_STR];
                                                                        itoa(val , val_str, 10);
                                                                        strcat(sir, val_str);
                                                                        outtextxy(xText, yText, sir);
                                                                        yText += textheight(sir);
                                                                        xText = 820;
                                                                    }
                                                                    tmp = tmp->urm;
                                                                }
                                                            }

                                                            bloc * tmp = prim;
                                                            while (tmp->Rurm != NULL)
                                                            {
                                                                //cout << tmp->id << ' ' << tmp->x << ' ' << tmp->y << ' ' << tmp->sirDeAfisat << '\n';
                                                                setfillstyle(SOLID_FILL, COLOR(0, 204, 0));
                                                                setbkcolor(COLOR(0, 204, 0));
                                                                bar(tmp->x - 50, tmp->y - 20, tmp->x + 50, tmp->y + 20);

                                                                int inaltimebuton = 40, latimebuton = 100;
                                                                int xText, yText;
                                                                int x1, y1, x2, y2;
                                                                x1 = tmp->x - latimebuton / 2;
                                                                y1 = tmp->y - inaltimebuton / 2;
                                                                x2 = tmp->x + latimebuton / 2;
                                                                y2 = tmp->y + inaltimebuton / 2;

                                                                char s[20];
                                                                char identificator = tmp->id;
                                                                switch (identificator)
                                                                {
                                                                case 'S':
                                                                    strcpy(s, "START");
                                                                    break;
                                                                case 'i':
                                                                    strcpy(s, "INPUT");
                                                                    break;
                                                                case 'o':
                                                                    strcpy(s, "OUTPUT");
                                                                    break;
                                                                case 'd':
                                                                    strcpy(s, "IF");
                                                                    break;
                                                                case 'a':
                                                                    strcpy(s, "ASSIGN");
                                                                    break;
                                                                case 's':
                                                                    strcpy(s, "STOP");
                                                                    break;
                                                                }
                                                                xText = x1 + (latimebuton - textwidth(s)) / 2;
                                                                yText = y1 + (inaltimebuton - textheight(s)) / 2 - 10;
                                                                outtextxy(xText, yText, s);

                                                                xText = x1 + (latimebuton - textwidth(tmp->sirDeAfisat)) / 2;
                                                                outtextxy(xText, yText + 20, tmp->sirDeAfisat);
                                                                if(tmp->id == 'S')
                                                                    bar(tmp->x-50,tmp->y,tmp->x+50,tmp->y+20);

                                                                if(tmp->id == 'd')
                                                                    tmp = tmp->Turm;
                                                                else
                                                                    tmp = tmp->Rurm;
                                                                delay(800);
                                                                if(tmp->id == 's')
                                                                {
                                                                    bar(tmp->x - 50, tmp->y - 20, tmp->x + 50, tmp->y + 20);
                                                                    strcpy(s, "STOP");
                                                                    x1 = tmp->x - latimebuton / 2;
                                                                    y1 = tmp->y - inaltimebuton / 2;
                                                                    x2 = tmp->x + latimebuton / 2;
                                                                    y2 = tmp->y + inaltimebuton / 2;
                                                                    xText = x1 + (latimebuton - textwidth(s)) / 2;
                                                                    yText = y1 + (inaltimebuton - textheight(s)) / 2 - 10;
                                                                    outtextxy(xText, yText, s);

                                                                }
                                                            }
                                                    }

                                afisareVariabile();
                            }
                        }
                    }

                }
                else
                    if(zona == 3) /// butonSaveFileApasat
                    {
                        char mesaj[MAX_STR];
                        strcpy(mesaj, "Fisier salvat cu succes!   ");
                        outtextxy(xText, yText, mesaj);
                        yText += textheight(mesaj);
                    }
                    else
                        if(zona == 4) /// butonOpenFileApasat
                        {
                            char mesaj[MAX_STR];
                            strcpy(mesaj, "Fisier deschis cu succes!");
                            outtextxy(xText, yText, mesaj);
                            yText += textheight(mesaj);
                        }

            }
        }
        if (ismouseclick(WM_RBUTTONDOWN))
        {
            clearmouseclick(WM_RBUTTONDOWN);
            x = mousex();
            y = mousey();
            if(butonDinSchemaApasat(x,y))
                mutareBloc(x,y);
        }
    }
}


void ruleazaSchema()
{
    bloc* tmp = prim;
    while (tmp->Rurm != NULL)
    {
        cout << "bloc id : " << tmp->id << " coordonatele " << tmp->x << ' ' << tmp->y;
        cout << " conectat cu bloc id : " << tmp->Rurm->id << " coordonatele " << tmp->Rurm->x << ' ' << tmp->Rurm->y << '\n';
        if(tmp->id == 'd')
            cout << "ramura de adevar bloc IF este bloc id : " << tmp->Turm->id << " coordonatele " << tmp->Turm->x << ' ' << tmp->Turm->y << '\n';
        tmp = tmp->Rurm;
    }
    cout << "Parcurgerea schemei s-a incheiat cu succes!";
}



int main()
{
    prim->urm = NULL;
    prim->Rurm = NULL;

    init_bgi();
    setlinestyle(0,0,3);
    fereastraStart();

    citesteCoordonateMouseFereastraStart();

    _getch();

    closegraph();
    f.close();

    return 0;
}
