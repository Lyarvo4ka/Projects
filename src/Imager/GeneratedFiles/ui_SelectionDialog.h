/********************************************************************************
** Form generated from reading UI file 'SelectionDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTIONDIALOG_H
#define UI_SELECTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "devicetableview.h"

QT_BEGIN_NAMESPACE

class Ui_SelectionDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *SourceText;
    DeviceTableView *DeviceTable;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *SelectionDialog)
    {
        if (SelectionDialog->objectName().isEmpty())
            SelectionDialog->setObjectName(QStringLiteral("SelectionDialog"));
        SelectionDialog->resize(607, 394);
        SelectionDialog->setModal(true);
        verticalLayout = new QVBoxLayout(SelectionDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        SourceText = new QLabel(SelectionDialog);
        SourceText->setObjectName(QStringLiteral("SourceText"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        SourceText->setFont(font);

        verticalLayout->addWidget(SourceText);

        DeviceTable = new DeviceTableView(SelectionDialog);
        DeviceTable->setObjectName(QStringLiteral("DeviceTable"));

        verticalLayout->addWidget(DeviceTable);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(SelectionDialog);
        okButton->setObjectName(QStringLiteral("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(SelectionDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        verticalLayout->addLayout(hboxLayout);


        retranslateUi(SelectionDialog);
        QObject::connect(okButton, SIGNAL(clicked()), SelectionDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), SelectionDialog, SLOT(reject()));
        QObject::connect(DeviceTable, SIGNAL(doubleClicked(QModelIndex)), SelectionDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(SelectionDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectionDialog)
    {
        SelectionDialog->setWindowTitle(QApplication::translate("SelectionDialog", "Select Device", Q_NULLPTR));
        SourceText->setText(QApplication::translate("SelectionDialog", "Source Devices", Q_NULLPTR));
        okButton->setText(QApplication::translate("SelectionDialog", "OK", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("SelectionDialog", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SelectionDialog: public Ui_SelectionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTIONDIALOG_H
