/********************************************************************************
 ** Form generated from reading UI file 'mainwindow.ui'
 **
 ** Created: Wed May 20 12:50:57 2015
 **      by: Qt User Interface Compiler version 4.8.1
 **
 ** WARNING! All changes made in this file will be lost when recompiling UI file!
 ********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include "scribblearea.h"
QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
	public:
		QWidget *centralWidget;
		QTimer *timer;
		QAction *saveAct;
		QAction *eraserAct;

		QAction *skeletonAct;
		QAction *nextFrameAct;
		QAction *prevFrameAct;
		QAction *riggingAct;
		QAction *retrieveSkeletonAct;
		QAction *changeRigPointsAct;
		QAction *modifyRigAct;	
		QAction *updateShadowAct;
		QAction *redrawSkeletonAct;
		QSpinBox *spinner;
		QSlider *slider;
		QHBoxLayout *horizontalLayout_3;
		QHBoxLayout *horizontalLayout_2;
		QVBoxLayout *verticalLayout_2;
		ScribbleArea *scribbleArea;
		QTextEdit *textEdit;
		QVBoxLayout *verticalLayout_3;
		QVBoxLayout *verticalLayout_4;
		QVBoxLayout *verticalLayout;
		 QPushButton *Shadow;
   		 QPushButton *Skeleton;
		QPushButton *Sketch;
		QPushButton *Normal;
		QPushButton *Erase;
		QPushButton *Play;
		QPushButton *Stop;
		QMenuBar *menuBar;
		QToolBar *mainToolBar;
		QStatusBar *statusBar;
		QLabel *label_10;
		void setupUi(QMainWindow *MainWindow)
		{
			if (MainWindow->objectName().isEmpty())
				MainWindow->setObjectName(QString::fromUtf8("MainWindow"));

			timer =new QTimer(MainWindow);
			saveAct = new QAction(MainWindow);
			saveAct->setObjectName(QString::fromUtf8("saveAct"));
			eraserAct = new QAction(MainWindow);
			eraserAct->setObjectName(QString::fromUtf8("eraserAct"));



			skeletonAct = new QAction(MainWindow);
			skeletonAct->setObjectName(QString::fromUtf8("skeletonAct"));
			nextFrameAct= new QAction(MainWindow);
			nextFrameAct->setObjectName(QString::fromUtf8("nextFrameAct"));
			nextFrameAct->setEnabled(false);
			prevFrameAct= new QAction(MainWindow);
			prevFrameAct->setObjectName(QString::fromUtf8("prevFrameAct"));
			prevFrameAct->setEnabled(false);	
			riggingAct = new QAction(MainWindow);
			riggingAct->setObjectName(QString::fromUtf8("riggingAct"));
			riggingAct->setEnabled(false);
			retrieveSkeletonAct = new QAction(MainWindow);
			retrieveSkeletonAct->setObjectName(QString::fromUtf8("retrieveSkeletonAct"));
			retrieveSkeletonAct->setEnabled(false);
			changeRigPointsAct = new QAction(MainWindow);
			changeRigPointsAct->setObjectName(QString::fromUtf8("changeRigPointsAct"));
			changeRigPointsAct->setEnabled(false);
			modifyRigAct = new QAction(MainWindow);
			modifyRigAct->setObjectName(QString::fromUtf8("modifyRigAct"));
			modifyRigAct->setEnabled(false);
			updateShadowAct = new QAction(MainWindow);
			updateShadowAct->setObjectName(QString::fromUtf8("updateShadowAct"));

			redrawSkeletonAct = new QAction(MainWindow);
			redrawSkeletonAct->setObjectName(QString::fromUtf8("redrawSkeletonAct"));
			redrawSkeletonAct->setEnabled(true);	
			centralWidget = new QWidget(MainWindow);
			centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
			spinner = new QSpinBox(centralWidget);
			slider = new QSlider(Qt::Horizontal,centralWidget);
			spinner->setRange(0,50);
			slider->setRange(0,50);
			slider->setGeometry(QRect(20, 620, 561, 29));
			spinner->setGeometry(QRect(640, 620, 50, 29));

			scribbleArea = new ScribbleArea(centralWidget);
			scribbleArea->setGeometry(QRect(2, 2, 600, 600));
			textEdit = new QTextEdit(centralWidget);
			textEdit->setObjectName(QString::fromUtf8("textEdit"));
			textEdit->setGeometry(QRect(930, 2, 300, 300));
			
			label_10 = new QLabel(centralWidget);
			label_10->setObjectName(QString::fromUtf8("label_10"));
			label_10->setGeometry(QRect(620, 2, 300, 300));

			Shadow = new QPushButton(centralWidget);
     		  	Shadow->setObjectName(QString::fromUtf8("Shadow"));
			Shadow->setGeometry(QRect(700, 350, 100, 30));
      			Skeleton = new QPushButton(centralWidget);
       			Skeleton->setObjectName(QString::fromUtf8("Skeleton"));
			Skeleton->setGeometry(QRect(700, 400, 100, 30));
			Skeleton->setEnabled(false);


			Sketch = new QPushButton(centralWidget);
       			Sketch->setObjectName(QString::fromUtf8("Sketch"));
			Sketch->setGeometry(QRect(700, 450, 100, 30));
			Sketch->setEnabled(false);
			
			Normal = new QPushButton(centralWidget);
       			Normal->setObjectName(QString::fromUtf8("Normal"));
			Normal->setGeometry(QRect(700, 500, 100, 30));


			Erase = new QPushButton(centralWidget);
       			Erase->setObjectName(QString::fromUtf8("Erase"));
			Erase->setGeometry(QRect(700, 550, 100, 30));

			Play = new QPushButton(centralWidget);
       			Play->setObjectName(QString::fromUtf8("Play"));
			Play->setGeometry(QRect(700, 600, 100, 30));

			Stop = new QPushButton(centralWidget);
       			Stop->setObjectName(QString::fromUtf8("Stop"));
			Stop->setGeometry(QRect(700, 650, 100, 30));

			Skeleton->setCheckable(true);
			Sketch->setCheckable(true);
			MainWindow->setCentralWidget(centralWidget);

			label_10->raise();
			label_10->raise();
			label_10->raise();
			textEdit->raise();
			menuBar = new QMenuBar(MainWindow);
			menuBar->setObjectName(QString::fromUtf8("menuBar"));
			menuBar->setGeometry(QRect(0, 0, 1200, 25));
			MainWindow->setMenuBar(menuBar);
			mainToolBar = new QToolBar(MainWindow);
			mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
			mainToolBar->addAction(skeletonAct);
			mainToolBar->addSeparator();
			mainToolBar->addAction(redrawSkeletonAct);
			mainToolBar->addSeparator();
			mainToolBar->addAction(retrieveSkeletonAct);
			mainToolBar->addSeparator();
			mainToolBar->addAction(riggingAct);
			mainToolBar->addSeparator();
			mainToolBar->addAction(changeRigPointsAct);
			mainToolBar->addSeparator();
			mainToolBar->addAction(modifyRigAct);
			mainToolBar->addSeparator();
			mainToolBar->addAction(nextFrameAct);
			mainToolBar->addSeparator();

			mainToolBar->addAction(updateShadowAct);
			
			
			MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
			statusBar = new QStatusBar(MainWindow);
			statusBar->setObjectName(QString::fromUtf8("statusBar"));
			MainWindow->setStatusBar(statusBar);

			retranslateUi(MainWindow);

			QMetaObject::connectSlotsByName(MainWindow);
		} // setupUi

		void retranslateUi(QMainWindow *MainWindow)
		{
			MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
			saveAct->setText(QApplication::translate("MainWindow", "Save Frame", 0, QApplication::UnicodeUTF8));
			eraserAct->setText(QApplication::translate("MainWindow", "Eraser Mode", 0, QApplication::UnicodeUTF8));

			skeletonAct->setText(QApplication::translate("MainWindow", "Draw Skeleton", 0, QApplication::UnicodeUTF8));
			nextFrameAct->setText(QApplication::translate("MainWindow", "Next Frame", 0, QApplication::UnicodeUTF8));
			prevFrameAct->setText(QApplication::translate("MainWindow", "Prev Frame", 0, QApplication::UnicodeUTF8));
			riggingAct->setText(QApplication::translate("MainWindow", "Rig", 0, QApplication::UnicodeUTF8));
			retrieveSkeletonAct->setText(QApplication::translate("MainWindow", "SkeletonFromDB", 0, QApplication::UnicodeUTF8));
			changeRigPointsAct->setText(QApplication::translate("MainWindow", "ManualRig", 0, QApplication::UnicodeUTF8));
			modifyRigAct->setText(QApplication::translate("MainWindow", "UpdateCurve", 0, QApplication::UnicodeUTF8));

			updateShadowAct->setText(QApplication::translate("MainWindow", "Update Shadow", 0, QApplication::UnicodeUTF8));
			redrawSkeletonAct->setText(QApplication::translate("MainWindow", "Redraw Skeleton", 0, QApplication::UnicodeUTF8));
			Shadow->setText(QApplication::translate("MainWindow", "Shadow", 0, QApplication::UnicodeUTF8));
        		Skeleton->setText(QApplication::translate("MainWindow", "Skeleton", 0, QApplication::UnicodeUTF8));
			Sketch->setText(QApplication::translate("MainWindow", "Sketch", 0, QApplication::UnicodeUTF8));
			Normal->setText(QApplication::translate("MainWindow", "Normal", 0, QApplication::UnicodeUTF8));
			Erase->setText(QApplication::translate("MainWindow", "Erase", 0, QApplication::UnicodeUTF8));
			Play->setText(QApplication::translate("MainWindow", "Play", 0, QApplication::UnicodeUTF8));
			Stop->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
			label_10->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
		} // retranslateUi

};

namespace Ui {
	class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
