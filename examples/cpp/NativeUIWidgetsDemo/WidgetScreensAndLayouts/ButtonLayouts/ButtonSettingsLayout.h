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
 *  ButtonSettingsLayout.h
 *
 *  Created on: Sept 3, 2012
 *      Author: Spiridon Alexandru
 */

#ifndef BUTTONSETTINGSLAYOUT_H_
#define BUTTONSETTINGSLAYOUT_H_

#include <maapi.h>
#include <MAUtil/util.h>

// Include all the wrappers.
#include <NativeUI/Widgets.h>

using namespace NativeUI;

class ButtonSettingsLayout:
	public VerticalLayout,
	public ButtonListener
{
public:
	/**
	 * Constructor.
	 */
	ButtonSettingsLayout();

	/**
	 * Destructor.
	 */
	~ButtonSettingsLayout();

	/**
	 * Sets the main button.
	 */
	void setMainButton(Button* button);
private:

	/**
	 * Creates and adds main layout to the screen.
	 */
	void createMainLayout();

	/**
	 * Creates the set button text layout.
	 */
	void createSetButtonTextLayout();

	/**
	 * Creates the get button text layout.
	 */
	void createGetButtonTextLayout();

    /**
     * This method is called if the touch-up event was inside the
     * bounds of the button.
     * @param button The button object that generated the event.
     */
    virtual void buttonClicked(Widget* button);
private:
	/**
	 * The main button (on which all the properties apply).
	 */
	Button* mButton;

	/**
	 * Sets the text of the button.
	 */
	Button* setTextButton;

	/**
	 * The edit box that contains the button text to be set.
	 */
	EditBox* setTextEditBox;

	/**
	 * Gets the text of the button.
	 */
	Button* getTextButton;

	/**
	 * Keeps the current text of the button.
	 */
	Label* getTextLabel;
};

#endif /* BUTTONSETTINGSLAYOUT_H_ */
