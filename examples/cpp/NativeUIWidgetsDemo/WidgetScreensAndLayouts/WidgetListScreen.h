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
 * WidgetListScreen.h
 *
 *  Created on: Aug 7, 2012
 *      Author: Spiridon Alexandru
 */
#ifndef WIDGETLISTSCREEN_H_
#define WIDGETLISTSCREEN_H_

#include <maapi.h>
#include <MAUtil/util.h>

// Include all the wrappers.
#include <NativeUI/Widgets.h>
#include "../MainScreen.h"

using namespace NativeUI;

class WidgetListScreenListener;

class WidgetListScreen:
	public Screen,
	public ListViewListener
{

public:
	/**
	 * Constructor.
	 */
	WidgetListScreen(MAUtil::Vector<MAUtil::String> widgets);

	/**
	 * Destructor.
	 */
	~WidgetListScreen();

	/**
	 * Add a widget list screen event listener.
	 * @param listener The listener that will receive widget list screen events.
	 */
	virtual void addWidgetListScreenListener(WidgetListScreenListener* listener);

	/**
	 * Remove the widget list screen listener.
	 * @param listener The listener that receives widget list screen events.
	 */
	virtual void removeWidgetListScreenListener(WidgetListScreenListener* listener);

	/**
	 * Sets a certain list item into the selected mode.
	 */
	void setSelected(int index);
private:
	/**
	 * Creates and adds main layout to the screen.
	 */
	void createMainScreen();

	/**
	 * Creates the main widget list view
	 */
	void createWidgetListView();

    /**
     * This method is called when a list view item is clicked.
     * @param listView The list view object that generated the event.
     * @param listViewItem The ListViewItem object that was clicked.
     */
    virtual void listViewItemClicked(
        ListView* listView,
        ListViewItem* listViewItem);

    /**
     * This method is called when a list view item is clicked.
     * @param listView The list view object that generated the event.
     * @param index The index on which the list view item is positioned.
     */
    virtual void listViewItemClicked(
        ListView* listView,
        int index);
private:
	/**
	 * Main layout.
	 */
	VerticalLayout* mMainLayout;

	/**
	 * The main application tab screen.
	 */
	MainScreen* mMainScreen;

	/**
	 * The list view contains all the widges available for NativeUI
	 */
	ListView* mWidgetListView;

	/**
	 * Array with widget list screen listeners.
	 */
	MAUtil::Vector<WidgetListScreenListener*> mWidgetListScreenListeners;

	/**
	 * The vector conaining all the widgets inside main list view.
	 */
	MAUtil::Vector<MAUtil::String> mWidgetList;
};

#endif /* WIDGETLISTSCREEN_H_ */
