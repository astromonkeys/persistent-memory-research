#include "LinksWidget.hpp"
#include <Wt/WLength.h>
#include <Wt/WPushButton.h>

using namespace Wt;

LinksWidget::LinksWidget() : WContainerWidget()
{
	setContentAlignment(AlignmentFlag::Center);
	
	links = addWidget(std::make_unique<WTable>());
	links->elementAt(0, 0)->addWidget(std::make_unique<WPushButton>("Home"));
    links->elementAt(0, 1)->addWidget(std::make_unique<WPushButton>("Explore"));
    links->elementAt(0, 2)->addWidget(std::make_unique<WPushButton>("My Profile"));
  
  	WLength *colWidth = new WLength(200);
	WLength *rowHeight = new WLength(35);
	links->rowAt(0)->setHeight(*rowHeight);
	
	for(int i = 0; i < 3; i++) 
	{ 
	links->columnAt(i)->setWidth(*colWidth); 
	links->elementAt(0, i)->setContentAlignment(AlignmentFlag::Center);
	}
	
	delete colWidth;
	delete rowHeight;
}
