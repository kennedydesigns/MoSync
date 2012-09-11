/*
 * WidgetListScreenListener.h
 *
 *  Created on: Sep 11, 2012
 *      Author: spiri
 */

#ifndef WIDGETLISTSCREENLISTENER_H_
#define WIDGETLISTSCREENLISTENER_H_

/**
 * \brief Listener for Widget list screen events.
 */
class WidgetListScreenListener
{
public:
	/**
	 * This method is called when a widget list item is clicked.
	 * @param index The index of the clicked widget.
	 */
	virtual void widgetListScreenItemClicked(int index) = 0;
};


#endif /* WIDGETLISTSCREENLISTENER_H_ */
