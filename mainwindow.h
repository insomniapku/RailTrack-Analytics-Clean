#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QVector>
#include <QPixmap>
#include <QDir>
#include "core/Statistics.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onGenerateReport();
    void on_addTripButton_clicked();
    void on_clearTripsButton_clicked();
    void resizeEvent(QResizeEvent* event) override;
    void onAnimationFrameTimeout();
    void startMainInterface();

private:
    Ui::MainWindow *ui;
    Statistics stats;
    // 动画相关成员
    QLabel* animationLabel;         // 动画显示标签
    QTimer* frameTimer;             // 帧切换定时器
    QVector<QPixmap> animationFrames; // 动画帧集合
    int currentFrame;               // 当前帧索引
    bool isPlayingAnimation;        // 动画播放状态

    void loadAnimationFrames();     // 加载动画帧
    void startAnimation();          // 开始播放动画
    void initializeData();  // 初始化数据
    // 添加成员函数与变量
    void loadRailwayOverlays(); // 加载所有铁路点亮图层
    void updateRailwayMap();    // 根据用户行程更新地图

    QMap<QString, QPixmap> railwayOverlays;

};

#endif // MAINWINDOW_H
