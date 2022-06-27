#include "mainscene.h"
#include "./ui_mainscene.h"
#include <QPainter>
#include "mypushbutton.h"

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

    // 开始按钮
    MyPushButton * startBtn = new MyPushButton(":/resource/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5, this->height() * 0.7);

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

