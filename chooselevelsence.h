#ifndef CHOOSELEVELSENCE_H
#define CHOOSELEVELSENCE_H

#include <QMainWindow>

class ChooseLevelSence : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelSence(QWidget *parent = nullptr);

    // 重写绘图事件
    void paintEvent(QPaintEvent *);
signals:
    // 写一个自定义信号 告诉主场景 点击了返回
    void chooseSceneBack();
};

#endif // CHOOSELEVELSENCE_H
