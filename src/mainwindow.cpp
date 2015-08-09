/****************************************************************************
 **
 ** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
 ** Contact: http://www.qt-project.org/legal
 **
 ** This file is part of the examples of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:BSD$
 ** You may use this file under the terms of the BSD license as follows:
 **
 ** "Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are
 ** met:
 **   * Redistributions of source code must retain the above copyright
 **     notice, this list of conditions and the following disclaimer.
 **   * Redistributions in binary form must reproduce the above copyright
 **     notice, this list of conditions and the following disclaimer in
 **     the documentation and/or other materials provided with the
 **     distribution.
 **   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
 **     of its contributors may be used to endorse or promote products derived
 **     from this software without specific prior written permission.
 **
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 ** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 ** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 ** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 ** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 ** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 ** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 ** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 ** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 ** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 ** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 **
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

#include <QtWidgets>

#include "mainwindow.h"
#include "xbeltree.h"

MainWindow::MainWindow()
{
  init_file="./test1.xbel";
  firstOpen=1;
  QWidget* w=new QWidget;
  xbelTree = new XbelTree(w);
  // setCentralWidget(xbelTree);
  setCentralWidget(w);
  

  createActions();

  createLabel();
  createButtonLayout();
  createMenus();
    
  statusBar()->showMessage(tr("Ready"));

  QGridLayout* GridLayout=new QGridLayout;
  // QVBoxLayout* vbox=new QVBoxLayout;
  // vbox->addLayout(GridLayout);
  GridLayout->addWidget(xbelTree,0,0);
  label->setText("TO be filled");
  GridLayout->addWidget(label,0,1);
  GridLayout->setColumnMinimumWidth(0,900);
  GridLayout->addLayout(buttonLayout,1,1,1,1);
    // GridLayout->addLayout(buttonLayout,1,2,1,2);
  // GridLayout->setColumnMaximunWidth(1,400);
  w->setLayout(GridLayout);

  // //  w->setAutoFillBackground(true);
  // QPalette palette;
  // //  palette.setColor(QPalette::Background, QColor(192,253,123));
  // palette.setBrush(QPalette::Background, QBrush(QPixmap("../resource/pic1.png")));

  // w->setPalette(palette);

  // xbelTree->show();
  // setLayout(vbox);
    
  setWindowIcon(QIcon("../resource/pic1.png"));
  setWindowTitle(tr("DOM Bookmarks"));
  // xbelTree->hide();
  // xbelTree->resize(800,600);
  resize(1024, 768);
}

void MainWindow::open()
{
  QString fileName;
  if (firstOpen) {
      fileName=init_file;
      firstOpen=0;
    } else {
      fileName =
      QFileDialog::getOpenFileName(this, tr("Open Bookmark File"),
				   QDir::currentPath(),
				   tr("XBEL Files (*.xbel *.xml)"));
  }
  if (fileName.isEmpty())
    return;

  QFile file(fileName);
  if (!file.open(QFile::ReadOnly | QFile::Text)) {
    QMessageBox::warning(this, tr("SAX Bookmarks"),
			 tr("Cannot read file %1:\n%2.")
			 .arg(fileName)
			 .arg(file.errorString()));
    return;
  }

  if (xbelTree->read(&file))
    statusBar()->showMessage(tr("File loaded"), 2000);
}

void MainWindow::saveAs()
{
  QString fileName =
    QFileDialog::getSaveFileName(this, tr("Save Bookmark File"),
				 QDir::currentPath(),
				 tr("XBEL Files (*.xbel *.xml)"));
  if (fileName.isEmpty())
    return;

  QFile file(fileName);
  if (!file.open(QFile::WriteOnly | QFile::Text)) {
    QMessageBox::warning(this, tr("SAX Bookmarks"),
			 tr("Cannot write file %1:\n%2.")
			 .arg(fileName)
			 .arg(file.errorString()));
    return;
  }

  if (xbelTree->write(&file))
    statusBar()->showMessage(tr("File saved"), 2000);
}

void MainWindow::about()
{
  QMessageBox::about(this, tr("About DOM Bookmarks"),
		     tr("The <b>DOM Bookmarks</b> example demonstrates how to "
			"use Qt's DOM classes to read and write XML "
			"documents."));
}

void MainWindow::createActions()
{
  openAct = new QAction(tr("&Open..."), this);
  openAct->setShortcuts(QKeySequence::Open);
  connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

  saveAsAct = new QAction(tr("&Save As..."), this);
  saveAsAct->setShortcuts(QKeySequence::SaveAs);
  connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

  exitAct = new QAction(tr("E&xit"), this);
  exitAct->setShortcuts(QKeySequence::Quit);
  connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

  aboutAct = new QAction(tr("&About"), this);
  connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

  aboutQtAct = new QAction(tr("About &Qt"), this);
  connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(openAct);
  fileMenu->addAction(saveAsAct);
  fileMenu->addAction(exitAct);

  menuBar()->addSeparator();

  helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(aboutAct);
  helpMenu->addAction(aboutQtAct);
}

void MainWindow::createLabel() {
  label=new QLabel;
  label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  label->setAlignment(Qt::AlignCenter);
  label->setMinimumSize(240, 160);
  
}
void MainWindow::createButtonLayout() {
  buttonLayout=new QHBoxLayout;
  buttonupdate = createButton(tr("Update Weight"), this, SLOT(updateWeight()));
  buttonexit = createButton(tr("Quit"), this, SLOT(close()));
  buttonLayout->addStretch();
  buttonLayout->addWidget(buttonupdate);
  buttonLayout->addWidget(buttonexit);
  
}
QPushButton *MainWindow::createButton(const QString &text, QWidget *receiver,
                                      const char *member)
{
  QPushButton *button = new QPushButton(text);
  button->connect(button, SIGNAL(clicked()), receiver, member);
  return button;
}


void MainWindow::updateWeight() {
  xbelTree->updateDomWeightAll();
}

