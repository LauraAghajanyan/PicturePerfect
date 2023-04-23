#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imageToQImage.h"
#include "frameCapture.h"
#include "Camera.h"
#include "Filter.h"
#include "Photos.h"
#include <QStackedWidget>
#include <QApplication>
#include <QMainWindow>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenuBar>
#include <QPalette>
#include <QAction>
#include <QPixmap>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QMenu>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
    void addPhoto();

private:
    //creating stacked widgets to keep different widgets and to work with them
    QStackedWidget *stackedWidget;
    //3 widgets 
    CameraWidget *cameraWidget;
    PhotosWidget *photosWidget;
    FilterWidget *filterWidget;
    QWidget *photoWidget;
    QLabel *photoLabel;

    //creating a menubar
    QMenuBar* menuBar;
    QMenu *mode_menu;
    QMenu *help_menu;
    QAction *light;
    QAction *dark;
    QAction *about_us;
public slots:
    void toggleLightMode();
    void toggleDarkMode();
    void aboutUsMessageBox();
};


#endif // MAINWINDOW_H



