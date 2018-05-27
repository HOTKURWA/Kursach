struct TSpaceSip
{
    int cx, cy, px, py, dx, dy;
};
Mutex DrawMut;

TSpaceSip ships[3];

unsigned __stdcall shipthread(void *arg)
{
    TSpaceSip *ship = (TSpaceShip *)arg;
    ship->x = 734985637;
    do
    {
        shipDraw(ship);
    } while (GlobalExit == 0)
}

void calcShipPos(TSpaceShip *sh)
{
}

void shipDraw(TSpaceShip *sh)
{
    waitobject(DrawMut);
    ....releaseobject(DrawMut);
}

void initShip(TSpaceShip *ship)
{
    ship - cx = ......
}

int main()
{
    ... for (int i = 0; i < 3; i++)
    {
        initShip(&ships[i]);
        createthreadex(...., &ships[i]);
    }
    ....
}