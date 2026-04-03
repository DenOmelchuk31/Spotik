#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QPixmap>
#include <QResizeEvent>
#include <QIcon>

// TagLib
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/mpegfile.h>
#include <taglib/id3v2tag.h>
#include <taglib/attachedpictureframe.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_player(new QMediaPlayer(this))
    , m_audio(new QAudioOutput(this))
{
    ui->setupUi(this);

    m_player->setAudioOutput(m_audio);
    m_audio->setVolume(0.3f);

    // Дефолтні значення
    ui->trackNameLabel->setText("Немає треку");
    ui->artistLabel->setText("—");
    ui->albumArt->setText("🎵");
    ui->albumArt->setAlignment(Qt::AlignCenter);
    ui->albumArt->setFixedSize(60, 60);

    // Like кнопка
    ui->LikeBtn->setIcon(QIcon(":/icons/LiketrackNotactive.png"));
    ui->LikeBtn->setIconSize(QSize(20, 20));
    ui->LikeBtn->setCheckable(false);

    // Play кнопка
    ui->PlayBtn->setIconSize(QSize(20, 20));
    ui->PlayBtn->setText("");
    updatePlayButtonIcon();

    connect(m_player, &QMediaPlayer::playbackStateChanged,
            this, [this](QMediaPlayer::PlaybackState) {
                updatePlayButtonIcon();
            });

    // Volume
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
        this,
        "Відкрити трек",
        "",
        "Аудіо (*.mp3 *.wav *.flac *.ogg)"
        );

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
    int panelH = 80;
    int leftW = 241;

    ui->leftwidget->setFixedSize(leftW, h);
    ui->playpanel->setGeometry(leftW, h - panelH, w - leftW, panelH);
    ui->nowPlayingWidget->setGeometry(0, h - panelH, leftW, panelH + 2);
}

void MainWindow::updateNowPlaying(const QString &filePath)
{
    TagLib::FileRef f(filePath.toStdWString().c_str());

    if (!f.isNull() && f.tag()) {
        TagLib::Tag *tag = f.tag();

        QString title  = QString::fromStdString(tag->title().to8Bit(true));
        QString artist = QString::fromStdString(tag->artist().to8Bit(true));

        ui->trackNameLabel->setText(title.isEmpty()
                                        ? QFileInfo(filePath).baseName() : title);
        ui->artistLabel->setText(artist.isEmpty() ? "Невідомий" : artist);
    } else {
        ui->trackNameLabel->setText(QFileInfo(filePath).baseName());
        ui->artistLabel->setText("Невідомий");
    }

    TagLib::MPEG::File mp3(filePath.toStdWString().c_str());
    if (mp3.isValid() && mp3.ID3v2Tag()) {
        auto frames = mp3.ID3v2Tag()->frameListMap()["APIC"];
        if (!frames.isEmpty()) {
            auto *pic = dynamic_cast<TagLib::ID3v2::AttachedPictureFrame*>(
                frames.front()
                );
            if (pic) {
                QPixmap pixmap;
                pixmap.loadFromData(
                    reinterpret_cast<const uchar*>(pic->picture().data()),
                    pic->picture().size()
                    );
                ui->albumArt->setPixmap(
                    pixmap.scaled(60, 60,
                                  Qt::KeepAspectRatio,
                                  Qt::SmoothTransformation)
                    );
                return;
            }
        }
    }

    ui->albumArt->setText("🎵");
}