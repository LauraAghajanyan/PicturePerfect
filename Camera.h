#ifndef CAMERA_H
#define CAMERA_H

#include "frameCapture.h"
#include <QApplication>
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPixmap>
#include <QLabel>

class CameraWidget : public QWidget
{
    Q_OBJECT

public:
    CameraWidget(QWidget *parent = nullptr);
    ~CameraWidget();

    // create a label to display camera stream
    QLabel *m_label;
    Camera cam;

    //filters on camera widget
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
    int filterNumber=0;
    int timerId;
    void timerEvent(QTimerEvent* event);
public:
    QToolButton *goToPhotos_button;
    QToolButton *goToFilter_button;
};
#endif // CAMERA_H

