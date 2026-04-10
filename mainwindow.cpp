#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "homewidget.h"
#include "librarywidget.h"
#include "favouriteswidget.h"
#include "playlistwidget.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QPixmap>
#include <QResizeEvent>
#include <QIcon>
#include <QEvent>

// TagLib
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/mpegfile.h>
#include <taglib/id3v2tag.h>
#include <taglib/attachedpictureframe.h>

MainWindow::MainWindow(QWidget *parent)
    : FramelessWindow(parent)
    , ui(new Ui::MainWindow)
    , m_player(new QMediaPlayer(this))
    , m_audio(new QAudioOutput(this))
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setDragWidget(ui->upperwidget);

    stackedWidget = new QStackedWidget(centralWidget());
    stackedWidget->setStyleSheet("background-color: transparent;");

    homePage = new QWidget();
    homePage->setStyleSheet("background-color: #FF4B5C;");

    libraryPage = new QWidget();
    libraryPage->setStyleSheet("background-color: #1A1A1A;");
    // сюди потім додаси QListWidget з треками

    favouritesPage = new QWidget();
    favouritesPage->setStyleSheet("background-color: #1A1A1A;");

    playlistPage = new QWidget();
    playlistPage->setStyleSheet("background-color: #1A1A1A;");
    stackedWidget = new QStackedWidget(centralWidget());

    stackedWidget->addWidget(new HomeWidget());       // індекс 0
    stackedWidget->addWidget(new LibraryWidget());    // індекс 1
    stackedWidget->addWidget(new FavouritesWidget()); // індекс 2
    stackedWidget->addWidget(new PlaylistWidget());   // індекс 3

    stackedWidget->setCurrentIndex(0);

    m_tracks = TrackStorage::load();

    m_libraryWidget = new LibraryWidget();
    m_favouritesWidget = new FavouritesWidget();

    m_libraryWidget->loadTracks(m_tracks);
    m_favouritesWidget->loadTracks(m_tracks);

    stackedWidget->addWidget(new HomeWidget());       // 0
    stackedWidget->addWidget(m_libraryWidget);         // 1
    stackedWidget->addWidget(m_favouritesWidget);      // 2
    stackedWidget->addWidget(new PlaylistWidget());

    // Підключаємо кнопки
    connect(ui->HomeBtn, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentIndex(0);
    });
    connect(ui->LibraryBtn, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentIndex(1);
    });
    connect(ui->FavoriteBtn, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentIndex(2);
    });
    connect(ui->AddBtn, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentIndex(3);
    });

    ui->HomeWidget->hide(); // ховаємо старий HomeWidget

    for (QWidget *child : findChildren<QWidget*>()) {
        child->setMouseTracking(true);
    }
    setMinimumSize(400, 300);

    connect(ui->closeBtn, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->minimizeBtn, &QPushButton::clicked, this, &MainWindow::showMinimized);
    connect(ui->maximizeBtn, &QPushButton::clicked, this, [this]() {
        if (isMaximized()) showNormal();
        else showMaximized();
    });

    m_player->setAudioOutput(m_audio);
    m_audio->setVolume(0.3f);

    ui->HomeWidget->setAutoFillBackground(true);

    ui->trackNameLabel->setText("Немає треку");
    ui->artistLabel->setText("—");
    ui->albumArt->setText("🎵");
    ui->albumArt->setAlignment(Qt::AlignCenter);
    ui->albumArt->setFixedSize(60, 60);

    ui->LikeBtn->setIcon(QIcon(":/icons/LiketrackNotactive.png"));
    ui->LikeBtn->setIconSize(QSize(20, 20));
    ui->LikeBtn->setCheckable(false);

    ui->PlayBtn->setIconSize(QSize(20, 20));
    ui->PlayBtn->setText("");
    updatePlayButtonIcon();

    connect(m_player, &QMediaPlayer::playbackStateChanged,
            this, [this](QMediaPlayer::PlaybackState) {
                updatePlayButtonIcon();
            });

    ui->VolBtn->setIconSize(QSize(25, 25));
    ui->volumeSlider->setValue(30);

    connect(ui->volumeSlider, &QSlider::valueChanged, this, [this](int value) {
        m_audio->setVolume(value / 100.0f);
        if (value == 0) {
            ui->VolBtn->setIcon(QIcon(":/icons/mute.png"));
            ui->VolBtn->setIconSize(QSize(25, 25));
        } else {
            ui->VolBtn->setIcon(QIcon(":/icons/volume.png"));
            ui->VolBtn->setIconSize(QSize(25, 25));
        }
    });

    connect(ui->VolBtn, &QPushButton::clicked, this, [this]() {
        if (m_audio->volume() > 0) {
            m_audio->setVolume(0);
            ui->volumeSlider->setValue(0);
            ui->VolBtn->setIcon(QIcon(":/icons/mute.png"));
            ui->VolBtn->setIconSize(QSize(25, 25));
        } else {
            m_audio->setVolume(0.3f);
            ui->volumeSlider->setValue(30);
            ui->VolBtn->setIcon(QIcon(":/icons/volume.png"));
            ui->VolBtn->setIconSize(QSize(25, 25));
        }
    });

    connect(ui->downloadBtn, &QPushButton::clicked,
            this, &MainWindow::onDownloadBtnClicked);
    connect(ui->PlayBtn, &QPushButton::clicked,
            this, &MainWindow::onPlayBtnClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::WindowStateChange) {
        if (isMaximized()) {
            ui->maximizeBtn->setIcon(QIcon(":/icons/restore.png"));
        } else {
            ui->maximizeBtn->setIcon(QIcon(":/icons/window.png"));
        }
        ui->maximizeBtn->setIconSize(QSize(16, 16));
    }
    QMainWindow::changeEvent(event);
}

void MainWindow::updatePlayButtonIcon()
{
    if (m_player->playbackState() == QMediaPlayer::PlayingState) {
        ui->PlayBtn->setIcon(QIcon(":/icons/pause.png"));
    } else {
        ui->PlayBtn->setIcon(QIcon(":/icons/play.png"));
    }
    ui->PlayBtn->setIconSize(QSize(20, 20));
}

void MainWindow::on_LikeBtn_clicked()
{
    isLiked = !isLiked;
    if (isLiked) {
        ui->LikeBtn->setIcon(QIcon(":/icons/LiketrackActive.png"));
    } else {
        ui->LikeBtn->setIcon(QIcon(":/icons/LiketrackNotactive.png"));
    }
    ui->LikeBtn->setIconSize(QSize(20, 20));
}

void MainWindow::onDownloadBtnClicked()
{
    QString path = QFileDialog::getOpenFileName(
        this, "Відкрити трек", "", "Аудіо (*.mp3 *.wav *.flac *.ogg)");

    if (path.isEmpty()) return;

    m_player->setSource(QUrl::fromLocalFile(path));
    m_player->play();
    updatePlayButtonIcon();
    updateNowPlaying(path);
}

void MainWindow::onPlayBtnClicked()
{
    if (m_player->playbackState() == QMediaPlayer::PlayingState) {
        m_player->pause();
    } else {
        m_player->play();
    }
    updatePlayButtonIcon();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    int w = centralWidget()->width();
    int h = centralWidget()->height();
    int leftW = w * 0.2;
    int btnW = 45;
    int panelH = h * 0.1;
    int upperH = h * 0.1;

    ui->upperwidget->setGeometry(0, 0, w, upperH);
    ui->minimizeBtn->setGeometry(w - btnW * 3, 0, btnW, upperH);
    ui->maximizeBtn->setGeometry(w - btnW * 2, 0, btnW, upperH);
    ui->closeBtn->setGeometry(w - btnW, 0, btnW, upperH);

    ui->LogoWidget->setGeometry(0, 0, leftW, upperH);
    ui->leftwidget->setGeometry(0, upperH, leftW, h - upperH - panelH);
    ui->nowPlayingWidget->setGeometry(0, h - panelH, leftW, panelH + 2);
    ui->playpanel->setGeometry(leftW, h - panelH, w - leftW, panelH);
    stackedWidget->setGeometry(leftW, upperH, w - leftW, h - panelH - upperH);
    ui->HomeWidget->hide();
}

void MainWindow::updateNowPlaying(const QString &filePath)
{
    TagLib::FileRef f(filePath.toStdWString().c_str());

    if (!f.isNull() && f.tag()) {
        TagLib::Tag *tag = f.tag();
        QString title  = QString::fromStdString(tag->title().to8Bit(true));
        QString artist = QString::fromStdString(tag->artist().to8Bit(true));
        ui->trackNameLabel->setText(title.isEmpty() ? QFileInfo(filePath).baseName() : title);
        ui->artistLabel->setText(artist.isEmpty() ? "Невідомий" : artist);
    } else {
        ui->trackNameLabel->setText(QFileInfo(filePath).baseName());
        ui->artistLabel->setText("Невідомий");
    }

    TagLib::MPEG::File mp3(filePath.toStdWString().c_str());
    if (mp3.isValid() && mp3.ID3v2Tag()) {
        auto frames = mp3.ID3v2Tag()->frameListMap()["APIC"];
        if (!frames.isEmpty()) {
            auto *pic = dynamic_cast<TagLib::ID3v2::AttachedPictureFrame*>(frames.front());
            if (pic) {
                QPixmap pixmap;
                pixmap.loadFromData(
                    reinterpret_cast<const uchar*>(pic->picture().data()),
                    pic->picture().size());
                ui->albumArt->setPixmap(
                    pixmap.scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                return;
            }
        }
    }

    ui->albumArt->setText("🎵");
}