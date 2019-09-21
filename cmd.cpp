#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
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
	void listAllFolders(string chosenFolder) {
		bool found = false;
		int iterateUntilFound = 0;
		unordered_set<string> allFolders;
		for (auto iterate : this->system) {
			iterateUntilFound++;
			//cout << ":::" << iterate.folder <<" : " << iterate.subfolder << " ::: ";
			if (iterate.folder == chosenFolder || iterate.subfolder == chosenFolder) {
				found = true;
				vector<Pair>::iterator iterateToFind = this->system.begin() + iterateUntilFound;

				for (iterateToFind; iterateToFind != this->system.end(); iterateToFind++) {
					//cout << ":::" << iterateToFind->folder << " : " << iterateToFind->subfolder << " ::: ";
					allFolders.insert(iterateToFind->folder);
					allFolders.insert(iterateToFind->subfolder);
				}
			}
		}
		if (found) {
			for (auto itr = allFolders.begin(); itr != allFolders.end(); ++itr)
				cout << *itr << '/' << endl;
		}
	}

	string changeDirectory(string chosenFolder, string currentfolder) {
		bool found = false;
		string whichFolder;
		unordered_set<string> allFolders;
		Pair allfolders;

		for (auto iterate : this->system) {
			allFolders.insert(iterate.folder);
			allFolders.insert(iterate.subfolder);
			if (iterate.folder == chosenFolder || iterate.subfolder == chosenFolder) {
				found = true;
				whichFolder = chosenFolder;
				break;
			}
		}
		if (found) {
			cout << "C:/root/";
			for (auto itr = allFolders.begin(); itr != allFolders.end(); ++itr)
				cout << *itr << '/';
			cout << endl;
		}

		else cout << "invalid folder name" << endl;
		return chosenFolder;

	}

	/*string changeToUpperFolder(string chosenFolder, string autotext) {
		int iter = 0;
		int iter2 = 0;
		bool found = false;
		string whichFolder;
		for (auto iterate : this->system) {
			iter++;
			if (iterate.folder == chosenFolder || iterate.subfolder == chosenFolder) {
				found = true;
				break;
			}
		}
		if (found) {
			autotext += "C:/Users/Fruzsi/";
			for (auto iterate : this->system) {
				if (iter2 <= iter) {
					autotext += iterate.folder + "/";
				}
				iter2++;

			}autotext += ">";
		}
		else cout << "invalid folder name" << endl;
		return autotext;
	}*/
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
					CurrentFolder = CurrentFolder.substr(0, cut - 1);
					cout << "\n ----------- \n" << CurrentFolder << "\n ------------ \n"; //Kizárólag debugolásra készült sor.
				}
				else {
					cout << "You're already in the root directory." << endl;
				}
			}
			else {
				CurrentFolder = d.changeDirectory(dirname, CurrentFolder);
			}
		}

		if (parancs == "ls") {
			d.ls(CurrentFolder);
		}
	}
}