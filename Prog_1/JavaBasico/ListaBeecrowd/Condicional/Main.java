package Prog_1.JavaBasico.ListaBeecrowd.Condicional;

import java.util.Scanner;

public class Main{
    public static void main(String [] args){
        Scanner entrada = new Scanner(System.in);

        int valor;

        valor = entrada.nextInt();

        if (valor < 0){
            System.out.print(("O número digitado (" + valor + ") é negativo."));
        }
        else{
            if (valor > 0){
                System.out.print("O número digitado (" + valor + ") é positivo.");
            }
            else{
                    System.out.print("O número digitado é igual a zero.");
            }
        }

        entrada.close();
    }
}
