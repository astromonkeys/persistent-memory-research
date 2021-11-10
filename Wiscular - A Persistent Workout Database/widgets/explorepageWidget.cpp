#include "explorepageWidget.hpp"

explorepageWidget::explorepageWidget() : WContainerWidget()
{
	logo = addWidget(std::make_unique<WiscularHomepageWidget>());	
	internalLinks = addWidget(std::make_unique<LinksWidget>());
	addWidget(std::make_unique<WText>("<h1>Recently added workouts...</h1>"));
    //space = addWidget(std::make_unique<transparentWidget>(700));
}

void explorepageWidget::showWorkouts(std::vector<std::vector<std::string>> workouts)
{
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
}

void explorepageWidget::removeWorkouts()
{
	clear();
	logo = addWidget(std::make_unique<WiscularHomepageWidget>());
    internalLinks = addWidget(std::make_unique<LinksWidget>());
    addWidget(std::make_unique<WText>("<h1>Recently added workouts...</h1>"));
}
