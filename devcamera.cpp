#include "devcamera.h"

DevCamera::DevCamera()
{
    m_pCamera = new VideoCapture();
}

void DevCamera::run()
{
    if( !m_pCamera->isOpened() )
    {
        m_pCamera->open( 0 );
    }
    m_bCameraRunning = true;
    while( true )
    {
        m_objMutex.lock();
        if( !m_bCameraRunning )
        {
            m_objMutex.unlock();
            break;
        }
        m_objMutex.unlock();
        *m_pCamera >> m_objFrame;

        //Face detection
        m_objFrame = m_objFaceRecog.paintRect( m_objFrame );

        QImage img = matToQimage( m_objFrame );
        if( m_objFaceRecog.getFaces() > 0 )
        {
            emit signalQimageToServer( img );
        }
        emit signalNewQimageAvailable( img );
        QThread::msleep( 20 );
    }
    m_pCamera->release();
    m_bCameraRunning = false;
    qDebug() << " break while ";
}

void DevCamera::closeCamera()
{
    m_objMutex.lock();
    m_bCameraRunning = false;
    m_objMutex.unlock();
}

QImage DevCamera::matToQimage( Mat frame )
{
    QImage img;

    if (frame.channels()==3)
    {
        cvtColor(frame, frame, cv::COLOR_BGR2RGB);
        img = QImage((const unsigned char *)(frame.data), frame.cols, frame.rows,
                frame.cols*frame.channels(), QImage::Format_RGB888);
    }
    else if (frame.channels()==1)
    {
        img = QImage((const unsigned char *)(frame.data), frame.cols, frame.rows,
                frame.cols*frame.channels(), QImage::Format_ARGB32);
    }
    else
    {
        img = QImage((const unsigned char *)(frame.data), frame.cols, frame.rows,
                frame.cols*frame.channels(), QImage::Format_RGB888);
    }

    return img;
}
