// Constantes físicas globais
const RAIO_BOLA = 0.4;
const RAIO_INTERNO_ARCO = 1.2;
const RAIO_EXTERNO_ARCO = 1.6;

const ALTURA_CUBO_FALHA = 0.4;
const COMPRIMENTO_CUBO_FALHA = 1.4;
const PROFUNDIDADE_CUBO_FALHA = 0.2;
const CHANCE_OBSTACULO = 0.1;
const CHANCE_MAXIMA_OBSTACULO = 0.3;
const CHANCE_POWERUP = 0.12;

const ARCOS_NO_POOL = 10;
const LIMITE_DISPERSAO = 3;
const RANKING_KEY = 'radarcos';

const VELOCIDADE_INICIAL = 0.18;
const VELOCIDADE_MAXIMA = 0.55;
const TEMPO_ESCALA = 90000;
const NIVEL_INICIAL = 1.0;

const DURACAO_INVENCIVEL = 5000;
const DURACAO_MULTI = 8000;
const DURACAO_FORMA = 8000;
const MULTI_VALOR = 3;
const VIDAS_INICIAIS = 1;
const CHANCE_FORMA = 0.04;

function criarInputManager() {
    var estado = { Esquerda: false, Direita: false, Cima: false, Baixo: false };

    function setTecla(key, valor) {
        if (key === 'ArrowLeft' || key === 'a' || key === 'A') estado.Esquerda = valor;
        if (key === 'ArrowRight' || key === 'd' || key === 'D') estado.Direita = valor;
        if (key === 'ArrowUp' || key === 'w' || key === 'W') estado.Cima = valor;
        if (key === 'ArrowDown' || key === 's' || key === 'S') estado.Baixo = valor;
    }

    function onKeyDown(e) { setTecla(e.key, true); }
    function onKeyUp(e) { setTecla(e.key, false); }

    window.addEventListener('keydown', onKeyDown);
    window.addEventListener('keyup', onKeyUp);

    function destruir() {
        window.removeEventListener('keydown', onKeyDown);
        window.removeEventListener('keyup', onKeyUp);
    }

    return { estado: estado, destruir: destruir };
}

function criarHUD() {
    var elHUD = document.getElementById('hud');
    var elPontos = document.getElementById('hud-pontos');
    var elVidas = document.getElementById('hud-vidas');
    var elPowerup = document.getElementById('hud-powerup');
    var elPUNome = document.getElementById('hud-powerup-nome');
    var elPUTempo = document.getElementById('hud-powerup-tempo');

    function mostrar(visivel) { elHUD.style.display = visivel ? 'block' : 'none'; }
    function atualizar(pontos) { elPontos.textContent = pontos; }
    function atualizarVidas(vidas) { elVidas.textContent = '❤️'.repeat(Math.max(0, vidas)); }
    function atualizarPowerup(nome, tempoRestanteMs) {
        if (!nome) { elPowerup.style.display = 'none'; return; }
        elPowerup.style.display = 'inline';
        elPUNome.textContent = nome;
        elPUTempo.textContent = Math.ceil(tempoRestanteMs / 1000);
    }

    return { mostrar: mostrar, atualizar: atualizar, atualizarVidas: atualizarVidas, atualizarPowerup: atualizarPowerup };
}

function criarRankingManager(maxEntradas) {
    var max = maxEntradas || 5;

    function carregar() {
        return JSON.parse(localStorage.getItem(RANKING_KEY)) || [];
    }

    function salvar(nome, pontuacao) {
        var ranking = carregar();
        ranking.push({ nome: nome, pontuacao: pontuacao });
        ranking.sort(function (a, b) { return b.pontuacao - a.pontuacao; });
        localStorage.setItem(RANKING_KEY, JSON.stringify(ranking.slice(0, max)));
    }

    function renderizarHTML(listaOL) {
        var ranking = carregar();
        listaOL.innerHTML = '';
        if (ranking.length === 0) {
            listaOL.innerHTML = '<li>Nenhum recorde ainda!</li>';
            return;
        }
        ranking.forEach(function (item) {
            var li = document.createElement('li');
            li.innerHTML = '<strong>' + item.nome + '</strong> - ' + item.pontuacao + ' pts';
            listaOL.appendChild(li);
        });
    }

    function limpar() { localStorage.removeItem(RANKING_KEY); }

    return { carregar: carregar, salvar: salvar, renderizarHTML: renderizarHTML, limpar: limpar };
}

function criarSceneManager(containerId) {
    var scene = new THREE.Scene();
    scene.background = new THREE.Color(0xf7d9aa);
    scene.fog = new THREE.Fog(0xf7d9aa, 100, 950);

    var camera = new THREE.PerspectiveCamera(60, window.innerWidth / window.innerHeight, 0.1, 1000);
    camera.position.set(0, 0, 5);

    var renderer = new THREE.WebGLRenderer({ antialias: true });
    renderer.setSize(window.innerWidth, window.innerHeight);
    document.getElementById(containerId).appendChild(renderer.domElement);

    // Luzes estilizadas do The Aviator
    var hemisphereLight = new THREE.HemisphereLight(0xaaaaaa, 0x000000, 0.9);
    scene.add(hemisphereLight);

    var ambientLight = new THREE.AmbientLight(0xdc8874, 0.5);
    scene.add(ambientLight);

    var dirLight = new THREE.DirectionalLight(0xffffff, 0.8);
    dirLight.position.set(150, 350, 350);
    scene.add(dirLight);

    function onResize() {
        camera.aspect = window.innerWidth / window.innerHeight;
        camera.updateProjectionMatrix();
        renderer.setSize(window.innerWidth, window.innerHeight);
    }
    window.addEventListener('resize', onResize);

    function render() { renderer.render(scene, camera); }
    function destruir() { window.removeEventListener('resize', onResize); }

    return { scene: scene, camera: camera, renderer: renderer, render: render, destruir: destruir };
}


function criarPlayer(scene) {
    var mesh = new THREE.Object3D();
    mesh.name = 'airplane';
    scene.add(mesh);

    var modelRotor = null;
    var planeMaterial = null;
    var modelLoaded = false;
    var animandoEntrada = false;
    var modelContainer = null;

    if (typeof THREE.MTLLoader !== 'undefined' && typeof THREE.OBJLoader !== 'undefined') {
        var mtlLoader = new THREE.MTLLoader();
        mtlLoader.setPath('textura/airplane/');
        mtlLoader.load('airplane.mtl', function (materials) {
            materials.preload();

            for (var matName in materials.materials) {
                var m = materials.materials[matName];
                m.flatShading = true;
                if (matName === '01___Airplane') {
                    planeMaterial = m;
                }
            }

            var objLoader = new THREE.OBJLoader();
            objLoader.setMaterials(materials);
            objLoader.setPath('textura/airplane/');
            objLoader.load('airplane.obj', function (object) {
                var bbox = new THREE.Box3().setFromObject(object);
                var size = new THREE.Vector3();
                bbox.getSize(size);
                var center = new THREE.Vector3();
                bbox.getCenter(center);

                var rotationGroup1 = new THREE.Group();
                rotationGroup1.add(object);
                rotationGroup1.rotation.z = -Math.PI/2;

                var rotationGroup2 = new THREE.Group();
                rotationGroup2.add(rotationGroup1);
                rotationGroup2.rotation.x = -Math.PI / 2;

                modelContainer = new THREE.Group();
                modelContainer.add(rotationGroup2);

                var scale = 1.85 / size.y;
                modelContainer.scale.set(scale, scale, scale);

                object.traverse(function (child) {
                    if (child.name === '11665_Rotor') {
                        modelRotor = child;

                        child.geometry.computeBoundingBox();
                        var localCenter = new THREE.Vector3();
                        child.geometry.boundingBox.getCenter(localCenter);

                        child.geometry.center();

                        child.position.copy(localCenter);
                    }
                });

                mesh.add(modelContainer);
                mesh.position.y = -10; 
                animandoEntrada = true;
                modelLoaded = true;
            });
        });
    }

    function resetar() {
        mesh.position.set(0, -2, 0);
        mesh.rotation.set(0, 0, 0);
        if (modelLoaded && planeMaterial) {
            planeMaterial.color.setHex(0xffffff);
        }
    }

    function moverParaMenu() { resetar(); }
    function moverParaJogo() { resetar(); }

    function atualizarCor(tipoPowerup) {
        var cores = { forma_velocidade: 0x9900ff, forma_pontos: 0x111111, forma_chance: 0x22cc22 };
        if (modelLoaded && planeMaterial) {
            planeMaterial.color.setHex(cores[tipoPowerup] || 0xffffff);
        }
    }

    function processarInput(input, velocidadeMulti) {
        if (!modelLoaded || animandoEntrada) return;

        velocidadeMulti = velocidadeMulti || 1;
        var vel = 0.1 * velocidadeMulti;
        var pos = mesh.position;
        var alvoZ = input.Esquerda ? 0.4 : (input.Direita ? -0.4 : 0);
        var alvoX = input.Cima ? -0.18 : (input.Baixo ? 0.18 : 0);
        mesh.rotation.z += (alvoZ - mesh.rotation.z) * 0.12;
        mesh.rotation.x += (alvoX - mesh.rotation.x) * 0.12;
        if (input.Esquerda) pos.x -= vel;
        if (input.Direita) pos.x += vel;
        if (input.Cima) pos.y += vel;
        if (input.Baixo) pos.y -= vel;
        pos.x = Math.max(Math.min(pos.x, 4), -4);
        pos.y = Math.max(Math.min(pos.y, 3), -3);
    }

    function atualizar() {
        if (!modelLoaded) return;

        if (animandoEntrada) {
            mesh.position.y += (-2 - mesh.position.y) * 0.05;
            if (Math.abs(mesh.position.y - (-2)) < 0.02) {
                mesh.position.y = -2;
                animandoEntrada = false;
            }
        }

        if (modelRotor) {
            modelRotor.rotation.x += 0.28;
        }
    }

    function destruir() {
        if (modelLoaded) {
            mesh.traverse(function(child) {
                if (child.isMesh) {
                    if (child.geometry) child.geometry.dispose();
                    if (child.material) {
                        if (Array.isArray(child.material)) child.material.forEach(function(m) { m.dispose(); });
                        else child.material.dispose();
                    }
                }
            });
        }
        scene.remove(mesh);
    }

    function posX() { return mesh.position.x; }
    function posY() { return mesh.position.y; }
    function posZ() { return mesh.position.z; }

    function isReady() {
        return modelLoaded && !animandoEntrada;
    }

    return {
        mesh: mesh,
        moverParaMenu: moverParaMenu, moverParaJogo: moverParaJogo,
        atualizarCor: atualizarCor, processarInput: processarInput,
        atualizar: atualizar, destruir: destruir,
        posX: posX, posY: posY, posZ: posZ,
        isReady: isReady
    };
}

function criarPowerUpManager() {
    var tipo = null;
    var tempoRestante = 0;

    function ativar(t) {
        tipo = t;
        if (t === 'invencivel') tempoRestante = DURACAO_INVENCIVEL;
        else if (t === 'multi') tempoRestante = DURACAO_MULTI;
        else if (t.startsWith('forma')) tempoRestante = DURACAO_FORMA;
        else tempoRestante = 0;
    }

    function tick(deltams) {
        if (!tipo || tipo === 'vida') return false;
        tempoRestante -= deltams;
        if (tempoRestante <= 0) { tipo = null; tempoRestante = 0; return true; }
        return false;
    }

    function ativo() { return tipo !== null; }
    function invencivel() { return tipo === 'invencivel'; }
    function multiplicador() { return tipo === 'multi' ? MULTI_VALOR : 1; }
    function velocidadeMulti() { return tipo === 'forma_velocidade' ? 3 : 1; }
    function pontosBase() { return tipo === 'forma_pontos' ? 2 : 1; }
    function chanceBonus() { return tipo === 'forma_chance' ? 0.15 : 0; }
    function getTipo() { return tipo; }
    function getTempoRestante() { return tempoRestante; }

    return {
        ativar: ativar, tick: tick,
        ativo: ativo, invencivel: invencivel,
        multiplicador: multiplicador, velocidadeMulti: velocidadeMulti,
        pontosBase: pontosBase, chanceBonus: chanceBonus,
        getTipo: getTipo, getTempoRestante: getTempoRestante
    };
}

function criarArcoPool(scene, tamanho) {
    var geo = new THREE.TorusGeometry(RAIO_INTERNO_ARCO, (RAIO_EXTERNO_ARCO - RAIO_INTERNO_ARCO) / 2, 8, 30);
    var geoFalha = new THREE.BoxGeometry(COMPRIMENTO_CUBO_FALHA, ALTURA_CUBO_FALHA, PROFUNDIDADE_CUBO_FALHA);
    var geoVida = new THREE.OctahedronGeometry(0.5);
    var geoInvenc = new THREE.DodecahedronGeometry(0.45);
    var geoMulti = new THREE.TetrahedronGeometry(0.55);
    var geoForma = new THREE.SphereGeometry(0.45, 12, 12);

    var matAzul = new THREE.MeshStandardMaterial({ color: 0x00aaff });
    var matVerde = new THREE.MeshStandardMaterial({ color: 0x00ff00 });
    var matVermelho = new THREE.MeshStandardMaterial({ color: 0xff0000 });
    var matVida = new THREE.MeshStandardMaterial({ color: 0x00ff88 });
    var matInvenc = new THREE.MeshStandardMaterial({ color: 0xffcc00 });
    var matMulti = new THREE.MeshStandardMaterial({ color: 0xcc00ff });
    // Power-ups de transformacao
    var matFVel = new THREE.MeshStandardMaterial({ color: 0x9900ff }); // roxo
    var matFPts = new THREE.MeshStandardMaterial({ color: 0x222222 }); // preto
    var matFChc = new THREE.MeshStandardMaterial({ color: 0x22cc22 }); // verde

    function geoParaTipo(tipo) {
        if (tipo === 'falha') return geoFalha;
        if (tipo === 'vida') return geoVida;
        if (tipo === 'invencivel') return geoInvenc;
        if (tipo === 'multi') return geoMulti;
        if (tipo.startsWith('forma')) return geoForma;
        return geo;
    }

    function matParaTipo(tipo) {
        if (tipo === 'falha') return matVermelho;
        if (tipo === 'vida') return matVida;
        if (tipo === 'invencivel') return matInvenc;
        if (tipo === 'multi') return matMulti;
        if (tipo === 'forma_velocidade') return matFVel;
        if (tipo === 'forma_pontos') return matFPts;
        if (tipo === 'forma_chance') return matFChc;
        return matAzul;
    }

    var pool = [];
    for (var i = 0; i < tamanho; i++) {
        var m = new THREE.Mesh(geo, matAzul);
        m.visible = false;
        m.userData = { ativo: false, passou: false, tipo: 'arco' };
        scene.add(m);
        pool.push(m);
    }

    var ativos = [];

    function getMenorZ() {
        var z = 0;
        for (var i = 0; i < ativos.length; i++) { if (ativos[i].position.z < z) z = ativos[i].position.z; }
        return z;
    }

    function desativar(obj) {
        obj.visible = false;
        obj.userData.ativo = false;
        obj.userData.passou = false;
        var idx = ativos.indexOf(obj);
        if (idx !== -1) ativos.splice(idx, 1);
    }

    function desativarTodos() {
        var copia = ativos.slice();
        for (var i = 0; i < copia.length; i++) desativar(copia[i]);
    }

    function ativar(posZ, nivelDificuldade, powerup) {
        var obj = null;
        for (var i = 0; i < pool.length; i++) { if (!pool[i].userData.ativo) { obj = pool[i]; break; } }
        if (!obj) return;

        var r = Math.random();
        var chanceBonus = powerup ? powerup.chanceBonus() : 0;
        var chanceObst = Math.min(CHANCE_OBSTACULO + nivelDificuldade * 0.05, CHANCE_MAXIMA_OBSTACULO);
        var tipo;

        if (r < CHANCE_FORMA) {
            var rF = Math.random();
            tipo = rF < 0.33 ? 'forma_velocidade' : rF < 0.66 ? 'forma_pontos' : 'forma_chance';
        } else if (r < CHANCE_FORMA + CHANCE_POWERUP + chanceBonus) {
            var rPU = Math.random();
            tipo = rPU < 0.4 ? 'vida' : rPU < 0.7 ? 'invencivel' : 'multi';
        } else if (r < CHANCE_FORMA + CHANCE_POWERUP + chanceBonus + chanceObst) {
            tipo = 'falha';
        } else {
            tipo = 'arco';
        }

        var maxDisp = Math.min(LIMITE_DISPERSAO, 1 + nivelDificuldade * 0.4);
        obj.position.set((Math.random() - 0.5) * maxDisp * 2, (Math.random() - 0.5) * maxDisp * 2, posZ);
        obj.rotation.set(0, 0, 0);
        obj.geometry = geoParaTipo(tipo);
        obj.material = matParaTipo(tipo);
        obj.userData.tipo = tipo;
        obj.userData.ativo = true;
        obj.userData.passou = false;
        obj.visible = true;
        ativos.push(obj);
    }

    function atualizar(velocidadeZ, player, nivelDificuldade, powerup) {
        var resultado = null;

        for (var i = ativos.length - 1; i >= 0; i--) {
            var obj = ativos[i];
            obj.position.z += velocidadeZ;

            if (obj.userData.tipo !== 'arco' && obj.userData.tipo !== 'falha') {
                obj.rotation.y += 0.04;
                obj.rotation.x += 0.02;
            }

            if (!obj.userData.passou && obj.position.z >= player.posZ()) {
                var tipo = obj.userData.tipo;

                if (tipo === 'arco') {
                    var dx = player.posX() - obj.position.x;
                    var dy = player.posY() - obj.position.y;
                    var dist = Math.sqrt(dx * dx + dy * dy);

                    if (dist <= RAIO_INTERNO_ARCO - RAIO_BOLA) {
                        obj.userData.passou = true;
                        obj.material = matVerde;
                        resultado = 'SUCESSO';
                    } else if (dist <= RAIO_EXTERNO_ARCO + RAIO_BOLA) {
                        if (powerup && powerup.invencivel()) {
                            obj.userData.passou = true;
                            obj.material = matVerde;
                            resultado = 'SUCESSO';
                        } else {
                            obj.userData.passou = true;
                            obj.material = matVermelho;
                            return 'GAMEOVER';
                        }
                    }

                } else if (tipo === 'falha') {
                    var metadeLargura = COMPRIMENTO_CUBO_FALHA / 2 + RAIO_BOLA;
                    var metadeAltura = ALTURA_CUBO_FALHA / 2 + RAIO_BOLA;
                    var colidiu = Math.abs(player.posX() - obj.position.x) < metadeLargura &&
                        Math.abs(player.posY() - obj.position.y) < metadeAltura;

                    if (colidiu) {
                        if (powerup && powerup.invencivel()) {
                            obj.userData.passou = true;
                            obj.material = matVerde;
                        } else {
                            obj.userData.passou = true;
                            return 'GAMEOVER';
                        }
                    } else {
                        obj.userData.passou = true;
                    }

                } else {
                    var dx2 = player.posX() - obj.position.x;
                    var dy2 = player.posY() - obj.position.y;
                    var dist2 = Math.sqrt(dx2 * dx2 + dy2 * dy2);
                    if (dist2 <= RAIO_BOLA + 0.6) {
                        resultado = { powerup: tipo, posicao: obj.position.clone() };
                        desativar(obj);
                        ativar(getMenorZ() - 20, nivelDificuldade, powerup);
                    }
                }
            }

            if (obj.position.z > 5) {
                desativar(obj);
                ativar(getMenorZ() - 20, nivelDificuldade, powerup);
            }
        }

        return resultado;
    }

    function destruir() {
        [geo, geoFalha, geoVida, geoInvenc, geoMulti, geoForma]
            .forEach(function (g) { g.dispose(); });
        [matAzul, matVerde, matVermelho, matVida, matInvenc, matMulti, matFVel, matFPts, matFChc]
            .forEach(function (mat) { mat.dispose(); });
    }

    return { ativar: ativar, desativarTodos: desativarTodos, atualizar: atualizar, destruir: destruir };
}

function Sea() {
    var radius = 600;
    var length = 800;
    var geom = new THREE.CylinderGeometry(radius, radius, length, 40, 10);
    geom.rotateZ(Math.PI / 2);

    var posAttr = geom.attributes.position;
    var count = posAttr.count;

    this.waves = [];
    this.initialPositions = new Float32Array(count * 3);
    for (var i = 0; i < count; i++) {
        var x = posAttr.getX(i);
        var y = posAttr.getY(i);
        var z = posAttr.getZ(i);
        this.initialPositions[i * 3] = x;
        this.initialPositions[i * 3 + 1] = y;
        this.initialPositions[i * 3 + 2] = z;

        this.waves.push({
            ang: Math.random() * Math.PI * 2,
            amp: 0.8 + Math.random() * 1.5,
            speed: 0.03 + Math.random() * 0.04
        });
    }

    var mat = new THREE.MeshPhongMaterial({
        color: 0x68c3c0,
        transparent: true,
        opacity: 0.8,
        flatShading: true
    });

    this.mesh = new THREE.Mesh(geom, mat);
    this.mesh.receiveShadow = true;

    var self = this;
    this.moveWaves = function() {
        var pos = self.mesh.geometry.attributes.position;
        var arr = pos.array;
        for (var i = 0; i < count; i++) {
            var wave = self.waves[i];
            var ox = self.initialPositions[i * 3];
            var oy = self.initialPositions[i * 3 + 1];
            var oz = self.initialPositions[i * 3 + 2];

            var lengthYZ = Math.sqrt(oy * oy + oz * oz);
            var ny = oy / lengthYZ;
            var nz = oz / lengthYZ;

            var offset = Math.sin(wave.ang) * wave.amp;
            arr[i * 3 + 1] = oy + ny * offset;
            arr[i * 3 + 2] = oz + nz * offset;

            wave.ang += wave.speed;
        }
        pos.needsUpdate = true;
    };
}

function Cloud() {
    this.mesh = new THREE.Group();
    this.mesh.name = "cloud";
    var geom = new THREE.BoxGeometry(20, 20, 20);
    var mat = new THREE.MeshPhongMaterial({
        color: 0xd8d0d1,
        flatShading: true
    });

    var nBlocs = 3 + Math.floor(Math.random() * 3);
    this.blocks = [];
    for (var i = 0; i < nBlocs; i++) {
        var m = new THREE.Mesh(geom, mat);
        m.position.x = i * 15;
        m.position.y = Math.random() * 10;
        m.position.z = Math.random() * 10;
        m.rotation.z = Math.random() * Math.PI * 2;
        m.rotation.y = Math.random() * Math.PI * 2;
        var s = 0.1 + Math.random() * 0.9;
        m.scale.set(s, s, s);
        m.castShadow = true;
        m.receiveShadow = true;
        this.mesh.add(m);
        this.blocks.push({
            mesh: m,
            rotSpeedZ: Math.random() * 0.005,
            rotSpeedY: Math.random() * 0.002
        });
    }

    var self = this;
    this.rotate = function() {
        for (var i = 0; i < self.blocks.length; i++) {
            var b = self.blocks[i];
            b.mesh.rotation.z += b.rotSpeedZ;
            b.mesh.rotation.y += b.rotSpeedY;
        }
    };
}

function Sky() {
    this.mesh = new THREE.Group();
    this.nClouds = 20;
    this.clouds = [];
    var stepAngle = Math.PI * 2 / this.nClouds;
    var seaRadius = 600;

    for (var i = 0; i < this.nClouds; i++) {
        var c = new Cloud();
        this.clouds.push(c);
        var a = stepAngle * i;
        var h = seaRadius + 150 + Math.random() * 200;
        c.mesh.position.y = Math.sin(a) * h;
        c.mesh.position.z = Math.cos(a) * h;
        c.mesh.position.x = (Math.random() - 0.5) * 800;

        c.mesh.rotation.x = a + Math.PI / 2;

        var s = 1 + Math.random() * 2;
        c.mesh.scale.set(s, s, s);
        this.mesh.add(c.mesh);
    }

    var self = this;
    this.moveClouds = function(speed) {
        for (var i = 0; i < self.nClouds; i++) {
            var c = self.clouds[i];
            c.rotate();
        }
        self.mesh.rotation.x += speed;
    };
}

function criarAmbientacao(scene) {
    var sea = new Sea();
    sea.mesh.position.y = -608;
    scene.add(sea.mesh);

    var sky = new Sky();
    sky.mesh.position.y = -608;
    scene.add(sky.mesh);

    function atualizar(velocidadeZ) {
        sea.mesh.rotation.x += velocidadeZ * 0.004;
        if (sea.mesh.rotation.x > Math.PI * 2) {
            sea.mesh.rotation.x -= Math.PI * 2;
        }
        sea.moveWaves();
        sky.moveClouds(velocidadeZ * 0.001);
    }

    function destruir() {
        if (sea.mesh.geometry) sea.mesh.geometry.dispose();
        if (sea.mesh.material) sea.mesh.material.dispose();
        sky.clouds.forEach(function(c) {
            c.blocks.forEach(function(b) {
                if (b.mesh.geometry) b.mesh.geometry.dispose();
                if (b.mesh.material) b.mesh.material.dispose();
            });
        });
        scene.remove(sea.mesh);
        scene.remove(sky.mesh);
    }

    return { atualizar: atualizar, destruir: destruir };
}

function criarParticleSystem(scene) {
    var CORES = {
        vida: 0x00ff88, invencivel: 0xffcc00, multi: 0xcc00ff,
        forma_velocidade: 0x9900ff, forma_pontos: 0x888888, forma_chance: 0x22cc22
    };

    var explosoes = [];

    function explodir(posicao, tipoPowerup) {
        var cor = CORES[tipoPowerup] || 0xffffff;
        var N = 24;
        var posArr = new Float32Array(N * 3);
        var vels = [];

        for (var i = 0; i < N; i++) {
            posArr[i * 3] = posicao.x;
            posArr[i * 3 + 1] = posicao.y;
            posArr[i * 3 + 2] = posicao.z;
            vels.push(new THREE.Vector3(
                (Math.random() - 0.5) * 0.25,
                (Math.random() - 0.5) * 0.25,
                (Math.random() - 0.5) * 0.15
            ));
        }

        var geo = new THREE.BufferGeometry();
        geo.setAttribute('position', new THREE.BufferAttribute(posArr, 3));

        var mat = new THREE.PointsMaterial({
            color: cor, size: 0.18, sizeAttenuation: true,
            transparent: true, opacity: 1.0, depthWrite: false
        });

        var points = new THREE.Points(geo, mat);
        scene.add(points);
        explosoes.push({ points: points, geo: geo, mat: mat, vels: vels, tempo: 0, duracao: 450 });
    }

    function atualizar(delta) {
        for (var i = explosoes.length - 1; i >= 0; i--) {
            var exp = explosoes[i];
            exp.tempo += delta;
            var progresso = exp.tempo / exp.duracao;
            var arr = exp.geo.attributes.position.array;

            for (var j = 0; j < exp.vels.length; j++) {
                arr[j * 3] += exp.vels[j].x;
                arr[j * 3 + 1] += exp.vels[j].y;
                arr[j * 3 + 2] += exp.vels[j].z;
                exp.vels[j].multiplyScalar(0.90);
            }
            exp.geo.attributes.position.needsUpdate = true;
            exp.mat.opacity = Math.max(0, 1 - progresso);

            if (exp.tempo >= exp.duracao) {
                scene.remove(exp.points);
                exp.geo.dispose();
                exp.mat.dispose();
                explosoes.splice(i, 1);
            }
        }
    }

    return { explodir: explodir, atualizar: atualizar };
}

function iniciarJogo() {
    var sceneManager = criarSceneManager('canvas-container');
    var input = criarInputManager();
    var hud = criarHUD();
    var ranking = criarRankingManager(5);
    var player = criarPlayer(sceneManager.scene);
    var pool = criarArcoPool(sceneManager.scene, ARCOS_NO_POOL);
    var particulas = criarParticleSystem(sceneManager.scene);
    var ambientacao = criarAmbientacao(sceneManager.scene);

    var telas = {
        menu: document.getElementById('menu-inicial'),
        hud: document.getElementById('hud'),
        gameOver: document.getElementById('tela-game-over'),
        ranking: document.getElementById('tela-ranking')
    };
    var elPontosFinais = document.getElementById('pontos-finais');
    var elListaRanking = document.getElementById('lista-ranking');
    var elNomeJogador = document.getElementById('nome-jogador');

    var estado = null;
    var pontos = 0;
    var velocidadeZ = 0.3;
    var nivelDificuldade = 1;
    var tempoDecorrido = 0;
    var vidas = VIDAS_INICIAIS;
    var powerup = criarPowerUpManager();

    var NOMES_PU = {
        invencivel: '⚡ Invencível',
        multi: '✖️ x' + MULTI_VALOR,
        forma_velocidade: '🟣 Turbo',
        forma_pontos: '⚫ x2 pts',
        forma_chance: '🟢 +Sorte'
    };

    document.getElementById('btn-jogar').addEventListener('click', function () {
        if (player.isReady()) {
            mudarEstado('JOGANDO');
        }
    });
    document.getElementById('btn-ranking-menu').addEventListener('click', function () { mudarEstado('RANKING'); });
    document.getElementById('btn-salvar-ranking').addEventListener('click', salvarEIrParaRanking);
    document.getElementById('btn-jogar-novamente').addEventListener('click', function () { mudarEstado('JOGANDO'); });
    document.getElementById('btn-voltar-menu').addEventListener('click', function () { mudarEstado('MENU'); });
    document.getElementById('btn-limpar-ranking').addEventListener('click', limparRanking);

    function mudarEstado(novoEstado) {
        estado = novoEstado;
        Object.values(telas).forEach(function (el) { el.style.display = 'none'; });

        if (novoEstado === 'MENU') {
            telas.menu.style.display = 'flex';
            player.moverParaMenu();
            pool.desativarTodos();
        } else if (novoEstado === 'JOGANDO') {
            telas.hud.style.display = 'block';
            iniciarNovaPartida();
        } else if (novoEstado === 'GAMEOVER') {
            telas.gameOver.style.display = 'flex';
            elPontosFinais.textContent = pontos;
            pool.desativarTodos();
        } else if (novoEstado === 'RANKING') {
            telas.ranking.style.display = 'flex';
            ranking.renderizarHTML(elListaRanking);
        }
    }

    function iniciarNovaPartida() {
        pontos = 0;
        velocidadeZ = VELOCIDADE_INICIAL;
        nivelDificuldade = NIVEL_INICIAL;
        tempoDecorrido = 0;
        vidas = VIDAS_INICIAIS;
        powerup = criarPowerUpManager();

        player.moverParaJogo();
        hud.atualizar(pontos);
        hud.atualizarVidas(vidas);
        hud.atualizarPowerup(null, 0);

        pool.desativarTodos();
        for (var i = 0; i < ARCOS_NO_POOL; i++) {
            pool.ativar(-20 - i * 20, NIVEL_INICIAL);
        }
    }

    function salvarEIrParaRanking() {
        var nome = elNomeJogador.value.trim() || 'Anônimo';
        ranking.salvar(nome, pontos);
        elNomeJogador.value = '';
        mudarEstado('RANKING');
    }

    function limparRanking() {
        ranking.limpar();
        ranking.renderizarHTML(elListaRanking);
        mudarEstado('MENU');
    }

    function aplicarPowerup(tipo, posicao) {
        if (posicao) particulas.explodir(posicao, tipo);

        if (tipo === 'vida') {
            vidas++;
            hud.atualizarVidas(vidas);
        } else {
            powerup.ativar(tipo);
            hud.atualizarPowerup(NOMES_PU[tipo] || tipo, powerup.getTempoRestante());
        }
    }

    function loop() {
        requestAnimationFrame(loop);

        if (estado === 'JOGANDO') {
            var delta = 16.66;
            tempoDecorrido += delta;
            nivelDificuldade = NIVEL_INICIAL + tempoDecorrido / TEMPO_ESCALA;
            velocidadeZ = Math.min(VELOCIDADE_INICIAL * nivelDificuldade, VELOCIDADE_MAXIMA);

            var expirou = powerup.tick(delta);
            if (expirou) {
                hud.atualizarPowerup(null, 0);
            } else if (powerup.ativo()) {
                hud.atualizarPowerup(NOMES_PU[powerup.getTipo()] || '', powerup.getTempoRestante());
            }

            player.processarInput(input.estado, powerup.velocidadeMulti());
            player.atualizarCor(powerup.getTipo());
            player.atualizar();
            ambientacao.atualizar(velocidadeZ);
            particulas.atualizar(delta);

            var resultado = pool.atualizar(velocidadeZ, player, nivelDificuldade, powerup);

            if (resultado === 'SUCESSO') {
                pontos += powerup.pontosBase() * powerup.multiplicador();
                hud.atualizar(pontos);
            } else if (resultado && resultado.powerup) {
                aplicarPowerup(resultado.powerup, resultado.posicao);
            } else if (resultado === 'GAMEOVER') {
                vidas--;
                hud.atualizarVidas(vidas);
                if (vidas <= 0) {
                    mudarEstado('GAMEOVER');
                }
            }
        } else if (estado === 'MENU') {
            player.atualizar();
            ambientacao.atualizar(0.1);

            var btnJogar = document.getElementById('btn-jogar');
            var btnRanking = document.getElementById('btn-ranking-menu');
            if (btnJogar) {
                if (player.isReady()) {
                    btnJogar.removeAttribute('disabled');
                    btnJogar.textContent = 'Jogar';
                    btnRanking.style = "display: block"
                } else {
                    btnJogar.setAttribute('disabled', 'true');
                    btnJogar.textContent = 'Carregando...';
                }
            }
        }

        sceneManager.render();
    }

    mudarEstado('MENU');
    loop();
}

window.addEventListener('DOMContentLoaded', iniciarJogo);