#ifndef BOXAABB_H_
#define BOXAABB_H_


namespace domain {
	
	class BoxAABB{
	public:
		BoxAABB(float *x, float *y, float *z, float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
		~BoxAABB();

		float get_x(){return *_x;}
		float get_y(){return *_y;}
		float get_z(){return *_z;}
		float get_xmin(){return *_x - _xmin;}
		float get_xmax(){return *_x + _xmax;}
		float get_ymin(){return *_y - _ymin;}
		float get_ymax(){return *_y + _ymax;}
		float get_zmin(){return *_z - _zmin;}
		float get_zmax(){return *_z + _zmax;}
 
     
		private:
 
		float *_x, *_y, *_z; //(x, y, z)
		float _xmin, _ymin, _xmax, _ymax, _zmin, _zmax; //Diferença do centro para os Xs e Ys max e min, varia com cada objecto
 


	};
}
#endif