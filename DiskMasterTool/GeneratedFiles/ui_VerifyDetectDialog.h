/********************************************************************************
** Form generated from reading UI file 'VerifyDetectDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VERIFYDETECTDIALOG_H
#define UI_VERIFYDETECTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_VerifyDetectUi
{
public:
    QVBoxLayout *verticalLayout_2;
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
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QComboBox *verifyCombo_;
    QSpacerItem *horizontalSpacer_3;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *VerifyDetectUi)
    {
        if (VerifyDetectUi->objectName().isEmpty())
            VerifyDetectUi->setObjectName(QStringLiteral("VerifyDetectUi"));
        VerifyDetectUi->resize(450, 183);
        QIcon icon;
        icon.addFile(QStringLiteral(":/DiskMasterUI/icons/verify_task.png"), QSize(), QIcon::Normal, QIcon::Off);
        VerifyDetectUi->setWindowIcon(icon);
        verticalLayout_2 = new QVBoxLayout(VerifyDetectUi);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_5 = new QLabel(VerifyDetectUi);
        label_5->setObjectName(QStringLiteral("label_5"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(label_5);

        taskNameEdit_ = new QLineEdit(VerifyDetectUi);
        taskNameEdit_->setObjectName(QStringLiteral("taskNameEdit_"));
        sizePolicy.setHeightForWidth(taskNameEdit_->sizePolicy().hasHeightForWidth());
        taskNameEdit_->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(taskNameEdit_);


        horizontalLayout_6->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_6 = new QLabel(VerifyDetectUi);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(label_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        workFolderEdit_ = new QLineEdit(VerifyDetectUi);
        workFolderEdit_->setObjectName(QStringLiteral("workFolderEdit_"));

        horizontalLayout_5->addWidget(workFolderEdit_);

        openFolderButton_2 = new QToolButton(VerifyDetectUi);
        openFolderButton_2->setObjectName(QStringLiteral("openFolderButton_2"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/DiskMasterUI/icons/folder_home.png"), QSize(), QIcon::Normal, QIcon::Off);
        openFolderButton_2->setIcon(icon1);

        horizontalLayout_5->addWidget(openFolderButton_2);


        verticalLayout_4->addLayout(horizontalLayout_5);


        horizontalLayout_6->addLayout(verticalLayout_4);


        verticalLayout_2->addLayout(horizontalLayout_6);

        line = new QFrame(VerifyDetectUi);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        groupBox = new QGroupBox(VerifyDetectUi);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(150, 0));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label);

        verifyCombo_ = new QComboBox(groupBox);
        verifyCombo_->setObjectName(QStringLiteral("verifyCombo_"));

        verticalLayout_5->addWidget(verifyCombo_);


        verticalLayout->addLayout(verticalLayout_5);


        horizontalLayout_2->addWidget(groupBox);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_2);

        line_2 = new QFrame(VerifyDetectUi);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        okButton = new QPushButton(VerifyDetectUi);
        okButton->setObjectName(QStringLiteral("okButton"));

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(VerifyDetectUi);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout->addWidget(cancelButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(VerifyDetectUi);
        QObject::connect(okButton, SIGNAL(clicked()), VerifyDetectUi, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), VerifyDetectUi, SLOT(reject()));

        QMetaObject::connectSlotsByName(VerifyDetectUi);
    } // setupUi

    void retranslateUi(QDialog *VerifyDetectUi)
    {
        VerifyDetectUi->setWindowTitle(QApplication::translate("VerifyDetectUi", "Verification - Detect device", 0));
        label_5->setText(QApplication::translate("VerifyDetectUi", "Task name:", 0));
        label_6->setText(QApplication::translate("VerifyDetectUi", "<html><head/><body><p>Work folder</p></body></html>", 0));
        openFolderButton_2->setText(QApplication::translate("VerifyDetectUi", "...", 0));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("VerifyDetectUi", "Device to verify:", 0));
        okButton->setText(QApplication::translate("VerifyDetectUi", "OK", 0));
        cancelButton->setText(QApplication::translate("VerifyDetectUi", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class VerifyDetectUi: public Ui_VerifyDetectUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VERIFYDETECTDIALOG_H
