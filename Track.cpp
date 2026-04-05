#include "Track.h"

Track::Track()
    : title(""),
    artist(""),
    album(""),
    filePath(""),
    duration(0),
    liked(false)
{
}

Track::Track(const QString& title, const QString& artist, const QString& album, const QString& filePath, int duration, bool liked)
    : title(title),
    artist(artist),
    album(album),
    filePath(filePath),
    duration(duration),
    liked(liked)
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

QString Track::getFilePath() const
{
    return filePath;
}

int Track::getDuration() const
{
    return duration;
}

bool Track::isLiked() const
{
    return liked;
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

void Track::setFilePath(const QString& filePath)
{
    this->filePath = filePath;
}

void Track::setDuration(int duration)
{
    if (duration >= 0) {
        this->duration = duration;
    }
}

void Track::setLiked(bool liked)
{
    this->liked = liked;
}

void Track::toggleLike()
{
    liked = !liked;
}
bool Track::isValid() const {
    return !title.trimmed().isEmpty()
    && !artist.trimmed().isEmpty()
        && duration > 0;
}

QJsonObject Track::toJson() const {
    QJsonObject obj;
    obj["title"] = title;
    obj["artist"] = artist;
    obj["album"] = album;
    obj["filePath"] = filePath;
    obj["duration"] = duration;
    obj["isLiked"] = liked;
    return obj;
}

Track Track::fromJson(const QJsonObject& obj) {
    return Track(
        obj["title"].toString(),
        obj["artist"].toString(),
        obj["album"].toString(),
        obj["filePath"].toString(),
        obj["duration"].toInt(),
        obj["isLiked"].toBool()
        );
}