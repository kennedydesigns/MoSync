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
 * MainScreen.h
 *
 *  Created on: Aug 7, 2012
 *      Author: Spiridon Alexandru
 */
#ifndef MAINSCREEN_H_
#define MAINSCREEN_H_

#include <maapi.h>
#include <MAUtil/util.h>

// Include all the wrappers.
#include <NativeUI/Widgets.h>
#include "WidgetScreensAndLayouts/WidgetListScreenListener.h"

using namespace NativeUI;

class WidgetListScreen;
class WidgetEventsScreen;
class WidgetSettingsScreen;

class MainScreen:
	public TabScreen,
	public TabScreenListener,
	public WidgetListScreenListener
{

public:
	/**
	 * Constructor.
	 */
	MainScreen();

	/**
	 * Destructor.
	 */
	~MainScreen();

	/**
	 * Sets the current visible events screen.
	 */
	void setEventsScreen(Screen* eventsScreen);

	/**
	 * Sets the current visible settings screen.
	 */
	void setSettingsScreen(Screen* settingsScreen);
private:
	/**
	 * Creates and adds main layout to the screen.
	 */
	void createMainScreen();

	/**
	 * Populates the widget vector.
	 */
	void populateWidgetVector();

    /**
     * This method is called when a tab screen has changed to a new tab.
     * @param tabScreen The tab screen object that generated the event.
     * @param tabScreenIndex The index of the new tab.
     */
    virtual void tabScreenTabChanged(
        TabScreen* tabScreen,
        const int tabScreenIndex);

	/**
	 * This method is called when a widget list item is clicked.
	 * @param index The index of the clicked widget.
	 */
	virtual void widgetListScreenItemClicked(int index);
private:
	/**
	 * The first screen from the tab screen contains the widget list.
	 */
	WidgetListScreen* mWidgetListScreen;

	/**
	 * The screen that contains the current widget selected from the list.
	 */
	WidgetEventsScreen* mWidgetEventsScreen;

	/**
	 * The screen that contains the current widget settings.
	 */
	WidgetSettingsScreen* mWidgetSettingsScreen;

	/**
	 * The vector conaining all the widgets inside the widget list screen.
	 */
	MAUtil::Vector<MAUtil::String> mWidgetList;
};

#endif /* MAINSCREEN_H_ */
