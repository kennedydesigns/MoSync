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
 * EditBoxSettingsLayout.h
 *
 *  Created on: Sept 3, 2012
 *      Author: Spiridon Alexandru
 */

#ifndef EDITBOXSETTINGSLAYOUT_H_
#define EDITBOXSETTINGSLAYOUT_H_

#include <maapi.h>
#include <MAUtil/util.h>

// Include all the wrappers.
#include <NativeUI/Widgets.h>

using namespace NativeUI;

class EditBoxSettingsLayout:
	public VerticalLayout,
	public ButtonListener,
	public ListViewListener,
	public EditBoxListener
{
public:
	/**
	 * Constructor.
	 */
	EditBoxSettingsLayout();

	/**
	 * Destructor.
	 */
	~EditBoxSettingsLayout();

	/**
	 * Sets the main button.
	 */
	void setMainEditBox(EditBox* editBox);
private:

	/**
	 * Creates and adds main layout to the screen.
	 */
	void createMainLayout();

	/**
	 * Creates the set edit box text layout.
	 */
	void createSetEditBoxTextLayout();

	/**
	 * Creates the get edit box text layout.
	 */
	void createGetEditBoxTextLayout();

	/**
	 * Creates the set edit box placeholder text layout.
	 */
	void createSetPlaceholderLayout();

    /**
     * This method is called if the touch-up event was inside the
     * bounds of the button.
     * @param button The button object that generated the event.
     */
    virtual void buttonClicked(Widget* button);

    /**
     * This method is called when the user selects an item from
     * the list view
     * @param listView The list view object that generated the event
     * @param listViewItem The ListViewItem object that was clicked.
     */
    virtual void listViewItemClicked(ListView* listView, ListViewItem* listViewItem);

    /**
     * This method is called when an edit box gains focus.
     * The virtual keyboard is shown.
     * Only for iphone platform.
     * @param editBox The edit box object that generated the event.
     */
    virtual void editBoxEditingDidBegin(EditBox* editBox);

    /**
     * This method is called when an edit box loses focus.
     * The virtual keyboard is hidden.
     * Only for iphone platform.
     * @param editBox The edit box object that generated the event.
     */
    virtual void editBoxEditingDidEnd(EditBox* editBox);

    /**
     * This method is called when the edit box text was changed.
     * Only for iphone platform.
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
     * Only for iphone platform.
     * @param editBox The edit box object that generated the event.
     */
    virtual void editBoxReturn(EditBox* editBox);

	/**
	 * Creates the input mode list view
	 * @param mainLayout Widgets will be added to it.
	 */
	void createInputModeListView(ListView* aListView);

	/**
	 * Creates the input flag list view
	 * @param mainLayout Widgets will be added to it.
	 */
	void createInputFlagListView(ListView* aListView);

	/**
	 * Creates a horizontal layout, adds it to the main layout, initializes the
	 * edit box and a label and adds it to the horizontal layout.
	 * @param editBox The editbox to be created and added on the screen.
	 * @param mainLayout Widgets will be added to it.
	 * @param text The text that will fill the label.
	 */
	void createDecimalEditBoxView(EditBox* &editBox, ListView* aListView, MAUtil::String text);

	/**
	 * Set the input mode of the edit box
	 * @param mode The input mode code
	 */
	void setInputMode(int mode);

	/**
	 * Set the input flag of the edit box
	 * @param flag The input flag code
	 */
	void setInputFlag(int flag);
private:
	/**
	 * The list view contains all the edit box properties widgets.
	 */
	ListView* mEditBoxListView;

	/**
	 * The main edit box (on which all the properties apply).
	 */
	EditBox* mEditBox;

	/**
	 * Sets the text of the edit box.
	 */
	Button* setTextButton;

	/**
	 * The edit box that contains the edit box text to be set.
	 */
	EditBox* setTextEditBox;

	/**
	 * Gets the text of the edit box.
	 */
	Button* getTextButton;

	/**
	 * Keeps the current text of the edit box.
	 */
	Label* getTextLabel;

	/**
	 * Sets the placeholder text of the button.edit box
	 */
	Button* setPlaceholderButton;

	/**
	 * The edit box that contains the edit box placeholder text to be set.
	 */
	EditBox* setPlaceholderEditBox;

	Button* mKeyboardButton;

	/**
	 * The max input text length for mEditBox.
	 */
	EditBox* mMaxTextLengthEditBox;
	EditBox* mPasswordEditBox;

	ListView* mInputModeListView;
	ListView* mInputFlagListView;

	/**
	 * The maximum number of lines for mEditBox
	 */
	EditBox* mMaxLinesEditBox;
	Label* mMaxLinesLabel;

	/**
	 * The minimum number of lines for mEditBox
	 */
	EditBox* mMinLinesEditBox;
	Label* mMinLinesLabel;

	/**
	 * The placeholder color for mEditBox
	 */
	EditBox* mPlaceholderColorEditBox;
	Label* mPlaceholderColorLabel;

	/**
	 * The lines number for mEditBox
	 */
	EditBox* mLinesNumberEditBox;
	Label *mLinesNumberLabel;

	bool mKeyboard;

	Label* mGetTextLabel;
};

#endif /* EDITBOXSETTINGSLAYOUT_H_ */
