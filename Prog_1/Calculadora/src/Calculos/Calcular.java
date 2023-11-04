package Calculos;

import Calculos.Operacoes.Operacao;
import Calculos.Operacoes.OperacoesBasicas.*;

public class Calcular {
    public static double soma(double valor1, double valor2, int precisao){
        Operacao soma = new Soma();
        double resultado = soma.executar(valor1, valor2, precisao);
        return resultado;
    }

    public static double subtracao(double valor1, double valor2, int precisao){
        Operacao Subtracao = new Subtracao();
        double resultado = Subtracao.executar(valor1, valor2, precisao);
        return resultado;
    }

    public static double divisao(double valor1, double valor2, int precisao){
        Operacao Divisao = new Divisao();
        double resultado = Divisao.executar(valor1, valor2, precisao);
        return resultado;
    }

    public static double multiplicacao(double valor1, double valor2, int precisao){
        Operacao Multiplicacao = new Multiplicacao();
        double resultado = Multiplicacao.executar(valor1, valor2, precisao);
        return resultado;
    }
}
