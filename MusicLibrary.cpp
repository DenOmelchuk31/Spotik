#include "MusicLibrary.h"

void Library::addTrack(const Track& track)
{
    if (track.isValid())
        tracks.push_back(track);
}

bool Library::removeTrackByTitle(const QString& title)
{
    int index = findTrackByTitle(title);
    if (index == -1) return false;
    tracks.removeAt(index);
    return true;
}

int Library::findTrackByTitle(const QString& title) const
{
    for (int i = 0; i < tracks.size(); i++) {
        if (tracks[i].getTitle().compare(title, Qt::CaseInsensitive) == 0)
            return i;
    }
    return -1;
}

bool Library::hasTrack(const QString& title) const
{
    return findTrackByTitle(title) != -1;
}
