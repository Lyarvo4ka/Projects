/********************************************************************************
** Form generated from reading UI file 'MainTaskPanel.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINTASKPANEL_H
#define UI_MAINTASKPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainTaskWidget
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QTreeView *treeView;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QToolButton *CopylButton;
    QToolButton *VerifylButton;
    QToolButton *EraseButton;
    QToolButton *modifyMBRButton;

    void setupUi(QWidget *MainTaskWidget)
    {
        if (MainTaskWidget->objectName().isEmpty())
            MainTaskWidget->setObjectName(QStringLiteral("MainTaskWidget"));
        MainTaskWidget->setEnabled(true);
        MainTaskWidget->resize(600, 386);
        MainTaskWidget->setMinimumSize(QSize(600, 200));
        gridLayout = new QGridLayout(MainTaskWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(MainTaskWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        treeView = new QTreeView(groupBox);
        treeView->setObjectName(QStringLiteral("treeView"));
        QFont font;
        font.setFamily(QStringLiteral("MS Shell Dlg 2"));
        font.setPointSize(8);
        font.setBold(false);
        font.setWeight(50);
        font.setStyleStrategy(QFont::PreferAntialias);
        treeView->setFont(font);
        treeView->setSelectionMode(QAbstractItemView::SingleSelection);
        treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
        treeView->setIconSize(QSize(20, 20));
        treeView->setIndentation(20);
        treeView->setRootIsDecorated(true);
        treeView->setUniformRowHeights(false);
        treeView->setAnimated(true);

        horizontalLayout->addWidget(treeView);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(MainTaskWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        CopylButton = new QToolButton(groupBox_2);
        CopylButton->setObjectName(QStringLiteral("CopylButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(CopylButton->sizePolicy().hasHeightForWidth());
        CopylButton->setSizePolicy(sizePolicy1);
        QIcon icon;
        icon.addFile(QStringLiteral(":/DiskMasterUI/icons/copy_disk.png"), QSize(), QIcon::Normal, QIcon::Off);
        CopylButton->setIcon(icon);
        CopylButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        verticalLayout->addWidget(CopylButton);

        VerifylButton = new QToolButton(groupBox_2);
        VerifylButton->setObjectName(QStringLiteral("VerifylButton"));
        sizePolicy1.setHeightForWidth(VerifylButton->sizePolicy().hasHeightForWidth());
        VerifylButton->setSizePolicy(sizePolicy1);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/DiskMasterUI/icons/verify_task.png"), QSize(), QIcon::Normal, QIcon::Off);
        VerifylButton->setIcon(icon1);
        VerifylButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        verticalLayout->addWidget(VerifylButton);

        EraseButton = new QToolButton(groupBox_2);
        EraseButton->setObjectName(QStringLiteral("EraseButton"));
        sizePolicy1.setHeightForWidth(EraseButton->sizePolicy().hasHeightForWidth());
        EraseButton->setSizePolicy(sizePolicy1);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/DiskMasterUI/icons/erase_task.png"), QSize(), QIcon::Normal, QIcon::Off);
        EraseButton->setIcon(icon2);
        EraseButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        verticalLayout->addWidget(EraseButton);

        modifyMBRButton = new QToolButton(groupBox_2);
        modifyMBRButton->setObjectName(QStringLiteral("modifyMBRButton"));
        modifyMBRButton->setEnabled(true);
        sizePolicy1.setHeightForWidth(modifyMBRButton->sizePolicy().hasHeightForWidth());
        modifyMBRButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(modifyMBRButton);


        gridLayout->addWidget(groupBox_2, 0, 1, 1, 1);


        retranslateUi(MainTaskWidget);
        QObject::connect(treeView, SIGNAL(doubleClicked(QModelIndex)), MainTaskWidget, SLOT(Double_Clicked(QModelIndex)));

        QMetaObject::connectSlotsByName(MainTaskWidget);
    } // setupUi

    void retranslateUi(QWidget *MainTaskWidget)
    {
        MainTaskWidget->setWindowTitle(QApplication::translate("MainTaskWidget", "Form", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainTaskWidget", "DiskMaster list:", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainTaskWidget", "Select a task", Q_NULLPTR));
        CopylButton->setText(QApplication::translate("MainTaskWidget", "Copying", Q_NULLPTR));
        VerifylButton->setText(QApplication::translate("MainTaskWidget", "Verification", Q_NULLPTR));
        EraseButton->setText(QApplication::translate("MainTaskWidget", "Eraseing", Q_NULLPTR));
        modifyMBRButton->setText(QApplication::translate("MainTaskWidget", "Modifying\n"
"MBR ", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainTaskWidget: public Ui_MainTaskWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINTASKPANEL_H
