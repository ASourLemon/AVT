#include "../include/Flare.h"
extern int WinX, WinY;

namespace domain {

float Flare::flareAmb[4] = {  0.0625f,  0.0625f,  0.0625f, 0.5f };
float Flare::flareDif[4] = {  0.25f,  0.25f,  0.25f, 0.5f };
float Flare::flareSpec[4] = {  0.25f,  0.25f,  0.25f, 0.5f };
float Flare::flareShininess = 10;

Flare::Flare() {

		support.setMaterialBlockName("Materials");
		support.setColor(VSResourceLib::DIFFUSE, flareDif);
		support.setColor(VSResourceLib::AMBIENT, flareAmb);
		support.setColor(VSResourceLib::SPECULAR, flareSpec);
		support.setColor(VSResourceLib::SHININESS, &flareShininess);
}

Flare::~Flare() {
}

void Flare::draw(VSMathLib* core, VSShaderLib* shader) {
/*	float aspectratio = 1;
	int lx, ly;
	int cx, cy;
	cx = WinX/2;
	cy = WinY/2;
	float maxflaredist = sqrt(cx^2 + cy^2); 
	float flaredist = sqrt((lx - cx)^2 + (ly - cy)^2);
	float distancescale = (maxflaredist - flaredist)/maxflaredist;
	
	float dx = cx + (cx - lx);
	float dy = cy + (cy - ly);
	
	for(int i = 0; i < 4; i++){
		int px = (1 - element.distance)*lx + element.distance*dx;
		int py = (1 - element.distance)*ly + element.distance*dy;
			
		float width = element.size * distancescale * flare.scale;

	 	if (width > flare.maxsize) {
	 		width = flare.maxsize;
	 	}

	 	float height = width * aspectratio;

	 	float alpha = element.alpha * distancescale;
	}
*/	
	/*
	 TODO: Implement this pseudo-code

	 lx, ly -> projected light on screen
	 cx, cy -> center of flare

	 maxflaredist = sqrt(cx^2 + cy^2);
	 flaredist = sqrt((lx - cx)^2 + (ly - cy)^2);

	 distancescale = (maxflaredist - flaredist)/maxflaredist);

	 dx = cx + (cx - lx);
	 dy = cy + (cy - ly);

     // TODO: Note: Element colours and textures is not done yet!
	 for each element in flare {
	 	px = (1 - element.distance)*lx + element.distance*dx;
	 	py = (1 - element.distance)*ly + element.distance*dy;

	 	width = element.size * distancescale * flare.scale;

	 	if (width > flare.maxsize) {
	 		width = flare.maxsize;
	 	}

	 	height = width * aspectratio;

	 	alpha = element.alpha * distancescale

	 	drawrectangle( element.texture, element.colour, alpha, px, py, dith, height);
	 }
	 */
}

void Flare::tick() {
}

} /* namespace domain */
