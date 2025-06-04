const express = require('express');
const cors = require('cors');


const app = express();
app.use(express.json());
app.use(cors({
    origin: 'http://127.0.0.1:5500'
}));

app.get('/', (req, res) => {
    res.send('Mano. Bora vazer esses trem\n');
});

app.post('/calcular-salario', (req, res) => {
    const { horas, valorHora } = req.body;
    const salario = (horas <= 200)? horas * valorHora: horas * valorHora * 1.05;
    res.send(`Horas trabalhadas: ${horas}\nValor da hora: ${valorHora.toFixed(2)}\nSalário: ${salario.toFixed(2)}\n`);
});

app.post('/comprar-produto', (req, res) => {
    const { preco, formaPagamento } = req.body;
    let precoFinal;
    
    if (formaPagamento === 1) {
        precoFinal = preco * 0.95;
    } else if (formaPagamento === 2) {
        precoFinal = preco * 1.1;
    } else {
        return res.status(400).json({
            error: "Forma de pagamento inválida. Utilize 1 (à vista) ou 2 (parcelado)."
        })
    }

    res.json({
        preco: preco.toFixed(2),
        formaPagamento,
        precoFinal: precoFinal.toFixed(2)
    });
});

app.post('/horario-evento', (req, res) => {
    const { inicio, fim } = req.body;
    if(inicio < 0 || inicio > 23 || fim < 0 || fim > 23){
        return res.status(400).json({
            error: "Os valores de inicio e fim devem estar entre 0h e 23h"
        })
    }

    const duracao = (fim > inicio)? fim - inicio: (24 - inicio) + fim;

    res.json({
        "inicio": inicio,
        "fim": fim,
        "duracao": duracao
    });
});

app.listen(3001, () => {
    console.log('Servidor rodando na porta 3001');
});