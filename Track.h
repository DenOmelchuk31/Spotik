#pragma once
#include <string>

class Track {
private:
    std::string title;
    std::string artist;
    int duration; // seconds
    std::string filePath;
    bool isFavorite;

public:
    Track();
    Track(std::string t, std::string a, int d, std::string path);

    std::string getTitle() const;
    std::string getArtist() const;
    int getDuration() const;
    std::string getFilePath() const;
    bool getFavorite() const;

    void setFavorite(bool value);
};