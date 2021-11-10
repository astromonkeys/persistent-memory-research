#include "profilepageWidgetLogged.hpp"
#include "workoutWidget.hpp"

using namespace Wt;

profilepageLogged::profilepageLogged(std::string username) : WContainerWidget()
{
	user = username;
	logo = addWidget(std::make_unique<WiscularHomepageWidget>());
    internalLinks = addWidget(std::make_unique<LinksWidget>());
	addWorkout = addWidget(std::make_unique<WPushButton>("Add a new workout"));	
	addWidget(std::make_unique<transparentWidget>(20));
	showMyWorkouts = addWidget(std::make_unique<WPushButton>("Display my workouts"));
	addWorkoutWidget = addWidget(std::make_unique<workoutInput>());
	addWorkoutWidget->hide();
	username_ = addWidget(std::make_unique<WText>("<h1>" + user + "'s profile...</h1>"));
	displayed = false;
	space = addWidget(std::make_unique<transparentWidget>(700));
}

void profilepageLogged::showWorkouts(std::vector<std::vector<std::string>> workouts)
{
	if(!displayed){
	removeWidget(space);
    for(int i = 0; i < workouts.size(); ++i) { // for each workout
        std::string type = workouts[i][0];
        std::string distance = workouts[i][1];
        std::string distanceUnits = workouts[i][2];
        std::string duration = workouts[i][3];
        std::string durationUnits = workouts[i][4];
        std::string day = workouts[i][5];
        std::string month = workouts[i][6];
        std::string year = workouts[i][7];
        std::string username = workouts[i][8];
        addWidget(std::make_unique<workoutWidget>(type, distance, distanceUnits, duration, durationUnits, day, month, year, username));
        addWidget(std::make_unique<transparentWidget>(30));
    }
	space = addWidget(std::make_unique<transparentWidget>(700));
	displayed = true;
	}
}

void profilepageLogged::removeWorkouts(std::string username)
{
    clear();
    logo = addWidget(std::make_unique<WiscularHomepageWidget>());
    internalLinks = addWidget(std::make_unique<LinksWidget>());
	addWorkout = addWidget(std::make_unique<WPushButton>("Add a new workout"));
	displayed = false;
	addWidget(std::make_unique<transparentWidget>(20));
	showMyWorkouts = addWidget(std::make_unique<WPushButton>("Display my workouts"));
	addWorkoutWidget = addWidget(std::make_unique<workoutInput>());
	hideAddWorkoutWidget();
    username_ = addWidget(std::make_unique<WText>("<h1>" + username + "'s profile...</h1>"));
	space = addWidget(std::make_unique<transparentWidget>(700));
}


void profilepageLogged::showAddWorkoutWidget()
{
	addWorkout->hide();
	addWorkoutWidget->show();
}

void profilepageLogged::hideAddWorkoutWidget()
{	
	addWorkoutWidget->inputDist->setText("");
	addWorkoutWidget->inputTime->setText("");
	
	addWorkoutWidget->hide();
	addWorkout->show();
}

void profilepageLogged::setname(std::string name)
{
	username_->setText("<h1>" + name + "'s profile... </h1>");
}	
