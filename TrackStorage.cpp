#include "TrackStorage.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDir>

void TrackStorage::save(const QVector<Track>& tracks) {
    QJsonArray array;
    for (const auto& track : tracks) {
        array.append(track.toJson());
    }

    QJsonDocument doc(array);

    // Створюємо папку data, якщо її немає
    if (!QDir("data").exists()) {
        QDir().mkdir("data");
    }

    QFile file("data/tracks.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

QVector<Track> TrackStorage::load() {
    QVector<Track> tracks;
    QFile file("data/tracks.json");
    if (!file.open(QIODevice::ReadOnly)) return tracks;

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();

    for (const auto& item : array) {
        tracks.append(Track::fromJson(item.toObject()));
    }
    return tracks;
}