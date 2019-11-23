#ifndef CMD_H
#define CMD_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Pair {
	string folder;
	string subfolder;
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
public:
	void mkdir(string dirName, string currentFolder);
	void ls(string currentFolder);
	string cd(string dirName, string currentFolder);
	void rm(string dirName, string currentFolder);
	void deleteRecursively(string toDelete, string currentFolder);
	void rmForce(string dirName, string currentFolder);
	void touch(string fileName, string currentFolder);
	void echo(string fileContent, string fileName, string currentFolder);
};

#endif