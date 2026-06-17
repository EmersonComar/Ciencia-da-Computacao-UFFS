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
    scene.background = new THREE.Color(0xffffff);

    var camera = new THREE.PerspectiveCamera(60, window.innerWidth / window.innerHeight, 0.1, 1000);
    camera.position.set(0, 0, 5);

    var renderer = new THREE.WebGLRenderer({ antialias: true });
    renderer.setSize(window.innerWidth, window.innerHeight);
    document.getElementById(containerId).appendChild(renderer.domElement);

    var ambientLight = new THREE.AmbientLight(0xffffff, 0.6);
    scene.add(ambientLight);
    var dirLight = new THREE.DirectionalLight(0xffffff, 0.8);
    dirLight.position.set(5, 10, 7);
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

    // Materiais
    var matBody = new THREE.MeshStandardMaterial({ color: 0xcc2200, flatShading: true });
    var matEngine = new THREE.MeshStandardMaterial({ color: 0xeeeeee, flatShading: true });
    var matProp = new THREE.MeshStandardMaterial({ color: 0x8B4513, flatShading: true });
    var matBlade = new THREE.MeshStandardMaterial({ color: 0x3D1C02, flatShading: true });
    var matGlass = new THREE.MeshStandardMaterial({ color: 0xaaddff, transparent: true, opacity: 0.35, flatShading: true });

    // Fuselagem
    var fuselage = new THREE.Mesh(new THREE.BoxGeometry(0.5, 0.4, 1.3), matBody);
    mesh.add(fuselage);

    // Motor
    var engine = new THREE.Mesh(new THREE.BoxGeometry(0.42, 0.42, 0.22), matEngine);
    engine.position.set(0, 0, -0.76);
    mesh.add(engine);

    // Asas
    var wings = new THREE.Mesh(new THREE.BoxGeometry(1.85, 0.06, 0.38), matBody);
    wings.position.set(0, 0.06, 0.1);
    mesh.add(wings);

    // Estabilizador vertical
    var tailV = new THREE.Mesh(new THREE.BoxGeometry(0.07, 0.27, 0.2), matBody);
    tailV.position.set(0, 0.22, 0.57);
    mesh.add(tailV);

    // Estabilizador horizontal
    var tailH = new THREE.Mesh(new THREE.BoxGeometry(0.6, 0.06, 0.17), matBody);
    tailH.position.set(0, 0.08, 0.57);
    mesh.add(tailH);

    // Para-brisa
    var windshield = new THREE.Mesh(new THREE.BoxGeometry(0.14, 0.2, 0.07), matGlass);
    windshield.position.set(0, 0.26, -0.18);
    mesh.add(windshield);

    // Helice
    var propGroup = new THREE.Object3D();
    propGroup.position.set(0, 0, -0.9);

    var hub = new THREE.Mesh(new THREE.BoxGeometry(0.1, 0.1, 0.1), matProp);
    propGroup.add(hub);

    var bladeGeo = new THREE.BoxGeometry(0.06, 0.72, 0.08);
    var blade1 = new THREE.Mesh(bladeGeo, matBlade);
    propGroup.add(blade1);
    var blade2 = new THREE.Mesh(bladeGeo, matBlade);
    blade2.rotation.z = Math.PI / 2;
    propGroup.add(blade2);

    mesh.add(propGroup);
    scene.add(mesh);

    function resetar() {
        mesh.position.set(0, -2, 0);
        mesh.rotation.set(0, 0, 0);
        matBody.color.setHex(0xcc2200);
    }

    function moverParaMenu() { resetar(); }
    function moverParaJogo() { resetar(); }

    function atualizarCor(tipoPowerup) {
        var cores = { forma_velocidade: 0x9900ff, forma_pontos: 0x111111, forma_chance: 0x22cc22 };
        matBody.color.setHex(cores[tipoPowerup] || 0xcc2200);
    }

    function processarInput(input, velocidadeMulti) {
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

    function atualizar() { propGroup.rotation.z += 0.28; }

    function destruir() {
        [matBody, matEngine, matProp, matBlade, matGlass].forEach(function (m) { m.dispose(); });
        scene.remove(mesh);
    }

    function posX() { return mesh.position.x; }
    function posY() { return mesh.position.y; }
    function posZ() { return mesh.position.z; }

    return {
        mesh: mesh,
        moverParaMenu: moverParaMenu, moverParaJogo: moverParaJogo,
        atualizarCor: atualizarCor, processarInput: processarInput,
        atualizar: atualizar, destruir: destruir,
        posX: posX, posY: posY, posZ: posZ
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
    var geo = new THREE.TorusGeometry(RAIO_INTERNO_ARCO, (RAIO_EXTERNO_ARCO - RAIO_INTERNO_ARCO) / 2, 8, 24);
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

    document.getElementById('btn-jogar').addEventListener('click', function () { mudarEstado('JOGANDO'); });
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
        }

        sceneManager.render();
    }

    mudarEstado('MENU');
    loop();
}

window.addEventListener('DOMContentLoaded', iniciarJogo);