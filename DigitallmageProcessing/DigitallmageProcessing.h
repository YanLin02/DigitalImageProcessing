#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DigitallmageProcessing.h"

class DigitallmageProcessing : public QMainWindow
{
    Q_OBJECT

public:
    DigitallmageProcessing(QWidget *parent = nullptr);
    ~DigitallmageProcessing();

private:
    Ui::DigitallmageProcessingClass ui;
};
