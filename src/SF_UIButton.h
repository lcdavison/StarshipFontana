#ifndef SF_UIBUTTON_H
#define SF_UIBUTTON_H

#include <functional>
#include <iostream>
#include "SFBoundingBox.h"

enum SF_BUTTONSTATE { SFBUTTON_IDLE, SFBUTTON_HOVER, SFBUTTON_CLICK };

class SF_UIButton {
	public:
		SF_UIButton(std::string, int, int, int, int, std::function<void (void)>);
		~SF_UIButton();

		void OnClick(); // Function pointer
	private:

		function<void (void)> OnClickFunction;

		std::string text;
		int x, y;
		int width, height;
		SF_BUTTONSTATE state;
		shared_ptr<SFBoundingBox>	box;
};
#endif
