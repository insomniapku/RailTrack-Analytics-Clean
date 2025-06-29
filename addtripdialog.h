#ifndef ADDTRIPDIALOG_H
#define ADDTRIPDIALOG_H

#include <QDialog>

namespace Ui {
class AddTripDialog;
}

class AddTripDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddTripDialog(QWidget *parent = nullptr);
    ~AddTripDialog();

    QString getFromCity() const;
    QString getToCity() const;
    QDateTime getDepartureTime() const;
    QDateTime getArrivalTime() const;
    QString getRailwayName() const;


private:
    Ui::AddTripDialog *ui;

    // 城市列表
    const QStringList cities = {
        "北京", "上海", "广州", "杭州", "徐州", "长沙",
        "郑州", "兰州", "西安", "乌鲁木齐", "大同", "洛阳",
        "呼和浩特", "成都", "贵阳", "昆明", "南宁", "桂林","沈阳",
        "天津","香港","哈尔滨","牡丹江","齐齐哈尔","拉萨","连云港"
    };
};

#endif // ADDTRIPDIALOG_H
