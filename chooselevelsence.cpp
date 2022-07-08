#include "chooselevelsence.h"
#include <QMenuBar>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include "mypushbutton.h"

ChooseLevelSence::ChooseLevelSence(QWidget *parent)
    : QMainWindow{parent}
{
    // 配置选择关卡场景
    this->setFixedSize(320, 588);

    // 设置图标
    this->setWindowIcon(QPixmap(":/resource/Coin0001.png"));

    // 设置标题
    this->setWindowTitle("选择关卡场景");

    // 创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    // 创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");

    // 创建退出 菜单项
    QAction * quitAction = startMenu->addAction("退出");

    // 点击退出，实现退出游戏
    connect(quitAction, &QAction::triggered, [=]() {
        this->close();
    });

    // 返回按钮
    MyPushButton * backBtn = new MyPushButton(":/resource/BackButton.png", ":resource/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width() - 5, this->height() - backBtn->height() - 5);

    // 点击返回
    connect(backBtn, &MyPushButton::clicked, [=]() {
        qDebug() << "点击了返回按钮";

        QTimer::singleShot(500, this, [=]() {
            emit this->chooseSceneBack();
        });
    });


    // 创建选择关卡的按钮
    for(int i = 0; i < 20; i++) {
        MyPushButton * menuBtn = new MyPushButton(":/resource/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25 + i % 4 * 70, 130 + i / 4 * 70);

        // 监听每个按钮的点击事件
        connect(menuBtn, &MyPushButton::clicked, [=]() {
            QString str = QString("您选择的是第%1关 ").arg(i + 1);
            qDebug() << str;
        });

        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        label->setText(QString::number(i + 1));
        label->move(25 + i % 4 * 70, 130 + i / 4 * 70);

        // 设置 label 上的文字对齐方式
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        // 设置让鼠标进行穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelSence::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap pix;

//    qDebug() << "进来了...";

    pix.load(":/resource/OtherSceneBg.png");
    painter.drawPixmap(0,0, this->width(), this->height(), pix);

    // 画背景上图标
    pix.load(":/resource/Title.png");
    painter.drawPixmap((this->width() - pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);

}
