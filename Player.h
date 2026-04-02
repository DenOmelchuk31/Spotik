#pragma once

#include "Track.h"
#include "Queue.h"

class Player
{
private:
    Track currentTrack;
    Queue playQueue;
    bool isPlaying;

public:
    Player();

    void setQueue(const Queue& queue);

    bool play();
    void pause();
    void stop();
    bool playNext();

    Track getCurrentTrack() const;
    Queue getQueue() const;

    bool getIsPlaying() const;
    bool hasCurrentTrack() const;
};