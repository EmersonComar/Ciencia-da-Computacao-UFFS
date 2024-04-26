package Prog_1.JavaBasico.ListaBeecrowd.LeituraDadosFormatacao;

import java.util.Scanner;

public class Main{
    public static void main(String [] args){
        Scanner entrada = new Scanner(System.in);

        int val1, val2;
        String texto;

        texto = entrada.nextLine();

        val1 = Integer.parseInt(texto.split(" ")[0]);
        val2 = Integer.parseInt(texto.split(" ")[1]);

        System.out.printf("%.2f", ((float) val1/val2));

        entrada.close();
    }
}
