/********************************************************************************
** Form generated from reading UI file 'CopyPropertiesDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COPYPROPERTIESDIALOG_H
#define UI_COPYPROPERTIESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "copypropertiesui.h"
#include "copyrangewidget.h"
#include "optionwidget.h"
#include "partitiontreewidget.h"

QT_BEGIN_NAMESPACE

class Ui_CopyPropertiesDlg
{
public:
    QVBoxLayout *verticalLayout_7;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_3;
    CopyPropertiesUi *propertiesWidget;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_3;
    OptionWidget *DeviceOptionsWidget;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *fullCopyButton;
    QRadioButton *partitionCopyButton;
    QRadioButton *userCopyButton;
    QStackedWidget *stackedWidget;
    QWidget *pagefullCopy;
    QVBoxLayout *verticalLayout_2;
    QWidget *pagePartitionCopy;
    QVBoxLayout *verticalLayout_4;
    PartitionTreeWidget *partitionWidget;
    QWidget *pageUserCopy;
    QVBoxLayout *verticalLayout_5;
    CopyRangeWidget *rangeWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;

    void setupUi(QDialog *CopyPropertiesDlg)
    {
        if (CopyPropertiesDlg->objectName().isEmpty())
            CopyPropertiesDlg->setObjectName(QStringLiteral("CopyPropertiesDlg"));
        CopyPropertiesDlg->setEnabled(true);
        CopyPropertiesDlg->resize(530, 349);
        verticalLayout_7 = new QVBoxLayout(CopyPropertiesDlg);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        tabWidget = new QTabWidget(CopyPropertiesDlg);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_8 = new QVBoxLayout(tab);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        propertiesWidget = new CopyPropertiesUi(tab);
        propertiesWidget->setObjectName(QStringLiteral("propertiesWidget"));

        horizontalLayout_3->addWidget(propertiesWidget);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_8->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 182, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer);

        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        verticalLayout_3 = new QVBoxLayout(tab_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        DeviceOptionsWidget = new OptionWidget(tab_3);
        DeviceOptionsWidget->setObjectName(QStringLiteral("DeviceOptionsWidget"));

        verticalLayout_3->addWidget(DeviceOptionsWidget);

        tabWidget->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_6 = new QVBoxLayout(tab_2);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        fullCopyButton = new QRadioButton(groupBox);
        fullCopyButton->setObjectName(QStringLiteral("fullCopyButton"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/DiskMasterUI/icons/hard_drive_clone.png"), QSize(), QIcon::Normal, QIcon::Off);
        fullCopyButton->setIcon(icon);
        fullCopyButton->setIconSize(QSize(24, 24));
        fullCopyButton->setChecked(true);

        verticalLayout->addWidget(fullCopyButton);

        partitionCopyButton = new QRadioButton(groupBox);
        partitionCopyButton->setObjectName(QStringLiteral("partitionCopyButton"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/DiskMasterUI/icons/Partition.png"), QSize(), QIcon::Normal, QIcon::Off);
        partitionCopyButton->setIcon(icon1);
        partitionCopyButton->setIconSize(QSize(24, 24));

        verticalLayout->addWidget(partitionCopyButton);

        userCopyButton = new QRadioButton(groupBox);
        userCopyButton->setObjectName(QStringLiteral("userCopyButton"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/DiskMasterUI/icons/user_copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        userCopyButton->setIcon(icon2);
        userCopyButton->setIconSize(QSize(24, 24));

        verticalLayout->addWidget(userCopyButton);


        horizontalLayout_2->addWidget(groupBox);

        stackedWidget = new QStackedWidget(tab_2);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setFrameShape(QFrame::Box);
        stackedWidget->setFrameShadow(QFrame::Plain);
        pagefullCopy = new QWidget();
        pagefullCopy->setObjectName(QStringLiteral("pagefullCopy"));
        verticalLayout_2 = new QVBoxLayout(pagefullCopy);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        stackedWidget->addWidget(pagefullCopy);
        pagePartitionCopy = new QWidget();
        pagePartitionCopy->setObjectName(QStringLiteral("pagePartitionCopy"));
        verticalLayout_4 = new QVBoxLayout(pagePartitionCopy);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        partitionWidget = new PartitionTreeWidget(pagePartitionCopy);
        partitionWidget->setObjectName(QStringLiteral("partitionWidget"));

        verticalLayout_4->addWidget(partitionWidget);

        stackedWidget->addWidget(pagePartitionCopy);
        pageUserCopy = new QWidget();
        pageUserCopy->setObjectName(QStringLiteral("pageUserCopy"));
        verticalLayout_5 = new QVBoxLayout(pageUserCopy);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        rangeWidget = new CopyRangeWidget(pageUserCopy);
        rangeWidget->setObjectName(QStringLiteral("rangeWidget"));
        rangeWidget->setEnabled(false);

        verticalLayout_5->addWidget(rangeWidget);

        stackedWidget->addWidget(pageUserCopy);

        horizontalLayout_2->addWidget(stackedWidget);


        verticalLayout_6->addLayout(horizontalLayout_2);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_7->addWidget(tabWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okButton = new QPushButton(CopyPropertiesDlg);
        okButton->setObjectName(QStringLiteral("okButton"));

        horizontalLayout->addWidget(okButton);


        verticalLayout_7->addLayout(horizontalLayout);


        retranslateUi(CopyPropertiesDlg);
        QObject::connect(okButton, SIGNAL(clicked()), CopyPropertiesDlg, SLOT(accept()));

        tabWidget->setCurrentIndex(2);
        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CopyPropertiesDlg);
    } // setupUi

    void retranslateUi(QDialog *CopyPropertiesDlg)
    {
        CopyPropertiesDlg->setWindowTitle(QApplication::translate("CopyPropertiesDlg", "Copy settings", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("CopyPropertiesDlg", "Main parameters", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("CopyPropertiesDlg", "DiskMaster options", Q_NULLPTR));
        groupBox->setTitle(QString());
        fullCopyButton->setText(QApplication::translate("CopyPropertiesDlg", "Full copy", Q_NULLPTR));
        partitionCopyButton->setText(QApplication::translate("CopyPropertiesDlg", "Partition copy", Q_NULLPTR));
        userCopyButton->setText(QApplication::translate("CopyPropertiesDlg", "User copy", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("CopyPropertiesDlg", "Copy options", Q_NULLPTR));
        okButton->setText(QApplication::translate("CopyPropertiesDlg", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CopyPropertiesDlg: public Ui_CopyPropertiesDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPYPROPERTIESDIALOG_H
