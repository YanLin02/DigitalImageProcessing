#include "CVHelper.h"

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

QImage CVHelper::FourierTransform(const QImage& image) {
	Mat srcImage = toGrayMat(image);

	int m = getOptimalDFTSize(srcImage.rows);
	int n = getOptimalDFTSize(srcImage.cols);

	Mat padded;
	copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));

	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI);

	dft(complexI, complexI);

	split(complexI, planes);
	magnitude(planes[0], planes[1], planes[0]);
	Mat magI = planes[0];

	magI += Scalar::all(1);
	log(magI, magI);

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

	normalize(magI, magI, 0, 1, NORM_MINMAX);

	//imshow("Input Image", srcImage);
	//imshow("spectrum magnitude", magI);
	//waitKey();

	return cvMat2QImage(magI);
}


