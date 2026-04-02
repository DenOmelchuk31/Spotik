#include "Player.h"

Player::Player()
    : isPlaying(false)
{
}

void Player::setQueue(const Queue& queue)
{
    playQueue = queue;
}

bool Player::play()
{
    if (!currentTrack.isValid())
    {
        if (!playNext())
        {
            return false;
        }
    }

    isPlaying = true;
    return true;
}

void Player::pause()
{
    isPlaying = false;
}

void Player::stop()
{
    isPlaying = false;
    currentTrack = Track();
}

bool Player::playNext()
{
    Track nextTrack;

    if (playQueue.dequeue(nextTrack))
    {
        currentTrack = nextTrack;
        isPlaying = true;
        return true;
    }

    currentTrack = Track();
    isPlaying = false;
    return false;
}

Track Player::getCurrentTrack() const
{
    return currentTrack;
}

Queue Player::getQueue() const
{
    return playQueue;
}

bool Player::getIsPlaying() const
{
    return isPlaying;
}

bool Player::hasCurrentTrack() const
{
    return currentTrack.isValid();
}