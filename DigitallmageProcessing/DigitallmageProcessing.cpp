#include "DigitallmageProcessing.h"
#include <qmenubar.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qpixmap.h>
#include "CVHelper.h"


DigitallmageProcessing::DigitallmageProcessing(QWidget* parent)
	: QMainWindow(parent) {
	ui.setupUi(this);

	//图像标签创建
	originalImageLabel = new QLabel(this);
	processingImageLabel = new QLabel(this);
	processedImageLabel = new QLabel(this);

	//布局设置


	QHBoxLayout* Imagelayout = new QHBoxLayout();
	Imagelayout->setAlignment(Qt::AlignCenter);
	Imagelayout->addWidget(originalImageLabel);
	Imagelayout->addWidget(processingImageLabel);
	Imagelayout->addWidget(processedImageLabel);
	centralWidget()->setLayout(Imagelayout);

	//状态栏显示路径
	this->labelPath = new QLabel("图片路径", this);
	statusBar()->addWidget(this->labelPath);

}

DigitallmageProcessing::~DigitallmageProcessing() {}

void DigitallmageProcessing::on_actionOpenFile_triggered() {
	QString path = QFileDialog::getOpenFileName(this, "打开文件", "C:/", "Image Files (*.png *.jpg *.bmp *)");
	if (path.isEmpty()) {//未选择路径
		QMessageBox::warning(this, "警告", "未选择路径");
		return;
	}
	if (!originalImage.loadImage(path)) {//打开文件失败
		QMessageBox::warning(this, "警告", "打开文件失败");
		return;
	}
	//状态栏显示路径
	labelPath->setText(path);
	//清除原有图像
	originalImageLabel->clear();
	processingImageLabel->clear();
	processedImageLabel->clear();
	//显示原始图像
	originalImage.displayImage(originalImageLabel);
}

void DigitallmageProcessing::on_actionGray_triggered() {

}


void DigitallmageProcessing::on_actionEnh_triggered() {

}


void DigitallmageProcessing::on_actionTranslation_triggered() {

}


void DigitallmageProcessing::on_actionRotate_triggered() {

}


void DigitallmageProcessing::on_actionScale_triggered() {

}


void DigitallmageProcessing::on_actionFourier_triggered() {
	cleanLabelImage();
	processedImage.setImage(CVHelper::FourierTransform(originalImage.getQImage()));
	processedImage.displayImage(processedImageLabel);
}


void DigitallmageProcessing::on_actionShowHistogram_triggered()
{
	cleanLabelImage();
	processedImage.setImage(CVHelper::Histogram(originalImage.getQImage()));
	processedImage.displayImage(processedImageLabel);
}


void DigitallmageProcessing::on_actionEqualization_triggered()
{
	cleanLabelImage();
	processedImage.setImage(CVHelper::HistogramEqualization(originalImage.getQImage()));//均衡化
	processedImage.displayImage(processedImageLabel);

	processingImage.setImage(CVHelper::Histogram(processedImage.getQImage()));//均衡化后的直方图
	processingImage.displayImage(processingImageLabel);
}

void DigitallmageProcessing::cleanLabelImage()
{
	processingImageLabel->clear();
	processedImageLabel->clear();
}

