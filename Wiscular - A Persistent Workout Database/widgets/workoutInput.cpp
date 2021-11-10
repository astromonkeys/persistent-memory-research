#include "workoutInput.hpp"
#include <typeinfo>
#include <Wt/WText.h>

using namespace std;

workoutInput::workoutInput() : WContainerWidget()
{
	setContentAlignment(AlignmentFlag::Center);

	picker = addWidget(std::make_unique<WDatePicker>());
	picker->setFormat("MM-dd-yyyy");
	picker->setInline(false);

	enterType = addWidget(std::make_unique<WComboBox>());
    enterType->addItem("Walk/Run");
    enterType->addItem("Bike");
    enterType->addItem("Swim");
	
	addWidget(std::make_unique<WText>(" "));
    inputDist = addWidget(std::make_unique<WLineEdit>());

	addWidget(std::make_unique<WText>(" "));
    enterDistUnits = addWidget(std::make_unique<WComboBox>());
    enterDistUnits->addItem("Meters");
    enterDistUnits->addItem("Kilometers");
    enterDistUnits->addItem("Miles");

	addWidget(std::make_unique<WText>(" "));
    inputTime = addWidget(std::make_unique<WLineEdit>());

	addWidget(std::make_unique<WText>(" "));
	enterTimeUnits = addWidget(std::make_unique<WComboBox>());
    enterTimeUnits->addItem("Minutes");
    enterTimeUnits->addItem("Hours");
    enterTimeUnits->addItem("Seconds");

	addWidget(std::make_unique<WText>(" "));
    commitData = addWidget(std::make_unique<WPushButton>("Submit"));

	addWidget(std::make_unique<WText>(" "));
	cancel = addWidget(std::make_unique<WPushButton>("Cancel"));
}

std::string workoutInput::getType() { return enterType->currentText().narrow(); }
std::string workoutInput::getDistanceUnits() { return enterDistUnits->currentText().narrow(); }
std::string workoutInput::getDurationUnits() { return enterTimeUnits->currentText().narrow(); }
std::string workoutInput::getDistance() { return inputDist->text().toXhtmlUTF8(); }
std::string workoutInput::getDuration() { return inputTime->text().toXhtmlUTF8(); }
std::string workoutInput::getDay() { return to_string(picker->date().day()); } 
std::string workoutInput::getMonth() { return to_string(picker->date().month()); }
std::string workoutInput::getYear() { return to_string(picker->date().year()); }
