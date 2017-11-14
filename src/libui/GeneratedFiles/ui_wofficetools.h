/********************************************************************************
** Form generated from reading UI file 'wofficetools.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WOFFICETOOLS_H
#define UI_WOFFICETOOLS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "wselectfolder.h"

QT_BEGIN_NAMESPACE

class Ui_wOfficeTools
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    WSelectFolder *src_folderwidget;
    QSpacerItem *verticalSpacer;
    WSelectFolder *dst_folderwidget;
    QGroupBox *groupBox;
    QRadioButton *sortByDateBtn;
    QRadioButton *splitToFoldersBtn;
    QRadioButton *movToFolderBtn;

    void setupUi(QWidget *wOfficeTools)
    {
        if (wOfficeTools->objectName().isEmpty())
            wOfficeTools->setObjectName(QStringLiteral("wOfficeTools"));
        wOfficeTools->resize(478, 114);
        horizontalLayout = new QHBoxLayout(wOfficeTools);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        src_folderwidget = new WSelectFolder(wOfficeTools);
        src_folderwidget->setObjectName(QStringLiteral("src_folderwidget"));

        verticalLayout_2->addWidget(src_folderwidget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        dst_folderwidget = new WSelectFolder(wOfficeTools);
        dst_folderwidget->setObjectName(QStringLiteral("dst_folderwidget"));

        verticalLayout_2->addWidget(dst_folderwidget);


        horizontalLayout->addLayout(verticalLayout_2);

        groupBox = new QGroupBox(wOfficeTools);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sortByDateBtn = new QRadioButton(groupBox);
        sortByDateBtn->setObjectName(QStringLiteral("sortByDateBtn"));
        sortByDateBtn->setGeometry(QRect(11, 24, 125, 17));
        sortByDateBtn->setChecked(true);
        splitToFoldersBtn = new QRadioButton(groupBox);
        splitToFoldersBtn->setObjectName(QStringLiteral("splitToFoldersBtn"));
        splitToFoldersBtn->setGeometry(QRect(11, 47, 211, 17));
        movToFolderBtn = new QRadioButton(groupBox);
        movToFolderBtn->setObjectName(QStringLiteral("movToFolderBtn"));
        movToFolderBtn->setGeometry(QRect(11, 70, 158, 17));

        horizontalLayout->addWidget(groupBox);


        retranslateUi(wOfficeTools);

        QMetaObject::connectSlotsByName(wOfficeTools);
    } // setupUi

    void retranslateUi(QWidget *wOfficeTools)
    {
        wOfficeTools->setWindowTitle(QApplication::translate("wOfficeTools", "wOfficeTools", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("wOfficeTools", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213:", Q_NULLPTR));
        sortByDateBtn->setText(QApplication::translate("wOfficeTools", "\321\201\320\276\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\277\320\276 \320\264\320\260\321\202\320\265", Q_NULLPTR));
        splitToFoldersBtn->setText(QApplication::translate("wOfficeTools", "\321\200\320\260\321\201\320\277\321\200\320\265\320\264\320\265\320\273\320\270\321\202\321\214 \320\277\320\276 \320\277\320\260\320\277\320\272\320\260\320\274(doc,xls,ppt)", Q_NULLPTR));
        movToFolderBtn->setText(QApplication::translate("wOfficeTools", "\320\277\320\265\321\200\320\265\320\274\320\265\321\201\321\202\320\270\321\202\321\214 \320\262 \320\276\320\264\320\275\321\203 \320\277\320\260\320\277\320\272\321\203", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class wOfficeTools: public Ui_wOfficeTools {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WOFFICETOOLS_H
