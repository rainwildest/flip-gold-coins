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
            if(this->gameArray[i][j] == 1) {
                coinImage = ":/resource/Coin0001.png";
            } else {
                coinImage = ":/resource/Coin0008.png";
            }

            // 创建金币
            MyCoin * coin = new MyCoin(coinImage);
            coin->setParent(this);
            coin->move(62 + i * 50, 203 + j * 50);

            // 给金币的属性赋值
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j]; // 0 反面 1 正面

            coinBtn[i][j] = coin;

            // 点击金币 进行翻转
            connect(coin, &MyCoin::clicked, [=]() {
                coin->changeFlag();
                this->gameArray[i][j] = this->gameArray[j][j] == 0 ? 1 : 0;

                QTimer::singleShot(300, this, [=]() {
                    // 翻转周围硬币
                    if(coin->posX + 1 <= 3) {
                        // 周围的右侧金币翻转的条件
                        coinBtn[coin->posX + 1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX + 1][coin->posY] = this->gameArray[coin->posX + 1][coin->posY] == 0 ? 1 : 0;
                    }

                    if(coin->posX - 1 >= 0) {
                        // 周围的左侧金币翻转的条件
                        coinBtn[coin->posX - 1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX - 1][coin->posY] = this->gameArray[coin->posX - 1][coin->posY] == 0 ? 1 : 0;
                    }

                    if(coin->posY + 1 <= 3){
                        // 周围的上侧金币翻转的条件
                        coinBtn[coin->posX][coin->posY + 1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY + 1] = this->gameArray[coin->posX][coin->posY + 1] == 0 ? 1 : 0;
                    }

                    if(coin->posY - 1 >= 0){
                        // 周围的下侧金币翻转的条件
                        coinBtn[coin->posX][coin->posY - 1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY - 1] = this->gameArray[coin->posX][coin->posY - 1] == 0 ? 1 : 0;
                    }

                    // 判断是否胜利
                    this->isWin = true;
                    for(int i = 0; i < 4; ++i) {
                        for(int j = 0; j < 4; ++j) {
                            if(coinBtn[i][j]->flag == false) {
                                // 只要有一个是反面 就算失败
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if(this->isWin == true) {
                        qDebug() << "胜利了";
                        // 将所有按钮的胜利标志改为 true
                        for(int i = 0; i < 4; ++i) {
                            for(int j = 0; j < 4; ++j) {
                                coinBtn[i][j]->isWin = true;
                            }
                        }
                    }
                });
            });
        }
    }
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
