// Turingas.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <thread>
#include <mutex> 
using namespace std;

struct Taisykles
{
    char elementas1, elementas2, judesys;
    int busenaPirma;
    string busenaPaskutine;
};

mutex mute;

void Programa()
{
    bool Programa = true;
    while (Programa)
    {
        vector <Taisykles> T; // leis mums irasyti visus duomenys pagal Turingo taisykles
        string Juosta, x;
        int Galva, p = -1;
        mute.lock();
        cout << "Pasirinkite faila: " << endl;
        cin >> x;
        mute.unlock();
        ifstream fd(x + ".txt");
        mute.lock();
        mute.unlock();
        fd >> Juosta;
        fd >> Galva;
        while (!fd.eof())
        {
            p++;
            T.push_back(Taisykles());
            fd >> T[p].busenaPirma >> T[p].elementas1 >> T[p].elementas2 >> T[p].judesys >> T[p].busenaPaskutine;

        }
        /*cout << Juosta << endl;
        cout << Galva << endl;
        for (int i = 0; i < p; i++)
        {
            cout << T[i].busenaPirma << T[i].elementas1 << T[i].elementas2 << T[i].judesys << T[i].busenaPaskutine << endl;
        }
        cout << p << endl;*/
        fd.close();
        bool veikimas = true;
        int dabartineBusena = 0, i = 0, y = 0;
        int limitas = Juosta.size();
        int eiluciusk = -1;
        while (veikimas == true)
        {
            if (GetAsyncKeyState(VK_SPACE))
            {
                veikimas = false;
            }
            /*cout << "veikia 0 " << i << " <-i ";
            cout << T[i].busenaPirma << T[i].elementas1 << T[i].elementas2 << T[i].judesys << T[i].busenaPaskutine << endl;*/
            if (dabartineBusena == T[i].busenaPirma)
            {
                /*cout << "veikia 1 ";*/
                if (Juosta[Galva] == T[i].elementas1)
                {
                    /* cout << "veikia 2 ";*/
                    Juosta[Galva] = T[i].elementas2;
                    cout << Juosta << endl;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 2 });
                    if (T[i].judesys == 'L')
                    {
                        Galva--;
                    }
                    if (T[i].judesys == 'R')
                    {
                        Galva++;
                    }
                    // netinka!
                    if (T[i].busenaPaskutine[0] == 'X')
                    {
                        veikimas = false;
                    }
                    /*if (eiluciusk == p)
                    {
                        veikimas = false;
                    }*/
                    else
                    {
                        dabartineBusena = stoi(T[i].busenaPaskutine);
                        y++;
                    }
                }
            }
            if (y == 1)
            {
                y--;
                i = 0;
            }
            else if (Galva == 0 or Galva == limitas)
            {
                veikimas = false;
            }
            else
            {
                i++;
            }
        }
        int ats;
        mute.lock();
        cout << "Ar pratesti darba? " << endl;
        cout << " 1. Ne " << endl;
        cout << " 2. Taip " << endl;
        cin >> ats;
        mute.unlock();
        mute.lock();
        mute.unlock();
        if (ats == 1)
        {
            Programa = false;
        }
        else if (ats != 1 && ats != 2)
        {
            Programa = false;
        }
    }
}

int main()
{ 
    thread first(Programa);
    thread second(Programa);
    first.join();
    second.join();
    /*Programa();*/
}
