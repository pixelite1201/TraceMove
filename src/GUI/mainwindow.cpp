/****************************************************************************
 **
 ** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 ** All rights reserved.
 ** Contact: Nokia Corporation (qt-info@nokia.com)
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
 **   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
 **     the names of its contributors may be used to endorse or promote
 **     products derived from this software without specific prior written
 **     permission.
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
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

#include <QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow():ui(new Ui::MainWindow)
{

	//ui->scribbleArea = new ScribbleArea;
	//setCentralWidget(ui->scribbleArea);
	fS=FrameStorage();
	failsafe=FailSafe();
	frame_no=0;
	frame_drawn=0;
	play_frame=0;
	ui->setupUi(this);

 ui->label_10->setPixmap((QPixmap("init.jpeg")).scaled(300,300));
ui->textEdit->setReadOnly(true);
QPalette p = ui->textEdit->palette();

  p.setColor(QPalette::Active, QPalette::Base, QColor(200,200,200));
  p.setColor(QPalette::Inactive, QPalette::Base,  QColor(200,200,200));

  ui->textEdit->setPalette(p);
ui->textEdit->setText("Draw character and for getting help from shadow image click on Update ShadowImage option in Tools menu. After finishing go to skeleton drawing mode by clicking on Draw Skeleton in Tools menu");
	createActions();
	createMenus();

	setWindowTitle(tr("Scribble"));
	resize(300, 300);

}


void MainWindow::open()
{
	QString fileName = QFileDialog::getOpenFileName(this,
			tr("Open File"), QDir::currentPath());
	if (!fileName.isEmpty()){
		string temp=fileName.toStdString();
		stringstream ss;
		temp=temp.substr(temp.find_last_of('/')+1);
		temp=temp.substr(2);
		frame_drawn=stoi(temp);
	}
	failsafe.read(ui->scribbleArea,ui->scribbleArea->path_to_DB);
	ui->scribbleArea->cV.rigPoints.resize(ui->scribbleArea->dS.node_count);//put these in failsafe
	ui->scribbleArea->cV.rigPoints_dualWt.resize(ui->scribbleArea->dS.node_count);
	ui->nextFrameAct->setEnabled(true);
	ui->prevFrameAct->setEnabled(true);		
	ui->changeRigPointsAct->setEnabled(true);
	ui->modifyRigAct->setEnabled(true);
	ui->Skeleton->setEnabled(true);
	ui->Sketch->setEnabled(true);
	ui->scribbleArea->sketch_flag=1;
	ui->scribbleArea->first_frame_done=1;
	ui->textEdit->setText("Select either CVx or DSx file from database where integer value x denotes the maximum frame upto which you want to retrieve the frames");
}

void MainWindow::play(){
	ui->scribbleArea->clearImage();
	fS.read(ui->scribbleArea,ui->scribbleArea->path_to_DB,play_frame);
	ui->scribbleArea->sketch_flag=1;
	if(ui->scribbleArea->skeleton_flag)
	ui->scribbleArea->read_display(Qt::red,Qt::green);
	if(ui->scribbleArea->sketch_flag)
	ui->scribbleArea->drawCurveDefaultColor();	
	if(play_frame<frame_drawn)
	play_frame++;
	else
	play_frame=0;
	

}
void MainWindow::save()
{
	frame_drawn=max(frame_drawn,frame_no+1); //to let the spinner load the frame
	saveFile();
}

void MainWindow::eraser()
{	
	if(ui->scribbleArea->first_frame_done){
		ui->scribbleArea->erase2=true;
		ui->scribbleArea->erase=false;
	}
	else{
		ui->scribbleArea->erase=false;
		ui->scribbleArea->erase=true;
	}
		
	ui->scribbleArea->skeleton=false;
	ui->scribbleArea->rig=false;
	ui->scribbleArea->normal2=false;
	ui->textEdit->setText("Click on the curve need to be erased");
}
void MainWindow::skeleton(){
	ui->scribbleArea->skeleton=true;
	ui->scribbleArea->rig=false;
	ui->scribbleArea->erase=false;
	ui->scribbleArea->erase2=false;
	ui->scribbleArea->normal2=false;
	ui->retrieveSkeletonAct->setEnabled(true);
	ui->label_10->setPixmap((QPixmap("skeleton_fig.png")).scaled(300,300));	
	ui->textEdit->setText("Draw skeleton of character, ordering of joints should be same as shown in image. You can redraw skeleton at any point by clicking at Redraw Skeleton from Tools menu. Note that left hand should be drawn before right hand and left leg should be drawn before right leg. After finishing skeleton drawing select SkeletonFromDB in toolbar");
}

void MainWindow::nextFrame(){
	maybeSave();
	ui->scribbleArea->clearImage();
	ui->scribbleArea->dS.update_Binding_Matrix();
	ui->scribbleArea->rS.find_diff(&(ui->scribbleArea->dS),1);
	ui->scribbleArea->dS.calculate_newP2();
	ui->scribbleArea->calculate_newP(ui->scribbleArea->dS.skeletonNodes,ui->scribbleArea->dS.oldSkeletonNodes);
	if(ui->scribbleArea->rS.frameNo<ui->scribbleArea->rS.total_skeleton-3){
	ui->scribbleArea->rS.frameNo++; //current frame is frameNo+1
	if(ui->scribbleArea->skeleton_flag)
	ui->scribbleArea->read_display(Qt::red,Qt::green);
	ui->scribbleArea->dS.update_Transform_Matrix();
	ui->scribbleArea->drawNextFrameCurve();
	ui->scribbleArea->drawCurveDiffColor();
	frame_no++;
	
	frame_drawn=max(frame_drawn,frame_no);
	ui->slider->blockSignals(true);
	ui->slider->setValue(frame_no);
	ui->slider->blockSignals(false);
	ui->spinner->blockSignals(true);
	ui->spinner->setValue(frame_no);
	ui->spinner->blockSignals(false);
	ui->prevFrameAct->setEnabled(true);		
	ui->scribbleArea->cV.curvePoints.clear();
	ui->scribbleArea->cV.curvePoints2.clear();
	ui->scribbleArea->curve=-1;
	ui->textEdit->setText("");
	}
	else{
		ui->nextFrameAct->setEnabled(false);
	}
	
	
}

void MainWindow::prevFrame(){
	maybeSave();
	ui->scribbleArea->clearImage();
	ui->scribbleArea->dS.update_Binding_Matrix();
	ui->scribbleArea->rS.find_diff(&(ui->scribbleArea->dS),0);
	ui->scribbleArea->dS.calculate_newP2();
	ui->scribbleArea->calculate_newP(ui->scribbleArea->dS.skeletonNodes,ui->scribbleArea->dS.oldSkeletonNodes);
	ui->scribbleArea->rS.frameNo--; //current frame is frameNo+1
	if(ui->scribbleArea->skeleton_flag)
	ui->scribbleArea->read_display(Qt::red,Qt::green);
	ui->scribbleArea->dS.update_Transform_Matrix();
	ui->scribbleArea->drawNextFrameCurve();
	ui->scribbleArea->drawCurveDiffColor();
	frame_no--;
	frame_drawn=max(frame_drawn,frame_no);
	ui->slider->blockSignals(true);
	ui->slider->setValue(frame_no);
	ui->slider->blockSignals(false);
	ui->spinner->blockSignals(true);
	ui->spinner->setValue(frame_no);
	ui->spinner->blockSignals(false);
	ui->scribbleArea->cV.curvePoints.clear();
	ui->scribbleArea->cV.curvePoints2.clear();
	ui->scribbleArea->curve=-1;
	ui->textEdit->setText("");
}


void MainWindow::spinnerValue(int frame){
	if(frame<frame_drawn){
	ui->scribbleArea->clearImage();
	frame_no=frame;
	fS.read(ui->scribbleArea,ui->scribbleArea->path_to_DB,frame_no);
	if(ui->scribbleArea->skeleton_flag)
	ui->scribbleArea->read_display(Qt::red,Qt::green);
	if(ui->scribbleArea->sketch_flag)
	ui->scribbleArea->drawCurveDiffColor();	
	}
}
void MainWindow::rigging(){
	ui->riggingAct->setEnabled(false);
	ui->scribbleArea->cV.assign_skeleton_midPt(ui->scribbleArea->dS);
	ui->scribbleArea->cV.rigging();
	ui->scribbleArea->cV.divideCurve();
//	ui->scribbleArea->drawCurve();
	ui->scribbleArea->drawCurveDiffColor();
	ui->scribbleArea->first_frame_done=true;
	ui->nextFrameAct->setEnabled(true);
	ui->changeRigPointsAct->setEnabled(true);
	
	ui->scribbleArea->cV.curvePoints.clear();
	ui->scribbleArea->cV.curvePoints2.clear();
	ui->scribbleArea->curve=-1;
	ui->Sketch->setEnabled(true);
	failsafe.write(ui->scribbleArea,ui->scribbleArea->path_to_DB);
ui->textEdit->setText("Automatic rigging is complete. Select ManualRig from toolbar to do the manual rigging");

}
void MainWindow::redrawSkeleton(){
ui->scribbleArea->redrawSkeleton();
}

void MainWindow::retrieveSkeleton(){	
	ui->scribbleArea->dS.update();
	ui->scribbleArea->rS.node_count=ui->scribbleArea->dS.skeletonNodes.size();
	ui->scribbleArea->rS.read();
	ui->scribbleArea->scale_f(&(ui->scribbleArea->dS),&(ui->scribbleArea->rS));
	ui->scribbleArea->calculate_newP(ui->scribbleArea->dS.skeletonNodes,ui->scribbleArea->dS.oldSkeletonNodes);
	ui->scribbleArea->rS.compare(&(ui->scribbleArea->dS));
	ui->scribbleArea->read_display(Qt::red,Qt::green);
	ui->riggingAct->setEnabled(true);
	ui->retrieveSkeletonAct->setEnabled(false);	
	ui->redrawSkeletonAct->setEnabled(false);
	ui->Skeleton->setEnabled(true);
	ui->textEdit->setText("Most matching skeleton is selected from database. Now click on Rig from toolbar to do the automatic rigging");
 ui->label_10->setPixmap((QPixmap("init.jpeg")).scaled(300,300));

}
void MainWindow::changeRigPoints(){
	ui->scribbleArea->rig=true;
	ui->scribbleArea->erase=false;
	ui->scribbleArea->erase2=false;
	ui->scribbleArea->skeleton=false;
	ui->scribbleArea->normal2=false;
	ui->scribbleArea->reassociate.clear();
	ui->modifyRigAct->setEnabled(true);
	ui->textEdit->setText("Select the curve by clicking on it. Similarly, select the skeleton joint to which the curve need to be associated. Click on UpdateCurve to reassociate");
}
void MainWindow::modifyRig(){
	ui->scribbleArea->modify_rig();
	ui->scribbleArea->drawCurveDiffColor();
}

void MainWindow::normalMode(){
		if(ui->scribbleArea->first_frame_done)
		ui->scribbleArea->normal2=true;
		else
		ui->scribbleArea->normal2=false;
		
		ui->scribbleArea->rig=false;
		ui->scribbleArea->erase=false;
		ui->scribbleArea->erase2=false;
		ui->scribbleArea->skeleton=false;
ui->textEdit->setText("Draw curve and for getting help from shadow image click on Update ShadowImage option in toolbar. Take care that skeleton mode is toggled off while updating shadow image.");
}
void MainWindow::updateShadow(){
ui->scribbleArea->shadow_flag=1;
ui->scribbleArea->save_updateShadow();
ui->label_10->setPixmap((QPixmap("b.jpg")).scaled(300,300));
}
void MainWindow::shadowOFF(){
ui->scribbleArea->shadow_flag=0;
ui->scribbleArea->update();

}
void MainWindow::skeletonOFF(bool i){
ui->scribbleArea->skeleton_flag=!i;
if(i)
ui->scribbleArea->read_display(Qt::white,Qt::white);
else
ui->scribbleArea->read_display(Qt::red,Qt::green);
}
void MainWindow::sketchOFF(bool i){
ui->scribbleArea->sketch_flag=!i;
if(i)
ui->scribbleArea->eraseSketch();
else
ui->scribbleArea->drawCurveDiffColor();
}
void MainWindow::playON(){
ui->timer->start(100);
}
void MainWindow::playOFF(){
ui->timer->stop();
}
void MainWindow::penColor()
{
	QColor newColor = QColorDialog::getColor(ui->scribbleArea->penColor());
	if (newColor.isValid())
	ui->scribbleArea->setPenColor(newColor);
	ui->scribbleArea->setPenWidth(2);

}

void MainWindow::penWidth()
{
	bool ok;
	int newWidth = QInputDialog::getInteger(this, tr("Scribble"),
			tr("Select pen width:"),
			ui->scribbleArea->penWidth(),
			1, 50, 1, &ok);
	if (ok)
		ui->scribbleArea->setPenWidth(newWidth);
}

void MainWindow::shadowVisibility()
{
	bool ok;
	double newVisibility = QInputDialog::getDouble(this, tr("Scribble"),
			tr("Select shadow visibility:"),
			ui->scribbleArea->shadowVisibility,
			0, 1, 3, &ok);
	if (ok)
		ui->scribbleArea->setVisibility(newVisibility);
}


void MainWindow::createActions()
{
	openAct = new QAction(tr("&Open..."), this);
	openAct->setShortcuts(QKeySequence::Open);
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

	connect(ui->saveAct, SIGNAL(triggered()),this,SLOT(save()));
	



	penColorAct = new QAction(tr("&Pen Color..."), this);
	connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

	ui->eraserAct->setShortcut(tr("Shift+E"));
	connect(ui->eraserAct, SIGNAL(triggered()), this, SLOT(eraser()));
	connect(ui->Erase, SIGNAL(released()), this, SLOT(eraser()));
	
	connect(ui->Play,SIGNAL(released()),this, SLOT(play()));
	ui->skeletonAct->setShortcut(tr("Shift+Q"));
	connect(ui->skeletonAct, SIGNAL(triggered()), this, SLOT(skeleton()));

	connect(ui->nextFrameAct, SIGNAL(triggered()), this, SLOT(nextFrame()));
	connect(ui->prevFrameAct, SIGNAL(triggered()), this, SLOT(prevFrame()));

	ui->riggingAct->setShortcut(tr("Shift+R"));
	connect(ui->riggingAct, SIGNAL(triggered()), this, SLOT(rigging()));

   
	ui->retrieveSkeletonAct->setShortcut(tr("Shift+P"));
	connect(ui->retrieveSkeletonAct, SIGNAL(triggered()), this, SLOT(retrieveSkeleton()));

	ui->changeRigPointsAct->setShortcut(tr("Shift+I"));
	connect(ui->changeRigPointsAct , SIGNAL(triggered()), this, SLOT(changeRigPoints()));

	ui->modifyRigAct->setShortcut(tr("Shift+J"));
	connect(ui->modifyRigAct, SIGNAL(triggered()), this, SLOT(modifyRig()));
	
	normalAct = new QAction(tr("&Normal mode..."),this);
	normalAct->setShortcut(tr("Shift+N"));
	connect(normalAct, SIGNAL(triggered()), this, SLOT(normalMode()));
	connect(ui->Normal, SIGNAL(released()), this, SLOT(normalMode()));

	penWidthAct = new QAction(tr("Pen &Width..."), this);
	connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

	
	connect(ui->updateShadowAct, SIGNAL(triggered()), this, SLOT(updateShadow()));
	connect(ui->Shadow,SIGNAL(released()),this,SLOT(shadowOFF()));

	connect(ui->redrawSkeletonAct,SIGNAL(triggered()), this, SLOT(redrawSkeleton()));

	shadowVisibilityAct = new QAction(tr("&Shadow Visibility..."), this);
	connect(shadowVisibilityAct, SIGNAL(triggered()), this, SLOT(shadowVisibility()));

	clearScreenAct = new QAction(tr("&Clear Screen"), this);
	clearScreenAct->setShortcut(tr("Ctrl+L"));
	connect(clearScreenAct, SIGNAL(triggered()),
			ui->scribbleArea, SLOT(clearImage()));

	

	connect(ui->Skeleton,SIGNAL(toggled(bool)),this,SLOT(skeletonOFF(bool)));
	connect(ui->Sketch,SIGNAL(toggled(bool)),this,SLOT(sketchOFF(bool)));
	connect(ui->Play,SIGNAL(pressed()),this,SLOT(playON()));
	connect(ui->Stop,SIGNAL(pressed()),this,SLOT(playOFF()));
	connect(ui->spinner, SIGNAL(valueChanged(int)),ui->slider,SLOT(setValue(int)));
	connect(ui->spinner, SIGNAL(valueChanged(int)),this,SLOT(spinnerValue(int)));
	connect(ui->slider,SIGNAL(valueChanged(int)),ui->spinner,SLOT(setValue(int)));
	connect(ui->slider, SIGNAL(valueChanged(int)),this,SLOT(spinnerValue(int)));
	connect(ui->timer,SIGNAL(timeout()),this,SLOT(play()));
	
}

void MainWindow::createMenus()
{
	

	fileMenu = new QMenu(tr("&File"), this);
	fileMenu->addAction(openAct);
	fileMenu->addAction(ui->saveAct);
	fileMenu->addSeparator();
	


	optionMenu = new QMenu(tr("&Options"), this);
	optionMenu->addAction(penColorAct);
	optionMenu->addAction(penWidthAct);
	optionMenu->addAction(ui->eraserAct);
	optionMenu->addAction(shadowVisibilityAct);
	optionMenu->addSeparator();
	optionMenu->addAction(clearScreenAct);

	toolsMenu = new QMenu(tr("&Tools"), this);
	toolsMenu->addAction(ui->skeletonAct);
	toolsMenu->addAction(ui->redrawSkeletonAct);
	toolsMenu->addAction(ui->nextFrameAct);
	toolsMenu->addAction(ui->prevFrameAct);
	toolsMenu->addAction(ui->riggingAct);
	toolsMenu->addAction(ui->retrieveSkeletonAct);
	toolsMenu->addAction(ui->changeRigPointsAct);
	toolsMenu->addAction(ui->modifyRigAct);
	toolsMenu->addAction(normalAct);
	toolsMenu->addAction(ui->updateShadowAct);


	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(optionMenu);
	menuBar()->addMenu(toolsMenu);

	//fileToolBar = new QToolBar(tr("File"), this);
   	

	//fileToolBar->addAction(eraserAct); 
	//fileToolBar->addSeparator();
	//fileToolBar->addAction(ui->skeletonAct); 
	//fileToolBar->addAction(ui->nextFrameAct); 
	
	


}

bool MainWindow::maybeSave()
{
	if (ui->scribbleArea->isModified()) {
		QMessageBox::StandardButton ret;
		ret = QMessageBox::warning(this, tr("Scribble"),
				tr("The image has been modified.\n"
					"Do you want to save your changes?"),
				QMessageBox::Save | QMessageBox::Cancel);
		if (ret == QMessageBox::Save) {
			return saveFile();
		} else if (ret == QMessageBox::Cancel) {
			return false;
		}
	}
	return true;
}

bool MainWindow::saveFile()
{
	fS.write(ui->scribbleArea,ui->scribbleArea->path_to_DB,frame_no);
}

