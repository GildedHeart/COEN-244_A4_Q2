#include"BaseTensor.h"
#include"RankOneTensorType.h"
#include"IoTDataTensor.h"
#include<iostream>
#include<string>

void testTensorType();
void testIoTDataTensor();

int main() {
	testTensorType();
	testIoTDataTensor();
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
	std::cout << dtensor[0] << "\n";
}

void testIoTDataTensor() { 
	IoTDataTensor iot; 
	try {
		iot.loadData();
		for (int i = 0; i < 85; i++) {
			for(int j = 0; j < 5; j++)
			std::cout << iot.getCategory(i) << " : [" << iot.getValue(j, i) << "] \n\n";
		}
	}
	catch (std::runtime_error& e) { std::cerr << e.what() << std::endl; }
}