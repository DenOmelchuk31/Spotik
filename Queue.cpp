#include "Queue.h"

Queue::Queue() {}

void Queue::enqueue(const Track& track)
{
    if (track.isValid())
    {
        tracks.push_back(track);
    }
}

bool Queue::dequeue(Track& track)
{
    if (tracks.isEmpty())
    {
        return false;
    }

    track = tracks.front();
    tracks.removeFirst();
    return true;
}

Track Queue::peek() const
{
    if (tracks.isEmpty())
    {
        return Track();
    }

    return tracks.first();
}

QVector<Track> Queue::getTracks() const
{
    return tracks;
}

bool Queue::isEmpty() const
{
    return tracks.isEmpty();
}

int Queue::size() const
{
    return tracks.size();
}

void Queue::clear()
{
    tracks.clear();
}