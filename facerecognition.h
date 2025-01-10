#ifndef FACERECOGNITION_H
#define FACERECOGNITION_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <vector>
#include <QDateTime>
#include <iostream>
#include <QTimer>

#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;


class FaceRecognition : public QObject
{
    Q_OBJECT

public:
    explicit FaceRecognition(QObject *parent = nullptr);

    //Initialize face recognition
    void initFaceRecog();

    //Initialization timer
    void initTimer();

    //Set the xml file of opencv face recognition library
    bool setXmlFilePath( QString path );

    //Get the path of opencv face recognition library file
    QString getXmlFilePath();

    //Set the value of the member variable m_objFrame
    void setFrame( Mat frame );

    // Use a rectangle to frame the face in the image
    Mat paintRect( Mat frame );

    //Get the number of faces
    int getFaces();

    //http flag bit, used to wait for the returned result
    void setHttpAvalable( bool state );

    //Get the flag bit result of http
    bool getHttpAvailable();

signals:

public slots:
    void onTimerTimeout();

private:
    //Face classifier
    CascadeClassifier m_objFace_cascade;
    //Mat of opencv
    Mat m_objFrame;
    //xml file path of face recognition database
    QString m_qsXmlFilePath;
    //Store face frame
    vector<Rect> m_veFaces;
    //Whether to identify the flag bit
    bool m_bRecognition;
    //Number of faces
    int m_iFaces;
    //timer
    QTimer m_timer;
    // Flag bit waiting for http to return results
    bool m_bHttpAvalable;

};

#endif // FACERECOGNITION_H
