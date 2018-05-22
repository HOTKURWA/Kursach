//gcc My.cpp -o My.exe -mwindows
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

HANDLE semafors[5];
HWND hMain = NULL;
HDC hdc;

int random[10];
int SHposX[3] = {100, 100, 100}, SHposY[3] = {10, 50, 80}, SHDirection[3] = {0, 0, 0};
int PlanetPosX[3], PlanetPosY[3];
int Spaship, Random[3];

unsigned tsh[3], tEarth, tAltair, tKanopus, tNewTerra, tKapella;
HANDLE hSH[3], hEarth, hAltair, hKanopus, hNewTerra, hKapella;

unsigned __stdcall SpaceShip1(void *pArguments)
{
        Spaship = 0;
        switch (SHDirection[Spaship])
        {
        case 0:
        {
                SHDirection[Spaship] = Random[Spaship];
                break;
        }
        case 1:
        {
                PlanetPosX[Spaship] = 50;
                PlanetPosY[Spaship] = 150;
                break;
        }

        case 2:
        {
                PlanetPosX[Spaship] = 50;
                PlanetPosY[Spaship] = 500;
                break;
        }
        case 3:
        {
                PlanetPosX[Spaship] = 650;
                PlanetPosY[Spaship] = 150;
                break;
        }
        case 4:
        {
                PlanetPosX[Spaship] = 650;
                PlanetPosY[Spaship] = 500;
                break;
        }
        case 5:
        {
                PlanetPosX[Spaship] = 355;
                PlanetPosY[Spaship] = 300;
                break;
        }
        }

        if ((SHposX[Spaship] == PlanetPosX[Spaship]) && (SHposY[Spaship] == PlanetPosY[Spaship]))
        {
                srand(time(NULL));

                Sleep(30);
                SHDirection[Spaship] = rand() % 5 + 1;
        }
        else
        {
                if (SHposX[Spaship] > PlanetPosX[Spaship])
                        SHposX[Spaship]--;
                if (SHposX[Spaship] < PlanetPosX[Spaship])
                        SHposX[Spaship]++;

                if (SHposY[Spaship] > PlanetPosY[Spaship])
                        SHposY[Spaship]--;
                if (SHposY[Spaship] < PlanetPosY[Spaship])
                        SHposY[Spaship]++;
        }
        _endthreadex(1);
        return 1;
}

unsigned __stdcall SpaceShip2(void *pArguments)
{
        Spaship = 1;
        switch (SHDirection[Spaship])
        {

        case 0:
        {
                SHDirection[Spaship] = Random[Spaship];
                break;
        }
        case 1:
        {
                PlanetPosX[Spaship] = 50;
                PlanetPosY[Spaship] = 150;
                break;
        }

        case 2:
        {
                PlanetPosX[Spaship] = 50;
                PlanetPosY[Spaship] = 500;
                break;
        }
        case 3:
        {
                PlanetPosX[Spaship] = 650;
                PlanetPosY[Spaship] = 150;
                break;
        }
        case 4:
        {
                PlanetPosX[Spaship] = 650;
                PlanetPosY[Spaship] = 500;
                break;
        }
        case 5:
        {
                PlanetPosX[Spaship] = 355;
                PlanetPosY[Spaship] = 300;
                break;
        }
        }

        if ((SHposX[Spaship] == PlanetPosX[Spaship]) && (SHposY[Spaship] == PlanetPosY[Spaship]))
        {
                srand(time(NULL));
                Sleep(35);
                SHDirection[Spaship] = rand() % 5 + 1;
        }
        else
        {
                if (SHposX[Spaship] > PlanetPosX[Spaship])
                        SHposX[Spaship]--;
                if (SHposX[Spaship] < PlanetPosX[Spaship])
                        SHposX[Spaship]++;

                if (SHposY[Spaship] > PlanetPosY[Spaship])
                        SHposY[Spaship]--;
                if (SHposY[Spaship] < PlanetPosY[Spaship])
                        SHposY[Spaship]++;
        }
        _endthreadex(1);
        return 1;
}

unsigned __stdcall SpaceShip3(void *pArguments)
{
        Spaship = 2;
        switch (SHDirection[Spaship])
        {
        case 0:
        {
                SHDirection[Spaship] = Random[Spaship];
                break;
        }
        case 1:
        {
                PlanetPosX[Spaship] = 50;
                PlanetPosY[Spaship] = 150;
                break;
        }

        case 2:
        {
                PlanetPosX[Spaship] = 50;
                PlanetPosY[Spaship] = 500;
                break;
        }
        case 3:
        {
                PlanetPosX[Spaship] = 650;
                PlanetPosY[Spaship] = 150;
                break;
        }
        case 4:
        {
                PlanetPosX[Spaship] = 650;
                PlanetPosY[Spaship] = 500;
                break;
        }
        case 5:
        {
                PlanetPosX[Spaship] = 355;
                PlanetPosY[Spaship] = 300;
                break;
        }
        }

        if ((SHposX[Spaship] == PlanetPosX[Spaship]) && (SHposY[Spaship] == PlanetPosY[Spaship]))
        {
                switch (SHDirection[Spaship])
                {
                        // case 1: hEarth = (HANDLE)_beginthreadex(NULL, 0, &Earth, NULL, 0, &tEarth);
                        // case 2: hAltair = (HANDLE)_beginthreadex(NULL, 0, &Altair, NULL, 0, &tAltair);
                        // case 3: hKanopus = (HANDLE)_beginthreadex(NULL, 0, &Kanopus, NULL, 0, &tKanopus);
                        // case 4: hNewTerra = (HANDLE)_beginthreadex(NULL, 0, &NewTerra, NULL, 0, &tNewTerra);
                        // case 5: hKapella = (HANDLE)_beginthreadex(NULL, 0, &Kapella, NULL, 0, &tKapella);
                }
                srand(time(NULL));
                Sleep(25);
                SHDirection[Spaship] = rand() % 5 + 1;
        }
        else
        {
                if (SHposX[Spaship] > PlanetPosX[Spaship])
                        SHposX[Spaship]--;
                if (SHposX[Spaship] < PlanetPosX[Spaship])
                        SHposX[Spaship]++;

                if (SHposY[Spaship] > PlanetPosY[Spaship])
                        SHposY[Spaship]--;
                if (SHposY[Spaship] < PlanetPosY[Spaship])
                        SHposY[Spaship]++;
        }
        _endthreadex(1);
        return 1;
}

unsigned __stdcall Earth(void *pArguments)
{

        _endthreadex(1);
        return 1;
}
unsigned __stdcall Altair(void *pArguments)
{

        _endthreadex(1);
        return 1;
}
unsigned __stdcall Kanopus(void *pArguments)
{

        _endthreadex(1);
        return 1;
}
unsigned __stdcall NewTerra(void *pArguments)
{

        _endthreadex(1);
        return 1;
}
unsigned __stdcall Kapella(void *pArguments)
{

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
        HANDLE hRand;
        PAINTSTRUCT ps;
        char buff[2];
        unsigned long SH1ID;
        srand(time(NULL));

        memset(&wc, 0, sizeof(wc));
        wc.lpszClassName = "MyWndClass"; //Название класса окна
        wc.hInstance = hInst;
        wc.lpfnWndProc = WndProc;
        RegisterClass(&wc);                                                                                        //Регистрируем класс окна
        hMain = CreateWindow(wc.lpszClassName, "SpaceX", WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, 0, 0, hInst, 0); //Создать окно
        ShowWindow(hMain, SW_SHOW);                                                                                //Показать окно
        hdc = BeginPaint(hMain, &ps);                                                                              // начало перерисовки

        for (int time = 0; time < 10; time++) //random
        {
                if (time < 3)
                        Random[time] = rand() % 5 + 1;
                if (time < 5)
                {
                        random[time] = rand() % 16 + 3;
                }
                else
                {
                        if (time < 10)
                                random[time] = rand() % 4 + 1;
                }
        }

        // for (int i = 0; i < 5; i++)
        // {
        //         semafors[i] = CreateSemaphore(NULL, 0, 1, NULL); // Создание семафора. Начальное значение 0 , максимальное 1.
        // }
        do
        {
                Rectangle(hdc, 20, 40, 120, 140); //Earth
                TextOut(hdc, 50, 80, "Earth", 6);
                sprintf(buff, "%d", random[1]);
                TextOut(hdc, 50, 95, buff, 2);

                Rectangle(hdc, 20, 390, 120, 490); //Altair
                TextOut(hdc, 50, 430, "Altair", 6);
                sprintf(buff, "%d", random[2]);
                TextOut(hdc, 50, 445, buff, 2);

                Rectangle(hdc, 630, 40, 730, 140); //Kanopus
                TextOut(hdc, 650, 80, "Kanopus", 7);
                sprintf(buff, "%d", random[3]);
                TextOut(hdc, 650, 95, buff, 2);

                Rectangle(hdc, 630, 390, 730, 490); //NewTerra
                TextOut(hdc, 650, 430, "NewTerra", 8);
                sprintf(buff, "%d", random[4]);
                TextOut(hdc, 650, 445, buff, 2);

                Rectangle(hdc, 330, 190, 430, 290); //Kapella
                TextOut(hdc, 355, 230, "Kapella", 7);
                sprintf(buff, "%d", random[4]);
                TextOut(hdc, 355, 245, buff, 2);

                TextOut(hdc, SHposX[0], SHposY[0], " SH1 ", 5);
                sprintf(buff, " %d %d ", SHposX[0], SHposY[0]);
                TextOut(hdc, SHposX[0], SHposY[0] + 15, buff, 9);

                TextOut(hdc, SHposX[1], SHposY[1], " SH2 ", 5);
                sprintf(buff, " %d %d ", SHposX[1], SHposY[1]);
                TextOut(hdc, SHposX[1], SHposY[1] + 15, buff, 9);

                TextOut(hdc, SHposX[2], SHposY[2], " SH3 ", 5);
                sprintf(buff, " %d %d ", SHposX[2], SHposY[2]);
                TextOut(hdc, SHposX[2], SHposY[2] + 15, buff, 9);

                hSH[0] = (HANDLE)_beginthreadex(NULL, 0, &SpaceShip1, NULL, 0, &tsh[1]);
                hSH[1] = (HANDLE)_beginthreadex(NULL, 0, &SpaceShip2, NULL, 0, &tsh[2]);
                hSH[2] = (HANDLE)_beginthreadex(NULL, 0, &SpaceShip3, NULL, 0, &tsh[3]);

                // hAltair = (HANDLE)_beginthreadex(NULL, 0, &Altair, NULL, 0, &tAltair);
                // hKanopus = (HANDLE)_beginthreadex(NULL, 0, &Kanopus, NULL, 0, &tKanopus);
                // hNewTerra = (HANDLE)_beginthreadex(NULL, 0, &NewTerra, NULL, 0, &tNewTerra);
                // hKapella = (HANDLE)_beginthreadex(NULL, 0, &Kapella, NULL, 0, &tKapella);
                Sleep(10);
                UpdateWindow(hMain); //Обновить окно

                CloseHandle(hSH);

        } while (1);
        return 0l;

        // while (GetMessage(&msg, NULL, 0, 0))
        // {
        //         TranslateMessage(&msg);
        //         DispatchMessage(&msg);
        // }

        //return (INT)msg.wParam;
}
