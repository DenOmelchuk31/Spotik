#ifndef FAVOURITESWIDGET_H
#define FAVOURITESWIDGET_H

#include <QWidget>
#include <QVector>
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

signals:
    void trackSelected(const Track &track);

private:
    Ui::FavouritesWidget *ui;
};

#endif