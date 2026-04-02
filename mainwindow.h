#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private:
    Ui::MainWindow *ui;

        QMediaPlayer *m_player;
    QAudioOutput *m_audio;

    void updateNowPlaying(const QString &filePath);
    void updatePlayButtonIcon();

};

#endif // MAINWINDOW_H