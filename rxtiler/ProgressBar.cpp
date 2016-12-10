#include "ProgressBar.h"
#include "ui_ProgressBar.h"

ProgressBar::ProgressBar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressBar)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
}

ProgressBar::~ProgressBar()
{
    delete ui;
}

void ProgressBar::setProgressBarValue(int value)
{
    ui->progressBar->setValue(value);
}
