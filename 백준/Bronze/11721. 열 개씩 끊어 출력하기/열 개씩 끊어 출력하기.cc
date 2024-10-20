#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    getline(cin, s);
	int count=1;
    
    for(int i=0; i<s.size(); i++) {
        cout << s[i];
        if(count%10 == 0)
            cout << endl;
		count++;
    }
}