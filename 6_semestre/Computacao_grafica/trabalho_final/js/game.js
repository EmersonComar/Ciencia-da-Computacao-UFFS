// Constantes físicas globais
const RAIO_BOLA          = 0.4;
const RAIO_INTERNO_ARCO  = 1.2;
const RAIO_EXTERNO_ARCO  = 1.6;

const ALTURA_CUBO_FALHA   = 0.4;
const COMPRIMENTO_CUBO_FALHA = 1.4;
const PROFUNDIDADE_CUBO_FALHA = 0.2;
const CHANCE_OBSTACULO        = 0.1;
const CHANCE_MAXIMA_OBSTACULO = 0.3;
const CHANCE_POWERUP          = 0.12;

const ARCOS_NO_POOL      = 10;
const LIMITE_DISPERSAO   = 3;
const RANKING_KEY        = 'radarcos';

const VELOCIDADE_INICIAL  = 0.18;
const VELOCIDADE_MAXIMA   = 0.55;
const TEMPO_ESCALA        = 90000;
const NIVEL_INICIAL       = 1.0;

const DURACAO_INVENCIVEL  = 5000;
const DURACAO_MULTI       = 8000;
const DURACAO_FORMA       = 8000;
const MULTI_VALOR         = 3;
const VIDAS_INICIAIS      = 1;
const CHANCE_FORMA        = 0.04;

class InputManager {
    constructor() {
        this.estado = { Esquerda: false, Direita: false, Cima: false, Baixo: false };

        this._onKeyDown = this._onKeyDown.bind(this);
        this._onKeyUp = this._onKeyUp.bind(this);

        window.addEventListener('keydown', this._onKeyDown);
        window.addEventListener('keyup', this._onKeyUp);
    }

    _onKeyDown(e) {
        this._setTecla(e.key, true);
    }

    _onKeyUp(e) {
        this._setTecla(e.key, false);
    }

    _setTecla(key, valor) {
        if (key === 'ArrowLeft' || key === 'a' || key === 'A') this.estado.Esquerda = valor;
        if (key === 'ArrowRight' || key === 'd' || key === 'D') this.estado.Direita = valor;
        if (key === 'ArrowUp' || key === 'w' || key === 'W') this.estado.Cima = valor;
        if (key === 'ArrowDown' || key === 's' || key === 'S') this.estado.Baixo = valor;
    }
    destruir() {
        window.removeEventListener('keydown', this._onKeyDown);
        window.removeEventListener('keyup', this._onKeyUp);
    }
}

class HUD {
    constructor() {
        this._elHUD        = document.getElementById('hud');
        this._elPontos     = document.getElementById('hud-pontos');
        this._elVidas      = document.getElementById('hud-vidas');
        this._elPowerup    = document.getElementById('hud-powerup');
        this._elPUNome     = document.getElementById('hud-powerup-nome');
        this._elPUTempo    = document.getElementById('hud-powerup-tempo');
    }

    mostrar(visivel) {
        this._elHUD.style.display = visivel ? 'block' : 'none';
    }

    atualizar(pontos) {
        this._elPontos.textContent = pontos;
    }

    atualizarVidas(vidas) {
        this._elVidas.textContent = '❤️'.repeat(Math.max(0, vidas));
    }

    atualizarPowerup(nome, tempoRestanteMs) {
        if (!nome) {
            this._elPowerup.style.display = 'none';
            return;
        }
        this._elPowerup.style.display = 'inline';
        this._elPUNome.textContent     = nome;
        this._elPUTempo.textContent    = Math.ceil(tempoRestanteMs / 1000);
    }
}

class RankingManager {
    constructor(maxEntradas = 5) {
        this._max = maxEntradas;
    }

    carregar() {
        return JSON.parse(localStorage.getItem(RANKING_KEY)) || [];
    }

    salvar(nome, pontuacao) {
        const ranking = this.carregar();
        ranking.push({ nome, pontuacao });
        ranking.sort((a, b) => b.pontuacao - a.pontuacao);
        localStorage.setItem(RANKING_KEY, JSON.stringify(ranking.slice(0, this._max)));
    }

    renderizarHTML(listaOL) {
        const ranking = this.carregar();
        listaOL.innerHTML = '';

        if (ranking.length === 0) {
            listaOL.innerHTML = '<li>Nenhum recorde ainda!</li>';
            return;
        }

        ranking.forEach(item => {
            const li = document.createElement('li');
            li.innerHTML = `<strong>${item.nome}</strong> - ${item.pontuacao} pts`;
            listaOL.appendChild(li);
        });
    }

    limpar() {
        localStorage.removeItem(RANKING_KEY);
    }
}

class SceneManager {
    constructor(containerId) {
        this.scene = new THREE.Scene();
        this.scene.background = new THREE.Color(0xffffff);

        this.camera = new THREE.PerspectiveCamera(
            60, window.innerWidth / window.innerHeight, 0.1, 1000
        );
        this.camera.position.set(0, 0, 5);

        this.renderer = new THREE.WebGLRenderer({ antialias: true });
        this.renderer.setSize(window.innerWidth, window.innerHeight);
        document.getElementById(containerId).appendChild(this.renderer.domElement);

        this.ambientLight = new THREE.AmbientLight(0xffffff, 0.6);
        this.scene.add(this.ambientLight);
        this.dirLight = new THREE.DirectionalLight(0xffffff, 0.8);
        this.dirLight.position.set(5, 10, 7);
        this.scene.add(this.dirLight);

        this._onResize = this._onResize.bind(this);
        window.addEventListener('resize', this._onResize);
    }

    _onResize() {
        this.camera.aspect = window.innerWidth / window.innerHeight;
        this.camera.updateProjectionMatrix();
        this.renderer.setSize(window.innerWidth, window.innerHeight);
    }

    render() {
        this.renderer.render(this.scene, this.camera);
    }

    destruir() {
        window.removeEventListener('resize', this._onResize);
    }
}

class Player {
    constructor(scene) {
        this._scene = scene;
        this.mesh   = new THREE.Object3D();
        this.mesh.name = 'airplane';

        // ── Materiais ──────────────────────────────────────────────────────
        this._matBody   = new THREE.MeshStandardMaterial({ color: 0xcc2200, flatShading: true });
        this._matEngine = new THREE.MeshStandardMaterial({ color: 0xeeeeee, flatShading: true });
        this._matProp   = new THREE.MeshStandardMaterial({ color: 0x8B4513, flatShading: true });
        this._matBlade  = new THREE.MeshStandardMaterial({ color: 0x3D1C02, flatShading: true });
        this._matGlass  = new THREE.MeshStandardMaterial({
            color: 0xaaddff, transparent: true, opacity: 0.35, flatShading: true
        });

        // ── Fuselagem (orientada em Z: nariz em -Z, cauda em +Z) ──────────
        const fuselage = new THREE.Mesh(new THREE.BoxGeometry(0.5, 0.4, 1.3), this._matBody);
        this.mesh.add(fuselage);

        // ── Motor (nariz, -Z) ─────────────────────────────────────────────
        const engine = new THREE.Mesh(new THREE.BoxGeometry(0.42, 0.42, 0.22), this._matEngine);
        engine.position.set(0, 0, -0.76);
        this.mesh.add(engine);

        // ── Asas principais ───────────────────────────────────────────────
        const wings = new THREE.Mesh(new THREE.BoxGeometry(1.85, 0.06, 0.38), this._matBody);
        wings.position.set(0, 0.06, 0.1);
        this.mesh.add(wings);

        // ── Estabilizador vertical (cauda) ────────────────────────────────
        const tailV = new THREE.Mesh(new THREE.BoxGeometry(0.07, 0.27, 0.2), this._matBody);
        tailV.position.set(0, 0.22, 0.57);
        this.mesh.add(tailV);

        // ── Estabilizador horizontal (cauda) ──────────────────────────────
        const tailH = new THREE.Mesh(new THREE.BoxGeometry(0.6, 0.06, 0.17), this._matBody);
        tailH.position.set(0, 0.08, 0.57);
        this.mesh.add(tailH);

        // ── Para-brisa ────────────────────────────────────────────────────
        const windshield = new THREE.Mesh(new THREE.BoxGeometry(0.14, 0.2, 0.07), this._matGlass);
        windshield.position.set(0, 0.26, -0.18);
        this.mesh.add(windshield);

        // ── Hélice (grupo que gira) ────────────────────────────────────────
        this._propGroup = new THREE.Object3D();
        this._propGroup.position.set(0, 0, -0.9);

        const hub = new THREE.Mesh(new THREE.BoxGeometry(0.1, 0.1, 0.1), this._matProp);
        this._propGroup.add(hub);

        const bladeGeo = new THREE.BoxGeometry(0.06, 0.72, 0.08);
        const blade1   = new THREE.Mesh(bladeGeo, this._matBlade);
        this._propGroup.add(blade1);
        const blade2   = new THREE.Mesh(bladeGeo, this._matBlade);
        blade2.rotation.z = Math.PI / 2;
        this._propGroup.add(blade2);

        this.mesh.add(this._propGroup);

        scene.add(this.mesh);
    }

    _resetar() {
        this.mesh.position.set(0, -2, 0);
        this.mesh.rotation.set(0, 0, 0);
        this._matBody.color.setHex(0xcc2200);
    }

    moverParaMenu() { this._resetar(); }
    moverParaJogo() { this._resetar(); }

    atualizarCor(tipoPowerup) {
        const cores = {
            forma_velocidade: 0x9900ff,
            forma_pontos:     0x111111,
            forma_chance:     0x22cc22,
        };
        this._matBody.color.setHex(cores[tipoPowerup] || 0xcc2200);
    }

    processarInput(input, velocidadeMulti = 1) {
        const vel = 0.1 * velocidadeMulti;
        const pos = this.mesh.position;

        // Inclinação visual suave proporcional ao movimento
        const alvoZ = input.Esquerda ? 0.4 : (input.Direita ? -0.4 : 0);
        const alvoX = input.Cima    ? -0.18 : (input.Baixo ? 0.18 : 0);
        this.mesh.rotation.z += (alvoZ - this.mesh.rotation.z) * 0.12;
        this.mesh.rotation.x += (alvoX - this.mesh.rotation.x) * 0.12;

        if (input.Esquerda) pos.x -= vel;
        if (input.Direita)  pos.x += vel;
        if (input.Cima)     pos.y += vel;
        if (input.Baixo)    pos.y -= vel;
        pos.x = Math.max(Math.min(pos.x, 4), -4);
        pos.y = Math.max(Math.min(pos.y, 3), -3);
    }

    atualizar() {
        this._propGroup.rotation.z += 0.28; // hélice girando
    }

    destruir() {
        [this._matBody, this._matEngine, this._matProp, this._matBlade, this._matGlass]
            .forEach(m => m.dispose());
        this._scene.remove(this.mesh);
    }

    get posX() { return this.mesh.position.x; }
    get posY() { return this.mesh.position.y; }
    get posZ() { return this.mesh.position.z; }
}

class PowerUpManager {
    constructor() {
        this.tipo          = null;
        this.tempoRestante = 0;
    }

    ativar(tipo) {
        this.tipo = tipo;
        if (tipo === 'invencivel')              this.tempoRestante = DURACAO_INVENCIVEL;
        else if (tipo === 'multi')              this.tempoRestante = DURACAO_MULTI;
        else if (tipo.startsWith('forma'))      this.tempoRestante = DURACAO_FORMA;
        else                                    this.tempoRestante = 0;
    }

    tick(deltams) {
        if (!this.tipo || this.tipo === 'vida') return false;
        this.tempoRestante -= deltams;
        if (this.tempoRestante <= 0) {
            this.tipo          = null;
            this.tempoRestante = 0;
            return true;
        }
        return false;
    }

    get ativo()           { return this.tipo !== null; }
    get invencivel()      { return this.tipo === 'invencivel'; }
    get multiplicador()   { return this.tipo === 'multi' ? MULTI_VALOR : 1; }
    get velocidadeMulti() { return this.tipo === 'forma_velocidade' ? 3 : 1; }
    get pontosBase()      { return this.tipo === 'forma_pontos'     ? 2 : 1; }
    get chanceBonus()     { return this.tipo === 'forma_chance'     ? 0.15 : 0; }
}

class ArcoPool {
    constructor(scene, tamanho) {
        this._scene = scene;

        this._geo = new THREE.TorusGeometry(
            RAIO_INTERNO_ARCO,
            (RAIO_EXTERNO_ARCO - RAIO_INTERNO_ARCO) / 2,
            8, 24
        );

        this._geoFalha = new THREE.BoxGeometry(
            COMPRIMENTO_CUBO_FALHA,
            ALTURA_CUBO_FALHA,
            PROFUNDIDADE_CUBO_FALHA
        );

        this._matAzul     = new THREE.MeshStandardMaterial({ color: 0x00aaff });
        this._matVerde    = new THREE.MeshStandardMaterial({ color: 0x00ff00 });
        this._matVermelho = new THREE.MeshStandardMaterial({ color: 0xff0000 });

        this._matVida     = new THREE.MeshStandardMaterial({ color: 0x00ff88 });
        this._matInvenc   = new THREE.MeshStandardMaterial({ color: 0xffcc00 });
        this._matMulti    = new THREE.MeshStandardMaterial({ color: 0xcc00ff });
        // Materiais e geometria dos power-ups de transformação (esfera = transforma o player)
        this._geoForma    = new THREE.SphereGeometry(0.45, 12, 12);
        this._matFVel     = new THREE.MeshStandardMaterial({ color: 0x9900ff }); // roxo
        this._matFPts     = new THREE.MeshStandardMaterial({ color: 0x222222 }); // preto
        this._matFChc     = new THREE.MeshStandardMaterial({ color: 0x22cc22 }); // verde

        this._geoVida     = new THREE.OctahedronGeometry(0.5);
        this._geoInvenc   = new THREE.DodecahedronGeometry(0.45);
        this._geoMulti    = new THREE.TetrahedronGeometry(0.55);


        this._pool = [];
        for (let i = 0; i < tamanho; i++) {
            const mesh = new THREE.Mesh(this._geo, this._matAzul);
            mesh.visible = false;
            mesh.userData = { ativo: false, passou: false, tipo: 'arco' };
            scene.add(mesh);
            this._pool.push(mesh);
        }

        this._ativos = [];
    }

    _geoParaTipo(tipo) {
        if (tipo === 'falha')            return this._geoFalha;
        if (tipo === 'vida')             return this._geoVida;
        if (tipo === 'invencivel')       return this._geoInvenc;
        if (tipo === 'multi')            return this._geoMulti;
        if (tipo.startsWith('forma'))    return this._geoForma;
        return this._geo;
    }
    _matParaTipo(tipo) {
        if (tipo === 'falha')             return this._matVermelho;
        if (tipo === 'vida')             return this._matVida;
        if (tipo === 'invencivel')       return this._matInvenc;
        if (tipo === 'multi')            return this._matMulti;
        if (tipo === 'forma_velocidade') return this._matFVel;
        if (tipo === 'forma_pontos')     return this._matFPts;
        if (tipo === 'forma_chance')     return this._matFChc;
        return this._matAzul;
    }

    ativar(posZ, nivelDificuldade, powerup = null) {
        const mesh = this._pool.find(m => !m.userData.ativo);
        if (!mesh) return;

        const r             = Math.random();
        const chanceBonus   = powerup ? powerup.chanceBonus : 0;
        const chanceObst    = Math.min(CHANCE_OBSTACULO + nivelDificuldade * 0.05, CHANCE_MAXIMA_OBSTACULO);
        let tipo;

        if (r < CHANCE_FORMA) {
            // Power-up de transformação — chance baixissíma (~1,3% cada)
            const rF = Math.random();
            tipo = rF < 0.33 ? 'forma_velocidade' : rF < 0.66 ? 'forma_pontos' : 'forma_chance';
        } else if (r < CHANCE_FORMA + CHANCE_POWERUP + chanceBonus) {
            // Power-up normal (bola verde aumenta esta faixa)
            const rPU = Math.random();
            tipo = rPU < 0.4 ? 'vida' : rPU < 0.7 ? 'invencivel' : 'multi';
        } else if (r < CHANCE_FORMA + CHANCE_POWERUP + chanceBonus + chanceObst) {
            tipo = 'falha';
        } else {
            tipo = 'arco';
        }

        const maxDisp = Math.min(LIMITE_DISPERSAO, 1 + nivelDificuldade * 0.4);
        mesh.position.set(
            (Math.random() - 0.5) * maxDisp * 2,
            (Math.random() - 0.5) * maxDisp * 2,
            posZ
        );

        
        mesh.rotation.set(0, 0, 0);

        mesh.geometry        = this._geoParaTipo(tipo);
        mesh.material        = this._matParaTipo(tipo);
        mesh.userData.tipo   = tipo;
        mesh.userData.ativo  = true;
        mesh.userData.passou = false;
        mesh.visible         = true;
        this._ativos.push(mesh);
    }

    _desativar(mesh) {
        mesh.visible = false;
        mesh.userData.ativo = false;
        mesh.userData.passou = false;
        const idx = this._ativos.indexOf(mesh);
        if (idx !== -1) this._ativos.splice(idx, 1);
    }

    desativarTodos() {
        [...this._ativos].forEach(m => this._desativar(m));
    }

    atualizar(velocidadeZ, player, nivelDificuldade, powerup) {
        let resultado = null;

        for (let i = this._ativos.length - 1; i >= 0; i--) {
            const obj = this._ativos[i];
            obj.position.z += velocidadeZ;
            if (obj.userData.tipo !== 'arco' && obj.userData.tipo !== 'falha') {
                obj.rotation.y += 0.04;
                obj.rotation.x += 0.02;
            }

            if (!obj.userData.passou && obj.position.z >= player.posZ) {
                const tipo = obj.userData.tipo;

                if (tipo === 'arco') {
                    const dx   = player.posX - obj.position.x;
                    const dy   = player.posY - obj.position.y;
                    const dist = Math.sqrt(dx * dx + dy * dy);

                    if (dist <= RAIO_INTERNO_ARCO - RAIO_BOLA) {
                        obj.userData.passou = true;
                        obj.material        = this._matVerde;
                        resultado           = 'SUCESSO';
                    } else if (dist <= RAIO_EXTERNO_ARCO + RAIO_BOLA) {
                        if (powerup && powerup.invencivel) {
                            obj.userData.passou = true;
                            obj.material        = this._matVerde;
                            resultado           = 'SUCESSO';
                        } else {
                            obj.userData.passou = true; 
                            return 'GAMEOVER';
                        }
                    }

                } else if (tipo === 'falha') {
                    const metadeLargura = COMPRIMENTO_CUBO_FALHA / 2 + RAIO_BOLA;
                    const metadeAltura  = ALTURA_CUBO_FALHA / 2 + RAIO_BOLA;
                    const colidiu =
                        Math.abs(player.posX - obj.position.x) < metadeLargura &&
                        Math.abs(player.posY - obj.position.y) < metadeAltura;

                    if (colidiu) {
                        if (powerup && powerup.invencivel) {
                            obj.userData.passou = true; 
                        } else {
                            obj.userData.passou = true; 
                            return 'GAMEOVER';
                        }
                    } else {
                        obj.userData.passou = true;
                    }

                } else {
                    const dx   = player.posX - obj.position.x;
                    const dy   = player.posY - obj.position.y;
                    const dist = Math.sqrt(dx * dx + dy * dy);
                    if (dist <= RAIO_BOLA + 0.6) {
                        resultado = { powerup: tipo, posicao: obj.position.clone() };
                        this._desativar(obj);
                        let menorZ = 0;
                        this._ativos.forEach(a => { if (a.position.z < menorZ) menorZ = a.position.z; });
                        this.ativar(menorZ - 20, nivelDificuldade, powerup);
                    }
                }
            }

            if (obj.position.z > 5) {
                this._desativar(obj);
                let menorZ = 0;
                this._ativos.forEach(a => { if (a.position.z < menorZ) menorZ = a.position.z; });
                this.ativar(menorZ - 20, nivelDificuldade, powerup);
            }
        }

        return resultado;
    }

    get menorZ() {
        let z = 0;
        this._ativos.forEach(a => { if (a.position.z < z) z = a.position.z; });
        return z;
    }

    destruir() {
        this._geo.dispose();     this._geoFalha.dispose();
        this._geoVida.dispose(); this._geoInvenc.dispose(); this._geoMulti.dispose();
        this._geoForma.dispose();
        this._matAzul.dispose();    this._matVerde.dispose();   this._matVermelho.dispose();
        this._matVida.dispose();    this._matInvenc.dispose();  this._matMulti.dispose();
        this._matFVel.dispose();    this._matFPts.dispose();    this._matFChc.dispose();
    }
}


class ParticleSystem {
    static CORES = {
        vida: 0x00ff88, invencivel: 0xffcc00, multi: 0xcc00ff,
        forma_velocidade: 0x9900ff, forma_pontos: 0x888888, forma_chance: 0x22cc22,
    };

    constructor(scene) {
        this._scene     = scene;
        this._explosoes = []; 
    }

    explodir(posicao, tipoPowerup) {
        const cor      = ParticleSystem.CORES[tipoPowerup] || 0xffffff;
        const N        = 24;
        const posArr   = new Float32Array(N * 3);
        const vels     = [];

        for (let i = 0; i < N; i++) {
            posArr[i * 3]     = posicao.x;
            posArr[i * 3 + 1] = posicao.y;
            posArr[i * 3 + 2] = posicao.z;

            vels.push(new THREE.Vector3(
                (Math.random() - 0.5) * 0.25,
                (Math.random() - 0.5) * 0.25,
                (Math.random() - 0.5) * 0.15
            ));
        }

        const geo = new THREE.BufferGeometry();
        geo.setAttribute('position', new THREE.BufferAttribute(posArr, 3));

        const mat = new THREE.PointsMaterial({
            color:          cor,
            size:           0.18,
            sizeAttenuation: true,
            transparent:    true,
            opacity:        1.0,
            depthWrite:     false,
        });

        const points = new THREE.Points(geo, mat);
        this._scene.add(points);
        this._explosoes.push({ points, geo, mat, vels, tempo: 0, duracao: 450 });
    }

    atualizar(delta) {
        for (let i = this._explosoes.length - 1; i >= 0; i--) {
            const exp      = this._explosoes[i];
            exp.tempo     += delta;
            const progresso = exp.tempo / exp.duracao; // 0 → 1
            const arr      = exp.geo.attributes.position.array;

            for (let j = 0; j < exp.vels.length; j++) {
                arr[j * 3]     += exp.vels[j].x;
                arr[j * 3 + 1] += exp.vels[j].y;
                arr[j * 3 + 2] += exp.vels[j].z;
                exp.vels[j].multiplyScalar(0.90);
            }
            exp.geo.attributes.position.needsUpdate = true;
            exp.mat.opacity = Math.max(0, 1 - progresso);

            if (exp.tempo >= exp.duracao) {
                this._scene.remove(exp.points);
                exp.geo.dispose();
                exp.mat.dispose();
                this._explosoes.splice(i, 1);
            }
        }
    }
}

class Game {
    constructor() {
        this._scene    = new SceneManager('canvas-container');
        this._input    = new InputManager();
        this._hud      = new HUD();
        this._ranking  = new RankingManager(5);
        this._player     = new Player(this._scene.scene);
        this._pool       = new ArcoPool(this._scene.scene, ARCOS_NO_POOL);
        this._particulas = new ParticleSystem(this._scene.scene);

        this._telas = {
            menu: document.getElementById('menu-inicial'),
            hud: document.getElementById('hud'),
            gameOver: document.getElementById('tela-game-over'),
            ranking: document.getElementById('tela-ranking'),
        };
        this._elPontosFinais = document.getElementById('pontos-finais');
        this._elListaRanking = document.getElementById('lista-ranking');
        this._elNomeJogador = document.getElementById('nome-jogador');

        document.getElementById('btn-jogar').addEventListener('click', () => this.mudarEstado('JOGANDO'));
        document.getElementById('btn-ranking-menu').addEventListener('click', () => this.mudarEstado('RANKING'));
        document.getElementById('btn-salvar-ranking').addEventListener('click', () => this._salvarEIrParaRanking());
        document.getElementById('btn-jogar-novamente').addEventListener('click', () => this.mudarEstado('JOGANDO'));
        document.getElementById('btn-voltar-menu').addEventListener('click', () => this.mudarEstado('MENU'));
        document.getElementById('btn-limpar-ranking').addEventListener('click', () => this._limparRanking());

        this._estado           = null;
        this._pontos           = 0;
        this._velocidadeZ      = 0.3;
        this._nivelDificuldade = 1;
        this._tempoDecorrido   = 0;
        this._vidas            = VIDAS_INICIAIS;
        this._powerup          = new PowerUpManager();

        this.mudarEstado('MENU');
        this._loop();
    }

    mudarEstado(novoEstado) {
        this._estado = novoEstado;

        Object.values(this._telas).forEach(el => el.style.display = 'none');

        switch (novoEstado) {
            case 'MENU':
                this._telas.menu.style.display = 'flex';
                this._player.moverParaMenu();
                this._pool.desativarTodos();
                break;

            case 'JOGANDO':
                this._telas.hud.style.display = 'block';
                this._iniciarNovaPartida();
                break;

            case 'GAMEOVER':
                this._telas.gameOver.style.display = 'flex';
                this._elPontosFinais.textContent = this._pontos;
                this.desativarTodos()
                break;

            case 'RANKING':
                this._telas.ranking.style.display = 'flex';
                this._ranking.renderizarHTML(this._elListaRanking);
                break;
        }
    }

    _iniciarNovaPartida() {
        this._pontos           = 0;
        this._velocidadeZ      = VELOCIDADE_INICIAL;
        this._nivelDificuldade = NIVEL_INICIAL;
        this._tempoDecorrido   = 0;
        this._vidas            = VIDAS_INICIAIS;
        this._powerup          = new PowerUpManager();

        this._player.moverParaJogo();
        this._hud.atualizar(this._pontos);
        this._hud.atualizarVidas(this._vidas);
        this._hud.atualizarPowerup(null, 0);

        this._pool.desativarTodos();
        for (let i = 0; i < ARCOS_NO_POOL; i++) {
            this._pool.ativar(-20 - i * 20, NIVEL_INICIAL);
        }
    }

    _salvarEIrParaRanking() {
        const nome = this._elNomeJogador.value.trim() || 'Anônimo';
        this._ranking.salvar(nome, this._pontos);
        this._elNomeJogador.value = '';
        this.mudarEstado('RANKING');
    }

    _limparRanking() {
        this._ranking.limpar();
        this._ranking.renderizarHTML(this._elListaRanking);
        this.mudarEstado('MENU');
    }

    _aplicarPowerup(tipo, posicao) {
        if (posicao) this._particulas.explodir(posicao, tipo);

        if (tipo === 'vida') {
            this._vidas++;
            this._hud.atualizarVidas(this._vidas);
        } else {
            this._powerup.ativar(tipo);
            const nomes = {
                invencivel:       '⚡ Invencível',
                multi:            `✖️ x${MULTI_VALOR}`,
                forma_velocidade: '🟣 Turbo',
                forma_pontos:     '⚫ x2 pts',
                forma_chance:     '🟢 +Sorte',
            };
            this._hud.atualizarPowerup(nomes[tipo] || tipo, this._powerup.tempoRestante);
        }
    }

    _loop() {
        requestAnimationFrame(() => this._loop());

        if (this._estado === 'JOGANDO') {
            const delta = 16.66;
            this._tempoDecorrido   += delta;
            this._nivelDificuldade  = NIVEL_INICIAL + this._tempoDecorrido / TEMPO_ESCALA;
            this._velocidadeZ       = Math.min(VELOCIDADE_INICIAL * this._nivelDificuldade, VELOCIDADE_MAXIMA);

            const expirou = this._powerup.tick(delta);
            if (expirou) {
                this._hud.atualizarPowerup(null, 0);
            } else if (this._powerup.ativo) {
                const nomes = {
                    invencivel:       '⚡ Invencível',
                    multi:            `✖️ x${MULTI_VALOR}`,
                    forma_velocidade: '🟣 Turbo',
                    forma_pontos:     '⚫ x2 pts',
                    forma_chance:     '🟢 +Sorte',
                };
                this._hud.atualizarPowerup(nomes[this._powerup.tipo] || '', this._powerup.tempoRestante);
            }

            this._player.processarInput(this._input.estado, this._powerup.velocidadeMulti);
            this._player.atualizarCor(this._powerup.tipo);
            this._player.atualizar();
            this._particulas.atualizar(delta);

            const resultado = this._pool.atualizar(
                this._velocidadeZ, this._player, this._nivelDificuldade, this._powerup
            );

            if (resultado === 'SUCESSO') {
                this._pontos += this._powerup.pontosBase * this._powerup.multiplicador;
                this._hud.atualizar(this._pontos);
            } else if (resultado && resultado.powerup) {
                this._aplicarPowerup(resultado.powerup, resultado.posicao);
            } else if (resultado === 'GAMEOVER') {
                this._vidas--;
                this._hud.atualizarVidas(this._vidas);
                if (this._vidas <= 0) {
                    this.mudarEstado('GAMEOVER');
                }
            }
        }

        this._scene.render();
    }
}

window.addEventListener('DOMContentLoaded', () => {
    new Game();
});