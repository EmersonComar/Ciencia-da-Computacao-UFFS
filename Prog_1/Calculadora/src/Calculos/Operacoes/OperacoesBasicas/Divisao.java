package Calculos.Operacoes.OperacoesBasicas;

import Calculos.Operacoes.Operacao;

public class Divisao extends Operacao{

    @Override
    public double executar(double x, double y, int precisao) {
        return truncarValor(x/y, precisao);
    }
     
}
