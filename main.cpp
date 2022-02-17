#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include<fstream>
#include "Meniuri.h"
#include "Joaca.h"
using namespace std;
int main()
{
    initwindow(800,800);
    Menu();
    getch();
    closegraph();
    return 0;
}
