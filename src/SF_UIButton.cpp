#include "SF_UIButton.h" 

SF_UIButton::SF_UIButton(std::string text, int x, int y, int w, int h) : text(text), x(x), y(y), width(w), height(h) {
	
	OnClickFunction = [] { std::cout << "Test" << std::endl; };
}

SF_UIButton::~SF_UIButton() {

} 

void SF_UIButton::OnClick() {
	OnClickFunction();
} 
