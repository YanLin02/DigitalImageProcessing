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


/// @brief 构造函数
DigitallmageProcessing::DigitallmageProcessing(QWidget* parent)
	: QMainWindow(parent), hasImage(false), hasProcessedImage(false) {
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

/// @brief 析构函数
DigitallmageProcessing::~DigitallmageProcessing() {}

/// @brief 打开文件
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

/// @brief 灰度化
void DigitallmageProcessing::on_actionGray_triggered() {
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}
}

/// @brief 增强
void DigitallmageProcessing::on_actionEnh_triggered() {
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}
}

/// @brief 平移
void DigitallmageProcessing::on_actionTranslation_triggered() {
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}
}

/// @brief 旋转
void DigitallmageProcessing::on_actionRotate_triggered() {
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}
}

/// @brief 缩放
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

/// @brief 傅里叶变换
void DigitallmageProcessing::on_actionFourier_triggered() {
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}
	cleanLabelImage();
	processedImage.setImage(CVHelper::FourierTransform(originalImage.getQImage()));
	processedImage.displayImage(processedImageLabel);

	hasProcessedImage = true;//有处理后图像
}

/// @brief 直方图
void DigitallmageProcessing::on_actionShowHistogram_triggered() {
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}
	cleanLabelImage();
	processedImage.setImage(CVHelper::myHistogram(originalImage.getQImage()));
	processedImage.displayImage(processedImageLabel);

	hasProcessedImage = true;//有处理后图像
}

/// @brief 直方图均衡化
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

	hasProcessedImage = true;//有处理后图像
}

/// @brief 清除图像标签
void DigitallmageProcessing::cleanLabelImage() {
	processingImageLabel->clear();
	processedImageLabel->clear();
	hasProcessedImage = false;
}

/// @brief 清空图像
void DigitallmageProcessing::on_actionCleanImage_triggered() {
	this->cleanLabelImage();
}

/// @brief CLAHE算法
void DigitallmageProcessing::on_actionCLAHE_triggered() {
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}
	//cleanLabelImage();

	//获取对比度限制阈值
	int ClipLimit = 40;//默认值
	NumericSelection* numericSelection = new NumericSelection("对比度限制阈值");
	numericSelection->setValue(40);
	connect(numericSelection, &NumericSelection::offerValue, this, [&](int v) {ClipLimit = v; });
	numericSelection->exec();

	//获取网格大小
	int TilesGridSize = 8;//默认值
	NumericSelection* numericSelection2 = new NumericSelection("网格大小");
	numericSelection2->setValue(8);
	connect(numericSelection2, &NumericSelection::offerValue, this, [&TilesGridSize](int v) {TilesGridSize = v; });
	numericSelection2->exec();

	processedImage.setImage(CVHelper::CLAHETran(originalImage.getQImage(), ClipLimit, TilesGridSize));
	processedImage.displayImage(processedImageLabel);

	processingImage.setImage(CVHelper::myHistogram(processedImage.getQImage()));//CLAHE后的直方图
	processingImage.displayImage(processingImageLabel);

	hasProcessedImage = true;//有处理后图像
}

/// @brief 保存图像
void DigitallmageProcessing::on_actionSaveImg_triggered()
{
	if (!hasProcessedImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "没有要保存的图片");
		return;
	}
}

/// @brief 高斯噪声
void DigitallmageProcessing::on_actionGaussNoice_triggered()
{
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}
}

/// @brief 椒盐噪声
void DigitallmageProcessing::on_actionSAPNoice_triggered()
{
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}
}

/// @brief 中值滤波
void DigitallmageProcessing::on_actionMedianFiltering_triggered()
{
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}
}

/// @brief 均值滤波
void DigitallmageProcessing::on_actionAverageFilter_triggered()
{
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}

}

/// @brief 自适应中值滤波
void DigitallmageProcessing::on_actionAdaptiveMedianFilters_triggered()
{
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}
}

/// @brief 将输出重新输入
void DigitallmageProcessing::on_action_Retreatment_triggered()
{
	if (!hasProcessedImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "输出图像为空");
		return;
	}
}

/// @brief NonlocalMeans非局部均值去噪
void DigitallmageProcessing::on_actionNonlocalMeans_triggered()
{
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}
}

