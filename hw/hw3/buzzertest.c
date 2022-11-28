#include "buzzer.h"

int main(void)
{
    buzzerInit();
    buzzerPlaySong(2);
    usleep(200000);
    buzzerStopSong();
    usleep(200000);
    buzzerPlaySong(1);
    usleep(200000);
    buzzerStopSong();
    usleep(200000);
    buzzerPlaySong(0);
    usleep(200000);
    buzzerStopSong();
    usleep(200000);
    buzzerPlaySong(1);
    usleep(200000);
    buzzerStopSong();
    usleep(400000);

    buzzerPlaySong(2);
    usleep(200000);
    buzzerStopSong();
    usleep(200000);
    buzzerPlaySong(2);
    usleep(200000);
    buzzerStopSong();
    usleep(200000);
    buzzerPlaySong(2);
    usleep(200000);
    buzzerStopSong();
    usleep(400000);

    buzzerPlaySong(1);
    usleep(200000);
    buzzerStopSong();
    usleep(200000);
    buzzerPlaySong(1);
    usleep(200000);
    buzzerStopSong();
    usleep(200000);
    buzzerPlaySong(1);
    usleep(200000);
    buzzerStopSong();
    usleep(400000);
    return 0;
}