#include <iostream>
#include <queue>

#define end 0
#define start 1


using namespace std;

queue < void (*)(int*) > proc;
queue <int> argv;

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

int main(){
	proc.push(&f0);
	argv.push(0);
	proc.push(&f1);
	argv.push(start);
	proc.push(&f2);
	argv.push(start);
	proc.push(&f3);
	argv.push(start);
	proc.push(&f4);
	argv.push(start);
	proc.push(&f0);
	argv.push(0);
	
	while (!proc.empty()){
		void (*temp_func)(int*);
		temp_func = proc.front();
		proc.pop();
		int temp_argv = argv.front();
		argv.pop();
		temp_func(&temp_argv);
		if (temp_argv){
			proc.push(temp_func);
			argv.push(temp_argv);
		}
	}
	return 0;
}