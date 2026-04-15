#include "TrackStorage.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QStandardPaths>
#include <QDir>

static QString storagePath()
{
    QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dir);
    return dir + "/tracks.json";
}

void TrackStorage::save(const QVector<Track>& tracks)
{
    QJsonArray array;
    for (const auto& track : tracks) {
        array.append(track.toJson());
    }

    QJsonDocument doc(array);
    QFile file(storagePath());
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
    }
}

QVector<Track> TrackStorage::load()
{
    QVector<Track> tracks;
    QFile file(storagePath());
    if (!file.open(QIODevice::ReadOnly))
        return tracks;

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray())
        return tracks;   // захист від пошкодженого JSON

    for (const auto& item : doc.array()) {
        if (item.isObject()) {
            Track t = Track::fromJson(item.toObject());
            if (t.isValid())             // не завантажуємо сміття
                tracks.append(t);
        }
    }
    return tracks;
}
