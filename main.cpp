#include "cmd.h"

bool validcommand(string command) {
	bool valid = false;
	vector<string> commands = { "mkdir","q","ls","cd","rm","touch", "echo" };
	for (unsigned int i = 0; i < commands.size(); i++) {
		if (command == commands[i]) {
			valid = true;
		}
	}
	return valid;
}

vector<string> split(string path) {
	vector<string> directories;
	int cut = 0;
	while (cut != string::npos) {
		cut = path.find_first_of("/");
		string element = path.substr(0, cut);
		directories.push_back(element);
		path = path.substr(cut + 1, path.size());
	}

	return directories;
}

int main() {
	cout << "Welcome in the terminal. Press 'q' to exit." << endl;
	string CurrentFolder = "root";
	Dictionary d;
	string parancs;

	while (parancs != "q") {
		string autotext = "C:/" + CurrentFolder + ">";
		cout << autotext;
		cin >> parancs;
		if (!validcommand(parancs)) {
			cout << "'" << parancs << "' is not recognized as an internal or external command, operable program or batch file." << endl;
		}
		else {
			if (parancs == "ls") {
				d.ls(CurrentFolder);
			}
			else {
				string dirname;
				cin >> dirname;
				vector<string> path;
				if (dirname.find_first_of("/") != string::npos) {
					path = split(dirname);
					path.pop_back();
					dirname = dirname.substr(dirname.find_last_of("/") + 1, dirname.size());
					for (unsigned int i = 0; i < path.size(); i++) {
						if (path[i] == "..") {
							if (CurrentFolder != "root") {
								int cut = CurrentFolder.find_last_of("/");
								CurrentFolder = CurrentFolder.substr(0, cut);
							}
							else {
								cout << "You're already in the root directory." << endl;
							}
						}
						else {
							CurrentFolder = d.cd(path[i], CurrentFolder);
						}
					}
				}
				if (parancs == "mkdir") {
					d.mkdir(dirname, CurrentFolder);
				}
				if (parancs == "cd") {
					if (dirname == "..") {
						if (CurrentFolder != "root") {
							int cut = CurrentFolder.find_last_of("/");
							CurrentFolder = CurrentFolder.substr(0, cut);
						}
						else {
							cout << "You're already in the root directory." << endl;
						}
					}
					else {
						CurrentFolder = d.cd(dirname, CurrentFolder);
					}

				}
				if (parancs == "rm") {
					if (dirname == "-rf") {
						cin >> dirname;
						d.rmForce(dirname, CurrentFolder);
					}
					else d.rm(dirname, CurrentFolder);
				}
				if (parancs == "touch") {
					d.touch(dirname, CurrentFolder);
				}
				if (parancs == "echo") {
					string fileContent;
					fileContent = dirname;
					string redirectSign;
					cin >> redirectSign;
					string fileName;
					cin >> fileName;
					if (redirectSign != ">") {
						cout << "Invalid command!" << endl;
					}
					else {
						d.echo(fileContent, fileName, CurrentFolder);
					}
				}
			}
		}
	}
	return 0;
}