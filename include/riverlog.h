#ifndef INCLUDE_RIVERLOG_H_
#define INCLUDE_RIVERLOG_H_

#include "drawable.h"

#define LOG_RADIOS 2.0f
#define LOG_HEIGHT 10.0f

namespace domain {

class Riverlog : public Drawable {
private:
	VSResSurfRevLib body;


public:
	Riverlog(float x, float y, float z, int quality);
	void draw(VSMathLib* core);

};

} /* namespace domain */

#endif /* INCLUDE_RIVERLOG_H_ */
