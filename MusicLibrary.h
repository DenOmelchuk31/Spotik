#pragma once

#include <vector>
#include "Track.h"
#include "Playlist.h"

class MusicLibrary {
private:
    std::vector<Track> allTracks;
    std::vector<Playlist> playlists;
    std::vector<Track> favorites;

public:
    MusicLibrary();

    std::vector<Track>& getTracks();
    std::vector<Playlist>& getPlaylists();
    std::vector<Track>& getFavorites();
};