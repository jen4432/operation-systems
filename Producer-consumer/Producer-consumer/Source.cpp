#include <iostream>
#include <vector>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <cmath>

using namespace std;

condition_variable cv;
mutex cv_mutex;
bool flag = false;


void find_next_prime(int n,int& result) {
	
	bool prime = true;
	while (!flag) {
		for (int i = 2; i <= sqrt(n); i++) {
			if (n % i == 0) {
				prime = false;
				break;
			}
		}
		if (prime) {
			result = n;
			flag = true;
			break;
		}
		prime = true;
		n++;
	}

	cv.notify_one();
}

void Print(int& result) {
	unique_lock<mutex> lock(cv_mutex);
	while (!flag) {
		cv.wait(lock);
	}
	cout << result;
}



int main() {
	int n;
	cout << "Enter number";
	cin >> n;

	int result = 0;
	
	thread t1(Print, ref(result)),t2(find_next_prime,n,ref(result));

	t1.join();
	t2.join();

}

