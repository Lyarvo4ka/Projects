/********************************************************************************
** Form generated from reading UI file 'OptionsWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONSWIDGET_H
#define UI_OPTIONSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OptionWidgetForm
{
public:
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QSpinBox *blockSizeEdit;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *NumRepeatRdEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *BadMarkerCmbBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpinBox *ShkPwrLimitEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *RdTimeLimitEdit;
    QFrame *line;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *ChirpCheck;
    QCheckBox *EndBeepCheck;
    QCheckBox *CrcBeepCheck;

    void setupUi(QWidget *OptionWidgetForm)
    {
        if (OptionWidgetForm->objectName().isEmpty())
            OptionWidgetForm->setObjectName(QStringLiteral("OptionWidgetForm"));
        OptionWidgetForm->resize(293, 169);
        verticalLayout_3 = new QVBoxLayout(OptionWidgetForm);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(OptionWidgetForm);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_6 = new QHBoxLayout(groupBox);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        blockSizeEdit = new QSpinBox(groupBox);
        blockSizeEdit->setObjectName(QStringLiteral("blockSizeEdit"));

        horizontalLayout_5->addWidget(blockSizeEdit);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        NumRepeatRdEdit = new QSpinBox(groupBox);
        NumRepeatRdEdit->setObjectName(QStringLiteral("NumRepeatRdEdit"));
        NumRepeatRdEdit->setEnabled(false);
        NumRepeatRdEdit->setMinimum(1);
        NumRepeatRdEdit->setMaximum(10);

        horizontalLayout->addWidget(NumRepeatRdEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        BadMarkerCmbBox = new QComboBox(groupBox);
        BadMarkerCmbBox->setObjectName(QStringLiteral("BadMarkerCmbBox"));
        BadMarkerCmbBox->setEnabled(false);

        horizontalLayout_4->addWidget(BadMarkerCmbBox);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        ShkPwrLimitEdit = new QSpinBox(groupBox);
        ShkPwrLimitEdit->setObjectName(QStringLiteral("ShkPwrLimitEdit"));
        ShkPwrLimitEdit->setEnabled(false);
        ShkPwrLimitEdit->setMinimum(10);
        ShkPwrLimitEdit->setMaximum(100);

        horizontalLayout_3->addWidget(ShkPwrLimitEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        RdTimeLimitEdit = new QSpinBox(groupBox);
        RdTimeLimitEdit->setObjectName(QStringLiteral("RdTimeLimitEdit"));
        RdTimeLimitEdit->setEnabled(false);
        RdTimeLimitEdit->setMinimum(3000);
        RdTimeLimitEdit->setMaximum(15000);

        horizontalLayout_2->addWidget(RdTimeLimitEdit);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_6->addLayout(verticalLayout);

        line = new QFrame(groupBox);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_6->addWidget(line);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        ChirpCheck = new QCheckBox(groupBox);
        ChirpCheck->setObjectName(QStringLiteral("ChirpCheck"));
        ChirpCheck->setCheckable(true);
        ChirpCheck->setChecked(false);
        ChirpCheck->setTristate(false);

        verticalLayout_2->addWidget(ChirpCheck);

        EndBeepCheck = new QCheckBox(groupBox);
        EndBeepCheck->setObjectName(QStringLiteral("EndBeepCheck"));
        EndBeepCheck->setChecked(false);

        verticalLayout_2->addWidget(EndBeepCheck);

        CrcBeepCheck = new QCheckBox(groupBox);
        CrcBeepCheck->setObjectName(QStringLiteral("CrcBeepCheck"));
        CrcBeepCheck->setChecked(false);

        verticalLayout_2->addWidget(CrcBeepCheck);


        horizontalLayout_6->addLayout(verticalLayout_2);


        verticalLayout_3->addWidget(groupBox);


        retranslateUi(OptionWidgetForm);

        QMetaObject::connectSlotsByName(OptionWidgetForm);
    } // setupUi

    void retranslateUi(QWidget *OptionWidgetForm)
    {
        OptionWidgetForm->setWindowTitle(QApplication::translate("OptionWidgetForm", "Form", 0));
        groupBox->setTitle(QApplication::translate("OptionWidgetForm", "Disk Master Options", 0));
        label_5->setText(QApplication::translate("OptionWidgetForm", "Block size", 0));
        label->setText(QApplication::translate("OptionWidgetForm", "Number of read bad sectors:", 0));
        label_4->setText(QApplication::translate("OptionWidgetForm", "Bad sectors marker", 0));
        label_3->setText(QApplication::translate("OptionWidgetForm", "Shake power limit", 0));
        label_2->setText(QApplication::translate("OptionWidgetForm", "Limit time to read:", 0));
        ChirpCheck->setText(QApplication::translate("OptionWidgetForm", "Chirp", 0));
        EndBeepCheck->setText(QApplication::translate("OptionWidgetForm", "End Beep", 0));
        CrcBeepCheck->setText(QApplication::translate("OptionWidgetForm", "CRC Beep", 0));
    } // retranslateUi

};

namespace Ui {
    class OptionWidgetForm: public Ui_OptionWidgetForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSWIDGET_H
