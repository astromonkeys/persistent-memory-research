#include "WiscularHomepageWidget.hpp"

using namespace Wt;

WiscularHomepageWidget::WiscularHomepageWidget() : WContainerWidget()
{
	//setInline(true);
	setContentAlignment(AlignmentFlag::Center);
	wiscularText = addWidget(std::make_unique<Wt::WImage>("assets/wiscularText.png"));
	wiscularText->resize(850, 240);
}
