#include "CustomGraphicsScene.h"

CustomGraphicsScene::CustomGraphicsScene(QObject* parent)
    : QGraphicsScene(parent)
{
}
void CustomGraphicsScene::setPixmap(QPixmap& pixmap,QColor& col,int& size)
{
    m_pixmap = &pixmap;
    m_currentColor = &col;
    m_penSize = &size;
}
void CustomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{ 
    if(is_active){
        if (event->button() == Qt::LeftButton) {
            // Record the last position of the mouse
            m_lastPos = event->scenePos();
        }
    }
}
void CustomGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(is_active){
        if (event->buttons() & Qt::LeftButton) {
            // Draw on the pixmap using a QPainter
            QPainter painter(m_pixmap);
            painter.setPen(QPen(*m_currentColor, *m_penSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawLine(m_lastPos, event->scenePos());
            m_lastPos = event->scenePos();
            clear();
            addPixmap(*m_pixmap);
        }
    }
}
void CustomGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if(is_active){
        if (event->button() == Qt::LeftButton) {
            // Record the last position of the mouse
            m_lastPos = event->scenePos();
        }
    }
}

