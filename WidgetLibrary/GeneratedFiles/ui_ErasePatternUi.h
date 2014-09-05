/********************************************************************************
** Form generated from reading UI file 'ErasePatternUi.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERASEPATTERNUI_H
#define UI_ERASEPATTERNUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widget
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *button_00;
    QRadioButton *button_FF;
    QRadioButton *button_RAND;

    void setupUi(QWidget *widget)
    {
        if (widget->objectName().isEmpty())
            widget->setObjectName(QStringLiteral("widget"));
        widget->resize(94, 96);
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        button_00 = new QRadioButton(groupBox);
        button_00->setObjectName(QStringLiteral("button_00"));
        button_00->setChecked(true);

        verticalLayout->addWidget(button_00);

        button_FF = new QRadioButton(groupBox);
        button_FF->setObjectName(QStringLiteral("button_FF"));

        verticalLayout->addWidget(button_FF);

        button_RAND = new QRadioButton(groupBox);
        button_RAND->setObjectName(QStringLiteral("button_RAND"));

        verticalLayout->addWidget(button_RAND);


        verticalLayout_2->addWidget(groupBox);


        retranslateUi(widget);

        QMetaObject::connectSlotsByName(widget);
    } // setupUi

    void retranslateUi(QWidget *widget)
    {
        widget->setWindowTitle(QApplication::translate("widget", "Form", 0));
        groupBox->setTitle(QApplication::translate("widget", "Erase pattern", 0));
        button_00->setText(QApplication::translate("widget", "0x00", 0));
        button_FF->setText(QApplication::translate("widget", "0xFF", 0));
        button_RAND->setText(QApplication::translate("widget", "Random", 0));
    } // retranslateUi

};

namespace Ui {
    class widget: public Ui_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERASEPATTERNUI_H
