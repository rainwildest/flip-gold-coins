#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyCoin(QWidget *parent = nullptr);
    // 参数代表 传入的金币路径还是银币路径
    MyCoin(QString btnImg);

    //金币的属性
    int posX; // X坐标位置
    int posY; // Y坐标位置

    bool flag; // 正反标示

    // 改变标志的方法
    void changeFlag();
    QTimer *timer1;
    QTimer *timer2;
    int min = 1;
    int max = 8;

    int millisecond = 40;

    // 执行动画 标志
    bool isAnimetion = false;

    // 重写 按下
    void mousePressEvent(QMouseEvent *);

    // 是否胜利的标志
    bool isWin;
signals:

};

#endif // MYCOIN_H
