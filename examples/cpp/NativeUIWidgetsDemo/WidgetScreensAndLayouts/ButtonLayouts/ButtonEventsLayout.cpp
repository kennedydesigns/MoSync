/*
Copyright (C) 2012 MoSync AB

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License,
version 2, as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301, USA.
*/

/**
 *  ButtonEventsLayout.cpp
 *
 *  Created on: Sept 3, 2012
 *      Author: Spiridon Alexandru
 */

#include "ButtonEventsLayout.h"

#define TITLE_LABEL_HEIGHT 100
#define TITLE_LABEL_FONT_SIZE 24

/**
 * Constructor.
 */
ButtonEventsLayout::ButtonEventsLayout():
	VerticalLayout(),
	mButton(NULL)
{
	createMainLayout();

	mButton->addButtonListener(this);
}

/**
 * Destructor.
 */
ButtonEventsLayout::~ButtonEventsLayout()
{
	mButton->removeButtonListener(this);
}

/**
 * Creates and adds main layout to the screen.
 */
void ButtonEventsLayout::createMainLayout()
{
	mButton = new Button();
	mButton->setText("Test button");
	mButton->fillSpaceHorizontally();

	this->addChild(mButton);

	Label* eventsLabel = new Label();
	eventsLabel->setText("Button events");
	eventsLabel->setFontSize(TITLE_LABEL_FONT_SIZE);
	eventsLabel->setHeight(TITLE_LABEL_HEIGHT);
	this->addChild(eventsLabel);

	mButtonPressedLabel = new Label();
	mButtonPressedLabel->setText("Button not pressed");
	this->addChild(mButtonPressedLabel);

	mButtonReleasedLabel = new Label();
	mButtonReleasedLabel->setText("Button not pressed");
	this->addChild(mButtonReleasedLabel);

	mButtonClickedLabel = new Label();
	mButtonClickedLabel->setText("Button not clicked");
	this->addChild(mButtonClickedLabel);
}

/**
 * Gets the main test button.
 */
Button* ButtonEventsLayout::getMainButton()
{
	return mButton;
}

/**
 * This method is called when there is an touch-down event for
 * a button.
 * Platform: iOS and Android.
 * @param button The button object that generated the event.
 */
void ButtonEventsLayout::buttonPressed(Widget* button)
{
	mButtonPressedLabel->setText("Main button pressed!");
}

/**
 * This method is called when there is an touch-up event for
 * a button.
 * Platform: iOS and Android.
 * @param button The button object that generated the event.
 */
void ButtonEventsLayout::buttonReleased(Widget* button)
{
	mButtonReleasedLabel->setText("Main button released!");
}

/**
 * This method is called if the touch-up event was inside the
 * bounds of the button.
 * Platform: iOS, Android, Windows Phone.
 * @param button The button object that generated the event.
 */
void ButtonEventsLayout::buttonClicked(Widget* button)
{
	mButtonClickedLabel->setText("Main button clicked!");
}
