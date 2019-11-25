#ifndef CMD_H
#define CMD_H
#include <iostream>
#include <string>
#include <vector>

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
	vector<string> commands = { "mkdir","exit","ls","cd","rm","touch" };
public:
	void mkdir(string dirName, string currentFolder);
	void ls(string currentFolder);
	string cd(string dirName, string currentFolder);
	void rm(string dirName, string currentFolder);
	void deleteRecursively(string toDelete, string currentFolder);
	void rmForce(string dirName, string currentFolder);
	void touch(string fileName, string currentFolder);
	void echo(string fileContent, string fileName, string currentFolder);
	void writeToFile(string fsname);
	void loadFromFile(string fsname);
	void splitString(string& str, vector<string>& out, string delim);
	void addPairToVector(string folder, string subfolder);
	void splitFolderPath(string line);
	bool isNotValid(string dirName);
	bool validcommand(string command);
};

#endif