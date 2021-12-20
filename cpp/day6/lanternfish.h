#ifndef LANTERNFISH_H
#define LANTERNFISH_H

class LanternFish {
public:
    
    LanternFish();

    LanternFish(int timer);

    // Advances the simulation 1 step and returns the new timer value
    int AdvanceStep();

    int getTimer();

private:
    // spawn wit a timer of 8
    int timer;
};

#endif  /* LANTERNFISH_H */