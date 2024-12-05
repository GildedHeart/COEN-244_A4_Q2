#include"BaseTensor.h"
#include"RankOneTensorType.h"
#include"IoTDataTensor.h"
#include<iostream>
#include<string>
#include<sstream>

void testTensorType();
void testIoTDataTensor();
void testIoTDataTensorV2(); // Had to rework test driver to get the output requested in the assignment guidelines. 

int main() {
	testTensorType();
	testIoTDataTensor();
	testIoTDataTensorV2();

	return 0;
}

void testTensorType() {
	RankOneTensorType<std::string> tensor(2);
	tensor[0] = "Hello";
	tensor[1] = "Coen244";
	std::cout << tensor;

	RankOneTensorType<double> dtensor(2);
	dtensor[0] = 0.15;
	dtensor[1] = 0.30;
	std::cout << dtensor;

	RankOneTensorType<double> dtensor2(2);
	dtensor2.loadData();
	std::cout << dtensor2;
	std::cout << dtensor + dtensor2;
	std::cout << dtensor[0] << "\n\n";
}

void testIoTDataTensor() { 
	IoTDataTensor iot; 
	try { 
		iot.loadData(); 
		
		int row = 0; 
		int col = 5; 

		std::cout << "\n" << iot.getCategory(col) << " : " << iot.getValue(row, col) << "\n\n";
	} 
	catch (std::runtime_error& e) { std::cerr << e.what() << std::endl; } 
}

void testIoTDataTensorV2() { 
	IoTDataTensor iot; 
	try {
		iot.loadData();

		std::cout << "\nData of all the shards in chosen file:\n";

		for (int i = 0; i < 85; i++) {
			std::cout << iot.getCategory(i) << "\n";
		}

		std::cout << "\n";

		for (size_t row = 0; row < iot.getDataRowCount(); row++) {
			std::stringstream dataValues;
			dataValues << "Data : " << "[";
			for (size_t col = 0; col < iot.getAttributeCount(); col++) {
				if (col != iot.getAttributeCount() - 1) {
					dataValues << iot.getValue(row, col) << ",";
				}
				else {
					dataValues << iot.getValue(row, col) << "]\n\n";
				}
			}
			std::cout << dataValues.str();
		}
	}
	catch (std::runtime_error& e) { std::cerr << e.what() << std::endl; }

	std::cout << "\nThere are no more shards in the file.\n\n";
}