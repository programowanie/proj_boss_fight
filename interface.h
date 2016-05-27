#include <iostream>
#include <cstdlib>
#include <termios.h>
#include <stdio.h>
#include <string>
using namespace std;
 
static struct termios old, snew;
 
void randomowo (int tab[][5])
{
    for(int i = 0;i < 3;i++)
    {
        for(int y = 0;y < 5;y++)
            tab[i][y] = 0;
    }
    int wszyst_w_klasie,st,pom;
        for(int i = 0;i < 3;i++)
        {
            wszyst_w_klasie = 100;
            st=0;
            while (wszyst_w_klasie > 0)
            {
                if(st<4 && wszyst_w_klasie >= 13)
                {
                    if(wszyst_w_klasie > 40)
                        pom = 28;
                    else
                        pom = wszyst_w_klasie - 12;
                    tab[i][st] = rand()%pom+13;
                    wszyst_w_klasie -= tab[i][st];
                }
                else if(st<4 && wszyst_w_klasie < 13)
                {
                    tab[i][st] = wszyst_w_klasie;
                    wszyst_w_klasie -= tab[i][st];
                }
                else
                {
                    tab[i][4] = wszyst_w_klasie;
                    wszyst_w_klasie -= tab[i][4];
                }
                st++;
            }
        }
}
 
void initTermios(int echo)
{
  tcgetattr(0, &old);
  snew = old;
  snew.c_lflag &= ~ICANON;
  snew.c_lflag &= echo ? ECHO : ~ECHO;
  tcsetattr(0, TCSANOW, &snew);
}
 
void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}
 
char getch_(int echo)
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}
 
char getch(void)
{
  return getch_(0);
}

string nazwy[7] = {"int.  ","sila  ","wytrz.","zre   ","kryt. ","OK             ","RAND           "};
string klasa_tab[3] = {"Healer","Tank","DPS"};
void wyswietl(int tab[][5],int linijka,int klasa)
{
    system("clear");
    for(int i = 0;i < 8;i++)
    {
        if(i == 0) cout<<"  < "<<klasa_tab[klasa]<<" >     ";
        else if(i < 6)
        {
            cout<<"  < "<<nazwy[i-1]<<" "<<tab[klasa][i-1]<<" >   ";
        }
        else cout<<"  "<<nazwy[i-1];
        if(linijka == i) cout<<"<-----";
        cout<<endl;
    }
}
 
int inter(int tab[][5])
{
    int linijka = 0,klasa = 0;//pierwsza linijka to '0'
    char a = 'g';
    int punkty[] = {0,0,0};
    while(int(a) != 27) //&& (linijka != 6 || int(a) != 13)) //&&  (linijka != 7 || int(a) != 13))
    {
        switch(int(a))
        {
        case 119://w
            linijka = (linijka + 7) % 8;
            break;
        case 97://a
            if(linijka == 0)
                klasa = (klasa + 2) % 3;
            else if(linijka != 6 && linijka != 7 && punkty[klasa]>0 /*&& punkty[klasa]<=100*/ && tab[klasa][linijka-1] > 0)
            {
                tab[klasa][linijka-1] -= 1;
                punkty[klasa] -= 1;
            }
            break;
        case 115://s
            linijka = (linijka+1) % 8;
            break;
        case 100://d
            if(linijka == 0)
                klasa = (klasa + 1) % 3;
            else if(linijka != 6 && linijka != 7 /*&& punkty[klasa]>=0*/ && punkty[klasa]<100)
            {
                tab[klasa][linijka-1] +=1;
                punkty[klasa] += 1;
            }
            break;
        case 10://enter
            if(linijka == 7)//RAND
            {
                randomowo(tab);
                return 1;
            }
            if(linijka == 6 && (punkty[0] + punkty[1] + punkty[2]) == 300)//OK
                return 0;
            break;
        }
        wyswietl(tab,linijka,klasa);
        a = getch();
    }
}