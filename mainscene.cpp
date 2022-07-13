#include "mainscene.h"
#include "./ui_mainscene.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QSoundEffect>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    // 配置主场景

    // 设置固定大小
    this->setFixedSize(320, 588);

    // 设置图标
    this->setWindowIcon(QIcon(":/resource/Coin0001.png"));

    // 设置标题
    this->setWindowTitle("翻金币主场景");

    connect(ui->actionopen, &QAction::triggered, [=](){
        this->close();
    });

    // 准备开始按钮的音效
    QSoundEffect * startSound = new QSoundEffect(this);
    startSound->setSource(QUrl::fromLocalFile(":/resource/TapButtonSound.wav"));


    // 开始按钮
    MyPushButton * startBtn = new MyPushButton(":/resource/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5, this->height() * 0.7);

    // 实例化选择关卡场景
    chooseScene = new ChooseLevelSence;

    // 监听选择关卡的返回按钮的信号
    connect(chooseScene, &ChooseLevelSence::chooseSceneBack, this, [=]() {
        // 将选择关卡场景 隐藏掉
        chooseScene->hide();
        // 重新显示主场景
        this->show();
    });

    connect(startBtn, &MyPushButton::clicked, [=](){
        // 播放开始音效资源
        startSound->play();

        startBtn->zoomDown();
        startBtn->zoomUp();

        //延时进入到选择关卡场景中
        QTimer::singleShot(300, this, [=](){
            // 进入选择关卡场景中
            chooseScene->show();
            // 自身隐藏
            this->hide();
        });
    });
}

void MainScene::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap pix;

    pix.load(":/resource/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0, this->width(), this->height(), pix);

    // 画背景上图标
    pix.load(":/resource/Title.png");
    pix = pix.scaled(pix.width() *0.5, pix.height() * 0.5);
    painter.drawPixmap(10, 30, pix);
}

MainScene::~MainScene()
{
    delete ui;
}

