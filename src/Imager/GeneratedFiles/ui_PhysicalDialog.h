/********************************************************************************
** Form generated from reading UI file 'PhysicalDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PHYSICALDIALOG_H
#define UI_PHYSICALDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "devicetableview.h"

QT_BEGIN_NAMESPACE

class Ui_PhysicalDialog
{
public:
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_6;
    QLabel *TargetText;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_2;
    TargetTableView *DeviceTable;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *PathToLog;
    QToolButton *pathlButton;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *checkBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *SourceStartSector;
    QLabel *label_2;
    QLineEdit *TargetStartSector;
    QLabel *label_3;
    QLineEdit *SectorsCount;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *PhysicalDialog)
    {
        if (PhysicalDialog->objectName().isEmpty())
            PhysicalDialog->setObjectName(QStringLiteral("PhysicalDialog"));
        PhysicalDialog->resize(739, 267);
        gridLayout_4 = new QGridLayout(PhysicalDialog);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        TargetText = new QLabel(PhysicalDialog);
        TargetText->setObjectName(QStringLiteral("TargetText"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        TargetText->setFont(font);

        verticalLayout_6->addWidget(TargetText);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        DeviceTable = new TargetTableView(PhysicalDialog);
        DeviceTable->setObjectName(QStringLiteral("DeviceTable"));

        verticalLayout_2->addWidget(DeviceTable);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(488, 31, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label_4 = new QLabel(PhysicalDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        PathToLog = new QLineEdit(PhysicalDialog);
        PathToLog->setObjectName(QStringLiteral("PathToLog"));

        horizontalLayout_2->addWidget(PathToLog);

        pathlButton = new QToolButton(PhysicalDialog);
        pathlButton->setObjectName(QStringLiteral("pathlButton"));

        horizontalLayout_2->addWidget(pathlButton);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);


        gridLayout_3->addLayout(verticalLayout_2, 0, 0, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        groupBox = new QGroupBox(PhysicalDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        splitter = new QSplitter(groupBox);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        checkBox = new QCheckBox(layoutWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setChecked(true);

        verticalLayout_3->addWidget(checkBox);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(false);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        SourceStartSector = new QLineEdit(layoutWidget);
        SourceStartSector->setObjectName(QStringLiteral("SourceStartSector"));
        SourceStartSector->setEnabled(false);

        gridLayout->addWidget(SourceStartSector, 0, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setEnabled(false);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        TargetStartSector = new QLineEdit(layoutWidget);
        TargetStartSector->setObjectName(QStringLiteral("TargetStartSector"));
        TargetStartSector->setEnabled(false);

        gridLayout->addWidget(TargetStartSector, 1, 1, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setEnabled(false);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        SectorsCount = new QLineEdit(layoutWidget);
        SectorsCount->setObjectName(QStringLiteral("SectorsCount"));
        SectorsCount->setEnabled(false);

        gridLayout->addWidget(SectorsCount, 2, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout);

        splitter->addWidget(layoutWidget);

        gridLayout_2->addWidget(splitter, 0, 0, 1, 1);


        verticalLayout_4->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);


        verticalLayout_5->addLayout(verticalLayout_4);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okButton = new QPushButton(PhysicalDialog);
        okButton->setObjectName(QStringLiteral("okButton"));

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(PhysicalDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout->addWidget(cancelButton);


        verticalLayout_5->addLayout(horizontalLayout);


        gridLayout_3->addLayout(verticalLayout_5, 0, 1, 1, 1);


        verticalLayout_6->addLayout(gridLayout_3);


        gridLayout_4->addLayout(verticalLayout_6, 0, 0, 1, 1);


        retranslateUi(PhysicalDialog);
        QObject::connect(okButton, SIGNAL(clicked()), PhysicalDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), PhysicalDialog, SLOT(reject()));
        QObject::connect(checkBox, SIGNAL(clicked(bool)), SourceStartSector, SLOT(setDisabled(bool)));
        QObject::connect(checkBox, SIGNAL(clicked(bool)), label, SLOT(setDisabled(bool)));
        QObject::connect(checkBox, SIGNAL(clicked(bool)), label_2, SLOT(setDisabled(bool)));
        QObject::connect(checkBox, SIGNAL(clicked(bool)), TargetStartSector, SLOT(setDisabled(bool)));
        QObject::connect(checkBox, SIGNAL(clicked(bool)), label_3, SLOT(setDisabled(bool)));
        QObject::connect(checkBox, SIGNAL(clicked(bool)), SectorsCount, SLOT(setDisabled(bool)));
        QObject::connect(DeviceTable, SIGNAL(clicked(QModelIndex)), PhysicalDialog, SLOT(OnSelectTarget(QModelIndex)));
        QObject::connect(pathlButton, SIGNAL(clicked()), PhysicalDialog, SLOT(OnOpenLogFile()));

        QMetaObject::connectSlotsByName(PhysicalDialog);
    } // setupUi

    void retranslateUi(QDialog *PhysicalDialog)
    {
        PhysicalDialog->setWindowTitle(QApplication::translate("PhysicalDialog", "Dialog", 0));
        TargetText->setText(QApplication::translate("PhysicalDialog", "Target devices", 0));
        label_4->setText(QApplication::translate("PhysicalDialog", "<html><head/><body><p><span style=\" font-weight:600;\">Path to log-file</span></p></body></html>", 0));
        pathlButton->setText(QApplication::translate("PhysicalDialog", "...", 0));
        groupBox->setTitle(QString());
        checkBox->setText(QApplication::translate("PhysicalDialog", "Full copy", 0));
        label->setText(QApplication::translate("PhysicalDialog", "<html><head/><body><p>Start setor (<span style=\" font-weight:600; text-decoration: underline;\">source</span>)</p></body></html>", 0));
        SourceStartSector->setText(QApplication::translate("PhysicalDialog", "0", 0));
        label_2->setText(QApplication::translate("PhysicalDialog", "<html><head/><body><p>Start sector (<span style=\" font-weight:600; text-decoration: underline;\">target</span>)</p></body></html>", 0));
        TargetStartSector->setText(QApplication::translate("PhysicalDialog", "0", 0));
        label_3->setText(QApplication::translate("PhysicalDialog", "Sectors Count", 0));
        SectorsCount->setText(QApplication::translate("PhysicalDialog", "0", 0));
        okButton->setText(QApplication::translate("PhysicalDialog", "OK", 0));
        cancelButton->setText(QApplication::translate("PhysicalDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class PhysicalDialog: public Ui_PhysicalDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PHYSICALDIALOG_H
