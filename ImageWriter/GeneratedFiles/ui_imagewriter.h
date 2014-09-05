/********************************************************************************
** Form generated from reading UI file 'imagewriter.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEWRITER_H
#define UI_IMAGEWRITER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageWriterClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLineEdit *fileEdit;
    QToolButton *selectFileButton;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *hddEdit;
    QToolButton *selectHddButton;
    QHBoxLayout *horizontalLayout_4;
    QProgressBar *progressBar;
    QToolButton *startButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ImageWriterClass)
    {
        if (ImageWriterClass->objectName().isEmpty())
            ImageWriterClass->setObjectName(QStringLiteral("ImageWriterClass"));
        ImageWriterClass->resize(853, 148);
        centralWidget = new QWidget(ImageWriterClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        fileEdit = new QLineEdit(centralWidget);
        fileEdit->setObjectName(QStringLiteral("fileEdit"));
        fileEdit->setReadOnly(true);

        horizontalLayout->addWidget(fileEdit);

        selectFileButton = new QToolButton(centralWidget);
        selectFileButton->setObjectName(QStringLiteral("selectFileButton"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/ImageWriter/icons/file.png"), QSize(), QIcon::Normal, QIcon::Off);
        selectFileButton->setIcon(icon);

        horizontalLayout->addWidget(selectFileButton);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/ImageWriter/icons/arrow_right.png")));

        horizontalLayout_2->addWidget(label_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        hddEdit = new QLineEdit(centralWidget);
        hddEdit->setObjectName(QStringLiteral("hddEdit"));
        hddEdit->setReadOnly(true);

        horizontalLayout_3->addWidget(hddEdit);

        selectHddButton = new QToolButton(centralWidget);
        selectHddButton->setObjectName(QStringLiteral("selectHddButton"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/ImageWriter/icons/hdd.png"), QSize(), QIcon::Normal, QIcon::Off);
        selectHddButton->setIcon(icon1);

        horizontalLayout_3->addWidget(selectHddButton);


        verticalLayout_2->addLayout(horizontalLayout_3);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy1);
        progressBar->setValue(24);
        progressBar->setTextVisible(true);

        horizontalLayout_4->addWidget(progressBar);

        startButton = new QToolButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy2);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/ImageWriter/icons/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        startButton->setIcon(icon2);
        startButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout_4->addWidget(startButton);


        verticalLayout_3->addLayout(horizontalLayout_4);

        ImageWriterClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ImageWriterClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 853, 21));
        ImageWriterClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ImageWriterClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setEnabled(false);
        ImageWriterClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ImageWriterClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ImageWriterClass->setStatusBar(statusBar);

        retranslateUi(ImageWriterClass);

        QMetaObject::connectSlotsByName(ImageWriterClass);
    } // setupUi

    void retranslateUi(QMainWindow *ImageWriterClass)
    {
        ImageWriterClass->setWindowTitle(QApplication::translate("ImageWriterClass", "ImageWriter", 0));
        label->setText(QApplication::translate("ImageWriterClass", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \321\204\320\260\320\271\320\273:", 0));
        selectFileButton->setText(QApplication::translate("ImageWriterClass", "...", 0));
        label_2->setText(QString());
        label_3->setText(QApplication::translate("ImageWriterClass", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \320\264\320\270\321\201\320\272", 0));
        selectHddButton->setText(QApplication::translate("ImageWriterClass", "...", 0));
        startButton->setText(QApplication::translate("ImageWriterClass", "\320\241\321\202\320\260\321\200\321\202", 0));
    } // retranslateUi

};

namespace Ui {
    class ImageWriterClass: public Ui_ImageWriterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEWRITER_H
