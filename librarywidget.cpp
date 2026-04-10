#include "librarywidget.h"
#include "ui_librarywidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidgetItem>

LibraryWidget::LibraryWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LibraryWidget)
{
    ui->setupUi(this);

    setStyleSheet("background-color: #121212;");

    ui->libraryTitle->setStyleSheet(
        "color: white;"
        "font-size: 24px;"
        "font-weight: bold;"
        "padding: 20px 20px 12px 20px;"
        );

    ui->trackList->setStyleSheet(
        "QListWidget {"
        "  background-color: #121212;"
        "  border: none;"
        "  outline: none;"
        "  padding: 4px 12px;"
        "}"
        "QListWidget::item {"
        "  background-color: transparent;"
        "  border: none;"
        "  margin: 3px 0px;"
        "}"
        "QListWidget::item:selected {"
        "  background-color: transparent;"
        "}"
        );

    ui->trackList->setSelectionMode(QAbstractItemView::NoSelection);
    ui->trackList->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->trackList->setSpacing(2);
}

LibraryWidget::~LibraryWidget()
{
    delete ui;
}

void LibraryWidget::buildRow(int number, const Track &track)
{
    // Контейнер рядка
    QWidget *row = new QWidget();
    row->setFixedHeight(52);
    row->setStyleSheet(
        "QWidget { background-color: #1A1A1A; border-radius: 8px; }"
        "QWidget:hover { background-color: #282828; }"
        );

    QHBoxLayout *layout = new QHBoxLayout(row);
    layout->setContentsMargins(12, 0, 12, 0);
    layout->setSpacing(12);

    // Номер
    QLabel *numLabel = new QLabel(QString::number(number));
    numLabel->setFixedWidth(28);
    numLabel->setAlignment(Qt::AlignCenter);
    numLabel->setStyleSheet("color: #888888; font-size: 13px; background: transparent;");

    // Назва треку
    QLabel *titleLabel = new QLabel(
        track.getTitle().isEmpty() ? "(без назви)" : track.getTitle());
    titleLabel->setStyleSheet(
        "color: white; font-size: 14px; font-weight: 600; background: transparent;");

    // Роздільник
    QLabel *sep = new QLabel("·");
    sep->setStyleSheet("color: #555; font-size: 14px; background: transparent;");

    // Виконавець
    QLabel *artistLabel = new QLabel(
        track.getArtist().isEmpty() ? "Невідомий" : track.getArtist());
    artistLabel->setStyleSheet(
        "color: #aaaaaa; font-size: 13px; background: transparent;");

    // Розтягнути пустий простір
    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacer->setStyleSheet("background: transparent;");

    // Кнопка видалення
    QPushButton *removeBtn = new QPushButton("✕");
    removeBtn->setFixedSize(28, 28);
    removeBtn->setCursor(Qt::PointingHandCursor);
    removeBtn->setToolTip("Видалити з бібліотеки");
    removeBtn->setStyleSheet(
        "QPushButton {"
        "  background-color: transparent;"
        "  color: #888888;"
        "  border: none;"
        "  font-size: 14px;"
        "  border-radius: 14px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #ff4444;"
        "  color: white;"
        "}"
        );

    QString filePath = track.getFilePath();
    connect(removeBtn, &QPushButton::clicked, this, [this, filePath]() {
        emit trackRemoved(filePath);
    });

    layout->addWidget(numLabel);
    layout->addWidget(titleLabel);
    layout->addWidget(sep);
    layout->addWidget(artistLabel);
    layout->addWidget(spacer);
    layout->addWidget(removeBtn);

    // Додаємо рядок у QListWidget
    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(QSize(0, 56));
    item->setData(Qt::UserRole, filePath);
    item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
    ui->trackList->addItem(item);
    ui->trackList->setItemWidget(item, row);
}

void LibraryWidget::loadTracks(const QVector<Track> &tracks)
{
    m_tracks = tracks;
    ui->trackList->clear();

    int number = 1;
    for (const Track &track : tracks) {
        buildRow(number++, track);
    }

    // Якщо список порожній
    if (ui->trackList->count() == 0) {
        QListWidgetItem *empty = new QListWidgetItem("  🎵   Бібліотека порожня — додайте перший трек");
        empty->setForeground(QColor("#555555"));
        empty->setFlags(Qt::NoItemFlags);
        ui->trackList->addItem(empty);
    }
}
