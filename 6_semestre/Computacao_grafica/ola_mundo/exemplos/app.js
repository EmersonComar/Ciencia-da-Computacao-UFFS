// import * as THREE from 'three'; // Removido pois Three.js é carregado globalmente

console.log('Three.js loaded:', typeof THREE);
console.log('Starting app...');

// --- 1. Criar a cena ---
const scene = new THREE.Scene();
scene.background = new THREE.Color(0x111122); // cor de fundo azul escuro

// --- 2. Criar a câmera (perspectiva) ---
// Parâmetros: ângulo de visão (FOV), aspecto (largura/altura), plano próximo, plano distante
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
camera.position.set(0, 2, 5);
camera.lookAt(0, 0, 0);

// --- 3. Criar o renderizador ---
const renderer = new THREE.WebGLRenderer({ antialias: true });
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement); // adiciona o <canvas> ao body

// --- 4. Adicionar um objeto 3D (cubo) ---
// Geometria: cubo de lado 1.5
const geometry = new THREE.BoxGeometry(1.5, 1.5, 1.5);
// Material: cores vibrantes (usando BasicMaterial para teste, sem necessidade de luzes)
const material = new THREE.MeshBasicMaterial({ 
    color: 0x44aa88
});
// Malha
const cube = new THREE.Mesh(geometry, material);
scene.add(cube);

// --- 5. Adicionar luzes (essenciais para ver o material Standard) ---
// Luz ambiente (iluminação base suave)
const ambientLight = new THREE.AmbientLight(0x404060);
scene.add(ambientLight);

// Luz direcional (como o sol)
const directionalLight = new THREE.DirectionalLight(0xffffff, 1);
directionalLight.position.set(1, 2, 1);
scene.add(directionalLight);

// Uma segunda luz para preencher sombras
const fillLight = new THREE.PointLight(0xffaa00, 0.5);
fillLight.position.set(-1, 1, 2);
scene.add(fillLight);

// --- 6. Animar o cubo (loop de renderização) ---
function animate() {
    requestAnimationFrame(animate);
    
    console.log('Animating...');
    
    // Rotacionar o cubo
    cube.rotation.x += 0.01;
    cube.rotation.y += 0.012;
    
    // Renderizar a cena com a câmera
    renderer.render(scene, camera);
}
animate();

// --- 7. Ajustar a tela quando a janela for redimensionada ---
window.addEventListener('resize', onWindowResize, false);
function onWindowResize() {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
}
