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
 * ButtonSettingsLayout.cpp
 *
 *  Created on: Sept 3, 2012
 *      Author: Spiridon Alexandru
 */

#include "ButtonSettingsLayout.h"

#define PROPERTY_LINE_HEIGHT 80

/**
 * Constructor.
 */
ButtonSettingsLayout::ButtonSettingsLayout():
	VerticalLayout(),
	setTextButton(NULL),
	setTextEditBox(NULL),
	getTextButton(NULL),
	getTextLabel(NULL)
{
	createMainLayout();

	setTextButton->addButtonListener(this);
	getTextButton->addButtonListener(this);
}

/**
 * Destructor.
 */
ButtonSettingsLayout::~ButtonSettingsLayout()
{
	setTextButton->removeButtonListener(this);
	getTextButton->removeButtonListener(this);
}

/**
 * Creates and adds main layout to the screen.
 */
void ButtonSettingsLayout::createMainLayout()
{
	createSetButtonTextLayout();
	createGetButtonTextLayout();
}

/**
 * Creates the set button text layout.
 */
void ButtonSettingsLayout::createSetButtonTextLayout()
{
	HorizontalLayout* setTextHorizontalLayout = new HorizontalLayout();
	setTextHorizontalLayout->setHeight(PROPERTY_LINE_HEIGHT);
	setTextButton = new Button();
	setTextButton->setText("Set button text:");
	setTextButton->fillSpaceHorizontally();
	setTextHorizontalLayout->addChild(setTextButton);

	setTextEditBox = new EditBox();
	setTextEditBox->setPlaceholder("Button text");
	setTextEditBox->fillSpaceHorizontally();
	setTextHorizontalLayout->addChild(setTextEditBox);

	this->addChild(setTextHorizontalLayout);
}

/**
 * Creates the get button text layout.
 */
void ButtonSettingsLayout::createGetButtonTextLayout()
{
	HorizontalLayout* getTextHorizontalLayout = new HorizontalLayout();
	getTextHorizontalLayout->setHeight(PROPERTY_LINE_HEIGHT);
	getTextButton = new Button();
	getTextButton->setText("Get button text:");
	getTextButton->fillSpaceHorizontally();
	getTextHorizontalLayout->addChild(getTextButton);

	getTextLabel = new Label();
	getTextLabel->setText("No text yet");
	getTextLabel->fillSpaceHorizontally();
	getTextHorizontalLayout->addChild(getTextLabel);

	this->addChild(getTextHorizontalLayout);
}

/**
 * Sets the main button.
 */
void ButtonSettingsLayout::setMainButton(Button* button)
{
	mButton = button;
}

/**
 * This method is called if the touch-up event was inside the
 * bounds of the button.
 * @param button The button object that generated the event.
 */
void ButtonSettingsLayout::buttonClicked(Widget* button)
{
	if (button == setTextButton)
	{
		mButton->setText(setTextEditBox->getText());
	}
	else if (button == getTextButton)
	{
		getTextLabel->setText(mButton->getText());
	}
}
