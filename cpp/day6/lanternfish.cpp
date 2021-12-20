#include "lanternfish.h"
#include <iostream>

LanternFish::LanternFish() : timer(8) {};

LanternFish::LanternFish(int timer) : timer(timer) {};

int LanternFish::getTimer()
{
    return timer;
}

int LanternFish::AdvanceStep()
{
    if (timer == 0) {
        timer = 6;
    } else {
        // std::cout << "decrementing timer: " << timer << '\n';
        timer--;
    }
    return timer;
}