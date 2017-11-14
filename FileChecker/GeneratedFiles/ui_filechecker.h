/********************************************************************************
** Form generated from reading UI file 'filechecker.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILECHECKER_H
#define UI_FILECHECKER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileCheckerClass
{
public:
    QAction *actionOffice_2003;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QMenuBar *menuBar;
    QMenu *menuTask;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FileCheckerClass)
    {
        if (FileCheckerClass->objectName().isEmpty())
            FileCheckerClass->setObjectName(QStringLiteral("FileCheckerClass"));
        FileCheckerClass->resize(574, 524);
        actionOffice_2003 = new QAction(FileCheckerClass);
        actionOffice_2003->setObjectName(QStringLiteral("actionOffice_2003"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/FileChecker/icons/office_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOffice_2003->setIcon(icon);
        centralWidget = new QWidget(FileCheckerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(20, 20, 511, 411));
        tabWidget->setTabBarAutoHide(true);
        FileCheckerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FileCheckerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 574, 21));
        menuTask = new QMenu(menuBar);
        menuTask->setObjectName(QStringLiteral("menuTask"));
        FileCheckerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FileCheckerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        FileCheckerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(FileCheckerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        FileCheckerClass->setStatusBar(statusBar);

        menuBar->addAction(menuTask->menuAction());
        menuTask->addAction(actionOffice_2003);
        mainToolBar->addAction(actionOffice_2003);

        retranslateUi(FileCheckerClass);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(FileCheckerClass);
    } // setupUi

    void retranslateUi(QMainWindow *FileCheckerClass)
    {
        FileCheckerClass->setWindowTitle(QApplication::translate("FileCheckerClass", "FileChecker", Q_NULLPTR));
        actionOffice_2003->setText(QApplication::translate("FileCheckerClass", "Office 2003", Q_NULLPTR));
        menuTask->setTitle(QApplication::translate("FileCheckerClass", "\320\227\320\260\320\264\320\260\321\207\320\260", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FileCheckerClass: public Ui_FileCheckerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILECHECKER_H
