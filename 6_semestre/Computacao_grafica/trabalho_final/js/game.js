// Constantes físicas globais
const RAIO_BOLA          = 0.4;
const RAIO_INTERNO_ARCO  = 1.2;
const RAIO_EXTERNO_ARCO  = 1.6;
const ARCOS_NO_POOL      = 6;
const LIMITE_DISPERSAO   = 3;
const RANKING_KEY        = 'radarcos';

const VELOCIDADE_INICIAL  = 0.18; 
const VELOCIDADE_MAXIMA   = 0.55;  
const TEMPO_ESCALA        = 90000; 
const NIVEL_INICIAL       = 1.0;   

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
        this._elHUD = document.getElementById('hud');
        this._elPontos = document.getElementById('hud-pontos');
    }

    mostrar(visivel) {
        this._elHUD.style.display = visivel ? 'block' : 'none';
    }

    atualizar(pontos) {
        this._elPontos.textContent = pontos;
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

class ArcoPool {
    constructor(scene, tamanho) {
        this._scene = scene;

        this._geo = new THREE.TorusGeometry(
            RAIO_INTERNO_ARCO,
            (RAIO_EXTERNO_ARCO - RAIO_INTERNO_ARCO) / 2,
            8, 24
        );
        this._matAzul = new THREE.MeshStandardMaterial({ color: 0x00aaff });
        this._matVerde = new THREE.MeshStandardMaterial({ color: 0x00ff00 });

        this._pool = [];
        for (let i = 0; i < tamanho; i++) {
            const mesh = new THREE.Mesh(this._geo, this._matAzul);
            mesh.visible = false;
            mesh.userData = { ativo: false, passou: false };
            scene.add(mesh);
            this._pool.push(mesh);
        }

        this._ativos = [];
    }

    ativar(posZ, nivelDificuldade) {
        const mesh = this._pool.find(m => !m.userData.ativo);
        if (!mesh) return;

        const maxDisp = Math.min(LIMITE_DISPERSAO, 1 + nivelDificuldade * 0.4);
        mesh.position.set(
            (Math.random() - 0.5) * maxDisp * 2,
            (Math.random() - 0.5) * maxDisp * 2,
            posZ
        );
        mesh.material = this._matAzul;
        mesh.userData.ativo = true;
        mesh.userData.passou = false;
        mesh.visible = true;
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

    atualizar(velocidadeZ, player, nivelDificuldade) {
        let resultado = null;

        for (let i = this._ativos.length - 1; i >= 0; i--) {
            const arco = this._ativos[i];
            arco.position.z += velocidadeZ;
            if (!arco.userData.passou && arco.position.z >= player.posZ) {
                const dx = player.posX - arco.position.x;
                const dy = player.posY - arco.position.y;
                const dist = Math.sqrt(dx * dx + dy * dy);

                const limiteSucesso = RAIO_INTERNO_ARCO - RAIO_BOLA;
                const limiteFalhaExt = RAIO_EXTERNO_ARCO + RAIO_BOLA;

                if (dist <= limiteSucesso) {
                    arco.userData.passou = true;
                    arco.material = this._matVerde;
                    resultado = 'SUCESSO';
                } else if (dist <= limiteFalhaExt) {
                    resultado = 'GAMEOVER';
                    return resultado;
                }
            }

            if (arco.position.z > 5) {
                this._desativar(arco);
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
        this._geo.dispose();
        this._matAzul.dispose();
        this._matVerde.dispose();
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

        this._estado = null;
        this._pontos = 0;
        this._velocidadeZ = 0.3;
        this._nivelDificuldade = 1;
        this._tempoDecorrido = 0;

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
        this._pontos              = 0;
        this._velocidadeZ         = VELOCIDADE_INICIAL;
        this._nivelDificuldade    = NIVEL_INICIAL;
        this._tempoDecorrido      = 0;

        this._player.moverParaJogo();
        this._hud.atualizar(this._pontos);

        this._pool.desativarTodos();
        // Espaçamento fixo de 30 unidades entre arcos iniciais
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

    _loop() {
        requestAnimationFrame(() => this._loop());

        if (this._estado === 'JOGANDO') {
            this._tempoDecorrido   += 16.66;

            // Curva de dificuldade suave:
            //   t=0s  → nível 1.00 → vel 0.18 u/frame
            //   t=30s → nível 1.33 → vel 0.24 u/frame
            //   t=60s → nível 1.67 → vel 0.30 u/frame
            //   t=90s → nível 2.00 → vel 0.36 u/frame (cap: 0.55)
            this._nivelDificuldade = NIVEL_INICIAL + this._tempoDecorrido / TEMPO_ESCALA;
            this._velocidadeZ      = Math.min(
                VELOCIDADE_INICIAL * this._nivelDificuldade,
                VELOCIDADE_MAXIMA
            );

            this._player.processarInput(this._input.estado);

            const resultado = this._pool.atualizar(this._velocidadeZ, this._player, this._nivelDificuldade);

            if (resultado === 'SUCESSO') {
                this._pontos += 1;
                this._hud.atualizar(this._pontos);
            } else if (resultado === 'GAMEOVER') {
                this.mudarEstado('GAMEOVER');
            }
        }

        this._scene.render();
    }
}

window.addEventListener('DOMContentLoaded', () => {
    new Game();
});