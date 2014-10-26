#ifndef BOXAABB_H_
#define BOXAABB_H_


namespace domain {
	
	class BoxAABB{

		BoxAABB(float *x, float *y, float xmin, float ymin, float xmax, float ymax);
		~BoxAABB();

		float get_x(){return *x;}
		float get_y(){return *y;}
		float get_xmin(){return *x-_xmin;}
		float get_ymin(){return *y-_ymin;}
		float get_xmax(){return *x+_xmax;}
		float get_ymax(){return *y+_ymax;}
 
     
     
		private:
 
		float *x, *y;
		float _xmin, _ymin, _xmax, _ymax; //Diferença do centro para os Xs e Ys max e min, varia com cada objecto
 


	};
}
#endif