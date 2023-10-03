#include "DigitallmageProcessing.h"
#include <qmenubar.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <QHBoxLayout>


DigitallmageProcessing::DigitallmageProcessing(QWidget* parent)
	: QMainWindow(parent) {
	ui.setupUi(this);

	//图像标签创建
	originalImageLabel = new QLabel(this);
	processedImageLabel = new QLabel(this);

	//布局设置
	QHBoxLayout* Imagelayout = new QHBoxLayout();
	Imagelayout->addWidget(originalImageLabel);
	Imagelayout->addWidget(processedImageLabel);
	centralWidget()->setLayout(Imagelayout);

	//状态栏显示路径
	QLabel* labelPath = new QLabel("图片路径", this);
	statusBar()->addWidget(labelPath);

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

	//显示原始图像
	originalImage.displayImage(originalImageLabel);

	//傅里叶变换
	//processedImage = originalImage.FourierTransform();

	//显示处理后图像
	originalImage.displayImage(processedImageLabel);

	//状态栏显示路径
	QLabel* labelPath = statusBar()->findChild<QLabel*>();
	labelPath->setText(path);

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

