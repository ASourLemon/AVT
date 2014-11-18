#ifndef INCLUDE_FLARE_H_
#define INCLUDE_FLARE_H_

#include "drawable.h"

typedef struct{
public:
	int type;
	float size;
	float maxSize;
	float alpha;
	float distance;
}FlareElement;

typedef struct{
public:
	float x;
	float y;
	float z;
	float w;
}Vec4;

namespace domain {
class Flare: public Drawable {
public:
	Flare();
	~Flare();
	void addFlareElement(int type, float size, float maxSize, float alpha, float distance);
	void addLight(float pos[4]);
	void draw(VSMathLib* core, VSShaderLib* shader);
	void tick();

protected:
	VSResSurfRevLib support;

private:
	bool created;
	static float flareAmb[4];
	static float flareDif[4];
	static float flareSpec[4];
	static float flareShininess;
	std::vector<FlareElement*> flareElements;
	std::vector<Vec4*> lights;
	void drawFlare(VSMathLib* core, VSShaderLib* shader, float pos[4]);
};

}
#endif
