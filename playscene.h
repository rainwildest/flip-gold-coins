#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(int level = 0);

    //内部成员属性 记录所选的关卡
    int levelIndex;

    // 重写绘图事件
    void paintEvent(QPaintEvent *);

    // 二维数组 维护每个关卡的具体数据
    int gameArray[4][4];
signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H
