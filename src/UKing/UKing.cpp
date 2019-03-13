
#include "UKing.h"

ofx::fixture::UKing::UFO::UFO(){
    
    // sets pan and tilt ranges
    setPanRange( -270, 270 );
    setTiltRange( -135, 135 );
    setColor(ofColor(255,255,255),false);
    
    // sets the max dmx channel used in dmx specification
    // this is needed for automatic address collision warning 
    setMaxDmxChannel( 14 );
}

std::string ofx::fixture::UKing::UFO::fixtureName(){
    return "UKING UFO";
}

void ofx::fixture::UKing::UFO::init(){
//    setDmx( 6, 89 );  // disabled blackout while pan/tilt moving
//    setDmx( 35, 255 );  // shutter open     
    
    // todo : set highest speed for panning and tilting 
}

void ofx::fixture::UKing::UFO::close(){

//    setDmx( 35, 9 );  // shutter close     
//
//    // resets to zero position
    pan = 0.0f;
    tilt = 0.0f; 
    dimmer = 0.0f;
    
    setDmxPan16bit( 1, 2 );
    setDmxTilt16bit( 3, 4 );
    setDmxDimmer16bit( 6, -1 );

    setDmx( 8, 0 );   // red
    setDmx( 9, 0 ); // green
    setDmx( 10, 0 );  // blue
    setDmx( 11, 0 );  // white

}

void ofx::fixture::UKing::UFO::update(){
    
    setDmxPan16bit( 1, 2 );
    setDmxTilt16bit( 3, 4 );
    setDmxDimmer16bit( 6, -1 );


    setDmx( 8, 255.0f - red );   // red
    setDmx( 9, 255.0f - green ); // green
    setDmx( 10, 255.0f - blue );  // blue
    setDmx( 11, 255.0f - white );  // white
    
    
//    float zones[3];
//    zones[0] = 1.0f;
//    zones[1] = ofMap( zoom, 0.0f,  0.15f, 0.0f, 1.0f, true );
//    zones[2] = ofMap( zoom, 0.15f, 0.30f, 0.0f, 1.0f, true );
//    float zoomval = ofMap( zoom, 0.3f, 1.0f, 0, 255, true );
//
//    for( int i=0; i<3; ++i ){
//        setDmx( 7+i*8,  red * zones[i] );
//        setDmx( 9+i*8,  green * zones[i]  );
//        setDmx( 11+i*8, blue * zones[i]  );
//        setDmx( 13+i*8, white * zones[i]  );
//    }
//
//    setDmx( 33, zoomval );
    
}
