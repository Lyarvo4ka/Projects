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

QT_BEGIN_NAMESPACE

class Ui_CopyWidgetUi
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
    QLabel *label_8;
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
    QWidget *sectorViewWidget;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *startButton;
    QToolButton *toolButton;

    void setupUi(QWidget *CopyWidgetUi)
    {
        if (CopyWidgetUi->objectName().isEmpty())
            CopyWidgetUi->setObjectName(QStringLiteral("CopyWidgetUi"));
        CopyWidgetUi->resize(714, 829);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CopyWidgetUi->sizePolicy().hasHeightForWidth());
        CopyWidgetUi->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(CopyWidgetUi);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        sourceWidget = new DeviceWidget(CopyWidgetUi);
        sourceWidget->setObjectName(QStringLiteral("sourceWidget"));

        horizontalLayout_12->addWidget(sourceWidget);

        label_3 = new QLabel(CopyWidgetUi);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/DiskMasterUI/icons/right_arrow.png")));

        horizontalLayout_12->addWidget(label_3);

        targetWidget = new DeviceWidget(CopyWidgetUi);
        targetWidget->setObjectName(QStringLiteral("targetWidget"));

        horizontalLayout_12->addWidget(targetWidget);


        horizontalLayout->addLayout(horizontalLayout_12);


        verticalLayout_2->addLayout(horizontalLayout);

        groupBox_4 = new QGroupBox(CopyWidgetUi);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setEnabled(true);
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(groupBox_4);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout->addWidget(label_8);

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
        redSquare = new QFrame(CopyWidgetUi);
        redSquare->setObjectName(QStringLiteral("redSquare"));
        redSquare->setMaximumSize(QSize(12, 12));
        redSquare->setAutoFillBackground(false);
        redSquare->setFrameShape(QFrame::Box);
        redSquare->setFrameShadow(QFrame::Plain);

        horizontalLayout_9->addWidget(redSquare);

        label_2 = new QLabel(CopyWidgetUi);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_9->addWidget(label_2);

        badSectorsText = new QLabel(CopyWidgetUi);
        badSectorsText->setObjectName(QStringLiteral("badSectorsText"));

        horizontalLayout_9->addWidget(badSectorsText);


        horizontalLayout_13->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        greenSquare = new QFrame(CopyWidgetUi);
        greenSquare->setObjectName(QStringLiteral("greenSquare"));
        greenSquare->setMaximumSize(QSize(12, 12));
        greenSquare->setAutoFillBackground(false);
        greenSquare->setFrameShape(QFrame::Box);
        greenSquare->setFrameShadow(QFrame::Plain);

        horizontalLayout_10->addWidget(greenSquare);

        label_5 = new QLabel(CopyWidgetUi);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_10->addWidget(label_5);

        readSectorsText = new QLabel(CopyWidgetUi);
        readSectorsText->setObjectName(QStringLiteral("readSectorsText"));

        horizontalLayout_10->addWidget(readSectorsText);


        horizontalLayout_13->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        graySquare = new QFrame(CopyWidgetUi);
        graySquare->setObjectName(QStringLiteral("graySquare"));
        graySquare->setMaximumSize(QSize(12, 12));
        graySquare->setAutoFillBackground(false);
        graySquare->setFrameShape(QFrame::Box);
        graySquare->setFrameShadow(QFrame::Plain);

        horizontalLayout_11->addWidget(graySquare);

        label_7 = new QLabel(CopyWidgetUi);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_11->addWidget(label_7);

        unreadText = new QLabel(CopyWidgetUi);
        unreadText->setObjectName(QStringLiteral("unreadText"));

        horizontalLayout_11->addWidget(unreadText);


        horizontalLayout_13->addLayout(horizontalLayout_11);


        verticalLayout_2->addLayout(horizontalLayout_13);

        tabWidget = new QTabWidget(CopyWidgetUi);
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
        sectorViewWidget = new QWidget(tab_sector);
        sectorViewWidget->setObjectName(QStringLiteral("sectorViewWidget"));

        horizontalLayout_2->addWidget(sectorViewWidget);

        tabWidget->addTab(tab_sector, QString());

        verticalLayout_2->addWidget(tabWidget);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_2 = new QSpacerItem(40, 23, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        startButton = new QToolButton(CopyWidgetUi);
        startButton->setObjectName(QStringLiteral("startButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy1);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/DiskMasterUI/icons/start_task.png"), QSize(), QIcon::Normal, QIcon::Off);
        startButton->setIcon(icon1);
        startButton->setIconSize(QSize(16, 16));
        startButton->setCheckable(false);
        startButton->setPopupMode(QToolButton::DelayedPopup);
        startButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        startButton->setAutoRaise(false);

        horizontalLayout_5->addWidget(startButton);

        toolButton = new QToolButton(CopyWidgetUi);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/DiskMasterUI/icons/application_exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon2);
        toolButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout_5->addWidget(toolButton);


        verticalLayout_2->addLayout(horizontalLayout_5);


        retranslateUi(CopyWidgetUi);
        QObject::connect(startButton, SIGNAL(clicked()), CopyWidgetUi, SLOT(start_clicked()));
        QObject::connect(toolButton, SIGNAL(clicked()), CopyWidgetUi, SLOT(exit_clicked()));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(CopyWidgetUi);
    } // setupUi

    void retranslateUi(QWidget *CopyWidgetUi)
    {
        CopyWidgetUi->setWindowTitle(QApplication::translate("CopyWidgetUi", "Form", 0));
        label_3->setText(QString());
        groupBox_4->setTitle(QApplication::translate("CopyWidgetUi", "\320\237\321\200\320\276\320\263\321\200\320\265\321\201\321\201", 0));
        label_8->setText(QApplication::translate("CopyWidgetUi", "\320\242\320\265\320\272\321\203\321\211\320\260\321\217 \320\267\320\260\320\264\320\260\321\207\320\260: \320\237\320\276\320\273\320\275\320\260\321\217 \320\272\320\276\320\277\320\270\321\217", 0));
        label_16->setText(QApplication::translate("CopyWidgetUi", "\320\241\320\265\320\272\321\202\320\276\321\200:", 0));
        currentSector->setText(QString());
        label_4->setText(QApplication::translate("CopyWidgetUi", "\320\222\321\200\320\265\320\274\321\217:", 0));
        timeText->setText(QApplication::translate("CopyWidgetUi", "0", 0));
        label->setText(QApplication::translate("CopyWidgetUi", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214:", 0));
        speedText->setText(QApplication::translate("CopyWidgetUi", "0", 0));
        label_6->setText(QApplication::translate("CopyWidgetUi", "\320\236\321\201\321\202\320\260\320\273\320\276\321\201\321\214:", 0));
        remainingText->setText(QApplication::translate("CopyWidgetUi", "0", 0));
        label_2->setText(QApplication::translate("CopyWidgetUi", "<html><head/><body><p>- \320\235\320\265\321\207\320\270\321\202\320\260\320\265\320\274\321\213\320\265 \321\201\320\265\320\272\321\202\320\276\321\200\320\260 : </p></body></html>", 0));
        badSectorsText->setText(QApplication::translate("CopyWidgetUi", "0", 0));
        label_5->setText(QApplication::translate("CopyWidgetUi", "<html><head/><body><p>- \320\237\321\200\320\276\321\207\320\270\321\202\320\260\321\202\321\213\320\265 \321\201\320\265\320\272\321\202\320\276\321\200\320\260</p></body></html>", 0));
        readSectorsText->setText(QApplication::translate("CopyWidgetUi", "0", 0));
        label_7->setText(QApplication::translate("CopyWidgetUi", "<html><head/><body><p>- \320\235\320\265\320\277\321\200\320\276\321\207\320\270\321\202\320\260\320\275\321\213\320\265 \321\201\320\265\320\272\321\202\320\276\321\200\320\260</p></body></html>", 0));
        unreadText->setText(QApplication::translate("CopyWidgetUi", "0", 0));
        logText->setHtml(QApplication::translate("CopyWidgetUi", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_log), QApplication::translate("CopyWidgetUi", "\320\237\321\200\320\276\321\202\320\276\320\272\320\276\320\273", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_sector), QApplication::translate("CopyWidgetUi", "\320\232\320\260\321\200\321\202\320\260 \321\201\320\265\320\272\321\202\320\276\321\200\320\276\320\262", 0));
        startButton->setText(QApplication::translate("CopyWidgetUi", "\320\241\321\202\320\260\321\200\321\202", 0));
        toolButton->setText(QApplication::translate("CopyWidgetUi", "\320\222\321\213\321\205\320\276\320\264", 0));
    } // retranslateUi

};

namespace Ui {
    class CopyWidgetUi: public Ui_CopyWidgetUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPYWIDGETUI_H
