#include "profilepageWidget.hpp"

profilepageWidget::profilepageWidget() : WContainerWidget()
{
	logo = addWidget(std::make_unique<WiscularHomepageWidget>());
	internalLinks = addWidget(std::make_unique<LinksWidget>());
	addWidget(std::make_unique<WText>("<h1>In order to view your profile and add workouts, go log in on the homepage!</h1>"));
    space = addWidget(std::make_unique<transparentWidget>(700));
}
