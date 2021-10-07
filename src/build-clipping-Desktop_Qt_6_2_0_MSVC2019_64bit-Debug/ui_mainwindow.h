/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_main_polygon;
    QAction *action_window_polygon;
    QAction *action_clip;
    QAction *action_empty;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        action_main_polygon = new QAction(MainWindow);
        action_main_polygon->setObjectName(QString::fromUtf8("action_main_polygon"));
        action_window_polygon = new QAction(MainWindow);
        action_window_polygon->setObjectName(QString::fromUtf8("action_window_polygon"));
        action_clip = new QAction(MainWindow);
        action_clip->setObjectName(QString::fromUtf8("action_clip"));
        action_empty = new QAction(MainWindow);
        action_empty->setObjectName(QString::fromUtf8("action_empty"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(action_main_polygon);
        menu->addAction(action_window_polygon);
        menu->addSeparator();
        menu->addAction(action_clip);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        action_main_polygon->setText(QCoreApplication::translate("MainWindow", "\344\270\273\345\244\232\350\276\271\345\275\242", nullptr));
        action_window_polygon->setText(QCoreApplication::translate("MainWindow", "\350\243\201\345\211\252\345\244\232\350\276\271\345\275\242", nullptr));
        action_clip->setText(QCoreApplication::translate("MainWindow", "\350\243\201\345\211\252", nullptr));
        action_empty->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
