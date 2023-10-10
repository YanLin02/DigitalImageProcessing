#include "CVHelper.h"

/// @brief 根据图像的类型，将Mat图像转换为QImage图像
/// @param mat cv::Mat图像
/// @return QImage图像
/// @note 万分感谢 sinat_34774186 的博客，本函数的实现参考了该博客的内容
QImage CVHelper::cvMat2QImage(const Mat& mat)
{
	if (mat.empty())
	{
		return QImage();
	}
	QImage image;
	switch (mat.type())
	{
	case CV_8UC1:
	{
		image = QImage((const uchar*)(mat.data),
			mat.cols, mat.rows, mat.step,
			QImage::Format_Grayscale8);
		return image.copy();
	}
	case CV_8UC2:
	{
		mat.convertTo(mat, CV_8UC1);
		image = QImage((const uchar*)(mat.data),
			mat.cols, mat.rows, mat.step,
			QImage::Format_Grayscale8);
		return image.copy();
	}
	case CV_8UC3:
	{
		// Copy input Mat
		const uchar* pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	case CV_8UC4:
	{
		// Copy input Mat
		const uchar* pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	case CV_32FC1:
	{
		Mat normalize_mat;
		normalize(mat, normalize_mat, 0, 255, NORM_MINMAX, -1);
		normalize_mat.convertTo(normalize_mat, CV_8U);
		const uchar* pSrc = (const uchar*)normalize_mat.data;
		QImage image(pSrc, normalize_mat.cols, normalize_mat.rows, normalize_mat.step, QImage::Format_Grayscale8);
		return image.copy();
	}
	case CV_32FC3:
	{
		Mat normalize_mat;
		normalize(mat, normalize_mat, 0, 255, NORM_MINMAX, -1);
		normalize_mat.convertTo(normalize_mat, CV_8U);
		const uchar* pSrc = (const uchar*)normalize_mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, normalize_mat.cols, normalize_mat.rows, normalize_mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	case CV_64FC1:
	{
		Mat normalize_mat;
		normalize(mat, normalize_mat, 0, 255, NORM_MINMAX, -1);
		normalize_mat.convertTo(normalize_mat, CV_8U);
		const uchar* pSrc = (const uchar*)normalize_mat.data;
		QImage image(pSrc, normalize_mat.cols, normalize_mat.rows, normalize_mat.step, QImage::Format_Grayscale8);
		return image.copy();
	}
	case CV_64FC3:
	{
		Mat normalize_mat;
		normalize(mat, normalize_mat, 0, 255, NORM_MINMAX, -1);
		normalize_mat.convertTo(normalize_mat, CV_8U);
		const uchar* pSrc = (const uchar*)normalize_mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, normalize_mat.cols, normalize_mat.rows, normalize_mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	case CV_32SC1:
	{
		Mat normalize_mat;
		normalize(mat, normalize_mat, 0, 255, NORM_MINMAX, -1);
		normalize_mat.convertTo(normalize_mat, CV_8U);
		const uchar* pSrc = (const uchar*)normalize_mat.data;
		QImage image(pSrc, normalize_mat.cols, normalize_mat.rows, normalize_mat.step, QImage::Format_Grayscale8);
		return image.copy();
	}
	case CV_32SC3:
	{
		Mat normalize_mat;
		normalize(mat, normalize_mat, 0, 255, NORM_MINMAX, -1);
		normalize_mat.convertTo(normalize_mat, CV_8U);
		const uchar* pSrc = (const uchar*)normalize_mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, normalize_mat.cols, normalize_mat.rows, normalize_mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	case CV_16SC1:
	{
		Mat normalize_mat;
		normalize(mat, normalize_mat, 0, 255, NORM_MINMAX, -1);
		normalize_mat.convertTo(normalize_mat, CV_8U);
		const uchar* pSrc = (const uchar*)normalize_mat.data;
		QImage image(pSrc, normalize_mat.cols, normalize_mat.rows, normalize_mat.step, QImage::Format_Grayscale8);
		return image.copy();
	}
	case CV_16SC3:
	{
		Mat normalize_mat;
		normalize(mat, normalize_mat, 0, 255, NORM_MINMAX, -1);
		normalize_mat.convertTo(normalize_mat, CV_8U);
		const uchar* pSrc = (const uchar*)normalize_mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, normalize_mat.cols, normalize_mat.rows, normalize_mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	case CV_8SC1:
	{
		//Mat normalize_mat;
		//normalize(mat, normalize_mat, 0, 255, NORM_MINMAX, -1);
		mat.convertTo(mat, CV_8U);
		const uchar* pSrc = (const uchar*)mat.data;
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
		return image.copy();
	}
	case CV_8SC3:
	{
		mat.convertTo(mat, CV_8U);
		const uchar* pSrc = (const uchar*)mat.data;
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	default:
		mat.convertTo(mat, CV_8UC3);
		QImage image((const uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
		return QImage();
		break;
	}
}

/// @brief 根据图像的类型，将QImage图像转换为Mat图像
/// @param image QImage图像
/// @return cv::Mat图像
/// @note 万分感谢 sinat_34774186 的博客，本函数的实现参考了该博客的内容
Mat CVHelper::QImage2cvMat(QImage& image){
	cv::Mat mat;
	//qDebug() << image.format();
	switch (image.format())
	{
	case QImage::Format_ARGB32:
		mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
		break;
	case QImage::Format_RGB32:
		mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
		//cv::cvtColor(mat, mat, CV_BGR2RGB);
		break;
	case QImage::Format_ARGB32_Premultiplied:
		mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
		break;
	case QImage::Format_RGB888:
		mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
		//cv::cvtColor(mat, mat, CV_BGR2RGB);
		break;
	case QImage::Format_Indexed8:
		mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
		break;
	case QImage::Format_Grayscale8:
		mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
		break;
	}
	return mat;
}

/// @brief 利用OpenCV的函数进行傅里叶变换
/// @param image QImage图像
/// @return 傅里叶变换后的QImage图像
QImage CVHelper::FourierTransform(const QImage& image) {
	//转化为灰度图
	Mat srcImage = toGrayMat(image);
	
	//扩展图像
	int m = getOptimalDFTSize(srcImage.rows);
	int n = getOptimalDFTSize(srcImage.cols);

	Mat padded;
	copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));
	
	//傅里叶变换分配空间
	//多加一个额外通道来存储复数部分
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI);

	//进行傅里叶变换
	dft(complexI, complexI);

	//分离通道
	split(complexI, planes);
	magnitude(planes[0], planes[1], planes[0]);
	Mat magI = planes[0];

	//用对数尺度来替换线性尺度
	magI += Scalar::all(1);
	log(magI, magI);

	//剪切和重分布幅度图象限
	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

	int cx = magI.cols / 2;
	int cy = magI.rows / 2;

	Mat q0(magI, Rect(0, 0, cx, cy));
	Mat q1(magI, Rect(cx, 0, cx, cy));
	Mat q2(magI, Rect(0, cy, cx, cy));
	Mat q3(magI, Rect(cx, cy, cx, cy));

	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	//归一化
	normalize(magI, magI, 0, 1, NORM_MINMAX);

	//imshow("Input Image", srcImage);
	//imshow("spectrum magnitude", magI);
	//waitKey();

	return cvMat2QImage(magI);
}

QImage CVHelper::Histogram(const QImage& image)
{
	//转化为灰度图
	Mat srcImage = toGrayMat(image);

	//计算图像直方图
	int histsize = 256;//直方图等级
	float ranges[] = { 0,256 };//灰度级范围
	const float* histRanges = { ranges };
	Mat HistImage;
	calcHist(&srcImage, 1, 0, Mat(), HistImage, 1, &histsize, &histRanges, true, false);//计算直方图

	//创建直方图显示图像
	int hist_h = 300;//直方图的图像的高
	int hist_w = 512; //直方图的图像的宽
	int bin_w = hist_w / histsize;//直方图的等级
	normalize(HistImage, HistImage, 0, hist_h, NORM_MINMAX, -1, Mat());//归一化

	//绘制并显示直方图
	Mat output(hist_h, hist_w, CV_8UC3, Scalar(240, 240, 240));//灰色背景
	for (int i = 1; i < histsize; i++)//绘制直方曲线
		line(output, Point((i - 1) * bin_w, hist_h - cvRound(HistImage.at<float>(i - 1))),
						Point((i)*bin_w, hist_h - cvRound(HistImage.at<float>(i))), 
						Scalar(0, 0, 0), 2, 8, 0);//白色，线宽为2，8连通性，无法抗锯齿

	return cvMat2QImage(output);
}

QImage CVHelper::HistogramEqualization(const QImage& image)
{
	Mat output;
	equalizeHist(toGrayMat(image), output);
	return cvMat2QImage(output);
}


