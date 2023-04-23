#ifndef FILTER_H
#define FILTER_H

#include "CustomGraphicsScene.h"
#include "functionFilter.h"
#include "imageToQImage.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolButton>
#include <QDateTime>
#include <QWidget>
#include <QCursor>
#include <QAction>
#include <QPixmap>
#include <QString>
#include <QColor>
#include <QMenu>



class FilterWidget: public QWidget
{
    Q_OBJECT
public:
    FilterWidget(QWidget *parent = nullptr);
//private:

    bool is_button_active = false;
    bool is_brush_active=false;
    //layouts
    QVBoxLayout *vlay1;
    QHBoxLayout *main_hlay;
    QVBoxLayout *vlay2;
    QHBoxLayout *hlay;
    QVBoxLayout *main_vlay;

    //filters
    QToolButton* original;
    QToolButton* sand;
    QToolButton* black_and_white;
    QToolButton* rain;
    QToolButton* hands; 
    QToolButton* date;
    QToolButton* blur;
    QToolButton* rainbow;
    QToolButton* snow;
    QToolButton* sparkles;
    QToolButton* redNose;
    QToolButton* square_on_face;

    //tools
    QToolButton* zoomIn;
    QToolButton* zoomOut;
    QToolButton* rotate_left;
    QToolButton* rotate_right;
    QToolButton* paint;
    QToolButton* erase;
    QToolButton* color;
    QToolButton* size_plus;
    QToolButton* size_minus;
    QToolButton* wheel;
    QToolButton* save;

    //go back button
    QToolButton* fromFilterback_button;

    //zoom in/out, rotates
    CustomGraphicsScene *scene;
    QGraphicsView *view;

    //image
    QPixmap originalPic;
    QPixmap pixmap;
    QPixmap prev;
    void setImage(QString);
    void setCamImage(const QPixmap* pixmap);
    QColor currentColor = Qt::black; // Initial pen color is black
    int penSize = 2;
    QCursor cursor;
public slots:
    void changeColor();
    void clearDrawing();
    void setPenSizeBig();
    void setPenSizeSmall();
    void slotZoomin();
    void slotZoomout();
    void slotRotateLeft();
    void slotRotateRight();
    void saveImages();
};


#endif // FILTER_H
