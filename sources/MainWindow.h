#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QImage>
#include <QPainter>
#include <QTime>
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

#include <time.h>
#include <math.h>
#include "fftw3.h"
#include "DeconvolutionTool.h"
#include "WorkerThread.h"


namespace Ui {
class MainWindow;
}

class WorkerThread;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *resizeEvent);
    
private:
    Ui::MainWindow *ui;
    WorkerThread *workerThread;
    QLabel *imageLabel;
    double scaleFactor;

    QImage *inputImage;
    QImage *outputImage;

    QProgressBar* progressBar;
    QLabel* lblDeconvolutionTime;

    double radius, PSNR, feather, strength, motionLength, motionAngle;

    Blur* generateBlurInfo(bool previewMode);
    void updatePreviewDeconvolution();
    void scaleImage(double factor);
    void initControls();
    void createActions();
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    static const double MAX_IMAGE_PIXELS = 3000000; // 3 mega-pixels
    static const double MAX_IMAGE_DIMENSION = 2048; // 3 mega-pixels

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
    void about();
    void showOriginalPressed();
    void showOriginalReleased();
    void updateFullDeconvolution();
    void updateZoomControls();
    void updatePreviewImage(int deconvolutionTime);
    void updateProgress(int value);

};

#endif // MAINWINDOW_H
