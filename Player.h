#pragma once

#include "Track.h"
#include "Queue.h"

class Player {
private:
    Track currentTrack;
    Queue playQueue;
    int currentIndex;
    bool isPlaying;

public:
    Player();
};