#ifndef NUMERICSELECTION_H
#define NUMERICSELECTION_H

#include <QWidget>
#include <qdialog.h>

namespace Ui {
	class NumericSelection;
}

class NumericSelection : public QDialog
{
	Q_OBJECT

public:
	explicit NumericSelection(QString title, QDialog* parent = nullptr);
	~NumericSelection();

	void setValue(int value);

	int getValue();

private slots:
	void on_ButtonClose_clicked();

	void on_ButtonGetValue_clicked();

private:
	Ui::NumericSelection* ui;

signals:
	void offerValue(int);
};

#endif // NUMERICSELECTION_H
