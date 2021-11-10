#ifndef TRANSPARENT_WIDGET
#define TRANSPARENT_WIDGET

#include <Wt/WImage.h>
#include <Wt/WContainerWidget.h>

using namespace Wt;

class transparentWidget : public WContainerWidget
{
public:
	transparentWidget(int spaceSize);
private:
	WImage *filler;
};

#endif // TRANSPARENT_WIDGET
