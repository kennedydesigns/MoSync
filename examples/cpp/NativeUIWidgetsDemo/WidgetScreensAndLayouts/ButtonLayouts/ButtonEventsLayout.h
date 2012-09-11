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
 * ButtonEventsLayout.h
 *
 *  Created on: Sept 3, 2012
 *      Author: Spiridon Alexandru
 */

#ifndef BUTTONEVENTSLAYOUT_H_
#define BUTTONEVENTSLAYOUT_H_

#include <maapi.h>
#include <MAUtil/util.h>

// Include all the wrappers.
#include <NativeUI/Widgets.h>

using namespace NativeUI;

class ButtonEventsLayout:
	public VerticalLayout,
	public ButtonListener
{
public:
	/**
	 * Constructor.
	 */
	ButtonEventsLayout();

	/**
	 * Destructor.
	 */
	~ButtonEventsLayout();

	/**
	 * Gets the main test button.
	 */
	Button* getMainButton();
private:

	/**
	 * Creates and adds main layout to the screen.
	 */
	void createMainLayout();

    /**
     * This method is called when there is an touch-down event for
     * a button.
     * Platform: iOS and Android.
     * @param button The button object that generated the event.
     */
    virtual void buttonPressed(Widget* button);

    /**
     * This method is called when there is an touch-up event for
     * a button.
     * Platform: iOS and Android.
     * @param button The button object that generated the event.
     */
    virtual void buttonReleased(Widget* button);

    /**
     * This method is called if the touch-up event was inside the
     * bounds of the button.
     * Platform: iOS, Android, Windows Phone.
     * @param button The button object that generated the event.
     */
    virtual void buttonClicked(Widget* button);
private:
	/**
	 * The main button.
	 */
	Button* mButton;

	Label* mButtonPressedLabel;
	Label* mButtonReleasedLabel;
	Label* mButtonClickedLabel;
};

#endif /* BUTTONEVENTSLAYOUT_H_ */
