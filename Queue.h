#pragma once

#include <QVector>
#include "Track.h"

class Queue
{
private:
    QVector<Track> tracks;

public:
    Queue();

    void enqueue(const Track& track);
    bool dequeue(Track& track);

    Track peek() const;

    QVector<Track> getTracks() const;

    bool isEmpty() const;
    int size() const;
    void clear();
};