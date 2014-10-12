#ifndef INCLUDE_FROG_H_
#define INCLUDE_FROG_H_

#include "drawable.h"

#define FROG_RADIOS 3.0f
#define FROG_DIVISIONS 10.0f

namespace domain {

	class Frog : public Drawable{
	
		private:
			VSResSurfRevLib body;
			bool created;

		public:
			Frog();
			void draw(VSMathLib* core);
	
	};

}

#endif