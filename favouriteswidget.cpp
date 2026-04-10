#include "favouriteswidget.h"
#include "ui_favouriteswidget.h"

FavouritesWidget::FavouritesWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FavouritesWidget)
{
    ui->setupUi(this);
    setStyleSheet("background-color: #121212;");
}

FavouritesWidget::~FavouritesWidget()
{
    delete ui;
}

void FavouritesWidget::loadTracks(const QVector<Track> &tracks)
{
    ui->favouritesList->clear();

    for (const Track &track : tracks) {
        if (track.isLiked()) {
            QString display = track.getTitle() + " — " + track.getArtist();
            QListWidgetItem *item = new QListWidgetItem(display);
            item->setData(Qt::UserRole, track.getFilePath());
            ui->favouritesList->addItem(item);
        }
    }
}