#ifndef FAVOURITESWIDGET_H
#define FAVOURITESWIDGET_H

#include <QWidget>
#include <QVector>
#include <QMap>
#include <QPushButton>
#include "Track.h"

namespace Ui {
class FavouritesWidget;
}

class FavouritesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FavouritesWidget(QWidget *parent = nullptr);
    ~FavouritesWidget();
    void loadTracks(const QVector<Track> &tracks);

    // Оновити стан Play/Pause без перебудови списку
    void setNowPlaying(const QString &filePath, bool isPlaying);

signals:
    void trackSelected(const Track &track);
    void trackPlayRequested(const QString &filePath);
    void trackRemoved(const QString &filePath);
    void trackLikeToggled(const QString &filePath);

private:
    Ui::FavouritesWidget *ui;

    QMap<QString, QPushButton*> m_playBtns;

    QString m_nowPlayingPath;
    bool    m_isPlaying = false;

    void buildRow(int number, const Track &track);
};

#endif
