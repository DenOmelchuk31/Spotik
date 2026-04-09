#include "framelesswindow.h"

FramelessWindow::FramelessWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);
}

FramelessWindow::Edge FramelessWindow::getEdge(const QPoint &pos)
{
    int x = pos.x(), y = pos.y(), w = width(), h = height();
    if (x <= BORDER && y <= BORDER) return TopLeft;
    if (x >= w - BORDER && y <= BORDER) return TopRight;
    if (x <= BORDER && y >= h - BORDER) return BottomLeft;
    if (x >= w - BORDER && y >= h - BORDER) return BottomRight;
    if (x <= BORDER) return Left;
    if (x >= w - BORDER) return Right;
    if (y <= BORDER) return Top;
    if (y >= h - BORDER) return Bottom;
    return None;
}

bool FramelessWindow::isInDragWidget(const QPoint &globalPos)
{
    if (!m_dragWidget) return false;
    QPoint local = m_dragWidget->mapFromGlobal(globalPos);
    return m_dragWidget->rect().contains(local);
}

void FramelessWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_edge = isMaximized() ? None : getEdge(event->pos());
        if (m_edge != None) {
            m_resizing = true;
            m_startGeometry = geometry();
            m_startPos = event->globalPosition().toPoint();
        } else if (isInDragWidget(event->globalPosition().toPoint())) {
            m_dragging = true;
            m_dragPos = event->globalPosition().toPoint() - frameGeometry().topLeft();
        }
    }
    QMainWindow::mousePressEvent(event);
}

void FramelessWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_resizing) {
        QPoint delta = event->globalPosition().toPoint() - m_startPos;
        QRect geo = m_startGeometry;
        switch (m_edge) {
        case Left:        geo.setLeft(geo.left() + delta.x()); break;
        case Right:       geo.setRight(geo.right() + delta.x()); break;
        case Top:         geo.setTop(geo.top() + delta.y()); break;
        case Bottom:      geo.setBottom(geo.bottom() + delta.y()); break;
        case TopLeft:     geo.setTopLeft(geo.topLeft() + delta); break;
        case TopRight:    geo.setTopRight(geo.topRight() + delta); break;
        case BottomLeft:  geo.setBottomLeft(geo.bottomLeft() + delta); break;
        case BottomRight: geo.setBottomRight(geo.bottomRight() + delta); break;
        default: break;
        }
        if (geo.width() >= minimumWidth() && geo.height() >= minimumHeight())
            setGeometry(geo);
    } else if (m_dragging) {
        if (isMaximized()) {
            showNormal();
            QPoint globalPos = event->globalPosition().toPoint();
            m_dragPos = QPoint(width() / 2, 10);
            move(globalPos - m_dragPos);
        }
        move(event->globalPosition().toPoint() - m_dragPos);
    } else {
        if (isMaximized()) {
            setCursor(Qt::ArrowCursor);
        } else {
            Edge edge = getEdge(event->pos());
            switch (edge) {
            case Left: case Right:           setCursor(Qt::SizeHorCursor); break;
            case Top: case Bottom:           setCursor(Qt::SizeVerCursor); break;
            case TopLeft: case BottomRight:  setCursor(Qt::SizeFDiagCursor); break;
            case TopRight: case BottomLeft:  setCursor(Qt::SizeBDiagCursor); break;
            default:                         setCursor(Qt::ArrowCursor); break;
            }
        }
    }
    QMainWindow::mouseMoveEvent(event);
}

void FramelessWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_dragging = false;
    m_resizing = false;
    m_edge = None;
    setCursor(Qt::ArrowCursor);
    QMainWindow::mouseReleaseEvent(event);
}