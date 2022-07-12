#include "mycoin.h"
#include <QDebug>

//MyCoin::MyCoin(QWidget *parent)
//    : QPushButton{parent}
//{

//}
MyCoin::MyCoin(QString btnImg) {
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret) {
        QString str = QString("图片 %1 加载失败").arg(btnImg);
        qDebug() << str;

        return;
    }

    this->setFixedSize(pix.width(), pix.height());
    this->setStyleSheet("QPushButton{border: 0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    // 初始化定时器对象
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    connect(timer1, &QTimer::timeout, [=]() {
        QPixmap pix;
        QString str = QString(":/resource/Coin000%1").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border: 0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));

        // 判断 是否翻完了
        if(this->min > this->max) {
            this->min = 1;
            timer1->stop();
            this->isAnimetion = false;
        }
    });

    // 监听反面翻正面的信号，并且翻转金币
    connect(timer2, &QTimer::timeout, [=]() {
        QPixmap pix;
        QString str = QString(":/resource/Coin000%1").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border: 0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));

        // 判断 是否翻完了
        if(this->max < this->min) {
            this->max = 8;
            timer2->stop();
            this->isAnimetion = false;
        }
    });
}

void MyCoin::mousePressEvent(QMouseEvent *e) {
    if(this->isAnimetion || this->isWin) return;

    return QPushButton::mousePressEvent(e);
}

// 改变正反面标志的方法
void MyCoin::changeFlag(){
    if(this->flag) {
        // 正面翻反面
        timer1->start(this->millisecond);
        this->flag = false;
        this->isAnimetion = true;
    } else {
        // 反面翻正面
        timer2->start(this->millisecond);
        this->flag = true;
        this->isAnimetion = true;
    }
}
