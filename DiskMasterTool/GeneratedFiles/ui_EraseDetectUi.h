/********************************************************************************
** Form generated from reading UI file 'EraseDetectUi.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERASEDETECTUI_H
#define UI_ERASEDETECTUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include "devicewidget.h"

QT_BEGIN_NAMESPACE

class Ui_EraseDetectUi
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_5;
    QLineEdit *taskNameEdit_;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *workFolderEdit_;
    QToolButton *openFolderButton_2;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QComboBox *verifyCombo_;
    ErasePatternWidget *patternWidget;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *EraseDetectUi)
    {
        if (EraseDetectUi->objectName().isEmpty())
            EraseDetectUi->setObjectName(QStringLiteral("EraseDetectUi"));
        EraseDetectUi->resize(400, 173);
        QIcon icon;
        icon.addFile(QStringLiteral(":/DiskMasterUI/icons/erase_task.png"), QSize(), QIcon::Normal, QIcon::Off);
        EraseDetectUi->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(EraseDetectUi);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_5 = new QLabel(EraseDetectUi);
        label_5->setObjectName(QStringLiteral("label_5"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(label_5);

        taskNameEdit_ = new QLineEdit(EraseDetectUi);
        taskNameEdit_->setObjectName(QStringLiteral("taskNameEdit_"));
        sizePolicy.setHeightForWidth(taskNameEdit_->sizePolicy().hasHeightForWidth());
        taskNameEdit_->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(taskNameEdit_);


        horizontalLayout_6->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_6 = new QLabel(EraseDetectUi);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(label_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        workFolderEdit_ = new QLineEdit(EraseDetectUi);
        workFolderEdit_->setObjectName(QStringLiteral("workFolderEdit_"));

        horizontalLayout_5->addWidget(workFolderEdit_);

        openFolderButton_2 = new QToolButton(EraseDetectUi);
        openFolderButton_2->setObjectName(QStringLiteral("openFolderButton_2"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/DiskMasterUI/icons/folder_home.png"), QSize(), QIcon::Normal, QIcon::Off);
        openFolderButton_2->setIcon(icon1);

        horizontalLayout_5->addWidget(openFolderButton_2);


        verticalLayout_4->addLayout(horizontalLayout_5);


        horizontalLayout_6->addLayout(verticalLayout_4);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        groupBox = new QGroupBox(EraseDetectUi);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(150, 0));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label);

        verifyCombo_ = new QComboBox(groupBox);
        verifyCombo_->setObjectName(QStringLiteral("verifyCombo_"));

        verticalLayout_5->addWidget(verifyCombo_);


        horizontalLayout->addLayout(verticalLayout_5);

        patternWidget = new ErasePatternWidget(groupBox);
        patternWidget->setObjectName(QStringLiteral("patternWidget"));

        horizontalLayout->addWidget(patternWidget);


        horizontalLayout_2->addWidget(groupBox);


        verticalLayout->addLayout(horizontalLayout_2);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(EraseDetectUi);
        okButton->setObjectName(QStringLiteral("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(EraseDetectUi);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        hboxLayout->addWidget(cancelButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(hboxLayout);


        retranslateUi(EraseDetectUi);
        QObject::connect(okButton, SIGNAL(clicked()), EraseDetectUi, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), EraseDetectUi, SLOT(reject()));

        QMetaObject::connectSlotsByName(EraseDetectUi);
    } // setupUi

    void retranslateUi(QDialog *EraseDetectUi)
    {
        EraseDetectUi->setWindowTitle(QApplication::translate("EraseDetectUi", "Erasing", 0));
        label_5->setText(QApplication::translate("EraseDetectUi", "Task name:", 0));
        label_6->setText(QApplication::translate("EraseDetectUi", "<html><head/><body><p>Work folder:</p></body></html>", 0));
        openFolderButton_2->setText(QApplication::translate("EraseDetectUi", "...", 0));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("EraseDetectUi", "Device to erase:", 0));
        okButton->setText(QApplication::translate("EraseDetectUi", "OK", 0));
        cancelButton->setText(QApplication::translate("EraseDetectUi", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class EraseDetectUi: public Ui_EraseDetectUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERASEDETECTUI_H
