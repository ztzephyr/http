#include <iostream>
#include<vector>
#include<unordered_set>
#include"sort_test.h"
using namespace std;



void printArray(const vector<int>& nums) {
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;
}

void test1() {
    vector<int> nums = {5,2,6,3,1,8,5,7,2,1,3,9,6,8};
//    printArray(nums);
//    shuffle(nums);
//    printArray(nums);
//    quickSort(nums);
//    printArray(nums);
    unordered_set<string> s;
    s.insert("");
    std::cout << s.size();

}


int main() {
    std::cout << "Hello, World!" << std::endl;

    test1();

    return 0;
}