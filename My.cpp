//g++ My.cpp -o My.exe -mwindows
//SetTextColor(hdc, RGB(0, 0, 0));

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
int SHposX[3] = {100}, SHposY[3] = {10}, SHDirection[3] = {0};
int PlanetPosX, PlanetPosY;

unsigned __stdcall SpaceShip1(void *pArguments)
{
        switch (SHDirection[1])
        {
        case 0:
        {
                SHDirection[1] = rand() % 5 + 1;
                break;
        }
        case 1:
        {
                PlanetPosX = 50;
                PlanetPosY = 120;
                break;
        }

        case 2:
        {
                PlanetPosX = 50;
                PlanetPosY = 500;
                break;
        }
        case 3:
        {
                PlanetPosX = 650;
                PlanetPosY = 150;
                break;
        }
        case 4:
        {
                PlanetPosX = 650;
                PlanetPosY = 500;
                break;
        }
        case 5:
        {
                PlanetPosX = 355;
                PlanetPosY = 300;
                break;
        }
        }

        if ((SHposX[1] == PlanetPosX) && (SHposY[1] == PlanetPosY))
        {
                ReleaseSemaphore(semafors[1], 1, NULL);
        }
        else
        {
                if (SHposX[1] > PlanetPosX)
                        SHposX[1]--;
                if (SHposX[1] < PlanetPosX)
                        SHposX[1]++;

                if (SHposY[1] > PlanetPosY)
                        SHposY[1]--;
                if (SHposY[1] < PlanetPosY)
                        SHposY[1]++;
        }
        _endthreadex(1);
        return 1;
}

unsigned __stdcall Earth(void *pArguments)
{
        WaitForSingleObject(semafors[1], INFINITE);
        if (random[1] > 3)
        {
                random[1] = -3;
                SHDirection[1] = random[5];
        }
        else
        {
                random[1] = 0;
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
        char buff[2];
        unsigned long SH1ID;
        unsigned tsh[3], tEarth, tAltair, tKanopus, tNewTerra, tKapella;
        HANDLE hSH[3], hEarth, hAltair, hKanopus, hNewTerra, hKapella;

        memset(&wc, 0, sizeof(wc));
        wc.lpszClassName = "MyWndClass"; //Название класса окна
        wc.hInstance = hInst;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW); //Курсор в окне
        wc.lpfnWndProc = WndProc;
        RegisterClass(&wc);                                                                                        //Регистрируем класс окна
        hMain = CreateWindow(wc.lpszClassName, "SpaceX", WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, 0, 0, hInst, 0); //Создать окно
        ShowWindow(hMain, SW_SHOW);                                                                                //Показать окно
        hdc = BeginPaint(hMain, &ps);                                                                              // начало перерисовки

        for (int time = 0; time < 10; time++) //random
        {
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

        for (int i = 0; i < 5; i++)
        {
                semafors[i] = CreateSemaphore(NULL, 1, 1, NULL); // Создание семафора. Начальное значение 1 (все могут ехать), максимальное тоже 1.

                if (semafors[i] == NULL)
                {
                        printf("Не могу создать семафор");
                        return 5;
                }
        }

        do
        {
                Rectangle(hdc, 20, 40, 120, 140); //Earth
                TextOut(hdc, 50, 80, "Earth", 6);
                sprintf(buff, "%d", random[1]);
                TextOut(hdc, 50, 95, buff, 3);

                Rectangle(hdc, 20, 390, 120, 490); //Altair
                TextOut(hdc, 50, 430, "Altair", 6);
                sprintf(buff, "%d", random[2]);
                TextOut(hdc, 50, 445, buff, 3);

                Rectangle(hdc, 630, 40, 730, 140); //Kanopus
                TextOut(hdc, 650, 80, "Kanopus", 7);
                sprintf(buff, "%d", random[3]);
                TextOut(hdc, 650, 95, buff, 3);

                Rectangle(hdc, 630, 390, 730, 490); //NewTerra
                TextOut(hdc, 650, 430, "NewTerra", 8);
                sprintf(buff, "%d", random[4]);
                TextOut(hdc, 650, 445, buff, 3);

                Rectangle(hdc, 330, 190, 430, 290); //Kapella
                TextOut(hdc, 355, 230, "Kapella", 7);
                sprintf(buff, "%d", random[4]);
                TextOut(hdc, 355, 245, buff, 3);

                TextOut(hdc, SHposX[1], SHposY[1], " SH1 ", 5);
                sprintf(buff, "%d %d", SHposX[1], SHposY[1]);
                TextOut(hdc, SHposX[1], SHposY[1] + 15, buff, 7);

                // TextOut(hdc, 800 - posision, 600 - posision, " SH2 ", 5);
                // TextOut(hdc, 800 - posision, 600 - posision + 15, " Pos ", 5);

                // TextOut(hdc, posision, 600 - posision, " SH3 ", 5);
                // TextOut(hdc, posision, 600 - posision + 15, " Pos ", 5);

                hSH[1] = (HANDLE)_beginthreadex(NULL, 0, &SpaceShip1, NULL, 0, &tsh[1]);

                // hSH[2] = (HANDLE)_beginthreadex(NULL, 0, &SpaceShip1, NULL, 0, &tsh[2]);
                // hSH[3] = (HANDLE)_beginthreadex(NULL, 0, &SpaceShip1, NULL, 0, &tsh[3]);

                hEarth = (HANDLE)_beginthreadex(NULL, 0, &Earth, NULL, 0, &tEarth);

                // hAltair = (HANDLE)_beginthreadex(NULL, 0, &Altair, NULL, 0, &tAltair);
                // hKanopus = (HANDLE)_beginthreadex(NULL, 0, &Kanopus, NULL, 0, &tKanopus);
                // hNewTerra = (HANDLE)_beginthreadex(NULL, 0, &NewTerra, NULL, 0, &tNewTerra);
                // hKapella = (HANDLE)_beginthreadex(NULL, 0, &Kapella, NULL, 0, &tKapella);

                UpdateWindow(hMain); //Обновить окно

                CloseHandle(hSH[1]);
                Sleep(20);

        } while (1);
        // return 0l;

        while (GetMessage(&msg, NULL, 0, 0))
        {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
        }

        return (INT)msg.wParam;
}
