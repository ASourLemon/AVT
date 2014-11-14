#ifndef INCLUDE_FLARE_H_
#define INCLUDE_FLARE_H_

#include "drawable.h"

namespace domain {
class Flare: public Drawable {
public:
	Flare();
	~Flare();
	void draw(VSMathLib* core, VSShaderLib* shader);
	void tick();

protected:
	VSResSurfRevLib support;

private:
	static float flareAmb[4];
	static float flareDif[4];
	static float flareSpec[4];
	static float flareShininess;
};

}
#endif
