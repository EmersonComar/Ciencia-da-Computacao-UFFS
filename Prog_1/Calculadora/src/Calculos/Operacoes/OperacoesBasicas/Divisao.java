package Calculos.Operacoes.OperacoesBasicas;

import Calculos.Operacoes.Operacao;

public class Divisao extends Operacao{

    public Divisao() {
        super("/");
        
    }

    @Override
    public double executar(int x, int y) {
        return x/y;
    }

    @Override
    public double executar(double x, double y) {
        return truncarValor(x/y, 2);
    }

    @Override
    public double executar(double x, double y, int precisao) {
        return truncarValor(x/y, precisao);
    }
     
}
