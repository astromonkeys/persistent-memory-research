#include "widgets/homepageWidget.hpp"
#include "widgets/explorepageWidget.hpp"
#include "widgets/profilepageWidget.hpp"
#include "widgets/profilepageWidgetLogged.hpp"
#include "widgets/workoutInput.hpp"

#include <Wt/WApplication.h>
#include <Wt/WColor.h>
#include <Wt/WTable.h>
#include <Wt/WTableCell.h>
#include <Wt/WText.h>
#include <Wt/WStackedWidget.h>

#include <iostream>
#include <vector>
#include <stdexcept>
#include <stdio.h>
#include <string>

using namespace Wt;
using namespace std;

class WiscularApp : public WApplication
{
public:
	WiscularApp(const WEnvironment &env);
private:
	FILE* backend(std::string command);
	bool userExists(std::string username);
	void showHomepage();
    void showExplorepage();
    void showProfilepage();
    void showProfilepageLogged();
    void logIn();
    void registerUser();
    void logOut();
    void hideWorkoutInterface();
    void displayWorkoutInterface();
    void persistWorkout();
	void connectLinks();
	void initializeApp();
	void initializeWidgets();
	bool loggedIn;
	void showExplorepageWorkouts();
	void showProfilepageWorkouts();
	void splitString(std::string s, std::vector<std::string> &v);
	std::string currentUser;
	WStackedWidget *mainstack; 
	homepageWidget *homepage;
	explorepageWidget *explorepage;
	profilepageWidget *profilepage;
	profilepageLogged *profilePageLogged;
};

WiscularApp::WiscularApp(const WEnvironment &env) : WApplication(env)
{ 	
	loggedIn = false;
	
	initializeApp();
	initializeWidgets();
	
	root()->addWidget(std::unique_ptr<WStackedWidget>(mainstack));
}

void WiscularApp::showProfilepageWorkouts()
{
	FILE *output = backend(std::string("/var/www/wt/wiscular_backend userWorkouts " + currentUser));
    size_t len = 0; ssize_t read; char *line = NULL;
    std::string text;
    std::vector<std::vector<std::string>> workouts;
    while((read = getline(&line, &len, output)) != -1) {
        std::vector<std::string> currentWorkout;
        text = std::string(line);
        splitString(text, currentWorkout);
        workouts.push_back(currentWorkout);
    }
	profilePageLogged->showWorkouts(workouts);
}

void WiscularApp::showExplorepageWorkouts()
{
	FILE *output = backend("/var/www/wt/wiscular_backend allWorkouts");
    size_t len = 0; ssize_t read; char *line = NULL;
    std::string text;
    std::vector<std::vector<std::string>> workouts;
    while((read = getline(&line, &len, output)) != -1) {
        std::vector<std::string> currentWorkout;
        text = std::string(line);
        splitString(text, currentWorkout);
        workouts.push_back(currentWorkout);
    }
	// send workouts to the explore page as a vector of vector<string>s
	// and have the explore page widget construct the widgets from there
	explorepage->showWorkouts(workouts);
}

void WiscularApp::splitString(std::string s, std::vector<std::string> &v)
{
    std::string temp = "";
    for(int i = 0;i < s.length(); ++i) {
        if(s[i] == ' ') {
            v.push_back(temp);
            temp = "";
        } else { temp.push_back(s[i]); }
    }
    v.push_back(temp);
}

void WiscularApp::persistWorkout() 
{
	// for some reason the pool becomes unavailable after calling this once, don't worry about it
	std::string type = profilePageLogged->addWorkoutWidget->getType();
	std::string distanceUnits = profilePageLogged->addWorkoutWidget->getDistanceUnits();
	std::string durationUnits = profilePageLogged->addWorkoutWidget->getDurationUnits();
	std::string duration = profilePageLogged->addWorkoutWidget->getDuration();
	std::string distance = profilePageLogged->addWorkoutWidget->getDistance();
	std::string day = profilePageLogged->addWorkoutWidget->getDay();
	std::string month = profilePageLogged->addWorkoutWidget->getMonth();
	std::string year = profilePageLogged->addWorkoutWidget->getYear();

	std::string command = "/var/www/wt/wiscular_backend addWorkout "\
						+ type + " "\
						+ currentUser + " "\
						+ distanceUnits + " "\
						+ durationUnits + " "\
						+ duration + " "\
						+ distance + " "\
						+ day + " "\
						+ month + " "\
						+ year;
	
	FILE *output = backend(command); // don't need file output
	size_t len = 0; ssize_t read; char *line = NULL;
    std::string text;
	getline(&line, &len, output);
	text = std::string(line);
	profilePageLogged->removeWorkouts(currentUser);
	explorepage->removeWorkouts();
	connectLinks();
	profilePageLogged->addWorkout->clicked().connect(this, &WiscularApp::displayWorkoutInterface);
	showExplorepageWorkouts();
	showProfilepageWorkouts();
}

FILE* WiscularApp::backend(std::string command)
{
    FILE *pipe = popen(command.c_str(), "r");
    if(!pipe) exit(EXIT_FAILURE);
    else return pipe; // let each function decide how to interpret the output file
}

bool WiscularApp::userExists(std::string username) 
{
	std::string command = "/var/www/wt/wiscular_backend listUsers";
    FILE *output = backend(command);
    size_t len = 0; ssize_t read; char *line = NULL;
    std::string text;
    username = username + "\n";
    while((read = getline(&line, &len, output)) != -1) {
        text = std::string(line);
        if(text == username) return true;
    }
    return false;
}

void WiscularApp::logIn()
{
	std::string usernameInput = homepage->loginInterface->enterName->text().narrow(); 
	if(userExists(usernameInput)) { 
		homepage->hideLoginError();
		currentUser = usernameInput;
		homepage->loginInterface->enterName->setText("");
		homepage->logIn(currentUser);
		homepage->logout->clicked().connect(this, &WiscularApp::logOut);
		loggedIn = true;
	} else {
		homepage->showLoginError(1, usernameInput);
		homepage->loginInterface->enterName->setText("");
	}
}

void WiscularApp::registerUser()
{
	std::string usernameInput = homepage->loginInterface->enterName->text().narrow();
	if(usernameInput != "" && usernameInput != " " && !userExists(usernameInput)) {
		std::string command = "/var/www/wt/wiscular_backend registerUser " + usernameInput;
		backend(command); // don't need file output
		std::string text = "User '" + usernameInput + "' successfully registered. Click 'Login' to log in!";
		homepage->loggedIn->setText(text);
		homepage->hideLoginError();
	} else {
		homepage->showLoginError(2, usernameInput);
        homepage->loginInterface->enterName->setText("");
	}
}

void WiscularApp::logOut()
{
	currentUser = "";
	profilePageLogged->removeWorkouts(currentUser);
    connectLinks();
    profilePageLogged->addWorkout->clicked().connect(this, &WiscularApp::displayWorkoutInterface);
	homepage->loginInterface->enterName->setText("");
	homepage->logOut();
	loggedIn = false;
}

void WiscularApp::hideWorkoutInterface() { profilePageLogged->hideAddWorkoutWidget(); }

void WiscularApp::displayWorkoutInterface()
{
    profilePageLogged->showAddWorkoutWidget();
    profilePageLogged->addWorkoutWidget->commitData->clicked().connect(this, &WiscularApp::persistWorkout);
    profilePageLogged->addWorkoutWidget->cancel->clicked().connect(this, &WiscularApp::hideWorkoutInterface);
}

void WiscularApp::showHomepage() { mainstack->setCurrentWidget(homepage); }

void WiscularApp::showExplorepage() { mainstack->setCurrentWidget(explorepage); }

void WiscularApp::showProfilepage()
{
	if(!loggedIn) {
		mainstack->setCurrentWidget(profilepage);
	} else {
		profilePageLogged->setname(currentUser);
    	mainstack->setCurrentWidget(profilePageLogged);
	}
}

void WiscularApp::connectLinks()
{
    homepage->internalLinks->links->elementAt(0, 0)->clicked().connect(this, &WiscularApp::showHomepage);
    homepage->internalLinks->links->elementAt(0, 1)->clicked().connect(this, &WiscularApp::showExplorepage);
    homepage->internalLinks->links->elementAt(0, 2)->clicked().connect(this, &WiscularApp::showProfilepage);

    explorepage->internalLinks->links->elementAt(0, 0)->clicked().connect(this, &WiscularApp::showHomepage);
    explorepage->internalLinks->links->elementAt(0, 1)->clicked().connect(this, &WiscularApp::showExplorepage);
    explorepage->internalLinks->links->elementAt(0, 2)->clicked().connect(this, &WiscularApp::showProfilepage);

    profilepage->internalLinks->links->elementAt(0, 0)->clicked().connect(this, &WiscularApp::showHomepage);
    profilepage->internalLinks->links->elementAt(0, 1)->clicked().connect(this, &WiscularApp::showExplorepage);
    profilepage->internalLinks->links->elementAt(0, 2)->clicked().connect(this, &WiscularApp::showProfilepage);

    profilePageLogged->internalLinks->links->elementAt(0, 0)->clicked().connect(this, &WiscularApp::showHomepage);
    profilePageLogged->internalLinks->links->elementAt(0, 1)->clicked().connect(this, &WiscularApp::showExplorepage);
    profilePageLogged->internalLinks->links->elementAt(0, 2)->clicked().connect(this, &WiscularApp::showProfilepage);
}

void WiscularApp::initializeWidgets()
{
    mainstack = new WStackedWidget();
    homepage = mainstack->addWidget(std::make_unique<homepageWidget>());
    explorepage = mainstack->addWidget(std::make_unique<explorepageWidget>());
	showExplorepageWorkouts();
    profilepage = mainstack->addWidget(std::make_unique<profilepageWidget>());
    profilePageLogged = mainstack->addWidget(std::make_unique<profilepageLogged>(""));
    profilePageLogged->showMyWorkouts->clicked().connect(this, &WiscularApp::showProfilepageWorkouts);
	profilePageLogged->addWorkout->clicked().connect(this, &WiscularApp::displayWorkoutInterface);
	connectLinks();
    mainstack->setCurrentWidget(homepage);
    homepage->loginInterface->login->clicked().connect(this, &WiscularApp::logIn);
    homepage->loginInterface->signup->clicked().connect(this, &WiscularApp::registerUser);
}

void WiscularApp::initializeApp()
{
    std::unique_ptr<WColor> backgroundColor(new WColor(125, 112, 112)); // initially set to gray
    root()->decorationStyle().setBackgroundColor(*backgroundColor);
    root()->setContentAlignment(AlignmentFlag::Center);
    setTitle("Wiscular");
}

int main(int argc, char *argv[])
{
    return WRun(argc, argv, [](const WEnvironment &env) {
        return std::make_unique<WiscularApp>(env);
    });
}

