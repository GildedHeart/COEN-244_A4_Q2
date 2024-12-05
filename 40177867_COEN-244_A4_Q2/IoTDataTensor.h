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
    const int attributeCount = 85;

public:
    IoTDataTensor();
    ~IoTDataTensor() override {}

    int getAttributeCount() const;

    std::string getValue(int, int) const;

    std::string getCategory(int) const;

    void loadData() override;

    size_t getDataRowCount() const;

};

