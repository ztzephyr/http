#include <iostream>
#include<vector>
#include<unordered_set>

#include "alg/alg_sort.h"
#include "util.h"


using namespace std;











void test1() {
    vector<int> nums = {5,2,6,3,1,8,5,7,2,1,3,9,6,8};
    Merge912 ms;
    ms.mergeSort(nums);
    printVector(nums);


}

int main() {
    std::cout << "Hello, World!" << std::endl;

    test1();

    return 0;
}



















