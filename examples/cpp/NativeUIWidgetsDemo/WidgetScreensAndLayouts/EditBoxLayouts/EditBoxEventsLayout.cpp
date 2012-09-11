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
 * EditBoxEventsLayout.cpp
 *
 *  Created on: Sept 3, 2012
 *      Author: Spiridon Alexandru
 */

#include "EditBoxEventsLayout.h"

#define TITLE_LABEL_HEIGHT 100
#define TITLE_LABEL_FONT_SIZE 24

/**
 * Constructor.
 */
EditBoxEventsLayout::EditBoxEventsLayout():
	VerticalLayout(),
	mEditBox(NULL),
	mEditBoxEditingBeginLabel(NULL),
	mEditBoxEditingEndLabel(NULL),
	mEditBoxTextChangedLabel(NULL),
	mEditBoxReturnLabel(NULL)
{
	createMainLayout();

	mEditBox->addEditBoxListener(this);
}

/**
 * Destructor.
 */
EditBoxEventsLayout::~EditBoxEventsLayout()
{
	mEditBox->removeEditBoxListener(this);
}

/**
 * Creates and adds main layout to the screen.
 */
void EditBoxEventsLayout::createMainLayout()
{
	mEditBox = new EditBox();
	mEditBox->setPlaceholder("Test edit box");
	mEditBox->fillSpaceHorizontally();

	this->addChild(mEditBox);

	Label* eventsLabel = new Label();
	eventsLabel->setText("Edit box events");
	eventsLabel->setFontSize(TITLE_LABEL_FONT_SIZE);
	eventsLabel->setHeight(TITLE_LABEL_HEIGHT);
	this->addChild(eventsLabel);

	mEditBoxEditingBeginLabel = new Label();
	mEditBoxEditingBeginLabel->setText("Edit box editing not started");
	this->addChild(mEditBoxEditingBeginLabel);

	mEditBoxEditingEndLabel = new Label();
	mEditBoxEditingEndLabel->setText("Edit box editing not started");
	this->addChild(mEditBoxEditingEndLabel);

	mEditBoxTextChangedLabel = new Label();
	mEditBoxTextChangedLabel->setText("Edit box text didn't change");
	this->addChild(mEditBoxTextChangedLabel);

	mEditBoxReturnLabel = new Label();
	mEditBoxReturnLabel->setText("The way of no return");
	this->addChild(mEditBoxReturnLabel);
}

/**
 * Gets the main test EditBox.
 */
EditBox* EditBoxEventsLayout::getMainEditBox()
{
	return mEditBox;
}

/**
  * This method is called when an edit box gains focus.
  * The virtual keyboard is shown.
  * Platform: Android and iOS.
  * @param editBox The edit box object that generated the event.
  */
void EditBoxEventsLayout::editBoxEditingDidBegin(EditBox* editBox)
{
	mEditBoxEditingBeginLabel->setText("Edit box editing started");
	mEditBoxEditingEndLabel->setText("");
}

 /**
  * This method is called when an edit box loses focus.
  * The virtual keyboard is hidden.
  * Platform: Android and iOS.
  * @param editBox The edit box object that generated the event.
  */
void EditBoxEventsLayout::editBoxEditingDidEnd(EditBox* editBox)
{
	mEditBoxEditingEndLabel->setText("Edit box editing ended");
	mEditBoxEditingBeginLabel->setText("Edit box editing not started");
}

 /**
  * This method is called when the edit box text was changed.
  * @param editBox The edit box object that generated the event.
  * @param text The new text.
  */
void EditBoxEventsLayout::editBoxTextChanged(
     EditBox* editBox,
     const MAUtil::String& text)
{
	mEditBoxTextChangedLabel->setText("Edit box text changed");
}

 /**
  * This method is called when the return button was pressed.
  * On iphone platform the virtual keyboard is not hidden after
  * receiving this event.
  * @param editBox The edit box object that generated the event.
  */
void EditBoxEventsLayout::editBoxReturn(EditBox* editBox)
{
	mEditBoxReturnLabel->setText("The return of the edit box!");
}