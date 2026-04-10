#ifndef MAINWINDOW_H
#define MAINWINDOW_H
// #include <feature-track-storage>

#include "MusicLibrary.h"
#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QStackedWidget>
#include "framelesswindow.h"
#include "Track.h"
#include "TrackStorage.h"
#include "librarywidget.h"
#include "favouriteswidget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public FramelessWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
protected:
    void resizeEvent(QResizeEvent *event) override;
    void changeEvent(QEvent *event) override;
private slots:
    void onDownloadBtnClicked();
    void onPlayBtnClicked();
    void on_LikeBtn_clicked();
private:
    Ui::MainWindow *ui;
    QMediaPlayer   *m_player;
    QAudioOutput   *m_audio;
    bool isLiked = false;
    QStackedWidget *stackedWidget;
    QWidget *homePage;
    QWidget *libraryPage;
    QWidget *favouritesPage;
    QWidget *playlistPage;
    QVector<Track> m_tracks;
    LibraryWidget *m_libraryWidget;
    FavouritesWidget *m_favouritesWidget;

    Library library;
    void updateNowPlaying(const QString &filePath);
    void updatePlayButtonIcon();
};
#endif