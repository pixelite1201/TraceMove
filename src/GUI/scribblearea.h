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

/*!
  \file scribblearea.h
  \brief This file basically deals with all the interface related functions
*/
#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QKeyEvent>
#include <vector>
#include<fstream>
#include "MatchingImage.h"
#include "RetrievedSkeleton.h"
#include "CurvePoints.h"

class ScribbleArea : public QWidget
{
	Q_OBJECT

	public:
		//! Constructor
		ScribbleArea(QWidget *parent = 0);
		//! Store the image displayed on the interface
		Mat testImg;
		//! RetrievedSkeleton object
		RetrievedSkeleton rS;
		//! DrawnSkeleton object
		DrawnSkeleton dS;
		//! CurvePoints object
		CurvePoints cV;
		//! Store path to database files
		string path_to_DB;  
		//! MatchingImage object
		MatchingImage matchI;	
		//! skeleton drawing mode flag	
		bool skeleton;
		//! manual rigging mode flag
		bool rig;
		//! erase1 mode flag 
		/*! Mode1 refers to the erase done by user before completing the first frame.
			* Since no rigging is done at this point, no rigged curves are present
			* only user drawn curves are present and stored in \ref CurvePoints::curvePoints
		*/
		bool erase;
		//! erase2 mode flag
		/*! Node2 refers to the erase done by user after completing the first frame.
			* After rigging is done  curves are present in \ref CurvePoints::final_rigPoints
			* and are deleted from there.
		*/
		bool erase2;
		//! normal mode2 flag
		/*! Normal2 mdoe is active after first frame is completed. 
			* When the normal2 mode is active, user drawn curves get automatically rigged.
		*/
		bool normal2;
		//! shadow_flag is used to display or hide shadow in background
		bool shadow_flag; 
		//! skeleton_flag is used to display or hide skeleton
		bool skeleton_flag;
		//! sketch_flag is used to display or hide sketch
		bool sketch_flag;
		//! Denotes whether first frame is completed or not
		bool first_frame_done;
		//! Store the number of curve drawn till now
		int curve;
		//! Store shadow visibility value on the scale of 0 to 1
		double shadowVisibility;
		//! Store the scale factor for user drawn skeleton and database skeleton
		vector<float> bone_scale;
		//! Will store the two points clicked during manual rigging
		/* First clicked point used to find the nearest curve and second clicked
		* point is used to search for nearest skeleton joint
		*/
		vector<POINT> reassociate;
		//! Set pen color to color provided as argument
		void setPenColor(const QColor &newColor);
		//! Set pen color to color provided as argument
		void setPenWidth(int newWidth);
		//! Set visibility of shadow in background on scale of 0 to 1
		void setVisibility(double newVisibility);
		//! Check whether the drawing area is modified
		bool isModified() const { return modified; }
		//! Return current pen color
		QColor penColor() const { return myPenColor; }
		//! Return current pen width
		int penWidth() const { return myPenWidth; }
		//! Update shadow displayed in the background on the basis of current user image
		/*! Will take the user drawn image as input, fint most matching image from database,
			* blend them together and display them on interface. Since the database images
			* are of 300*300, final blend image need to be scaled to 600*600 before displaying.
		*/
		void updateShadow();
		//! Image displayed on interface is converted to 300*300 as database images are of size 300*300
		void save_updateShadow();
		//! Display skeleton 
		/*! If both color arguments are white then it will erase the skeleton, else it will draw the 
			* skeleton using the color passed as argument
		*/
		void read_display(QColor,QColor);
		//! Take points drawn by user as input and fit bezier curve on it
		void drawCurve(vector<POINT>);
		//! Redraw skeleton 
		/*! If user has made some mistake while drawing the skeleton, he can redraw it. 
			* The function will remove the skeleton points drawn till now
			* from dS->skeletonNodes vector
		*/
		void redrawSkeleton();
		//! Draw the curve with default pen color
		void drawCurveDefaultColor();
		//! Draw the curve in different color on the basis of their attachment to skeleton joints
		void drawCurveDiffColor();
		//! Will update the rig as user's input
		/*! User will click on the curve and the skeleton joint to which he want to associte the curve.
			* It will be passed to \ref CurvePoints::manualRigging(vector<POINT> curvePoint,int skeleton) function which will 
			* associate the curvepoints to the user clicked skeleton joint. It will again divide curve into different 
			* curves on the basis of threshold value using \ref CurvePoints::divideCurve(). Finally, it will erase the 
			* curve from the original joints its associated to.
		*/
		void modify_rig();
		//!  Will erase the sketch on the interface
		void eraseSketch();
		//! Will update the display on the screen by erasing the curve user has clicked on.
		void after_erase(int);
		//! Will update the display on the screen by erasing the curve user has clicked on.
		void after_erase2(POINT);
		//! Will calculate new skeleton joints after scaling the original drawn by scale factor
		void calculate_newP(vector<POINT>, vector<POINT>&);
		//! Will calculate scale factor of user drawn skeleton bones and database skeleton bones
		void scale_f(DrawnSkeleton*, RetrievedSkeleton*);
		//! Apply Transformation matrix to current frame curve to generate next frame curves
		void drawNextFrameCurve();
		

	public slots:
		//! Will clear the entire display area
		void clearImage();

	protected:
		void keyPressEvent(QKeyEvent* event);
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void paintEvent(QPaintEvent *event);
		void resizeEvent(QResizeEvent *event);

	private:
		void drawLineTo(const QPoint &endPoint);
		void drawPointTo(const QPoint &endPoint);
		void resizeImage(QImage *image, const QSize &newSize);
		bool modified;
		bool scribbling;
		int myPenWidth;
		QImage shadow;
		QColor myPenColor;
		QImage image;
		QImage image2;
		QPoint lastPoint;
		QPoint lastCursor;
};
		

#endif

