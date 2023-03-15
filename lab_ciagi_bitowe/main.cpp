#include<iostream>

using namespace std;

void printReversedString(int counter, string palindrome) {
	string reversedPalindrome = "";
	for (int i = counter; i >= 0; i--) {
		reversedPalindrome += palindrome[i];
	}
	cout << reversedPalindrome;
}


void solution(string palindrome, int counter, int n) {
	if (counter == n/2) {
		if (n % 2 == 1) {
			cout << palindrome;
			cout << "1";
			printReversedString(counter, palindrome);
			cout << palindrome;
			cout << "0";
			printReversedString(counter, palindrome);
		}
		else {
			cout << palindrome;
			printReversedString(counter, palindrome);
		}
		return;
	}
	solution(palindrome + "1", counter + 1, n);
	solution(palindrome + "0", counter + 1, n);
}


int main() {	
	int n;
	while (cin >> n) {
		solution("", 0, n);
		cout << endl;
	}	
	return 0;
}