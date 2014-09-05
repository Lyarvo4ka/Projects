/********************************************************************************
** Form generated from reading UI file 'CopyDetectUi.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COPYDETECTUI_H
#define UI_COPYDETECTUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_copyDetectDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_5;
    QLineEdit *taskNameEdit_;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *workFolderEdit_;
    QToolButton *openFolderButton_2;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QComboBox *sourceCombo_;
    QLabel *label_7;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_3;
    QComboBox *targetCombo_;
    QFrame *line_3;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *fullCopyButton;
    QRadioButton *partitionCopyButton;
    QRadioButton *userCopyButton;
    QToolButton *toolButton;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *copyDetectDialog)
    {
        if (copyDetectDialog->objectName().isEmpty())
            copyDetectDialog->setObjectName(QStringLiteral("copyDetectDialog"));
        copyDetectDialog->setWindowModality(Qt::WindowModal);
        copyDetectDialog->resize(550, 225);
        QIcon icon;
        icon.addFile(QStringLiteral(":/DiskMasterUI/icons/copy_disk.png"), QSize(), QIcon::Normal, QIcon::Off);
        copyDetectDialog->setWindowIcon(icon);
        copyDetectDialog->setModal(true);
        verticalLayout = new QVBoxLayout(copyDetectDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_5 = new QLabel(copyDetectDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(label_5);

        taskNameEdit_ = new QLineEdit(copyDetectDialog);
        taskNameEdit_->setObjectName(QStringLiteral("taskNameEdit_"));
        sizePolicy.setHeightForWidth(taskNameEdit_->sizePolicy().hasHeightForWidth());
        taskNameEdit_->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(taskNameEdit_);


        horizontalLayout_6->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_6 = new QLabel(copyDetectDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(label_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        workFolderEdit_ = new QLineEdit(copyDetectDialog);
        workFolderEdit_->setObjectName(QStringLiteral("workFolderEdit_"));

        horizontalLayout_5->addWidget(workFolderEdit_);

        openFolderButton_2 = new QToolButton(copyDetectDialog);
        openFolderButton_2->setObjectName(QStringLiteral("openFolderButton_2"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/DiskMasterUI/icons/folder_home.png"), QSize(), QIcon::Normal, QIcon::Off);
        openFolderButton_2->setIcon(icon1);

        horizontalLayout_5->addWidget(openFolderButton_2);


        verticalLayout_4->addLayout(horizontalLayout_5);


        horizontalLayout_6->addLayout(verticalLayout_4);


        verticalLayout->addLayout(horizontalLayout_6);

        line = new QFrame(copyDetectDialog);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label = new QLabel(copyDetectDialog);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        verticalLayout_5->addWidget(label);

        sourceCombo_ = new QComboBox(copyDetectDialog);
        sourceCombo_->setObjectName(QStringLiteral("sourceCombo_"));

        verticalLayout_5->addWidget(sourceCombo_);


        horizontalLayout->addLayout(verticalLayout_5);

        label_7 = new QLabel(copyDetectDialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy2);
        label_7->setPixmap(QPixmap(QString::fromUtf8(":/DiskMasterUI/icons/right_arrow.png")));

        horizontalLayout->addWidget(label_7);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        label_3 = new QLabel(copyDetectDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        verticalLayout_6->addWidget(label_3);

        targetCombo_ = new QComboBox(copyDetectDialog);
        targetCombo_->setObjectName(QStringLiteral("targetCombo_"));
        sizePolicy.setHeightForWidth(targetCombo_->sizePolicy().hasHeightForWidth());
        targetCombo_->setSizePolicy(sizePolicy);

        verticalLayout_6->addWidget(targetCombo_);


        horizontalLayout->addLayout(verticalLayout_6);


        verticalLayout->addLayout(horizontalLayout);

        line_3 = new QFrame(copyDetectDialog);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        fullCopyButton = new QRadioButton(copyDetectDialog);
        fullCopyButton->setObjectName(QStringLiteral("fullCopyButton"));
        fullCopyButton->setEnabled(true);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/DiskMasterUI/icons/hard_drive_clone.png"), QSize(), QIcon::Normal, QIcon::Off);
        fullCopyButton->setIcon(icon2);
        fullCopyButton->setChecked(true);

        horizontalLayout_2->addWidget(fullCopyButton);

        partitionCopyButton = new QRadioButton(copyDetectDialog);
        partitionCopyButton->setObjectName(QStringLiteral("partitionCopyButton"));
        partitionCopyButton->setEnabled(true);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/DiskMasterUI/icons/Partition.png"), QSize(), QIcon::Normal, QIcon::Off);
        partitionCopyButton->setIcon(icon3);

        horizontalLayout_2->addWidget(partitionCopyButton);

        userCopyButton = new QRadioButton(copyDetectDialog);
        userCopyButton->setObjectName(QStringLiteral("userCopyButton"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/DiskMasterUI/icons/user_copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        userCopyButton->setIcon(icon4);

        horizontalLayout_2->addWidget(userCopyButton);

        toolButton = new QToolButton(copyDetectDialog);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/DiskMasterUI/icons/preferences.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon5);
        toolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_2->addWidget(toolButton);


        verticalLayout->addLayout(horizontalLayout_2);

        line_2 = new QFrame(copyDetectDialog);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        okButton = new QPushButton(copyDetectDialog);
        okButton->setObjectName(QStringLiteral("okButton"));

        horizontalLayout_4->addWidget(okButton);

        cancelButton = new QPushButton(copyDetectDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout_4->addWidget(cancelButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        line->raise();
        line_2->raise();
        line_3->raise();

        retranslateUi(copyDetectDialog);
        QObject::connect(okButton, SIGNAL(clicked()), copyDetectDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), copyDetectDialog, SLOT(reject()));
        QObject::connect(toolButton, SIGNAL(clicked()), copyDetectDialog, SLOT(copySettingClicked()));
        QObject::connect(fullCopyButton, SIGNAL(clicked()), copyDetectDialog, SLOT(fullCopyClicked()));
        QObject::connect(partitionCopyButton, SIGNAL(clicked()), copyDetectDialog, SLOT(partitionCopyClicked()));
        QObject::connect(userCopyButton, SIGNAL(clicked()), copyDetectDialog, SLOT(userCopyClicked()));

        QMetaObject::connectSlotsByName(copyDetectDialog);
    } // setupUi

    void retranslateUi(QDialog *copyDetectDialog)
    {
        copyDetectDialog->setWindowTitle(QApplication::translate("copyDetectDialog", "Copying - Device detection", 0));
        label_5->setText(QApplication::translate("copyDetectDialog", "Task name:", 0));
        label_6->setText(QApplication::translate("copyDetectDialog", "<html><head/><body><p>Work folder:</p></body></html>", 0));
        openFolderButton_2->setText(QApplication::translate("copyDetectDialog", "...", 0));
        label->setText(QApplication::translate("copyDetectDialog", "Soruce device:", 0));
        label_7->setText(QString());
        label_3->setText(QApplication::translate("copyDetectDialog", "Target device:", 0));
        fullCopyButton->setText(QApplication::translate("copyDetectDialog", "Full copy", 0));
        partitionCopyButton->setText(QApplication::translate("copyDetectDialog", "Partition copy", 0));
        userCopyButton->setText(QApplication::translate("copyDetectDialog", "Custom copy", 0));
        toolButton->setText(QApplication::translate("copyDetectDialog", "Preferences", 0));
        okButton->setText(QApplication::translate("copyDetectDialog", "Ok", 0));
        cancelButton->setText(QApplication::translate("copyDetectDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class copyDetectDialog: public Ui_copyDetectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPYDETECTUI_H
