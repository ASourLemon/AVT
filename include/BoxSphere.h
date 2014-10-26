#ifndef BOXSPHERE_H_
#define BOXSPHERE_H_


namespace domain {

	class BoxSphere{

		public:
     
			BoxSphere(float raio, float *x, float *y);
			~BoxSphere();
     
			float get_x(){return *x;}
			float get_y(){return *y;}
 
			float get_raio(){return _raio;}
 
     
		private:
			float _raio, raio2;
			float *x, *y;
	
	};
}

#endif