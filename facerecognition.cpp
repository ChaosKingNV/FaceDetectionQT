#include "facerecognition.h"

FaceRecognition::FaceRecognition(QObject *parent) : QObject(parent)
{
    initFaceRecog();
    initTimer();
}

void FaceRecognition::initFaceRecog()
{
    m_bRecognition = true;
    bool ok = setXmlFilePath( "../../resources/haarcascade_frontalface_alt2.xml" );
    if( !ok )
    {
        qDebug() << " xml file not existed";
        return;
    }

    //Load character training model
    if( !m_objFace_cascade.load( m_qsXmlFilePath.toLocal8Bit().toStdString() ) )
    {
        qDebug() << " load xml file failed ";
        return;
    }
    qDebug() << " load xml file success ";
}

void FaceRecognition::initTimer()
{
    m_timer.setInterval( 300 );
    connect( &m_timer, &QTimer::timeout, this, &FaceRecognition::onTimerTimeout );
    m_timer.start();
}

bool FaceRecognition::setXmlFilePath( QString path )
{
    QFile file( path );
    QFileInfo fileInfo( file );
    if( !fileInfo.exists() )
    {
        return false;
    }
    m_qsXmlFilePath = fileInfo.absoluteFilePath();
    qDebug() << "xml path = " << m_qsXmlFilePath;
    return true;
}

QString FaceRecognition::getXmlFilePath()
{
    return m_qsXmlFilePath;
}

void FaceRecognition::setFrame( Mat frame )
{
    if( frame.empty() )
    {
        qDebug() << " empty frame ";
        return;
    }
    m_objFrame = frame;
}

Mat FaceRecognition::paintRect( Mat frame )
{
    if( !m_bRecognition )
    {
        return frame;
    }
    setFrame( frame );
    m_veFaces.clear();
    Mat grayImg;
    Mat outPutGrayImg;
    Mat smallImg;

    //Convert to grayscale
    cvtColor( m_objFrame, grayImg, cv::COLOR_BGR2GRAY );

//    resize( grayImg, smallImg, Size(), 0.9, 0.9, INTER_LINEAR );

    //Histogram equalization to improve image quality
    equalizeHist( grayImg, outPutGrayImg );

//    cout<< " size = " <<outPutGrayImg.size() << endl;

//    qint64 time1 = QDateTime::currentMSecsSinceEpoch();

    //Start face detection. The Size will affect the performance of face detection. It is recommended to set the minimum Size slightly larger
    m_objFace_cascade.detectMultiScale( outPutGrayImg, m_veFaces, 1.1, 3, 0, Size( 100, 100 ), Size( 300, 300 ) );

    //Store the number of faces in the image to determine whether to send the image to the server through http in the run() function of DevCamera.cpp
    m_iFaces = m_veFaces.size();
//    qDebug() << " there are " << m_veFaces.size() << " faces ";

//    qDebug() << QString( " coast %1 " ).arg( QDateTime::currentMSecsSinceEpoch() - time1 );

    for( size_t i = 0; i < m_veFaces.size(); i++ )
    {
        Rect tmpFace = m_veFaces[ i ];
        Point point1( tmpFace.x, tmpFace.y );
        Point point2( tmpFace.x + tmpFace.width, tmpFace.y + tmpFace.height );
        rectangle( m_objFrame, point1, point2, Scalar( 255, 0, 0 ) );
    }

    return m_objFrame;
}

int FaceRecognition::getFaces()
{
    return m_iFaces;
}

void FaceRecognition::setHttpAvalable( bool state )
{
    m_bHttpAvalable = state;
}

bool FaceRecognition::getHttpAvailable()
{
    return m_bHttpAvalable;
}

void FaceRecognition::onTimerTimeout()
{
    m_bRecognition = !m_bRecognition;
}
