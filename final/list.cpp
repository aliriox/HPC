#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(){
	int n;
	cin >> n;

	cout << n << endl;

	for(int i = 0; i < n; i++){
		int aux = rand() % 1001;
		cout << aux << endl;
	}

	return 0;
}