#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
using namespace cv;
using namespace std;
Mat videoFrame;
int rho = 100;

void Hough(const Mat &input, std::vector<Vec4i>&lines) {
	Mat contours;
	Canny(input, contours, 50, 150);
	lines.clear();
	HoughLinesP(contours, lines, 1, CV_PI / 180, 50, 100);
}

void drawLines(Mat &input, const std::vector<Vec4i> &lines) {
	cvtColor(videoFrame, videoFrame, COLOR_GRAY2BGR);
	for (int i = 0; i < lines.size(); i++) {
		line(input, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(255, 0, 0), 2);
	}
	imshow("frame", videoFrame);
}

int main() {
	int switch_value = 100;
	VideoCapture cap;
	char input = 0;
	cap.open(0);
	while (1) {
		if (!cap.read(videoFrame)) break;
		cvCreateTrackbar("Threshold", "frame", &switch_value, 255);

		imshow("video", videoFrame);
		vector<Vec4i> linesP;
		cvtColor(videoFrame, videoFrame, COLOR_BGR2GRAY);




		threshold(videoFrame, videoFrame, switch_value, 255, THRESH_BINARY);
		Hough(videoFrame, linesP);
		cout << linesP.size() << endl;
		drawLines(videoFrame, linesP);


		input = cv::waitKey(1);
		if (input == 's') {
			imwrite("photo.jpg", videoFrame);
		}
		else if (input == 'q') {
			break;
		}
	}
	system("pause");
	destroyAllWindows();
	return 0;
}