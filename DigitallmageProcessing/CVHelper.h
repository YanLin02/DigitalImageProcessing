#pragma once
#include <opencv2/opencv.hpp>
#include <QImage>

using namespace cv;

class CVHelper
{
public:

	static QImage cvMat2QImage(const Mat& mat);

	/// @brief 将Mat转换为QImage
	/// @param mat BGR的Mat
	/// @return RGB888格式的QImage
	/// @note 该函数用于将Mat转换为QImage,并且将BGR转换为RGB
	static QImage BGRMat2QImage(const Mat& mat) {
		cvtColor(mat, mat, cv::COLOR_BGR2RGB);
		return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888).copy();
	}

	/// @brief 将灰度图Mat转换为QImage
	/// @param mat 8位灰度图Mat
	/// @return QImage
	static QImage Gray8Mat2QImage(const Mat& mat) {
		return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8).copy();
	}

	/// @brief 获取BGR的Mat
	/// @return BGR格式的Mat
	/// @note 该函数用于将QImage转换为Mat,并且将RGB转换为BGR
	static Mat QImagetoBGRMat(const QImage& image) {
		//TODO 搞清楚这里的格式转换,RGB和BGR的转化是否能简化
		QImage RGBimage = image.convertToFormat(QImage::Format_RGB888);//转换为RGB888格式 TODO Alpha通道的处理?
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

	static QImage FourierTransform(const QImage& image);
};

