#ifndef EVALUARE_INFIXAT_H_INCLUDED
#define EVALUARE_INFIXAT_H_INCLUDED

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>

#define infinit INT_MAX

using namespace std;


// Contine operanzii din forma infixata necesari scrierii formei postfixata
struct NodStiva
{
    char opr;
    NodStiva* urm;
};


// Contine operatorii din forma infixata necesari scrierii formei postfixata
struct NodCoada
{
    int operand;
    char opr;
    NodCoada* urm;
};


// Adauga un nod in stiva
NodStiva* push(NodStiva* vf, char c)
{
    NodStiva* nou = new NodStiva;
    nou->opr = c;
    nou->urm = vf;
    return nou;
}


//Scoate varful stivei
NodStiva* pop(NodStiva* vf, char* c)
{
    if (vf)
    {
        *c = vf->opr;
        NodStiva* t = vf;
        vf = vf->urm;
        delete t;
        return vf;
    }
    return vf;
}

// Adauga un nod in coada
NodCoada* put(NodCoada* c, int v, char o)
{
    NodCoada* nou = new NodCoada;
    nou->operand = v;
    nou->opr = o;
    nou->urm = NULL;
    if (!c)
        return nou;
    else
    {
        NodCoada* t = c;
        while (t->urm)
        {
            t = t->urm;
        }
        t->urm = nou;
        return c;
    }
}


NodCoada* get(NodCoada* c, int * v, char* o)
{
    if (c)
    {
        *v = c->operand;
        *o = c->opr;
        NodCoada* t = c;
        c = c->urm;
        delete t;
        return c;
    }
    return c;
}


int prioritate(char c)
{
    switch (c)
    {
    case '(':
    case ')':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    case '#':
    case '=':
    case '<':
    case '>':
        return 4;
    case 'c':
    case 's':
    case 'l':
    case 'e':
    case 'a':
    case 'r':
        return 5;
    default:
        return 6;
    }
}


void tranformareInfixInPostfix(char exprInfix[], char exprPostfix[][101], int& lgCoada, int& flag, char& numeVariabila)
{
    NodStiva* stiva = NULL;
    NodCoada* coada = NULL;
    char SubExpr[100], o;
    int esteNumar;
    flag = 0;        //daca se intalneste vreun operator gresit / inexistent

    int i = 0;
    while (exprInfix[i] != '\0')
    {
        int k = 0;
        if (exprInfix[i] > 47 && exprInfix[i] < 58)     //daca este cifra
        {
            while (exprInfix[i] > 47 && exprInfix[i] < 58)
            {
                SubExpr[k] = exprInfix[i];
                k++;
                i++;
            }
            SubExpr[k] = '\0';
            esteNumar = 1;
        }
        else
        {
            SubExpr[k] = exprInfix[i];
            SubExpr[k + 1] = '\0';
            i++;
            esteNumar = 0;
        }

        if (esteNumar)
        {
            o = 0;
            coada = put(coada, atoi(SubExpr), o);
        }
        else
        {
            if (SubExpr[0] == '(')
            {
                stiva = push(stiva, SubExpr[0]);
            }
            else
            {
                if (SubExpr[0] == ')')
                {
                    stiva = pop(stiva, &o);
                    while (o != '(')
                    {
                        coada = put(coada, 0, o);
                        stiva = pop(stiva, &o);
                    }
                }
                else
                {
                    if (prioritate(SubExpr[0]) < 6)
                    {
                        if (stiva)
                        {
                            while (stiva && prioritate(stiva->opr) >= prioritate(SubExpr[0]))
                            {
                                stiva = pop(stiva, &o);
                                coada = put(coada, 0, o);
                            }
                        }
                        stiva = push(stiva, SubExpr[0]);
                    }
                    else
                    {
                        //cout << "Operator incorect introdus!";
                        flag = 1;
                        numeVariabila = SubExpr[0];
                    }
                }
            }
        }
    }

    while (stiva)
    {
        stiva = pop(stiva, &o);
        coada = put(coada, 0, o);
    }

    lgCoada = 0;
    NodCoada* t;
    if (!flag)
    {
        t = coada;
        while (t)
        {
            if (t->operand)
            {
                char aux[101];
                _itoa(t->operand, aux, 10);
                strcpy(exprPostfix[++lgCoada], aux);
            }
            else
            {
                char aux[101];
                aux[0] = t->opr;
                aux[1] = '\0';
                strcpy(exprPostfix[++lgCoada], aux);
            }
            t = t->urm;
        }
    }
}


bool esteOperator(char expr[])
{
    if (strlen(expr) != 1)
    {
        return 0;
    }
    else
    {
        switch (expr[0])
        {
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '#':
        case '=':
        case '<':
        case '>':
        case 'c':
        case 's':
        case 'l':
        case 'e':
        case 'a':
        case 'r':
            return 1;
        default:
            return 0;
        }
    }
}


bool difInf(int x)
{
    return abs(infinit - abs(x)) > infinit / 2;
}


int Plus(int x, int y)
{
    if (difInf(x) && difInf(y))
    {
        return x + y;
    }
    else
    {
        return infinit;
    }
}


int Minus(int x, int y)
{
    if (difInf(x) && difInf(y))
    {
        return x - y;
    }
    else
    {
        return infinit;
    }
}


int Inmultit(int x, int y)
{
    if (difInf(x) && difInf(y))
    {
        return x * y;
    }
    else
    {
        return infinit;
    }
}


int Impartit(int x, int y)
{
    if (difInf(x) && difInf(y))
    {
        return x / y;
    }
    else
    {
        return infinit;
    }
}


int RidicatLaPuterea(int x, int y)
{


    if (x == 0)
    {
        return 0;
    }
    else
        if (y == 0)
        {
            return 1;
        }
        else
            if (x == infinit || y == infinit)
            {
                return infinit;
            }
            else
            {
                int aux = x;
                while (y)
                {
                    x *= aux;
                    y--;
                }
                return x;
            }
}


int Diferit(int x, int y)
{
    return x != y;
}


int Egal(int x, int y)
{
    return x == y;
}


int MaiMic(int x, int y)
{
    if (difInf(x) && difInf(y))
    {
        return x < y;
    }
    else
    {
        return 0;
    }
}


int MaiMare(int x, int y)
{
    if (difInf(x) && difInf(y))
    {
        return x > y;
    }
    else
    {
        return 0;
    }
}


int Cosinus(int x)
{
    if (difInf(x))
    {
        return cos(x);
    }
    else
    {
        return 0;
    }
}


int Sinus(int x)
{
    if (difInf(x))
    {
        return sin(x);
    }
    else
    {
        return 0;
    }
}


int Logaritm(int x)
{
    if (difInf(x))
    {
        return log(x);
    }
    else
    {
        return infinit;
    }
}


int Exponential(int x)
{
    if (difInf(x))
    {
        return exp(x);
    }
    else
    {
        return infinit;
    }
}


int Modul(int x)       //degeaba, algoritmul de transformare in scrierea postfixata functioneaza doar pe numere intregi si strict pozitive
{
    if (difInf(x))
    {
        return abs(x);
    }
    else
    {
        return infinit;
    }
}


int Radical(int x)
{
    if (difInf(x))
    {
        return sqrt(x);
    }
    else
    {
        return infinit;
    }
}



struct NodStivaInt
{
    int val;
    NodStivaInt* urm;
};


// Adauga un nod in stiva
NodStivaInt* pushInt(NodStivaInt* vf, int x)
{
    NodStivaInt* nou = new NodStivaInt;
    nou->val = x;
    nou->urm = vf;
    return nou;
}


//Scoate varful stivei
NodStivaInt* popInt(NodStivaInt* vf, int& x)
{
    if (vf)
    {
        x = vf->val;
        NodStivaInt* t = vf;
        vf = vf->urm;
        delete t;
        return vf;
    }
    return vf;
}



int valoareaExpresieiPostfixate(char exprPostfix[][101], int lgCoada)
{
    NodStivaInt* stiva = NULL;
    NodCoada* coada = NULL;

    int opd;       // operand
    char opr;      // operator

    for (int i = 1; i <= lgCoada; i++)
    {
        if (esteOperator(exprPostfix[i]))
        {
            opd = 0;
            opr = exprPostfix[i][0];
            coada = put(coada, opd, opr);
        }
        else
        {
            opr = 0;
            opd = atoi(exprPostfix[i]);
            coada = put(coada, opd, opr);
        }
    }


    while (coada)
    {
        coada = get(coada, &opd, &opr);
        if (!opr)
        {
            stiva = pushInt(stiva, opd);
        }
        else
        {
            int ult, penult;
            int rez;
            switch (opr)
            {
                case '+':
                    stiva = popInt(stiva, ult);
                    stiva = popInt(stiva, penult);
                    rez = Plus(penult, ult);
                    break;
                case '-':
                    stiva = popInt(stiva, ult);
                    stiva = popInt(stiva, penult);
                    rez = Minus(penult, ult);
                    break;
                case '*':
                    stiva = popInt(stiva, ult);
                    stiva = popInt(stiva, penult);
                    rez = Inmultit(penult, ult);
                    break;
                case '/':
                    stiva = popInt(stiva, ult);
                    stiva = popInt(stiva, penult);
                    rez = Impartit(penult, ult);
                    break;
                case '^':
                    stiva = popInt(stiva, ult);
                    stiva = popInt(stiva, penult);
                    rez = RidicatLaPuterea(penult, ult);
                    break;
                case '#':
                    stiva = popInt(stiva, ult);
                    stiva = popInt(stiva, penult);
                    rez = Diferit(penult, ult);
                    break;
                case '=':
                    stiva = popInt(stiva, ult);
                    stiva = popInt(stiva, penult);
                    rez = Egal(penult, ult);
                    break;
                case '<':
                    stiva = popInt(stiva, ult);
                    stiva = popInt(stiva, penult);
                    rez = MaiMic(penult, ult);
                    break;
                case '>':
                    stiva = popInt(stiva, ult);
                    stiva = popInt(stiva, penult);
                    rez = MaiMare(penult, ult);
                    break;
                case 'c':
                    stiva = popInt(stiva, ult);
                    rez = Cosinus(ult);
                    break;
                case 's':
                    stiva = popInt(stiva, ult);
                    rez = Cosinus(ult);
                    break;
                case 'l':
                    stiva = popInt(stiva, ult);
                    rez = Logaritm(ult);
                    break;
                case 'e':
                    stiva = popInt(stiva, ult);
                    rez = Exponential(ult);
                    break;
                case 'a':
                    stiva = popInt(stiva, ult);
                    rez = Modul(ult);
                    break;
                case 'r':
                    stiva = popInt(stiva, ult);
                    rez = Radical(ult);
                    break;
            }

            stiva = pushInt(stiva, rez);
        }
    }

    int rezultat;
    stiva = popInt(stiva, rezultat);
    return rezultat;
}


void evalueaza()
{
    char exprInfix[101];
    cout << "Introduceti expresia matematica in forma infixata: ";
    cin >> exprInfix;

    char exprPostfix[101][101];
    char numeVariabila;
    int flag = 0, lgCoada = 0;
    if((strlen(exprInfix) == 1 && exprInfix[0] >= 'A' && exprInfix[0] <= 'Z') || (exprInfix[0] >= 'A' && exprInfix[0] <= 'Z'))
    {
        flag = 1;
        numeVariabila = exprInfix[0];
        cout << numeVariabila << '\n';
    }
    else
    {
        tranformareInfixInPostfix(exprInfix, exprPostfix, lgCoada, flag, numeVariabila);
        if(flag == 0)
        {
            int valoare = valoareaExpresieiPostfixate(exprPostfix, lgCoada);
            cout << valoare << '\n';
            for (int i = 1; i <= lgCoada; i++)
            {
                cout << exprPostfix[i] << ' ';
            }
            cout << '\n';
        }
        else
        {
            //face ceva
            cout << numeVariabila << '\n';
        }
    }
}
#endif // EVALUARE_INFIXAT_H_INCLUDED
