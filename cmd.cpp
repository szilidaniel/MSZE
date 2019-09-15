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
		Pair p;
		p.folder = currentfolder;
		p.subfolder = s;
		this->system.push_back(p);
		//megkeresni azt az elemet amit a cd visszaad és amögé beszúrni a köv foldert
	}
	void listAllFolders(string chosenFolder) {
		bool found = false;
		unordered_set<string> allFolders;
		for (auto iterate : this->system) {
			if (iterate.folder == chosenFolder || iterate.subfolder == chosenFolder) {
					found = true;
					allFolders.insert(iterate.folder);
			}
		}
		if (found) {
			for (auto itr = allFolders.begin(); itr != allFolders.end(); ++itr)
				cout << *itr << '/';
		}
	}

	void changeDirectory(string chosenFolder) {
		bool found = false;
		string whichFolder;
		unordered_set<string> allFolders;
		for (auto iterate : this->system) {
			allFolders.insert(iterate.folder);
			if (iterate.folder == chosenFolder || iterate.subfolder == chosenFolder) {
				found = true;
				whichFolder = chosenFolder;
				break;
			}
		}
		if (found) {
			cout << "C:/Users/Fruzsi/";
			for (auto itr = allFolders.begin(); itr != allFolders.end(); ++itr)
				cout << *itr << '/';
			cout << chosenFolder << endl;
		}

		else cout << "invalid folder name" << endl;

	}

	string changeToUpperFolder(string chosenFolder) {
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
			cout << "C:/Users/Fruzsi/";
			for (auto iterate : this->system) {
				if (iter2 <= iter) {
					cout << iterate.folder << "/";
				}
				iter2++;

			}cout << endl;
		}
		else cout << "invalid folder name" << endl;
		return chosenFolder;
	}
};

void main() {
	cout << "Welcome in the terminal. Press 'q' to exit." << endl;
	string CurrentFolder = "root";
	Dictionary d;
	string parancs;
	string currentFolderCd;
	while (parancs != "q") {
		cout << "C:/Users/Fruzsi>";
		cin >> parancs;
		if (parancs != "mkdir" && parancs != "q" && parancs != "ls" && parancs != "cd" && parancs != "cd..") {
			cout << "'" << parancs << "' is not recognized as an internal or external command, operable program or batch file." << endl;
		}
		if (parancs == "mkdir") {
			string temp;
			cout << "Directoryname:";
			string dirname;
			cin >> dirname;
			d.mkdir(dirname, CurrentFolder);
			temp = CurrentFolder;
			CurrentFolder = dirname;
			dirname = temp;
		}
		if (parancs == "ls") {
			cout << CurrentFolder;
			d.listAllFolders(CurrentFolder);
		}
		if (parancs == "cd") {
			string dirname;
			cin >> dirname;
			CurrentFolder = dirname;
			currentFolderCd = dirname;
			d.changeDirectory(dirname);
		}
		if (parancs == "cd..") {
			d.changeToUpperFolder(CurrentFolder);
		}
	}
}