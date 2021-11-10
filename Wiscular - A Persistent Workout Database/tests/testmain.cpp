#include <iostream>
#include <vector>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <memory>

using namespace std;

class WiscularApp
{
public:
	WiscularApp(char *args[]);
//private:
	FILE *backendCommand(std::string command);
	void registerUser(std::string in);
	bool checkUserExists(std::string name);
	void splitString(std::string s, std::vector<std::string> &v);
	std::string currentUser;
};

WiscularApp::WiscularApp(char *args[])
{

}

FILE *WiscularApp::backendCommand(std::string command)
{
	FILE *pipe = popen(command.c_str(), "r");
    if(!pipe) exit(EXIT_FAILURE);
	else return pipe; // let each function decide how to interpret the output file
}

void WiscularApp::registerUser(std::string in)
{
	std::string register_user = "backend register " + in;
	FILE *output = backendCommand(register_user);
	size_t len = 0;
    ssize_t read;
    char *line = NULL;

	while((read = getline(&line, &len, output)) != -1) {
		cout << line << endl;
	}
}

bool WiscularApp::checkUserExists(std::string username) {
    std::string command = "/var/www/wt/backend list";
    FILE *output = backendCommand(command); 
	size_t len = 0; ssize_t read; char *line = NULL;
    std::string text;
	username = username + "\n";
	cout << "\"" << username << "\"" << endl;
    while((read = getline(&line, &len, output)) != -1) {
        text = std::string(line);
		cout << "\"" << text << "\"" << endl;
        if(text == username) return true;
    }
    return false;
}

/*
std::vector<Workout> WiscularApp::showExplorepageWorkouts()
{
    // TODO make sure to refresh the explore page when a new workout is added(on clicking submit)
    std::string command = "/var/www/wt/backend allWorkouts";
    FILE *output = backend(command);
    size_t len = 0; ssize_t read; char *line = NULL;
    std::string text;
    std::vector<Workout> workouts;
    std::vector<std::string> currentWorkout;
    while((read = getline(&line, &len, output)) != -1) {
        text = std::string(line);
        splitString(text, currentWorkout);
    }
}
*/
void WiscularApp::splitString(std::string s, std::vector<std::string> &v)
{
    string temp = "";
    for(int i = 0;i < s.length(); ++i) {
        if(s[i] == ' ') {
            v.push_back(temp);
            temp = "";
        } else { temp.push_back(s[i]); }
    }
    v.push_back(temp);
}

int main(int agrc, char *argv[])
{
    std::unique_ptr<WiscularApp> app = std::make_unique<WiscularApp>(argv);
	
	string command = argv[1];
	if(command == "register") {
		app->registerUser(argv[2]);
	} else if(command == "addWorkout") {
		std::string command = "backend addWorkout Swim greg Miles Minutes 78 1.8 25 7 2021";
		FILE *output = app->backendCommand(command);
		size_t len = 0;
    	ssize_t read;
    	char *line = NULL;

    	while((read = getline(&line, &len, output)) != -1) {
        	cout << line << endl;
    	}
	} else if(command == "explore") {
		FILE *output = app->backendCommand("backend allWorkouts");
		size_t len = 0; ssize_t read; char *line = NULL;
    	std::string text;
    	std::vector<std::vector<std::string>> workouts;
    	while((read = getline(&line, &len, output)) != -1) {
        	std::vector<std::string> currentWorkout;
			text = std::string(line);
        	app->splitString(text, currentWorkout);
			workouts.push_back(currentWorkout);
    	}
		for(int i = 0; i < workouts.size(); ++i) {
			for(int j = 0; j < workouts[i].size(); ++j) {
				cout << workouts[i][j] << endl;
			}
			cout << " " << endl;
		}
	} else {
		cout << "command not recognized" << endl;
	}
	return 0;
}

