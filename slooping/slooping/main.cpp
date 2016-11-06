#include <iostream>
#include <list>

#define end 0
#define start 1


using namespace std;

list < void (*)(int*) > proc;
list <int> argv;

void f0(int *argv){
	string s = "abc";
	for (; s[*argv];){
		cout << s[*argv] << endl;
		(*argv)++;
		return;
	}
	(*argv) = end;
	return;
}

void f1(int *argv){
	cout << "f1\n";
	*argv = 0;
	return;
}

void f2(int *argv){
	cout << "f2\n";
	*argv = 0;
	return;
}

void f3(int *argv){
	cout << "f3\n";
	*argv = 0;
	return;
}

void f4(int *argv){
	cout << "f4\n";
	*argv = 0;
	return;
}


void input(){
		proc.push_back(&f0);
		argv.push_back(0);
		proc.push_back(&f1);
		argv.push_back(start);
		proc.push_back(&f2);
		argv.push_back(start);
		proc.push_back(&f3);
		argv.push_back(start);
		proc.push_back(&f4);
		argv.push_back(start);
		proc.push_back(&f0);
		argv.push_back(0);
}

void fifo(){
	while (!proc.empty()){
		void (*temp_func)(int*);
		temp_func = proc.front();
		proc.pop_front();
		int temp_argv = argv.front();
		argv.pop_front();
		temp_func(&temp_argv);
		if (temp_argv){
			proc.push_back(temp_func);
			argv.push_back(temp_argv);
		}
	}
	return;
}

void filo(){
	while (!proc.empty()){
		wait(1e4);
		void (*temp_func)(int*);
		temp_func = proc.back();
		proc.pop_back();
		int temp_argv = argv.back();
		argv.pop_back();
		temp_func(&temp_argv);
		if (temp_argv){
			proc.push_back(temp_func);
			argv.push_back(temp_argv);
		}
	}
	return;
}

int main(){
	input();
	cout << "choose strategy:\n\t1: FIFO\n\t2: FILO\n";
	int strat;
	cin >> strat;
	if (strat == 1){
		fifo();
	}
	if (strat == 2){
		filo();
	}
	return 0;
}