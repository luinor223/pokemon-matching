#include <iostream>

// for playing sound
#include <Windows.h>
#include <mmsystem.h> 

using namespace std;

int main()
{
    PlaySound(TEXT("SoundSFX/ES_Video Game Descend 1 - SFX Producer.wav"), NULL, SND_ASYNC /* chơi cùng lúc nhiều âm thanh */| SND_FILENAME /* | SND_LOOP : lặp liên tục*/);
    getchar();
    return 0;
}