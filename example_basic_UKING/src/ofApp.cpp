#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
   
    ofSetWindowTitle( "moving heads simulation" );
	ofSetVerticalSync(true);
    
    gui.setup("settings", "settings.xml", ofGetWidth()-220, 20 );
    positions.setup("positions", "positions.xml", ofGetWidth()-440, 20 );
 
    transitioning = 0;
    cursor = 0.0f;



//    dmx.connect( "tty.usbserial-EN092227", 512 ); // use the name
    dmx.connect(0, 512); // or use a number

    // -------------------- set up manager --------------------------  
   
    // simulated world boundaries, I like to think it as centimeters
    float sw = 1200.0f;
    float sh = 600.0f;
    float sd = 800.0f;
    
    // ==== WARNING!!! call this function before all the others =====
    manager.setup( dmx, sw, sh, sd ); 
    // ==============================================================  
    
    // use this if you don't want simulated graphics 
    // manager.setup( dmx, sw, sh, sd, false ); 
    
    manager.simulation.setStage( sw, 500, sd ); // stage can be smaller than boundaries
    manager.simulation.setGraphics( 20, 20, 900, 800 ); 
    manager.simulation.setDrawAddress( true );
    
    // use minimal 2d graphics 
    //manager.simulation.enable3DGraphics( false ); 
        
    // use this to change the floor or wall color
    // manager.simulation.setFloorColor( ofColor(40) );
    // manager.simulation.setWallColor( ofColor(255, 200, 200 ) );
    
    // -------------------- heads setup -----------------------------
    heads.resize(4);

    heads[0].setup( dmx, 1 );
    heads[1].setup( dmx, 15 );
    heads[2].setup( dmx, 29 );
    heads[3].setup( dmx, 43 );
    
    heads[0].position.set( glm::vec3( sw*0.25f, sh, sd*0.25f) );
    heads[1].position.set( glm::vec3( sw*0.75f, sh, sd*0.25f) );
    heads[2].position.set( glm::vec3( sw*0.75f, sh, sd*0.75f) );
    heads[3].position.set( glm::vec3( sw*0.25f, sh, sd*0.75f) );
 
    for( auto & head : heads ){ head.dimmer = 1.0f; }
 
    for( auto & fixt : heads ){ manager.add( fixt ); }


    // adds misc parameters to gui ----------------------------------
    gui.add( manager.controls );
    gui.add( ofx::fixture::Dimmer::bDrawAddress ); // static ofParameter<bool>
    gui.add( bFloorDemo.set("floor demo", false) );
    gui.add( bSearchlightDemo.set("search demo", false) );

    
    gui.add( manager.multiple );
//    gui.loadFromFile("gui.xml");
//    gui.minimizeAll();
    
    bShowGui = true;
    
    positions.add( manager.positions );
//    positions.minimizeAll();
    positions.loadFromFile( "positions.xml" );

    circle_angle = 0;
    
    for( auto & head : heads ){
        head.dimmer = 0;
    }
}

void ofApp::exit(){
    for( auto & head : heads ){
        head.close();
    }
}
//--------------------------------------------------------------
void ofApp::update(){
    
    if( bFloorDemo ){ // chase a noise generated target 
        for( auto & head : heads ){
            head.setTarget( glm::vec3( 
                    ofNoise(ofGetElapsedTimef()*0.08f, 0) * 1200.0f, 
                    0.0f,
                    ofNoise(ofGetElapsedTimef()*0.08f, 2) * 800.0f
            ));  
            
//            head.setColor(ofColor(255,255,255));
        }        
    } else if(bSearchlightDemo == true){
        
        int circle_radius = 500;
        circle_angleStep = 0.3;
        
        float center_x = 325;
        float center_z = 525;
        float x = center_x + (circle_radius) * cos(ofDegToRad(circle_angle));
        float z = center_z + (circle_radius) * sin(ofDegToRad(circle_angle));
        
        circle_angle+=circle_angleStep;
        ofLog()<<"circle_angle "<<circle_angle;
//        circle_angle = ofWrapDegrees(circle_angle,0,360);
        
        for( auto & head : heads ){
            head.setTarget( glm::vec3(x,600.0f,z) );  
            
//            head.setColor(ofColor(255,255,255));
        }
    }
//    manager.update( false ); // don't send dmx in this example
    
    // usually you call this
     manager.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    
    manager.draw();
    
    
    
    if(bShowGui == true){
        positions.draw();
        gui.draw();
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 'g'){
        bShowGui = !bShowGui;
        
        if(bShowGui == false){
            gui.saveToFile("gui.xml");
             positions.saveToFile( "positions.xml" );
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
