#ifndef EXPLOREPAGE_WIDGET
#define EXPLOREPAGE_WIDGET

#include "WiscularHomepageWidget.hpp"
#include "LinksWidget.hpp"
#include "transparentWidget.hpp"
#include "workoutWidget.hpp"
#include "../backend.hpp"

#include <vector>
#include <string>

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>

using namespace Wt;

class explorepageWidget : public WContainerWidget
{
public:
	explorepageWidget();
	void showWorkouts(std::vector<std::vector<std::string>> workouts);
	void removeWorkouts();
	LinksWidget *internalLinks;
private:
	WiscularHomepageWidget *logo;
	transparentWidget *space;
};

#endif // EXPLOREPAGE_WIDGET
