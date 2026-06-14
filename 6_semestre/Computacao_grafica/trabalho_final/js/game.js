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
const MULTI_VALOR         = 3;    
const VIDAS_INICIAIS      = 1;   

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

        this.scene.add(new THREE.AmbientLight(0xffffff, 0.6));
        const luzDir = new THREE.DirectionalLight(0xffffff, 0.8);
        luzDir.position.set(5, 10, 7);
        this.scene.add(luzDir);

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
        const geo = new THREE.SphereGeometry(RAIO_BOLA, 16, 16);
        const mat = new THREE.MeshStandardMaterial({ color: 0xff0000 });
        this.mesh = new THREE.Mesh(geo, mat);
        scene.add(this.mesh);
    }

    moverParaMenu() {
        this.mesh.position.set(0, -2, 0);
    }

    moverParaJogo() {
        this.mesh.position.set(0, -2, 0);
    }

    processarInput(input) {
        const vel = 0.1;
        const pos = this.mesh.position;

        if (input.Esquerda) pos.x -= vel;
        if (input.Direita) pos.x += vel;
        if (input.Cima) pos.y += vel;
        if (input.Baixo) pos.y -= vel;
        pos.x = Math.max(Math.min(pos.x, 4), -4);
        pos.y = Math.max(Math.min(pos.y, 3), -3);
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
        if (tipo === 'invencivel') this.tempoRestante = DURACAO_INVENCIVEL;
        else if (tipo === 'multi') this.tempoRestante = DURACAO_MULTI;
        else this.tempoRestante = 0; 
    }

    tick(deltams) {
        if (!this.tipo || this.tipo === 'vida') return false;
        this.tempoRestante -= deltams;
        if (this.tempoRestante <= 0) {
            this.tipo          = null;
            this.tempoRestante = 0;
            return true; // expirou
        }
        return false;
    }

    get ativo() { return this.tipo !== null; }
    get invencivel() { return this.tipo === 'invencivel'; }
    get multiplicador() { return this.tipo === 'multi' ? MULTI_VALOR : 1; }
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
        // Materiais dos power-ups
        this._matVida     = new THREE.MeshStandardMaterial({ color: 0x00ff88 });
        this._matInvenc   = new THREE.MeshStandardMaterial({ color: 0xffcc00 });
        this._matMulti    = new THREE.MeshStandardMaterial({ color: 0xcc00ff });
        // Geometrias dos power-ups (formas distintas)
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
        if (tipo === 'falha')     return this._geoFalha;
        if (tipo === 'vida')      return this._geoVida;
        if (tipo === 'invencivel') return this._geoInvenc;
        if (tipo === 'multi')     return this._geoMulti;
        return this._geo;
    }
    _matParaTipo(tipo) {
        if (tipo === 'falha')     return this._matVermelho;
        if (tipo === 'vida')      return this._matVida;
        if (tipo === 'invencivel') return this._matInvenc;
        if (tipo === 'multi')     return this._matMulti;
        return this._matAzul;
    }

    ativar(posZ, nivelDificuldade) {
        const mesh = this._pool.find(m => !m.userData.ativo);
        if (!mesh) return;

        const r = Math.random();
        const chanceObstaculo = Math.min(CHANCE_OBSTACULO + nivelDificuldade * 0.05, CHANCE_MAXIMA_OBSTACULO);
        let tipo;
        if (r < CHANCE_POWERUP) {
            const rPU = Math.random();
            tipo = rPU < 0.4 ? 'vida' : rPU < 0.7 ? 'invencivel' : 'multi';
        } else if (r < CHANCE_POWERUP + chanceObstaculo) {
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
                            // Invencível: trata colisão no aro como sucesso
                            obj.userData.passou = true;
                            obj.material        = this._matVerde;
                            resultado           = 'SUCESSO';
                        } else {
                            obj.userData.passou = true; // evita re-colisão nos frames seguintes
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
                            obj.userData.passou = true; // invencível desvia automaticamente
                        } else {
                            obj.userData.passou = true; // evita re-colisão nos frames seguintes
                            return 'GAMEOVER';
                        }
                    } else {
                        obj.userData.passou = true;
                    }

                } else {
                    // Power-up: colisão por esfera simples
                    const dx   = player.posX - obj.position.x;
                    const dy   = player.posY - obj.position.y;
                    const dist = Math.sqrt(dx * dx + dy * dy);
                    if (dist <= RAIO_BOLA + 0.6) {
                        obj.userData.passou = true;
                        resultado = { powerup: tipo };
                    }
                }
            }

            if (obj.position.z > 5) {
                this._desativar(obj);
                let menorZ = 0;
                this._ativos.forEach(a => { if (a.position.z < menorZ) menorZ = a.position.z; });
                this.ativar(menorZ - 20, nivelDificuldade);
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
        this._matAzul.dispose();    this._matVerde.dispose();   this._matVermelho.dispose();
        this._matVida.dispose();    this._matInvenc.dispose();  this._matMulti.dispose();
    }
}

class Game {
    constructor() {
        this._scene = new SceneManager('canvas-container');
        this._input = new InputManager();
        this._hud = new HUD();
        this._ranking = new RankingManager(5);
        this._player = new Player(this._scene.scene);
        this._pool = new ArcoPool(this._scene.scene, ARCOS_NO_POOL);

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
        for (let i = 0; i < 4; i++) {
            this._pool.ativar(-20 - i * 30, NIVEL_INICIAL);
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

    _aplicarPowerup(tipo) {
        if (tipo === 'vida') {
            this._vidas++;
            this._hud.atualizarVidas(this._vidas);
        } else {
            this._powerup.ativar(tipo);
            const nomes = { invencivel: '⚡ Invencível', multi: `✖️ x${MULTI_VALOR}` };
            this._hud.atualizarPowerup(nomes[tipo], this._powerup.tempoRestante);
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
                const nomes = { invencivel: '⚡ Invencível', multi: `✖️ x${MULTI_VALOR}` };
                this._hud.atualizarPowerup(nomes[this._powerup.tipo], this._powerup.tempoRestante);
            }

            this._player.processarInput(this._input.estado);

            const resultado = this._pool.atualizar(
                this._velocidadeZ, this._player, this._nivelDificuldade, this._powerup
            );

            if (resultado === 'SUCESSO') {
                this._pontos += 1 * this._powerup.multiplicador;
                this._hud.atualizar(this._pontos);
            } else if (resultado && resultado.powerup) {
                this._aplicarPowerup(resultado.powerup);
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