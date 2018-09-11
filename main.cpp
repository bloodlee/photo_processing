#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <sstream>
#include <string>
#include <rxcpp/rx.hpp>
#include <boost/asio.hpp>
#include <thread>
#include "thread_pool.h"

namespace Rx
{
    using namespace rxcpp;
    using namespace rxcpp::subjects;
    using namespace rxcpp::sources;
    using namespace rxcpp::operators;
    using namespace rxcpp::util;
}

using namespace cv;
using namespace std;
using namespace boost::asio;

namespace fs = std::experimental::filesystem::v1;

CascadeClassifier faceCascade;

int main() {
    // initialize the face cascade.
    faceCascade.load("G:\\Downloads\\OpenCV\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt2.xml");

    fs::path imgFolderPath("H:\\export_files");
    fs::directory_entry facesDirEntry(imgFolderPath);

    ThreadPool pool(10);

    for (auto& p : fs::directory_iterator(imgFolderPath)) {
        auto filePath = p.path().string();

        if (filePath.find("smaller") != string::npos) {
            cout << "Skip the file named " << filePath << endl;
            continue;
        }

        pool.enqueue([p, imgFolderPath] {
            Mat img = imread(p.path().string());
            Mat imgSmallerOne;

            resize(img, imgSmallerOne, Size(), 0.4, 0.4);

            stringstream ss;
            ss << p.path().stem() << "_smaller.jpg";

            cout << "Write resized img into file of " << ss.str() << " in t:"
                 << boost::this_thread::get_id() << endl;
            fs::path newPath = fs::path(imgFolderPath) / fs::path(ss.str()).c_str();
            imwrite(newPath.string(), imgSmallerOne);

            fs::remove(p);
        });
    }

    return 0;
}