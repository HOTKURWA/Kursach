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

char buff[2];

int random[10];
int SHposX[3] = {100, 100, 100}, SHposY[3] = {10, 50, 80}, SHDirection[3] = {0, 0, 0};
int PlanetPosX[3], PlanetPosY[3];
int Spaship, Random[3];

unsigned tsh[3], tPaint;
HANDLE hSH[3], hPaint;

struct TSpaceSip
{
 int cx, cy, px, py, dx, dy;

};

TSpaceSip ships[3];

unsigned __stdcall SpaceShips(void *pArguments)
{
        while (1)
        {
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
                Sleep(50);
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

                Sleep(50);
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
        HANDLE hRand;
        PAINTSTRUCT ps;

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
        //         semafors[i] = CreateSemaphore(NULL, 0, 5, NULL); // Создание семафора. Начальное значение 0 , максимальное 1.
        // }

        hPaint = (HANDLE)_beginthreadex(NULL, 0, &Paint, NULL, 0, &tPaint);

        for (int i = 0; i, 3; i++)
        {
                hSH[i] = (HANDLE)_beginthreadex(NULL, 0, &SpaceShips, NULL, 0, &tsh[i]);
                Spaship = i;
        }

        // CloseHandle(hSH);

        while (GetMessage(&msg, NULL, 0, 0))
        {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
        }

        return (INT)msg.wParam;
}
