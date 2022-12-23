#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <thread>
#include <algorithm>
#include <mutex>

using namespace std;

bool answer = false;

void print_vec(vector <int> vec) {
	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}
	cout << endl;
}

void make_sum(const vector <int>& vec,vector <int>& sums,int start) {
	for (int k = start; k < 1 << vec.size(); k += 2) {
		int sum = 0;
		for (int i = 0; i < vec.size(); i++) {
			if (k & (1 << i)) {
				sum += vec[i];

			}
		}
		sums.push_back(sum);
	}
}

mutex mut;

void find_zero_subset(vector <int>& first,vector <int>& second,int n,int position) {

	for (int i = position; i < first.size(); i+= n) {
		if (answer == true) {
			return;
		}
		bool flag = binary_search(second.begin(),second.end(), -first[i]);
		if (flag == true) {
			mut.lock();
			answer = true;
			mut.unlock();
		}
	}

}


int main() {
	
	int n;

	cout << "Enter size";
	cin >> n;
	
	cout << "Enter Numbers";
	vector <int> vec(n);
	vector <int> sums;

	for (int i = 0; i < n; i++) {
		cin >> vec[i];
	}

	vector <int> first_half_of_sums;
	vector <int> second_half_of_sums;

	int start = 1;

	thread thread_first(make_sum,ref(vec),ref(first_half_of_sums),start);
	thread thread_second(make_sum, ref(vec),ref(second_half_of_sums),++start);

	thread_first.join();
	thread_second.join();

	print_vec(first_half_of_sums);
	print_vec(second_half_of_sums);

	sort(first_half_of_sums.begin(), first_half_of_sums.end());
	sort(second_half_of_sums.begin(), second_half_of_sums.end());

	cout << "input count of threads";
	int count_of_threads;
	cin >> count_of_threads;

	vector <thread> threads;

	int position = 0;

	for (int i = 0; i < count_of_threads; i++) {
		threads.push_back(thread(find_zero_subset, ref(first_half_of_sums), ref(second_half_of_sums),count_of_threads,position));
		position++;
	}

	for (int i = 0; i < count_of_threads; i++) {
		threads[i].join();
	}

	if (answer == true) {
		cout << "Yes";
	}
	else {
		cout << "No";
	}
}
