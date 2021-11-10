#ifndef LOGIN_WIDGET
#define LOGIN_WIDGET

#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

using namespace Wt;

class LoginWidget : public WContainerWidget
{
public:
	LoginWidget();
	WLineEdit *enterName;
	WPushButton *login, *signup;
private:
	WText *spacer;
};

#endif // LOGIN_WIDGET
