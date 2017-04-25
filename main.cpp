#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "imbang.h"

using namespace cv;

int main() {
    imbang bang;

    string src = "/home/lunaticf/Desktop/JPEGImages";
    string dst = "/home/lunaticf/Desktop/Annotations";

    bang.ClearNotUsedImgByXML(src,dst);

    return 0;
}
