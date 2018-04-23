#include "SF_UIButton.h" 

SF_UIButton::SF_UIButton(std::string text, int x, int y, int w, int h, std::function<void (void)> click_func) : text(text), x(x), y(y), width(w), height(h) {

	OnClickFunction	= click_func;
//	OnClickFunction = [] { std::cout << "Test" << std::endl; };
}

SF_UIButton::~SF_UIButton() {

} 

void SF_UIButton::OnClick() {
	OnClickFunction();
} 
