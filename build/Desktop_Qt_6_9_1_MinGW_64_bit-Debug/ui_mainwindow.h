/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *buttonLayout;
    QPushButton *addTripButton;
    QPushButton *generateReportButton;
    QPushButton *clearTripsButton;
    QLabel *mapLabel;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        addTripButton = new QPushButton(centralwidget);
        addTripButton->setObjectName("addTripButton");

        buttonLayout->addWidget(addTripButton);

        generateReportButton = new QPushButton(centralwidget);
        generateReportButton->setObjectName("generateReportButton");

        buttonLayout->addWidget(generateReportButton);

        clearTripsButton = new QPushButton(centralwidget);
        clearTripsButton->setObjectName("clearTripsButton");

        buttonLayout->addWidget(clearTripsButton);


        verticalLayout->addLayout(buttonLayout);

        mapLabel = new QLabel(centralwidget);
        mapLabel->setObjectName("mapLabel");
        mapLabel->setScaledContents(true);
        mapLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(mapLabel);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 18));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\351\223\201\350\267\257\350\241\214\347\250\213\345\210\206\346\236\220\347\263\273\347\273\237", nullptr));
        addTripButton->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\350\241\214\347\250\213", nullptr));
        generateReportButton->setText(QCoreApplication::translate("MainWindow", "\347\224\237\346\210\220\346\212\245\345\221\212", nullptr));
        clearTripsButton->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\231\244\350\241\214\347\250\213", nullptr));
        mapLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
