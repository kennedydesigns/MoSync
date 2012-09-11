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
 * EditBoxEventsLayout.h
 *
 *  Created on: Sept 3, 2012
 *      Author: Spiridon Alexandru
 */

#ifndef EDITBOXEVENTSLAYOUT_H_
#define EDITBOXEVENTSLAYOUT_H_

#include <maapi.h>
#include <MAUtil/util.h>

// Include all the wrappers.
#include <NativeUI/Widgets.h>

using namespace NativeUI;

class EditBoxEventsLayout:
	public VerticalLayout,
	public EditBoxListener
{
public:
	/**
	 * Constructor.
	 */
	EditBoxEventsLayout();

	/**
	 * Destructor.
	 */
	~EditBoxEventsLayout();

	/**
	 * Gets the main test button.
	 */
	EditBox* getMainEditBox();
private:

	/**
	 * Creates and adds main layout to the screen.
	 */
	void createMainLayout();

    /**
      * This method is called when an edit box gains focus.
      * The virtual keyboard is shown.
      * Platform: Android and iOS.
      * @param editBox The edit box object that generated the event.
      */
     virtual void editBoxEditingDidBegin(EditBox* editBox);

     /**
      * This method is called when an edit box loses focus.
      * The virtual keyboard is hidden.
      * Platform: Android and iOS.
      * @param editBox The edit box object that generated the event.
      */
     virtual void editBoxEditingDidEnd(EditBox* editBox);

     /**
      * This method is called when the edit box text was changed.
      * @param editBox The edit box object that generated the event.
      * @param text The new text.
      */
     virtual void editBoxTextChanged(
         EditBox* editBox,
         const MAUtil::String& text);

     /**
      * This method is called when the return button was pressed.
      * On iphone platform the virtual keyboard is not hidden after
      * receiving this event.
      * @param editBox The edit box object that generated the event.
      */
     virtual void editBoxReturn(EditBox* editBox);
private:
	/**
	 * The main EditBox.
	 */
	EditBox* mEditBox;

	Label* mEditBoxEditingBeginLabel;
	Label* mEditBoxEditingEndLabel;
	Label* mEditBoxTextChangedLabel;
	Label* mEditBoxReturnLabel;
};

#endif /* EDITBOXEVENTSLAYOUT_H_ */
