#pragma once

#include <QString>
#include <QVector>
#include "Track.h"

class Playlist
{
private:
    QString name;
    QVector<Track> tracks;

public:
    Playlist();
    Playlist(const QString& name);

    QString getName() const;
    QVector<Track> getTracks() const;

    void setName(const QString& name);

    void addTrack(const Track& track);
    bool removeTrackByTitle(const QString& title);
    int findTrackByTitle(const QString& title) const;

    bool isEmpty() const;
    int getTrackCount() const;
    void clear();
};