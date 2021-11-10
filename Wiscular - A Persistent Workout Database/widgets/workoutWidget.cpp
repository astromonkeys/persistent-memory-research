#include "workoutWidget.hpp"
#include <iostream>

using namespace std;

workoutWidget::workoutWidget(std::string type_, std::string distance_, std::string distanceUnits_, std::string duration_, std::string durationUnits_, std::string day_, std::string month_, std::string year_, std::string username_) : WContainerWidget()
{
	setContentAlignment(AlignmentFlag::Center);
	if(type_ == "Walk/Run") {
		icon = addWidget(std::make_unique<WImage>("assets/run.png"));
	} else if (type_ == "Swim") {
		icon = addWidget(std::make_unique<WImage>("assets/swim.png"));
	} else {
		icon = addWidget(std::make_unique<WImage>("assets/bike.png"));
	}
	icon->resize(40, 40);
	WImage *spaceragain = addWidget(std::make_unique<WImage>("assets/filler.png"));
	spaceragain->resize(17, 17);

	month = addWidget(std::make_unique<WText>(month_ + "/"));
	day = addWidget(std::make_unique<WText>(day_ + "/"));
	year = addWidget(std::make_unique<WText>(year_ + "    "));
	std::string st1 = "<b>" + username_ + "</b> did a ";
	username = addWidget(std::make_unique<WText>(st1));
	std::string st3 = std::string(type_ + " for ");
	type = addWidget(std::make_unique<WText>(st3));
	distance = addWidget(std::make_unique<WText>(distance_ + " "));
	std::string st2 = std::string(distanceUnits_ + " in ");
	distanceUnits = addWidget(std::make_unique<WText>(st2));
	duration = addWidget(std::make_unique<WText>(duration_ + " "));
	durationUnits = addWidget(std::make_unique<WText>(durationUnits_));
}
