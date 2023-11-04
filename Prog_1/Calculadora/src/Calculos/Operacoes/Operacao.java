package Calculos.Operacoes;

public abstract class Operacao {
    private String simbolo;

    public Operacao(String simbolo){
        this.simbolo = simbolo;
    }

    public String getSimbolo(){
        return this.simbolo;
    }

    public abstract double executar(int x, int y);
    public abstract double executar(double x, double y);
    public abstract double executar(double x, double y, int precisao);

    public double truncarValor(double x, int precisao){
        if (precisao > 10){
            precisao = 10;
        }
        double escala = Math.pow(10, precisao);
        long aux = (long)(x * escala);
        return (double) aux/escala;
    }

    @Override
    public String toString(){
        return " " + this.simbolo + " ";
    }
}
