package Calculos.Operacoes;

public abstract class Operacao {

    public abstract double executar(double x, double y, int precisao);

    public double truncarValor(double x, int precisao){
        if (precisao > 10){
            precisao = 10;
        }
        double escala = Math.pow(10, precisao);
        long aux = (long)(x * escala);
        return (double) aux/escala;
    }

}
