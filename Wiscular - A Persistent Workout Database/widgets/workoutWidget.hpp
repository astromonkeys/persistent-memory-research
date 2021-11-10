#ifndef WORKOUT_WIDGET
#define WORKOUT_WIDGET

#include <string>

#include <Wt/WText.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WImage.h>
#include "../backend.hpp"

using namespace Wt;

class workoutWidget : public WContainerWidget
{
public:
	workoutWidget(std::string type_, std::string distance_, std::string distanceUnits_, std::string duration_, std::string durationUnits_, std::string day_, std::string month_, std::string year_, std::string username_);
private:
	WText *day, *month, *year, *username, *type, *duration, *distance, *durationUnits, *distanceUnits; // keep text based for now, maybe make prettier later
	WImage *icon;
};

#endif // WORKOUT_WIDGET
