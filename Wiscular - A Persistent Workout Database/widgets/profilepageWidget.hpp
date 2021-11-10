#ifndef PROFILEPAGE_WIDGET
#define PROFILEPAGE_WIDGET

#include "WiscularHomepageWidget.hpp"
#include "LinksWidget.hpp"
#include "transparentWidget.hpp"

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>

using namespace Wt;

class profilepageWidget : public WContainerWidget
{
public:
	profilepageWidget();
	LinksWidget *internalLinks;
private:
	transparentWidget *space; 
	WiscularHomepageWidget *logo;
};

#endif // PROFILEPAGE_WIDGET
