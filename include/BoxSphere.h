#ifndef BOXSPHERE_H_
#define BOXSPHERE_H_


namespace domain {

	class BoxSphere{

		public:
     
			BoxSphere(float *x, float *y, float *z, float raio);
			~BoxSphere();
     
			
			float get_x(){return *_x;}
			float get_y(){return *_y;}
			float get_z(){return *_z;}
 
			float get_raio(){return _raio;}
 
     
		private:
			float _raio, raio2;
			float *_x, *_y, *_z;
	
	};
}

#endif