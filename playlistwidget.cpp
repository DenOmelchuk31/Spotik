#include "playlistwidget.h"
#include "ui_playlistwidget.h"
#include <QMessageBox>

PlaylistWidget::PlaylistWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlaylistWidget)
{
    ui->setupUi(this);
    setStyleSheet("background-color: #121212;");

    connect(ui->createBtn, &QPushButton::clicked,
            this, &PlaylistWidget::onCreateClicked);
}

PlaylistWidget::~PlaylistWidget()
{
    delete ui;
}

void PlaylistWidget::onCreateClicked()
{
    QString name = ui->playlistNameEdit->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Введіть назву плейлисту");
        return;
    }
    emit playlistCreated(name);
    ui->playlistNameEdit->clear();
}