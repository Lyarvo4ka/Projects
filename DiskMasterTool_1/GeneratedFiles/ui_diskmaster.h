/********************************************************************************
** Form generated from reading UI file 'diskmaster.ui'
**
** Created: Tue Mar 23 09:58:02 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISKMASTER_H
#define UI_DISKMASTER_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_DiskMasterDialog
{
public:
    QGridLayout *gridLayout;

    void setupUi(QDialog *DiskMasterDialog)
    {
        if (DiskMasterDialog->objectName().isEmpty())
            DiskMasterDialog->setObjectName(QString::fromUtf8("DiskMasterDialog"));
        DiskMasterDialog->setWindowModality(Qt::NonModal);
        DiskMasterDialog->resize(697, 555);
        DiskMasterDialog->setLayoutDirection(Qt::LeftToRight);
        DiskMasterDialog->setAutoFillBackground(false);
        DiskMasterDialog->setStyleSheet(QString::fromUtf8("border-right-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(255, 178, 102, 255), stop:0.55 rgba(235, 148, 61, 255), stop:0.98 rgba(0, 0, 0, 255), stop:1 rgba(0, 0, 0, 0));"));
        DiskMasterDialog->setLocale(QLocale(QLocale::Russian, QLocale::RussianFederation));
        DiskMasterDialog->setSizeGripEnabled(false);
        gridLayout = new QGridLayout(DiskMasterDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        retranslateUi(DiskMasterDialog);

        QMetaObject::connectSlotsByName(DiskMasterDialog);
    } // setupUi

    void retranslateUi(QDialog *DiskMasterDialog)
    {
        DiskMasterDialog->setWindowTitle(QApplication::translate("DiskMasterDialog", "DiskMasterTool", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DiskMasterDialog: public Ui_DiskMasterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISKMASTER_H
