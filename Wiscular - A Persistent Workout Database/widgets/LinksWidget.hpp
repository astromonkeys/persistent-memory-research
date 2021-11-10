#ifndef LINKS_WIDGET
#define LINKS_WIDGET

#include <Wt/WAnchor.h>
#include <Wt/WTable.h>
#include <Wt/WTableCell.h>

using namespace Wt;

class LinksWidget : public WContainerWidget
{
public:
	LinksWidget();
	WTable *links;
private:
};

#endif // LINKS_WIDGET
