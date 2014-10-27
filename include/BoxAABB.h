#ifndef BOXAABB_H_
#define BOXAABB_H_


namespace domain {
	
	class BoxAABB{
	public:
		BoxAABB(float *center, float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
		~BoxAABB();

		float get_x(){return *_center;}
		//float get_y(){return *y;}
		float get_xmin(){return _center[0]-_xmin;}
		float get_xmax(){return _center[0]+_xmax;}
		float get_ymin(){return _center[1]-_ymin;}
		float get_ymax(){return _center[1]+_ymax;}
		float get_zmin(){return _center[0]-_zmin;}
		float get_zmax(){return _center[0]+_zmax;}
 
     
		private:
 
		float _center[3]; //(x, y, z)
		float _xmin, _ymin, _xmax, _ymax, _zmin, _zmax; //Diferença do centro para os Xs e Ys max e min, varia com cada objecto
 


	};
}
#endif