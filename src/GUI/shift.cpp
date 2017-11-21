#include "shift.h"
void shift(const cv::Mat& src, cv::Mat& dst, cv::Point2f delta, int fill=cv::BORDER_CONSTANT, cv::Scalar value=cv::Scalar(0,0,0,0)) {

	// error checking
	assert(fabs(delta.x) < src.cols && fabs(delta.y) < src.rows);

	// split the shift into integer and subpixel components
	cv::Point2i deltai(ceil(delta.x), ceil(delta.y));
	cv::Point2f deltasub(fabs(delta.x - deltai.x), fabs(delta.y - deltai.y));

	// INTEGER SHIFT
	// first create a border around the parts of the Mat that will be exposed
	int t = 0, b = 0, l = 0, r = 0;
	if (deltai.x > 0) l =  deltai.x;
	if (deltai.x < 0) r = -deltai.x;
	if (deltai.y > 0) t =  deltai.y;
	if (deltai.y < 0) b = -deltai.y;
	cv::Mat padded;
	cv::copyMakeBorder(src, padded, t, b, l, r, fill, value);

	// SUBPIXEL SHIFT
	float eps = std::numeric_limits<float>::epsilon();
	if (deltasub.x > eps || deltasub.y > eps) {
		switch (src.depth()) {
			case CV_32F:
			{
				cv::Matx<float, 1, 2> dx(1-deltasub.x, deltasub.x);
				cv::Matx<float, 2, 1> dy(1-deltasub.y, deltasub.y);
				sepFilter2D(padded, padded, -1, dx, dy, cv::Point(0,0), 0, cv::BORDER_CONSTANT);
				break;
			}
			case CV_64F:
			{
				cv::Matx<double, 1, 2> dx(1-deltasub.x, deltasub.x);
				cv::Matx<double, 2, 1> dy(1-deltasub.y, deltasub.y);
				sepFilter2D(padded, padded, -1, dx, dy, cv::Point(0,0), 0, cv::BORDER_CONSTANT);
				break;
			}
			default:
			{
				cv::Matx<float, 1, 2> dx(1-deltasub.x, deltasub.x);
				cv::Matx<float, 2, 1> dy(1-deltasub.y, deltasub.y);
				padded.convertTo(padded, CV_32F);
				sepFilter2D(padded, padded, CV_32F, dx, dy, cv::Point(0,0), 0, cv::BORDER_CONSTANT);
				break;
			}
		}
	}

	// construct the region of interest around the new matrix
	cv::Rect roi = cv::Rect(std::max(-deltai.x,0),std::max(-deltai.y,0),0,0) + src.size();
	dst = padded(roi);
}


