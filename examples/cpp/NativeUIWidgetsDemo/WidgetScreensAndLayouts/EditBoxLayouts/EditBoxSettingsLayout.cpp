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
 * EditBoxSettingsLayout.cpp
 *
 *  Created on: Sept 3, 2012
 *      Author: Spiridon Alexandru
 */

#include "EditBoxSettingsLayout.h"

#define PROPERTY_LINE_HEIGHT 80
#define MAX_TEXT_LENGTH_LABEL_TEXT "Max text length"
#define MAX_LINES_LABEL_TEXT "Max lines"
#define MIN_LINES_LABEL_TEXT "Min lines"
#define PLACEHOLDER_COLOR_LABEL_TEXT "Placeholder color"
#define LINES_NUMBER_LABEL_TEXT "Lines number"
#define INPUT_MODES_COUNT 7
#define INPUT_FLAGS_COUNT 5

using namespace MAUtil;

const String inputModes[] = {
		"ANY",
		"EMAILADDR",
		"NUMERIC",
		"PHONENUMBER",
		"URL",
		"DECIMAL",
		"SINGLELINE"
};

const String inputFlags[] = {
		"FLAG_PASSWORD",
		"FLAG_SENSITIVE",
		"FLAG_INITIAL_CAPS_ALL_CHARACTERS",
		"FLAG_INITIAL_CAPS_WORD",
		"FLAG_INITIAL_CAPS_SENTENCE"
};

enum InputModeType {
	ANY,
	EMAILADDR,
	NUMERIC,
	PHONENUMBER,
	URL,
	DECIMAL,
	SINGLELINE
};

enum InputFlagType {
	PASSWORD,
	SENSITIVE,
	CAPS_ALL_CHARACTERS,
	CAPS_WORD,
	CAPS_SENTENCE
};

/**
 * Constructor.
 */
EditBoxSettingsLayout::EditBoxSettingsLayout():
	VerticalLayout(),
	mEditBoxListView(NULL),
	mEditBox(NULL),
	setTextButton(NULL),
	setTextEditBox(NULL),
	getTextButton(NULL),
	getTextLabel(NULL),
	setPlaceholderButton(NULL),
	setPlaceholderEditBox(NULL),
	mKeyboardButton(NULL),
	mMaxTextLengthEditBox(NULL),
	mInputFlagListView(NULL),
	mInputModeListView(NULL),
	mMaxLinesEditBox(NULL),
	mMaxLinesLabel(NULL),
	mMinLinesEditBox(NULL),
	mMinLinesLabel(NULL),
	mPlaceholderColorEditBox(NULL),
	mPlaceholderColorLabel(NULL),
	mLinesNumberEditBox(NULL),
	mLinesNumberLabel(NULL),
	mKeyboard(false),
	mGetTextLabel(NULL)
{
	createMainLayout();

	setTextButton->addButtonListener(this);
	getTextButton->addButtonListener(this);
	setPlaceholderButton->addButtonListener(this);
	mKeyboardButton->addButtonListener(this);
	mMaxTextLengthEditBox->addEditBoxListener(this);
	mInputModeListView->addListViewListener(this);
	mInputFlagListView->addListViewListener(this);
	mMaxLinesEditBox->addEditBoxListener(this);
	mMinLinesEditBox->addEditBoxListener(this);
	mPlaceholderColorEditBox->addEditBoxListener(this);
	mLinesNumberEditBox->addEditBoxListener(this);
}

/**
 * Destructor.
 */
EditBoxSettingsLayout::~EditBoxSettingsLayout()
{
	setTextButton->removeButtonListener(this);
	getTextButton->removeButtonListener(this);
	setPlaceholderButton->removeButtonListener(this);
	mKeyboardButton->removeButtonListener(this);
	mMaxTextLengthEditBox->removeEditBoxListener(this);
	mInputModeListView->removeListViewListener(this);
	mInputFlagListView->removeListViewListener(this);
	mMaxLinesEditBox->removeEditBoxListener(this);
	mMinLinesEditBox->removeEditBoxListener(this);
	mPlaceholderColorEditBox->removeEditBoxListener(this);
	mLinesNumberEditBox->removeEditBoxListener(this);
}

/**
 * Creates and adds main layout to the screen.
 */
void EditBoxSettingsLayout::createMainLayout()
{
	mEditBoxListView = new ListView();
	this->addChild(mEditBoxListView);

	createSetEditBoxTextLayout();
	createGetEditBoxTextLayout();
	createSetPlaceholderLayout();

	mGetTextLabel = new Label();
	mEditBoxListView->addChild(mGetTextLabel);

	// create and add the show/hide keyboard button
	mKeyboardButton = new Button();
	mKeyboardButton->setText("Show/hide keyboard");
	mKeyboardButton->setHeight(PROPERTY_LINE_HEIGHT);
	mKeyboardButton->fillSpaceHorizontally();
	mEditBoxListView->addChild(mKeyboardButton);

	// Create layout for widgets.
	createDecimalEditBoxView(mMaxTextLengthEditBox, mEditBoxListView, MAX_TEXT_LENGTH_LABEL_TEXT);
	createDecimalEditBoxView(mMaxLinesEditBox, mEditBoxListView, MAX_LINES_LABEL_TEXT);
	createDecimalEditBoxView(mMinLinesEditBox, mEditBoxListView, MIN_LINES_LABEL_TEXT);
	createDecimalEditBoxView(mLinesNumberEditBox, mEditBoxListView, LINES_NUMBER_LABEL_TEXT);
	createDecimalEditBoxView(mPlaceholderColorEditBox, mEditBoxListView, PLACEHOLDER_COLOR_LABEL_TEXT);

	createInputModeListView(mEditBoxListView);

	// create a black separator between the lists
	HorizontalLayout* separatorLayout = new HorizontalLayout();
	separatorLayout->setBackgroundColor(0x000000);
	separatorLayout->setHeight(PROPERTY_LINE_HEIGHT);
	mEditBoxListView->addChild(separatorLayout);

	createInputFlagListView(mEditBoxListView);
}

/**
 * Creates the set button text layout.
 */
void EditBoxSettingsLayout::createSetEditBoxTextLayout()
{
	HorizontalLayout* setTextHorizontalLayout = new HorizontalLayout();
	setTextHorizontalLayout->setHeight(PROPERTY_LINE_HEIGHT);
	setTextButton = new Button();
	setTextButton->setText("Set edit box text:");
	setTextButton->fillSpaceHorizontally();
	setTextHorizontalLayout->addChild(setTextButton);

	setTextEditBox = new EditBox();
	setTextEditBox->setPlaceholder("Edit box text");
	setTextEditBox->fillSpaceHorizontally();
	setTextHorizontalLayout->addChild(setTextEditBox);

	mEditBoxListView->addChild(setTextHorizontalLayout);
}

/**
 * Creates the get button text layout.
 */
void EditBoxSettingsLayout::createGetEditBoxTextLayout()
{
	HorizontalLayout* getTextHorizontalLayout = new HorizontalLayout();
	getTextHorizontalLayout->setHeight(PROPERTY_LINE_HEIGHT);
	getTextButton = new Button();
	getTextButton->setText("Get edit box text:");
	getTextButton->fillSpaceHorizontally();
	getTextHorizontalLayout->addChild(getTextButton);

	getTextLabel = new Label();
	getTextLabel->setText("No text yet");
	getTextLabel->fillSpaceHorizontally();
	getTextHorizontalLayout->addChild(getTextLabel);

	mEditBoxListView->addChild(getTextHorizontalLayout);
}

/**
 * Creates the set edit box placeholder text layout.
 */
void EditBoxSettingsLayout::createSetPlaceholderLayout()
{
	HorizontalLayout* getPlaceholderHorizontalLayout = new HorizontalLayout();
	getPlaceholderHorizontalLayout->setHeight(PROPERTY_LINE_HEIGHT);
	setPlaceholderButton = new Button();
	setPlaceholderButton->setText("Set placeholder text:");
	setPlaceholderButton->fillSpaceHorizontally();
	getPlaceholderHorizontalLayout->addChild(setPlaceholderButton);

	setPlaceholderEditBox = new EditBox();
	setPlaceholderEditBox->setPlaceholder("Edit box placeholder");
	setPlaceholderEditBox->fillSpaceHorizontally();
	getPlaceholderHorizontalLayout->addChild(setPlaceholderEditBox);

	mEditBoxListView->addChild(getPlaceholderHorizontalLayout);
}

/**
 * Creates a horizontal layout, adds it to the main layout, initializes the
 * edit box and adds it to the horizontal layout.
 * @param editBox The editbox to be created and added on the screen.
 * @param mainLayout Widgets will be added to it.
 */
void EditBoxSettingsLayout::createDecimalEditBoxView(EditBox* &editBox, ListView* aListView, String text)
{
	// Create layout for widgets.
	HorizontalLayout* layout = new HorizontalLayout();
	layout->setHeight(PROPERTY_LINE_HEIGHT);

	aListView->addChild(layout);

	// Add label with info.
	Label* label = new Label();
	label->setText(text);
	layout->addChild(label);

	// Create the edit box.
	editBox = new EditBox();
	editBox->setInputMode(EDIT_BOX_INPUT_MODE_DECIMAL);
	editBox->fillSpaceHorizontally();
	layout->addChild(editBox);
}

/**
 * Creates the input mode list view
 * @param mainLayout Widgets will be added to it.
 */
void EditBoxSettingsLayout::createInputModeListView(ListView* aListView)
{
	mInputModeListView = new ListView();
	mInputModeListView->setHeight(PROPERTY_LINE_HEIGHT * 4);
	mInputModeListView->setBackgroundColor(0xFFFFFF);

	for(int i = 0; i < INPUT_MODES_COUNT; i++)
	{
		ListViewItem* inputModeItem = new ListViewItem();
		inputModeItem->setText(inputModes[i]);
		inputModeItem->setBackgroundColor(0xFFFFFF);
		inputModeItem->setFontColor(0x000000);
		inputModeItem->fillSpaceHorizontally();
		mInputModeListView->addChild(inputModeItem);
	}

	mInputModeListView->fillSpaceHorizontally();
	aListView->addChild(mInputModeListView);
}

/**
 * Creates the input flag list view
 * @param mainLayout Widgets will be added to it.
 */
void EditBoxSettingsLayout::createInputFlagListView(ListView* aListView)
{
	mInputFlagListView = new ListView();
	mInputFlagListView->setHeight(PROPERTY_LINE_HEIGHT * 4);
	mInputFlagListView->setBackgroundColor(0xFFFFFF);

	for(int i = 0; i < INPUT_FLAGS_COUNT; i++)
	{
		ListViewItem* inputFlagItem = new ListViewItem();
		inputFlagItem->setText(inputFlags[i]);
		inputFlagItem->setBackgroundColor(0xFFFFFF);
		inputFlagItem->setFontColor(0x000000);
		inputFlagItem->fillSpaceHorizontally();
		mInputFlagListView->addChild(inputFlagItem);
	}

	mInputFlagListView->fillSpaceHorizontally();
	aListView->addChild(mInputFlagListView);
}

/**
 * Set the input mode of the edit box
 * @param mode The input mode code
 */
void EditBoxSettingsLayout::setInputMode(int mode)
{
	mEditBox->setText("");
	switch(mode)
	{
		case ANY:
			mGetTextLabel->setText("ANY");
			mEditBox->setInputMode(EDIT_BOX_INPUT_MODE_ANY);
			break;
		case EMAILADDR:
			mGetTextLabel->setText("EMAIL");
			mEditBox->setInputMode(EDIT_BOX_INPUT_MODE_EMAILADDR);
			break;
		case NUMERIC:
			mGetTextLabel->setText("NUMERIC");
			mEditBox->setInputMode(EDIT_BOX_INPUT_MODE_NUMERIC);
			break;
		case PHONENUMBER:
			mGetTextLabel->setText("PHONENUMBER");
			mEditBox->setInputMode(EDIT_BOX_INPUT_MODE_PHONENUMBER);
			break;
		case URL:
			mGetTextLabel->setText("URL");
			mEditBox->setInputMode(EDIT_BOX_INPUT_MODE_URL);
			break;
		case DECIMAL:
			mGetTextLabel->setText("DECIMAL");
			mEditBox->setInputMode(EDIT_BOX_INPUT_MODE_DECIMAL);
			break;
		case SINGLELINE:
			mGetTextLabel->setText("SINGLELINE");
			mEditBox->setInputMode(EDIT_BOX_INPUT_MODE_SINGLE_LINE);
			break;
		default:
			mGetTextLabel->setText("Not a valid mode selection");
			break;
	}
}

/**
 * Set the input flag of the edit box
 * @param flag The input flag code
 */
void EditBoxSettingsLayout::setInputFlag(int flag)
{
	mEditBox->setText("");
	switch(flag)
	{
		case PASSWORD:
			mGetTextLabel->setText("PASSWORD");
			mEditBox->setInputFlag(EDIT_BOX_INPUT_FLAG_PASSWORD);
			break;
		case SENSITIVE:
			mGetTextLabel->setText("SENSITIVE");
			mEditBox->setInputFlag(EDIT_BOX_INPUT_FLAG_SENSITIVE);
			break;
		case CAPS_ALL_CHARACTERS:
			mGetTextLabel->setText("CAPS_ALL_CHARACTERS");
			mEditBox->setInputFlag(EDIT_BOX_INPUT_GLAG_INITIAL_CAPS_ALL_CHARACTERS);
			break;
		case CAPS_WORD:
			mGetTextLabel->setText("CAPS_WORD");
			mEditBox->setInputFlag(EDIT_BOX_INPUT_FLAG_INITIAL_CAPS_WORD);
			break;
		case CAPS_SENTENCE:
			mGetTextLabel->setText("CAPS_SENTENCE");
			mEditBox->setInputFlag(EDIT_BOX_INPUT_FLAG_INITIAL_CAPS_SENTENCE);
			break;
		default:
			mGetTextLabel->setText("Not a valid flag selection!");
			break;
	}
}


/**
 * Sets the main button.
 */
void EditBoxSettingsLayout::setMainEditBox(EditBox* editBox)
{
	mEditBox = editBox;
}

/**
 * This method is called if the touch-up event was inside the
 * bounds of the button.
 * @param button The button object that generated the event.
 */
void EditBoxSettingsLayout::buttonClicked(Widget* button)
{
	if (button == setTextButton)
	{
		mEditBox->setText(setTextEditBox->getText());
	}
	else if (button == getTextButton)
	{
		getTextLabel->setText(mEditBox->getText());
	}
	else if (button == setPlaceholderButton)
	{
		mEditBox->setPlaceholder(setPlaceholderEditBox->getText());
	}
}

/**
 * This method is called when the user selects an item from
 * the list view
 * @param listView The list view object that generated the event
 * @param listViewItem The ListViewItem object that was clicked.
 */
void EditBoxSettingsLayout::listViewItemClicked(ListView* listView, ListViewItem* listViewItem)
{
	int listViewItemIndex = -1;
	for(int i = 0; i < listView->countChildWidgets(); i++)
	{
		ListViewItem* currentItem = (ListViewItem*)listView->getChild(i);
		currentItem->setBackgroundColor(0xFFFFFF);

		if (currentItem == listViewItem)
		{
			listViewItemIndex = i;
		}
	}

	if (listView == mInputModeListView)
	{
		listViewItem->setBackgroundColor(0xFF0000);

		if (listViewItemIndex >= 0)
		{
			this->setInputMode(listViewItemIndex);
		}
	}
	else if (listView == mInputFlagListView)
	{
		listViewItem->setBackgroundColor(0xFF0000);

		if (listViewItemIndex >= 0)
		{
			this->setInputFlag(listViewItemIndex);
		}
	}
}

/**
 * This method is called when an edit box gains focus.
 * The virtual keyboard is shown.
 * Only for iphone platform.
 * @param editBox The edit box object that generated the event.
 */
void EditBoxSettingsLayout::editBoxEditingDidBegin(EditBox* editBox)
{
	// do nothing
}

/**
 * This method is called when an edit box loses focus.
 * The virtual keyboard is hidden.
 * Only for iphone platform.
 * @param editBox The edit box object that generated the event.
 */
void EditBoxSettingsLayout::editBoxEditingDidEnd(EditBox* editBox)
{
	// do nothing
}

/**
 * This method is called when the edit box text was changed.
 * Only for iphone platform.
 * @param editBox The edit box object that generated the event.
 * @param text The new text.
 */
void EditBoxSettingsLayout::editBoxTextChanged(
	EditBox* editBox,
	const MAUtil::String& text)
{
	if (editBox == mMaxTextLengthEditBox)
	{
		int maxTextLength = MAUtil::stringToInteger(
			mMaxTextLengthEditBox->getText());
		if (maxTextLength != 0)
		{
			mEditBox->setMaxLength(maxTextLength);
			mGetTextLabel->setText("Max text length changed!");
		}
	}
	else if (editBox == mMaxLinesEditBox)
	{
		int maxLines = MAUtil::stringToInteger(
			mMaxLinesEditBox->getText());
		mEditBox->setMaxLines(maxLines);
		mGetTextLabel->setText("Max lines changed!");
	}
	else if (editBox == mMinLinesEditBox)
	{
		int minLines = MAUtil::stringToInteger(
			mMinLinesEditBox->getText());
		mEditBox->setMinLines(minLines);
		mGetTextLabel->setText("Min lines changed!");
	}
	else if (editBox == mPlaceholderColorEditBox)
	{
		int placeHolderColor = MAUtil::stringToInteger(
			mPlaceholderColorEditBox->getText());
		mEditBox->setPlaceholderFontColor(placeHolderColor);
		mGetTextLabel->setText("Placeholder color changed!");
	}
	else if (editBox == mLinesNumberEditBox)
	{
		int linesNumber = MAUtil::stringToInteger(
				mLinesNumberEditBox->getText());
		mEditBox->setLinesNumber(linesNumber);
		mGetTextLabel->setText("Lines number changed!");
	}
}

/**
 * This method is called when the return button was pressed.
 * On iphone platform the virtual keyboard is not hidden after
 * receiving this event.
 * Only for iphone platform.
 * @param editBox The edit box object that generated the event.
 */
void EditBoxSettingsLayout::editBoxReturn(EditBox* editBox)
{
	// do nothing
}
