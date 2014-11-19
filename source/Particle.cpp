#include "../include/Particle.h"

namespace domain{

#define frand()			((float)rand()/RAND_MAX)
#ifndef M_PI
#define M_PI 3.14159265
#endif

float Particle::bodyAmbient[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
float Particle::bodyDiffuse[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
float Particle::bodySpec[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
float Particle::bodyShininess = 60;

float Particle::bodyAmbientS[4] = { 0.08f, 0.08f, 0.12f, 0.8f };
float Particle::bodyDiffuseS[4] = { 0.6f, 0.6f, 0.8f, 0.8f };
float Particle::bodySpecS[4] = { 0.0f, 0.0f, 0.0f, 0.8f };
float Particle::bodyShininessS = 10;

Particle::Particle(): x(0.0), y(0.0), z(0.0), life(0.0f), created(false), color(0){

	Respawn(false, 0); //Default color = Red
}

void Particle::Draw(VSMathLib* core){
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureArray[9]);
	
	core->pushMatrix(VSMathLib::MODEL);
	core->translate(x, y, z);	
	core->rotate(frand(), 0, 1, 0);
	core->scale(0.025f, 0.025f, 0.025f);
	if (!created) {
		//body.createSphere(1.0f, 3.0f);
		body.createRectangle(2.0f, 2.0f);
		created = true;
	}
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	body.render();
	//glDisable(GL_BLEND);
	core->popMatrix(VSMathLib::MODEL);

}

void Particle::setColor(int c){
	 color = c;
	switch(color){
	case 0: //BLOOD!!
		body.setMaterialBlockName("Materials");
		body.setColor(VSResourceLib::SPECULAR, bodySpec);
		body.setColor(VSResourceLib::DIFFUSE, bodyDiffuse);
		body.setColor(VSResourceLib::AMBIENT, bodyAmbient);
		body.setColor(VSResourceLib::SHININESS, &bodyShininess);
		break;
	case 1: //SPLASH
		body.setMaterialBlockName("Materials");
		body.setColor(VSResourceLib::SPECULAR, bodySpecS);
		body.setColor(VSResourceLib::DIFFUSE, bodyDiffuseS);
		body.setColor(VSResourceLib::AMBIENT, bodyAmbientS);
		body.setColor(VSResourceLib::SHININESS, &bodyShininessS);
	}
}

bool Particle::Respawn(bool spawn, int c){
	
	setColor(c);

    if ( life <= 0.0f  || spawn ){

		if(color == 0){ //BLOOD
        double v = -0.8*frand()+0.2;
        double phi = frand()*M_PI;
        double theta = 2.0*frand()*M_PI;
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
        vx = -v * sin(theta);;
        vy = v * sin(phi) * cos(theta);
        vz = v * cos(phi) * sin(theta);//v * sin(theta) * sin(phi) - 3.0f;
        ax =  -0.15f; 
        ay = -0.15f; /* gravity pull */
        az =  0.0f;
        
        life = .20f;		                        /* life granted to particle */
		fade = 0.0001515 + frand() * .000303;	    /* life decay */
		}
		if(color == 1){ //SPLASH
			double v = -0.8*frand()+0.2;
			double phi = frand()*M_PI;
			double theta = 2.0*frand()*M_PI;
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
			vx = v * sin(phi) * cos(theta);
			vy = v * sin(theta);
			vz = v * cos(phi) * sin(theta);//v * sin(theta) * sin(phi) - 3.0f;
			ax =  -0.05f; 
			ay = -0.15f; /* gravity pull */
			az =  -0.05f;
        
			life = .15f;		                        /* life granted to particle */
			fade = 0.0001515 + frand() * .000303;	    /* life decay */
		}
        return true;
    }
    return false;
}

bool Particle::Update_particle(float elapsedTime, bool respawn){


    if ( respawn && life <= 0.0 )
        Respawn(false, 0);
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



