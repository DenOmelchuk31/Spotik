#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MusicLibrary.h"
#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onDownloadBtnClicked();
    void onPlayBtnClicked();
    void on_LikeBtn_clicked();

private:
    Ui::MainWindow *ui;
    bool isLiked = false;

    QMediaPlayer *m_player;
    QAudioOutput *m_audio;

    Library library;

    void updateNowPlaying(const QString &filePath);
    void updatePlayButtonIcon();

};

#endif // MAINWINDOW_H