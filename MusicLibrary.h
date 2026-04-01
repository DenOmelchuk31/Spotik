#ifndef LIBRARY_H
#define LIBRARY_H

#include <QString>
#include <QVector>
#include "Track.h"
#include "Playlist.h"

class Library
{
private:
    QVector<Track> tracks;
    QVector<Playlist> playlists;

public:
    Library();

    QVector<Track> getTracks() const;
    QVector<Playlist> getPlaylists() const;

    void addTrack(const Track& track);
    bool removeTrackByTitle(const QString& title);
    int findTrackByTitle(const QString& title) const;
    bool hasTrack(const QString& title) const;

    void addPlaylist(const Playlist& playlist);
    bool removePlaylistByName(const QString& name);
    int findPlaylistByName(const QString& name) const;
    bool hasPlaylist(const QString& name) const;

    bool isTracksEmpty() const;
    bool isPlaylistsEmpty() const;
    bool isEmpty() const;

    int getTrackCount() const;
    int getPlaylistCount() const;

    void clearTracks();
    void clearPlaylists();
    void clearAll();
};
#endif // LIBRARY_H