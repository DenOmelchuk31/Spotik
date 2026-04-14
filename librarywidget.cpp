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
    const QString filePath = track.getFilePath();
    const bool isThisPlaying = (filePath == m_nowPlayingPath);

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

    // --- Номер ---
    QLabel *numLabel = new QLabel(QString::number(number));
    numLabel->setFixedWidth(24);
    numLabel->setAlignment(Qt::AlignCenter);
    numLabel->setStyleSheet("color: #888888; font-size: 13px; background: transparent;");

    // --- Кнопка Play / Pause ---
    QPushButton *playBtn = new QPushButton();
    playBtn->setFixedSize(28, 28);
    playBtn->setCursor(Qt::PointingHandCursor);
    playBtn->setStyleSheet(
        "QPushButton {"
        "  background-color: transparent;"
        "  border: none;"
        "  border-radius: 14px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #2a2a2a;"
        "}"
        );

    if (isThisPlaying && m_isPlaying) {
        playBtn->setIcon(QIcon(":/icons/pause.png"));
        playBtn->setIconSize(QSize(20, 20));
        playBtn->setToolTip("Пауза");
    } else {
        playBtn->setIcon(QIcon(":/icons/play.png"));
        playBtn->setIconSize(QSize(20, 20));
        playBtn->setToolTip("Відтворити");
    }

    m_playBtns[filePath] = playBtn;

    connect(playBtn, &QPushButton::clicked, this, [this, filePath]() {
        emit trackPlayRequested(filePath);
    });

    // --- Назва треку ---
    QLabel *titleLabel = new QLabel(
        track.getTitle().isEmpty() ? "(без назви)" : track.getTitle());
    titleLabel->setStyleSheet(
        isThisPlaying
            ? "color: #E8335A; font-size: 14px; font-weight: 600; background: transparent;"
            : "color: white;   font-size: 14px; font-weight: 600; background: transparent;"
        );

    // --- Роздільник ---
    QLabel *sep = new QLabel("·");
    sep->setStyleSheet("color: #555; font-size: 14px; background: transparent;");

    // --- Виконавець ---
    QLabel *artistLabel = new QLabel(
        track.getArtist().isEmpty() ? "Невідомий" : track.getArtist());
    artistLabel->setStyleSheet(
        "color: #aaaaaa; font-size: 13px; background: transparent;");

    // --- Розтягнути простір ---
    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacer->setStyleSheet("background: transparent;");

    // --- Кнопка лайку (сердечко) ---
    QPushButton *likeBtn = new QPushButton();
    likeBtn->setFixedSize(28, 28);
    likeBtn->setCursor(Qt::PointingHandCursor);
    likeBtn->setToolTip(track.isLiked() ? "Прибрати з улюблених" : "Додати до улюблених");
    likeBtn->setIcon(QIcon(track.isLiked() ? ":/icons/LiketrackActive.png" : ":/icons/LiketrackNotactive.png"));
    likeBtn->setIconSize(QSize(20, 20));
    likeBtn->setStyleSheet(
        track.isLiked()
            ? "QPushButton { background: transparent; border: none; border-radius: 14px; }"
              "QPushButton:hover { background-color: #2a2a2a; }"
            : "QPushButton { background: transparent; border: none; border-radius: 14px; }"
              "QPushButton:hover { background-color: #2a2a2a; }"
        );

    m_likeBtns[filePath] = likeBtn;

    connect(likeBtn, &QPushButton::clicked, this, [this, filePath]() {
        emit trackLikeToggled(filePath);
    });

    // --- Кнопка видалення ---
    QPushButton *removeBtn = new QPushButton();
    removeBtn->setFixedSize(28, 28);
    removeBtn->setCursor(Qt::PointingHandCursor);
    removeBtn->setToolTip("Видалити з бібліотеки");
    removeBtn->setIcon(QIcon(":/icons/delete.png"));
    removeBtn->setIconSize(QSize(18, 18));
    removeBtn->setStyleSheet(
        "QPushButton {"
        "  background-color: transparent;"
        "  border: none;"
        "  border-radius: 14px;"
        "}"
        "QPushButton:hover {"
        "  background-color: transparent;"
        "}"
        );

    connect(removeBtn, &QPushButton::clicked, this, [this, filePath]() {
        emit trackRemoved(filePath);
    });

    layout->addWidget(numLabel);
    layout->addWidget(playBtn);
    layout->addWidget(titleLabel);
    layout->addWidget(sep);
    layout->addWidget(artistLabel);
    layout->addWidget(spacer);
    layout->addWidget(likeBtn);
    layout->addWidget(removeBtn);

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
    m_playBtns.clear();
    m_likeBtns.clear();
    ui->trackList->clear();

    int number = 1;
    for (const Track &track : tracks) {
        buildRow(number++, track);
    }

    if (ui->trackList->count() == 0) {
        QListWidgetItem *empty = new QListWidgetItem("  🎵   Бібліотека порожня — додайте перший трек");
        empty->setForeground(QColor("#555555"));
        empty->setFlags(Qt::NoItemFlags);
        ui->trackList->addItem(empty);
    }
}

void LibraryWidget::setNowPlaying(const QString &filePath, bool isPlaying)
{
    const QString prevPath = m_nowPlayingPath;
    m_nowPlayingPath = filePath;
    m_isPlaying      = isPlaying;

    // Скидаємо попередній трек на play
    if (!prevPath.isEmpty() && m_playBtns.contains(prevPath)) {
        m_playBtns[prevPath]->setIcon(QIcon(":/icons/play.png"));
        m_playBtns[prevPath]->setIconSize(QSize(20, 20));
        m_playBtns[prevPath]->setToolTip("Відтворити");
    }

    // Встановлюємо новий стан
    if (!filePath.isEmpty() && m_playBtns.contains(filePath)) {
        m_playBtns[filePath]->setIcon(QIcon(isPlaying ? ":/icons/pause.png" : ":/icons/play.png"));
        m_playBtns[filePath]->setIconSize(QSize(20, 20));
        m_playBtns[filePath]->setToolTip(isPlaying ? "Пауза" : "Відтворити");
    }
}

void LibraryWidget::setTrackLiked(const QString &filePath, bool liked)
{
    if (!m_likeBtns.contains(filePath)) return;
    QPushButton *btn = m_likeBtns[filePath];
    btn->setIcon(QIcon(liked ? ":/icons/LiketrackActive.png" : ":/icons/LiketrackNotactive.png"));
    btn->setIconSize(QSize(20, 20));
    btn->setToolTip(liked ? "Прибрати з улюблених" : "Додати до улюблених");
    btn->setStyleSheet(
        liked
            ? "QPushButton { background: transparent; border: none; border-radius: 14px; }"
              "QPushButton:hover { background-color: #2a2a2a; }"
            : "QPushButton { background: transparent; border: none; border-radius: 14px; }"
              "QPushButton:hover { background-color: #2a2a2a; }"
        );
}
