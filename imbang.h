//
// Created by lunaticf on 17-4-18.
//

#ifndef IMBANG_IMBANG_H
#define IMBANG_IMBANG_H

#include <vector>
#include <string>


#include "tinyxml2.h"

using namespace std;

class imbang {

public:
      void fileUnderDir(const string &dirName, int mode);

      void enhancePicByLapa(const string &dirName,const string dstDirName, bool processAll = true);

      void batchAlterXMLNode(const string &dirName, const string &imageDir);

      void batchAlterXMLName(const string &dirName, const string &prefix);

      void batchBlur(const string &dirName,const string &dstDirName,const string &prefix);

      void batchGaussianBlur(const string &dirName,const string &dstDirName,const string &prefix);

      void batchMedianBlur(const string &dirName,const string &dstDirName,const string &prefix);

      void batchBilateralBlur(const string &dirName,const string &dstDirName,const string &prefix);


      void enhancePicByLog(const string &dirName,const string dstDirName,const string &prefix);

      void batchSobel(const string &dirName,const string dstDirName,const string &prefix);

      void batchNoise(const string &dirName,const string dstDirName,const string &prefix,int noiseNum);

      void batchRotate(const string &dirName,const string dstDirName,const string &prefix, int degree);

      void alterXMLofRotate(const string &dirName, vector<double> &vec);



    void pointThePicture(const string &xmlName,const string &imgName);




        private:
      vector<string> imgBarn;
      vector<string> xmlBarn;




};


#endif //IMBANG_IMBANG_H
