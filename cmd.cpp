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
		bool found = false;
		for (int i = 0; i < this->system.size(); i++) {
			if (currentfolder == this->system[i].folder && s == this->system[i].subfolder) {
				found = true;
			}
		}
		if (found) {
			cout << "This directory already exist" << endl;
		}
		if (s != "..") {
			Pair p;
			p.folder = currentfolder;
			p.subfolder = s;
			this->system.push_back(p);
		}
		else {
			cout << "Invalid foldername" << endl;
		}
	}

	void ls(string c) {
		for (int i = 0; i < this->system.size(); i++) {
			if (c == this->system[i].folder) {
				cout << this->system[i].subfolder << endl;
			}
		}
	}
	string cd(string chosen, string current) {
		int found = 0;
		for (int i = 0; i < this->system.size(); i++) {
			if (current == this->system[i].folder && chosen == this->system[i].subfolder) {
				current += "/" + chosen;
				found++;
			}
		}
		if (found == 0) {
			cout << "No such file in this directory" << endl;
		}
		return current;
	}

};

void main() {
	cout << "Welcome in the terminal. Press 'q' to exit." << endl;
	string CurrentFolder = "root";
	Dictionary d;
	string parancs;
	string currentFolderCd;

	while (parancs != "q") {
		string autotext = "C:/" + CurrentFolder + ">";
		cout << autotext;
		cin >> parancs;
		if (parancs != "mkdir" && parancs != "q" && parancs != "ls" && parancs != "cd" && parancs != "cd..") {
			cout << "'" << parancs << "' is not recognized as an internal or external command, operable program or batch file." << endl;
		}
		if (parancs == "mkdir") {
			string temp;
			string dirname;
			cin >> dirname;
			d.mkdir(dirname, CurrentFolder);
		}
		if (parancs == "cd") {
			string dirname;
			cin >> dirname;
			if (dirname == "..") {
				if (CurrentFolder != "root") {
					int cut = CurrentFolder.find_last_of("/");
					CurrentFolder = CurrentFolder.substr(0, cut);
					cout << "\n ----------- \n" << CurrentFolder << "\n ------------ \n"; //Kizárólag debugolásra készült sor.
				}
				else {
					cout << "You're already in the root directory." << endl;
				}
			}
			else {
				CurrentFolder = d.cd(dirname, CurrentFolder);
			}
		}

		if (parancs == "ls") {
			d.ls(CurrentFolder);
		}
	}
}