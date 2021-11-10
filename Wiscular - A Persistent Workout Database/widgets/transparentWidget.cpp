#include "transparentWidget.hpp"

// TODO implementation
// image path is "assets/filler.png"
transparentWidget::transparentWidget(int spaceSize) : WContainerWidget()
{
	setContentAlignment(AlignmentFlag::Center);
    filler = addWidget(std::make_unique<Wt::WImage>("assets/filler.png"));
    filler->resize(spaceSize, spaceSize);

}
