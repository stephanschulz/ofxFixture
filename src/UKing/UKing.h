
#pragma once

#include "ofxFixture.h"

namespace ofx{ namespace fixture{ namespace UKing{
    
    class UFO : public ofx::fixture::Head {
        
    public:
        
        UFO();
        
        std::string fixtureName() override;
        
        void init() override;
        void update() override;
        void close() override;
        
    };
    
}}}
