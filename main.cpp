#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) 
{
    // creating an instance of the QApplication class, which manages the GUI application and its event loop
    QApplication app(argc, argv);
    //creating an instance of the MainWindow class, which is a custom widget that represents the main window of the application
    MainWindow w;
    //showing the main window on the screen
    w.show();
    //starting the event loop of the application and waiting for events to be processed
    return app.exec();
}
