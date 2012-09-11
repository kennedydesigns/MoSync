/*
 * WidgetListScreen.cpp
 *
 *  Created on: Sep 5, 2012
 *      Author: spiri
 */

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
 * MainScreen.cpp
 *
 *  Created on: Aug 7, 2012
 *      Author: Spiridon Alexandru
 */
#include <conprint.h>
#include <wchar.h>
#include <ma.h>
#include <maassert.h>
#include <mawstring.h>
#include <mastdlib.h>

#include "WidgetListScreen.h"
#include "WidgetListScreenListener.h"
#include "ButtonLayouts/ButtonEventsLayout.h"
#include "ButtonLayouts/ButtonSettingsLayout.h"

/**
 * Constructor.
 */
WidgetListScreen::WidgetListScreen(MAUtil::Vector<MAUtil::String> widgets):
	Screen(),
	mMainLayout(NULL),
	mWidgetListView(NULL)
{
	mWidgetList = widgets;

	createMainScreen();

	mWidgetListView->addListViewListener(this);
}

/**
 * Creates and adds main layout to the screen.
 */
void WidgetListScreen::createMainScreen()
{
	// create the main vertical layout and set it as the main screen widget
	mMainLayout = new VerticalLayout();
	this->setMainWidget(mMainLayout);

	createWidgetListView();
}

/**
 * Creates the main widget list view
 */
void WidgetListScreen::createWidgetListView()
{
	mWidgetListView = new ListView();

	for (int i = 0; i < mWidgetList.size(); i++)
	{
		ListViewItem* listViewItem = new ListViewItem();
		listViewItem->setText(mWidgetList[i]);
		listViewItem->setFontSize(24);
		mWidgetListView->addChild(listViewItem);
	}

	mMainLayout->addChild(mWidgetListView);
}

/**
 * Sets a certain list item into the selected mode.
 */
void WidgetListScreen::setSelected(int index)
{
	// TODO SA: select the item at index index
}

/**
 * This method is called when a list view item is clicked.
 * @param listView The list view object that generated the event.
 * @param listViewItem The ListViewItem object that was clicked.
 */
void WidgetListScreen::listViewItemClicked(
    ListView* listView,
    ListViewItem* listViewItem)
{

}

/**
 * This method is called when a list view item is clicked.
 * @param listView The list view object that generated the event.
 * @param index The index on which the list view item is positioned.
 */
void WidgetListScreen::listViewItemClicked(
    ListView* listView,
    int index)
{
	if (listView == mWidgetListView)
	{
		// we announce all the listeners
		for (int i = 0; i < mWidgetListScreenListeners.size(); i++)
		{
			mWidgetListScreenListeners[i]->widgetListScreenItemClicked(index);
		}
	}
}

/**
 * Add a widget list screen event listener.
 * @param listener The listener that will receive widget list screen events.
 */
void WidgetListScreen::addWidgetListScreenListener(WidgetListScreenListener* listener)
{
    for (int i = 0; i < mWidgetListScreenListeners.size(); i++)
    {
        if (listener == mWidgetListScreenListeners[i])
        {
            return;
        }
    }

    mWidgetListScreenListeners.add(listener);
}

/**
 * Remove the widget list screen listener.
 * @param listener The listener that receives widget list screen events.
 */
void WidgetListScreen::removeWidgetListScreenListener(WidgetListScreenListener* listener)
{
    for (int i = 0; i < mWidgetListScreenListeners.size(); i++)
    {
        if (listener == mWidgetListScreenListeners[i])
        {
			mWidgetListScreenListeners.remove(i);
            break;
        }
    }
}

/**
 * Destructor.
 */
WidgetListScreen::~WidgetListScreen()
{
	mWidgetListView->removeListViewListener(this);
	mWidgetListScreenListeners.clear();
}