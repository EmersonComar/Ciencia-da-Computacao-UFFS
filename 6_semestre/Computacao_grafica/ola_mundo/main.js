import * as THREE from 'three'

const scene = new THREE.Scene();
scene.background = new THREE.Color(0x1111122)

const camera = new THREE.PerspectiveCamera(75, window.innerWidth/window.innerHeight, 0.1, 1000);
camera.position.z = 5;

const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);

const geo = new THREE.SphereGeometry(1);
const mat = new THREE.MeshStandardMaterial({
    color: 0x00ff00,
    roughness: 0.3,
    metalness: 0.1
});
const cube = new THREE.Mesh(geo, mat)
scene.add(cube)


const ambient = new THREE.AmbientLight(0x404060)
scene.add(ambient)

const directLight = new THREE.DirectionalLight(0xfffff);
directLight.position.set(-1, 1, 2)
scene.add(directLight)

const fill = new THREE.PointLight(0xffaa00, 0.1)
fill.position.set(1, 0, 0)
scene.add(fill)

function ani() {
    requestAnimationFrame(ani);

    cube.rotation.y += 0.01;
    cube.rotation.x = 2;

    renderer.render(scene, camera)
}

ani()


window.addEventListener('resize', onWindowReize, false);
function onWindowReize() {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight)
}