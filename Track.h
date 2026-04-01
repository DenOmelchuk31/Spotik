#pragma once

#include <QString>

class Track
{
private:
    QString title;
    QString artist;
    int duration;
    QString filePath;
    bool isFavorite;

public:
    Track();
    Track(const QString& title, const QString& artist, int duration, const QString& filePath, bool isFavorite = false);

    QString getTitle() const;
    QString getArtist() const;
    int getDuration() const;
    QString getFilePath() const;
    bool getFavorite() const;

    void setTitle(const QString& title);
    void setArtist(const QString& artist);
    void setDuration(int duration);
    void setFilePath(const QString& filePath);
    void setFavorite(bool value);
};