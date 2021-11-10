#ifndef HOMEPAGE_WIDGET
#define HOMEPAGE_WIDGET

#include "WiscularHomepageWidget.hpp"
#include "LinksWidget.hpp"
#include "LoginWidget.hpp"
#include "transparentWidget.hpp"

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WPushButton.h>

using namespace Wt;

class homepageWidget : public WContainerWidget
{
public:
	homepageWidget();
	void logIn(std::string username);
	void logOut();
	void showLoginError(int code, std::string name);
	void hideLoginError();
	LinksWidget *internalLinks;
	LoginWidget *loginInterface;
	WPushButton *logout;
	WText *loginText1, *loggedIn, *loginError;
private:
	WiscularHomepageWidget *logo;
	transparentWidget *logoutSpace, *space, *space1, *space2; 
};

#endif // HOMEPAGE_WIDGET
