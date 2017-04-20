//#include <iostream>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include "imbang.h"
//
//using namespace cv;
//
//int main() {
//    imbang bang;
////
////    string src = "/home/lunaticf/Desktop/tanke_all";
////    string dst = "/home/lunaticf/Desktop/newTankeDataset/rotate300";
////
////
////    bang.batchRotate(src,dst,"85",300);
////
////    string obj2 = "/home/lunaticf/Desktop/newTankeDataset/rotate60xml";
////    string src2 = "/home/lunaticf/Desktop/newTankeDataset/rotate60";
////    bang.batchAlterXMLNode(obj2,src2);
////
////    string prefix = "81";
////    bang.batchAlterXMLName(obj2, prefix);
//
//    string obj2 = "/home/lunaticf/Desktop/newTankeDataset/rotate60xml";
//
//    string obj3 = "/home/lunaticf/Desktop/newTankeDataset/rotate60";
//    vector<double> vec = {0.5, 0.866025 ,-0.912743 ,-0.866025,0.5,748.123};
//    //bang.alterXMLofRotate(obj2,vec);
////
////    imread("/home/lunaticf/Desktop/newTankeDataset/rotate60/812001.jpg");
//
//    bang.pointThePicture(obj2,obj3);


//
//
//
//    return 0;
//}

//
// Created by chen on 17-4-20.
//

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <cstdlib>
#include <stdio.h>
#include <cstring>
#include <vector>

using namespace std;

int main()
{
    string path="/home/lunaticf/Desktop/newTankeDataset";
    vector<string> files;//存放文件名
    DIR *dir;
    struct dirent *ptr;
    char base[1000];
    string temp;

    const char *b =path.c_str();

    if ((dir=opendir(b)) == NULL)
    {
        perror("Open dir error...");
        exit(1);
    }

    while ((ptr=readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
            continue;
        else if(ptr->d_type == 8)    ///file
        {
            //printf("d_name:%s/%s\n",basePath,ptr->d_name);
            temp=ptr->d_name;
            files.push_back(temp);
        }
        else if(ptr->d_type == 10)    ///link file
            //printf("d_name:%s/%s\n",basePath,ptr->d_name);
            continue;
        else if(ptr->d_type == 4)    ///dir
        {
            temp=ptr->d_name;
            files.push_back(temp);
            /*
                memset(base,'\0',sizeof(base));
                strcpy(base,basePath);
                strcat(base,"/");
                strcat(base,ptr->d_nSame);
                readFileList(base);
            */
        }
    }
    closedir(dir);
    string cmd="";
    for(int i=0; i<files.size(); i++)
    {
        //cout<<files[i]<<endl;
        cmd+="mv /home/lunaticf/Desktop/newTankeDataset/";
        cmd+=files[i];
        cmd+="/* ";
        cmd+="/home/lunaticf/Desktop/newccl";

        system(cmd.c_str());
        cmd="";
    }

    system("mv /home/lunaticf/Desktop/newTankeDataset/rotate180/* /home/lunaticf/Desktop/newccl");




    return 0;
}