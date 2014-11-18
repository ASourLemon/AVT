#ifndef BOXAABB_H_
#define BOXAABB_H_

#include "Vec3.h"


namespace domain {
	
	class BoxAABB{
	public:
		BoxAABB(Vec3 *center, float x_size, float y_size, float z_size);
		~BoxAABB();

		float get_x(){ return _center->getX(); }
		float get_y(){ return _center->getY(); }
		float get_z(){ return _center->getZ(); }
		float get_xmin(){ return get_x() - _x_size / 2; }
		float get_xmax(){ return get_x() + _x_size / 2; }
		float get_ymin(){ return get_y() - _y_size / 2; }
		float get_ymax(){ return get_y() + _y_size / 2; }
		float get_zmin(){ return get_z() - _z_size / 2; }
		float get_zmax(){ return get_z() + _z_size / 2; }
 
     
		private:
			Vec3 *_center;
			float _x_size, _y_size, _z_size;

	};
}
#endif