#include "numericselection.h"
#include "ui_numericselection.h"

NumericSelection::NumericSelection(QString title, QDialog* parent) :
	QDialog(parent),
	ui(new Ui::NumericSelection)
{
	ui->setupUi(this);

	this->setWindowTitle(title);

	//设置阻塞
	//this->setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::Dialog);
	//this->setWindowModality(Qt::ApplicationModal);
	//this->setAttribute(Qt::WA_ShowModal, true);

	this->setAttribute(Qt::WA_DeleteOnClose, true);

	// Connect the spinbox and slider together
	connect(ui->spinBox, SIGNAL(valueChanged(int)), ui->horizontalSlider, SLOT(setValue(int)));
	connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->spinBox, SLOT(setValue(int)));

}

NumericSelection::~NumericSelection()
{
	delete ui;
}

void NumericSelection::setValue(int value)
{
	ui->spinBox->setValue(value);
	ui->horizontalSlider->setValue(value);
}

void NumericSelection::setMinimum(int value)
{
	ui->spinBox->setMinimum(value);
	ui->horizontalSlider->setMinimum(value);
}

void NumericSelection::setMaximum(int value)
{
	ui->spinBox->setMaximum(value);
	ui->horizontalSlider->setMaximum(value);
}

int NumericSelection::getValue()
{
	return ui->spinBox->value();
}

void NumericSelection::on_ButtonClose_clicked()
{
	this->close();
}


void NumericSelection::on_ButtonGetValue_clicked()
{
	int value = ui->spinBox->value();
	emit offerValue(value);
	this->close();
}

