#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Pair {
	string folder;
	string subfolder;
};

class Dictionary {
	private:
		vector<Pair> system;
	public:
		void mkdir(string s, string currentfolder) {
			Pair p;
			p.folder = currentfolder;
			p.subfolder = s;
			this->system.push_back(p);
		}

};

void main() {
	cout << "Welcome in the terminal. Press 'q' to exit." << endl;
	string CurrentFolder = "root";
	Dictionary d;
	string parancs;
	while (parancs != "q") {
		cout << "C:/Users/Fruzsi>";
		cin >> parancs;
		if (parancs != "mkdir" && parancs != "q") {
			cout << "'" << parancs << "' is not recognized as an internal or external command, operable program or batch file." << endl;
		}
		if (parancs == "mkdir") {
			cout << "Directoryname:";
			string dirname;
			cin >> dirname;
			d.mkdir(dirname, CurrentFolder);
		}
	}	
}