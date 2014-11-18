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

namespace domain {
class Flare: public Drawable {
public:
	Flare();
	~Flare();
	void addFlareElement(int type, float size, float maxSize, float alpha, float distance);
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
};

}
#endif
