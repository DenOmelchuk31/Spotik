#include "Track.h"

Track::Track()
    : title(""),
    artist(""),
    album(""),
    genre(""),
    duration(0),
    filePath(""),
    isFavorite(false),
    playCount(0)
{
}

Track::Track(const QString& title,
             const QString& artist,
             const QString& album,
             const QString& genre,
             int duration,
             const QString& filePath,
             bool isFavorite,
             int playCount)
    : title(title),
    artist(artist),
    album(album),
    genre(genre),
    duration(duration),
    filePath(filePath),
    isFavorite(isFavorite),
    playCount(playCount)
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

QString Track::getAlbum() const
{
    return album;
}

QString Track::getGenre() const
{
    return genre;
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

int Track::getPlayCount() const
{
    return playCount;
}

void Track::setTitle(const QString& title)
{
    this->title = title;
}

void Track::setArtist(const QString& artist)
{
    this->artist = artist;
}

void Track::setAlbum(const QString& album)
{
    this->album = album;
}

void Track::setGenre(const QString& genre)
{
    this->genre = genre;
}

void Track::setDuration(int duration)
{
    if (duration >= 0)
    {
        this->duration = duration;
    }
}

void Track::setFilePath(const QString& filePath)
{
    this->filePath = filePath;
}

void Track::setFavorite(bool value)
{
    isFavorite = value;
}

void Track::setPlayCount(int count)
{
    if (count >= 0)
    {
        playCount = count;
    }
}

void Track::incrementPlayCount()
{
    playCount++;
}

bool Track::isValid() const
{
    return !title.trimmed().isEmpty()
    && !artist.trimmed().isEmpty()
        && duration > 0
        && !filePath.trimmed().isEmpty();
}

QString Track::getFormattedDuration() const
{
    int minutes = duration / 60;
    int seconds = duration % 60;

    QString secondsText;
    if (seconds < 10)
    {
        secondsText = "0" + QString::number(seconds);
    }
    else
    {
        secondsText = QString::number(seconds);
    }

    return QString::number(minutes) + ":" + secondsText;
}