#include "LoginWidget.hpp"

using namespace Wt;

LoginWidget::LoginWidget() : WContainerWidget()
{
	enterName = addWidget(std::make_unique<WLineEdit>());
	spacer = addWidget(std::make_unique<WText>(" "));
	login = addWidget(std::make_unique<WPushButton>("Login"));
	signup = addWidget(std::make_unique<WPushButton>("Register"));
}
