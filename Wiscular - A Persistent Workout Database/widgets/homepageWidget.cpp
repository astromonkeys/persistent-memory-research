#include "homepageWidget.hpp"

homepageWidget::homepageWidget() : WContainerWidget()
{
	logo = addWidget(std::make_unique<WiscularHomepageWidget>());
	internalLinks = addWidget(std::make_unique<LinksWidget>());
    
	loginText1 = addWidget(std::make_unique<WText>("<b>Enter your user name to login or register:</b>"));
    loginText1->setInline(false);
    space1 = addWidget(std::make_unique<transparentWidget>(20));

	loginError = addWidget(std::make_unique<WText>());
	loginError->hide();

	loginInterface = addWidget(std::make_unique<LoginWidget>());
	space2 = addWidget(std::make_unique<transparentWidget>(20));
	loggedIn = addWidget(std::make_unique<WText>("Not logged in. Register or log in above!"));
	
	logoutSpace = addWidget(std::make_unique<transparentWidget>(10));
    logout = addWidget(std::make_unique<WPushButton>("Logout"));
	logoutSpace->hide();
	logout->hide();

	space = addWidget(std::make_unique<transparentWidget>(750));
}

void homepageWidget::logIn(std::string username)
{
	space1->hide();
	space2->hide();
	loginText1->hide();
	loginInterface->hide();
	loggedIn->setText("Logged in as: <b>" + username + "</b>");
	logoutSpace->show();
	logout->show();
}

void homepageWidget::logOut()
{
	space1->show();
	space2->show();
	logoutSpace->hide();
	logout->hide();
	loginText1->show();
	loginInterface->show();
	loggedIn->setText("Not logged in. Register or log in above!");
}

void homepageWidget::hideLoginError()
{
	loginError->hide();
}

void homepageWidget::showLoginError(int code, std::string name)
{	
	loginError->show();
	if(code == 1) {
		loginError->setText("Username '" + name + "' not found. Re-enter or register!");
	} else { // code == 2
		loginError->setText("Username '" + name + "' already taken. Try a different one!");
	}
}
