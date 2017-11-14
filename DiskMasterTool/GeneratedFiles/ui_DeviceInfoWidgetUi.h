/********************************************************************************
** Form generated from reading UI file 'DeviceInfoWidgetUi.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICEINFOWIDGETUI_H
#define UI_DEVICEINFOWIDGETUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *diskMasterText;
    QLabel *idText;
    QHBoxLayout *horizontalLayout_2;
    QLabel *statusText;
    QToolButton *toolButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(251, 42);
        horizontalLayout_3 = new QHBoxLayout(Form);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        diskMasterText = new QLabel(Form);
        diskMasterText->setObjectName(QStringLiteral("diskMasterText"));

        horizontalLayout->addWidget(diskMasterText);

        idText = new QLabel(Form);
        idText->setObjectName(QStringLiteral("idText"));

        horizontalLayout->addWidget(idText);


        horizontalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        statusText = new QLabel(Form);
        statusText->setObjectName(QStringLiteral("statusText"));

        horizontalLayout_2->addWidget(statusText);

        toolButton = new QToolButton(Form);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/DiskMasterUI/icons/ready.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon);
        toolButton->setPopupMode(QToolButton::DelayedPopup);

        horizontalLayout_2->addWidget(toolButton);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", Q_NULLPTR));
        diskMasterText->setText(QApplication::translate("Form", "DiskMasterUSB :", Q_NULLPTR));
        idText->setText(QApplication::translate("Form", "id # 0001", Q_NULLPTR));
        statusText->setText(QApplication::translate("Form", "status Ready", Q_NULLPTR));
        toolButton->setText(QApplication::translate("Form", "...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICEINFOWIDGETUI_H
