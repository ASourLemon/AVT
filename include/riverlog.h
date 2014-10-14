#ifndef INCLUDE_RIVERLOG_H_
#define INCLUDE_RIVERLOG_H_

#include "drawable.h"

#define LOG_RADIOS 0.5f
#define LOG_HEIGHT 3.5f

namespace domain {

class Riverlog : public Drawable {
private:
	VSResSurfRevLib body;


public:
	Riverlog(float x, float y, float z, int quality);
	void draw(VSMathLib* core);
	void tick();

};

} /* namespace domain */

#endif /* INCLUDE_RIVERLOG_H_ */
