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

#include "MainScreen.h"
#include "WidgetScreensAndLayouts/WidgetListScreen.h"
#include "WidgetScreensAndLayouts/WidgetEventsScreen.h"
#include "WidgetScreensAndLayouts/WidgetSettingsScreen.h"

#include "WidgetScreensAndLayouts/ButtonLayouts/ButtonEventsLayout.h"
#include "WidgetScreensAndLayouts/ButtonLayouts/ButtonSettingsLayout.h"
#include "WidgetScreensAndLayouts/EditBoxLayouts/EditBoxEventsLayout.h"
#include "WidgetScreensAndLayouts/EditBoxLayouts/EditBoxSettingsLayout.h"

/**
 * Constructor.
 */
MainScreen::MainScreen() :
	TabScreen(),
	mWidgetListScreen(NULL),
	mWidgetEventsScreen(NULL),
	mWidgetSettingsScreen(NULL)
{
	createMainScreen();

	mWidgetListScreen->addWidgetListScreenListener(this);
}

/**
 * Creates and adds main layout to the screen.
 */
void MainScreen::createMainScreen()
{
	populateWidgetVector();

	mWidgetListScreen = new WidgetListScreen(mWidgetList);
	mWidgetListScreen->setTitle("Widget list");
	this->addTab(mWidgetListScreen);

	mWidgetEventsScreen = new WidgetEventsScreen();
	mWidgetEventsScreen->setTitle("Button events");
	ButtonEventsLayout* buttonEventsLayout = new ButtonEventsLayout();
	mWidgetEventsScreen->setMainWidget(buttonEventsLayout);
	this->addTab(mWidgetEventsScreen);

	mWidgetSettingsScreen = new WidgetSettingsScreen();
	mWidgetSettingsScreen->setTitle("Button props");
	ButtonSettingsLayout* buttonSettingsLayout = new ButtonSettingsLayout();
	buttonSettingsLayout->setMainButton(buttonEventsLayout->getMainButton());
	mWidgetSettingsScreen->setMainWidget(buttonSettingsLayout);
	this->addTab(mWidgetSettingsScreen);

	this->addTabScreenListener(this);
	this->setActiveTab(0);
}

/**
 * Populates the widget vector.
 */
void MainScreen::populateWidgetVector()
{
	mWidgetList.add("Button");
	mWidgetList.add("EditBox");
}

/**
 * Sets the current visible events screen.
 */
void MainScreen::setEventsScreen(Screen* eventsScreen)
{
	if (mWidgetEventsScreen == NULL)
	{
		this->addTab(eventsScreen);
	}
	mWidgetEventsScreen->setMainWidget(eventsScreen->getChild(0));
}

/**
 * Sets the current visible settings screen.
 */
void MainScreen::setSettingsScreen(Screen* settingsScreen)
{
	if (mWidgetSettingsScreen == NULL)
	{
		this->addTab(settingsScreen);
	}
	mWidgetSettingsScreen->setMainWidget(settingsScreen->getChild(0));
}

/**
 * This method is called when a tab screen has changed to a new tab.
 * @param tabScreen The tab screen object that generated the event.
 * @param tabScreenIndex The index of the new tab.
 */
void MainScreen::tabScreenTabChanged(
    TabScreen* tabScreen,
    const int tabScreenIndex)
{
    if (tabScreen == this)
    {
        printf("tab changed : %d", tabScreenIndex);
        printf("getActiveTabIndex() = %d", this->getActiveTabIndex());
    }
}

/**
 * This method is called when a widget list item is clicked.
 * @param index The index of the clicked widget.
 */
void MainScreen::widgetListScreenItemClicked(int index)
{
	switch (index)
	{
		case 0:
			mWidgetEventsScreen->setTitle("Button events");
			ButtonEventsLayout* buttonEventsLayout = new ButtonEventsLayout();
			mWidgetEventsScreen->setMainWidget(buttonEventsLayout);

			mWidgetSettingsScreen->setTitle("Button props");
			ButtonSettingsLayout* buttonSettingsLayout = new ButtonSettingsLayout();
			buttonSettingsLayout->setMainButton(buttonEventsLayout->getMainButton());
			mWidgetSettingsScreen->setMainWidget(buttonSettingsLayout);
			break;
		case 1:
			EditBoxEventsLayout* editBoxEventsLayout = new EditBoxEventsLayout();
			mWidgetEventsScreen->setTitle("EditBox events");
			mWidgetEventsScreen->setMainWidget(editBoxEventsLayout);

			mWidgetSettingsScreen->setTitle("EditBox props");
			EditBoxSettingsLayout* editBoxSettingsLayout = new EditBoxSettingsLayout();
			editBoxSettingsLayout->setMainEditBox(editBoxEventsLayout->getMainEditBox());
			mWidgetSettingsScreen->setMainWidget(editBoxSettingsLayout);
			break;
		default:
			break;
	};
}

/**
 * Destructor.
 */
MainScreen::~MainScreen()
{
	mWidgetListScreen->removeWidgetListScreenListener(this);
	mWidgetList.clear();
}