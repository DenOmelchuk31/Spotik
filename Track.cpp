#include "Track.h"

Track::Track()
    : title(QString()),
    artist(QString()),
    album(QString()),
    filePath(QString()),
    duration(0),
    liked(false)
{}

Track::Track(const QString& title, const QString& artist, const QString& album,
             const QString& filePath, int duration, bool liked)
    : title(title),
    artist(artist),
    album(album),
    filePath(filePath),
    duration(duration >= 0 ? duration : 0),  // БАГ-ФІХ: захист у конструкторі
    liked(liked)
{}

QString Track::getTitle()    const { return title;    }
QString Track::getArtist()   const { return artist;   }
QString Track::getAlbum()    const { return album;    }
QString Track::getFilePath() const { return filePath; }
int     Track::getDuration() const { return duration; }
bool    Track::isLiked()     const { return liked;    }

bool Track::isValid() const {
    return !title.trimmed().isEmpty() && !filePath.trimmed().isEmpty();
}

void Track::setTitle(const QString& title)       { this->title  = title;  }
void Track::setArtist(const QString& artist)     { this->artist = artist; }
void Track::setAlbum(const QString& album)       { this->album  = album;  }
void Track::setFilePath(const QString& filePath) { this->filePath = filePath; }
void Track::setLiked(bool liked)                 { this->liked  = liked;  }

void Track::setDuration(int duration) {
    if (duration >= 0)
        this->duration = duration;
}

void Track::toggleLike() {
    liked = !liked;
}

QJsonObject Track::toJson() const {
    QJsonObject obj;
    obj["title"]    = title;
    obj["artist"]   = artist;
    obj["album"]    = album;
    obj["filePath"] = filePath;
    obj["duration"] = duration;
    obj["isLiked"]  = liked;
    return obj;
}

Track Track::fromJson(const QJsonObject& obj) {
    // БАГ-ФІХ: перевіряємо наявність ключів перш ніж читати
    return Track(
        obj.value("title").toString(),
        obj.value("artist").toString(),
        obj.value("album").toString(),
        obj.value("filePath").toString(),
        obj.value("duration").toInt(),
        obj.value("isLiked").toBool()
        );
}
