/**
* @file CVHelper.h
* @auther Yanlin02
* @email 213213459@seu.edu.cn
* @date 2023/10/4 21:55
* @brief CVHelper类的声明，用于提供一些OpenCV和Qt图像格式的转换、图像处理等功能
* @note 万分感谢 sinat_34774186 提供的图像格式转化代码，以及其在我为此困扰四天后所给予的帮助，本人在此基础上进行了一些修改。
*/

#pragma once
#include <opencv2/opencv.hpp>
#include <QImage>
#include <vector>

using namespace cv;
using std::vector;

class CVHelper
{
public:
	static QImage FourierTransform(const QImage& image);

	static QImage Histogram(const QImage& image);
	static QImage myHistogram(const QImage& image);

	static QImage HistogramEqualization(const QImage& image);
	static QImage myHistogramEqualization(const QImage& image);

	static QImage CLAHETran(const QImage& image, double ClipLimit = 40.0, int TilesGridSize = 8);

	static QImage AddGaussNoice(const QImage& image, double mean = 15.0, double sigma = 30.0);

	static QImage AddSAPNoice(const QImage& image, double p = 0.05);

	static QImage MedianFilter(const QImage& image, int ksize = 3);
	static QImage myMedianFilter(const QImage& image, int ksize = 3);

	static QImage AverageFilter(const QImage& image, int ksize = 3);
	static QImage myAverageFilter(const QImage& image, int ksize = 3);

	static QImage AdaptiveMedianFilters(const QImage& image, int Maxsize = 7, int Minsize = 3);
	static uchar adaptiveProcess(const Mat& image, int row, int col, int kernelSize, int maxSize);

	static QImage NonlocalMeansFilter(const QImage& image, int KernelSize = 3, int searchWindowSize = 15, double h = 20.0);

	static QImage AdaptiveLocalFilter(const QImage& image, int LocalHalfSize = 3, double noiseVar = 30.0);

	static QImage SecondDerivative(const QImage& image);

	static QImage UnsharpMasking(const QImage& image, double weight = 0.6);

	static QImage cvMat2QImage(const Mat& mat);

	static Mat QImage2cvMat(QImage& image);

	static bool saveAsJPEG(const QImage& image, const QString& fileName, int quality = 100);

	static bool saveAsJPEG2000(const QImage& image, const QString& fileName, int quality = 100);

	/// @brief 将Mat转换为QImage
	/// @param mat BGR的Mat
	/// @return RGB888格式的QImage
	/// @note 不要使用，使用cvMat2QImage代替
	static QImage BGRMat2QImage(const Mat& mat) {
		cvtColor(mat, mat, cv::COLOR_BGR2RGB);
		return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888).copy();
	}
	/// @brief 将灰度图Mat转换为QImage
	/// @param mat 8位灰度图Mat
	/// @return QImage
	/// @note 不要使用，使用cvMat2QImage代替
	static QImage Gray8Mat2QImage(const Mat& mat) {
		return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8).copy();
	}
	/// @brief 获取BGR的Mat
	/// @return BGR格式的Mat
	/// @note 不要使用，使用QImagetoBGRMat代替
	static Mat QImagetoBGRMat(const QImage& image) {
		QImage RGBimage = image.convertToFormat(QImage::Format_RGB888);//转换为RGB888格式
		Mat mat(RGBimage.height(), RGBimage.width(), CV_8UC3, RGBimage.bits(), RGBimage.bytesPerLine());
		cv::cvtColor(mat, mat, cv::COLOR_RGB2BGR);
		return mat;
	}
	/// @brief 获取灰度图的Mat
	/// @return GRAY格式的Mat
	static Mat toGrayMat(const QImage& image) {
		QImage RGBimage = image.convertToFormat(QImage::Format_RGB888);
		Mat mat(RGBimage.height(), RGBimage.width(), CV_8UC3, RGBimage.bits(), RGBimage.bytesPerLine());
		cv::cvtColor(mat, mat, cv::COLOR_RGB2GRAY);
		return mat;
	}

};

