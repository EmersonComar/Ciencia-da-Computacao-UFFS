import * as THREE from 'three';

const scene = new THREE.Scene();
scene.background = new THREE.Color(0x111122);

const camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 0.1, 1000);
camera.position.set(5, 5, 10);
camera.lookAt(0, 0, 0);

const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.setAnimationLoop(animate);
document.body.appendChild(renderer.domElement);

const gridHelper = new THREE.GridHelper(20, 20, 0x888888, 0x444444);
scene.add(gridHelper);

const transCube = new THREE.Mesh(
    new THREE.BoxGeometry(1, 1, 1),
    new THREE.MeshStandardMaterial({ color: 0xff3333, emissive: 0x331100 })
);
transCube.position.set(-3, 0, 0);
scene.add(transCube);

const rotCube = new THREE.Mesh(
    new THREE.BoxGeometry(1, 1, 1),
    new THREE.MeshStandardMaterial({ color: 0x33ff33, emissive: 0x003300 })
);
rotCube.position.set(0, 0, 0);
scene.add(rotCube);

const scaleCube = new THREE.Mesh(
    new THREE.BoxGeometry(1, 1, 1),
    new THREE.MeshStandardMaterial({ color: 0x3399ff, emissive: 0x001133 })
);
scaleCube.position.set(3, 0, 0);
scene.add(scaleCube);

const ambientLight = new THREE.AmbientLight(0x404060);
scene.add(ambientLight);
const dirLight = new THREE.DirectionalLight(0xffffff, 1);
dirLight.position.set(1, 2, 1);
scene.add(dirLight);

let time = 0;

function animate() {
    time += 0.02; 

    const t = Math.sin(time) * 4; 
    transCube.position.x = t;

    rotCube.rotation.y = time * 1.5;
    rotCube.rotation.x = time * 0.8;

    const scaleFactor = 0.8 + Math.sin(time * 2) * 0.5;
    scaleCube.scale.set(scaleFactor, scaleFactor, scaleFactor);

    renderer.render(scene, camera);
}

window.addEventListener('resize', () => {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
});