/********************************************************************************
** Form generated from reading UI file 'CopyWidgetUi.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COPYWIDGETUI_H
#define UI_COPYWIDGETUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "devicewidget.h"
#include "sectormapwidget.h"

QT_BEGIN_NAMESPACE

class Ui_CopyWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_12;
    DeviceWidget *sourceWidget;
    QLabel *label_3;
    DeviceWidget *targetWidget;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_8;
    QLabel *currentTaskText;
    QProgressBar *progressBar;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_16;
    QLabel *currentSector;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLabel *timeText;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLabel *speedText;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_6;
    QLabel *remainingText;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_13;
    QHBoxLayout *horizontalLayout_9;
    QFrame *redSquare;
    QLabel *label_2;
    QLabel *badSectorsText;
    QHBoxLayout *horizontalLayout_10;
    QFrame *greenSquare;
    QLabel *label_5;
    QLabel *readSectorsText;
    QHBoxLayout *horizontalLayout_11;
    QFrame *graySquare;
    QLabel *label_7;
    QLabel *unreadText;
    QTabWidget *tabWidget;
    QWidget *tab_log;
    QHBoxLayout *horizontalLayout_6;
    QTextEdit *logText;
    QWidget *tab_sector;
    QHBoxLayout *horizontalLayout_2;
    SectorMapWidget *sectorViewWidget;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *startButton;
    QToolButton *toolButton;

    void setupUi(QWidget *CopyWidget)
    {
        if (CopyWidget->objectName().isEmpty())
            CopyWidget->setObjectName(QStringLiteral("CopyWidget"));
        CopyWidget->resize(714, 829);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CopyWidget->sizePolicy().hasHeightForWidth());
        CopyWidget->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(CopyWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        sourceWidget = new DeviceWidget(CopyWidget);
        sourceWidget->setObjectName(QStringLiteral("sourceWidget"));

        horizontalLayout_12->addWidget(sourceWidget);

        label_3 = new QLabel(CopyWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/DiskMasterUI/icons/right_arrow.png")));

        horizontalLayout_12->addWidget(label_3);

        targetWidget = new DeviceWidget(CopyWidget);
        targetWidget->setObjectName(QStringLiteral("targetWidget"));

        horizontalLayout_12->addWidget(targetWidget);


        horizontalLayout->addLayout(horizontalLayout_12);


        verticalLayout_2->addLayout(horizontalLayout);

        groupBox_4 = new QGroupBox(CopyWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setEnabled(true);
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(groupBox_4);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_14->addWidget(label_8);

        currentTaskText = new QLabel(groupBox_4);
        currentTaskText->setObjectName(QStringLiteral("currentTaskText"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(currentTaskText->sizePolicy().hasHeightForWidth());
        currentTaskText->setSizePolicy(sizePolicy1);

        horizontalLayout_14->addWidget(currentTaskText);


        verticalLayout->addLayout(horizontalLayout_14);

        progressBar = new QProgressBar(groupBox_4);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(progressBar);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_16 = new QLabel(groupBox_4);
        label_16->setObjectName(QStringLiteral("label_16"));

        horizontalLayout_7->addWidget(label_16);

        currentSector = new QLabel(groupBox_4);
        currentSector->setObjectName(QStringLiteral("currentSector"));

        horizontalLayout_7->addWidget(currentSector);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout_7, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        timeText = new QLabel(groupBox_4);
        timeText->setObjectName(QStringLiteral("timeText"));

        horizontalLayout_4->addWidget(timeText);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout_4, 0, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(groupBox_4);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        speedText = new QLabel(groupBox_4);
        speedText->setObjectName(QStringLiteral("speedText"));

        horizontalLayout_3->addWidget(speedText);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_8->addWidget(label_6);

        remainingText = new QLabel(groupBox_4);
        remainingText->setObjectName(QStringLiteral("remainingText"));

        horizontalLayout_8->addWidget(remainingText);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_5);


        gridLayout->addLayout(horizontalLayout_8, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        verticalLayout_2->addWidget(groupBox_4);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        redSquare = new QFrame(CopyWidget);
        redSquare->setObjectName(QStringLiteral("redSquare"));
        redSquare->setMaximumSize(QSize(12, 12));
        redSquare->setAutoFillbackground(false);
        redSquare->setFrameShape(QFrame::Box);
        redSquare->setFrameShadow(QFrame::Plain);

        horizontalLayout_9->addWidget(redSquare);

        label_2 = new QLabel(CopyWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_9->addWidget(label_2);

        badSectorsText = new QLabel(CopyWidget);
        badSectorsText->setObjectName(QStringLiteral("badSectorsText"));

        horizontalLayout_9->addWidget(badSectorsText);


        horizontalLayout_13->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        greenSquare = new QFrame(CopyWidget);
        greenSquare->setObjectName(QStringLiteral("greenSquare"));
        greenSquare->setMaximumSize(QSize(12, 12));
        greenSquare->setAutoFillbackground(false);
        greenSquare->setFrameShape(QFrame::Box);
        greenSquare->setFrameShadow(QFrame::Plain);

        horizontalLayout_10->addWidget(greenSquare);

        label_5 = new QLabel(CopyWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_10->addWidget(label_5);

        readSectorsText = new QLabel(CopyWidget);
        readSectorsText->setObjectName(QStringLiteral("readSectorsText"));

        horizontalLayout_10->addWidget(readSectorsText);


        horizontalLayout_13->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        graySquare = new QFrame(CopyWidget);
        graySquare->setObjectName(QStringLiteral("graySquare"));
        graySquare->setMaximumSize(QSize(12, 12));
        graySquare->setAutoFillbackground(false);
        graySquare->setFrameShape(QFrame::Box);
        graySquare->setFrameShadow(QFrame::Plain);

        horizontalLayout_11->addWidget(graySquare);

        label_7 = new QLabel(CopyWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_11->addWidget(label_7);

        unreadText = new QLabel(CopyWidget);
        unreadText->setObjectName(QStringLiteral("unreadText"));

        horizontalLayout_11->addWidget(unreadText);


        horizontalLayout_13->addLayout(horizontalLayout_11);


        verticalLayout_2->addLayout(horizontalLayout_13);

        tabWidget = new QTabWidget(CopyWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setDocumentMode(false);
        tabWidget->setMovable(false);
        tab_log = new QWidget();
        tab_log->setObjectName(QStringLiteral("tab_log"));
        horizontalLayout_6 = new QHBoxLayout(tab_log);
        horizontalLayout_6->setSpacing(1);
        horizontalLayout_6->setContentsMargins(1, 1, 1, 1);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        logText = new QTextEdit(tab_log);
        logText->setObjectName(QStringLiteral("logText"));
        logText->setFrameShape(QFrame::Box);
        logText->setFrameShadow(QFrame::Plain);
        logText->setReadOnly(true);

        horizontalLayout_6->addWidget(logText);

        QIcon icon;
        icon.addFile(QStringLiteral(":/DiskMasterUI/icons/log.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab_log, icon, QString());
        tab_sector = new QWidget();
        tab_sector->setObjectName(QStringLiteral("tab_sector"));
        horizontalLayout_2 = new QHBoxLayout(tab_sector);
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(9, 0, 0, 0);
        sectorViewWidget = new SectorMapWidget(tab_sector);
        sectorViewWidget->setObjectName(QStringLiteral("sectorViewWidget"));

        horizontalLayout_2->addWidget(sectorViewWidget);

        tabWidget->addTab(tab_sector, QString());

        verticalLayout_2->addWidget(tabWidget);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_2 = new QSpacerItem(40, 23, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        startButton = new QToolButton(CopyWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy2);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/DiskMasterUI/icons/start_task.png"), QSize(), QIcon::Normal, QIcon::Off);
        startButton->setIcon(icon1);
        startButton->setIconSize(QSize(16, 16));
        startButton->setCheckable(false);
        startButton->setPopupMode(QToolButton::DelayedPopup);
        startButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        startButton->setAutoRaise(false);

        horizontalLayout_5->addWidget(startButton);

        toolButton = new QToolButton(CopyWidget);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/DiskMasterUI/icons/application_exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon2);
        toolButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout_5->addWidget(toolButton);


        verticalLayout_2->addLayout(horizontalLayout_5);


        retranslateUi(CopyWidget);
        QObject::connect(startButton, SIGNAL(clicked()), CopyWidget, SLOT(start_clicked()));
        QObject::connect(toolButton, SIGNAL(clicked()), CopyWidget, SLOT(exit_clicked()));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(CopyWidget);
    } // setupUi

    void retranslateUi(QWidget *CopyWidget)
    {
        CopyWidget->setWindowTitle(QApplication::translate("CopyWidget", "Form", 0));
        label_3->setText(QString());
        groupBox_4->setTitle(QApplication::translate("CopyWidget", "Progress", 0));
        label_8->setText(QApplication::translate("CopyWidget", "Current task", 0));
        currentTaskText->setText(QApplication::translate("CopyWidget", "Full copy", 0));
        label_16->setText(QApplication::translate("CopyWidget", "Sector:", 0));
        currentSector->setText(QString());
        label_4->setText(QApplication::translate("CopyWidget", "Time:", 0));
        timeText->setText(QApplication::translate("CopyWidget", "0", 0));
        label->setText(QApplication::translate("CopyWidget", "Speed:", 0));
        speedText->setText(QApplication::translate("CopyWidget", "0", 0));
        label_6->setText(QApplication::translate("CopyWidget", "Remaining:", 0));
        remainingText->setText(QApplication::translate("CopyWidget", "0", 0));
        label_2->setText(QApplication::translate("CopyWidget", "<html><head/><body><p>- Bad sectors : </p></body></html>", 0));
        badSectorsText->setText(QApplication::translate("CopyWidget", "0", 0));
        label_5->setText(QApplication::translate("CopyWidget", "<html><head/><body><p>- Read sectors :</p></body></html>", 0));
        readSectorsText->setText(QApplication::translate("CopyWidget", "0", 0));
        label_7->setText(QApplication::translate("CopyWidget", "<html><head/><body><p>- Not read sectors</p></body></html>", 0));
        unreadText->setText(QApplication::translate("CopyWidget", "0", 0));
        logText->setHtml(QApplication::translate("CopyWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_log), QApplication::translate("CopyWidget", "Log", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_sector), QApplication::translate("CopyWidget", "Sector map", 0));
        startButton->setText(QApplication::translate("CopyWidget", "Start", 0));
        toolButton->setText(QApplication::translate("CopyWidget", "Exit", 0));
    } // retranslateUi

};

namespace Ui {
    class CopyWidget: public Ui_CopyWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPYWIDGETUI_H
