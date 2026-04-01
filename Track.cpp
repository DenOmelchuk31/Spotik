#include "Track.h"

Track::Track()
    : title(""),
    artist(""),
    duration(0),
    filePath(""),
    isFavorite(false)
{
}

Track::Track(const QString& title, const QString& artist, int duration, const QString& filePath, bool isFavorite)
    : title(title),
    artist(artist),
    duration(duration),
    filePath(filePath),
    isFavorite(isFavorite)
{
}

QString Track::getTitle() const
{
    return title;
}

QString Track::getArtist() const
{
    return artist;
}

int Track::getDuration() const
{
    return duration;
}

QString Track::getFilePath() const
{
    return filePath;
}

bool Track::getFavorite() const
{
    return isFavorite;
}

void Track::setTitle(const QString& title)
{
    this->title = title;
}

void Track::setArtist(const QString& artist)
{
    this->artist = artist;
}

void Track::setDuration(int duration)
{
    this->duration = duration;
}

void Track::setFilePath(const QString& filePath)
{
    this->filePath = filePath;
}

void Track::setFavorite(bool value)
{
    isFavorite = value;
}