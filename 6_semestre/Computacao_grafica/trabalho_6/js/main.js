import * as THREE from 'three';

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
camera.position.z = 20;
scene.background = new THREE.Color(0x000000)

const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.setAnimationLoop(animate);
document.body.appendChild(renderer.domElement);

const dt = 0.16;

const criar_esferas = (raio, cor, pos, vel, ehLuz = false) => {
    const material = ehLuz 
        ? new THREE.MeshBasicMaterial({ color: cor }) 
        : new THREE.MeshStandardMaterial({ color: cor, roughness: 0.2, metalness: 0.1 });

    const mesh = new THREE.Mesh(new THREE.SphereGeometry(raio, 32, 16), material);
    
    if (ehLuz) {
        const light = new THREE.PointLight(cor, 500, 30);
        mesh.add(light);
    }

    return {
        mesh: mesh,
        posicao: pos,
        velocidade: vel
    };
};

const esferas = [
    // Esferas de luz
    criar_esferas(1.2, 0xFFFF00, new THREE.Vector3(-5, 0, 0), new THREE.Vector3(0.5, 0.3, 0), true),
    criar_esferas(1.2, 0x00FFFF, new THREE.Vector3(5, 5, 0), new THREE.Vector3(-0.4, -0.6, 0), true),
    
    // Esferas normais
    criar_esferas(0.5, 0x00FF88, new THREE.Vector3(5, -2, 2), new THREE.Vector3(-1, 0.2, 0)),
    criar_esferas(2, 0x4B0082, new THREE.Vector3(0, -4, -5), new THREE.Vector3(0, 1.5, 0)),
    criar_esferas(0.8, 0xFF69B4, new THREE.Vector3(-2, -3, 0), new THREE.Vector3(0.5, 0.8, 0)),
    criar_esferas(1.5, 0x1E90FF, new THREE.Vector3(4, 5, -3), new THREE.Vector3(-0.7, -1, 0)),
    criar_esferas(0.3, 0xFFD700, new THREE.Vector3(-6, 1, 4), new THREE.Vector3(1.2, 0, 0)),
    criar_esferas(1.2, 0x8B0000, new THREE.Vector3(2, -1, -2), new THREE.Vector3(-0.4, 0.6, 0)),
];

esferas.forEach(e => {
    scene.add(e.mesh);
    e.mesh.position.copy(e.posicao);
});

const ambientLight = new THREE.AmbientLight(0xffffff, 0.1);
scene.add(ambientLight);

function update() {
    esferas.forEach(e => {
        e.posicao.add(e.velocidade.clone().multiplyScalar(dt));

        if (Math.abs(e.posicao.x) > 15) e.velocidade.x *= -1;
        if (Math.abs(e.posicao.y) > 10) e.velocidade.y *= -1;

        e.mesh.position.copy(e.posicao);
    });
}

function animate() {
    update();
    renderer.render(scene, camera);
}

window.addEventListener('resize', () => {
    camera.aspect = window.innerWidth / window.innerHeight;
    renderer.setSize(window.innerWidth, window.innerHeight);
    camera.updateProjectionMatrix();
});
