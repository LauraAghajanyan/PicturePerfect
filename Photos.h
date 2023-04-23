#ifndef PHOTOS_H
#define PHOTOS_H

#include <QGridLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include <QWidget>
#include <QVector>
#include <QString>

class PhotosWidget : public QWidget
{
    Q_OBJECT

public:
    PhotosWidget(QWidget *parent = nullptr);
public:
    //go back to home page
    QToolButton *fromPhotosBack_button;

    //layouts
    QVBoxLayout* lay;
    QGridLayout *grid_lay;

    //buttons of gallery pictures
    QVector<QToolButton*> button_array;
    //gallery pictures
    QVector<QString> path_array={":Images/selena.jpg",
                                        ":Images/ariana_grande.jpeg",
                                        ":Images/image2.jpg",
                                        ":Images/smiles.png",
                                        ":Icons/image.png"};
};



#endif // PHOTOS_H


