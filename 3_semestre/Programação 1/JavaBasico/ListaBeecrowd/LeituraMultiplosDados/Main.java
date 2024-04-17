package Prog_1.JavaBasico.ListaBeecrowd.LeituraMultiplosDados;

import java.util.Scanner;

public class Main{
    public static void main(String [] args){
        Scanner entrada = new Scanner(System.in);

        int total;
        String valores;

        total = entrada.nextInt();
        entrada.nextLine();
        valores = entrada.nextLine();

        System.out.println(valores);
        for (int i=0; i < total; i++){
            System.out.println(valores.split(" ")[i]);
        }

        entrada.close();
    }
}
