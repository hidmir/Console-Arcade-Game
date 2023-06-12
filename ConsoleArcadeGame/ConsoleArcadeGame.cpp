#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <string>
using namespace std;
//Deklaracja struktury sluzacej do stworzenia gracza
struct Player
{
    int x,y;
};
//Deklaracja struktury sluzacej do stworzenia przeciwnika poruszajacego sie tylko poziomo
struct Enemypoz
{
    int x,y;
    bool wprawo;
};
//Deklaracja struktury sluzacej do stworzenia przeciwnika poruszajacego sie tylko pionowo
struct Enemypion
{
    int x,y;
    bool wgore;
};
//Deklaracja struktury sluzacej do stworzenia obiektu przesuwnego
struct Movableobject
{
    int x,y;
};
//Deklaracja struktury sluzacej do stworzenia obiektu konczacego dany poziom
struct Endlevelobject
{
    int x,y;
};
//Deklaracja struktury sluzacej do stworzenia obiektu otwierajacego zablokowane przejscie
struct Unlockobject
{
    int x,y;
};

Player player;
Enemypoz enemypoz[15];   //zmienne sa deklarowanie jako tablice o wymiarach odpowiadajacych
Enemypion enemypion[15]; //maksymalnej ilosci danych obiektow wystepujacych w grze
Movableobject movableobject[30];
Endlevelobject endlevelobject[1];
Unlockobject unlockobject[5];
bool newgame,backtomainmenu,wyjscie; //zmienne wystepujace w glownych petlach na podstawie ktorych gra dziala
bool unlock,unlock1,unlock2,unlock3,unlock4,unlock5; //zmienne sluzace do odblokowania przejsc
char c; //zmienna w ktorej zapisuje sie aktualnie wcisniety klawisz
int completedlevels; //zmienna sluzaca do zapisania ilosci ukonczonych poziomow
int wybor2; //zmienna na podstawie ktorej wlaczaja sie poszczegolne poziomy

//kolory wersja 1
const int k1=7,k2=10,k3=13,k4=4,k5=9,k6=4,k7=6,k8=1,k9=13,k10=11,k11=8,k12=15,k13=14,k14=4,k15=k10,k16=10,k17=k10;
const int k18=6,k19=4,k20=8,k21=4,k22=4,k23=12,k24=6;

//kolory wersja 2
//const int k1=7,k2=10,k3=12,k4=13,k5=9,k6=11,k7=12,k8=6,k9=7,k10=11,k11=8,k12=15,k13=14,k14=12,k15=11,k16=10,k17=11;
//const int k18=14,k19=12,k20=8,k21=12,k22=12,k23=4,k24=14;

//k1=movableobject   k2=endlevelobject   k3=enemypoz   k4=enemypion   k5=specialcreate5,specialcreate61
//k6=specialcreate62   k7=specialcreate63   k8=specialcreate64   k9=specialcreate65   k10=player
//k11=movedmovableobject   k12=sterowanieinfo   k13=sciany   k14=playerdefeated1   k15=playerdefeated2
//k16=endlevelanimation1   k17=endlevelanimation2   k18=keyinfo   k19=availablelevel   k20=unavailablelevel
//k21=menuinfo   k22=completepreviouslevels1   k23=completepreviouslevels2   k24=zaznaczenie

//funkcja umozliwiajaca przejscie do konkretnych koordynatow
void gotoxy(int x, int y)
{
    COORD xy;
    xy.X=x; //Deklaracja wspolrzednej X
    xy.Y=y; //Deklaracja wspolrzednej Y
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),xy);//Przyjęcie argumentow takich jak standardowe urzadzenie wyjscia oraz strutura COORD dla funkcji SetConsoleCursorPosition
}
//funkcja tworzaca obiekt przesuwny. Jej argumentami jest numer obiektu oraz koordynaty
void createmovableobject(int n,int x,int y)
{
    movableobject[n].x=x;
    movableobject[n].y=y;
    gotoxy(x,y); //przejscie do koordynatow obiektu
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k1); //Funkcja zmieniajaca kolor znakow, przyjmuje za argument standardowe urzadzenie wyjscia oraz atrybut dla tekstu
    cout<<"@"; //wyswietlenie obiektu
}
//funkcja tworzaca obiekt konczacy poziom. Jej argumentami jest numer obiektu oraz koordynaty
void createendlevelobject(int n,int x,int y)
{
    endlevelobject[n].x=x;
    endlevelobject[n].y=y;
    gotoxy(x,y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k2);
    cout<<"O";
}
//funkcja tworzaca przeciwnika poruszajacego sie tylko poziomo. Jej argumentami jest numer obiektu, koordynaty oraz kierunek poczatkowego ruchu
void createenemypoz(int n,int x,int y,bool wprawo)
{
    enemypoz[n].x=x;
    enemypoz[n].y=y;
    enemypoz[n].wprawo=wprawo;
    gotoxy(x,y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k3);
    cout<<"<";
}
//funkcja tworzaca przeciwnika poruszajacego sie tylko pionowo. Jej argumentami jest numer obiektu, koordynaty oraz kierunek poczatkowego ruchu
void createenemypion(int n,int x,int y,bool wgore)
{
    enemypion[n].x=x;
    enemypion[n].y=y;
    enemypion[n].wgore=wgore;
    gotoxy(x,y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k4);
    cout<<"V";
}

//funkcja tworzaca przecinikow dla poziomu drugiego
void loadenemy2()
{
    createenemypoz(0,30,14,true);
    createenemypion(0,37,4,false);
}
//funkcja tworzaca przecinikow dla poziomu trzeciego
void loadenemy3()
{
    createenemypoz(0,32,13,false);
    createenemypoz(1,34,6,true);
    createenemypoz(2,34,10,true);
    createenemypion(0,32,16,false);
    createenemypion(1,37,16,false);
    createenemypion(2,38,5,false);
}
//funkcja tworzaca przecinikow dla poziomu czwartego
void loadenemy4()
{
    createenemypion(0,32,16,false);
    createenemypion(1,25,6,false);
    createenemypion(2,35,6,false);
    createenemypion(3,36,6,false);
    createenemypion(4,37,6,false);
    createenemypion(5,38,6,false);
    createenemypion(6,39,6,false);
    createenemypion(7,40,6,false);
}
//funkcja tworzaca przecinikow dla poziomu piatego
void loadenemy5()
{
    createenemypoz(0,27,17,true);
    createenemypion(0,33,5,false);
    createenemypion(1,34,5,false);
    createenemypion(2,35,5,false);
}
//funkcja tworzaca przecinikow dla poziomu szostego
void loadenemy6()
{
    createenemypoz(0,30,17,true);
    createenemypoz(1,53,17,false);
    createenemypoz(2,53,16,false);
    createenemypoz(3,53,15,false);
    createenemypoz(4,45,9,true);
    createenemypoz(5,53,7,false);
    createenemypoz(6,32,7,true);
    createenemypoz(7,32,11,true);
    createenemypoz(8,18,5,true);
    createenemypion(0,47,11,false);
    createenemypion(1,28,8,false);
    createenemypion(2,26,11,false);
    createenemypion(3,24,16,true);
    createenemypion(4,22,16,true);
}
//funkcja tworzaca przecinikow dla poziomu siodmego
void loadenemy7()
{
    createenemypoz(0,36,14,false);
    createenemypoz(1,32,12,false);
    createenemypoz(2,18,20,true);
    createenemypoz(3,15,16,true);
    createenemypoz(4,15,14,true);
    createenemypoz(5,16,10,true);
    createenemypoz(6,18,6,false);
    createenemypoz(7,9,4,true);
    createenemypoz(8,22,3,true);
    createenemypoz(9,51,14,false);
    createenemypoz(10,50,17,false);
    createenemypoz(11,56,19,false);
    createenemypion(0,13,14,false);
    createenemypion(1,10,9,false);
    createenemypion(2,16,8,true);
    createenemypion(3,20,2,false);
    createenemypion(4,26,5,false);
    createenemypion(5,28,7,true);
    createenemypion(6,43,2,false);
    createenemypion(7,45,5,false);
    createenemypion(8,47,5,false);
    createenemypion(9,49,5,false);
    createenemypion(10,51,5,false);
    createenemypion(11,53,12,false);
    createenemypion(12,38,20,true);
}
//funkcja dla poziomu piatego tworzaca sciany posiadajace mozliwosc odblokowania oraz obiekt sluzacy do ich odblokowania
void specialcreate5()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k5);
    gotoxy(32,9);
    cout<<"#";
    gotoxy(33,9);
    cout<<"#";
    gotoxy(34,9);
    cout<<"#";
    gotoxy(35,9);
    cout<<"#";
    gotoxy(36,9);
    cout<<"#";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k5);
    unlockobject[1].x=28;
    unlockobject[1].y=10;
    gotoxy(unlockobject[1].x,unlockobject[1].y);
    cout<<"+";
}
//funkcja dla poziomu szostego tworzaca sciany posiadajace mozliwosc odblokowania oraz obiekt sluzacy do ich odblokowania
void specialcreate6()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k5);
    gotoxy(29,15);
    cout<<"#";
    gotoxy(30,15);
    cout<<"#";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k5);
    unlockobject[1].x=35;
    unlockobject[1].y=20;
    gotoxy(unlockobject[1].x,unlockobject[1].y);
    cout<<"+";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k6);
    gotoxy(47,18);
    cout<<"#";
    gotoxy(39,19);
    cout<<"#";
    gotoxy(39,20);
    cout<<"#";
    gotoxy(30,14);
    cout<<"#";
    gotoxy(30,13);
    cout<<"#";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k6);
    unlockobject[2].x=38;
    unlockobject[2].y=16;
    gotoxy(unlockobject[2].x,unlockobject[2].y);
    cout<<"+";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k7);
    gotoxy(43,18);
    cout<<"#";
    gotoxy(44,18);
    cout<<"#";
    gotoxy(48,17);
    cout<<"#";
    gotoxy(48,16);
    cout<<"#";
    gotoxy(48,15);
    cout<<"#";
    gotoxy(30,12);
    cout<<"#";
    gotoxy(30,11);
    cout<<"#";
    gotoxy(21,5);
    cout<<"#";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k7);
    unlockobject[3].x=53;
    unlockobject[3].y=5;
    gotoxy(unlockobject[3].x,unlockobject[3].y);
    cout<<"+";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k8);
    gotoxy(30,9);
    cout<<"#";
    gotoxy(30,10);
    cout<<"#";
    gotoxy(22,12);
    cout<<"#";
    gotoxy(35,7);
    cout<<"#";
    gotoxy(35,11);
    cout<<"#";
    gotoxy(35,13);
    cout<<"#";
    gotoxy(35,14);
    cout<<"#";
    gotoxy(35,15);
    cout<<"#";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k8);
    unlockobject[4].x=32;
    unlockobject[4].y=5;
    gotoxy(unlockobject[4].x,unlockobject[4].y);
    cout<<"+";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k9);
    gotoxy(43,14);
    cout<<"#";
    gotoxy(44,14);
    cout<<"#";
    gotoxy(30,7);
    cout<<"#";
    gotoxy(30,8);
    cout<<"#";
    gotoxy(24,12);
    cout<<"#";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k9);
    unlockobject[0].x=32;
    unlockobject[0].y=9;
    gotoxy(unlockobject[0].x,unlockobject[0].y);
    cout<<"+";
}
//Funkcja zwracajaca znak wystepujacy w miejscu kursora
wchar_t getCursorChar()
{
    wchar_t c = L'\0';
    CONSOLE_SCREEN_BUFFER_INFO con;
    if (GetStdHandle(STD_OUTPUT_HANDLE) != INVALID_HANDLE_VALUE && GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &con))
    {
        DWORD read = 0;
        if (!ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), &c, 1, con.dwCursorPosition, &read) || read != 1)
            c = L'\0';
    }
    return c;
}
//Funkcja odczytujaca znak w okreslonych koordynatach
char readChar (int x,int y)
{
    gotoxy(x,y);
    char ccccc=getCursorChar();
    return ccccc;
}
//funkcja dla poziomu piatego sluzaca do odblokowania sciany
void specialunlock5()
{
    if(readChar(unlockobject[1].x,unlockobject[1].y)=='@')
    {
        gotoxy(32,9);
        cout<<" ";
        gotoxy(33,9);
        cout<<" ";
        gotoxy(34,9);
        cout<<" ";
        gotoxy(35,9);
        cout<<" ";
        gotoxy(36,9);
        cout<<" ";
        unlock=true;
    }
}
//funkcja dla poziomu szostego sluzaca do odblokowania pierwszej sciany
void specialunlock61()
{
    if(readChar(unlockobject[1].x,unlockobject[1].y)=='@')
    {
        gotoxy(29,15);
        cout<<" ";
        gotoxy(30,15);
        cout<<" ";
        unlock1=true;
    }
}
//funkcja dla poziomu szostego sluzaca do odblokowania drugiej sciany
void specialunlock62()
{
    if(readChar(unlockobject[2].x,unlockobject[2].y)=='@')
    {
        gotoxy(47,18);
        cout<<" ";
        gotoxy(39,19);
        cout<<" ";
        gotoxy(39,20);
        cout<<" ";
        gotoxy(30,14);
        cout<<" ";
        gotoxy(30,13);
        cout<<" ";
        unlock2=true;
    }
}
//funkcja dla poziomu szostego sluzaca do odblokowania trzeciej sciany
void specialunlock63()
{
    if(readChar(unlockobject[3].x,unlockobject[3].y)=='@')
    {
        gotoxy(43,18);
        cout<<" ";
        gotoxy(44,18);
        cout<<" ";
        gotoxy(48,17);
        cout<<" ";
        gotoxy(48,16);
        cout<<" ";
        gotoxy(48,15);
        cout<<" ";
        gotoxy(30,12);
        cout<<" ";
        gotoxy(30,11);
        cout<<" ";
        gotoxy(21,5);
        cout<<" ";
        unlock3=true;
    }
}
//funkcja dla poziomu szostego sluzaca do odblokowania czwartej sciany
void specialunlock64()
{
    if(readChar(unlockobject[4].x,unlockobject[4].y)=='@')
    {
        gotoxy(30,9);
        cout<<" ";
        gotoxy(30,10);
        cout<<" ";
        gotoxy(22,12);
        cout<<" ";
        gotoxy(35,7);
        cout<<" ";
        gotoxy(35,11);
        cout<<" ";
        gotoxy(35,13);
        cout<<" ";
        gotoxy(35,14);
        cout<<" ";
        gotoxy(35,15);
        cout<<" ";
        unlock4=true;
    }
}
//funkcja dla poziomu szostego sluzaca do odblokowania piatej sciany
void specialunlock65()
{
    if(readChar(unlockobject[0].x,unlockobject[0].y)=='@')
    {
        cout<<" ";
        gotoxy(44,14);
        cout<<" ";
        gotoxy(43,14);
        cout<<" ";
        gotoxy(30,7);
        cout<<" ";
        gotoxy(30,8);
        cout<<" ";
        gotoxy(24,12);
        cout<<" ";
        unlock5=true;
    }
}
//funkcja tworzaca gracza
void createplayer()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k10);
    gotoxy(player.x,player.y);
    cout<<'X';
}
//funkcja odpowiadajaca za ruch gracza
void moving()
{
    if(c=='w'||c=='s'||c=='a'||c=='d'||c=='W'||c=='S'||c=='A'||c=='D')
    {
        if (c=='w'||c=='W') //ruch w gore
        {
            gotoxy(player.x,player.y);
            cout<<" ";
            if ((readChar(player.x,player.y-1)!= '#')&&(readChar(player.x,player.y-1)!= '+')&&(readChar(player.x,player.y-1)!= 'H'))
            {
                if (readChar(player.x,player.y-1)=='@')
                {
                    if ((readChar(player.x,player.y-2)==' ')&&(readChar(player.x,player.y-5)!='H')&&(readChar(player.x,player.y-3)!='H')&&(readChar(player.x,player.y-4)!='H')||(readChar(player.x,player.y-2)=='+')&&(readChar(player.x,player.y-5)!='H')&&(readChar(player.x,player.y-3)!='H')&&(readChar(player.x,player.y-4)!='H'))
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k11);
                        gotoxy(player.x,player.y-2);
                        cout<<"@";
                        player.y-=1;
                    }
                }else
                    player.y-=1;
            }
        }
        if (c=='s'||c=='S') //ruch w dol
        {
            gotoxy(player.x,player.y);
            cout<<" ";
            if ((readChar(player.x,player.y+1)!= '#')&&(readChar(player.x,player.y+1)!= '+')&&(readChar(player.x,player.y+1)!= 'H'))
            {
                if (readChar(player.x,player.y+1)=='@')
                {
                    if ((readChar(player.x,player.y+2)==' ')&&(readChar(player.x,player.y+5)!='H')&&(readChar(player.x,player.y+3)!='H')&&(readChar(player.x,player.y+4)!='H')||(readChar(player.x,player.y+2)=='+')&&(readChar(player.x,player.y+5)!='H')&&(readChar(player.x,player.y+3)!='H')&&(readChar(player.x,player.y+4)!='H'))
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k11);
                        gotoxy(player.x,player.y+2);
                        cout<<"@";
                        player.y+=1;
                    }
                }else
                    player.y+=1;
            }
        }
        if (c=='a'||c=='A') //ruch w lewo
        {
            gotoxy(player.x,player.y);
            cout<<" ";
            if ((readChar(player.x-1,player.y)!= '#')&&(readChar(player.x-1,player.y)!= '+')&&(readChar(player.x-1,player.y)!= 'H'))
            {
                if (readChar(player.x-1,player.y)=='@')
                {
                    if ((readChar(player.x-2,player.y)==' ')&&(readChar(player.x-5,player.y)!='H')&&(readChar(player.x-3,player.y)!='H')&&(readChar(player.x-4,player.y)!='H')||(readChar(player.x-2,player.y)=='+')&&(readChar(player.x-5,player.y)!='H')&&(readChar(player.x-3,player.y)!='H')&&(readChar(player.x-4,player.y)!='H'))
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k11);
                        gotoxy(player.x-2,player.y);
                        cout<<"@";
                        player.x-=1;
                    }
                }else
                    player.x-=1;
            }
        }
        if (c=='d'||c=='D') //ruch w prawo
        {
            gotoxy(player.x,player.y);
            cout<<" ";
            if ((readChar(player.x+1,player.y)!= '#')&&(readChar(player.x+1,player.y)!= '+')&&(readChar(player.x+1,player.y)!= 'H'))
            {
                if (readChar(player.x+1,player.y)=='@')
            {
                    if ((readChar(player.x+2,player.y)==' ')&&(readChar(player.x+5,player.y)!='H')&&(readChar(player.x+3,player.y)!='H')&&(readChar(player.x+4,player.y)!='H')||(readChar(player.x+2,player.y)=='+')&&(readChar(player.x+5,player.y)!='H')&&(readChar(player.x+3,player.y)!='H')&&(readChar(player.x+4,player.y)!='H'))
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k11);
                        gotoxy(player.x+2,player.y);
                        cout<<"@";
                        player.x+=1;
                        gotoxy(player.x+1,player.y);
                        cout<<"@";
                    }
                }else
                    player.x+=1;
            }
        }
        if(c=='w'||c=='s'||c=='a'||c=='d'||c=='W'||c=='S'||c=='A'||c=='D')
            createplayer();
    }
}
//funkcja generujaca opis sterowania
void sterowanieinfo()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k12);
    gotoxy(1,26);
    cout<<"| W/S/A/D - Move character |";
    gotoxy(50,26);
    cout<<" ESC - Level menu |";
    gotoxy(29,26);
    cout<<" R - Restart level |";
}
//funkcja sluzaca do wczytania danego poziomu z pliku tekstowego oraz przeniesieniu go na ekran konsoli
void startlevel(string fileName)
{
    string getcontent;
    ifstream file(fileName.c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k13);
    if(file.is_open())
    {
        int movableObjectID = 0; //TODO:Just do this in better way xD
        int y = 0;
        while(getline(file,getcontent))
        {
            for(int x = 0; x < getcontent.size(); x++)
            {
                if(getcontent[x] == 'O')
                {
                    createendlevelobject(0, x, y);
                }
                else if(getcontent[x] == '@')
                {
                    createmovableobject(movableObjectID++, x, y);
                }
                else
                {
                    gotoxy(x,y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k13);
                    cout<<getcontent[x]<<endl;
                }
            }
            y++;
        }
    }
}

//funkcja wyswietlajaca animacje zanikania ekranu
void animation1()
{
    for(int i=0;i<=30;i++)
    {
        gotoxy(0,0+i);
        cout<<"                                                                      ";
        Sleep(10);
    }
    gotoxy(0,0);
}
//funkcja wyswietlajaendlevelanimation1ca animacje zanikania ekranu
void animation2()
{
    for(int i=0;i<=29;i++)
    {
        gotoxy(0,29-i);
        cout<<"                                                                      ";
        Sleep(10);
    }
    gotoxy(0,0);
}
//funkcja wyswietlajaca animacje zanikania ekranu
void animation3()
{
    for(int i=0;i<=15;i++)
    {
        gotoxy(0,0+i);
        cout<<"                                                                      ";
        Sleep(10);
        gotoxy(0,29-i);
        cout<<"                                                                      ";
        Sleep(10);
        if(i==15)
            Sleep(50);
    }
    gotoxy(0,0);
}
//funkcja resetujaca poziom pierwszy
void resetlevel1()
{
    animation3();
    player.x=34;
    player.y=18;
    startlevel("level_1.txt");
    sterowanieinfo();
    createobject1();
    createplayer();
}
//funkcja resetujaca poziom drugi
void resetlevel2()
{
    animation3();
    player.x=34;
    player.y=19;
    startlevel("level_2.txt");
    sterowanieinfo();
    loadenemy2();
    createobject2();
    createplayer();
}
//funkcja resetujaca poziom trzeci
void resetlevel3()
{
    animation3();
    player.x=40;
    player.y=20;
    startlevel("level_3.txt");
    sterowanieinfo();
    loadenemy3();
    createobject3();
    createplayer();
}
//funkcja resetujaca poziom czwarty
void resetlevel4()
{
    animation3();
    player.x=44;
    player.y=18;
    startlevel("level_4.txt");
    sterowanieinfo();
    loadenemy4();
    createobject4();
    createplayer();
}
//funkcja resetujaca poziom piaty
void resetlevel5()
{
    animation3();
    player.x=29;
    player.y=14;
    startlevel("level_5.txt");
    sterowanieinfo();
    loadenemy5();
    createobject5();
    specialcreate5();
    unlock=false;
    createplayer();
}
//funkcja resetujaca poziom szosty
void resetlevel6()
{
    animation3();
    player.x=35;
    player.y=18;
    startlevel("level_6.txt");
    sterowanieinfo();
    loadenemy6();
    createobject6();
    specialcreate6();
    unlock1=false;
    unlock2=false;
    unlock3=false;
    unlock4=false;
    unlock5=false;
    createplayer();
}
//funkcja resetujaca poziom siodmy
void resetlevel7()
{
    animation3();
    player.x=34;
    player.y=11;
    startlevel("level_7.txt");
    sterowanieinfo();
    loadenemy7();
    createobject7();
    createplayer();
}
//funkcja wyswietlajaca animacje smierci gracza oraz resetujaca poziom
void playerdefeated()
{
    for (int i=0; i<=4; i++)
        {
            gotoxy(player.x,player.y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
            cout<<'x';
            Sleep(150);
            gotoxy(player.x,player.y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
            cout<<'X';
            Sleep(150);
        }
        switch(wybor2)
        {
        case 0:
            resetlevel1();
            break;
        case 2:
            resetlevel2();
            break;
        case 4:
            resetlevel3();
            break;
        case 6:
            resetlevel4();
            break;
        case 8:
            resetlevel5();
            break;
        case 10:
            resetlevel6();
            break;
        case 12:
            resetlevel7();
            break;
        }
}
//funkcja odpowiadajaca za ruch przeciwnikow poruszajacych sie tylko poziomo
void enemypozmoving(int amountofenemypoz)
{
    for (int i=0;i<=amountofenemypoz;i++)
    {
        if (enemypoz[i].wprawo==false)
        {
            gotoxy(enemypoz[i].x,enemypoz[i].y);
            cout<<" ";
            if ((readChar(enemypoz[i].x-1,enemypoz[i].y)!= '#')&&(readChar(enemypoz[i].x-1,enemypoz[i].y)!= '@')&&(readChar(enemypoz[i].x-2,enemypoz[i].y)!= '@')&&(readChar(enemypoz[i].x-1,enemypoz[i].y)!= 'H'))
                {
                    enemypoz[i].x-=1;
                    gotoxy(enemypoz[i].x,enemypoz[i].y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k3);
                    cout<<"<";
                }
            else
                enemypoz[i].wprawo=true;
        }
        if (enemypoz[i].wprawo==true)
        {
            gotoxy(enemypoz[i].x,enemypoz[i].y);
            cout<<" ";
            if ((readChar(enemypoz[i].x+1,enemypoz[i].y)!= '#')&&(readChar(enemypoz[i].x+1,enemypoz[i].y)!= '@')&&(readChar(enemypoz[i].x+2,enemypoz[i].y)!= '@')&&(readChar(enemypoz[i].x+1,enemypoz[i].y)!= 'H'))
                {
                    enemypoz[i].x+=1;
                    gotoxy(enemypoz[i].x,enemypoz[i].y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k3);
                    cout<<">";
                }
            else
                enemypoz[i].wprawo=false;
        }
        if((readChar(enemypoz[i].x,enemypoz[i].y)==readChar(player.x,player.y))) //warunek smierci gracza nr1
            playerdefeated();
        if(enemypoz[i].x==player.x&&enemypoz[i].y==player.y) //warunek smierci gracza nr2
            playerdefeated();
    }

}
//funkcja odpowiadajaca za ruch przeciwnikow poruszajacych sie tylko pionowo
void enemypionmoving(int amountofenemypion)
{
    for (int i=0;i<=amountofenemypion;i++)
    {
        if (enemypion[i].wgore==false)
        {
            gotoxy(enemypion[i].x,enemypion[i].y);
            cout<<" ";
            if ((readChar(enemypion[i].x,enemypion[i].y+1)!= '#')&&(readChar(enemypion[i].x,enemypion[i].y+1)!= '@')&&(readChar(enemypion[i].x,enemypion[i].y+2)!= '@')&&(readChar(enemypion[i].x,enemypion[i].y+1)!= 'H'))
                {
                    enemypion[i].y+=1;
                    gotoxy(enemypion[i].x,enemypion[i].y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k4);
                    cout<<"V";
                }
            else
                enemypion[i].wgore=true;

        }
        if (enemypion[i].wgore==true)
        {
            gotoxy(enemypion[i].x,enemypion[i].y);
            cout<<" ";
            if ((readChar(enemypion[i].x,enemypion[i].y-1)!= '#')&&(readChar(enemypion[i].x,enemypion[i].y-1)!= '@')&&(readChar(enemypion[i].x,enemypion[i].y-2)!= '@')&&(readChar(enemypion[i].x,enemypion[i].y-1)!= 'H'))
                {
                    enemypion[i].y-=1;
                    gotoxy(enemypion[i].x,enemypion[i].y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k4);
                    cout<<"V";
                }
            else
                enemypion[i].wgore=false;
        }
        if((readChar(enemypion[i].x,enemypion[i].y)==readChar(player.x,player.y))) //warunek smierci gracza nr1
            playerdefeated();
        if(((enemypion[i].x)==(player.x))&&((enemypion[i].y)==(player.y))) //warunek smierci gracza nr2
            playerdefeated();
    }

}
//funkcja zapisujaca postepy gracza do pliku tekstowego
void savetofile()
{
    completedlevels++;
    fstream plik;
    plik.open("gamesaves.txt",ios::out);
    plik<<completedlevels<<endl;
    plik.close();
}
//funkcja zapisujaca postepy gry po ukonczeniu danego poziomu
void savecomplete()
{
    switch(wybor2)
    {
    case 0:
        {
            if(completedlevels==0)
                savetofile();
            break;
        }
    case 2:
        {
            if(completedlevels==1)
                savetofile();
            break;
        }
    case 4:
        {
            if(completedlevels==2)
                savetofile();
            break;
        }
    case 6:
        {
            if(completedlevels==3)
                savetofile();
            break;
        }
    case 8:
        {
            if(completedlevels==4)
                savetofile();
            break;
        }
    case 10:
        {
            if(completedlevels==5)
                savetofile();
            break;
        }
    case 12:
        {
            if(completedlevels==6)
                savetofile();
            break;
        }
    }
}
//funkcja odpowiedzialna za warunek ukonczenia poziomu
void gettoendoflevel()
{
    if((player.x)==(endlevelobject[0].x)&&(player.y)==(endlevelobject[0].y))
    {
        for (int i=0; i<=2; i++) //petla wyswietlajaca animacje ukonczenia poziomu
        {
            gotoxy(player.x,player.y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k16);
            cout<<'x';
            Sleep(150);
            gotoxy(player.x,player.y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k17);
            cout<<'X';
            Sleep(150);
        }
        newgame=false;
        savecomplete();
    }
}
//funkcja odpowiedzialna za odczytywanie wcisnietych klawiszy
void playermove()
{
    c='0';
    if (_kbhit()==1)
        c=_getch();
    //funkcja _kbhit sprawia, ze wszystkie obiekty poruszaja sie bez przerwy niezaleznie od tego czy zostal wcisniety jakis klawisz
}
//funkcja odpowiadajaca za resetowanie poziomu poprzez nacisniecie klawisza 'R'
void resetonkey()
{
    if(c=='r'||c=='R')
        switch(wybor2)
        {
        case 0:
            resetlevel1();
            break;
        case 2:
            resetlevel2();
            break;
        case 4:
            resetlevel3();
            break;
        case 6:
            resetlevel4();
            break;
        case 8:
            resetlevel5();
            break;
        case 10:
            resetlevel6();
            break;
        case 12:
            resetlevel7();
            break;
        }
}

//funkcje startgame sluza do ustawienia poczatkowych koordynatow gracza, wczytania poziomu, opisu sterowania, utworzenia obiektow i wczytania przeciwnikow dla danego poziomu

void startgame1()
{
    player.x=34;
    player.y=18;
    startlevel("level_1.txt");
    sterowanieinfo();
    createplayer();
}

void startgame2()
{
    player.x=34;
    player.y=19;
    startlevel("level_2.txt");
    sterowanieinfo();
    loadenemy2();
    createplayer();
}

void startgame3()
{
    player.x=40;
    player.y=20;
    startlevel("level_3.txt");
    sterowanieinfo();
    loadenemy3();
    createplayer();
}

void startgame4()
{
    player.x=44;
    player.y=18;
    startlevel("level_4.txt");
    sterowanieinfo();
    loadenemy4();
    createplayer();
}

void startgame5()
{
    player.x=29;
    player.y=14;
    startlevel("level_5.txt");
    sterowanieinfo();
    loadenemy5();
    specialcreate5();
    createplayer();
}

void startgame6()
{
    player.x=35;
    player.y=18;
    startlevel("level_6.txt");
    sterowanieinfo();
    loadenemy6();
    specialcreate6();
    createplayer();
}

void startgame7()
{
    player.x=34;
    player.y=11;
    startlevel("level_7.txt");
    sterowanieinfo();
    loadenemy7();
    createplayer();
}

//w funkcjach playlevel zawarta jest glowna petla na podstawie ktorej wlaczony jest dany poziom

void playlevel1()
{
    startgame1();
    newgame=true;
        while(newgame==true)
        {
            enemypozmoving(-1);
            enemypionmoving(-1);
            moving();
            playermove();
            gettoendoflevel();
            resetonkey();
            Sleep(50); //za pomoca funkcji Sleep okreslona jest predkosc przeciwnikow
            if (c==char(27)) //po wcisniesciu klawisza escape nastepuje powrot do menu
                newgame=false;
        }
        animation1(); //animacja wyjscia z poziomu
}

void playlevel2()
{
    startgame2();
    newgame=true;
        while(newgame==true)
        {
            enemypozmoving(0);
            enemypionmoving(0);
            moving();
            playermove();
            gettoendoflevel();
            resetonkey();
            Sleep(45);
            if (c==char(27))
                newgame=false;
        }
        animation1();
}

void playlevel3()
{
    startgame3();
    newgame=true;
        while(newgame==true)
        {
            enemypozmoving(2);
            enemypionmoving(2);
            moving();
            playermove();
            gettoendoflevel();
            resetonkey();
            Sleep(40);
            if (c==char(27))
                newgame=false;
        }
        animation1();
}

void playlevel4()
{
    startgame4();
    newgame=true;
        while(newgame==true)
        {
            enemypozmoving(-1);
            enemypionmoving(7);
            moving();
            playermove();
            gettoendoflevel();
            resetonkey();
            Sleep(35);
            if (c==char(27))
                newgame=false;
        }
        animation1();
}

void playlevel5()
{
    startgame5();
    newgame=true;
    unlock=false;
        while(newgame==true)
        {
            enemypozmoving(0);
            enemypionmoving(2);
            moving();
            playermove();
            gettoendoflevel();
            resetonkey();
            if (unlock==false) //warunek odblokowania przejscia
                specialunlock5();
            Sleep(40);
            if (c==char(27))
                newgame=false;
        }
        animation1();
}

void playlevel6()
{
    startgame6();
    newgame=true;
    unlock1=false;
    unlock2=false;
    unlock3=false;
    unlock4=false;
    unlock5=false;
        while(newgame==true)
        {
            enemypozmoving(8);
            enemypionmoving(4);
            moving();
            playermove();
            gettoendoflevel();
            resetonkey();
            Sleep(30);
            if (unlock1==false)
                specialunlock61();
            if (unlock2==false)
                specialunlock62();
            if (unlock3==false)
                specialunlock63();
            if (unlock4==false)
                specialunlock64();
            if (unlock5==false)
                specialunlock65();
            if (c==char(27))
                newgame=false;
        }
        animation1();
}

void playlevel7()
{
    startgame7();
    newgame=true;
        while(newgame==true)
        {
            enemypozmoving(11);
            enemypionmoving(12);
            moving();
            playermove();
            gettoendoflevel();
            resetonkey();
            Sleep(25);
            if (c==char(27))
                newgame=false;
        }
            animation1();
}
//funkcja odpowiedzialna za poprawne wyswietlanie menu wyboru poziomu
void menu2info()
{
    bool completedlevel1=false,completedlevel2=false,completedlevel3=false,completedlevel4=false,completedlevel5=false,completedlevel6=false,completedlevel7=false;
    if(completedlevels>=1)
    {
        completedlevel1=true;
        if(completedlevels>=2)
        {
            completedlevel2=true;
            if(completedlevels>=3)
            {
                completedlevel3=true;
                if(completedlevels>=4)
                {
                    completedlevel4=true;
                    if(completedlevels>=5)
                    {
                        completedlevel5=true;
                        if(completedlevels>=6)
                        {
                            completedlevel6=true;
                            if(completedlevels>=7)
                                completedlevel7=true;
                        }
                    }
                }
            }
        }
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k18);
    gotoxy(34,5);
    cout<<"[W]";
    gotoxy(34,23);
    cout<<"[S]";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k19);
    gotoxy(32,7);
    cout<<"LEVEL 1";
    switch(completedlevel1)
    {
    case 0:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k20);
        gotoxy(32,9);
        cout<<"LEVEL 2";
        break;
    case 1:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k19);
        gotoxy(32,9);
        cout<<"LEVEL 2";
        break;
    }
    switch(completedlevel2)
    {
    case 0:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k20);
        gotoxy(32,11);
        cout<<"LEVEL 3";
        break;
    case 1:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k19);
        gotoxy(32,11);
        cout<<"LEVEL 3";
        break;
    }
    switch(completedlevel3)
    {
    case 0:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k20);
        gotoxy(32,13);
        cout<<"LEVEL 4";
        break;
    case 1:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k19);
        gotoxy(32,13);
        cout<<"LEVEL 4";
        break;
    }
    switch(completedlevel4)
    {
    case 0:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k20);
        gotoxy(32,15);
        cout<<"LEVEL 5";
        break;
    case 1:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k19);
        gotoxy(32,15);
        cout<<"LEVEL 5";
        break;
    }
    switch(completedlevel5)
    {
    case 0:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k20);
        gotoxy(32,17);
        cout<<"LEVEL 6";
        break;
    case 1:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k19);
        gotoxy(32,17);
        cout<<"LEVEL 6";
        break;
    }
    switch(completedlevel6)
    {
    case 0:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k20);
        gotoxy(32,19);
        cout<<"LEVEL 7";
        break;
    case 1:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k19);
        gotoxy(32,19);
        cout<<"LEVEL 7";
        break;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k21);
    gotoxy(29,21);
    cout<<" BACK TO MENU";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k21);
    gotoxy(43,3);
    cout<<"COMPLETED LEVELS: "<<completedlevels;
}
//funkcja uruchamiana podczas proby wlaczenia zablokowanego poziomu
void completepreviouslevels()
{
    for (int i=0; i<=4; i++)
    {
        if(i==0||i==2||i==4)
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k22);
        else
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k23);
        Sleep(150);
        gotoxy(48,10);
        cout<<"You must first";
        gotoxy(48,11);
        cout<<"complete the";
        gotoxy(48,12);
        cout<<"the previous levels.";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k24);
}
//funkcja odpowiedzialna za dzialanie menu wyboru poziomow
void menu2()
{
    wybor2=0;
    newgame=false;
    backtomainmenu=false;

    while((newgame==false)&&(backtomainmenu==false))
    {
        menu2info();
        //ustawienie poczatkowej pozycji kursora na podstawie ilosci ukonczonych poziomow
        if(completedlevels==0)
            wybor2=0;

        if(completedlevels==1)
            wybor2=2;

        if(completedlevels==2)
            wybor2=4;

        if(completedlevels==3)
            wybor2=6;

        if(completedlevels==4)
            wybor2=8;

        if(completedlevels==5)
            wybor2=10;

        if(completedlevels==6)
            wybor2=12;

        if(completedlevels==7)
            wybor2=12;

        while (c!=char(13)) //dopoki nie zostanie wcisniety enter
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k24);
            gotoxy(26,7+wybor2); //wybor2 okresla takze pozycje kursora
            cout<<"< ";
            gotoxy(43,7+wybor2);
            cout<<"  >";
            gotoxy(0,0);
            c=_getch(); //pobieranie wcisnietego klawisza klawiatury
            gotoxy(26,7+wybor2);
            cout<<"   ";
            gotoxy(43,7+wybor2);
            cout<<"   ";

            if ((c=='s'||c=='S')&&(wybor2<16))
                wybor2+=2;
                if (wybor2==16)
                    wybor2=0;

            if ((c=='w'||c=='W')&&(wybor2>-2))
                wybor2-=2;
                if (wybor2==-2)
                    wybor2=14;
        }
        if(completedlevels==7)
        {
            if ((wybor2==0)||wybor2==2||wybor2==4||wybor2==6||wybor2==8||wybor2==10||wybor2==12)
                newgame=true;
            else if (wybor2==14)
                backtomainmenu=true;
            else
                completepreviouslevels();
        }
        if(completedlevels==6)
        {
            if ((wybor2==0)||wybor2==2||wybor2==4||wybor2==6||wybor2==8||wybor2==10||wybor2==12)
                newgame=true;
            else if (wybor2==14)
                backtomainmenu=true;
            else
                completepreviouslevels();
        }
        if(completedlevels==5)
        {
            if ((wybor2==0)||wybor2==2||wybor2==4||wybor2==6||wybor2==8||wybor2==10)
                newgame=true;
            else if (wybor2==14)
                backtomainmenu=true;
            else
                completepreviouslevels();
        }
        if(completedlevels==4)
        {
            if ((wybor2==0)||wybor2==2||wybor2==4||wybor2==6||wybor2==8)
                newgame=true;
            else if (wybor2==14)
                backtomainmenu=true;
            else
                completepreviouslevels();
        }
        if(completedlevels==3)
        {
            if ((wybor2==0)||wybor2==2||wybor2==4||wybor2==6)
                newgame=true;
            else if (wybor2==14)
                backtomainmenu=true;
            else
                completepreviouslevels();
        }
        if(completedlevels==2)
        {
            if ((wybor2==0)||wybor2==2||wybor2==4)
                newgame=true;
            else if (wybor2==14)
                backtomainmenu=true;
            else
                completepreviouslevels();
        }
        if(completedlevels==1)
        {
            if ((wybor2==0)||wybor2==2)
                newgame=true;
            else if (wybor2==14)
                backtomainmenu=true;
            else
                completepreviouslevels();
        }
        if(completedlevels==0)
        {
            if ((wybor2==0))
                newgame=true;
            else if (wybor2==14)
                backtomainmenu=true;
            else
                completepreviouslevels();
        }
        c='0';
        if(newgame==true||backtomainmenu==true)
            system("cls");
            //animation1();
            //animation2();
    }
}
//funkcja odpowiedzialna za dzialanie oraz wyswietlanie menu glownego
void menu()
{
    int wybor=0; //zmiena wybor okresla polozenia kursora wyboru oraz na jej podstawie uramiane sa poszczegolne opcje menu
    newgame=false;
    backtomainmenu=false;

    while((newgame==false)&&(wyjscie==false))
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k18);
        gotoxy(34,7);
        cout<<"[W]";
        gotoxy(34,19);
        cout<<"[S]";

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k21);
        gotoxy(32,11);
        cout<<"NEW GAME";
        gotoxy(30,13);
        cout<<"RESET LEVELS";
        gotoxy(32,15);
        cout<<"  QUIT";

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k21);
        gotoxy(43,3);
        cout<<"COMPLETED LEVELS: "<<completedlevels; //wyswietlanie ilosci ukonczonych poziomow

        if(completedlevels>0)
            {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k21);
            gotoxy(32,11);
            cout<<"CONTINUE";
            }

        while (c!=char(13))
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),k24);
            gotoxy(26,11+wybor);
            cout<<"< ";
            gotoxy(43,11+wybor);
            cout<<"  >";
            gotoxy(0,0);
            c=_getch();
            gotoxy(26,11+wybor);
            cout<<"   ";
            gotoxy(43,11+wybor);
            cout<<"   ";

            if ((c=='s'||c=='S')&&(wybor<6))
                wybor+=2;
                if (wybor==6)
                    wybor=0;

            if ((c=='w'||c=='W')&&(wybor>-2))
                wybor-=2;
                if (wybor==-2)
                    wybor=4;
        }
        if (wybor==0)
            newgame=true;
        if (wybor==2) //resetowanie postepow gracza
        {
            completedlevels=0;
            ofstream plik;
            plik.open("gamesaves.txt");
            plik<<completedlevels<<endl;
            plik.close();
            system("CLS");
        }
        if (wybor==4) //wyjscie z programu
            wyjscie=true;
        c='0';
        if(wybor!=2)
            animation1();
    }

}
//funkcja odpowiedzialna za ustawienie rozmiarow okna
void setwindow(int width, int height)
{
    _COORD xy;
    xy.X=width;
    xy.Y=height;

    _SMALL_RECT rect; //deklaracja koordynatow wierzcholkow konsoli
    rect.Top=0;
    rect.Left=0;
    rect.Bottom=height-1;
    rect.Right=width-1;

    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), xy); //ustawienie rozmiaru bufora konsoli
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &rect); //ustawienie rozmiaru okna
}
//Funkcja odpowiedzialna za ukrycie kursora
void showconsolecursor(bool showFlag)
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); //pobranie infomracji o kursorze
    cursorInfo.bVisible = showFlag; //widocznosc kursora rowna jest zmiennej showFlag
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); //ustawienie widocznosci kursora
}

int main()
{
    setwindow(70,30); //ustawienie wielkosci okna
    showconsolecursor(false); //ukrycie kursora
    backtomainmenu=false;
    wyjscie=false;
    ifstream plik; //wczytanie postepow gracza z pliku
    plik.open("gamesaves.txt");
    plik>>completedlevels;
    plik.close();
    menu(); //wlaczenie menu
    while(wyjscie==false)
    {
        while(backtomainmenu==false)
        {
            menu2(); //wlaczenie menu wyboru poziomow
            switch(wybor2)
            {
            case 0:
                playlevel1();
                break;
            case 2:
                playlevel2();
                break;
            case 4:
                playlevel3();
                break;
            case 6:
                playlevel4();
                break;
            case 8:
                playlevel5();
                break;
            case 10:
                playlevel6();
                break;
            case 12:
                playlevel7();
                break;
            }
        }
        main();
    }
    return 0;
}
