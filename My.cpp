﻿//gcc My.cpp -o My.exe -mwindows
//cd C:\Andrew\ОмГТУ\2 курс\OC\Курсач\Kursach
//SetTextColor(hdc, RGB(0, 0, 0));

//WaitForSingleObject(semafors[SHDirection[Spaship]], INFINITE);
//ReleaseSemaphore(semafors[SHDirection[Spaship]], 1, NULL);

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <math.h>
#include <locale.h>
#include <time.h>
#include <ctype.h>

HANDLE semShip[3];
HANDLE semPlanet[5];
HWND hMain = NULL;
HDC hdc;

char buff[2];

int randNP[5];
int NumPass = 0, PassSum = 5;
int PassPos[100], PassDir[100], pPas;

int SHposX[3] = {100, 100, 100}, SHposY[3] = {10, 50, 80}, SHDirection[3] = {1, 2, 3};
int Spaship;

int PlanetPosX[3], PlanetPosY[3];

unsigned __stdcall Passengers(void *pArguments)
{
        int nPas = NumPass;

        while (1)
        {                
                WaitForSingleObject(semPlanet[PassPos[nPas]], INFINITE);
                randNP[PassPos[nPas]]--;
        }
        _endthreadex(1);
        return 1;
}

unsigned __stdcall SpaceShips(void *pArguments)
{
        int nSh = Spaship;

        while (1)
        {

                switch (SHDirection[nSh])
                {
                case 0:
                {

                        PlanetPosX[nSh] = 50;
                        PlanetPosY[nSh] = 150;
                        break;
                }

                case 1:
                {

                        PlanetPosX[nSh] = 50;
                        PlanetPosY[nSh] = 500;
                        break;
                }
                case 2:
                {

                        PlanetPosX[nSh] = 650;
                        PlanetPosY[nSh] = 150;
                        break;
                }
                case 3:
                {

                        PlanetPosX[nSh] = 650;
                        PlanetPosY[nSh] = 500;
                        break;
                }
                case 4:
                {

                        PlanetPosX[nSh] = 355;
                        PlanetPosY[nSh] = 300;
                        break;
                }
                }

                if ((SHposX[nSh] == PlanetPosX[nSh]) && (SHposY[nSh] == PlanetPosY[nSh]))
                {
                        srand(time(NULL));
                        Sleep(1);

                        ReleaseSemaphore(semPlanet[SHDirection[nSh]], 1, NULL);
                        SHDirection[nSh] = rand() % 5 + 1;
                }
                else
                {
                        if (SHposX[nSh] > PlanetPosX[nSh])
                                SHposX[nSh]--;
                        if (SHposX[nSh] < PlanetPosX[nSh])
                                SHposX[nSh]++;

                        if (SHposY[nSh] > PlanetPosY[nSh])
                                SHposY[nSh]--;
                        if (SHposY[nSh] < PlanetPosY[nSh])
                                SHposY[nSh]++;
                }
                Sleep(20);
        }
        _endthreadex(1);
        return 1;
}

unsigned __stdcall Paint(void *pArguments)
{
        while (1)
        {
                for (int i = 0; i < 3; i++)
                {
                        sprintf(buff, " %d ", i);
                        TextOut(hdc, SHposX[i], SHposY[i] + 5, "    ", 5);
                        TextOut(hdc, SHposX[i], SHposY[i] - 5, "    ", 5);
                        TextOut(hdc, SHposX[i], SHposY[i], buff, 3);
                }


                Rectangle(hdc, 20, 40, 120, 140); //Earth
                TextOut(hdc, 50, 80, "Earth", 6);
                sprintf(buff, "%d", randNP[0]);
                TextOut(hdc, 50, 95, buff, 3);

                Rectangle(hdc, 20, 390, 120, 490); //Altair
                TextOut(hdc, 50, 430, "Altair", 6);
                sprintf(buff, "%d", randNP[1]);
                TextOut(hdc, 50, 445, buff, 3);

                Rectangle(hdc, 630, 40, 730, 140); //Kanopus
                TextOut(hdc, 650, 80, "Kanopus", 7);
                sprintf(buff, "%d", randNP[2]);
                TextOut(hdc, 650, 95, buff, 3);

                Rectangle(hdc, 630, 390, 730, 490); //NewTerra
                TextOut(hdc, 650, 430, "NewTerra", 8);
                sprintf(buff, "%d", randNP[3]);
                TextOut(hdc, 650, 445, buff, 3);

                Rectangle(hdc, 330, 190, 430, 290); //Kapella
                TextOut(hdc, 355, 230, "Kapella", 7);
                sprintf(buff, "%d", randNP[4]);
                TextOut(hdc, 355, 245, buff, 3);

                Sleep(20);
                UpdateWindow(hMain);
        }
        _endthreadex(1);
        return 1;
}

//Стандартная функция обработки сообщений окном
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
        UINT nCmd = HIWORD(wParam);
        UINT idCtrl = LOWORD(wParam);
        HWND hChild = (HWND)lParam;
        switch (msg)
        {
        case WM_DESTROY:
                PostQuitMessage(0); //Закрываем приложение
                break;
        default:
                return DefWindowProc(hWnd, msg, wParam, lParam); //возвращаем дефолтные значения
        }
        return 0l;
}
//Главная функция приложения
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{

        MSG msg;
        WNDCLASS wc;
        PAINTSTRUCT ps;

        unsigned tsh[3], tPaint, tPas[100];
        HANDLE hSH[3], hPaint, hPas[100];

        srand(time(NULL));

        memset(&wc, 0, sizeof(wc));
        wc.lpszClassName = "MyWndClass"; //Название класса окна
        wc.hInstance = hInst;
        wc.lpfnWndProc = WndProc;
        RegisterClass(&wc);                                                                                        //Регистрируем класс окна
        hMain = CreateWindow(wc.lpszClassName, "SpaceX", WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, 0, 0, hInst, 0); //Создать окно
        ShowWindow(hMain, SW_SHOW);                                                                                //Показать окно
        hdc = BeginPaint(hMain, &ps);                                                                              // начало перерисовки

        for (int i = 0; i < 3; i++)
        {
                semShip[i] = CreateSemaphore(NULL, 0, 3, NULL);
        }

        for (int i = 0; i < 5; i++)
        {
                semPlanet[i] = CreateSemaphore(NULL, 0, 1, NULL);
        }

        hPaint = (HANDLE)_beginthreadex(NULL, 0, &Paint, NULL, 0, &tPaint);

        for (int i = 0; i < 5; i++) //random
        {
                randNP[i] = rand() % 10 + 10;
                PassSum = +randNP[i];
        }

        for (int i = 0; i < 5; i++)
        {
                for (int n = 0; n < randNP[i]; n++)
                {
                        PassPos[NumPass] = i;
                        hPas[NumPass] = (HANDLE)_beginthreadex(NULL, 0, &Passengers, NULL, 0, &tPas[NumPass]);
                        Sleep(5);
                        NumPass++;
                }
        }

        for (int i = 0; i < 3; i++)
        {
                hSH[i] = (HANDLE)_beginthreadex(NULL, 0, &SpaceShips, NULL, 0, &tsh[i]);
                Spaship = i;
                Sleep(10);
        }

        while (GetMessage(&msg, NULL, 0, 0))
        {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
        }

        CloseHandle(hSH);
        CloseHandle(hPas);
        return (INT)msg.wParam;
}
