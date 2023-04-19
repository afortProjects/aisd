#include <iostream>
#include <vector>
#include <string>

int max(int x, int y) {
   return (x > y) ? x : y;
}

int knapsack(int capacity, std::vector<int> profits, std::vector<int> weights, int amountOfObjects) {
   int i, j;
   int** solutions = new int*[amountOfObjects+1];
   
   for(size_t i=0; i<amountOfObjects+1; i++) {
        solutions[i] = new int[capacity+1];
   }

   for (i = 0; i <= amountOfObjects; i++) {
      for (j = 0; j <= capacity; j++) {
         if (i == 0 || j == 0)
            solutions[i][j] = 0;
         else if (weights[i - 1] <= j)
            solutions[i][j] = max( profits[i-1] + solutions[i - 1][j - weights[i - 1]], solutions[i - 1][j]);
         else
            solutions[i][j] = solutions[i - 1][j];
      }
   }
   
   return solutions[amountOfObjects][capacity];
}

int main() {
   int amountOfObjects;
   std::string output = "";
   while(std::cin>>amountOfObjects) {
    int capacity;
    std::vector<int> weights;
    std::vector<int> profits;
    for(size_t i = 0;i<amountOfObjects;i++) {
        int tempProfit;
        std::cin>>tempProfit;
        profits.push_back(tempProfit);
    }
    for(size_t i = 0;i<amountOfObjects;i++) {
        int tempWeight;
        std::cin>>tempWeight;
        weights.push_back(tempWeight);
    }

    std::cin>>capacity;     
    output += std::to_string(knapsack(capacity, profits, weights, amountOfObjects)) + '\n';
   }
   std::cout<<output;
   return 0;
}