/*
 * MainWindow.cpp
 *
 *  Created on: Dec 6, 2017
 *      Author: denizcan
 */

#include <MainWindow.h>
#include <FontArial24.h>

using namespace Art;

MainWindow::MainWindow()
{
	// set window background
	setBackgroundColor(StandardColorBlue);

	// sets all children font unless children override..
	setFont(fontArial24());

	m_count = 0;
	setBounds(0, 0, 240, 320);

	m_companyLabel.setBounds(20, 300, 200, 20);
	m_companyLabel.setText("Arselon Ltd.");
	m_companyLabel.setTextAlignment(AlignCenter);
	// set font to ovveride parent font
	m_companyLabel.setFont(Fonts::lerosG9());
	add(&m_companyLabel);

	m_countLabel.setBounds(20, 20, 200, 40);
	m_countLabel.setTextAlignment(AlignHCenter| AlignVCenter);
	add(&m_countLabel);

	m_upButton.setBounds(20, 80, 200, 80);
	m_upButton.setText("Up");
	m_upButton.setBackgroundColor(StandardColorGreen);
	m_upButton.onClick().connect(this, &MainWindow::doUpButtonClick);
	add(&m_upButton);

	m_downButton.setBounds(20, 180, 200, 80);
	m_downButton.setText("Down");
	m_downButton.setBackgroundColor(StandardColorRed);
	m_downButton.onClick().connect(this, &MainWindow::doDownButtonClick);
	add(&m_downButton);

	updateLabel();
}

MainWindow::~MainWindow()
{
}

void MainWindow::doUpButtonClick(void*)
{
	m_count++;
	updateLabel();
}

void MainWindow::doDownButtonClick(void*)
{
	m_count--;
	updateLabel();
}

void MainWindow::updateLabel()
{
	m_countLabel.setText(String("Count: %0").arg(m_count));
}
