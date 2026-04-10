#include "librarywidget.h"
#include "ui_librarywidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>

LibraryWidget::LibraryWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LibraryWidget)
{
    ui->setupUi(this);
    setStyleSheet("background-color: #121212;");
}

LibraryWidget::~LibraryWidget()
{
    delete ui;
}

void LibraryWidget::loadTracks(const QVector<Track> &tracks)
{
    m_tracks = tracks;
    ui->trackList->clear();

    for (const Track &track : tracks) {
        QString display = track.getTitle() + " — " + track.getArtist();
        QListWidgetItem *item = new QListWidgetItem(display);
        item->setData(Qt::UserRole, track.getFilePath());
        ui->trackList->addItem(item);
    }
}