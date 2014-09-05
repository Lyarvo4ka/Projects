/********************************************************************************
** Form generated from reading UI file 'DiskMasterTool.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISKMASTERTOOL_H
#define UI_DISKMASTERTOOL_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_DiskMasterDialog
{
public:
    QGridLayout *gridLayout;

    void setupUi(QDialog *DiskMasterDialog)
    {
        if (DiskMasterDialog->objectName().isEmpty())
            DiskMasterDialog->setObjectName(QStringLiteral("DiskMasterDialog"));
        DiskMasterDialog->setWindowModality(Qt::NonModal);
        DiskMasterDialog->resize(697, 555);
        QIcon icon;
        icon.addFile(QStringLiteral(":/DiskMaster/diskmaster.png"), QSize(), QIcon::Normal, QIcon::Off);
        DiskMasterDialog->setWindowIcon(icon);
        DiskMasterDialog->setLayoutDirection(Qt::LeftToRight);
        DiskMasterDialog->setAutoFillBackground(false);
        DiskMasterDialog->setStyleSheet(QStringLiteral("border-right-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(255, 178, 102, 255), stop:0.55 rgba(235, 148, 61, 255), stop:0.98 rgba(0, 0, 0, 255), stop:1 rgba(0, 0, 0, 0));"));
        DiskMasterDialog->setLocale(QLocale(QLocale::Russian, QLocale::RussianFederation));
        DiskMasterDialog->setSizeGripEnabled(false);
        gridLayout = new QGridLayout(DiskMasterDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));

        retranslateUi(DiskMasterDialog);

        QMetaObject::connectSlotsByName(DiskMasterDialog);
    } // setupUi

    void retranslateUi(QDialog *DiskMasterDialog)
    {
        DiskMasterDialog->setWindowTitle(QApplication::translate("DiskMasterDialog", "DiskMasterTool", 0));
    } // retranslateUi

};

namespace Ui {
    class DiskMasterDialog: public Ui_DiskMasterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISKMASTERTOOL_H
