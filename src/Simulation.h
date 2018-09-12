
#pragma once 

#include "ofMain.h"
#include "Dimmer.h"
#include "Head.h"

namespace ofx{ namespace fixture {
    
class Simulation {

public:  
    Simulation();

    void setStage();
    void setStage( float stageWidht, float stageHeight, float stageDepth );
    
    void setGraphics( int x, int y, int w, int h );
    void moveGraphics( int x, int y );

    void add( Head & head );
    void add( Dimmer & dimmer );   
    
    virtual void drawObjects(){};
    
    void update();
    void draw();
    
    void enable();
    void disable();
    
    void setDrawAddress( bool drawAddress );
    void toggleDrawAddress();
    
private:

    ofEasyCam camera;
    ofFbo fbo;

    ofPlanePrimitive floor;
    ofPlanePrimitive wall;
    
    ofMaterial material;

    std::vector<Dimmer*> dimmers;
    std::vector<Head*>   heads;
    
    int gx;
    int gy;
    
    bool bActive;
    
};
    
    
}}
