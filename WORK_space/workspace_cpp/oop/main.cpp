#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <string>

using namespace cv;
using namespace std;

int main() {
    // 1. 定义棋盘格尺寸
    const int boardWidth = 7;  // 棋盘格的内部角点数量（列数）
    const int boardHeight = 6; // 棋盘格的内部角点数量（行数）
    const Size boardSize(boardWidth, boardHeight);
    const float squareSize = 0.108;  // 棋盘格每个小方块的实际大小（米）

    // 2. 读取相机采集的标定板图像
    vector<String> imagePaths;
    glob("images", imagePaths); // 替换为你图像所在路径
    vector<vector<Point2f>> imagePoints;
    vector<vector<Point3f>> objectPoints;
    vector<Point3f> objp;

    // 计算棋盘格的世界坐标点
    for (int i = 0; i < boardHeight; ++i) {
        for (int j = 0; j < boardWidth; ++j) {
            objp.push_back(Point3f(j * squareSize, i * squareSize, 0));
        }
    }

    Size imageSize;  // 只定义一次

    for (const auto& imagePath : imagePaths) {
        Mat img = imread(imagePath);
        if (img.empty()) {
            cerr << "Failed to load image: " << imagePath << endl;
            continue;
        }
        if (imageSize == Size()) {
            imageSize = img.size();  // 使用第一张图像的尺寸
        }

        Mat gray;
        cvtColor(img, gray, COLOR_BGR2GRAY);

        vector<Point2f> corners;
        bool found = findChessboardCorners(gray, boardSize, corners,
                                           CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FAST_CHECK | CALIB_CB_NORMALIZE_IMAGE);
        if (found) {
            cornerSubPix(gray, corners, Size(11, 11), Size(-1, -1), 
                         TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.01));
            drawChessboardCorners(img, boardSize, corners, found);
            imshow("Chessboard", img);
            waitKey(500);

            imagePoints.push_back(corners);
            objectPoints.push_back(objp);
        }
    }

    // 3. 计算相机内参矩阵和畸变系数
    Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
    Mat distCoeffs = Mat::zeros(8, 1, CV_64F);
    vector<Mat> rvecs, tvecs;
    calibrateCamera(objectPoints, imagePoints, imageSize, cameraMatrix, distCoeffs, rvecs, tvecs);

    // 打印相机内参和畸变系数
    cout << "Camera Matrix: " << endl << cameraMatrix << endl;
    cout << "Distortion Coefficients: " << endl << distCoeffs << endl;

    // 4. 畸变矫正
    Mat map1, map2;
    Mat img = imread(imagePaths[0]);  // 读取一张图像进行畸变矫正
    if (img.empty()) {
        cerr << "Failed to load image for undistortion" << endl;
        return -1;
    }
    initUndistortRectifyMap(cameraMatrix, distCoeffs, Mat(),
                            getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, imageSize, 0, imageSize, 0),
                            imageSize, CV_16SC2, map1, map2);
    Mat imgUndistorted;
    remap(img, imgUndistorted, map1, map2, INTER_LINEAR);
    imshow("Undistorted Image", imgUndistorted);
    waitKey(0);

    return 0;
}
