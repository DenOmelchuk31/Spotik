#ifndef LIBRARY_H
#define LIBRARY_H

#include <QString>
#include <QVector>
#include "Track.h"

class Library
{
private:
    QVector<Track> tracks;

public:
    Library() = default;

    const QVector<Track>& getTracks() const { return tracks; }

    void addTrack(const Track& track);
    bool removeTrackByTitle(const QString& title);
    int  findTrackByTitle(const QString& title) const;
    bool hasTrack(const QString& title) const;

    bool isEmpty()       const { return tracks.isEmpty(); }
    int  getTrackCount() const { return tracks.size();    }

    void clearTracks() { tracks.clear(); }
};

#endif // LIBRARY_H
