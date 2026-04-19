import * as THREE from 'three';

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
camera.position.z = 20;

const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.setAnimationLoop(animate);
document.body.appendChild(renderer.domElement);




const dt = 0.16;

const criar_esferas = (raio, cor, pos, vel) => ({
    mesh: new THREE.Mesh(
        new THREE.SphereGeometry(raio, 32, 16),
        new THREE.MeshBasicMaterial({ color: cor})
    ),
    posicao: pos,
    velocidade: vel
})

const esferas = [
    criar_esferas(1, 0xFFF0000, new THREE.Vector3(-5, 0, 0), new THREE.Vector3(1, -0.5, 0)),
    criar_esferas(1, 0xFFF9030, new THREE.Vector3(-3, 2, 0), new THREE.Vector3(1, -0.5, 0)),
    criar_esferas(1, 0xF129009, new THREE.Vector3(1, 2, 0), new THREE.Vector3(1, 0.4, 0)),
    criar_esferas(1, 0x7F9509, new THREE.Vector3(1, 2, 0), new THREE.Vector3(1, -0.4, 0)),
]

esferas.forEach(e => {
    scene.add(e.mesh)
    e.mesh.position.copy(e.posicao)
});

function update() {
    esferas.forEach(e => {
        e.posicao.add(e.velocidade.clone().multiplyScalar(dt));

        if (Math.abs(e.posicao.x) > 10) {
            e.velocidade.x *= -1
        };
        if (Math.abs(e.posicao.y) > 10) e.velocidade.y *= -1;

        e.mesh.position.copy(e.posicao);
    })
}

function animate() {
    update();
    renderer.render(scene, camera);
}


// resize
window.addEventListener('resize', () => {
  camera.aspect = window.innerWidth / window.innerHeight;
  renderer.setSize(window.innerWidth, window.innerHeight);
  camera.updateProjectionMatrix();
});