/********************************************************************************
** Form generated from reading UI file 'CopyRangeWidgetUi.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COPYRANGEWIDGETUI_H
#define UI_COPYRANGEWIDGETUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_copyRangeWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *verticalLayout_6;
    QLabel *labelSourceOffset;
    QLineEdit *sourceOffset;
    QVBoxLayout *verticalLayout_7;
    QLabel *labelTargetOffset;
    QLineEdit *targetOffset;
    QVBoxLayout *verticalLayout_8;
    QLabel *labelSectorsCount;
    QLineEdit *sectorsCount;

    void setupUi(QWidget *copyRangeWidget)
    {
        if (copyRangeWidget->objectName().isEmpty())
            copyRangeWidget->setObjectName(QStringLiteral("copyRangeWidget"));
        copyRangeWidget->resize(189, 156);
        verticalLayout = new QVBoxLayout(copyRangeWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(copyRangeWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setCheckable(false);
        groupBox->setChecked(false);
        verticalLayout_9 = new QVBoxLayout(groupBox);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setSizeConstraint(QLayout::SetFixedSize);
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(2);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        labelSourceOffset = new QLabel(groupBox);
        labelSourceOffset->setObjectName(QStringLiteral("labelSourceOffset"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelSourceOffset->sizePolicy().hasHeightForWidth());
        labelSourceOffset->setSizePolicy(sizePolicy1);

        verticalLayout_6->addWidget(labelSourceOffset);

        sourceOffset = new QLineEdit(groupBox);
        sourceOffset->setObjectName(QStringLiteral("sourceOffset"));

        verticalLayout_6->addWidget(sourceOffset);


        verticalLayout_9->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(2);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        labelTargetOffset = new QLabel(groupBox);
        labelTargetOffset->setObjectName(QStringLiteral("labelTargetOffset"));
        sizePolicy1.setHeightForWidth(labelTargetOffset->sizePolicy().hasHeightForWidth());
        labelTargetOffset->setSizePolicy(sizePolicy1);

        verticalLayout_7->addWidget(labelTargetOffset);

        targetOffset = new QLineEdit(groupBox);
        targetOffset->setObjectName(QStringLiteral("targetOffset"));

        verticalLayout_7->addWidget(targetOffset);


        verticalLayout_9->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(2);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        labelSectorsCount = new QLabel(groupBox);
        labelSectorsCount->setObjectName(QStringLiteral("labelSectorsCount"));
        sizePolicy1.setHeightForWidth(labelSectorsCount->sizePolicy().hasHeightForWidth());
        labelSectorsCount->setSizePolicy(sizePolicy1);

        verticalLayout_8->addWidget(labelSectorsCount);

        sectorsCount = new QLineEdit(groupBox);
        sectorsCount->setObjectName(QStringLiteral("sectorsCount"));

        verticalLayout_8->addWidget(sectorsCount);


        verticalLayout_9->addLayout(verticalLayout_8);


        verticalLayout->addWidget(groupBox);


        retranslateUi(copyRangeWidget);

        QMetaObject::connectSlotsByName(copyRangeWidget);
    } // setupUi

    void retranslateUi(QWidget *copyRangeWidget)
    {
        copyRangeWidget->setWindowTitle(QApplication::translate("copyRangeWidget", "Form", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("copyRangeWidget", "The boundaries of copying", Q_NULLPTR));
        labelSourceOffset->setText(QApplication::translate("copyRangeWidget", "Source offset:", Q_NULLPTR));
        labelTargetOffset->setText(QApplication::translate("copyRangeWidget", "Target offset:", Q_NULLPTR));
        labelSectorsCount->setText(QApplication::translate("copyRangeWidget", "Number of sectors:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class copyRangeWidget: public Ui_copyRangeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPYRANGEWIDGETUI_H
