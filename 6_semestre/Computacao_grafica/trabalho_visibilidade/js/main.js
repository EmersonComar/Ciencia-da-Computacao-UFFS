import * as THREE from 'three';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';

// 1. Criar um elemento de texto simples na tela para os dados
const painelTexto = document.createElement('pre');
document.body.appendChild(painelTexto);

// 2. Configuração Padrão do Three.js
const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(60, window.innerWidth / window.innerHeight, 0.1, 1000);
camera.position.set(3, 3, 5);

const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);

const controls = new OrbitControls(camera, renderer.domElement);

// 3. Cubo com 6 Cores Diferentes (Uma para cada face)
const geometry = new THREE.BoxGeometry(2, 2, 2);
const materiais = [
    new THREE.MeshBasicMaterial({ color: 0xff0000, transparent: true, opacity: 0.5 }), // Direita (Vermelho)
    new THREE.MeshBasicMaterial({ color: 0x00ffff, transparent: true, opacity: 0.5 }), // Esquerda (Ciano)
    new THREE.MeshBasicMaterial({ color: 0x00ff00, transparent: true, opacity: 0.5 }), // Cima (Verde)
    new THREE.MeshBasicMaterial({ color: 0xff00ff, transparent: true, opacity: 0.5 }), // Baixo (Magenta)
    new THREE.MeshBasicMaterial({ color: 0x0000ff, transparent: true, opacity: 0.5 }), // Frente (Azul)
    new THREE.MeshBasicMaterial({ color: 0xffff00, transparent: true, opacity: 0.5 })  // Trás (Amarelo)
];
const cubo = new THREE.Mesh(geometry, materiais);
scene.add(cubo);

// 4. Mapeamento das Normais e Setas Indicativas
const dadosFaces = [
    { nome: "Direita (Vermelha)", normal: new THREE.Vector3(1, 0, 0) },
    { nome: "Esquerda (Ciano)",  normal: new THREE.Vector3(-1, 0, 0) },
    { nome: "Cima (Verde)",       normal: new THREE.Vector3(0, 1, 0) },
    { nome: "Baixo (Magenta)",    normal: new THREE.Vector3(0, -1, 0) },
    { nome: "Frente (Azul)",      normal: new THREE.Vector3(0, 0, 1) },
    { nome: "Trás (Amarela)",     normal: new THREE.Vector3(0, 0, -1) }
];

dadosFaces.forEach(face => {
    const seta = new THREE.ArrowHelper(face.normal, face.normal, 0.8, 0xffffff);
    cubo.add(seta);
});

// 5. Loop de Renderização e Atualização do Texto
function animate() {
    requestAnimationFrame(animate);
    controls.update();

    let textoFormatado = "PRODUTO ESCALAR DAS FACES:\n";
    textoFormatado += "----------------------------\n";

    dadosFaces.forEach(face => {
        // Calcula o vetor que aponta do centro da face até a câmera
        const vetorVisao = new THREE.Vector3().copy(camera.position).sub(face.normal).normalize();
        
        // Operação matemática do Back-Face Culling
        const produtoEscalar = face.normal.dot(vetorVisao);
        const status = produtoEscalar > 0 ? "VISÍVEL" : "OCULTA";

        textoFormatado += `Face ${face.nome} | PE: ${produtoEscalar.toFixed(2)} -> ${status}\n`;
    });

    // Injeta o texto puro diretamente na tela
    painelTexto.innerText = textoFormatado;

    renderer.render(scene, camera);
}
animate();

window.addEventListener('resize', () => {
    camera.aspect = window.innerWidth / window.innerHeight;
    renderer.setSize(window.innerWidth, window.innerHeight);
    camera.updateProjectionMatrix();
});
