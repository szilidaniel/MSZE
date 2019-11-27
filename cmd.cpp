#include "cmd.h"
using namespace std;
#include <iostream>
#include <fstream>

Pair::Pair() {
	this->folder = "";
	this->subfolder = "";
}
Pair::Pair(string folder, string subfolder) {
	this->folder = folder;
	this->subfolder = subfolder;
}

void Dictionary::mkdir(string dirName, string currentFolder) {
/**@brief Mappa l�trehoz�sa
*@param dirName egy mappanevet kell megadni a f�ggv�nynek, m�gpedig amilyen n�ven l�tre szeretn�nk hozni. 
*@param currentFolder �t kell adni az aktu�lis tart�zkod�si helyet a mapparendszeren bel�l �s ott ker�l l�trehoz�sra a mappa.
*/
	bool found = false;
	for (unsigned int i = 0; i < this->system.size(); i++) {
		if (currentFolder == this->system[i].folder && dirName == this->system[i].subfolder) {
			found = true;
		}
/**@brief Mappa ellen�rz�se
*@return Igaz �rt�ket ad vissza, ha a mappa l�tezik.
*/
	}
	for (unsigned int i = 0; i < this->fileDescriptorVector.size(); i++) {
		if (dirName == this->fileDescriptorVector[i].fileName && currentFolder == this->fileDescriptorVector[i].filePath) {
			found = true;
		}
	}
	if (found) {
		cout << "This file/directory already exists" << endl;
	}
	else
	{
		if (!(this->isNotValid(dirName))) {
			this->addPairToVector(currentFolder, dirName);
		}
		else {
			cout << "Invalid foldername" << endl;
		}
	}
}

void Dictionary::ls(string currentFolder) {
	for (unsigned int i = 0; i < this->system.size(); i++) {
		if (currentFolder == this->system[i].folder) {
			cout << this->system[i].subfolder << endl;
		}
	}
	for (unsigned int i = 0; i < this->fileDescriptorVector.size(); i++) {
		if (currentFolder == this->fileDescriptorVector[i].filePath) {
			cout << this->fileDescriptorVector[i].fileName << endl;
		}
	}
}
string Dictionary::cd(string dirName, string currentFolder) {
	bool found = false;
	for (unsigned int i = 0; i < this->system.size(); i++) {
		if ((currentFolder == this->system[i].folder) && (dirName == this->system[i].subfolder)) {
			currentFolder += "/" + dirName;
			found = true;
			break;
		}
	}
	if (found == false) {
		cout << "No such file in this directory." << endl;
	}
	return currentFolder;
}

void Dictionary::rm(string toDelete, string currentFolder) {
	bool found = false;

	for (unsigned int i = 0; i < this->fileDescriptorVector.size(); i++) {
		if (toDelete == this->fileDescriptorVector[i].fileName && currentFolder == this->fileDescriptorVector[i].filePath) {
			found = true;
			this->fileDescriptorVector.erase(this->fileDescriptorVector.begin() + i);
			cout << "File has been deleted!" << endl;
		}
	}

	if (!found) {
		bool hasContent = false;
		string toDeleteAsFolder = currentFolder + "/" + toDelete;

		// vagy ha van file a mappaban
		for (unsigned int i = 0; i < this->fileDescriptorVector.size(); i++) {
			if (toDeleteAsFolder == this->fileDescriptorVector[i].filePath) {
				hasContent = true;
			}
		}
		// vagy ha van almappaja
		for (unsigned int i = 0; i < this->system.size(); i++) {
			if (toDeleteAsFolder == this->system[i].folder) {
				hasContent = true;
			}
		}

		if (hasContent) {
			cout << "Cannot delete folder, it has content in it!" << endl;
		}
		else {
			// mappakent probaljuk megtalalni es torolni
			for (unsigned int i = 0; i < this->system.size(); i++) {
				if (currentFolder == this->system[i].folder && toDelete == this->system[i].subfolder) {
					found = true;
					this->system.erase(this->system.begin() + i);
				}
			}
			if (!found) {
				cout << "No such file/directory in this directory" << endl;
			}
		}
	}
}

void Dictionary::deleteRecursively(string toDelete, string currentFolder) {
	cout << "Directory is not empty, deleting content recursively ..." << endl;

	string toDeleteAsFolder = currentFolder + "/" + toDelete;

	// Fileokat
	vector<FileDescriptor> fileDescriptorVectorNew;
	for (unsigned int i = this->fileDescriptorVector.size(); i > 0; i--) {
		if (this->fileDescriptorVector[i - 1].filePath.find(toDeleteAsFolder) != std::string::npos) {
			cout << "Deleted:" << this->fileDescriptorVector[i - 1].fileName << endl;
		}
		else {
			FileDescriptor currentFileData;
			currentFileData.fileName = this->fileDescriptorVector[i - 1].fileName;
			currentFileData.filePath = this->fileDescriptorVector[i - 1].filePath;
			fileDescriptorVectorNew.push_back(currentFileData);
		}
	}
	this->fileDescriptorVector = fileDescriptorVectorNew;

	// Almappakat
	vector<Pair> subFolderVectorNew;
	for (unsigned int i = this->system.size(); i > 0; i--) {
		if (this->system[i - 1].folder.find(toDeleteAsFolder) != std::string::npos) {
			cout << "Deleted:" << this->system[i - 1].subfolder << endl;
		}
		else {
			Pair folderNew;
			folderNew.folder = this->system[i - 1].folder;
			folderNew.subfolder = this->system[i - 1].subfolder;
			subFolderVectorNew.push_back(folderNew);
		}
	}
	this->system = subFolderVectorNew;

	// Vegul a torlendo mappat
	for (unsigned int i = 0; i < this->system.size(); i++) {
		if (currentFolder == this->system[i].folder && toDelete == this->system[i].subfolder) {
			cout << "Deleted:" << this->system[i].subfolder << endl;
			this->system.erase(this->system.begin() + i);
		}
	}
}

void Dictionary::rmForce(string toDelete, string currentFolder) {
	bool found = false;

	for (unsigned int i = 0; i < this->fileDescriptorVector.size(); i++) {
		if (toDelete == this->fileDescriptorVector[i].fileName && currentFolder == this->fileDescriptorVector[i].filePath) {
			found = true;
			this->fileDescriptorVector.erase(this->fileDescriptorVector.begin() + i);
			cout << "File has been deleted!" << endl;
		}
	}

	if (!found) {
		bool hasContent = false;
		string toDeleteAsFolder = currentFolder + "/" + toDelete;

		// vagy ha van file a mappaban
		for (unsigned int i = 0; i < this->fileDescriptorVector.size(); i++) {
			if (toDeleteAsFolder == this->fileDescriptorVector[i].filePath) {
				hasContent = true;
			}
		}
		// vagy ha van almappaja
		for (unsigned int i = 0; i < this->system.size(); i++) {
			if (toDeleteAsFolder == this->system[i].folder) {
				hasContent = true;
			}
		}

		if (hasContent) {
			deleteRecursively(toDelete, currentFolder);
		}
		else {
			// mappakent probaljuk megtalalni es torolni
			for (unsigned int i = 0; i < this->system.size(); i++) {
				if (currentFolder == this->system[i].folder && toDelete == this->system[i].subfolder) {
					found = true;
					this->system.erase(this->system.begin() + i);
				}
			}
			if (!found) {
				cout << "No such file/directory in this directory" << endl;
			}
		}
	}
}
void Dictionary::touch(string fileName, string currentFolder) {
	bool found = false;
	for (unsigned int i = 0; i < this->fileDescriptorVector.size(); i++) {
		if (fileName == this->fileDescriptorVector[i].fileName && currentFolder == this->fileDescriptorVector[i].filePath) {
			found = true;
		}
	}
	for (unsigned int i = 0; i < this->system.size(); i++) {
		if (fileName == this->system[i].subfolder && currentFolder == this->system[i].folder) {
			found = true;
		}
	}
	if (found) {
		cout << "This file/directory already exists" << endl;
	}
	else
	{
		if (fileName != "..") {
			FileDescriptor currentFileData;
			currentFileData.fileName = fileName;
			currentFileData.filePath = currentFolder;
			this->fileDescriptorVector.push_back(currentFileData);
		}
		else {
			cout << "Invalid filename" << endl;
		}
	}
}
void Dictionary::echo(string fileContent, string fileName, string currentFolder) {
	bool foundDirectory = false;
	for (unsigned int i = 0; i < this->system.size(); i++) {
		if (fileName == this->system[i].subfolder) {
			foundDirectory = true;
		}
	}
	if (foundDirectory) {
		cout << "This directory already exists" << endl;
	}
	else {
		bool foundFile = false;

		for (unsigned int i = 0; i < this->fileDescriptorVector.size(); i++) {
			if (fileName == this->fileDescriptorVector[i].fileName) {
				this->fileDescriptorVector[i].fileContent = fileContent;
				foundFile = true;
			}
		}
		if (!foundFile) {
			if (fileName != ".." && fileName != ".") {
				FileDescriptor currentFileData;
				if (fileContent == "\"\"") {
					currentFileData.fileContent = "";
				}
				else {
					currentFileData.fileContent = fileContent;
				}
				currentFileData.fileName = fileName;
				currentFileData.filePath = currentFolder;
				this->fileDescriptorVector.push_back(currentFileData);
			}
			else {
				cout << "Invalid filename" << endl;
			}
		}

	}
}

void Dictionary::writeToFile(string fsname) {
	ofstream systemStructure;
	systemStructure.open(fsname + ".txt");
	for (unsigned int i = 0; i < this->system.size(); i++) {
		systemStructure << this->system[i].folder << "/" << this->system[i].subfolder << "\n";
	}
	systemStructure.close();
}

void Dictionary::loadFromFile(string fsname) {
	string line;
	ifstream systemStructure(fsname + ".txt");
	if (systemStructure.is_open())
	{
		while (getline(systemStructure, line))
		{
			this->splitFolderPath(line);
		}
		systemStructure.close();
	}
}

void Dictionary::splitString(string& str, vector<string>& out, string delim) {
	size_t start;
	size_t end = 0;
	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}

void Dictionary::addPairToVector(string folder, string subfolder) {
	this->system.push_back(Pair(folder, subfolder));
}

void Dictionary::splitFolderPath(string line) {
	string path = line;
	int cut = line.find_last_of("/");
	line = line.substr(cut + 1, line.size());
	path = path.substr(0, cut);
	Pair p(path, line);
	this->system.push_back(p);
}

bool Dictionary::isNotValid(string dirName) {
	if (isalpha(dirName[0]))
		return false;
	else
		return true;
}


bool Dictionary::validcommand(string command) {
	bool valid = false;
	for (unsigned int i = 0; i < this->commands.size(); i++) {
		if (command == this->commands[i]) {
			valid = true;
		}
	}
	return valid;

}
