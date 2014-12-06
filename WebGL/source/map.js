
//var texture = loader.load( 'textures/grass.tga' );
//var material1 = new THREE.MeshPhongMaterial( { color: 0xffffff, map: texture1 } );


uniforms = {
 	color: { type: "v4", value: new THREE.Vector4(0.0, 1.0, 0.0, 1.0) },
};

material = new THREE.ShaderMaterial( {

	uniforms: uniforms,
	vertexShader: vertShader,
	fragmentShader: fragShader

} )

var Mapgeometry1 = new THREE.PlaneBufferGeometry( 20, 3);
var floor1 = new THREE.Mesh( Mapgeometry1, material );
floor1.translateX(4.0);

//Estrada
// uniforms = {
//  	color: { type: "v4", value: new THREE.Vector4(0.1, 0.2, 0.1, 1.0) },
// };

// material1 = new THREE.ShaderMaterial( {

// 	uniforms: uniforms,
// 	vertexShader: vertShader,
// 	fragmentShader: fragShader

// } )

// var Mapgeometry2 = new THREE.PlaneBufferGeometry( 20, 6);
// var road = new THREE.Mesh( Mapgeometry2, material1 );
// //plane.translateY(1.0);
// road.translateX(4.0);


