#include <iostream>

struct MotorState{
	int motorNumber;
	int angle;
};

MotorState _receive_state(){
	return {1, 2};
}

int main(){
	MotorState a = _receive_state();
	std::cout << a.motorNumber << " " << a.angle << std::endl;
	return 0;	
}
