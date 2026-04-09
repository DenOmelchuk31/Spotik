#ifndef FRAMELESSWINDOW_H
#define FRAMELESSWINDOW_H
#include <QMainWindow>
#include <QMouseEvent>
class FramelessWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit FramelessWindow(QWidget *parent = nullptr);
    void setDragWidget(QWidget *widget) { m_dragWidget = widget; }
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    enum Edge { None, Left, Right, Top, Bottom, TopLeft, TopRight, BottomLeft, BottomRight };
    Edge getEdge(const QPoint &pos);
    bool isInDragWidget(const QPoint &globalPos);
    QWidget *m_dragWidget = nullptr;
    bool m_dragging = false;
    bool m_resizing = false;
    QPoint m_dragPos;
    QRect m_startGeometry;
    QPoint m_startPos;
    Edge m_edge = None;
    const int BORDER = 8;
};
#endif // FRAMELESSWINDOW_H