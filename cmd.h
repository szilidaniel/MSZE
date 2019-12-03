#ifndef CMD_H
#define CMD_H
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct Pair {
	string folder;
	string subfolder;
	Pair();
	Pair(string folder, string subfolder);
};

struct FileDescriptor {
	string fileName;
	string filePath;
	string fileContent;
};

class Dictionary {
private:
	vector<Pair> system;
	vector<FileDescriptor> fileDescriptorVector;
	vector<string> commands = { "mkdir","exit","ls","cd","rm","touch", "echo" };
	void deleteRecursively(string toDelete, string currentFolder);
	bool searchFile(string fileName, string filePath);
	bool searchDirectory(string forder, string subfolder);
	string getLastElement(string fullPath);
	string getPath(string fullPath, string currentFolder);
	string getParentPath(string fullPath);
	string convertRelativeToAbsolutePath(string relativePath, string currentFolder);
	void moveFile(string sourcePath, string sourceLastElement, string destPath, string destLastElement);
	void moveDirectory(string sourcePath, string sourceLastElement, string destPath, string destLastElement);

public:
	void mkdir(string dirName, string currentFolder);
	void ls(string currentFolder);
	string cd(string dirName, string currentFolder);
	void rm(string dirName, string currentFolder);
	void rmForce(string dirName, string currentFolder);
	void touch(string fileName, string currentFolder);
	void echo(string fileContent, string fileName, string currentFolder);
	void writeToFile(string fsname);
	void loadFromFile(string fsname);
	void splitString(string& str, vector<string>& out, string delim);
	void addPairToVector(string folder, string subfolder);
	void splitFolderPath(string line);
	bool isValid(string dirName);
	bool validcommand(string command);
	void splitDirNameAndPath(string dirname, string CurrentFolder, vector<string>path);
	string splitCurrentFolder(string CurrentFolder);
	void mv(string currentFolder, string source, string dest);
};

#endif
