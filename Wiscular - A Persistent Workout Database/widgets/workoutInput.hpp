#ifndef INPUT_WORKOUT
#define INPUT_WORKOUT

#include "../backend.hpp"

#include <string>

#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WComboBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDatePicker.h>

using namespace Wt;

class workoutInput : public WContainerWidget
{
public:
	workoutInput();
	std::string getType();
	std::string getDurationUnits();
	std::string getDistanceUnits();
	std::string getDuration();
	std::string getDistance();
	std::string getDay();
	std::string getMonth();
	std::string getYear();
	WDatePicker *picker;
	WPushButton *cancel, *commitData;
	WComboBox *enterType, *enterDistUnits, *enterTimeUnits;
    WLineEdit *inputDist, *inputTime;
private:
};

#endif // INPUT_WORKOUT
