#ifndef TRACKSTORAGE_H
#define TRACKSTORAGE_H

#include <QVector>
#include "Track.h"

class TrackStorage {
public:
    static void save(const QVector<Track>& tracks);
    static QVector<Track> load();

private:
    TrackStorage() = delete;   // суто статичний клас — не можна створити екземпляр
};

#endif // TRACKSTORAGE_H
