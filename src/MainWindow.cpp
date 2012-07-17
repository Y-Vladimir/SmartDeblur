#include "MainWindow.h"
#include "ui_MainWindow.h"

const QString MainWindow::appVersion = "0.48";
const double MainWindow::MAX_IMAGE_PIXELS = 3000000;
const double MainWindow::MAX_IMAGE_DIMENSION = 2048;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {


    ui->setupUi(this);

    resize(1000, 700);

    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    ui->scrollArea->setBackgroundRole(QPalette::Dark);
    ui->scrollArea->setWidget(imageLabel);

    radius = 9;
    PSNR = 0.001;

    workerThread = new WorkerThread();

    inputImage = NULL;
    outputImage = NULL;

    createActions();
    initControls();
    updateZoomControls();

    progressBar = new QProgressBar();
    progressBar->setValue(0);
    progressBar->setVisible(false);
    lblDeconvolutionTime = new QLabel();
    lblThreadsCount = new QLabel();
    lblImageSize = new QLabel();
    ui->statusBar->addWidget(lblThreadsCount);
    ui->statusBar->addWidget(lblImageSize);
    ui->statusBar->addWidget(lblDeconvolutionTime);
    ui->statusBar->addWidget(progressBar);

    workerThread->start();
}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updatePreviewImage(int deconvolutionTime) {
    progressBar->setValue(0);
    progressBar->setVisible(false);
    // Hack to force update resized pixmap
    imageLabel->setPixmap(0);
    imageLabel->setPixmap(QPixmap::fromImage(*outputImage));

    lblDeconvolutionTime->setText(" Last operation time: " + QString::number(deconvolutionTime) + " ms ");
}

void MainWindow::updateProgress(int value) {
    progressBar->setVisible(true);
    progressBar->setValue(value);
}


Blur *MainWindow::generateBlurInfo(bool previewMode) {
    Blur* blur;
    QImage* kernelImage;
    if (ui->comboBoxType->currentIndex() == 0) {
        FocusBlur* focusBlur = new FocusBlur();
        focusBlur->radius = radius;
        focusBlur->edgeFeather = feather;
        focusBlur->correctionStrength = strength;
        focusBlur->PSNR = PSNR;
        focusBlur->previewMode = previewMode;
        kernelImage = ImageUtils::buildKernelImage(focusBlur);
        blur = focusBlur;
    } else {
        MotionBlur* motionBlur = new MotionBlur();
        motionBlur->radius = motionLength;
        motionBlur->angle = motionAngle;
        motionBlur->PSNR = PSNR;
        motionBlur->previewMode = previewMode;
        kernelImage = ImageUtils::buildKernelImage(motionBlur);
        blur = motionBlur;
    }
    // Update kernel preview
    ui->labelKernelPreview->setPixmap(QPixmap::fromImage(kernelImage->scaled(ui->labelKernelPreview->size())));
    delete(kernelImage);

    return blur;
}


void MainWindow::updatePreviewDeconvolution() {
    Blur* blur = generateBlurInfo(true);
    if (inputImage) {
        workerThread->deconvolutionRequest(inputImage, outputImage, blur);
    }
}


void MainWindow::updateFullDeconvolution() {
    Blur* blur = generateBlurInfo(false);
    if (inputImage) {
        workerThread->deconvolutionRequest(inputImage, outputImage, blur);
    }
}

void MainWindow::radiusChanged() {
    radius = ui->sliderRadius->value()/10.0;
    ui->labelRadius->setText(QString::number(radius));
    updatePreviewDeconvolution();

}

void MainWindow::PSNRChanged() {
    // Non-linear transformation
    PSNR = pow(1.07, ui->sliderPSNR->value())/10000.0;
    ui->labelPSNR->setText(QString::number(ui->sliderPSNR->value()) + "%");
    updatePreviewDeconvolution();
}

void MainWindow::kernelFeatherChanged() {
    feather = ui->sliderKernelFeather->value();
    ui->labelFeather->setText(QString::number(feather) + "%");
    updatePreviewDeconvolution();;
}

void MainWindow::kernelStrengthChanged() {
    strength = ui->sliderKernelStrength->value();
    ui->labelStrength->setText(QString::number(strength) + "%");
    updatePreviewDeconvolution();;
}

void MainWindow::motionLengthChanged() {
    motionLength = ui->sliderMotionLength->value()/10.0;
    ui->labelMotionLength->setText(QString::number(motionLength));
    updatePreviewDeconvolution();

}

void MainWindow::motionAngleChanged() {
    motionAngle = ui->sliderMotionAngle->value();
    ui->labelMotionAngle->setText(QString::number(motionAngle) + "�");
    updatePreviewDeconvolution();
}

void MainWindow::defectTypeChanged(int type) {
    bool motionVisible = (type == 1);
    int yMotion1 = 29;
    int yMotion2 = 49;
    int yMotion3 = 69;

    bool focusVisible = (type == 0);
    int yFocus1 = 36;
    int yFocus2 = 63;

    // Set visibility
    ui->labelMotionLengthCaption->setVisible(motionVisible);
    ui->labelMotionLength->setVisible(motionVisible);
    ui->sliderMotionLength->setVisible(motionVisible);

    ui->labelMotionAngleCaption->setVisible(motionVisible);
    ui->labelMotionAngle->setVisible(motionVisible);
    ui->sliderMotionAngle->setVisible(motionVisible);

    ui->labelRadiusCaption->setVisible(focusVisible);
    ui->labelRadius->setVisible(focusVisible);
    ui->sliderRadius->setVisible(focusVisible);

    ui->labelFeatherCaption->setVisible(focusVisible);
    ui->labelFeather->setVisible(focusVisible);
    ui->sliderKernelFeather->setVisible(focusVisible);

    ui->labelStrengthCaption->setVisible(focusVisible);
    ui->labelStrength->setVisible(focusVisible);
    ui->sliderKernelStrength->setVisible(focusVisible);

    // Move controls
    if (type == 1) {
        // Out of Focus Blur
        ui->labelMotionLengthCaption->move( ui->labelMotionLengthCaption->x(), yMotion1);
        ui->labelMotionLength->move( ui->labelMotionLength->x(), yMotion1);
        ui->sliderMotionLength->move( ui->sliderMotionLength->x(), yMotion1);

        ui->labelMotionAngleCaption->move( ui->labelMotionAngleCaption->x(), yMotion2);
        ui->labelMotionAngle->move( ui->labelMotionAngle->x(), yMotion2);
        ui->sliderMotionAngle->move( ui->sliderMotionAngle->x(), yMotion2);

        ui->labelPSNRCaption->move( ui->labelPSNRCaption->x(), yMotion3);
        ui->labelPSNR->move( ui->labelPSNR->x(), yMotion3);
        ui->sliderPSNR->move( ui->sliderPSNR->x(), yMotion3);
    } else {
        // Motion Blur
        ui->labelRadiusCaption->move( ui->labelRadiusCaption->x(), yFocus1);
        ui->labelRadius->move( ui->labelRadius->x(), yFocus1);
        ui->sliderRadius->move( ui->sliderRadius->x(), yFocus1);

        ui->labelPSNRCaption->move( ui->labelPSNRCaption->x(), yFocus2);
        ui->labelPSNR->move( ui->labelPSNR->x(), yFocus2);
        ui->sliderPSNR->move( ui->sliderPSNR->x(), yFocus2);
    }

    updateFullDeconvolution();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
 {
     event->acceptProposedAction();
 }

 void MainWindow::dragMoveEvent(QDragMoveEvent *event)
 {
     event->acceptProposedAction();
 }


void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) {
        return;
    }

    QString fileName = urls.first().toLocalFile();
    if (fileName.isEmpty()) {
        return;
    }
    event->acceptProposedAction();
    openFile(fileName);

}

void MainWindow::openFile(QString fileName) {
    delete(inputImage);
    delete(outputImage);
    inputImage = new QImage(fileName);

    if (inputImage->isNull()) {
        QMessageBox::information(this, tr("Smart Deblur"),
                                 tr("Cannot load %1.").arg(fileName));
        return;
    }

    // Resize image if it's necessary
    int width = inputImage->width();
    int height = inputImage->height();

    if (width > MAX_IMAGE_DIMENSION || height > MAX_IMAGE_DIMENSION) {
        double resizeRatio = qMin(MAX_IMAGE_DIMENSION/width, MAX_IMAGE_DIMENSION/height);
        width = width*resizeRatio;
        height = height*resizeRatio;

        width += width % 2;
        height += height % 2;

        inputImage = new QImage(inputImage->scaled(
                                    width, height,
                                    Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

        QMessageBox::information(this, tr("Smart Deblur"),
                                 tr("Image was resized to %1 * %2 because of performance reason")
                                 .arg(width).arg(height));
    }

    // Crop image if sizes are odd
    if (width%2 != 0 || height%2 !=0) {
        width -= width % 2;
        height -= height % 2;
        inputImage = new QImage(inputImage->copy(0,0, width, height));
    }

    lblImageSize->setText(tr(" Image Size: %1 x %2 ").arg(inputImage->width()).arg(inputImage->height()));

    ui->btnSave->setEnabled(true);
    ui->btnShowOriginal->setEnabled(true);

    outputImage = new QImage(inputImage->width(), inputImage->height(), QImage::Format_RGB32);
    lblThreadsCount->setText(tr(" Threads: %1 ").arg(workerThread->initFFT(inputImage)));
    imageLabel->setPixmap(QPixmap::fromImage(*inputImage));
    updateFullDeconvolution();
    ui->checkBoxFitToWindow->setChecked(true);
    fitToWindow();
}

void MainWindow::open() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty()) {
        openFile(fileName);
    }
}

void MainWindow::save() {
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save File"), QDir::currentPath(),tr("Images (*.png *.jpg)"));
    if (!fileName.isEmpty()) {
        outputImage->save(fileName);
    }
}

void MainWindow::zoomIn() {
    ui->checkBoxFitToWindow->setChecked(false);
    scaleImage(scaleFactor*2.0);
}

void MainWindow::zoomOut() {
    ui->checkBoxFitToWindow->setChecked(false);
    scaleImage(scaleFactor*0.5);
}

void MainWindow::actualSize() {
    ui->checkBoxFitToWindow->setChecked(false);
    scaleFactor = 1;
    scaleImage(scaleFactor);
}

void MainWindow::fitToWindow() {
    if (!imageLabel->pixmap()) {
        return;
    }

    double factor = qMin(
                ui->scrollArea->width()/((double)inputImage->width()),
                ui->scrollArea->height()/((double)inputImage->height()));
    if (factor > 1) {
        factor = 1;
    }
    scaleImage(factor);
}

void MainWindow::about() {
    QMessageBox::about(this, tr("About SmartDeblur"),
                       tr("<p>The <b>SmartDeblur</b> is a tool for restoration of defocused and blurred images. "
                          "Algorithm based on Wiener deconvolution.<br>"
                          "Supported defect types:<ul>"
                          "<li>Out of Focus blur (with kernel deep tuning)</li>"
                          "<li>Motion blur</li></ul></p>"
                          "<p>SmartDeblur uses the FFTW library which provides fast fourier tranformation implementation. "
                          "See <a href='www.fftw.org'>www.fftw.org</a> for details </p>"
                          "<p>Author: <b>Vladimir Yuzhikov</b> (yuvladimir@gmail.com), the latest sources and binaries are available on: <a href='https://github.com/Y-Vladimir/SmartDeblur'>https://github.com/Y-Vladimir/SmartDeblur</a></p>"
                          "<p><b>Version: %1</b></p>").arg(appVersion));

}

void MainWindow::showOriginalPressed() {
    imageLabel->setPixmap(QPixmap::fromImage(*inputImage));
}

void MainWindow::showOriginalReleased() {
    imageLabel->setPixmap(QPixmap::fromImage(*outputImage));
}


void MainWindow::scaleImage(double factor) {
    if (!imageLabel->pixmap()) {
        return;
    }

    scaleFactor =factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(ui->scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(ui->scrollArea->verticalScrollBar(), factor);

    ui->btnZoomIn->setEnabled(scaleFactor < 1.0);
    ui->btnZoomOut->setEnabled(scaleFactor > 0.3);       
}

void MainWindow::initControls() {
    ui->sliderRadius->setValue(1);
    ui->sliderPSNR->setValue(40);
    ui->sliderKernelStrength->setValue(0);
    ui->sliderKernelFeather->setValue(20);

    ui->sliderMotionLength->setValue(1);
    ui->sliderMotionAngle->setValue(0);

    ui->comboBoxType->setCurrentIndex(0);
    defectTypeChanged(0);

    ui->btnSave->setEnabled(false);
    ui->btnShowOriginal->setEnabled(false);

    this->setAcceptDrops(true);
}

void MainWindow::createActions() {
    connect(ui->btnZoomIn, SIGNAL(clicked()), this, SLOT(zoomIn()));
    connect(ui->btnZoomOut, SIGNAL(clicked()), this, SLOT(zoomOut()));
    connect(ui->btnZoomNormal, SIGNAL(clicked()), this, SLOT(actualSize()));
    connect(ui->checkBoxFitToWindow, SIGNAL(stateChanged(int)), SLOT(updateZoomControls()));

    connect(ui->btnOpen, SIGNAL(clicked()), this, SLOT(open()));
    connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(save()));
    connect(ui->btnAbout, SIGNAL(clicked()), this, SLOT(about()));

    connect(ui->sliderRadius, SIGNAL(valueChanged(int)), this, SLOT(radiusChanged()));
    connect(ui->sliderKernelFeather, SIGNAL(valueChanged(int)), this, SLOT(kernelFeatherChanged()));
    connect(ui->sliderKernelStrength, SIGNAL(valueChanged(int)), this, SLOT(kernelStrengthChanged()));
    connect(ui->sliderMotionLength, SIGNAL(valueChanged(int)), this, SLOT(motionLengthChanged()));
    connect(ui->sliderMotionAngle, SIGNAL(valueChanged(int)), this, SLOT(motionAngleChanged()));
    connect(ui->sliderPSNR, SIGNAL(valueChanged(int)), this, SLOT(PSNRChanged()));

    connect(ui->sliderRadius, SIGNAL(sliderReleased()), this, SLOT(updateFullDeconvolution()));
    connect(ui->sliderKernelFeather, SIGNAL(sliderReleased()), this, SLOT(updateFullDeconvolution()));
    connect(ui->sliderKernelStrength, SIGNAL(sliderReleased()), this, SLOT(updateFullDeconvolution()));
    connect(ui->sliderPSNR, SIGNAL(sliderReleased()), this, SLOT(updateFullDeconvolution()));
    connect(ui->sliderMotionLength, SIGNAL(sliderReleased()), this, SLOT(updateFullDeconvolution()));
    connect(ui->sliderMotionAngle, SIGNAL(sliderReleased()), this, SLOT(updateFullDeconvolution()));

    connect(ui->btnShowOriginal, SIGNAL(pressed()), this, SLOT(showOriginalPressed()));
    connect(ui->btnShowOriginal, SIGNAL(released()), this, SLOT(showOriginalReleased()));

    connect(ui->comboBoxType, SIGNAL(currentIndexChanged(int)), this, SLOT(defectTypeChanged(int)));

    connect(workerThread, SIGNAL(deconvolutionFinished(int)), SLOT(updatePreviewImage(int)));
    connect(workerThread->getDeconvolutionTool(), SIGNAL(progressEvent(int)), this, SLOT(updateProgress(int)));
}

void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor) {
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

void MainWindow::resizeEvent(QResizeEvent *resizeEvent) {
    if (ui->checkBoxFitToWindow->isChecked()) {
        fitToWindow();
    }
}

void MainWindow::updateZoomControls() {
    bool fitChecked = ui->checkBoxFitToWindow->isChecked();

    ui->scrollArea->setVerticalScrollBarPolicy(!fitChecked ? Qt::ScrollBarAsNeeded : Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setHorizontalScrollBarPolicy(!fitChecked ? Qt::ScrollBarAsNeeded : Qt::ScrollBarAlwaysOff);

    if (fitChecked) {
        fitToWindow();
    }
}
