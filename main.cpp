#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <QString>
#include <QDebug>




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::vector<cv::Rect> cars;
    double scale = 1;

    cv::VideoCapture cap("/home/andre/Documentos/opencv/cpp/car/build-CarTrack-Desktop-Debug/treci.mkv");

    cv::Mat gray, gray_blur, frame;
    cv::CascadeClassifier carCascade;

    bool b = carCascade.load("/home/andre/Documentos/opencv/cpp/car/build-CarTrack-Desktop-Debug/cars3.xml");
    if(b == false) { std::cout << "Load error of XML\n"; return -1; }


    while (true) {

        cap >> frame;

        if(frame.empty()){ std::cout << "Matriz vazia\n"; break; }

        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(gray, gray_blur, cv::Size(11,11), 0);
        carCascade.detectMultiScale(gray_blur, cars, 1.7, 2.1);



        for(size_t i = 0; i < cars.size(); i++)
        {
            cv::Rect r = cars[i];
            cv::Scalar color = cv::Scalar(255, 0, 0); // Color for Drawing tool



            cv::rectangle( frame, cv::Point(cvRound(r.x*scale), cvRound(r.y*scale)),
                           cv::Point(cvRound((r.x + r.width-1)*scale),
                                     cvRound((r.y + r.height-1)*scale)), color, 3, 8, 0);



            cv::imshow("Carros", frame);

        }

        char c = (char)cv::waitKey(10);

        // Press q to exit from window
        if( c == 27 || c == 'q' || c == 'Q' ){

            break;
            return 0;
        }

    }

    return a.exec();
}
