#include "mainwindow.h"
#include "addtripdialog.h"
#include "ui_mainwindow.h"
#include "addtripdialog.h"
#include <QMessageBox>
#include <sstream>
//#include<iomanip>
#include<iostream>
#include <QPalette>
#include <QPixmap>
#include <QPainter>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentFrame(0),
    isPlayingAnimation(true)
{

    resize(1037, 720);
    // 创建动画标签并设置属性
    animationLabel = new QLabel(this);
    animationLabel->setStyleSheet("background-color: black;");
    animationLabel->setAlignment(Qt::AlignCenter);
    animationLabel->setGeometry(0, 0, width(), height());
    animationLabel->raise(); // 显示在顶层
    animationLabel->show();  // 确保标签可见

    // 初始化定时器
    frameTimer = new QTimer(this);
    connect(frameTimer, &QTimer::timeout, this, &MainWindow::onAnimationFrameTimeout);

    // 加载动画帧并开始播放
    loadAnimationFrames();
    if (isPlayingAnimation) {
        startAnimation();
    } else {
        // 动画加载失败，直接显示主界面
        startMainInterface();
    }
}

MainWindow::~MainWindow() {
    delete ui;
    frameTimer->stop();
}

/*void MainWindow::loadAnimationFrames() {
    animationFrames.clear();
        qDebug() << "当前运行目录:" << QCoreApplication::applicationDirPath();
    // 获取绝对路径
    QDir dir(QCoreApplication::applicationDirPath() + "/../images/begin");  // debug 目录的上级

    QStringList filters;
    filters << "frame_*.png";
    QStringList fileList = dir.entryList(filters, QDir::Files, QDir::Name);

    if (fileList.isEmpty()) {
        qDebug() << "❌ 没有找到动画帧图像";
        isPlayingAnimation = false;
        return;
    }

    fileList.sort();

    for (const QString &fileName : fileList) {
        QString path = dir.absoluteFilePath(fileName);
        QPixmap frame(path);
        if (frame.isNull()) {
            qDebug() << "⚠️ 加载失败: " << path;
        } else {
            animationFrames.append(frame);
        }
    }

    qDebug() << "✅ 成功加载帧数:" << animationFrames.size();


}*/
void MainWindow::loadAnimationFrames() {
    animationFrames.clear();
    qDebug() << "当前运行目录:" << QCoreApplication::applicationDirPath();

    // 获取绝对路径
    QDir dir(QCoreApplication::applicationDirPath() + "/../images/begin");

    QStringList filters;
    filters << "frame_*.png";
    QStringList fileList = dir.entryList(filters, QDir::Files, QDir::Name);

    if (fileList.isEmpty()) {
        qDebug() << "❌ 没有找到动画帧图像";
        isPlayingAnimation = false;
        return;
    }

    fileList.sort();

    for (const QString &fileName : fileList) {
        QString path = dir.absoluteFilePath(fileName);
        QPixmap frame(path);
        if (frame.isNull()) {
            qDebug() << "⚠️ 加载失败: " << path;
        } else {
            // ✅ 将每帧统一缩放为 800×600
            QPixmap scaledFrame = frame.scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            animationFrames.append(scaledFrame);
        }
    }

    qDebug() << "✅ 成功加载帧数:" << animationFrames.size();
}




void MainWindow::startAnimation() {
    if (!isPlayingAnimation || animationFrames.isEmpty()) {
        qDebug() << "跳过动画：状态错误或无有效帧";
        startMainInterface();
        return;
    }

    currentFrame = 0;
    animationLabel->setPixmap(animationFrames[currentFrame]);
    frameTimer->start(1000 / 10); // 10fps
    qDebug() << "动画开始播放";
}

void MainWindow::onAnimationFrameTimeout() {
    if (!isPlayingAnimation || animationFrames.isEmpty()) {
        frameTimer->stop();
        return;
    }

    currentFrame++;

    if (currentFrame < animationFrames.size()) {
        // 显示下一帧并适应窗口大小
        animationLabel->setPixmap(animationFrames[currentFrame]);
        animationLabel->setGeometry(0, 0, width(), height());
    } else {
        // 动画播放完毕，显示主界面
        frameTimer->stop();
        startMainInterface();
        qDebug() << "动画播放完毕，显示主界面";
    }

}

void MainWindow::startMainInterface() {
    // 隐藏动画标签
    animationLabel->hide();

    // 显示主界面内容（例如初始化UI控件）
    ui->setupUi(this);
    initializeData();
    connect(ui->generateReportButton, &QPushButton::clicked, this, &MainWindow::onGenerateReport);
    connect(ui->addTripButton, &QPushButton::clicked, this, &MainWindow::on_addTripButton_clicked);
    connect(ui->clearTripsButton, &QPushButton::clicked, this, &MainWindow::on_clearTripsButton_clicked);
    loadRailwayOverlays();
    QPixmap bkgnd(":/images/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
    // 注意：需确保主界面控件在动画结束后显示
    ui->centralwidget->setVisible(true);

    qDebug() << "主界面已显示";
    loadRailwayOverlays();
    updateRailwayMap(); // ✅ 首次加载地图时绘制一次

}


void MainWindow::onGenerateReport() {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    stats.runAnalysis();
    std::cout.rdbuf(old);

    QMessageBox::information(this, "年度出行报告", QString::fromStdString(buffer.str()));
}

void MainWindow::on_addTripButton_clicked() {
    qDebug() << "🚩 点击了添加行程按钮";  // 添加这一行
    AddTripDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString from = dialog.getFromCity();
        QString to = dialog.getToCity();

        std::string fromName = from.trimmed().toUtf8().constData();
        std::string toName = to.trimmed().toUtf8().constData();

        City* fromCity = stats.getCityByName(fromName);
        City* toCity = stats.getCityByName(toName);


        if (!fromCity || !toCity) {
            QMessageBox::warning(this, "添加失败", "输入的起止城市不存在！");
            return;
        }

        // 生成一个默认时间行程（例如用当前模拟时间）
        Trip trip(fromCity, toCity, Time::now(), Time::now());

        stats.addTrip(trip);
        qDebug() << "✅ 添加行程: Trip(" << QString::fromStdString(fromName) << " -> " << QString::fromStdString(toName) << ")";
        updateRailwayMap();
        QMessageBox::information(this, "添加成功", "行程已成功添加！");

    }
}

void MainWindow::on_clearTripsButton_clicked() {
    auto reply = QMessageBox::question(this, "确认清除", "是否清除所有行程？", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        stats.clearall();
        updateRailwayMap();
        QMessageBox::information(this, "清除成功", "所有行程已清除。");
    }
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    if (isPlayingAnimation) {
        animationLabel->setGeometry(0, 0, width(), height());
    }
    else{
        QPixmap bkgnd(":/images/background.jpg");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        QPalette p = this->palette();
        p.setBrush(QPalette::Window, bkgnd);
        this->setPalette(p);
    }
    QMainWindow::resizeEvent(event);
}


void MainWindow::initializeData() {
    // 提取城市名
    QStringList cityNames = {
        "北京", "大同", "沈阳", "天津", "香港", "郑州", "成都", "昆明", "呼和浩特", "洛阳",
        "广州", "长沙", "贵阳", "哈尔滨", "牡丹江", "齐齐哈尔", "杭州", "兰州", "拉萨", "乌鲁木齐",
        "桂林", "南宁", "上海", "徐州", "连云港", "西安"
    };

    // 创建城市对象
    for (const QString& name : cityNames) {
        City* city = new City(name.toStdString(), 0, 0, CityRank::MIDDLE); // 坐标设为0,0，等级为NORMAL
        stats.addCity(city);
    }

    // 铁路初始化（name, from, to）
    std::vector<std::tuple<std::string, std::string, std::string>> railwayData = {
        {"北京", "大同", "北京-大同"},
        {"北京", "沈阳", "北京-沈阳"},
        {"北京", "天津", "北京-天津"},
        {"北京", "香港", "北京-香港"},
        {"北京", "郑州", "北京-郑州"},
        {"成都", "昆明", "成都-昆明"},
        {"大同", "呼和浩特", "大同-呼和浩特"},
        {"大同", "洛阳", "大同-洛阳"},
        {"广州", "长沙", "广州-长沙"},
        {"贵阳", "长沙", "贵阳-长沙"},
        {"哈尔滨", "牡丹江", "哈尔滨-牡丹江"},
        {"哈尔滨", "齐齐哈尔", "哈尔滨-齐齐哈尔"},
        {"杭州", "长沙", "杭州-长沙"},
        {"呼和浩特", "兰州", "呼和浩特-兰州"},
        {"昆明", "贵阳", "昆明-贵阳"},
        {"昆明", "南宁", "昆明-南宁"},
        {"兰州", "拉萨", "兰州-拉萨"},
        {"兰州", "乌鲁木齐", "兰州-乌鲁木齐"},
        {"洛阳", "桂林", "洛阳-桂林"},
        {"南宁", "贵阳", "南宁-贵阳"},
        {"上海", "杭州", "上海-杭州"},
        {"沈阳", "哈尔滨", "沈阳-哈尔滨"},
        {"天津", "徐州", "天津-徐州"},
        {"西安", "成都", "西安-成都"},
        {"西安", "兰州", "西安-兰州"},
        {"徐州", "连云港", "徐州-连云港"},
        {"徐州", "上海", "徐州-上海"},
        {"郑州", "西安", "郑州-西安"},
        {"郑州", "徐州", "郑州-徐州"},
        {"郑州", "长沙", "郑州-长沙"}
    };

    for (const auto& [fromName, toName, railwayName] : railwayData) {
        City* from = stats.getCityByName(fromName);
        City* to = stats.getCityByName(toName);
        if (from && to) {
            Railway* r = new Railway(railwayName, from, to);
            stats.addRailway(*r);
        } else {
            qDebug() << "❌ 城市未找到:" << QString::fromStdString(fromName) << "或" << QString::fromStdString(toName);
        }
    }

    // 可选设置家乡和工作地（以北京和上海为例）
    stats.setHometown(stats.getCityByName("北京"));
    stats.setWorkplace(stats.getCityByName("上海"));
}


void MainWindow::loadRailwayOverlays() {
    QString basePath = QCoreApplication::applicationDirPath() + "/../images/railways";

    QStringList filenames = QDir(basePath).entryList(QStringList() << "*.png", QDir::Files);
    for (const QString& file : filenames) {
        QPixmap img(basePath + "/" + file);
        if (!img.isNull()) {
            QString railwayName = file.section('.', 0, 0); // 去掉 .png 后缀
            railwayOverlays[railwayName] = img;
            qDebug() << "✅ 加载图层:" << railwayName;
        } else {
            qDebug() << "⚠️ 无法加载:" << file;
        }
    }
}
void MainWindow::updateRailwayMap() {
    // 加载背景图（资源文件）
    ui->mapLabel->resize(800, 600);
    QPixmap baseMap(":/images/background.png");
    if (baseMap.isNull()) {
        QMessageBox::warning(this, "错误", "未能加载背景地图！");
        return;
    }

    // 获取目标尺寸：mapLabel控件的显示区域
    QSize targetSize = ui->mapLabel->size();
    if (targetSize.width() < 10 || targetSize.height() < 10) {
        qDebug() << "❌ mapLabel 尺寸异常:" << targetSize;
        return;
    }

    // 缩放背景图适配控件
    QPixmap finalMap = baseMap.scaled(targetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPainter painter(&finalMap);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    std::set<std::string> visitedRailways;

    const auto& trips = stats.getAllTrips();
    qDebug() << "🚶 当前行程数量:" << trips.size();

    // 遍历所有行程，查找所经铁路
    for (const Trip& trip : trips) {
        auto path = stats.findRailwayPathBFS(trip);
        qDebug() << "📍 行程:" << QString::fromStdString(trip.getStart()->getName())
                 << " -> " << QString::fromStdString(trip.getEnd()->getName())
                 << " 路径长度:" << path.size();

        for (Railway* r : path) {
            visitedRailways.insert(r->getName());
        }
    }

    // 绘制所有访问过的铁路图层
    for (const std::string& name : visitedRailways) {
        QString qName = QString::fromStdString(name);
        if (railwayOverlays.contains(qName)) {
            QPixmap overlay = railwayOverlays[qName];
            if (!overlay.isNull()) {
                overlay = overlay.scaled(targetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                painter.drawPixmap(0, 0, overlay);
                    qDebug() << "✅ 成功叠加图层:" << qName;
            } else {
                qDebug() << "⚠️ 图层为空:" << qName;
            }
        } else {
            qDebug() << "🚫 缺失图层文件:" << qName;
        }
    }

    painter.end();
    ui->mapLabel->resize(800, 600);
    ui->mapLabel->setPixmap(finalMap);

    // 保存调试输出（可选）
    // 假设 finalMap 是你当前绘制好的 QPixmap
    QPixmap scaledPixmap = finalMap.scaled(2936, 2000, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    // 保存到文件
    QString savePath = QCoreApplication::applicationDirPath() + "/../debug_output.png";
    if (scaledPixmap.save(savePath)) {
        qDebug() << "🖼️ 地图已保存至:" << savePath;
    } else {
        qDebug() << "⚠️ 地图保存失败:" << savePath;
    }

}
