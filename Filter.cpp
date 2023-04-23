#include "Filter.h"

FilterWidget::FilterWidget(QWidget *parent)
    : QWidget(parent)
{
    cursor.setShape(Qt::ArrowCursor);
    setCursor(cursor);

    //layouts
    vlay1 = new QVBoxLayout;
    main_hlay=new QHBoxLayout;
    vlay2=new QVBoxLayout;
    hlay=new QHBoxLayout;
    main_vlay = new QVBoxLayout;

    //filters
    original = new QToolButton;
    black_and_white = new QToolButton;
    sand = new QToolButton;
    rain = new QToolButton;
    hands = new QToolButton;
    date = new QToolButton;
    blur = new QToolButton;
    rainbow = new QToolButton;
    snow = new QToolButton;
    sparkles = new QToolButton;
    redNose = new QToolButton;
    square_on_face = new QToolButton;

    original->setIcon(QIcon(":Icons/original.jpg"));
    original->setIconSize(QSize(80, 80));
    original->setAutoRaise(true);
    original->setToolTip("No Filter");
    original->setStyleSheet("QToolButton { border: none; }");

    black_and_white->setIcon(QIcon(":Icons/black_and_white.jpg"));
    black_and_white->setIconSize(QSize(80, 80));
    black_and_white->setAutoRaise(true);
    black_and_white->setToolTip("Black And White");
    black_and_white->setStyleSheet("QToolButton { border: none; }");

    sand->setIcon(QIcon(":Icons/sand.jpg"));
    sand->setIconSize(QSize(80, 80));
    sand->setAutoRaise(true);
    sand->setToolTip("Sand");
    sand->setStyleSheet("QToolButton { border: none; }");

    blur->setIcon(QIcon(":Icons/blur.jpg"));
    blur->setIconSize(QSize(80, 80));
    blur->setAutoRaise(true);
    blur->setToolTip("Blur Effect");
    blur->setStyleSheet("QToolButton { border: none; }");

    rain->setIcon(QIcon(":Icons/rain.jpg"));
    rain->setIconSize(QSize(80, 80));
    rain->setAutoRaise(true);
    rain->setToolTip("Rain");
    rain->setStyleSheet("QToolButton { border: none; }");

    hands->setIcon(QIcon(":Icons/hands.jpg"));
    hands->setIconSize(QSize(80, 80));
    hands->setAutoRaise(true);
    hands->setToolTip("Hands");
    hands->setStyleSheet("QToolButton { border: none; }");
        
    date->setIcon(QIcon(":Icons/date.jpg"));
    date->setIconSize(QSize(80, 80));
    date->setAutoRaise(true);
    date->setToolTip("Date and Time");
    date->setStyleSheet("QToolButton { border: none; }");

    rainbow->setIcon(QIcon(":Icons/rainbow.jpg"));
    rainbow->setIconSize(QSize(80, 80));
    rainbow->setAutoRaise(true);
    rainbow->setToolTip("Rainbow");
    rainbow->setStyleSheet("QToolButton { border: none; }");

    snow->setIcon(QIcon(":Icons/snow.jpg"));
    snow->setIconSize(QSize(80, 80));
    snow->setAutoRaise(true);
    snow->setToolTip("Snow");
    snow->setStyleSheet("QToolButton { border: none; }");

    sparkles->setIcon(QIcon(":Icons/sparkles.jpg"));
    sparkles->setIconSize(QSize(80, 80));
    sparkles->setAutoRaise(true);
    sparkles->setToolTip("Sparkles");
    sparkles->setStyleSheet("QToolButton { border: none; }");

    redNose->setIcon(QIcon(":Icons/redNose.jpg"));
    redNose->setIconSize(QSize(80, 80));
    redNose->setAutoRaise(true);
    redNose->setToolTip("Clown");
    redNose->setStyleSheet("QToolButton { border: none; }");

    square_on_face->setIcon(QIcon(":Icons/square_on_face.png"));
    square_on_face->setIconSize(QSize(80, 80));
    square_on_face->setAutoRaise(true);
    square_on_face->setToolTip("Face detection");
    square_on_face->setStyleSheet("QToolButton { border: none; }");
    
    //tools
    zoomIn = new QToolButton;
    zoomOut = new QToolButton;
    rotate_left = new QToolButton;
    rotate_right = new QToolButton;
    paint = new QToolButton;
    erase = new QToolButton;
    color = new QToolButton;
    size_plus = new QToolButton;
    size_minus = new QToolButton;
    wheel = new QToolButton;
    save = new QToolButton;

    //go back to home page button
    fromFilterback_button = new QToolButton;

    scene = new CustomGraphicsScene;
    view = new QGraphicsView(scene);

    fromFilterback_button->setIcon(QIcon(":Icons/home.png"));
    fromFilterback_button->setIconSize(QSize(30, 30));
    fromFilterback_button->setAutoRaise(true);
    fromFilterback_button->setToolTip("Home Page");
    fromFilterback_button->setStyleSheet("QToolButton { border: none; }");

    zoomIn->setIcon(QIcon(":Icons/zoomIn.png"));
    zoomIn->setIconSize(QSize(30, 30));
    zoomIn->setAutoRaise(true);
    zoomIn->setToolTip("Zoom In");
    zoomIn->setStyleSheet("QToolButton { border: none; }");

    zoomOut->setIcon(QIcon(":Icons/zoomOut.jpg"));
    zoomOut->setIconSize(QSize(30, 30));
    zoomOut->setAutoRaise(true);
    zoomOut->setToolTip("Zoom Out");
    zoomOut->setStyleSheet("QToolButton { border: none; }");

    rotate_left->setIcon(QIcon(":Icons/rotateLeft.png"));
    rotate_left->setIconSize(QSize(30, 30));
    rotate_left->setAutoRaise(true);
    rotate_left->setToolTip("Rotate Left");
    rotate_left->setStyleSheet("QToolButton { border: none; }");

    rotate_right->setIcon(QIcon(":Icons/rotateRight.png"));
    rotate_right->setIconSize(QSize(30, 30));
    rotate_right->setAutoRaise(true);
    rotate_right->setToolTip("Rotate Right");
    rotate_right->setStyleSheet("QToolButton { border: none; }");

    paint->setIcon(QIcon(":Icons/color-palette.png"));
    paint->setIconSize(QSize(30, 30));
    paint->setAutoRaise(true);
    paint->setToolTip("Paint");
    paint->setStyleSheet("QToolButton { border: none; }");

    erase->setIcon(QIcon(":Icons/rubber.png"));
    erase->setIconSize(QSize(30, 30));
    erase->setAutoRaise(true);
    erase->setToolTip("Rubber");
    erase->setStyleSheet("QToolButton { border: none; }");

    color->setIcon(QIcon(":Icons/paint.jpg"));
    color->setIconSize(QSize(30, 30));
    color->setAutoRaise(true);
    color->setToolTip("Colors");
    color->setStyleSheet("QToolButton { border: none; }");

    size_plus->setIcon(QIcon(":Icons/plus.png"));
    size_plus->setIconSize(QSize(30, 30));
    size_plus->setAutoRaise(true);
    size_plus->setToolTip("Increase The Size Of Brush");
    size_plus->setStyleSheet("QToolButton { border: none; }");

    size_minus->setIcon(QIcon(":Icons/minus.png"));
    size_minus->setIconSize(QSize(30, 30));
    size_minus->setAutoRaise(true);
    size_minus->setToolTip("Decrease The Size Of Brush");
    size_minus->setStyleSheet("QToolButton { border: none; }");

    wheel->setIcon(QIcon(":Icons/wheel.png"));
    wheel->setIconSize(QSize(30, 30));
    wheel->setAutoRaise(true);
    wheel->setToolTip("Choose Colors");
    wheel->setStyleSheet("QToolButton { border: none; }");

    save->setIcon(QIcon(":Icons/disk.png"));
    save->setIconSize(QSize(30, 30));
    save->setAutoRaise(true);
    save->setToolTip("Save");
    save->setStyleSheet("QToolButton { border: none; }");

    hlay->addWidget(original);
    hlay->addWidget(black_and_white);
    hlay->addWidget(sand);
    hlay->addWidget(blur);
    hlay->addWidget(rain);
    hlay->addWidget(hands);
    hlay->addWidget(date);
    hlay->addWidget(rainbow);
    hlay->addWidget(snow);
    hlay->addWidget(sparkles);
    hlay->addWidget(redNose);
    hlay->addWidget(square_on_face);

    vlay1->addWidget(view);

    vlay2->addWidget(fromFilterback_button,1);
    vlay2->addWidget(save,2);
    vlay2->addWidget(zoomIn,3);
    vlay2->addWidget(zoomOut,4);
    vlay2->addWidget(rotate_left,5);
    vlay2->addWidget(rotate_right,6);
    vlay2->addWidget(paint,7);

    main_hlay->addLayout(vlay1);
    main_hlay->addLayout(vlay2);
    main_vlay->addLayout(main_hlay);
    main_vlay->addLayout(hlay);
    setLayout(main_vlay);

    //connections for tools
    connect(zoomIn,&QToolButton::clicked,this,&FilterWidget::slotZoomin);
    connect(zoomOut,&QToolButton::clicked,this,&FilterWidget::slotZoomout);
    connect(rotate_right,&QToolButton::clicked,this,&FilterWidget::slotRotateRight);
    connect(rotate_left,&QToolButton::clicked,this,&FilterWidget::slotRotateLeft);
    connect(save,&QToolButton::clicked,this,&FilterWidget::saveImages);

    //connections for filter buttons
    connect(original,&QToolButton::clicked,this,[this](){
        scene->clear();
        originalPic=originalPic.scaled(QSize(1000, 1000), Qt::KeepAspectRatio);
        pixmap = originalPic;
        prev=pixmap;
        scene->addPixmap(originalPic);
        });
    connect(black_and_white,&QToolButton::clicked,this,[this](){
        scene->clear();
        Image img=QImageToImage(originalPic.toImage());
        makeGray(img);
        QImage qimg = ImageToQImage(img).scaled(QSize(1000, 1000), Qt::KeepAspectRatio);
        pixmap=QPixmap::fromImage(qimg);
        prev=pixmap;
        scene->addPixmap(pixmap);
        });
    connect(sand,&QToolButton::clicked,this,[this](){
        scene->clear();
        Image img=QImageToImage(originalPic.toImage());
        Grain(img);
        QImage qimg = ImageToQImage(img).scaled(QSize(1000, 1000), Qt::KeepAspectRatio);
        pixmap=QPixmap::fromImage(qimg);
        prev=pixmap;
        scene->addPixmap(pixmap);
        });
    connect(rain,&QToolButton::clicked,this,[this](){
        scene->clear();
        Image img=QImageToImage(originalPic.toImage());
        _add_rain(img);
        QImage qimg = ImageToQImage(img).scaled(QSize(1000, 1000), Qt::KeepAspectRatio);
        pixmap=QPixmap::fromImage(qimg);
        prev=pixmap;
        scene->addPixmap(pixmap);
        });
    connect(hands,&QToolButton::clicked,this,[this](){
        scene->clear();
        Image img=QImageToImage(originalPic.toImage());
        _AdamHands(img);
        QImage qimg = ImageToQImage(img).scaled(QSize(1000, 1000), Qt::KeepAspectRatio);
        pixmap=QPixmap::fromImage(qimg);
        prev=pixmap;
        scene->addPixmap(pixmap);
        });
    connect(date,&QToolButton::clicked,this,[this](){
        scene->clear();
        Image img=QImageToImage(originalPic.toImage());
        date_and_time(img);
        QImage qimg = ImageToQImage(img).scaled(QSize(1000, 1000), Qt::KeepAspectRatio);
        pixmap=QPixmap::fromImage(qimg);
        prev=pixmap;
        scene->addPixmap(pixmap);
        });
    connect(blur,&QToolButton::clicked,this,[this](){
        scene->clear();
        Image img=QImageToImage(originalPic.toImage());
        blurImage(img);
        QImage qimg = ImageToQImage(img).scaled(QSize(1000, 1000), Qt::KeepAspectRatio);
        pixmap=QPixmap::fromImage(qimg);
        prev=pixmap;
        scene->addPixmap(pixmap);
        });
    connect(rainbow,&QToolButton::clicked,this,[this](){
        scene->clear();
        Image img=QImageToImage(originalPic.toImage());
        five_filters(img);
        QImage qimg = ImageToQImage(img).scaled(QSize(1000, 1000), Qt::KeepAspectRatio);
        pixmap=QPixmap::fromImage(qimg);
        prev=pixmap;
        scene->addPixmap(pixmap);
        });
    connect(snow,&QToolButton::clicked,this,[this](){
        scene->clear();
        Image img=QImageToImage(originalPic.toImage());
        _add_snow(img);
        QImage qimg = ImageToQImage(img).scaled(QSize(1000, 1000), Qt::KeepAspectRatio);
        pixmap=QPixmap::fromImage(qimg);
        prev=pixmap;
        scene->addPixmap(pixmap);
        });
    connect(sparkles,&QToolButton::clicked,this,[this](){
        scene->clear();
        Image img=QImageToImage(originalPic.toImage());
        _add_sparkles(img);
        QImage qimg = ImageToQImage(img).scaled(QSize(1000, 1000), Qt::KeepAspectRatio);
        pixmap=QPixmap::fromImage(qimg);
        prev=pixmap;
        scene->addPixmap(pixmap);
        });
    connect(redNose,&QToolButton::clicked,this,[this](){
        scene->clear();
        Image img=QImageToImage(originalPic.toImage());
        clown(img);
        QImage qimg = ImageToQImage(img).scaled(QSize(1000, 1000), Qt::KeepAspectRatio);
        pixmap=QPixmap::fromImage(qimg);
        prev=pixmap;
        scene->addPixmap(pixmap);
        });
    connect(square_on_face,&QToolButton::clicked,this,[this](){
        scene->clear();
        Image img=QImageToImage(originalPic.toImage());
        detectFace(img);
        QImage qimg = ImageToQImage(img).scaled(QSize(1000, 1000), Qt::KeepAspectRatio);
        pixmap=QPixmap::fromImage(qimg);
        prev=pixmap;
        scene->addPixmap(pixmap);
        });

    //connections for paint
    connect(paint,&QToolButton::clicked,this,[this](){
        if(is_button_active == false){
            prev=pixmap;
            erase = new QToolButton;
            color = new QToolButton;
            size_plus = new QToolButton;
            size_minus = new QToolButton;
            wheel = new QToolButton;
            erase->setIcon(QIcon(":Icons/rubber.png"));
            erase->setIconSize(QSize(30, 30));
            erase->setAutoRaise(true);
            erase->setToolTip("Rubber");
            erase->setStyleSheet("QToolButton { border: none; }");

            color->setIcon(QIcon(":Icons/paint.jpg"));
            color->setIconSize(QSize(30, 30));
            color->setAutoRaise(true);
            color->setToolTip("Brush");
            color->setStyleSheet("QToolButton { border: none; }");

            size_plus->setIcon(QIcon(":Icons/plus.png"));
            size_plus->setIconSize(QSize(30, 30));
            size_plus->setAutoRaise(true);
            size_plus->setToolTip("Increase the size");
            size_plus->setStyleSheet("QToolButton { border: none; }");

            size_minus->setIcon(QIcon(":Icons/minus.png"));
            size_minus->setIconSize(QSize(30, 30));
            size_minus->setAutoRaise(true);
            size_minus->setToolTip("Decrease the size");
            size_minus->setStyleSheet("QToolButton { border: none; }");

            wheel->setIcon(QIcon(":Icons/wheel.png"));
            wheel->setIconSize(QSize(30, 30));
            wheel->setAutoRaise(true);
            wheel->setToolTip("Choose Colors");
            wheel->setStyleSheet("QToolButton { border: none; }");

            vlay2->addWidget(color,8);
            vlay2->addWidget(erase,9);
            vlay2->addWidget(wheel,10);
            vlay2->addWidget(size_plus,11);
            vlay2->addWidget(size_minus,12);
            is_button_active = true;
            connect(color,&QToolButton::clicked,this,[this](){
                if(is_brush_active)
                {
                    scene->is_active = false;
                    is_brush_active=false;
                    cursor.setShape(Qt::ArrowCursor);      
                    setCursor(cursor);
                }
                else
                {
                    scene->is_active = true;
                    is_brush_active=true;
                    cursor.setShape(Qt::CrossCursor);
                    setCursor(cursor);
                }
            });
            connect(wheel,SIGNAL(clicked()),this,SLOT(changeColor()));
            connect(size_plus,SIGNAL(clicked()),this,SLOT(setPenSizeBig()));
            connect(size_minus,SIGNAL(clicked()),this,SLOT(setPenSizeSmall()));
            connect(erase,SIGNAL(clicked()),this,SLOT(clearDrawing()));
        }
        else{
            delete erase;
            delete color;
            delete wheel;
            delete size_plus;
            delete size_minus;
            is_button_active = false;
            scene->is_active = false;
            is_brush_active=false;
            cursor.setShape(Qt::ArrowCursor);      
            setCursor(cursor);
        }
    });

}

//save image slot
void FilterWidget::saveImages(){
    // Get the path where the images will be saved
    QString path = QFileDialog::getExistingDirectory(this, tr("Save Images"));
    // Loop through the QGraphicsScene and get each QPixmap
    foreach (QGraphicsItem* item, scene->items()) {
        if (item->type() == QGraphicsPixmapItem::Type) {
            QGraphicsPixmapItem* pixmapItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
            QPixmap pixmap = pixmapItem->pixmap();

            // Use the QPixmap::save() function to save each image to the file system with a unique name
            QString fileName = QString("%1/image_%2.png").arg(path).arg(QDateTime::currentDateTime().toString("yyyyMMdd-hhmmsszzz").replace(":", "_"));
            pixmap.save(fileName);
        }
    }
}

void FilterWidget::slotZoomin()
{
    view->scale(1.1,1.1);
}

void FilterWidget::slotZoomout()
{
    view->scale(1/1.1,1/1.1);
}

void FilterWidget::slotRotateLeft()
{
    QTransform transform;
    transform.rotate(-90); // Rotate by 90 degrees
    pixmap = pixmap.transformed(transform, Qt::SmoothTransformation);
    scene->clear();
    scene->addPixmap(pixmap);
}

void FilterWidget::slotRotateRight()
{
    QTransform transform;
    transform.rotate(90); // Rotate by 90 degrees
    pixmap = pixmap.transformed(transform, Qt::SmoothTransformation);
    scene->clear();
    scene->addPixmap(pixmap);
}

//set image on filterswidget graphicsview
void FilterWidget::setImage(QString path)
{
    pixmap= QPixmap(path);
    originalPic = pixmap.scaled(QSize(1000, 1000), Qt::KeepAspectRatio);
    pixmap=originalPic;
    scene = new CustomGraphicsScene;
    scene->addPixmap(pixmap);
    view = new QGraphicsView(scene);
    vlay1->addWidget(view);
    scene->setPixmap(pixmap,currentColor,penSize);
}

//set image took on camera on filters widget graphicsview
void FilterWidget::setCamImage(const QPixmap* p)
{
    scene = new CustomGraphicsScene;
    pixmap=(*p).scaled(QSize(1000, 1000), Qt::KeepAspectRatio);
    scene->addPixmap(pixmap);
    view = new QGraphicsView(scene);
    vlay1->addWidget(view);
    scene->setPixmap(pixmap,currentColor,penSize);
}

//change color of paint brush 
void FilterWidget::changeColor() {
        QColorDialog colorDialog(this);
        QColor newColor = colorDialog.getColor(currentColor);
        if (newColor.isValid()) {
            currentColor = newColor; // Update currentColor with the chosen color
        }
    }

//clear drwaings from  picture
void FilterWidget::clearDrawing() {
        scene->clear();
        pixmap=prev;
        scene->addPixmap(prev);
    }

void FilterWidget::setPenSizeBig() {
        penSize++; // Update penSize with the chosen pen size
    }

void FilterWidget::setPenSizeSmall() {
        penSize--; // Update penSize with the chosen pen size
    }




