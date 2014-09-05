/********************************************************************************
** Form generated from reading UI file 'imager.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGER_H
#define UI_IMAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImagerClass
{
public:
    QAction *actionPreferences;
    QAction *actionExit;
    QWidget *centralWidget;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout;
    QGroupBox *SourceGroupBox;
    QGridLayout *gridLayout;
    QLineEdit *SourceText;
    QPushButton *SourceButton;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *CurrentLBAText;
    QLineEdit *EditNumberLBA;
    QLabel *CurrentSpeedText;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QGroupBox *TargetGroupBox;
    QGridLayout *gridLayout_3;
    QLineEdit *TargetText;
    QPushButton *TargetButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *StartButton;
    QPushButton *StopButton;
    QProgressBar *progressBar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSetting;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ImagerClass)
    {
        if (ImagerClass->objectName().isEmpty())
            ImagerClass->setObjectName(QStringLiteral("ImagerClass"));
        ImagerClass->resize(715, 380);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ImagerClass->sizePolicy().hasHeightForWidth());
        ImagerClass->setSizePolicy(sizePolicy);
        ImagerClass->setMinimumSize(QSize(0, 0));
        ImagerClass->setFocusPolicy(Qt::NoFocus);
        actionPreferences = new QAction(ImagerClass);
        actionPreferences->setObjectName(QStringLiteral("actionPreferences"));
        actionExit = new QAction(ImagerClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(ImagerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_5 = new QGridLayout(centralWidget);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        SourceGroupBox = new QGroupBox(centralWidget);
        SourceGroupBox->setObjectName(QStringLiteral("SourceGroupBox"));
        gridLayout = new QGridLayout(SourceGroupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        SourceText = new QLineEdit(SourceGroupBox);
        SourceText->setObjectName(QStringLiteral("SourceText"));

        gridLayout->addWidget(SourceText, 0, 0, 1, 1);

        SourceButton = new QPushButton(SourceGroupBox);
        SourceButton->setObjectName(QStringLiteral("SourceButton"));
        SourceButton->setMaximumSize(QSize(24, 24));
        SourceButton->setCursor(QCursor(Qt::OpenHandCursor));
        QIcon icon;
        icon.addFile(QStringLiteral("icons/DeviceIcon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        SourceButton->setIcon(icon);
        SourceButton->setIconSize(QSize(24, 24));
        SourceButton->setCheckable(false);
        SourceButton->setChecked(false);
        SourceButton->setFlat(false);

        gridLayout->addWidget(SourceButton, 0, 1, 1, 1);


        verticalLayout->addWidget(SourceGroupBox);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        CurrentLBAText = new QLabel(groupBox);
        CurrentLBAText->setObjectName(QStringLiteral("CurrentLBAText"));

        gridLayout_2->addWidget(CurrentLBAText, 0, 0, 1, 1);

        EditNumberLBA = new QLineEdit(groupBox);
        EditNumberLBA->setObjectName(QStringLiteral("EditNumberLBA"));
        EditNumberLBA->setReadOnly(true);

        gridLayout_2->addWidget(EditNumberLBA, 0, 1, 1, 1);

        CurrentSpeedText = new QLabel(groupBox);
        CurrentSpeedText->setObjectName(QStringLiteral("CurrentSpeedText"));

        gridLayout_2->addWidget(CurrentSpeedText, 1, 0, 1, 1);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout_2->addWidget(lineEdit, 1, 1, 1, 1);


        verticalLayout->addWidget(groupBox);


        gridLayout_4->addLayout(verticalLayout, 0, 0, 2, 1);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setMinimumSize(QSize(0, 50));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        pushButton->setFont(font);
        pushButton->setCheckable(false);
        pushButton->setFlat(true);

        gridLayout_4->addWidget(pushButton, 0, 1, 1, 1);

        TargetGroupBox = new QGroupBox(centralWidget);
        TargetGroupBox->setObjectName(QStringLiteral("TargetGroupBox"));
        gridLayout_3 = new QGridLayout(TargetGroupBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        TargetText = new QLineEdit(TargetGroupBox);
        TargetText->setObjectName(QStringLiteral("TargetText"));

        gridLayout_3->addWidget(TargetText, 0, 0, 1, 1);

        TargetButton = new QPushButton(TargetGroupBox);
        TargetButton->setObjectName(QStringLiteral("TargetButton"));
        TargetButton->setMaximumSize(QSize(24, 24));
        TargetButton->setCursor(QCursor(Qt::OpenHandCursor));
        TargetButton->setIcon(icon);
        TargetButton->setIconSize(QSize(24, 24));
        TargetButton->setCheckable(false);
        TargetButton->setChecked(false);
        TargetButton->setFlat(false);

        gridLayout_3->addWidget(TargetButton, 0, 1, 1, 1);


        gridLayout_4->addWidget(TargetGroupBox, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 1, 2, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 99, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(27, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        StartButton = new QPushButton(centralWidget);
        StartButton->setObjectName(QStringLiteral("StartButton"));

        horizontalLayout->addWidget(StartButton);

        StopButton = new QPushButton(centralWidget);
        StopButton->setObjectName(QStringLiteral("StopButton"));

        horizontalLayout->addWidget(StopButton);


        gridLayout_5->addLayout(horizontalLayout, 2, 0, 1, 1);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);
        progressBar->setAlignment(Qt::AlignCenter);
        progressBar->setTextVisible(true);
        progressBar->setInvertedAppearance(false);
        progressBar->setTextDirection(QProgressBar::TopToBottom);

        gridLayout_5->addWidget(progressBar, 3, 0, 1, 1);

        ImagerClass->setCentralWidget(centralWidget);
        progressBar->raise();
        groupBox->raise();
        pushButton->raise();
        menuBar = new QMenuBar(ImagerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 715, 20));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuSetting = new QMenu(menuBar);
        menuSetting->setObjectName(QStringLiteral("menuSetting"));
        ImagerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ImagerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ImagerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ImagerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setEnabled(false);
        ImagerClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuSetting->menuAction());
        menuFile->addAction(actionExit);
        menuSetting->addAction(actionPreferences);

        retranslateUi(ImagerClass);

        QMetaObject::connectSlotsByName(ImagerClass);
    } // setupUi

    void retranslateUi(QMainWindow *ImagerClass)
    {
        ImagerClass->setWindowTitle(QApplication::translate("ImagerClass", "Imager", 0));
        actionPreferences->setText(QApplication::translate("ImagerClass", "Preferences", 0));
        actionExit->setText(QApplication::translate("ImagerClass", "Exit", 0));
        SourceGroupBox->setTitle(QApplication::translate("ImagerClass", "Source Device", 0));
        SourceButton->setText(QString());
        groupBox->setTitle(QApplication::translate("ImagerClass", "GroupBox", 0));
        CurrentLBAText->setText(QApplication::translate("ImagerClass", "<html><head/><body><p><span style=\" font-weight:600; text-decoration: underline;\">Current LBA:</span></p></body></html>", 0));
        CurrentSpeedText->setText(QApplication::translate("ImagerClass", "<html><head/><body><p><span style=\" font-weight:600; text-decoration: underline;\">Current Speed:</span></p></body></html>", 0));
        pushButton->setText(QApplication::translate("ImagerClass", "--->", 0));
        TargetGroupBox->setTitle(QApplication::translate("ImagerClass", "Target Device", 0));
        TargetButton->setText(QString());
        StartButton->setText(QApplication::translate("ImagerClass", "Start", 0));
        StopButton->setText(QApplication::translate("ImagerClass", "Stop", 0));
        menuFile->setTitle(QApplication::translate("ImagerClass", "File", 0));
        menuSetting->setTitle(QApplication::translate("ImagerClass", "Setting", 0));
    } // retranslateUi

};

namespace Ui {
    class ImagerClass: public Ui_ImagerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGER_H
