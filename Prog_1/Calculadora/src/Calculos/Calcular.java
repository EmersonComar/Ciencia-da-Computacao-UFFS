package Calculos;

import Calculos.Operacoes.Operacao;

public class Calcular {
    public static double realizarOperacao(Operacao operacao, double primeiroValor, double segundoValor, int precisao){
        return operacao.executar(primeiroValor, segundoValor, precisao);
    }
}
