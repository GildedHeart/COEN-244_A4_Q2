#include "IoTDataTensor.h"

IoTDataTensor::IoTDataTensor() {
    iot_category.resize(0);
    iot_data.resize(0);
}

double IoTDataTensor::getValue(const int row, const int col) const{
    return std::stod(iot_data[row][col]);
}

std::string IoTDataTensor::getCategory(const int col) const{
    return iot_category[col];
}


void IoTDataTensor::loadData() {
    int shardIndex = 0;
    const int attributeCount = 85;
    
    std::string inputFilePath;
    std::string line;

    std::cout << "Please enter the file path to the location of the shards: \n";
    getline(std::cin,inputFilePath);

    while (true) {
        std::string shardFilePath = (inputFilePath + "\\shard_" + std::to_string(shardIndex) + ".txt");

        std::ifstream inputFile(shardFilePath);

        if (!inputFile) {
            break;
        }

        if (iot_category.size() < 1) {
            for (int i = 0; i < attributeCount; i++) {
                getline(inputFile, line);
                iot_category.push_back(line);
            }
        }

        while (getline(inputFile, line)) {
            size_t startOfDataSet = line.find('[');
            size_t endOfDataSet = line.find(']');

            if (startOfDataSet != std::string::npos && endOfDataSet != std::string::npos) {
                std::string token;
                std::string dataLine = line.substr(startOfDataSet + 1, endOfDataSet - startOfDataSet - 1); 
                std::vector<std::string> dataVector;
                std::stringstream dataStream(dataLine);
                while(getline(dataStream, token, ',')){
                    dataVector.push_back(token);
                }

                RankOneTensorType<std::string> dataTensor;
                dataTensor.setData(dataVector);
                iot_data.push_back(dataTensor);
            }
        }
        inputFile.close();
        shardIndex++;
    }
}
