/********************************************************************************
** Form generated from reading UI file 'signatureseditor.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNATURESEDITOR_H
#define UI_SIGNATURESEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignaturesEditorClass
{
public:
    QAction *actionNew_file;
    QAction *actionLoad_file;
    QAction *actionSave_file;
    QAction *actionExit;
    QAction *actionAbout;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SignaturesEditorClass)
    {
        if (SignaturesEditorClass->objectName().isEmpty())
            SignaturesEditorClass->setObjectName(QStringLiteral("SignaturesEditorClass"));
        SignaturesEditorClass->resize(645, 526);
        actionNew_file = new QAction(SignaturesEditorClass);
        actionNew_file->setObjectName(QStringLiteral("actionNew_file"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/SignaturesEditor/icons/newfile.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew_file->setIcon(icon);
        actionLoad_file = new QAction(SignaturesEditorClass);
        actionLoad_file->setObjectName(QStringLiteral("actionLoad_file"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/SignaturesEditor/icons/loadfile2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoad_file->setIcon(icon1);
        actionSave_file = new QAction(SignaturesEditorClass);
        actionSave_file->setObjectName(QStringLiteral("actionSave_file"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/SignaturesEditor/icons/savefile.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_file->setIcon(icon2);
        actionExit = new QAction(SignaturesEditorClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/SignaturesEditor/icons/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon3);
        actionAbout = new QAction(SignaturesEditorClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        centralWidget = new QWidget(SignaturesEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        horizontalLayout->addWidget(listWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);


        horizontalLayout->addLayout(verticalLayout);

        SignaturesEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SignaturesEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 645, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        SignaturesEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SignaturesEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SignaturesEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SignaturesEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SignaturesEditorClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew_file);
        menuFile->addAction(actionLoad_file);
        menuFile->addAction(actionSave_file);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuHelp->addAction(actionAbout);
        mainToolBar->addAction(actionNew_file);
        mainToolBar->addAction(actionLoad_file);
        mainToolBar->addAction(actionSave_file);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionExit);

        retranslateUi(SignaturesEditorClass);

        QMetaObject::connectSlotsByName(SignaturesEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *SignaturesEditorClass)
    {
        SignaturesEditorClass->setWindowTitle(QApplication::translate("SignaturesEditorClass", "SignaturesEditor", Q_NULLPTR));
        actionNew_file->setText(QApplication::translate("SignaturesEditorClass", "New file", Q_NULLPTR));
        actionLoad_file->setText(QApplication::translate("SignaturesEditorClass", "Load file", Q_NULLPTR));
        actionSave_file->setText(QApplication::translate("SignaturesEditorClass", "Save file", Q_NULLPTR));
        actionExit->setText(QApplication::translate("SignaturesEditorClass", "Exit", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("SignaturesEditorClass", "About", Q_NULLPTR));
        pushButton->setText(QApplication::translate("SignaturesEditorClass", "Add", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("SignaturesEditorClass", "Remove", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("SignaturesEditorClass", "Modify", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("SignaturesEditorClass", "File", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("SignaturesEditorClass", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SignaturesEditorClass: public Ui_SignaturesEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNATURESEDITOR_H
