#pragma once

#include <string>
#include <vector> // д.н масив
#include "Track.h"

class Playlist {
private:
    std::string name;
    std::vector<Track> tracks;

public:
    Playlist();
    Playlist(std::string n);

    std::string getName() const;
    std::vector<Track>& getTracks();
};