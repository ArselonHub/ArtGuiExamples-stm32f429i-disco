/*
 * MainWindow.h
 *
 *  Created on: Dec 6, 2017
 *      Author: denizcan
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <Art/Window.h>
#include <Art/Label.h>
#include <Art/Button.h>

class MainWindow : public Art::Window
{
public:
	MainWindow();
	virtual ~MainWindow();
private:
	void doDownButtonClick(void*);
	void doUpButtonClick(void*);
	void updateLabel();

	Art::Label		m_countLabel;
	Art::Label		m_companyLabel;
	Art::Button		m_downButton;
	Art::Button 	m_upButton;
	Int				m_count;
};

#endif /* SOURCES_MAINWINDOW_H_ */
