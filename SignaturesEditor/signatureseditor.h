#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_signatureseditor.h"

class SignaturesEditor : public QMainWindow
{
    Q_OBJECT

public:
    SignaturesEditor(QWidget *parent = Q_NULLPTR);

private:
    Ui::SignaturesEditorClass ui;
};
