#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <cmath>

using namespace std;

mutex mut;

void find_prime_numbers(vector <int> &vec,int &count,int begin,int end) {
	for (int i = begin; i < end; i++) {
		bool flag = true;
		for(int j = 2;j <= sqrt(vec[i]);j++){
			if (vec[i] % j == 0) {
				flag = false;
			}
		}
		if (flag == true && vec[i] != 1) {
			mut.lock();
			cout << vec[i] << " ";
			count++;
			mut.unlock();
		}
	}
}


int main() {
	int n;
	cin >> n;
	vector <int> vec(n);

	for (int i = 0; i < n; i++) {
		cin >> vec[i];
	}

	cout << "Enter number of threads";

	int k;

	cin >> k;


	vector <thread> treads;

	int count = 0;

	int begin = 0;
	int end = n / k;

	for (int i = 0; i < k; i++) {
		treads.push_back(thread(find_prime_numbers, ref(vec),ref(count),begin,end));
		begin = end;
		end += n / k;
	}

	for (auto&& t : treads) {
		t.join();
	}

	cout << count;
}
