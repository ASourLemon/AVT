#ifndef BOXSPHERE_H_
#define BOXSPHERE_H_


namespace domain {

	class BoxSphere{

		public:
     
			BoxSphere( float center[3], float raio);
			~BoxSphere();
     
			float get_center(){return *_center;}
			//float get_y(){return *y;}
 
			float get_raio(){return _raio;}
 
     
		private:
			float _raio, raio2;
			float _center[3];
	
	};
}

#endif