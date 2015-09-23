/********************************************************************************
** Form generated from reading UI file 'CopyPropertiesUi.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COPYPROPERTIESUI_H
#define UI_COPYPROPERTIESUI_H

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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CopyPropertiesWidget
{
public:
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *jumpSizeBox;
    QLabel *label_4;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_5;
    QComboBox *directionCombo;
    QSpacerItem *horizontalSpacer;
    QFrame *line_2;
    QCheckBox *readUnread;

    void setupUi(QWidget *CopyPropertiesWidget)
    {
        if (CopyPropertiesWidget->objectName().isEmpty())
            CopyPropertiesWidget->setObjectName(QStringLiteral("CopyPropertiesWidget"));
        CopyPropertiesWidget->resize(263, 168);
        verticalLayout_4 = new QVBoxLayout(CopyPropertiesWidget);
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        groupBox = new QGroupBox(CopyPropertiesWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(label_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        jumpSizeBox = new QSpinBox(groupBox);
        jumpSizeBox->setObjectName(QStringLiteral("jumpSizeBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(jumpSizeBox->sizePolicy().hasHeightForWidth());
        jumpSizeBox->setSizePolicy(sizePolicy1);
        jumpSizeBox->setMaximum(999999999);
        jumpSizeBox->setValue(16);

        horizontalLayout_2->addWidget(jumpSizeBox);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_4);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout_7->addLayout(verticalLayout_2);


        verticalLayout->addLayout(verticalLayout_7);

        line = new QFrame(groupBox);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setEnabled(false);
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(label_5);

        directionCombo = new QComboBox(groupBox);
        directionCombo->setObjectName(QStringLiteral("directionCombo"));
        directionCombo->setEnabled(false);

        verticalLayout_3->addWidget(directionCombo);


        horizontalLayout->addLayout(verticalLayout_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        line_2 = new QFrame(groupBox);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        readUnread = new QCheckBox(groupBox);
        readUnread->setObjectName(QStringLiteral("readUnread"));
        readUnread->setChecked(true);

        verticalLayout->addWidget(readUnread);

        line->raise();
        line_2->raise();
        readUnread->raise();

        verticalLayout_4->addWidget(groupBox);


        retranslateUi(CopyPropertiesWidget);
        QObject::connect(jumpSizeBox, SIGNAL(valueChanged(int)), CopyPropertiesWidget, SLOT(JumpSizeChanged(int)));
        QObject::connect(directionCombo, SIGNAL(currentIndexChanged(int)), CopyPropertiesWidget, SLOT(DirectionChanged(int)));
        QObject::connect(readUnread, SIGNAL(stateChanged(int)), CopyPropertiesWidget, SLOT(ReadUnReadChanged(int)));

        QMetaObject::connectSlotsByName(CopyPropertiesWidget);
    } // setupUi

    void retranslateUi(QWidget *CopyPropertiesWidget)
    {
        CopyPropertiesWidget->setWindowTitle(QApplication::translate("CopyPropertiesWidget", "Form", 0));
        groupBox->setTitle(QApplication::translate("CopyPropertiesWidget", "Copy options", 0));
        label_3->setText(QApplication::translate("CopyPropertiesWidget", "Jump size when bad sector", 0));
        label_4->setText(QApplication::translate("CopyPropertiesWidget", "( sectors )", 0));
        label_5->setText(QApplication::translate("CopyPropertiesWidget", "Copy direction", 0));
        readUnread->setText(QApplication::translate("CopyPropertiesWidget", "Reread unread", 0));
    } // retranslateUi

};

namespace Ui {
    class CopyPropertiesWidget: public Ui_CopyPropertiesWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPYPROPERTIESUI_H
