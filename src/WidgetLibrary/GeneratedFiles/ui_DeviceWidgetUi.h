/********************************************************************************
** Form generated from reading UI file 'DeviceWidgetUi.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICEWIDGETUI_H
#define UI_DEVICEWIDGETUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_deviceWidgetUi
{
public:
    QGridLayout *gridLayout;
    QGroupBox *deviceGroupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QComboBox *deviceComboBox;
    QToolButton *detectButton;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLabel *serialNumberText;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QLabel *sectorsCountText;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_4;
    QLabel *sectorSizeText;

    void setupUi(QWidget *deviceWidgetUi)
    {
        if (deviceWidgetUi->objectName().isEmpty())
            deviceWidgetUi->setObjectName(QStringLiteral("deviceWidgetUi"));
        deviceWidgetUi->resize(370, 107);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(deviceWidgetUi->sizePolicy().hasHeightForWidth());
        deviceWidgetUi->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(deviceWidgetUi);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        deviceGroupBox = new QGroupBox(deviceWidgetUi);
        deviceGroupBox->setObjectName(QStringLiteral("deviceGroupBox"));
        deviceGroupBox->setEnabled(true);
        sizePolicy.setHeightForWidth(deviceGroupBox->sizePolicy().hasHeightForWidth());
        deviceGroupBox->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(deviceGroupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        deviceComboBox = new QComboBox(deviceGroupBox);
        deviceComboBox->setObjectName(QStringLiteral("deviceComboBox"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(deviceComboBox->sizePolicy().hasHeightForWidth());
        deviceComboBox->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(deviceComboBox);

        detectButton = new QToolButton(deviceGroupBox);
        detectButton->setObjectName(QStringLiteral("detectButton"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/DiskMasterUI/icons/arrow_refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        detectButton->setIcon(icon);

        horizontalLayout->addWidget(detectButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_5 = new QLabel(deviceGroupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);
        label_5->setFrameShape(QFrame::NoFrame);

        horizontalLayout_3->addWidget(label_5);

        serialNumberText = new QLabel(deviceGroupBox);
        serialNumberText->setObjectName(QStringLiteral("serialNumberText"));
        sizePolicy.setHeightForWidth(serialNumberText->sizePolicy().hasHeightForWidth());
        serialNumberText->setSizePolicy(sizePolicy);
        serialNumberText->setFrameShape(QFrame::NoFrame);

        horizontalLayout_3->addWidget(serialNumberText);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_6 = new QLabel(deviceGroupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy2.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy2);
        label_6->setFrameShape(QFrame::NoFrame);

        horizontalLayout_4->addWidget(label_6);

        sectorsCountText = new QLabel(deviceGroupBox);
        sectorsCountText->setObjectName(QStringLiteral("sectorsCountText"));
        sizePolicy.setHeightForWidth(sectorsCountText->sizePolicy().hasHeightForWidth());
        sectorsCountText->setSizePolicy(sizePolicy);
        sectorsCountText->setFrameShape(QFrame::NoFrame);

        horizontalLayout_4->addWidget(sectorsCountText);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_4 = new QLabel(deviceGroupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);
        label_4->setFrameShape(QFrame::NoFrame);

        horizontalLayout_8->addWidget(label_4);

        sectorSizeText = new QLabel(deviceGroupBox);
        sectorSizeText->setObjectName(QStringLiteral("sectorSizeText"));
        sizePolicy.setHeightForWidth(sectorSizeText->sizePolicy().hasHeightForWidth());
        sectorSizeText->setSizePolicy(sizePolicy);
        sectorSizeText->setFrameShape(QFrame::NoFrame);

        horizontalLayout_8->addWidget(sectorSizeText);


        verticalLayout->addLayout(horizontalLayout_8);


        gridLayout->addWidget(deviceGroupBox, 0, 0, 1, 1);


        retranslateUi(deviceWidgetUi);
        QObject::connect(detectButton, SIGNAL(clicked()), deviceWidgetUi, SLOT(RefreshClicked()));

        QMetaObject::connectSlotsByName(deviceWidgetUi);
    } // setupUi

    void retranslateUi(QWidget *deviceWidgetUi)
    {
        deviceWidgetUi->setWindowTitle(QApplication::translate("deviceWidgetUi", "Form", 0));
        deviceGroupBox->setTitle(QString());
        detectButton->setText(QApplication::translate("deviceWidgetUi", "...", 0));
        label_5->setText(QApplication::translate("deviceWidgetUi", "Serial number:", 0));
        serialNumberText->setText(QString());
        label_6->setText(QApplication::translate("deviceWidgetUi", "Sectors count:", 0));
        sectorsCountText->setText(QString());
        label_4->setText(QApplication::translate("deviceWidgetUi", "Sector size:", 0));
        sectorSizeText->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class deviceWidgetUi: public Ui_deviceWidgetUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICEWIDGETUI_H
