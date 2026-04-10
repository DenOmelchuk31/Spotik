#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QWidget>

namespace Ui {
class PlaylistWidget;
}

class PlaylistWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlaylistWidget(QWidget *parent = nullptr);
    ~PlaylistWidget();

signals:
    void playlistCreated(const QString &name);

private slots:
    void onCreateClicked();

private:
    Ui::PlaylistWidget *ui;
};

#endif