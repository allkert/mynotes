# include<iostream>
# include<limits>
# include<sstream>
# include<vector>


using namespace std;

int func1(int* array, int size){
    int sum = 0;
    for(int i = 0; i < size; i++){
        sum += array[i];
    }
    return sum;
}

int func2(int array[], int size){
    int sum = 0;
    for(int i = 0; i < size; i++){
        sum += array[i];
    }
    return sum;
}

int func(int &par){
    par = 1000;
    return par;
}

std::vector<int> splitAndConvert(const std::string& str) {
    std::istringstream iss(str);
    std::vector<int> nums;
    int num;
    while (iss >> num) {
        nums.push_back(num);
    }
    return nums;
}

int main(){
    string s = "1 2 3 4 55 6";
    vector<int> nums = splitAndConvert(s);
    for(int num:nums){
        cout<<num<<'\t';
    }
}