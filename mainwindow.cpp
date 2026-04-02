#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QPixmap>
#include <QResizeEvent>

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
    m_audio->setVolume(0.5f);

    // Дефолтні значення
    ui->trackNameLabel->setText("Немає треку");
    ui->artistLabel->setText("—");
    ui->albumArt->setText("🎵");
    ui->albumArt->setAlignment(Qt::AlignCenter);
    ui->albumArt->setFixedSize(60, 60);

    connect(ui->downloadBtn, &QPushButton::clicked,
            this, &MainWindow::onDownloadBtnClicked);
    connect(ui->PlayBtn, &QPushButton::clicked,
            this, &MainWindow::onPlayBtnClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    updateNowPlaying(path);
}

void MainWindow::onPlayBtnClicked()
{
    if (m_player->playbackState() == QMediaPlayer::PlayingState) {
        m_player->pause();
    } else {
        m_player->play();
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    int w = centralWidget()->width();
    int h = centralWidget()->height();
    int panelH = 91;
    int leftW = 241;

    ui->leftwidget->setFixedSize(leftW, h);
    ui->playpanel->setGeometry(leftW, h - panelH, w - leftW, panelH);
    ui->nowPlayingWidget->setGeometry(0, h - panelH, leftW, panelH + 2);
}

void MainWindow::updateNowPlaying(const QString &filePath)
{
    // Читаємо метадані через TagLib
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

    // Читаємо обкладинку (тільки MP3)
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



    // Якщо обкладинки немає — показуємо дефолтний текст
    ui->albumArt->setText("🎵");
}