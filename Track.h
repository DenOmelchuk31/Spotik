#pragma once

#include <QString>

class Track
{
private:
    QString title;
    QString artist;
    QString album;
    QString genre;
    int duration;
    QString filePath;
    bool isFavorite;
    int playCount;

public:
    Track();
    Track(const QString& title,
          const QString& artist,
          const QString& album,
          const QString& genre,
          int duration,
          const QString& filePath,
          bool isFavorite = false,
          int playCount = 0);

    QString getTitle() const;
    QString getArtist() const;
    QString getAlbum() const;
    QString getGenre() const;
    int getDuration() const;
    QString getFilePath() const;
    bool getFavorite() const;
    int getPlayCount() const;

    void setTitle(const QString& title);
    void setArtist(const QString& artist);
    void setAlbum(const QString& album);
    void setGenre(const QString& genre);
    void setDuration(int duration);
    void setFilePath(const QString& filePath);
    void setFavorite(bool value);
    void setPlayCount(int count);

    void incrementPlayCount();

    bool isValid() const;
    QString getFormattedDuration() const;
};