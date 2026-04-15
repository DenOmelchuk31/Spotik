#include "homewidget.h"
#include "ui_homewidget.h"

HomeWidget::HomeWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HomeWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("background-color: #FF4B5C;");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    QLabel *icon = new QLabel(this);
    QPixmap pixmap(":/icons/music.png"); // якщо в іншій папці — зміни шлях
    icon->setPixmap(pixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    icon->setAlignment(Qt::AlignCenter);

    layout->addWidget(icon);
    QPushButton *trialBtn = new QPushButton("Get free trial", this);
    trialBtn->setStyleSheet(
        "background-color: white;"
        "color: black;"
        "border-radius: 20px;"
        "padding: 10px 30px;"
        "font-size: 16px;"
        "font-weight: bold;"
        );
    trialBtn->setCursor(Qt::PointingHandCursor);
    layout->addWidget(trialBtn, 0, Qt::AlignCenter);
    setLayout(layout);
}

HomeWidget::~HomeWidget()
{
    delete ui;
}
