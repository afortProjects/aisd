#include <iostream>
#include <string>
#include <algorithm>

void reverseStr(std::string& str)
{
    int n = str.length();
 
    for (int i = 0; i < n / 2; i++)
        std::swap(str[i], str[n - i - 1]);
}

void solution(std::string text, int n, int counter) {
    if(counter == n/2) {
        if(n%2 == 0) {
            std::cout<<text;
            std::string text2 = text;
            reverseStr(text2);;
            std::cout<<text2;
            std::cout<<std::flush;
            return;
        } else {
            std::cout<<text;
            std::string text2 = text;
            reverseStr(text2);;

            std::cout<<"1";
            std::cout<<text2;
            std::cout<<text;
            std::cout<<"0";
            std::cout<<text2;

            std::cout<<std::flush;
            return;
        }
    }
    
    solution(text+"1", n, counter+1);
    solution(text+"0", n, counter+1);


}

int main() {
    int n;
    while(std::cin>>n) {
        solution("", n, 0);
        std::cout<<"\n"<<std::flush;

    }
    return 0;
}