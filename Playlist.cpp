#include "Playlist.h"

Playlist::Playlist()
    : name("")
{
}

Playlist::Playlist(const QString& name)
    : name(name)
{
}

QString Playlist::getName() const
{
    return name;
}

QVector<Track> Playlist::getTracks() const
{
    return tracks;
}

void Playlist::setName(const QString& name)
{
    this->name = name;
}

void Playlist::addTrack(const Track& track)
{
    if (track.isValid())
    {
        tracks.push_back(track);
    }
}

bool Playlist::removeTrackByTitle(const QString& title)
{
    for (int i = 0; i < tracks.size(); i++)
    {
        if (tracks[i].getTitle().compare(title, Qt::CaseInsensitive) == 0)
        {
            tracks.remove(i);
            return true;
        }
    }

    return false;
}

int Playlist::findTrackByTitle(const QString& title) const
{
    for (int i = 0; i < tracks.size(); i++)
    {
        if (tracks[i].getTitle().compare(title, Qt::CaseInsensitive) == 0)
        {
            return i;
        }
    }

    return -1;
}

bool Playlist::isEmpty() const
{
    return tracks.isEmpty();
}

int Playlist::getTrackCount() const
{
    return tracks.size();
}

void Playlist::clear()
{
    tracks.clear();
}