#include "cmd.h"
#include <map>

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

enum commands {
	mkdir, exitsys, ls, cd, rm, touch, echo,
};
map<string, commands> userCommands;

void checkCommands() {
	userCommands["mkdir"] = mkdir;
	userCommands["exit"] = exitsys;
	userCommands["ls"] = ls;
	userCommands["cd"] = cd;
	userCommands["rm"] = rm;
	userCommands["touch"] = touch;
	userCommands["echo"] = echo;
}

int main() {
	cout << "Welcome in the terminal. Write exit' to exit." << endl;
	cout << "Please add a valid file name to load filesystem from. " << endl;
	string CurrentFolder = "root";
	Dictionary d;
	string parancs;
	string dirname;
	string fsname;
	cin >> fsname;
	checkCommands();
	/** A main fuggvenyrol
	*
	*Ez a fuggveny reteges szerkezete egy else ranezesre if-ek tomegenek nez ki, de valojaban ezzel sok hely meg lett sporolva.
	*Vannak olyan resze a parancsoknak amik bar kozosek megsem erdemes egy fuggvenybe kiszedni, de egy if-fel el tudjuk kuloniteni, hogy ne kelljen tul sokszor be�rni.
	*Minden parancsot külön kezelünk es előtte megnezzuk szerepel-e az erveyes parancsok kozott.
	*Minden fuggveny a maga hibauzenetevel rendelkezik.
	*/
	while (d.validcommand(fsname)) {
		cout << "You entered a command. Please add a valid file name to load filesystem from. " << endl;
		cin >> fsname;
		if (fsname == "exit") break;
	}
	d.loadFromFile(fsname);
	while (parancs != "exit") {
		string autotext = "C:/" + CurrentFolder + ">";
		cout << autotext;
		cin >> parancs;
		if (parancs == "exit") break;
		else if (!d.validcommand(parancs)) {
			cout << "'" << parancs << "' is not recognized as an internal or external command, operable program or batch file." << endl;
		}
		else {
			if (parancs == "ls") {
				d.ls(CurrentFolder);
			}
			else if (parancs == "mv") {
				string source;
				cin >> source;
				string dest;
				cin >> dest;
				d.mv(CurrentFolder, source, dest);
			}
			else {
				cin >> dirname;
				vector<string> path;
				if (dirname.find_first_of("/") != string::npos) {
					path = split(dirname);
					d.splitDirNameAndPath(dirname, CurrentFolder, path);
				}
				switch (userCommands[parancs]) {
					case mkdir:
						d.mkdir(dirname, CurrentFolder);
						break;
					case cd:
						if (dirname == "..") {
							if (CurrentFolder != "root") {
								CurrentFolder=d.splitCurrentFolder(CurrentFolder);
							}
							else {
								cout << "You're already in the root directory." << endl;
							}
						}
						else {
							CurrentFolder = d.cd(dirname, CurrentFolder);
						}
						break;
					case rm:
						if (dirname == "-rf") {
							cin >> dirname;
							d.rmForce(dirname, CurrentFolder);
						}
						else d.rm(dirname, CurrentFolder);
						break;
					case touch:
						d.touch(dirname, CurrentFolder);
						break;
					case echo:
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
						break;
					}
			}
		}
	}
	d.writeToFile(fsname);
	return 0;
}
