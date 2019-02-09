#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <iomanip>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;
void line();
void text(string tekst,int x,int y);
void intro(int &b, int &k, int &w, int &r, int &n);
void wektor(int b, int k, int w, vector<queue <string> > &mapa);
void print_board(vector<queue <string> > mapa, int w, int k);
bool game_over(vector<queue <string> > &mapa, int k);
void round(vector<queue <string> > &mapa, int w, int k);
void shooting(vector<queue <string> > &mapa, int w, int k, int b, int &licznik);
void game(vector<queue <string> > &mapa, int w, int k, int b, int r, int n);


int main()
{

    vector<queue <string> >mapa;
    int bloczki;
    int kolumny;
    int wiersze;
    int random;
    int number;
    bool czy_wznowic=false;
    string tekst_koniec="TO PLAY AGAIN PRESS 1; TO EXIT PRESS 0";

    while(1)
    {
        intro(bloczki, kolumny, wiersze, random, number);
        wektor(bloczki, kolumny, wiersze, mapa);
        game(mapa,wiersze,kolumny,bloczki, random, number);
        system ("pause");
        system("cls");
        text(tekst_koniec,54,14);
        cin>>czy_wznowic;
        system("cls");
        if(czy_wznowic==false)
            return 0;
    }
}



void line()
{
    cout<<endl<<" -------------------------------------------------------------------"<<endl;
}

void text(string tekst, int x, int y)
{
    line();
    for(int i=0; i<3; i++)
    {

        if(i==1)
        {
            cout<<"|";
            cout.width(x);
            cout<<internal<<tekst;
            cout<<setw(y)<<"|"<<endl;
        }
        else if(i==2) cout <<"|" <<setw(68) <<"|";
        else cout <<"|" <<setw(68) <<"|" <<endl;
    }
    line();

}

void intro(int &b, int &k, int &w, int &r, int &n)
{
    string tekst1= "LONG TIME AGO IN THE GALAXY FAR, FAR AWAY...";
    text(tekst1, 54, 14);
    Sleep(5000);
    system("cls");

    line();
    for(int i=0; i<3; i++)
    {

        if(i==1)
        {
            cout<<"|";
            cout.width(45);
            cout<<internal<<"HELLO DEAR REBELLIAN";
            cout<<setw(23)<<"|"<<endl;
            cout<<"|";
            cout.width(54);
            cout<<internal<<"THE EMPEROR HAS MADE A CRITICAL ERROR";
            cout<<setw(14)<<"|"<<endl;
            cout<<"|";
            cout.width(54);
            cout<<internal<<"AND THE TIME FOR OUR ATTACK HAS COME";
            cout<<setw(14)<<"|"<<endl;
        }
        else if(i==2) cout <<"|" <<setw(68) <<"|";
        else cout <<"|" <<setw(68) <<"|" <<endl;
    }
    line();
    Sleep(6000);
    system("cls");

    string tekst5 = "MOVES YOU CAN MAKE: A - TURN LEFT; D - TURN RIGHT; W - SHOOTING";
    text(tekst5, 64, 4);
    Sleep(5000);
    system("cls");

    string tekst3 = "CHOOSE THE LEVEL OF DIFFICULTY FOR YOUR MISSION";
    text(tekst3, 56, 12);
    cin>>b;                                                              //gracz wpisuje iloœæ bloczków
    system("cls");


    string tekst4 = "CHOOSE HOW BIG THE FILED OF BATTLE SHOULD BE (WIDTH & HIGHT)"; //gracz wpisuje iloœæ kolumn i wierszy
    text(tekst4, 64, 4);
    cin>>k;
    cin>>w;
    system("cls");

    while(w<=b)
    {
        string tekst6 = "THE BATTLEFIELD NEEDS TO BE HIGHER - CHANGE IT";
        text(tekst6, 54, 14);
        system("cls");

        string tekst4 = "CHOOSE HOW BIG THE FILED OF BATTLE SHOULD BE (WIDTH THEN HIGHT)";
        text(tekst4, 64, 4);
        cin>>k;
        cin>>w;
        system("cls");

        if(w>b)break;
    }

    string tekst7 = "CHOOSE NUMBERS OF YOUR TWO FAVOURITE STAR WARS MOVIES (1-8)";
    text(tekst7, 64, 4);
    cin>>r;
    cin>>n;
    system("cls");

    string tekst2 = "AND MAY THE FORCE BE WITH YOU";
    text(tekst2, 50, 18);
    Sleep(2000);
    system("cls");
}

void wektor(int b, int k, int w, vector< queue <string> > & mapa)
{
    srand(time(NULL));
    int los;
    int poz_start=rand()%k;

    for(int i=0; i<k; i++)              //zape³niani wektora kolejkami
    {
        mapa.push_back(queue<string>());
    }

    string blok = "####";
    string bonus1 = "#::#";
    string bonus2 = "#++#";
    string xwing  = ">||<";


    for(int i=0; i<k; i++)
        for(int j=0; j<w-b; j++)
            if(j==0 and i==poz_start)
                mapa[i].push(xwing);
            else
                mapa[i].push("    ");

    for(int i=0; i<k; i++)                //zape³nianie pola gry bloczkami
    {

        for(int j=0; j<b; j++)
        {
            los=rand()%10;
            if(los==0 or los==1)
                mapa[i].push(bonus1);
            else if(los==2)
                mapa[i].push(bonus2);
            else
                mapa[i].push(blok);
        }
    }
}
void print_board(vector<queue <string> > mapa, int w, int k)  //rysuje plansze
{
    vector<stack <string> > stos;                           //tworzenie wektora stosu zeby odwrocic kolejke do wypisanie
    for(int i=0; i<k; i++)
        stos.push_back(stack <string>());
    for(int i=0; i<k; i++)
    {
        for(int j=0; j<w; j++)
        {
            stos[i].push(mapa[i].front());                  //zapisuje do stosow elementy kolejek
            mapa[i].pop();
        }

    }

    for(int i=0; i<w; i++)
    {
        for(int j=0; j<k; j++)
        {
            cout<<stos[j].top()<<" ";                    //wypisuje wektor stosow
            stos[j].pop();

        }
        cout<<endl;
    }
}

bool game_over(vector<queue <string> > &mapa, int k)
{
    bool przegrana = false;
    for(int i=0; i<k; i++)
    {
        if((mapa[i].front()==("####"))||(mapa[i].front()==("#::#"))||(mapa[i].front()==("#++#")))
            przegrana = true;
    }
    if(przegrana==true)
    {
        string tekst= "GAME OVER";
        text(tekst, 34, 34);
    }
    return przegrana;
}

void round(vector<queue <string> > &mapa, int w, int k)
{

    int los;
    bool runda = false;
    srand(time(NULL));



    for(int i=0; i<k; i++)
    {
        if(mapa[i].front()==(">||<"))
        {
            mapa[i].pop();
            los=rand()%10;
            if(los==0 or los==1)
                mapa[i].push("#++#");
            else if(los==2)
                mapa[i].push("#::#");
            else
                mapa[i].push("####");
            mapa[i].pop();
            mapa[i].push(">||<");
            while(1)
            {
                if(mapa[i].front()==(">||<"))
                    break;
                mapa[i].push(mapa[i].front());
                mapa[i].pop();
            }


        }
        else if(mapa[i].front()==("    "))
        {

            mapa[i].pop();
            los=rand()%10;
            if(los==0 or los==1)
                mapa[i].push("#++#");
            else if(los==2)
                mapa[i].push("#::#");
            else
                mapa[i].push("####");

            for(int j=0; j<w; j++)
            {
                mapa[i].push(mapa[i].front());
                mapa[i].pop();
            }

        }

    }

}

void shooting (vector<queue <string> > &mapa, int w, int k, int b, int &licznik)
{
    bool zestrzelony_bloczek = false;
    for(int i=0; i<k; i++)
    {
        if(mapa[i].front()==(">||<"))
        {
            mapa[i].pop();
            mapa[i].push(">||<");
            while(1)
            {
                if(!(mapa[i].front()==("    "))) break;
                mapa[i].pop();
                mapa[i].push("    ");
            }
            if(mapa[i].front()==("####"))
            {
                mapa[i].pop();
                mapa[i].push("    ");
                while(1)
                {
                    if((mapa[i].front()==(">||<"))) break;
                    mapa[i].push(mapa[i].front());
                    mapa[i].pop();
                }
                system("cls");

            }
            else if(mapa[i].front()==("#++#"))
            {
                mapa[i].pop();
                mapa[i].push("    ");
                zestrzelony_bloczek = true;

                while(1)
                {
                    if((mapa[i].front()==(">||<"))) break;
                    mapa[i].pop();
                    mapa[i].push("    ");
                }
                system("cls");
            }
            else if(mapa[i].front()==(">||<"))
            {
                cout<<"DO NOT SHOOT TO EMPTY SPACE!"<<endl<<endl;
                Sleep(2000);
                system("cls");

            }
            else if(mapa[i].front()==("#::#"))
            {
                mapa[i].pop();
                mapa[i].push("    ");
                zestrzelony_bloczek = true;
                while(1)
                {
                    if((mapa[i].front()==(">||<"))) break;
                    mapa[i].push(mapa[i].front());
                    mapa[i].pop();
                }
                licznik = licznik - 2;
                system("cls");
            }

        }
    }



}


void game(vector<queue <string> > &mapa, int w, int k, int b, int r, int n)
{
    char wybor;
    bool p=false;
    int licznik=0;                // licznik ruchów w grze

    r=r+(rand()%n);

    string buf;
    queue<string> kolejka;
    while(1)
    {
        p=false;
        print_board( mapa,w,k);


        cin>>wybor;

        switch (wybor)
        {
        case 100:
        {

            for(int i=0; i<k; i++)
            {
                if(mapa[i].front()==(">||<"))
                {
                    licznik++;
                    if(i+1<k)
                    {
                        mapa[i].pop();
                        mapa[i].push("    ");
                        for(int j=0; j<w-1; j++)
                        {
                            mapa[i].push(mapa[i].front());
                            mapa[i].pop();
                        }
                        mapa[i+1].push(">||<");
                        mapa[i+1].pop();
                        for(int j=0; j<w-1; j++)
                        {
                            mapa[i+1].push(mapa[i+1].front());
                            mapa[i+1].pop();
                            p=true;
                        }
                        system("cls");
                    }
                    else
                    {
                        cout<<"YOU CAN'T GO ANY FURTHER RIGHT! MAKE ANOTHER MOVE!";
                        cout<<endl<<endl;
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                }

                if(p==true) break;
            }
            licznik ++;
        }
        break;

        case 97:
        {

            for(int i=0; i<k; i++)
            {
                licznik++;
                if(mapa[i].front()==">||<")
                {
                    if(i-1>=0)
                    {
                        mapa[i].pop();
                        mapa[i].push("    ");
                        for(int j=0; j<w-1; j++)
                        {
                            mapa[i].push(mapa[i].front());
                            mapa[i].pop();

                        }
                        mapa[i-1].push(">||<");
                        mapa[i-1].pop();
                        for(int j=0; j<w-1; j++)
                        {
                            mapa[i-1].push(mapa[i-1].front());
                            mapa[i-1].pop();
                            p=true;
                        }
                        system("cls");
                    }
                    else
                    {
                        cout<<"YOU CAN'T GO ANY FURTHER LEFT! MAKE ANOTHER MOVE!";
                        cout<<endl<<endl;
                        Sleep(2000);
                        system("cls");
                        break;

                    }
                }

                if(p==true) break;
            }

            licznik++;
        }
        break;
        case 119:
            shooting(mapa,w,k,b,licznik);
            licznik++;
            break;

        }
        if(licznik%r==0)
            round(mapa, w, k);
        if(game_over(mapa,k)==true)
        {
            for(int m=0; m<k; m++)                  //czysci kolejke przed nastepna gra
                while(!(mapa[m].empty()))
                {
                    mapa[m].pop();
                }
            break;
        }
        {
        }

    }
}
