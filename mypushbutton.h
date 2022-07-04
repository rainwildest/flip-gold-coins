#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton(QString normalImg, QString pressImg="");

    QString normalImgPath;
    QString pressImgPath;

    // 弹跳效果
    void zoomDown(); // 向下跳
    void zoomUp(); // 向上跳
signals:

};

#endif // MYPUSHBUTTON_H
