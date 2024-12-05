#pragma once
#include "RankOneTensorType.h"
#include<fstream>
#include<sstream>
class IoTDataTensor :
    public RankOneTensorType<std::string>
{
private:
    std::vector<std::string> iot_category;
    std::vector<RankOneTensorType<std::string>> iot_data;

public:
    IoTDataTensor();
    ~IoTDataTensor() override {}

    double getValue(const int,const int) const;

    std::string getCategory(const int) const;

   void loadData() override;

};

