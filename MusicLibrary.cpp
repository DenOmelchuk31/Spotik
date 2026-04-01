#include "MusicLibrary.h"

Library::Library() {}

QVector<Track> Library::getTracks() const
{
    return tracks;
}

QVector<Playlist> Library::getPlaylists() const
{
    return playlists;
}

void Library::addTrack(const Track& track)
{
    tracks.push_back(track);
}

bool Library::removeTrackByTitle(const QString& title)
{
    int index = findTrackByTitle(title);

    if (index == -1) {
        return false;
    }

    tracks.removeAt(index);
    return true;
}

int Library::findTrackByTitle(const QString& title) const
{
    for (int i = 0; i < tracks.size(); i++) {
        if (tracks[i].getTitle().compare(title, Qt::CaseInsensitive) == 0) {
            return i;
        }
    }

    return -1;
}

bool Library::hasTrack(const QString& title) const
{
    return findTrackByTitle(title) != -1;
}

void Library::addPlaylist(const Playlist& playlist)
{
    playlists.push_back(playlist);
}

bool Library::removePlaylistByName(const QString& name)
{
    int index = findPlaylistByName(name);

    if (index == -1) {
        return false;
    }

    playlists.removeAt(index);
    return true;
}

int Library::findPlaylistByName(const QString& name) const
{
    for (int i = 0; i < playlists.size(); i++) {
        if (playlists[i].getName().compare(name, Qt::CaseInsensitive) == 0) {
            return i;
        }
    }

    return -1;
}

bool Library::hasPlaylist(const QString& name) const
{
    return findPlaylistByName(name) != -1;
}

bool Library::isTracksEmpty() const
{
    return tracks.isEmpty();
}

bool Library::isPlaylistsEmpty() const
{
    return playlists.isEmpty();
}

bool Library::isEmpty() const
{
    return tracks.isEmpty() && playlists.isEmpty();
}

int Library::getTrackCount() const
{
    return tracks.size();
}

int Library::getPlaylistCount() const
{
    return playlists.size();
}

void Library::clearTracks()
{
    tracks.clear();
}

void Library::clearPlaylists()
{
    playlists.clear();
}

void Library::clearAll()
{
    tracks.clear();
    playlists.clear();
}