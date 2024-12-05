#include "IoTDataTensor.h"

IoTDataTensor::IoTDataTensor() {
    iot_category.resize(0);
    iot_data.resize(0);
}

int IoTDataTensor::getAttributeCount() const { return attributeCount; }

std::string IoTDataTensor::getValue(int row, int col) const{
    return iot_data[row][col];
}

std::string IoTDataTensor::getCategory(int col) const{
    return iot_category[col];
}


void IoTDataTensor::loadData() {
    int shardIndex = 0;
    
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
                std::stringstream dataStream(dataLine);
                std::vector<std::string> dataVector;
                RankOneTensorType<std::string> dataTensor;

                while(getline(dataStream, token, ',')){
                    dataVector.push_back(token);
                }

                dataTensor.setData(dataVector);
                iot_data.push_back(dataTensor);
            }
        }
        inputFile.close();
        shardIndex++;
    }
}

size_t IoTDataTensor::getDataRowCount() const {
    return iot_data.size();
}
