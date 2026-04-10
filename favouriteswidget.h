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
    void trackRemoved(const QString &filePath);  // новий сигнал — видалення

private:
    Ui::FavouritesWidget *ui;
    void buildRow(int number, const Track &track);
};

#endif