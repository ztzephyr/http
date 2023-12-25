
#include<iostream>
#include<random>
#include<vector>

//using namespace std;

std::vector<uint8_t> GenRandomBytes()
{
	//random_device rd;
	//mt19937 e(rd);
	static std::default_random_engine e(time(0));
	static std::uniform_int_distribution<int> u(0, 255);

	std::vector<uint8_t> res;
	for (int i = 0; i < 32; i++)
	{
		res.push_back(u(e));
		std::cout << (int)res[i] << ", ";
	}
	std::cout << std::endl;
	return res;
}

int main()
{
	std::cout << "hello, world" << std::endl;

	GenRandomBytes();
	
	return 0;
}