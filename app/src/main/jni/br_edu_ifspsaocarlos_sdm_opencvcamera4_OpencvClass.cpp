#include <br_edu_ifspsaocarlos_sdm_opencvcamera4_OpencvClass.h>

JNIEXPORT void JNICALL Java_br_edu_ifspsaocarlos_sdm_opencvcamera4_OpencvClass_faceDetection
  (JNIEnv *, jclass, jlong addrRgba){
  Mat& frame = *(Mat*)addrRgba;

  detect(frame);
  }

void detect(Mat& frame){
   // String face_cascade_name = "/storage/emulated/0/Data/haarcascade_frontalface_alt.xml";
  //  String eyes_cascade_name = "/storage/emulated/0/Data/haarcascade_eye_tree_eyeglasses.xml";
    String face_cascade_name = "/storage/sdcard0/haarcascade_frontalface_alt.xml";
    String eyes_cascade_name = "/storage/sdcard0/haarcascade_eye_tree_eyeglasses.xml";
    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return; };
    if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading eyes cascade\n"); return; };

std::vector<Rect> faces;
    Mat frame_gray;
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;
        //-- In each face, detect eyes
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
        for ( size_t j = 0; j < eyes.size(); j++ )
        {
            Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
        }
    }
}