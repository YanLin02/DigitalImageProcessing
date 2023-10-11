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
Mat CVHelper::QImage2cvMat(QImage& image) {
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

	//扩展图像（选）
	//int m = getOptimalDFTSize(srcImage.rows);
	//int n = getOptimalDFTSize(srcImage.cols);
	//copyMakeBorder(srcImage, srcImage, 0, m - srcImage.rows, 0, n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));

	//傅里叶变换分配空间
	//多加一个额外通道来存储复数部分
	Mat planes[] = { Mat_<float>(srcImage), Mat::zeros(srcImage.size(), CV_32F) };
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

/// @brief OpenCV的函数进行直方图获取
/// @param image 原始图像
/// @return 直方图
QImage CVHelper::Histogram(const QImage& image)
{
	//转化为灰度图
	Mat srcImage = toGrayMat(image);

	//计算图像直方图数组
	int histsize = 256;//直方图等级
	float ranges[] = { 0,256 };//灰度级范围
	const float* histRanges = { ranges };
	Mat HistNum;//容纳直方图数组
	calcHist(&srcImage, 1, 0, Mat(), HistNum, 1, &histsize, &histRanges, true, false);//计算直方图

	//通过数组创建直方图显示图像
	int hist_h = image.height();
	int hist_w = image.width();
	//TODO 宽度和高度自定义功能
	int bin_w = cvRound((double)hist_w / histsize);//单位宽度
	normalize(HistNum, HistNum, 0, hist_h, NORM_MINMAX, -1, Mat());//归一化

	//绘制并显示直方图
	Mat output(hist_h, hist_w, CV_8UC3, Scalar(240, 240, 240));//灰色背景
	for (int i = 1; i < histsize; i++)//绘制直方曲线
		line(output,
			Point((i - 1) * bin_w, hist_h - cvRound(HistNum.at<float>(i - 1))),
			Point((i)*bin_w, hist_h - cvRound(HistNum.at<float>(i))),
			Scalar(0, 0, 0), 2, 8, 0);//白色，线宽为2，连通性8

	return cvMat2QImage(output);
}

/// @brief 自己写的直方图获取
/// @param image 原始图像
/// @return 直方图
QImage CVHelper::myHistogram(const QImage& image)
{
	//转化为灰度图
	Mat srcImage = toGrayMat(image);

	//统计各个灰度级的像素个数
	int hist[256] = { 0 };
	for (int i = 0; i < srcImage.cols * srcImage.rows; i++)
		hist[srcImage.data[i]]++;

	//这里，x轴取个近似不归一了
	int n = srcImage.cols / 256;//每个灰度级的宽度

	Mat output(srcImage.rows, 256 * n, CV_8UC1, Scalar(0));
	int max = 0;
	for (int i = 0; i < 256; i++)
		if (hist[i] > max)
			max = hist[i];

	for (int i = 0; i < 256; i++) {
		int normalization = (double)hist[i] * srcImage.rows / max;//每次都要将数组的值根据最大值归一化
		for (int j = 0; j < n; j++)
			line(output, Point(n * i + j, output.rows - 1), Point(n * i + j, output.rows - 1 - normalization), Scalar(255, 255, 255));
	}

	return cvMat2QImage(output);
}

/// @brief OpenCV的函数进行直方图均衡化
/// @param image 原始图像
/// @return 均衡化后的图像
QImage CVHelper::HistogramEqualization(const QImage& image)
{
	Mat output;
	equalizeHist(toGrayMat(image), output);
	return cvMat2QImage(output);
}

/// @brief 自己写的直方图均衡化
/// @param image 原始图像
/// @return 均衡化后的图像
QImage CVHelper::myHistogramEqualization(const QImage& image)
{
	//转化为灰度图
	Mat srcImage = toGrayMat(image);

	//统计各个灰度级的像素个数
	int hist[256] = { 0 };
	for (int i = 0; i < srcImage.cols * srcImage.rows; i++)
		hist[srcImage.data[i]]++;


	//计算方式：255 * 累计概率

	int grayMap[256] = { 0 };//灰度映射表
	int SumOfProbability = 0;//累计概率
	for (int i = 0; i < 256; i++) {
		SumOfProbability += hist[i];
		grayMap[i] = (double)SumOfProbability / (srcImage.rows * srcImage.cols) * 255;
	}

	Mat output(srcImage.rows, srcImage.cols, CV_8UC1, Scalar(0));
	for (int i = 0; i < srcImage.rows * srcImage.cols; i++)
		output.data[i] = grayMap[srcImage.data[i]];//对每个像素点进行灰度映射

	return cvMat2QImage(output);
}

/// @brief CLAHE算法对图像的局部区域应用直方图均衡化来增强图像的对比度。
/// @param image 原始图像
/// @param ClipLimit 对比度限制阈值，默认为 40.0
/// @param TilesGridSize 区块尺寸，默认为 8x8
/// @return 处理后的图像
/// @note 避免了全局直方图均衡化可能引起的过度增强和噪点的问题
/// @note 将图像分成多个区块，并在每个区块内进行直方图均衡化，限制对比度的增强在每个区块中进行。
/// @note 由于每个区块的直方图都是局部的，这种方法对图像中不同区域的对比度变化有很好的效果。
/// @note 对比度限制阈值 拉高会增加图像细节，同时会增大噪声的影响
/// @note 区块尺寸 拉高会导致整体效果更加平滑，可能导致细节的丢失。
/// @note 膝盖图像设置 4 / 6 结果较好
QImage CVHelper::CLAHETran(const QImage& image, double ClipLimit, int TilesGridSize)
{
	//转化为灰度图
	Mat srcImage = toGrayMat(image);
	Mat output;
	Ptr<CLAHE> clahe = createCLAHE();
	clahe->setClipLimit(ClipLimit);  // 对比度限制阈值，默认为 40.0
	clahe->setTilesGridSize(Size(TilesGridSize, TilesGridSize));  // 区块尺寸，默认为 8x8
	clahe->apply(srcImage, output);

	return cvMat2QImage(output);
}


