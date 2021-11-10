#ifndef PROFILE_LOGGED
#define PROFILE_LOGGED

#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

#include "WiscularHomepageWidget.hpp"
#include "LinksWidget.hpp"
#include "transparentWidget.hpp"
#include "workoutInput.hpp"

#include <string>
#include <vector>

using namespace Wt;

class profilepageLogged : public WContainerWidget
{
public:
	profilepageLogged(std::string username);
	void showAddWorkoutWidget();
	void hideAddWorkoutWidget(); 
	void setname(std::string name);
	void showWorkouts(std::vector<std::vector<std::string>> workouts);
	void removeWorkouts(std::string username);

	LinksWidget *internalLinks;
	WPushButton *addWorkout, *showMyWorkouts;
	WText *username_;
	workoutInput *addWorkoutWidget;
private:
	std::string user;
	bool displayed;
	WiscularHomepageWidget *logo;
	transparentWidget *space;
};

#endif // PROFILE_LOGGED
