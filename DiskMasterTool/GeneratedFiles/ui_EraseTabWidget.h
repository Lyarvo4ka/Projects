/********************************************************************************
** Form generated from reading UI file 'EraseTabWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERASETABWIDGET_H
#define UI_ERASETABWIDGET_H

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

class Ui_EraseWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    DeviceWidget *deviceWidget;
    ErasePatternWidget *patternWidget;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_13;
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
    QSpacerItem *horizontalSpacer;
    QToolButton *startButton;
    QToolButton *cancelButton;

    void setupUi(QWidget *EraseWidget)
    {
        if (EraseWidget->objectName().isEmpty())
            EraseWidget->setObjectName(QStringLiteral("EraseWidget"));
        EraseWidget->resize(613, 746);
        verticalLayout_2 = new QVBoxLayout(EraseWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        deviceWidget = new DeviceWidget(EraseWidget);
        deviceWidget->setObjectName(QStringLiteral("deviceWidget"));

        horizontalLayout_2->addWidget(deviceWidget);

        patternWidget = new ErasePatternWidget(EraseWidget);
        patternWidget->setObjectName(QStringLiteral("patternWidget"));

        horizontalLayout_2->addWidget(patternWidget);


        verticalLayout_2->addLayout(horizontalLayout_2);

        groupBox_4 = new QGroupBox(EraseWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        verticalLayout_13 = new QVBoxLayout(groupBox_4);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        progressBar = new QProgressBar(groupBox_4);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(progressBar);

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


        verticalLayout_13->addLayout(horizontalLayout_7);


        verticalLayout_2->addWidget(groupBox_4);

        tabWidget = new QTabWidget(EraseWidget);
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

        verticalLayout_2->addWidget(tabWidget);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        startButton = new QToolButton(EraseWidget);
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

        cancelButton = new QToolButton(EraseWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/DiskMasterUI/icons/application_exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        cancelButton->setIcon(icon2);
        cancelButton->setIconSize(QSize(16, 16));
        cancelButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout_5->addWidget(cancelButton);


        verticalLayout_2->addLayout(horizontalLayout_5);


        retranslateUi(EraseWidget);
        QObject::connect(startButton, SIGNAL(clicked()), EraseWidget, SLOT(start_clicked()));
        QObject::connect(cancelButton, SIGNAL(clicked()), EraseWidget, SLOT(exit_clicked()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EraseWidget);
    } // setupUi

    void retranslateUi(QWidget *EraseWidget)
    {
        EraseWidget->setWindowTitle(QApplication::translate("EraseWidget", "Form", Q_NULLPTR));
        groupBox_4->setTitle(QString());
        label_16->setText(QApplication::translate("EraseWidget", "Sector:", Q_NULLPTR));
        currentSector->setText(QString());
        logText->setHtml(QApplication::translate("EraseWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p></body></html>", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_log), QApplication::translate("EraseWidget", "\320\237\321\200\320\276\321\202\320\276\320\272\320\276\320\273", Q_NULLPTR));
        startButton->setText(QApplication::translate("EraseWidget", "Start", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("EraseWidget", "Exit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class EraseWidget: public Ui_EraseWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERASETABWIDGET_H
