#include "../include/Flare.h"
extern int WinX, WinY;

namespace domain {

float Flare::flareAmb[4] = {  0.0625f,  0.0625f,  0.0625f, 0.5f };
float Flare::flareDif[4] = {  0.25f,  0.25f,  0.25f, 0.5f };
float Flare::flareSpec[4] = {  0.25f,  0.25f,  0.25f, 0.5f };
float Flare::flareShininess = 10;

Flare::Flare() : created(false) {
		support.setMaterialBlockName("Materials");
		support.setColor(VSResourceLib::DIFFUSE, flareDif);
		support.setColor(VSResourceLib::AMBIENT, flareAmb);
		support.setColor(VSResourceLib::SPECULAR, flareSpec);
		support.setColor(VSResourceLib::SHININESS, &flareShininess);
}

Flare::~Flare() {
}

void Flare::addFlareElement(int type, float size, float maxSize, float alpha, float distance){
	FlareElement* fl = new FlareElement();
	fl->type = type;
	fl->size = size;
	fl->alpha = alpha;
	fl->distance = distance;
	fl->maxSize = maxSize;
	
	flareElements.push_back(fl);
}

void Flare::addLight(float pos[4]){
	Vec4* vc = new Vec4();
	vc->x = pos[0];
	vc->y = pos[1];
	vc->z = pos[2];
	vc->w = pos[3];
	lights.push_back(vc);
}

void Flare::drawFlare(VSMathLib* core, VSShaderLib* shader, float pos[4]) {

	//hardcooded light pos
	float p_p[4];
	
	//get viewport coordinates [-1, 1]
	core->multMatrixPoint(VSMathLib::PROJ_VIEW_MODEL, pos, p_p);
	p_p[0] /= p_p[3];
	p_p[1] /= p_p[3];
	
	//transform to window coordinates [0, WinX] and [0, WinY] 
	p_p[0] *= 0.5;
	p_p[0] += 0.5;
	p_p[0] *= WinX;
	p_p[1] *= 0.5;
	p_p[1] += 0.5;
	p_p[1] *= WinY;
	
	if(p_p[0] < 0.0 || p_p[0] > WinX || p_p[1] < 0.0 || p_p[1] > WinX || p_p[2] < 0.0){
		//printf("x: %.1f, y: %.1f, z: %.1f\n", (p_p[0]),  p_p[1], p_p[2]); 
		//printf("Discarded\n");
		return;
	} 
	//printf("x: %.1f, y: %.1f, z: %.1f\n", (p_p[0]),  p_p[1], p_p[2]); 

	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	
	
	core->pushMatrix(VSMathLib::MODEL);
	core->loadIdentity(VSMathLib::MODEL);
	
	core->pushMatrix(VSMathLib::VIEW);
	core->loadIdentity(VSMathLib::VIEW);
	
	core->pushMatrix(VSMathLib::PROJECTION);	
	core->loadIdentity(VSMathLib::PROJECTION);
	core->ortho(.0f, float(WinX), .0f, float(WinY), -1.0f, 1.0f);
	
	
	
	float radio = WinX/WinY;
	
	
	float lx = p_p[0];
	float ly = p_p[1];
	
	
	float cx = WinX*0.5f;
	float cy = WinY*0.5f;
	
	//compute flare distance from center
	float maxflaredist = sqrt(cx*cx + cy*cy);
	float flaredist = sqrt((lx - cx)*(lx - cx) + (ly - cy)*(ly - cy));
	
	//compute scalling
	float distancescale = (maxflaredist - flaredist) / maxflaredist;
	
	float dx = cx + (cx - lx);
	float dy = cy + (cy - ly);

	for(int i = 0; i < flareElements.size(); i++){
		
		//position is interpolated between (lx,ly) and (dx,dy)
		float el_distance = flareElements.at(i)->distance;
		
		float px = (1.0f - el_distance)*lx + el_distance*dx;
		float py = (1.0f - el_distance)*ly + el_distance*dy;
		
		
		float w = flareElements.at(i)->size * distancescale;
		if(w >  flareElements.at(i)->maxSize){
			w = flareElements.at(i)->maxSize;
		}
		float h = w * radio;
		
		
		float alpha = flareElements.at(i)->alpha;
		
		core->pushMatrix(VSMathLib::MODEL);
		core->loadIdentity(VSMathLib::MODEL);
		core->translate(px, py, 0);	//flare position
		core->scale(w, h, 1.0f);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, FlareTextureArray[flareElements.at(i)->type]);

		glEnable(GL_BLEND); 
		glBlendFunc (GL_ONE, GL_ONE);
		support.render();
		glDisable(GL_BLEND);		
		core->popMatrix(VSMathLib::MODEL);	
	}
	 
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	core->popMatrix(VSMathLib::MODEL);	
	core->popMatrix(VSMathLib::VIEW);
	core->popMatrix(VSMathLib::PROJECTION);
}


void Flare::draw(VSMathLib* core, VSShaderLib* shader) {
	if(!created){
		support.createRectangle(20.0f, 20.0f);
		created = true;
	} 

	float pos[4];
	for(unsigned int i = 0; i < lights.size(); i++){
		pos[0] = lights.at(i)->x;
		pos[1] = lights.at(i)->y;
		pos[2] = lights.at(i)->z;
		pos[3] = lights.at(i)->w;
		//printf("Light - %u \n", i);
		drawFlare(core, shader, pos);
	}
}

void Flare::tick() {
}

} /* namespace domain */
