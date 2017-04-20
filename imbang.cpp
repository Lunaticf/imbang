//
// Created by lunaticf on 17-4-18.
//


#include <iostream>
#include <dirent.h>
#include <string>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "imbang.h"
#include "tinyxml2.h"

using namespace std;
using namespace cv;
using namespace tinyxml2;

void imbang::fileUnderDir(const string &dirName, int mode){
    // open specific dir
    DIR* dir = opendir(dirName.c_str());
    if(dir == NULL){
        cout<<"The dir not exist!";
    } else {
        dirent* p = NULL;

        while((p = readdir(dir)) != NULL)
        {
            if(p->d_name[0] != '.')
            {
                string filename = string(p->d_name);
                if(mode == 1){
                    imgBarn.push_back(filename);
                } else {
                    xmlBarn.push_back(filename);
                }
            }
        }
        closedir(dir);
    }
}

void imbang::enhancePicByLapa(const string &dirName,const string dstDirName, bool processAll){
    fileUnderDir(dirName,1);
    if(processAll){
        for(auto &el:imgBarn){
            string str = dirName + "/" + el;
            Mat image = imread(str);
            if (image.empty())
            {
                cout << "打开图片失败,请检查" << endl;
                return;
            }
            cout<<str + "    processing";
            Mat imageEnhance;
            el[0] = '9';
            el[1] = '4';

            Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, 0,3.5, 0, 0, -1, 0);
            filter2D(image, imageEnhance, CV_8UC3, kernel);
            string saveImagePath = dstDirName + "/" + el;
            imwrite(saveImagePath,imageEnhance);
            cout<<endl<<saveImagePath<<"    saved"<<endl;
        }
    }
    imgBarn.clear();
}

void imbang::batchBlur(const string &dirName,const string &dstDirName,const string &prefix){
    fileUnderDir(dirName,1);
    for(auto &el:imgBarn){
        string str = dirName + "/" + el;
            Mat image = imread(str);
            if (image.empty())
            {
                cout << "打开图片失败,请检查" << endl;
                return;
            }
            cout<<str + "    processing";
            el[0] = prefix[0];
            el[1] = prefix[1];
            Mat bluredImg;
            blur( image,bluredImg, Size( 7, 7), Point(-1,-1) );


            string saveImagePath = dstDirName + "/" + el;
            imwrite(saveImagePath,bluredImg);
            cout<<endl<<saveImagePath<<"    saved"<<endl;
    }
    imgBarn.clear();
}


void imbang::batchGaussianBlur(const string &dirName,const string &dstDirName,const string &prefix){
    fileUnderDir(dirName,1);
    for(auto &el:imgBarn){
        string str = dirName + "/" + el;
        Mat image = imread(str);
        if (image.empty())
        {
            cout << "打开图片失败,请检查" << endl;
            return;
        }
        cout<<str + "    processing";
        el[0] = prefix[0];
        el[1] = prefix[1];
        Mat bluredImg;
        GaussianBlur( image,bluredImg, Size( 5, 5),0,0);


        string saveImagePath = dstDirName + "/" + el;
        imwrite(saveImagePath,bluredImg);
        cout<<endl<<saveImagePath<<"    saved"<<endl;
    }
    imgBarn.clear();
}

void imbang::batchMedianBlur(const string &dirName,const string &dstDirName,const string &prefix){
    fileUnderDir(dirName,1);
    for(auto &el:imgBarn){
        string str = dirName + "/" + el;
        Mat image = imread(str);
        if (image.empty())
        {
            cout << "打开图片失败,请检查" << endl;
            return;
        }
        cout<<str + "    processing";
        el[0] = prefix[0];
        el[1] = prefix[1];
        Mat bluredImg;
        medianBlur( image,bluredImg,7);


        string saveImagePath = dstDirName + "/" + el;
        imwrite(saveImagePath,bluredImg);
        cout<<endl<<saveImagePath<<"    saved"<<endl;
    }
    imgBarn.clear();
}


void imbang::batchBilateralBlur(const string &dirName,const string &dstDirName,const string &prefix){
    fileUnderDir(dirName,1);
    for(auto &el:imgBarn){
        string str = dirName + "/" + el;
        Mat image = imread(str);
        if (image.empty())
        {
            cout << "打开图片失败,请检查" << endl;
            return;
        }
        cout<<str + "    processing";
        el[0] = prefix[0];
        el[1] = prefix[1];
        Mat bluredImg;
        bilateralFilter(image,bluredImg, 25, 25*2, 25/2);


        string saveImagePath = dstDirName + "/" + el;
        imwrite(saveImagePath,bluredImg);
        cout<<endl<<saveImagePath<<"    saved"<<endl;
    }
    imgBarn.clear();
}




void imbang::batchAlterXMLNode(const string &dirName,const string &imageDir){
    fileUnderDir(imageDir,1);
    fileUnderDir(dirName,2);
    std::sort(xmlBarn.begin(),xmlBarn.end());
    std::sort(imgBarn.begin(),imgBarn.end());


    int i = 0;
    for(auto &el:xmlBarn){
        XMLDocument doc;
        string filePath = dirName + "/" +el;
        doc.LoadFile(filePath.c_str());

        //initialize root node
        XMLElement *RootElement = doc.RootElement();
        XMLElement *fileNameNode = RootElement->FirstChildElement()->NextSiblingElement();
        fileNameNode->SetText((imgBarn[i++]).c_str());
        doc.SaveFile(filePath.c_str());
    }

    imgBarn.clear();
    xmlBarn.clear();
}

void imbang::batchAlterXMLName(const string &dirName, const string &prefix){
    fileUnderDir(dirName,2);
    for(auto &el:xmlBarn){
        string filePath = dirName + "/" + el;
        el[0] = prefix[0];
        el[1] = prefix[1];
        string toFilePath = dirName + "/" + el;
        rename(filePath.c_str(),toFilePath.c_str());
        cout<<toFilePath<<"          rename successful!"<<endl;
    }

    imgBarn.clear();
    xmlBarn.clear();

}


void imbang::enhancePicByLog(const string &dirName,const string dstDirName,const string &prefix){
    fileUnderDir(dirName,1);
        for(auto &el:imgBarn){
            string str = dirName + "/" + el;
            Mat image = imread(str);
            if (image.empty())
            {
                cout << "打开图片失败,请检查" << endl;
                return;
            }
            cout<<str + "    processing";
            el[0] = prefix[0];
            el[1] = prefix[1];

            Mat imageLog(image.size(), CV_32FC3);
            for (int i = 0; i < image.rows; i++)
            {
                for (int j = 0; j < image.cols; j++)
                {
                    imageLog.at<Vec3f>(i, j)[0] = log(1 + image.at<Vec3b>(i, j)[0]);
                    imageLog.at<Vec3f>(i, j)[1] = log(1 + image.at<Vec3b>(i, j)[1]);
                    imageLog.at<Vec3f>(i, j)[2] = log(1 + image.at<Vec3b>(i, j)[2]);
                }
            }
            //归一化到0~255
            normalize(imageLog, imageLog, 0, 255, CV_MINMAX);

            //转换成8bit图像显示
            convertScaleAbs(imageLog, imageLog);
            string saveImagePath = dstDirName + "/" + el;
            imwrite(saveImagePath,imageLog);
            cout<<endl<<saveImagePath<<"    saved"<<endl;
        }
    imgBarn.clear();
}

void imbang::batchSobel(const string &dirName,const string dstDirName,const string &prefix){
    fileUnderDir(dirName,1);
    Mat grad_x,grad_y;
    Mat abs_grad_x,abs_grad_y,dst;
    for(auto &el:imgBarn){
        string str = dirName + "/" + el;
        Mat image = imread(str);
        if (image.empty())
        {
            cout << "打开图片失败,请检查" << endl;
            return;
        }
        cout<<str + "    processing";
        el[0] = prefix[0];
        el[1] = prefix[1];

        Sobel(image, grad_x,CV_16S,1,0,3,1,1,BORDER_DEFAULT);
        convertScaleAbs(grad_x,abs_grad_x);

        Sobel(image, grad_y,CV_16S,0,1,3,1,1,BORDER_DEFAULT);
        convertScaleAbs(grad_y,abs_grad_y);

        addWeighted(abs_grad_x,0.5,abs_grad_y,0.5,0,dst);

        string saveImagePath = dstDirName + "/" + el;
        imwrite(saveImagePath,dst);

        cout<<endl<<saveImagePath<<"    saved"<<endl;
    }
    imgBarn.clear();
}

void imbang::batchNoise(const string &dirName,const string dstDirName,const string &prefix,int noiseNum){
    fileUnderDir(dirName,1);

    for(auto &el:imgBarn){
        string str = dirName + "/" + el;
        Mat image = imread(str);
        if (image.empty())
        {
            cout << "打开图片失败,请检查" << endl;
            return;
        }
        cout<<str + "    processing";
        el[0] = prefix[0];
        el[1] = prefix[1];

            for(int k=0;k<noiseNum;k++)
            {
                int i=rand()%image.cols;
                int j=rand()%image.rows;
                if(image.channels()==1)
                {
                    image.at<uchar>(j,i)=255;
                }
                else if(image.channels()==3)
                {
                    image.at<Vec3b>(j,i)[0]=255;
                    image.at<Vec3b>(j,i)[1]=255;
                    image.at<Vec3b>(j,i)[2]=255;
                }
            }

        string saveImagePath = dstDirName + "/" + el;
        imwrite(saveImagePath,image);

        cout<<endl<<saveImagePath<<"    saved"<<endl;
    }
    imgBarn.clear();
}

void imbang::batchRotate(const string &dirName,const string dstDirName,const string &prefix, int degree){
    fileUnderDir(dirName,1);
    for(auto &el:imgBarn){
        string str = dirName + "/" + el;
        Mat image = imread(str);
        if (image.empty())
        {
            cout << "打开图片失败,请检查" << endl;
            return;
        }
        cout<<str + "    processing";
        el[0] = prefix[0];
        el[1] = prefix[1];

        double angle = degree * CV_PI / 180.; // 旋转角度
        double a = sin(angle), b = cos(angle);
        int width = image.cols;
        int height = image.rows;
        int width_rotate = int(height * fabs(a) + width * fabs(b));
        int height_rotate = int(width * fabs(a) + height * fabs(b));

        //生成仿射变换矩阵
        float map[6];
        Mat map_matrix = Mat(2, 3, CV_32F, map);
        CvPoint2D32f center = cvPoint2D32f(width / 2, height / 2);
        CvMat map_matrix2 = map_matrix;
        cv2DRotationMatrix(center, degree, 1.0, &map_matrix2);
        map[2] += (width_rotate - width) / 2;
        map[5] += (height_rotate - height) / 2;

        Mat img_rotate;
        float *tmp = (float *)map_matrix.data;
        warpAffine(image, img_rotate, map_matrix, Size(width_rotate, height_rotate), 1, 0, 0);	//仿射变换函数
//        for (int i = 0; i < 6; i++) {
//            varyData[i] = tmp[i];
//        }


        string saveImagePath = dstDirName + "/" + el;
        imwrite(saveImagePath,img_rotate);

        cout<<endl<<saveImagePath<<"    saved"<<endl;
    }
    imgBarn.clear();
}

void imbang::alterXMLofRotate(const string &dirName, vector<double> &varyData) {
    fileUnderDir(dirName,2);
    std::sort(xmlBarn.begin(),xmlBarn.end());

    int i = 0;
    for(auto &el:xmlBarn){
        XMLDocument doc;
        string filePath = dirName + "/" +el;
        // read a xml
        doc.LoadFile(filePath.c_str());

        //initialize root node
        XMLElement *RootElement = doc.RootElement();

        XMLElement *locationNode = RootElement->FirstChildElement("object");
        while(locationNode){
            XMLElement *bndBox = locationNode->FirstChildElement("bndbox");

            XMLElement *xmin = bndBox->FirstChildElement("xmin");
            XMLElement *ymin = bndBox->FirstChildElement("ymin");
            XMLElement *xmax = bndBox->FirstChildElement("xmax");
            XMLElement *ymax = bndBox->FirstChildElement("ymax");

            double oldxmin = atof(xmin->GetText());
            double oldymin = atof(ymin->GetText());
            double oldxmax = atof(xmax->GetText());
            double oldymax = atof(ymax->GetText());




            int newxmin = oldxmin * varyData[0] + oldymin * varyData[1] + varyData[2];
            int newymin = oldxmin * varyData[3] + oldymin * varyData[4] + varyData[5];
            int newxmax = (oldxmax) * varyData[0] + (oldymax) * varyData[1] + varyData[2];
            int newymax = (oldxmax) * varyData[3] + (oldymax) * varyData[4] + varyData[5];



            xmin->SetText(newxmin);
            ymin->SetText(newymin);
            xmax->SetText(newxmax);
            ymax->SetText(newymax);

            locationNode = locationNode->NextSiblingElement("object");
        }

        doc.SaveFile(filePath.c_str());
        cout<<filePath<<"           saved "<<endl;
    }

    imgBarn.clear();
    xmlBarn.clear();
}


void imbang::pointThePicture(const string &xmlName,const string &imgName) {
    fileUnderDir(xmlName,2);
    fileUnderDir(imgName,1);

    std::sort(xmlBarn.begin(),xmlBarn.end());
    std::sort(imgBarn.begin(),imgBarn.end());


    int i = 0;
    for(auto &el:xmlBarn){
        XMLDocument doc;
        string filePath = xmlName + "/" +el;
        string imgPath = imgName + "/" + imgBarn[i++];

        Mat Aimg  = imread(imgPath);

        Point center(Aimg.cols/2.0, Aimg.rows/2.0);



        // read a xml
        doc.LoadFile(filePath.c_str());

        //initialize root node
        XMLElement *RootElement = doc.RootElement();

        XMLElement *locationNode = RootElement->FirstChildElement("object");
        while(locationNode){
            XMLElement *bndBox = locationNode->FirstChildElement("bndbox");

            XMLElement *xmin = bndBox->FirstChildElement("xmin");
            XMLElement *ymin = bndBox->FirstChildElement("ymin");
            XMLElement *xmax = bndBox->FirstChildElement("xmax");
            XMLElement *ymax = bndBox->FirstChildElement("ymax");



            int oldxmin = atoi(xmin->GetText());
            int oldymin = atoi(ymin->GetText());
            int oldxmax = atoi(xmax->GetText());
            int oldymax = atoi(ymax->GetText());




            Point dsta, dstb;
            int x1 = oldxmin - center.x;
            int y1 = oldymin - center.y;

            double angle=60*CV_PI/180;

            dsta.x = cvRound(x1 * cos(angle) + y1 * sin(angle) + center.x);
            dsta.y = cvRound(-x1 * sin(angle) + y1 * cos(angle) + center.y);

            int x2 = oldxmax - center.x;
            int y2 = oldymax - center.y;

            dstb.x = cvRound(x2 * cos(angle) + y2 * sin(angle) + center.x);
            dstb.y = cvRound(-x2 * sin(angle) + y2 * cos(angle) + center.y);




            rectangle(Aimg,dsta,dstb,Scalar(0,0,255),3,8,0);
            imshow("a",Aimg);

            waitKey(0);

            locationNode = locationNode->NextSiblingElement("object");
        }

        string imgPath1 = imgName + "/s" + imgBarn[i];
        imwrite(imgPath1,Aimg);
        imshow("a",Aimg);

        waitKey(0);
        cout<<imgPath1<<"         saved"<<endl;

    }

    imgBarn.clear();
    xmlBarn.clear();
}





