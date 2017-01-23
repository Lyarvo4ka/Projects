/********************************************************************************
** Form generated from reading UI file 'wselectfolder.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WSELECTFOLDER_H
#define UI_WSELECTFOLDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WSelectFolder
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QToolButton *openButton;

    void setupUi(QWidget *WSelectFolder)
    {
        if (WSelectFolder->objectName().isEmpty())
            WSelectFolder->setObjectName(QStringLiteral("WSelectFolder"));
        WSelectFolder->resize(413, 43);
        verticalLayout_2 = new QVBoxLayout(WSelectFolder);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(WSelectFolder);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit = new QLineEdit(WSelectFolder);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        openButton = new QToolButton(WSelectFolder);
        openButton->setObjectName(QStringLiteral("openButton"));

        horizontalLayout->addWidget(openButton);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(WSelectFolder);

        QMetaObject::connectSlotsByName(WSelectFolder);
    } // setupUi

    void retranslateUi(QWidget *WSelectFolder)
    {
        WSelectFolder->setWindowTitle(QApplication::translate("WSelectFolder", "WSelectFolder", Q_NULLPTR));
        label->setText(QApplication::translate("WSelectFolder", "TextLabel", Q_NULLPTR));
        openButton->setText(QApplication::translate("WSelectFolder", "...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WSelectFolder: public Ui_WSelectFolder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WSELECTFOLDER_H
