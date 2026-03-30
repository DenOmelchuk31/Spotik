#pragma once

#include <vector>
#include "Track.h"

class Queue {
private:
    std::vector<Track> queue;

public:
    Queue();

    std::vector<Track>& getQueue();
};