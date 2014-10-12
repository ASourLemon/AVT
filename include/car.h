#ifndef INCLUDE_CAR_H_
#define INCLUDE_CAR_H_

#include "drawable.h"

namespace domain {
	class Car : public Drawable {
	private:
		VSResSurfRevLib body;
		float x;
		float y;
		float z;
		bool created;


	public:
		Car(float x, float y, float z);
		void draw(VSMathLib* core);

	};

}
#endif