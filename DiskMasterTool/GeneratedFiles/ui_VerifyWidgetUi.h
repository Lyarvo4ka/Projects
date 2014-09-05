/********************************************************************************
** Form generated from reading UI file 'VerifyWidgetUi.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VERIFYWIDGETUI_H
#define UI_VERIFYWIDGETUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
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

class Ui_VerifyWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    DeviceWidget *deviceWidget;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_12;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_16;
    QLabel *currentSector;
    QSpacerItem *horizontalSpacer_2;
    QTabWidget *tabWidget;
    QWidget *tab_log;
    QHBoxLayout *horizontalLayout_6;
    QTextEdit *logText;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *startButton;
    QToolButton *cancelButton;

    void setupUi(QWidget *VerifyWidget)
    {
        if (VerifyWidget->objectName().isEmpty())
            VerifyWidget->setObjectName(QStringLiteral("VerifyWidget"));
        VerifyWidget->resize(602, 690);
        verticalLayout = new QVBoxLayout(VerifyWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        deviceWidget = new DeviceWidget(VerifyWidget);
        deviceWidget->setObjectName(QStringLiteral("deviceWidget"));

        horizontalLayout->addWidget(deviceWidget);


        verticalLayout->addLayout(horizontalLayout);

        groupBox_4 = new QGroupBox(VerifyWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        verticalLayout_12 = new QVBoxLayout(groupBox_4);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        progressBar = new QProgressBar(groupBox_4);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);

        verticalLayout_12->addWidget(progressBar);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_16 = new QLabel(groupBox_4);
        label_16->setObjectName(QStringLiteral("label_16"));

        horizontalLayout_7->addWidget(label_16);

        currentSector = new QLabel(groupBox_4);
        currentSector->setObjectName(QStringLiteral("currentSector"));

        horizontalLayout_7->addWidget(currentSector);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);


        verticalLayout_12->addLayout(horizontalLayout_7);


        verticalLayout->addWidget(groupBox_4);

        tabWidget = new QTabWidget(VerifyWidget);
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

        verticalLayout->addWidget(tabWidget);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_3 = new QSpacerItem(40, 23, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        startButton = new QToolButton(VerifyWidget);
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

        cancelButton = new QToolButton(VerifyWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/DiskMasterUI/icons/application_exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        cancelButton->setIcon(icon2);
        cancelButton->setIconSize(QSize(16, 16));
        cancelButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout_5->addWidget(cancelButton);


        verticalLayout->addLayout(horizontalLayout_5);


        retranslateUi(VerifyWidget);
        QObject::connect(startButton, SIGNAL(clicked()), VerifyWidget, SLOT(start_clicked()));
        QObject::connect(cancelButton, SIGNAL(clicked()), VerifyWidget, SLOT(exit_clicked()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(VerifyWidget);
    } // setupUi

    void retranslateUi(QWidget *VerifyWidget)
    {
        VerifyWidget->setWindowTitle(QApplication::translate("VerifyWidget", "Form", 0));
        groupBox_4->setTitle(QString());
        label_16->setText(QApplication::translate("VerifyWidget", "Sector:", 0));
        currentSector->setText(QString());
        logText->setHtml(QApplication::translate("VerifyWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_log), QApplication::translate("VerifyWidget", "Log", 0));
        startButton->setText(QApplication::translate("VerifyWidget", "Start", 0));
        cancelButton->setText(QApplication::translate("VerifyWidget", "Exit", 0));
    } // retranslateUi

};

namespace Ui {
    class VerifyWidget: public Ui_VerifyWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VERIFYWIDGETUI_H
