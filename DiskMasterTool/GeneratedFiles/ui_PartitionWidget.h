/********************************************************************************
** Form generated from reading UI file 'PartitionWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARTITIONWIDGET_H
#define UI_PARTITIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PartitionForm
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QTreeView *treeView;

    void setupUi(QWidget *PartitionForm)
    {
        if (PartitionForm->objectName().isEmpty())
            PartitionForm->setObjectName(QStringLiteral("PartitionForm"));
        PartitionForm->resize(626, 282);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PartitionForm->sizePolicy().hasHeightForWidth());
        PartitionForm->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(PartitionForm);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(PartitionForm);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setCheckable(false);
        groupBox->setChecked(false);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        treeView = new QTreeView(groupBox);
        treeView->setObjectName(QStringLiteral("treeView"));
        sizePolicy.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
        treeView->setSizePolicy(sizePolicy);
        treeView->setMinimumSize(QSize(0, 0));
        treeView->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout->addWidget(treeView);


        verticalLayout_2->addWidget(groupBox);


        retranslateUi(PartitionForm);

        QMetaObject::connectSlotsByName(PartitionForm);
    } // setupUi

    void retranslateUi(QWidget *PartitionForm)
    {
        PartitionForm->setWindowTitle(QApplication::translate("PartitionForm", "Form", 0));
        groupBox->setTitle(QApplication::translate("PartitionForm", "Partition copy", 0));
    } // retranslateUi

};

namespace Ui {
    class PartitionForm: public Ui_PartitionForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARTITIONWIDGET_H
