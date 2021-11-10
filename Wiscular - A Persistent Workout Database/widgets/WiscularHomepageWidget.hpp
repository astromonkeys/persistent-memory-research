#ifndef WISCULAR_HOMEPAGE_WIDGET
#define WISCULAR_HOMEPAGE_WIDGET

#include <Wt/WContainerWidget.h>
#include <Wt/WImage.h>

using namespace Wt;

class WiscularHomepageWidget : public WContainerWidget
{
public:
	WiscularHomepageWidget();
private:
	WImage *wiscularText;
};

#endif // WISCULAR_HOMEPAGE_WIDGET
