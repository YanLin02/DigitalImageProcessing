﻿/**
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

using namespace cv;

class CVHelper
{
public:
	static QImage FourierTransform(const QImage& image);

	static QImage Histogram(const QImage& image);

	static QImage HistogramEqualization(const QImage& image);

	static QImage cvMat2QImage(const Mat& mat);

	static Mat QImage2cvMat(QImage& image);

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

};

