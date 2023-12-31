﻿#include "DigitallmageProcessing.h"
#include <opencv2/opencv.hpp>
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

	//设置种子
	srand((unsigned)time(NULL));

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
	this->labelVar = new QLabel(" ", this);
	statusBar()->addPermanentWidget(this->labelVar);

	//// 创建一个512x512的灰度图像
	//cv::Mat image(512, 512, CV_8UC1, cv::Scalar(1));
	//// 保存图像为BMP文件
	//cv::imwrite("gray_image.bmp", image);
}

/// @brief 析构函数
DigitallmageProcessing::~DigitallmageProcessing() {}

/// @brief 打开文件
void DigitallmageProcessing::on_actionOpenFile_triggered() {
	QString path = QFileDialog::getOpenFileName(this, "打开文件", "C:/", "Image Files (*.png *.jpg *.bmp *)");
	if (path.isEmpty()) {//未选择路径
		//QMessageBox::warning(this, "警告", "未选择路径");
		return;
	}
	if (!originalImage.loadImage(path)) {//打开文件失败
		cv::Mat img;
		img = cv::imread(path.toStdString());
		if (img.empty()) {
			QMessageBox::warning(this, "警告", "打开文件失败(检查中文路径)");
			return;
		}
		originalImage.setImage(CVHelper::cvMat2QImage(img));
	}
	//状态栏显示路径
	labelPath->setText(path);
	labelVar->setText(" ");
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

	processedImage.setImage(CVHelper::cvMat2QImage(CVHelper::toGrayMat(originalImage.getQImage())));
	processedImage.displayImage(processedImageLabel);

	hasProcessedImage = true;//有处理后图像
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
	labelVar->setText(" ");
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
	if (!hasProcessedImage) {//没有输出图片无效
		QMessageBox::warning(this, "警告", "没有要保存的图片");
		return;
	}

	QString path = QFileDialog::getSaveFileName(this, "保存文件", "C:/", "Image Files (*.png *.jpg *.bmp *)");
	if (path.isEmpty()) return; //未选择路径

	if (!processedImage.getQImage().save(path, nullptr, 100)) {//保存文件失败
		QMessageBox::warning(this, "警告", "保存文件失败");
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

	//获取高斯噪声均值
	double mean = 15.0;//默认值
	NumericSelection* numericSelection = new NumericSelection("高斯噪声均值");
	numericSelection->setMinimum(0);
	numericSelection->setValue(15);
	connect(numericSelection, &NumericSelection::offerValue, this, [&](int v) {mean = v; });
	numericSelection->exec();

	//获取高斯噪声方差
	double sigma = 30.0;//默认值
	NumericSelection* numericSelection2 = new NumericSelection("高斯噪声方差");
	numericSelection2->setValue(30);
	connect(numericSelection2, &NumericSelection::offerValue, this, [&](int v) {sigma = v; });
	numericSelection2->exec();

	processedImage.setImage(CVHelper::AddGaussNoice(originalImage.getQImage(), mean, sigma));
	processedImage.displayImage(processedImageLabel);

	hasProcessedImage = true;//有处理后图像
}

/// @brief 椒盐噪声
void DigitallmageProcessing::on_actionSAPNoice_triggered()
{
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}

	//获取椒盐噪声概率
	int p = 5;//默认值
	NumericSelection* numericSelection = new NumericSelection("椒盐噪声概率");
	numericSelection->setMinimum(0);
	numericSelection->setMaximum(100);
	numericSelection->setValue(5);
	connect(numericSelection, &NumericSelection::offerValue, this, [&](int v) {p = v; });
	numericSelection->exec();

	processedImage.setImage(CVHelper::AddSAPNoice(originalImage.getQImage(), p / 100.0));
	processedImage.displayImage(processedImageLabel);

	hasProcessedImage = true;//有处理后图像
}

/// @brief 中值滤波
void DigitallmageProcessing::on_actionMedianFiltering_triggered()
{
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}

	//获取核大小
	int ksize = 3;//默认值
	NumericSelection* numericSelection = new NumericSelection("核大小");
	numericSelection->setMaximum(21);
	numericSelection->setValue(3);
	connect(numericSelection, &NumericSelection::offerValue, this, [&](int v) {ksize = v / 2 * 2 + 1; });
	numericSelection->exec();

	processedImage.setImage(CVHelper::MedianFilter(originalImage.getQImage(), ksize));//<<<<用自己的函数慢上不少
	processedImage.displayImage(processedImageLabel);

	hasProcessedImage = true;//有处理后图像
}

/// @brief 均值滤波
void DigitallmageProcessing::on_actionAverageFilter_triggered()
{
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}

	//获取核大小
	int ksize = 3;//默认值
	NumericSelection* numericSelection = new NumericSelection("核大小");
	numericSelection->setMaximum(21);
	numericSelection->setValue(3);
	connect(numericSelection, &NumericSelection::offerValue, this, [&](int v) {ksize = v / 2 * 2 + 1; });
	numericSelection->exec();

	processedImage.setImage(CVHelper::AverageFilter(originalImage.getQImage(), ksize));
	processedImage.displayImage(processedImageLabel);

	hasProcessedImage = true;//有处理后图像
}

/// @brief 自适应中值滤波
void DigitallmageProcessing::on_actionAdaptiveMedianFilters_triggered()
{
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}

	//获取最大核大小
	int Maxsize = 7;//默认值
	NumericSelection* numericSelection = new NumericSelection("最大核大小");
	numericSelection->setMaximum(21);
	numericSelection->setValue(7);
	connect(numericSelection, &NumericSelection::offerValue, this, [&](int v) {Maxsize = v / 2 * 2 + 1; });
	numericSelection->exec();

	//获取最小核大小
	int Minsize = 3;//默认值
	NumericSelection* numericSelection2 = new NumericSelection("最小核大小");
	numericSelection2->setMaximum(21);
	numericSelection2->setValue(3);
	connect(numericSelection2, &NumericSelection::offerValue, this, [&](int v) {Minsize = v / 2 * 2 + 1; });
	numericSelection2->exec();

	processedImage.setImage(CVHelper::AdaptiveMedianFilters(originalImage.getQImage(), Maxsize, Minsize));
	processedImage.displayImage(processedImageLabel);

	hasProcessedImage = true;//有处理后图像
}

/// @brief 将输出重新输入
void DigitallmageProcessing::on_action_Retreatment_triggered()
{
	if (!hasProcessedImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "输出图像为空");
		return;
	}

	originalImage = processedImage;
	cleanLabelImage();
	originalImage.displayImage(originalImageLabel);

	hasImage = true;
	hasProcessedImage = false;
}

/// @brief NonlocalMeans非局部均值去噪
void DigitallmageProcessing::on_actionNonlocalMeans_triggered()
{
	if (!hasImage) {//没有导入图片无效
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}

	//获取核大小
	int KernelSize = 3;//默认值
	NumericSelection* numericSelection = new NumericSelection("核大小");
	numericSelection->setMaximum(15);
	numericSelection->setValue(3);
	connect(numericSelection, &NumericSelection::offerValue, this, [&](int v) {KernelSize = v / 2 * 2 + 1; });
	numericSelection->exec();

	//获取搜索窗口大小
	int searchWindowSize = 15;//默认值
	NumericSelection* numericSelection2 = new NumericSelection("搜索窗口大小");
	numericSelection2->setMaximum(33);
	numericSelection2->setValue(15);
	connect(numericSelection2, &NumericSelection::offerValue, this, [&](int v) {searchWindowSize = v / 2 * 2 + 1; });
	numericSelection2->exec();

	//获取参数h
	int h = 20;//默认值
	NumericSelection* numericSelection3 = new NumericSelection("参数h");
	numericSelection3->setValue(20);
	connect(numericSelection3, &NumericSelection::offerValue, this, [&](int v) {h = v; });
	numericSelection3->exec();

	processedImage.setImage(CVHelper::NonlocalMeansFilter(originalImage.getQImage(), KernelSize, searchWindowSize, h));
	processedImage.displayImage(processedImageLabel);

	hasProcessedImage = true;//有处理后图像
}

/// @brief 二阶导数
void DigitallmageProcessing::on_actionsecond_derivative_triggered()
{
	if (!hasImage) {
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}

	processedImage.setImage(CVHelper::SecondDerivative(originalImage.getQImage()));
	processedImage.displayImage(processedImageLabel);

	hasProcessedImage = true;//有处理后图像
}

/// @brief 非锐化掩蔽
void DigitallmageProcessing::on_actionUnsharp_Masking_triggered()
{
	if (!hasImage) {
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}

	//获取参数
	double weight = 0.0;//默认值
	NumericSelection* numericSelection = new NumericSelection("权重");
	numericSelection->setMinimum(-100);
	numericSelection->setMaximum(1000);
	numericSelection->setValue(0);
	connect(numericSelection, &NumericSelection::offerValue, this, [&](int v) {weight = v / 100.0; });
	numericSelection->exec();

	processedImage.setImage(CVHelper::UnsharpMasking(originalImage.getQImage(), weight));
	processedImage.displayImage(processedImageLabel);

	hasProcessedImage = true;//有处理后图像
}

/// @brief 自适应局部降噪
void DigitallmageProcessing::on_actionAdaptiveLocalFilter_triggered()
{
	if (!hasImage) {
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}

	//获取参数
	int LocalHalfSize = 3;
	NumericSelection* numericSelection = new NumericSelection("局部半径");
	numericSelection->setMaximum(50);
	numericSelection->setValue(3);
	connect(numericSelection, &NumericSelection::offerValue, this, [&](int v) {LocalHalfSize = v; });
	numericSelection->exec();

	double noiseVar = 30.0;
	NumericSelection* numericSelection2 = new NumericSelection("噪声方差");
	numericSelection2->setValue(30);
	connect(numericSelection2, &NumericSelection::offerValue, this, [&](int v) {noiseVar = v; });
	numericSelection2->exec();

	processedImage.setImage(CVHelper::AdaptiveLocalFilter(originalImage.getQImage(), LocalHalfSize, noiseVar));
	processedImage.displayImage(processedImageLabel);

	hasProcessedImage = true;//有处理后图像
}


void DigitallmageProcessing::on_actionjpeg_triggered()
{
	if (!hasImage) {
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}

	QString path = QFileDialog::getSaveFileName(this, "保存文件", "C:/", "Image Files (*.jpg)");
	if (path.isEmpty()) return; //未选择路径

	//获取参数
	int quality = 95;
	NumericSelection* numericSelection = new NumericSelection("压缩质量");
	numericSelection->setMaximum(100);
	numericSelection->setValue(95);
	numericSelection->setMinimum(0);
	connect(numericSelection, &NumericSelection::offerValue, this, [&](int v) {quality = v; });
	numericSelection->exec();

	if (!CVHelper::saveAsJPEG(originalImage.getQImage(), path, quality)) {//保存文件失败
		QMessageBox::warning(this, "警告", "保存文件失败(检查中文路径)");
		return;
	}
}


void DigitallmageProcessing::on_actionjpeg2000_triggered()
{
	if (!hasImage) {
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}

	QString path = QFileDialog::getSaveFileName(this, "保存文件", "C:/", "Image Files (*.jp2)");
	if (path.isEmpty()) return; //未选择路径

	//获取参数
	int quality = 95;
	NumericSelection* numericSelection = new NumericSelection("压缩质量");
	numericSelection->setMaximum(100);
	numericSelection->setValue(95);
	numericSelection->setMinimum(0);
	connect(numericSelection, &NumericSelection::offerValue, this, [&](int v) {quality = v; });
	numericSelection->exec();

	if (!CVHelper::saveAsJPEG2000(originalImage.getQImage(), path, quality)) {//保存文件失败
		QMessageBox::warning(this, "警告", "保存文件失败(检查中文路径)");
		return;
	}
}


void DigitallmageProcessing::on_actionErosion_triggered()
{
	if (!hasImage) {
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}

	processedImage.setImage(CVHelper::Erosion(originalImage.getQImage()));
	processedImage.displayImage(processedImageLabel);

	hasProcessedImage = true;//有处理后图像
}


void DigitallmageProcessing::on_actionDilation_triggered()
{
	if (!hasImage) {
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}

	processedImage.setImage(CVHelper::Dilation(originalImage.getQImage()));
	processedImage.displayImage(processedImageLabel);

	hasProcessedImage = true;//有处理后图像
}


void DigitallmageProcessing::on_actionOpening_triggered()
{
	if (!hasImage) {
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}

	processedImage.setImage(CVHelper::Dilation(CVHelper::Erosion(originalImage.getQImage())));
	processedImage.displayImage(processedImageLabel);

	hasProcessedImage = true;//有处理后图像
}


void DigitallmageProcessing::on_actionClosing_triggered()
{
	if (!hasImage) {
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}

	processedImage.setImage(CVHelper::Erosion(CVHelper::Dilation(originalImage.getQImage())));
	processedImage.displayImage(processedImageLabel);

	hasProcessedImage = true;//有处理后图像
}


void DigitallmageProcessing::on_actionGlobalThresholding_triggered()
{
	if (!hasImage) {
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}
	int ans = -1;
	//获取参数
	int defaultTh = -1;
	NumericSelection* numericSelection = new NumericSelection("初始阈值");
	numericSelection->setMaximum(255);
	numericSelection->setMinimum(-1);
	numericSelection->setValue(-1);
	connect(numericSelection, &NumericSelection::offerValue, this, [&](int v) {defaultTh = v; });
	numericSelection->exec();

	QImage temp;
	double timer = (double)cv::getTickCount();
	temp = CVHelper::GlobalThresholding(originalImage.getQImage(), ans, defaultTh);
	timer = (double)cv::getTickCount() - timer;
	processedImage.setImage(temp);
	processedImage.displayImage(processedImageLabel);
	labelVar->setText("阈值：" + QString::number(ans) + "  时间：" + QString::number(timer * 1000. / cv::getTickFrequency()) + "ms");


	//processedImage.setImage(CVHelper::GlobalThresholding(originalImage.getQImage(), ans, defaultTh));
	//processedImage.displayImage(processedImageLabel);
	//labelVar->setText("阈值：" + QString::number(ans));

	hasProcessedImage = true;//有处理后图像
}


void DigitallmageProcessing::on_actionOstusThresholding_triggered()
{
	if (!hasImage) {
		QMessageBox::warning(this, "警告", "未导入图片");
		return;
	}
	int ans = -1;

	QImage temp;
	double timer = (double)cv::getTickCount();
	temp = CVHelper::OstusThresholding(originalImage.getQImage(), ans);
	timer = (double)cv::getTickCount() - timer;
	processedImage.setImage(temp);
	processedImage.displayImage(processedImageLabel);
	labelVar->setText("阈值：" + QString::number(ans) + "  时间：" + QString::number(timer * 1000. / cv::getTickFrequency()) + "ms");

	//processedImage.setImage(CVHelper::OstusThresholding(originalImage.getQImage(), ans));
	//processedImage.displayImage(processedImageLabel);
	//labelVar->setText("阈值：" + QString::number(ans));

	hasProcessedImage = true;//有处理后图像
}

