#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include <QWidget>
#include <QVector>
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

signals:
    void trackSelected(const Track &track);
    void trackRemoved(const QString &filePath); // сигнал видалення

private:
    Ui::LibraryWidget *ui;
    QVector<Track> m_tracks;
    void buildRow(int number, const Track &track);
};

#endif
