#ifndef TRACK_H
#define TRACK_H

#include <QString>
#include <QJsonObject>

class Track
{
private:
    QString title;
    QString artist;
    QString album;
    QString filePath;
    int duration;
    bool liked;

public:
    Track();
    Track(const QString& title, const QString& artist, const QString& album, const QString& filePath, int duration, bool liked = false);

    QJsonObject toJson() const;
    static Track fromJson(const QJsonObject& obj);

    QString getTitle() const;
    QString getArtist() const;
    QString getAlbum() const;
    QString getFilePath() const;
    int getDuration() const;
    bool isLiked() const;
    bool isValid() const;

    void setTitle(const QString& title);
    void setArtist(const QString& artist);
    void setAlbum(const QString& album);
    void setFilePath(const QString& filePath);
    void setDuration(int duration);
    void setLiked(bool liked);

    void toggleLike();
};

#endif // TRACK_H