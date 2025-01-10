#ifndef DEVCAMERA_H
#define DEVCAMERA_H


#include <QObject>
#include <iostream>
#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QImage>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "FaceRecognition.h"

class DevCamera : public QThread
{
    Q_OBJECT
public:
    DevCamera();

    //Convert the Mat type of opencv to QImage
    QImage matToQimage( Mat frame );

    //The thread on which the QThread actually resides
    void run();

    //Turn off the camera
    void closeCamera();

signals:
    void signalNewQimageAvailable( QImage image );

    void signalQimageToServer( QImage image );
private:
    //Camera object
    VideoCapture       *m_pCamera;
    //Camera operation flag bit
    bool                m_bCameraRunning;
    //Wire program lock
    QMutex              m_objMutex;
    //Path of opencv face recognition library file
    QString             m_objXmlPath;
    //
    QImage              m_objQimg;
    // Mat type of opencv
    Mat                 m_objFrame;
    //Face recognition class
    FaceRecognition     m_objFaceRecog;
};

#endif // DEVCAMERA_H
