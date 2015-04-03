/********************************************************************************
** Form generated from reading UI file 'diskmasterui.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISKMASTERUI_H
#define UI_DISKMASTERUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "tabwidget.h"

QT_BEGIN_NAMESPACE

class Ui_DiskMasterUIClass
{
public:
    QAction *actionExit;
    QAction *CopyAction;
    QAction *EraseAction;
    QAction *action_5;
    QAction *VerifyAction;
    QAction *StartAction;
    QAction *StopTask;
    QAction *actionOpenTask;
    QAction *actionPreferences;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    TabWidget *mainTabWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QToolBar *mainToolbar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DiskMasterUIClass)
    {
        if (DiskMasterUIClass->objectName().isEmpty())
            DiskMasterUIClass->setObjectName(QStringLiteral("DiskMasterUIClass"));
        DiskMasterUIClass->resize(997, 681);
        actionExit = new QAction(DiskMasterUIClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/DiskMasterUI/icons/application_exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon);
        CopyAction = new QAction(DiskMasterUIClass);
        CopyAction->setObjectName(QStringLiteral("CopyAction"));
        CopyAction->setEnabled(false);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/DiskMasterUI/icons/copy_disk.png"), QSize(), QIcon::Normal, QIcon::Off);
        CopyAction->setIcon(icon1);
        EraseAction = new QAction(DiskMasterUIClass);
        EraseAction->setObjectName(QStringLiteral("EraseAction"));
        EraseAction->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/DiskMasterUI/icons/erase_task.png"), QSize(), QIcon::Normal, QIcon::Off);
        EraseAction->setIcon(icon2);
        action_5 = new QAction(DiskMasterUIClass);
        action_5->setObjectName(QStringLiteral("action_5"));
        VerifyAction = new QAction(DiskMasterUIClass);
        VerifyAction->setObjectName(QStringLiteral("VerifyAction"));
        VerifyAction->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/DiskMasterUI/icons/verify_task.png"), QSize(), QIcon::Normal, QIcon::Off);
        VerifyAction->setIcon(icon3);
        StartAction = new QAction(DiskMasterUIClass);
        StartAction->setObjectName(QStringLiteral("StartAction"));
        StartAction->setEnabled(false);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/DiskMasterUI/icons/start_task.png"), QSize(), QIcon::Normal, QIcon::Off);
        StartAction->setIcon(icon4);
        StopTask = new QAction(DiskMasterUIClass);
        StopTask->setObjectName(QStringLiteral("StopTask"));
        StopTask->setEnabled(false);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/DiskMasterUI/icons/stop_task.png"), QSize(), QIcon::Normal, QIcon::Off);
        StopTask->setIcon(icon5);
        actionOpenTask = new QAction(DiskMasterUIClass);
        actionOpenTask->setObjectName(QStringLiteral("actionOpenTask"));
        actionOpenTask->setCheckable(false);
        actionOpenTask->setChecked(false);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/DiskMasterUI/icons/open_task.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenTask->setIcon(icon6);
        actionPreferences = new QAction(DiskMasterUIClass);
        actionPreferences->setObjectName(QStringLiteral("actionPreferences"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/DiskMasterUI/icons/preferences.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPreferences->setIcon(icon7);
        centralWidget = new QWidget(DiskMasterUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        mainTabWidget = new TabWidget(centralWidget);
        mainTabWidget->setObjectName(QStringLiteral("mainTabWidget"));

        horizontalLayout->addWidget(mainTabWidget);

        DiskMasterUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DiskMasterUIClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 997, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        DiskMasterUIClass->setMenuBar(menuBar);
        mainToolbar = new QToolBar(DiskMasterUIClass);
        mainToolbar->setObjectName(QStringLiteral("mainToolbar"));
        DiskMasterUIClass->addToolBar(mainToolbar);
        statusBar = new QStatusBar(DiskMasterUIClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DiskMasterUIClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menu->addAction(actionOpenTask);
        menu->addSeparator();
        menu->addAction(actionExit);
        menu_2->addAction(StartAction);
        menu_2->addSeparator();
        menu_2->addAction(CopyAction);
        menu_2->addAction(EraseAction);
        menu_2->addAction(VerifyAction);
        menu_3->addAction(actionPreferences);
        mainToolbar->addAction(actionOpenTask);
        mainToolbar->addSeparator();
        mainToolbar->addAction(CopyAction);
        mainToolbar->addAction(VerifyAction);
        mainToolbar->addAction(EraseAction);
        mainToolbar->addSeparator();
        mainToolbar->addAction(StartAction);
        mainToolbar->addSeparator();
        mainToolbar->addAction(actionPreferences);
        mainToolbar->addSeparator();
        mainToolbar->addAction(actionExit);

        retranslateUi(DiskMasterUIClass);
        QObject::connect(mainTabWidget, SIGNAL(tabCloseRequested(int)), mainTabWidget, SLOT(CloseTabWidget(int)));
        QObject::connect(actionExit, SIGNAL(activated()), DiskMasterUIClass, SLOT(close()));

        mainTabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(DiskMasterUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *DiskMasterUIClass)
    {
        DiskMasterUIClass->setWindowTitle(QApplication::translate("DiskMasterUIClass", "DiskMasterTool", 0));
        actionExit->setText(QApplication::translate("DiskMasterUIClass", "Exit", 0));
        CopyAction->setText(QApplication::translate("DiskMasterUIClass", "Copying", 0));
        EraseAction->setText(QApplication::translate("DiskMasterUIClass", "Erasing", 0));
        action_5->setText(QApplication::translate("DiskMasterUIClass", "\320\277\321\200\320\270\320\276\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", 0));
        VerifyAction->setText(QApplication::translate("DiskMasterUIClass", "Verification", 0));
        StartAction->setText(QApplication::translate("DiskMasterUIClass", "Execute task", 0));
        StopTask->setText(QApplication::translate("DiskMasterUIClass", "\320\236\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \320\267\320\260\320\264\320\260\321\207\321\203", 0));
        actionOpenTask->setText(QApplication::translate("DiskMasterUIClass", "Open task", 0));
        actionPreferences->setText(QApplication::translate("DiskMasterUIClass", "Preferences", 0));
        menu->setTitle(QApplication::translate("DiskMasterUIClass", "File", 0));
        menu_2->setTitle(QApplication::translate("DiskMasterUIClass", "Task", 0));
        menu_3->setTitle(QApplication::translate("DiskMasterUIClass", "Settings", 0));
    } // retranslateUi

};

namespace Ui {
    class DiskMasterUIClass: public Ui_DiskMasterUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISKMASTERUI_H
