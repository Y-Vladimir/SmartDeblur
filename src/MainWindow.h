#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QImage>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QThread>
#include <QLabel>
#include <QScrollBar>
#include <QScrollArea>
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>
#include <QResizeEvent>
#include <QSharedPointer>
#include <QProgressBar>
#include <QString>
#include <QDropEvent>
#include <QUrl>
#include <time.h>

#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#include <cmath>
#else
#include <math.h>
#endif
#if defined (Q_WS_WIN)

#include "fftw3.h"
#else
#include <fftw3.h>
#endif
#include "DeconvolutionTool.h"
#include "WorkerThread.h"
#include "HelpDialog.h"
#include "CheckUpdatesThread.h"


namespace Ui {
class MainWindow;
}

class WorkerThread;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    static const double MAX_IMAGE_PIXELS;
    static double MAX_IMAGE_DIMENSION;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static const QString appVersion;

protected:
    void resizeEvent(QResizeEvent *resizeEvent);
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
private:
    Ui::MainWindow *ui;    
    HelpDialog *helpDialog;
    QTimer *startupTimer;
    WorkerThread *workerThread;
    CheckUpdatesThread *checkUpdatesThread;
    QLabel *imageLabel;
    double scaleFactor;

    QImage *inputImage;
    QImage *outputImage;

    QProgressBar* progressBar;
    QLabel* lblDeconvolutionTime;
    QLabel* lblThreadsCount;
    QLabel* lblImageSize;

    double radius, quality, feather, strength, motionLength, motionAngle;

    Blur* generateBlurInfo(bool previewMode);
    void updatePreviewDeconvolution();
    void scaleImage(double factor);
    void initControls();
    void createActions();
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    void openFile(QString fileName);




private slots:
    void radiusChanged();
    void PSNRChanged();
    void kernelFeatherChanged();
    void kernelStrengthChanged();
    void motionLengthChanged();
    void motionAngleChanged();
    void defectTypeChanged(int type);
    void open();
    void save();
    void zoomIn();
    void zoomOut();
    void actualSize();
    void fitToWindow();
    void help();
    void showOriginalPressed();
    void showOriginalReleased();
    void updateFullDeconvolution();
    void updateZoomControls();
    void updatePreviewImage(int deconvolutionTime);
    void updateProgress(int value, QString text);
    void imageSizeLimitChanged(int value);
    void tvIterationsCountChanged(int value);
    void previewMethodChanged(int value);

};



#endif // MAINWINDOW_H
