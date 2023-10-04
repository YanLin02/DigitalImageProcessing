#pragma once
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <qstring.h>
#include <opencv2/opencv.hpp>
#include <qpixmap.h>

using cv::Mat;
using std::complex;
using std::byte;

class Image {
private:
	QImage image;

public:

	Image() {}

	Image(const QImage& image) {
		this->image = image;
	}

	/// @brief 从指定路径加载图像
	/// @param fileName 图像路径
	/// @return 是否加载成功
	bool loadImage(const QString& fileName) {
		return image.load(fileName);
	}

	/// @brief 向指定标签显示图像
	/// @param label 用于展示图像的标签
	void displayImage(QLabel* label) {
		label->clear();
		label->setPixmap(QPixmap::fromImage(this->getQImage()));
		label->adjustSize();
	}

	/// @brief 获取图像
	/// @return QImage类型的图像
	QImage getQImage() {
		return image;
	}
	QImage getQImage() const{
		return image;
	}

	/// @brief 设置图像
	/// @param image QImage类型的图像
	void setImage(const QImage& image) {
		this->image = image;
	}

};