#include "ImageToQImage.h"
#include "Camera.h"

CameraWidget::CameraWidget(QWidget *parent)
    : QWidget(parent)
{
    cam.startCamera();
    timerId = startTimer(30); // start timer to capture frames

    m_label = new QLabel(this);
    m_label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_label->setAlignment(Qt::AlignCenter);
        
    //a layout to position the label and button
    QHBoxLayout *camLay = new QHBoxLayout;
    QVBoxLayout *layout = new QVBoxLayout(this);
    camLay->addWidget(m_label);

    original = new QToolButton;
    black_and_white = new QToolButton;
    sand = new QToolButton;
    rain = new QToolButton;
    hands = new QToolButton;
    date = new QToolButton;
    rainbow = new QToolButton;
    snow = new QToolButton;
    sparkles = new QToolButton;
    blur = new QToolButton;

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

    blur->setIcon(QIcon(":Icons/blur.jpg"));
    blur->setIconSize(QSize(80, 80));
    blur->setAutoRaise(true);
    blur->setToolTip("Blur Effect");
    blur->setStyleSheet("QToolButton { border: none; }");

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

    QHBoxLayout *filtersLay=new QHBoxLayout(this);

    filtersLay->addWidget(original);
    filtersLay->addWidget(black_and_white);
    filtersLay->addWidget(sand);
    filtersLay->addWidget(blur);
    filtersLay->addWidget(rain);
    filtersLay->addWidget(hands);
    filtersLay->addWidget(date);
    filtersLay->addWidget(rainbow);
    filtersLay->addWidget(snow);
    filtersLay->addWidget(sparkles);
    layout->addLayout(camLay);
    layout->addLayout(filtersLay);

    goToPhotos_button = new QToolButton;
    goToFilter_button = new QToolButton;

    goToPhotos_button->setIcon(QIcon(":Icons/add_picT.jpg"));
    goToPhotos_button->setIconSize(QSize(30, 30));
    goToPhotos_button->setAutoRaise(true);
    goToPhotos_button->setToolTip("Add Picture");
    goToPhotos_button->setStyleSheet("QToolButton { border: none; }");

    goToFilter_button->setIcon(QIcon(":Icons/camera_t.png"));
    goToFilter_button->setIconSize(QSize(30, 30));
    goToFilter_button->setAutoRaise(true);
    goToFilter_button->setToolTip("Capture");
    goToFilter_button->setStyleSheet("QToolButton { border: none; }");
    
    filtersLay->addWidget(goToFilter_button);
    filtersLay->addWidget(goToPhotos_button);

    //connecting filters to the filter buttons
    connect(original,&QToolButton::clicked,this,[this](){filterNumber=0;});
    connect(sand,&QToolButton::clicked,this,[this](){filterNumber=1;});
    connect(black_and_white,&QToolButton::clicked,this,[this](){filterNumber=2;});
    connect(rain,&QToolButton::clicked,this,[this](){filterNumber=3;});
    connect(hands,&QToolButton::clicked,this,[this](){filterNumber=4;});
    connect(date,&QToolButton::clicked,this,[this](){filterNumber=5;});
    connect(blur,&QToolButton::clicked,this,[this](){filterNumber=6;});
    connect(rainbow,&QToolButton::clicked,this,[this](){filterNumber=7;});
    connect(snow,&QToolButton::clicked,this,[this](){filterNumber=8;});
    connect(sparkles,&QToolButton::clicked,this,[this](){filterNumber=9;});

    setLayout(layout);

}

CameraWidget::~CameraWidget() 
{
    cam.endCamera(); // release the camera
}

void CameraWidget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timerId)
    {
        QImage image = ImageToQImage(cam.captureImage(filterNumber)).scaled(QSize(1000, 1000), Qt::KeepAspectRatio);
        m_label->setPixmap(QPixmap::fromImage(image));
    }
}



