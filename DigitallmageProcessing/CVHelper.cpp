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

/// @brief 保存文件为JPEG格式
/// @param image 原始图像
/// @param fileName 路径
/// @param quality 0-100 图像质量
/// @return 是否保存成功
bool CVHelper::saveAsJPEG(const QImage& image, const QString& fileName, int quality)
{
	Mat srcImage = toGrayMat(image);
	vector <int> compression_params;
	compression_params.push_back(IMWRITE_JPEG_QUALITY);
	compression_params.push_back(quality);
	return imwrite(fileName.toStdString(), srcImage, compression_params);
}

/// @brief 保存文件为JPEG2000格式
/// @param image 原始图像
/// @param fileName 路径
/// @param quality 0-100 图像质量
/// @return 是否保存成功
bool CVHelper::saveAsJPEG2000(const QImage& image, const QString& fileName, int quality)
{
	Mat srcImage = toGrayMat(image);
	vector <int> compression_params;
	compression_params.push_back(IMWRITE_JPEG2000_COMPRESSION_X1000);
	compression_params.push_back(quality * 10);
	return imwrite(fileName.toStdString(), srcImage, compression_params);
}

QImage CVHelper::Erosion(const QImage& image)
{
	Mat srcImage = toGrayMat(image);
	Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, CV_8UC1);

	//腐蚀操作
	for (int i = 0; i < srcImage.rows; ++i) {
		for (int j = 0; j < srcImage.cols; ++j) {
			uchar minV = 255;

			//遍历周围最小像素值
			for (int a = i - 1; a <= i + 1; a++) {
				for (int b = j - 1; b <= j + 1; b++) {
					if (b < 0 || b >= srcImage.cols || a < 0 || a >= srcImage.rows)
						continue;
					minV = (std::min<uchar>)(minV, srcImage.at<uchar>(a, b));
				}
			}
			dstImage.at<uchar>(i, j) = minV;
		}
	}
	return cvMat2QImage(dstImage);
}

QImage CVHelper::Dilation(const QImage& image)
{
	Mat srcImage = toGrayMat(image);
	Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, CV_8UC1);

	//腐蚀操作
	for (int i = 0; i < srcImage.rows; ++i) {
		for (int j = 0; j < srcImage.cols; ++j) {
			uchar maxV = 0;

			//遍历周围最大像素值
			for (int a = i - 1; a <= i + 1; a++) {
				for (int b = j - 1; b <= j + 1; b++) {
					if (b < 0 || b >= srcImage.cols || a < 0 || a >= srcImage.rows)
						continue;
					maxV = (std::max<uchar>)(maxV, srcImage.at<uchar>(a, b));
				}
			}
			dstImage.at<uchar>(i, j) = maxV;
		}
	}
	return cvMat2QImage(dstImage);
}

QImage CVHelper::GlobalThresholding(const QImage& image, int& threshold, int defth)
{
	const int delta = 0;
	Mat srcImage = toGrayMat(image);

	if (defth == -1) {
		Scalar mean = cv::mean(srcImage);
		threshold = mean[0];
	}
	else {
		threshold = defth;
	}

	//计算图像直方图数组
	int histsize = 256;//直方图等级
	float ranges[] = { 0,256 };//灰度级范围
	const float* histRanges = { ranges };
	Mat HistNum;//容纳直方图数组
	calcHist(&srcImage, 1, 0, Mat(), HistNum, 1, &histsize, &histRanges, true, false);//计算直方图

	int old = threshold;

	do
	{
		old = threshold;
		int sum1 = 0, sum2 = 0, num1 = 0, num2 = 0;
		for (int i = 0; i < threshold; i++) {
			sum1 += i * HistNum.at<float>(i);
			num1 += HistNum.at<float>(i);
		}
		for (int i = threshold; i < 256; i++) {
			sum2 += i * HistNum.at<float>(i);
			num2 += HistNum.at<float>(i);
		}
		threshold = (sum1 / num1 + sum2 / num2) / 2;
	} while (abs(threshold - old) > delta);

	Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, CV_8UC1);

	for (int i = 0; i < srcImage.rows; ++i) {
		for (int j = 0; j < srcImage.cols; ++j) {
			dstImage.at<uchar>(i, j) = srcImage.at<uchar>(i, j) > threshold ? 255 : 0;
		}
	}

	return cvMat2QImage(dstImage);
}

QImage CVHelper::OstusThresholding(const QImage& image, int& threshold)
{
	Mat srcImage = toGrayMat(image);

	//计算图像直方图数组
	const int grayscale = 256;//直方图等级
	float ranges[] = { 0,256 };//灰度级范围
	const float* histRanges = { ranges };
	Mat HistNum;//容纳直方图数组
	calcHist(&srcImage, 1, 0, Mat(), HistNum, 1, &grayscale, &histRanges, true, false);//计算直方图

	double P[grayscale] = { 0 };
	double PK[grayscale] = { 0 };
	double MK[grayscale] = { 0 };
	double srcpixnum = srcImage.rows * srcImage.cols, sumtmpPK = 0, sumtmpMK = 0;
	for (int i = 0; i < grayscale; ++i) {
		P[i] = HistNum.at<float>(i) / srcpixnum;   //每个灰度级出现的概率
		PK[i] = sumtmpPK + P[i];         //概率累计和 
		sumtmpPK = PK[i];
		MK[i] = sumtmpMK + i * P[i];       //灰度级的累加均值                                                                                                                                                                                                                                                                                                                                                                                                        
		sumtmpMK = MK[i];
	}

	//计算类间方差
	double temp = 0;
	for (int k = 0; k < grayscale; ++k) {
		if ((MK[grayscale - 1] * PK[k] - MK[k]) * (MK[grayscale - 1] * PK[k] - MK[k]) / (PK[k] * (1 - PK[k])) > temp) {
			temp = (MK[grayscale - 1] * PK[k] - MK[k]) * (MK[grayscale - 1] * PK[k] - MK[k]) / (PK[k] * (1 - PK[k]));
			threshold = k;
		}
	}

	Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, CV_8UC1);

	for (int i = 0; i < srcImage.rows; ++i) {
		for (int j = 0; j < srcImage.cols; ++j) {
			dstImage.at<uchar>(i, j) = srcImage.at<uchar>(i, j) > threshold ? 255 : 0;
		}
	}

	return cvMat2QImage(dstImage);
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
/// @note 不再使用，因为自己写的直方图获取更加方便
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
	//宽度和高度自定义功能
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
/// @note 不再使用，因为自己写的直方图均衡化更加方便
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

/// @brief 为图片添加高斯噪声
/// @param image 图片
/// @param mean 均值
/// @param sigma 标准差
/// @return 添加噪声后的图片
QImage CVHelper::AddGaussNoice(const QImage& image, double mean, double sigma)
{
	//转化为灰度图
	Mat srcImage = toGrayMat(image);
	//生成高斯噪声
	Mat noise = Mat::zeros(srcImage.rows, srcImage.cols, srcImage.type());
	RNG rng;//创建一个RNG类<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<可以添加随机种子
	rng.fill(noise, RNG::NORMAL, mean, sigma);//生成高斯分布随机数
	Mat dstImage = srcImage + noise;//添加高斯噪声

	return cvMat2QImage(dstImage);
}

/// @brief 为图片添加椒盐噪声
/// @param image 图片
/// @param p 椒盐噪声密度
/// @return 添加噪声后的图片
QImage CVHelper::AddSAPNoice(const QImage& image, double p)
{
	//转化为灰度图
	Mat srcImage = toGrayMat(image);
	//生成椒盐噪声
	for (int i = 0; i < srcImage.rows * srcImage.cols * p; i++)
		srcImage.at<uchar>(rand() % srcImage.rows, rand() % srcImage.cols) = (rand() % 2) ? 0 : 255;

	return cvMat2QImage(srcImage);
}

/// @brief CV的中值滤波
/// @param image 图像
/// @param ksize 核大小
/// @return 滤波后的图像
QImage CVHelper::MedianFilter(const QImage& image, int ksize)
{
	//转化为灰度图
	Mat srcImage = toGrayMat(image);
	//中值滤波
	Mat dstImage;//中值滤波后的图像
	medianBlur(srcImage, dstImage, ksize);
	return cvMat2QImage(dstImage);
}

/// @brief 自己写的中值滤波
/// @param image 图像
/// @param ksize 核大小
/// @return 滤波后的图像
/// @note 由于中值滤波是非线性滤波，所以不能用卷积的方式来实现
/// @note 本函数采用的是直接遍历的方式，效率较低<超级超级慢>
QImage CVHelper::myMedianFilter(const QImage& image, int ksize)
{
	//转化为灰度图
	Mat srcImage = toGrayMat(image);

	Mat dstImage;
	dstImage = dstImage.zeros(srcImage.rows, srcImage.cols, srcImage.type());

	copyMakeBorder(srcImage, srcImage, ksize / 2, ksize / 2, ksize / 2, ksize / 2, BORDER_REPLICATE);//复制边界
	//核
	uchar* data = new uchar[ksize * ksize];
	//中值滤波
	for (int i = ksize / 2; i < srcImage.rows - ksize / 2; i++)
		for (int j = ksize / 2; j < srcImage.cols - ksize / 2; j++) {
			int k = 0;
			for (int m = i - ksize / 2; m <= i + ksize / 2; m++)
				for (int n = j - ksize / 2; n <= j + ksize / 2; n++)
					data[k++] = srcImage.at<uchar>(m, n);
			std::sort(data, data + ksize * ksize);
			dstImage.at<uchar>(i - ksize / 2, j - ksize / 2) = data[ksize * ksize / 2];
		}

	delete[] data;

	return cvMat2QImage(dstImage);
}

/// @brief CV的均值滤波
/// @param image 图像
/// @param ksize 核大小
/// @return 滤波后的图像
QImage CVHelper::AverageFilter(const QImage& image, int ksize)
{
	//转化为灰度图
	Mat srcImage = toGrayMat(image);
	//中值滤波
	Mat dstImage;//中值滤波后的图像
	blur(srcImage, dstImage, Size(ksize, ksize));
	return cvMat2QImage(dstImage);
}

/// @brief 我的均值滤波
/// @param image 图像
/// @param ksize 核大小
/// @return 滤波后的图像
QImage CVHelper::myAverageFilter(const QImage& image, int ksize)
{
	//转化为灰度图
	Mat srcImage = toGrayMat(image);

	Mat dstImage;
	dstImage = dstImage.zeros(srcImage.rows, srcImage.cols, srcImage.type());

	copyMakeBorder(srcImage, srcImage, ksize / 2, ksize / 2, ksize / 2, ksize / 2, BORDER_REPLICATE);//复制边界

	//均值滤波
	for (int i = ksize / 2; i < srcImage.rows - ksize / 2; i++)
		for (int j = ksize / 2; j < srcImage.cols - ksize / 2; j++) {
			int k = 0;
			int sum = 0;
			for (int m = i - ksize / 2; m <= i + ksize / 2; m++)
				for (int n = j - ksize / 2; n <= j + ksize / 2; n++)
					sum += srcImage.at<uchar>(m, n);
			dstImage.at<uchar>(i - ksize / 2, j - ksize / 2) = sum / (ksize * ksize);
		}

	return cvMat2QImage(dstImage);
}

/// @brief 自适应中值滤波
/// @param image 图像
/// @param Maxsize 最大核大小
/// @param Minsize 初始核大小
/// @return 滤波后的图像
QImage CVHelper::AdaptiveMedianFilters(const QImage& image, int Maxsize, int Minsize)
{
	//转化为灰度图
	Mat srcImage = toGrayMat(image);

	Mat dstImage;
	dstImage = dstImage.zeros(srcImage.rows, srcImage.cols, srcImage.type());

	copyMakeBorder(srcImage, srcImage, Maxsize / 2, Maxsize / 2, Maxsize / 2, Maxsize / 2, BORDER_REPLICATE);//复制边界

	for (int i = Maxsize / 2; i < srcImage.rows - Maxsize / 2; i++)
		for (int j = Maxsize / 2; j < srcImage.cols - Maxsize / 2; j++)
			dstImage.at<uchar>(i - Maxsize / 2, j - Maxsize / 2) = adaptiveProcess(srcImage, i, j, Minsize, Maxsize);

	return cvMat2QImage(dstImage);
}

/// @brief 自适应中值滤波的递归函数
/// @param im 图像
/// @param row 当前行
/// @param col 当前列
/// @param kernelSize 核大小
/// @param maxSize 最大核大小
/// @return 处理后的像素值
/// @note 工具函数
uchar CVHelper::adaptiveProcess(const Mat& im, int row, int col, int kernelSize, int maxSize)
{
	uchar* pixels = new uchar[kernelSize * kernelSize];
	int index = 0;

	for (int a = -kernelSize / 2; a <= kernelSize / 2; a++)
		for (int b = -kernelSize / 2; b <= kernelSize / 2; b++)
			pixels[index++] = im.at<uchar>(row + a, col + b);

	std::sort(pixels, pixels + kernelSize * kernelSize);

	uchar Fmin = pixels[0];//最小值
	uchar Fmax = pixels[kernelSize * kernelSize - 1];//最大值
	uchar Fmed = pixels[kernelSize * kernelSize / 2];//中值
	uchar Fij = im.at<uchar>(row, col);//当前值

	delete[] pixels;

	if (Fmed > Fmin && Fmed < Fmax) {//中值在最大最小值之间,转到第二步
		if (Fij > Fmin && Fij < Fmax)//当前值在最大最小值之间
			return Fij;
		else
			return Fmed;
	}
	else {//中值不在最大最小值之间,转到第一步
		kernelSize += 2;
		if (kernelSize <= maxSize)//核大小小于最大核大小
			return adaptiveProcess(im, row, col, kernelSize, maxSize); //增大窗口尺寸
		else
			return Fmed;
	}
}

/// @brief 非局部均值滤波
/// @param image 图像
/// @param KernelSize 周边核大小
/// @param searchWindowSize 扫描范围
/// @param h h越大去噪效果越好，但是图像越模糊，反之h越小去噪效果越差，但去噪之后的失真度越小。
/// @return 滤波后的图像
QImage CVHelper::NonlocalMeansFilter(const QImage& image, int KernelSize, int searchWindowSize, double h)
{
	//转化为灰度图
	Mat srcImage = toGrayMat(image);

	//输出图像
	Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, CV_8UC1);

	//预计算
	float* table1 = new float[256];//存储0-255的平方
	//float table1[256] = { 0 };//存储0-255的平方
	for (int i = 0; i < 256; i++)
		table1[i] = (float)(i * i);

	uchar** table2 = new uchar * [256];//存储0-255的差值的绝对值
	for (int i = 0; i < 256; i++)
		table2[i] = new uchar[256];
	//uchar table2[256][256] = { 0 };//存储0-255的差值的绝对值
	for (int i = 0; i < 256; i++)
		for (int j = i; j < 256; j++) {
			table2[i][j] = abs(i - j);
			table2[j][i] = table2[i][j];
		}

	int rows = srcImage.rows;//行数
	int cols = srcImage.cols;//列数
	int halfKernelSize = KernelSize / 2;//半核大小
	int halfSearchSize = searchWindowSize / 2;//半搜索框大小
	int boardSize = halfKernelSize + halfSearchSize;//边界大小
	copyMakeBorder(srcImage, srcImage, boardSize, boardSize, boardSize, boardSize, BORDER_REFLECT);//边界扩展
	double h2 = h * h;//h的平方

	//计算每个像素点的值
	for (int j = boardSize; j < boardSize + rows; j++) {//行遍历
		uchar* dst_p = dstImage.ptr<uchar>(j - boardSize);//输出图像的行指针。提高效率，比at快
		for (int i = boardSize; i < boardSize + cols; i++) {//列遍历
			//对于每个像素点，有如下计算：
			Mat patchA = srcImage(Range(j - halfKernelSize, j + halfKernelSize), Range(i - halfKernelSize, i + halfKernelSize));//当前像素点的核

			double w = 0;//权重
			double p = 0;//像素值》累加计算
			double sumw = 0;//权重和

			for (int sr = -halfSearchSize; sr <= halfSearchSize; sr++) {//在搜索框内遍历搜索 sr:search row, sc:search col
				uchar* boardSrc_p = srcImage.ptr<uchar>(j + sr);
				for (int sc = -halfSearchSize; sc <= halfSearchSize; sc++) {
					//对于搜索框内的每个像素点，有如下计算：
					Mat patchB = srcImage(Range(j + sr - halfKernelSize, j + sr + halfKernelSize), Range(i + sc - halfKernelSize, i + sc + halfKernelSize));//搜索框内遍历的核

					//计算两个核的均方误差
					float MSE = 0.0;
					for (int a = 0; a < patchA.rows; a++) {
						uchar* data1 = patchA.ptr<uchar>(a);
						uchar* data2 = patchB.ptr<uchar>(a);
						for (int b = 0; b < patchA.cols; b++)
							MSE += table1[table2[data1[b]][data2[b]]];//两点灰度差值的平方累计
					}
					MSE = MSE / (patchA.rows * patchB.cols);//除以核的大小

					w = exp(-MSE / h2);
					p += boardSrc_p[i + sc] * w;//像素值乘以权重 的累计
					sumw += w;
				}
			}
			dst_p[i - boardSize] = saturate_cast<uchar>(p / sumw);//该点赋值
		}
	}
	delete[] table1;
	for (int i = 0; i < 256; i++)
		delete[] table2[i];
	delete[] table2;
	return cvMat2QImage(dstImage);
}

/// @brief 自适应局部降噪滤波
/// @param image 图像
/// @param LocalHalfSize 局部大小
/// @param noiseVar 噪声方差
/// @return 滤波后的图像
QImage CVHelper::AdaptiveLocalFilter(const QImage& image, int LocalHalfSize, double noiseVar)
{
	//转化为灰度图
	Mat srcImage = toGrayMat(image);

	//输出图像
	Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, CV_8UC1);

	copyMakeBorder(srcImage, srcImage, LocalHalfSize, LocalHalfSize, LocalHalfSize, LocalHalfSize, BORDER_REFLECT);


	for (int i = LocalHalfSize; i < srcImage.rows - LocalHalfSize; i++)
		for (int j = LocalHalfSize; j < srcImage.cols - LocalHalfSize; j++)
		{
			Mat local(srcImage, Rect(j - LocalHalfSize, i - LocalHalfSize, 2 * LocalHalfSize + 1, 2 * LocalHalfSize + 1));//局部块
			Mat m_localMean, m_localStddev; //局部均值标准差矩阵
			double localmean, localstddev;  //图像标准差，局部均值和标准差
			meanStdDev(local, m_localMean, m_localStddev); //获取局部块的平均值和标准差矩阵
			localmean = m_localMean.at<double>(0, 0);  //局部均值
			localstddev = m_localStddev.at<double>(0, 0);  //局部标准差

			double k;  //滤波系数
			if (localstddev == 0)//防止除0
				k = 1;
			else
				k = (noiseVar * noiseVar) / (localstddev * localstddev);

			if (k < 1)//防止k大于1
				dstImage.at<uchar>(i - LocalHalfSize, j - LocalHalfSize) = srcImage.at<uchar>(i, j) - k * (srcImage.at<uchar>(i, j) - localmean);
			else
				dstImage.at<uchar>(i - LocalHalfSize, j - LocalHalfSize) = localmean;
		}

	return cvMat2QImage(dstImage);
}

/// @brief 二阶导数图像增强
/// @param image 图像
/// @return 增强后的图像
QImage CVHelper::SecondDerivative(const QImage& image)
{
	//转化为灰度图
	Mat srcImage = toGrayMat(image);
	Mat dstImage = srcImage.clone();

	copyMakeBorder(srcImage, srcImage, 1, 1, 1, 1, BORDER_REPLICATE);//复制边界

	int kernel[9] = {
		0, -1, 0,
		-1, 4, -1,
		0, -1, 0 };

	//int kernel[9] = {
	//-1, -1, -1,
	//-1,  8, -1,
	//-1, -1, -1 };

	int pix;
	for (int i = 1; i < srcImage.rows - 1; i++) {
		for (int j = 1; j < srcImage.cols - 1; j++) {
			pix = kernel[0] * srcImage.at<uchar>(i - 1, j - 1)
				+ kernel[1] * srcImage.at<uchar>(i - 1, j)
				+ kernel[2] * srcImage.at<uchar>(i - 1, j + 1)
				+ kernel[3] * srcImage.at<uchar>(i, j - 1)
				+ kernel[4] * srcImage.at<uchar>(i, j)
				+ kernel[5] * srcImage.at<uchar>(i, j + 1)
				+ kernel[6] * srcImage.at<uchar>(i + 1, j - 1)
				+ kernel[7] * srcImage.at<uchar>(i + 1, j)
				+ kernel[8] * srcImage.at<uchar>(i + 1, j + 1);

			dstImage.at<uchar>(i - 1, j - 1) = saturate_cast<uchar>(dstImage.at<uchar>(i - 1, j - 1) + pix);
		}
	}

	return cvMat2QImage(dstImage);
}

/// @brief 非锐化掩蔽
/// @param image 图像
/// @param weight 增强权重
/// @return 增强后的图像
QImage CVHelper::UnsharpMasking(const QImage& image, double weight)
{
	//转化为灰度图
	Mat srcImage = toGrayMat(image);

	Mat unsharp;
	GaussianBlur(srcImage, unsharp, Size(5, 5), 5);//高斯模糊

	Mat mask = srcImage - unsharp;//掩膜

	Mat dstImage = srcImage + weight * mask;//锐化

	return cvMat2QImage(dstImage);
}
