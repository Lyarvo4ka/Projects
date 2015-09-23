/********************************************************************************
** Form generated from reading UI file 'ModifySectorUi.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIFYSECTORUI_H
#define UI_MODIFYSECTORUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "devicewidget.h"

QT_BEGIN_NAMESPACE

class Ui_ModifySectorUi
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    DeviceWidget *modifyDevice;
    QVBoxLayout *verticalLayout;
    QPushButton *ModifyButton;
    QPushButton *WriteButton;
    QPushButton *VerifyButton;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;

    void setupUi(QDialog *ModifySectorUi)
    {
        if (ModifySectorUi->objectName().isEmpty())
            ModifySectorUi->setObjectName(QStringLiteral("ModifySectorUi"));
        ModifySectorUi->resize(389, 134);
        verticalLayout_2 = new QVBoxLayout(ModifySectorUi);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        modifyDevice = new DeviceWidget(ModifySectorUi);
        modifyDevice->setObjectName(QStringLiteral("modifyDevice"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(modifyDevice->sizePolicy().hasHeightForWidth());
        modifyDevice->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(modifyDevice);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        ModifyButton = new QPushButton(ModifySectorUi);
        ModifyButton->setObjectName(QStringLiteral("ModifyButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ModifyButton->sizePolicy().hasHeightForWidth());
        ModifyButton->setSizePolicy(sizePolicy1);
        ModifyButton->setCheckable(false);
        ModifyButton->setAutoRepeat(false);
        ModifyButton->setFlat(false);

        verticalLayout->addWidget(ModifyButton);

        WriteButton = new QPushButton(ModifySectorUi);
        WriteButton->setObjectName(QStringLiteral("WriteButton"));
        sizePolicy1.setHeightForWidth(WriteButton->sizePolicy().hasHeightForWidth());
        WriteButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(WriteButton);

        VerifyButton = new QPushButton(ModifySectorUi);
        VerifyButton->setObjectName(QStringLiteral("VerifyButton"));
        sizePolicy1.setHeightForWidth(VerifyButton->sizePolicy().hasHeightForWidth());
        VerifyButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(VerifyButton);


        horizontalLayout_2->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okButton = new QPushButton(ModifySectorUi);
        okButton->setObjectName(QStringLiteral("okButton"));

        horizontalLayout->addWidget(okButton);


        verticalLayout_2->addLayout(horizontalLayout);

        QWidget::setTabOrder(ModifyButton, WriteButton);
        QWidget::setTabOrder(WriteButton, VerifyButton);
        QWidget::setTabOrder(VerifyButton, okButton);

        retranslateUi(ModifySectorUi);
        QObject::connect(okButton, SIGNAL(clicked()), ModifySectorUi, SLOT(accept()));

        ModifyButton->setDefault(false);


        QMetaObject::connectSlotsByName(ModifySectorUi);
    } // setupUi

    void retranslateUi(QDialog *ModifySectorUi)
    {
        ModifySectorUi->setWindowTitle(QApplication::translate("ModifySectorUi", "Dialog", 0));
        ModifyButton->setText(QApplication::translate("ModifySectorUi", "Modify", 0));
        WriteButton->setText(QApplication::translate("ModifySectorUi", "Write signature", 0));
        VerifyButton->setText(QApplication::translate("ModifySectorUi", "Check signature", 0));
        okButton->setText(QApplication::translate("ModifySectorUi", "Exit", 0));
    } // retranslateUi

};

namespace Ui {
    class ModifySectorUi: public Ui_ModifySectorUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFYSECTORUI_H
