#include <iostream>
#include <windows.h>
#include <mmsystem.h>

int main()
{
    PlaySound(TEXT("recycle.wav"), NULL, SND_FILENAME);
}