#include "../include/Particle.h"

namespace domain{

#define frand()			((float)rand()/RAND_MAX)
#ifndef M_PI
#define M_PI 3.14159265
#endif

float Particle::bodyAmbient[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
float Particle:: bodyDiffuse[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
float Particle::bodySpec[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
float Particle::bodyShininess = 60;

Particle::Particle(): x(0.0), y(0.0), z(0.0), life(0.0f), created(false){

    
	body.setMaterialBlockName("Materials");
	body.setColor(VSResourceLib::SPECULAR, bodySpec);
	body.setColor(VSResourceLib::DIFFUSE, bodyDiffuse);
	body.setColor(VSResourceLib::AMBIENT, bodyAmbient);
	body.setColor(VSResourceLib::SHININESS, &bodyShininess);
	Respawn();
}

void Particle::Draw(VSMathLib* core){

	core->pushMatrix(VSMathLib::MODEL);
	core->translate(x, y, z);
	//core->scale(0.1f, 0.10f, 0.10f);
	if (!created) {
		body.createSphere(2.2f, 5.0f);
	}
	
	core->popMatrix(VSMathLib::MODEL);

}

bool Particle::Respawn(bool spawn){

    if ( life <= 0.0f  || spawn )
    {
        double v = 0.8*frand()+0.2;
        double phi = frand()*M_PI;
        double theta = 2.0*frand()*M_PI;
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
        vx = v * cos(theta) * sin(phi);
        vy = v * cos(phi);
        vz = v * sin(theta) * sin(phi);
        ax =  0.01f; /* just a little wind */
        ay = -0.15f; /* gravity pull */
        az =  0.0f;
        
        /* yelowish colour to be multiplied by the texture grey tone */
        r = 0.882f;
        g = 0.552f;
        b = 0.211f;
        
        life = .5f;		                        /* life granted to particle */
		fade = 0.0001515 + frand() * .000303;	    /* life decay */
        return true;
    }
    return false;
}

bool Particle::Update_particle(float elapsedTime, bool respawn){


    if ( respawn && life <= 0.0 )
        Respawn();
    if ( life > 0.0 )
    {
        float delta = elapsedTime * .00378;
        x += (vx * delta);
        y += (vy * delta);
        z += (vz * delta);
        vx += (ax * delta);
        vy += (ay * delta);
        vz += (az * delta);
        life -= (fade * elapsedTime );
        return true;
    }

    return false;
}

}