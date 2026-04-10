#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include <QWidget>
#include <QVector>
#include <QMap>
#include <QPushButton>
#include "Track.h"

namespace Ui {
class LibraryWidget;
}

class LibraryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LibraryWidget(QWidget *parent = nullptr);
    ~LibraryWidget();
    void loadTracks(const QVector<Track> &tracks);

    // Оновити стан Play/Pause та лайку без перебудови всього списку
    void setNowPlaying(const QString &filePath, bool isPlaying);
    void setTrackLiked(const QString &filePath, bool liked);

signals:
    void trackPlayRequested(const QString &filePath);
    void trackRemoved(const QString &filePath);
    void trackLikeToggled(const QString &filePath);

private:
    Ui::LibraryWidget *ui;
    QVector<Track> m_tracks;

    // filePath → відповідна кнопка (для динамічного оновлення)
    QMap<QString, QPushButton*> m_playBtns;
    QMap<QString, QPushButton*> m_likeBtns;

    QString m_nowPlayingPath;
    bool    m_isPlaying = false;

    void buildRow(int number, const Track &track);
};

#endif
