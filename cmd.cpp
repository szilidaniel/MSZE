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
	/**@brief Mappa létrehozása
	*@param dirName egy mappanevet kell megadni a függvénynek, mégpedig amilyen néven létre szeretnénk hozni.
	*@param currentFolder át kell adni az aktuális tartózkodási helyet a mapparendszeren belül és ott kerül létrehozásra a mappa.
	*/
	bool found = false;
	for (unsigned int i = 0; i < this->system.size(); i++) {
		if (currentFolder == this->system[i].folder && dirName == this->system[i].subfolder) {
			found = true;
		}
		/**@brief Mappa ellenõrzése
		*@return Igaz értéket ad vissza, ha a mappa létezik.
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
		if (!(this->isValid(dirName))) {
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

bool Dictionary::isValid(string dirName) {
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


void Dictionary::splitDirNameAndPath(string dirname, string CurrentFolder, vector<string>path) {
		path.pop_back();
		dirname = dirname.substr(dirname.find_last_of("/") + 1, dirname.size());
		for (unsigned int i = 0; i < path.size(); i++) {
			if (path[i] == "..") {
				if (CurrentFolder != "root") {
					CurrentFolder=splitCurrentFolder(CurrentFolder);
				}
				else {
					cout << "You're already in the root directory." << endl;
				}
			}
			else {
				CurrentFolder = cd(path[i], CurrentFolder);
			}
		}
}


string Dictionary::splitCurrentFolder(string CurrentFolder) {
	int cut = CurrentFolder.find_last_of("/");
	CurrentFolder = CurrentFolder.substr(0, cut);
	return CurrentFolder;
}


bool Dictionary::searchFile(string fileName, string filePath) {
	bool found = false;

	for (unsigned int i = 0; i < this->fileDescriptorVector.size(); i++) {
		if (this->fileDescriptorVector[i].fileName == fileName && this->fileDescriptorVector[i].filePath == filePath) {
			found = true;	
		}
	}
	return found;
}
bool Dictionary::searchDirectory(string folder, string subfolder) {
	bool found = false;
	if (folder == "root" && (subfolder.size() == 0 || subfolder == "root")) {
		// faking the root directory
		found = true;
	}
	else {
		for (unsigned int i = 0; i < this->system.size(); i++) {
			if (this->system[i].folder == folder && this->system[i].subfolder == subfolder) {
				found = true;
			}
		}
	}
	return found;
}

string Dictionary::getLastElement(string fullPath) {
	string lastElement;
	if (fullPath.find_first_of("/") == string::npos) {
		lastElement = fullPath;
	}
	else {
		lastElement = fullPath.substr(fullPath.find_last_of("/") + 1, fullPath.size());
	}
	return lastElement;
}

string Dictionary::convertRelativeToAbsolutePath(string relativePath, string currentFolder) {
	string absolutPath;
	// ha nincs benne se . se ..
	if (relativePath.find_first_of(".") == string::npos) {
		absolutPath = currentFolder + "/" + relativePath;
	}
	//elso helyen van a .
	if (relativePath.size() > 1 && relativePath.at(0) == '.' && relativePath.at(1) == '/') {
		absolutPath = currentFolder + "/" + relativePath.substr(2, relativePath.size());
	} else if (relativePath.size() == 2 && relativePath.at(0) == '.'  && relativePath.at(1) == '.') {
		int cut = currentFolder.find_last_of("/");
		string currentFolderParent = currentFolder.substr(0, cut);
		absolutPath = currentFolderParent;
	} else if (relativePath.size() > 2 && relativePath.at(0) == '.'  && relativePath.at(1) == '.' && relativePath.at(2) == '/') {
		int cut = currentFolder.find_last_of("/");
		string currentFolderParent = currentFolder.substr(0, cut);
		string relativePathPart = relativePath.substr(2, relativePath.size());
		if (relativePathPart.size() == 1 && relativePathPart.at(0) == '/')
			absolutPath = currentFolderParent;
		else
			absolutPath = currentFolderParent + relativePathPart;
	} else {
		absolutPath = currentFolder + "/" + relativePath;
	}

	// ha /-re vegzodik, levagjuk
	if (absolutPath.at(absolutPath.size() - 1) == '/')
		absolutPath = absolutPath.substr(0, absolutPath.size() - 1);
	return absolutPath;
}

string Dictionary::getPath(string fullPath, string currentFolder) {
	string path;
	if (fullPath.find_first_of("/") == string::npos) {
		path = currentFolder;
	}
	else {
		path = fullPath.substr(0, fullPath.find_last_of("/")+1);
		path = convertRelativeToAbsolutePath(path, currentFolder);
	}
	return path;
}

string Dictionary::getParentPath(string fullPath) {
	string path = fullPath.substr(0, fullPath.find_last_of("/"));
	return path;
}

void Dictionary::moveFile(string sourcePath, string sourceLastElement, string destPath, string destLastElement) {
	bool found = false;
	for (unsigned int i = 0; i < this->fileDescriptorVector.size(); i++) {
		if (!found && this->fileDescriptorVector[i].fileName == sourceLastElement && this->fileDescriptorVector[i].filePath == sourcePath) {
			this->fileDescriptorVector[i].fileName = destLastElement;
			this->fileDescriptorVector[i].filePath = destPath;
			found = true;
			cout << "File "<< sourcePath << "/" << sourceLastElement  << " has been moved to " << destPath << "/" << destLastElement << endl;
		}
	}
}

void Dictionary::moveDirectory(string sourcePath, string sourceLastElement, string destPath, string destLastElement) {
	bool found = false;
	for (unsigned int i = 0; i < this->system.size(); i++) {
		if (!found && this->system[i].folder == sourcePath && this->system[i].subfolder == sourceLastElement) {
			this->system[i].folder = destPath;
			this->system[i].subfolder = destLastElement;
			found = true;
			cout << "Directory " << sourcePath << "/" << sourceLastElement << " has been moved to " << destPath << "/" << destLastElement << endl;
		}
	}

}

void Dictionary::mv(string currentFolder, string source, string dest) {
	string sourcePath = getPath(source, currentFolder);
	string sourceLastElement = getLastElement(source);
	string destPath = getPath(dest, currentFolder);
	string destLastElement = getLastElement(dest);

	bool isSourceFile = searchFile(sourceLastElement, sourcePath);
	bool isSourceDirectory = searchDirectory(sourcePath, sourceLastElement);
	bool isDestFile = searchFile(destLastElement, destPath);
	bool isDestDirectory = searchDirectory(destPath, destLastElement);

	if (isDestDirectory) {
		destPath = destPath + "/" + destLastElement;
		destLastElement = sourceLastElement;
		isDestFile = searchFile(destLastElement, destPath);
		isDestDirectory = searchDirectory(destPath, destLastElement);
	}

	if (isSourceFile == false && isSourceDirectory == false) {
		cout << "No such source file/directory!" << endl;
	}
	else if (isDestFile == true || isDestDirectory == true) {
		cout << "The destination file/directory already exists!" << endl;
	}
	else if (isDestFile == false && isDestDirectory == false && searchDirectory(getParentPath(destPath), getLastElement(destPath)) == false) {
		cout << "Neither the destination directory nor the parent of destination directory exist !" << endl;
	}
	else {
		if (isSourceFile) 
			moveFile(sourcePath, sourceLastElement, destPath, destLastElement);
		else 
			moveDirectory(sourcePath, sourceLastElement, destPath, destLastElement);
	}

}

