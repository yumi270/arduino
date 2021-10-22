window.addEventListener("DOMContentLoaded", init);
setTimeout("updateStatus()",10);
var roll ;
var pitch ;
var yaw ;
function updateStatus(){
	var xhr = new XMLHttpRequest();
	// --------------------------------------------------------
	xhr.onreadystatechange =
		function (){
			//	  ready http responce
			if(xhr.readyState == 4){
				if(xhr.status == 200){
					//	  xhr success
					var res = xhr.responseText ;
					
					if(xhr.responseText){
						var tmp  = res.split(",");//,xx,の数字を取りたす
						roll  = parseFloat(tmp[0]);
						pitch = parseFloat(tmp[1])*-1; // Atom Matrix Rotation Fix
						yaw   = parseFloat(tmp[2]);
						
						button= parseFloat(tmp[3]);//書かないと０

						zero_roll  = parseFloat(tmp[4]);
						zero_pitch = parseFloat(tmp[5])*-1; // Atom Matrix Rotation Fix
						zero_yaw   = parseFloat(tmp[6]);


                        roll  = roll.toFixed(2);
						pitch = pitch.toFixed(2);
						yaw   = yaw.toFixed(2);

						button   = button.toFixed(2);

						zero_roll  = zero_roll.toFixed(2);
						zero_pitch = zero_pitch.toFixed(2);
						zero_yaw   = zero_yaw.toFixed(2);
						console.log("/roll=" + roll + "/pitch="+pitch+"/yaw="+yaw+"/zero_roll=" + zero_roll + "/zero_pitch="+zero_pitch+"/zero_yaw="+zero_yaw);
						//ソースみるものCTRL+F12
					}else{
						console.log("read empty data");
					}	
				}
			}
		};
	// --------------------------------------------------------
	var url = "/angle" + "?sn=" + Math.random() ;
	//randomやらないとエラー
	xhr.open("GET" , url , true);
	xhr.send();

	setTimeout("updateStatus()",10);
}
function init() {
	//	three rendrer 三渲染
	const renderer = new THREE.WebGLRenderer({//WebGL 渲染器使用WebGL显示您精心制作的场景 。
		canvas: document.querySelector("#canvas")//画布:
	});
	// window size
	width  = document.getElementById("main_canvas").getBoundingClientRect().width;
	height = document.getElementById("main_canvas").getBoundingClientRect().height;

	renderer.setPixelRatio(4);
	renderer.setSize(width, height);
	renderer.setClearColor(0xf8f8f8);
	renderer.gammaOutput = true;
	renderer.gammaFactor = 2.2;

	//	scene场景
	const scene = new THREE.Scene()	;

	//	camera
	camera = new THREE.PerspectiveCamera(45, width / height, 1, 10000);
	camera.position.set(0, 400, -1000);
	camera.lookAt(new THREE.Vector3(0, 0, 0));

	//	control
	const controls = new THREE.OrbitControls(camera, renderer.domElement);

	//	 axis helper
	axis = new THREE.AxisHelper(2000);
    axis.position.set(0,-1,0);
    scene.add(axis);

	//	GLB loader
	const loader = new THREE.GLTFLoader();

	//	model
	modelUrl1 = "/demo/atom.glb";
	var model;
	loader.load(
	    modelUrl1,
		function(gltf) {
			model = gltf.scene;
			model.scale.set(1500.0, 1500.0, 1500.0);
			model.position.set(0, 0 , 0);
			console.log(model);
			scene.add(gltf.scene);
		},
		function(error) {
			console.log("An error happened");
			console.log(error);
		}
	);



	// light1 上から照らす
	const light1 = new THREE.DirectionalLight(0xffffff);
	light1.intensity = 1.5;
	light1.position.set(1, 1, 1);
	scene.add(light1);

	// light2  下から照らす
	const light2 = new THREE.DirectionalLight(0xffffff);
	light2.intensity = 1.5;
	light2.position.set(-1, -1, -1);
	scene.add(light2);


	render();
	function render(){
	    requestAnimationFrame(render);
    	renderer.render(scene, camera);
		if (typeof model !== "undefined") {//不明确的
			//	ここがレンダリングされるときに呼び出される
			model.rotation.x = (roll-zero_roll)*Math.PI/180 ;//rotation回转
			model.rotation.z = (pitch-zero_pitch)*Math.PI/180 ;//変換したい部分を出力したい

		}
	}

}

