#include "DigitallmageProcessing.h"
#include <qmenubar.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qpixmap.h>
#include <qdialog.h>
#include <qdebug.h>
#include "CVHelper.h"


DigitallmageProcessing::DigitallmageProcessing(QWidget* parent)
	: QMainWindow(parent), hasImage(false) {
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

	hasImage = true;
}

void DigitallmageProcessing::on_actionGray_triggered() {
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}
}


void DigitallmageProcessing::on_actionEnh_triggered() {
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}
}


void DigitallmageProcessing::on_actionTranslation_triggered() {
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}
}


void DigitallmageProcessing::on_actionRotate_triggered() {
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}
}


void DigitallmageProcessing::on_actionScale_triggered() {
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}

	//获取倍率
	int vlaue = 100;
	NumericSelection* numericSelection = new NumericSelection("缩放倍率");
	connect(numericSelection, &NumericSelection::offerValue, this, [&](int v) {vlaue = v; });
	numericSelection->exec();


}


void DigitallmageProcessing::on_actionFourier_triggered() {
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}
	cleanLabelImage();
	processedImage.setImage(CVHelper::FourierTransform(originalImage.getQImage()));
	processedImage.displayImage(processedImageLabel);
}


void DigitallmageProcessing::on_actionShowHistogram_triggered() {
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}
	cleanLabelImage();
	processedImage.setImage(CVHelper::myHistogram(originalImage.getQImage()));
	processedImage.displayImage(processedImageLabel);
}


void DigitallmageProcessing::on_actionEqualization_triggered() {
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}
	cleanLabelImage();
	processedImage.setImage(CVHelper::myHistogramEqualization(originalImage.getQImage()));//均衡化
	processedImage.displayImage(processedImageLabel);

	processingImage.setImage(CVHelper::myHistogram(processedImage.getQImage()));//均衡化后的直方图
	processingImage.displayImage(processingImageLabel);
}

void DigitallmageProcessing::cleanLabelImage() {
	processingImageLabel->clear();
	processedImageLabel->clear();
}


void DigitallmageProcessing::on_actionCleanImage_triggered() {
	this->cleanLabelImage();
}


void DigitallmageProcessing::on_actionCLAHE_triggered() {
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}
	//cleanLabelImage();


	//获取对比度限制阈值
	int ClipLimit = 40;
	NumericSelection* numericSelection = new NumericSelection("对比度限制阈值");
	numericSelection->setValue(40);
	connect(numericSelection, &NumericSelection::offerValue, this, [&](int v) {ClipLimit = v; });
	numericSelection->exec();

	//获取网格大小
	int TilesGridSize = 8;
	NumericSelection* numericSelection2 = new NumericSelection("网格大小");
	numericSelection2->setValue(8);
	connect(numericSelection2, &NumericSelection::offerValue, this, [&TilesGridSize](int v) {TilesGridSize = v; });
	numericSelection2->exec();

	processedImage.setImage(CVHelper::CLAHETran(originalImage.getQImage(), ClipLimit, TilesGridSize));
	processedImage.displayImage(processedImageLabel);

	processingImage.setImage(CVHelper::myHistogram(processedImage.getQImage()));//CLAHE后的直方图
	processingImage.displayImage(processingImageLabel);
}

