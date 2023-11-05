package Prog_1.JavaBasico.ListaBeecrowd.LeituraDados;

import java.util.Scanner;

public class Main{
    public static void main(String [] args){
        Scanner entrada = new Scanner(System.in);
        String frase;

        frase = entrada.nextLine();
        System.out.println(frase);
        entrada.close();
    }
}