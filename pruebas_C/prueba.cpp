#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <iostream>

#define N 20

using namespace std;

void insert(int *a){

	list<int> order;
	list<int>::iterator it;
	order.push_back(a[0]);

	for(int i = 1; i < N; i++){

		int num = a[i];
		bool t = true;
		it = order.begin();

		while(it!=order.end() && t != false){
			if(*it > num){ 
				order.insert(it,num);
				t = false;
			}
			++it;
		}
		if(t){
			order.push_back(num);
		}

	}

	it = order.begin();
	int cont  = 0;
	while(it != order.end()){
		a[cont] = *it;
		cont++;
		++it;
	}
}

void imp(int *a){
	for(int i = 0; i < N; i++){
		cout << a[i] <<endl;
	}
	cout<<endl<<endl;
}

int main(){

	int *a;
	a = (int*)malloc(N*sizeof(int));

	for(int i = 0; i < N; i++){
		a[i] = rand() % 1000;
	}

	imp(a);
	insert(a);
	imp(a);

    return 0;
}
