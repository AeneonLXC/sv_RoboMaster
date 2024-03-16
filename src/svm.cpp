// #include <iostream>
// #include <opencv2/opencv.hpp>

// using namespace cv;
// using namespace std;

// int main() {
//     // 加载模型
//     Ptr<ml::SVM> svm = ml::StatModel::load<ml::SVM>("svm_data_red.yml");

//     // 读取图像
//     string path = "your_image_directory/";
//     string tag = "num_5";
//     Mat frame = imread(path + tag + "/7.jpg");
//     Mat gray;
//     cvtColor(frame, gray, COLOR_BGR2GRAY);

//     // 将图像展平为一维数组
//     Mat img = gray.reshape(1, 1);
//     img.convertTo(img, CV_32F);

//     // 使用SVM进行预测
//     float result = svm->predict(img);

//     cout << "预测结果为: " << result << endl;

//     return 0;
// }
