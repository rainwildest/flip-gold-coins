#include "playscene.h"
#include <QMenuBar>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include "mypushbutton.h"
#include "mycoin.h"
#include "dataconfig.h"

//PlayScene::PlayScene(QWidget *parent)
//    : QMainWindow{parent}
//{

//}

PlayScene::PlayScene(int level) {
    this->levelIndex = level;
    QString str = QString("进入第 %1 关").arg(level);
    qDebug() << str;

    // 配置选择关卡场景
    this->setFixedSize(320, 588);

    // 设置图标
    this->setWindowIcon(QPixmap(":/resource/Coin0001.png"));

    // 设置标题
    this->setWindowTitle("翻金币场景");

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
        qDebug() << "翻金币的场景中，点击了返回按钮";

        QTimer::singleShot(300, this, [=]() {
            emit this->chooseSceneBack();
        });
    });

    // 显示当前关卡数
    QLabel * label = new QLabel();
    label->setParent(this);

    QString levelStr = QString("Level: %1").arg(this->levelIndex);

    // 设置字体
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);

    label->setFont(font);
    label->setText(levelStr);
    label->setGeometry(10, this->height() - 45, 120, 50);



    dataConfig config;
    // 初始化每个关卡的二维数组
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    // 显示金币背景图案
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            // 绘制背景图片
            QPixmap pix = QPixmap(":/resource/BoardNode.png");
            QLabel * label = new QLabel;

            label->setGeometry(0,0, pix.width(), pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(60+ i * 50, 200 + j * 50);

            QString coinImage;
            if(this->gameArray[i][j]==1) {
                coinImage = ":/resource/Coin0001.png";
            } else {
                coinImage = ":/resource/Coin0008.png";
            }

            // 创建金币
            MyCoin * coin = new MyCoin(coinImage);
            coin->setParent(this);
            coin->move(62 + i * 50, 203 + j * 50);
        }
    }

//    for(int i = 0; i < 16; i++) {
//        QPixmap pix = QPixmap(":/resource/BoardNode.png");
//        QLabel * label = new QLabel;
//        label->setGeometry(0,0, pix.width(), pix.height());
//        label->setPixmap(pix);
//        label->setParent(this);
//        label->move(60 + i % 4 * 50, 200 + i/4 * 50);

//        // 创建金币
//        MyCoin * coin = new MyCoin(":/resource/Coin0001.png");
//        coin->setParent(this);
//        coin->move(62 + i % 4 * 50, 203 + i/4 * 50);
//    }
}


void PlayScene::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap pix;

    pix.load(":/resource/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0, this->width(), this->height(), pix);

    // 画背景上图标
    pix.load(":/resource/Title.png");
    pix = pix.scaled(pix.width() *0.5, pix.height() * 0.5);
    painter.drawPixmap(10, 30, pix);
}
