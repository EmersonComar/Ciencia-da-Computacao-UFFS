package Apresentacao;

import java.net.URL;
import java.util.ResourceBundle;

import Calculos.Operacoes.Operacao;
import Calculos.Operacoes.OperacoesBasicas.*;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.Spinner;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.control.Alert.AlertType;

public class CalculadoraController extends Exception implements Initializable{

    @FXML
    private Button bntCalcular;

    @FXML
    private Button bntCopiar;

    @FXML
    private Button bntLimpar;

    @FXML
    private ChoiceBox<String> chbOperacao;

    @FXML
    private Spinner<?> spnPrecisao;

    @FXML
    private TextArea txaResultado;

    @FXML
    private TextField txfPrimeiroValor;

    @FXML
    private TextField txfSegundoValor;
    
    @Override
    public void initialize(URL location, ResourceBundle resources) {
        String[] operacoes = {"Soma", "Subtração", "Multiplicação", "Divisão"};
        chbOperacao.getItems().addAll(operacoes);
        chbOperacao.setValue(operacoes[0]);
    }


    @FXML
    void calcularResultado(ActionEvent event){
        try {
            String tipoOperacao = chbOperacao.getValue();
            Operacao operacao = new Soma();

            switch (tipoOperacao) {
                case "Soma" -> {operacao = new Soma();}
                case "Subtração" -> {operacao = new Subtracao();}
                case "Multiplicação" -> {operacao = new Multiplicacao();}
                case "Divisão" -> {operacao = new Divisao();}  
            }

            double primeiroValor = Double.parseDouble(txfPrimeiroValor.getText());
            double segundoValor = Double.parseDouble(txfSegundoValor.getText());
            double resultado = operacao.executar(primeiroValor, segundoValor, 5);

            txaResultado.setText(String.valueOf(resultado));
            
        } catch (NumberFormatException e) {
            Alert alerta = new Alert(AlertType.ERROR);
            exibirAlertas(alerta, "Valor inválido", "Digite apenas valores numéricos.");
        }
    }

    @FXML
    void copiarResultado(ActionEvent event) {

    }

    @FXML
    void limparResultado(ActionEvent event) {
        txaResultado.setText("");
    }

    private static void exibirAlertas(Alert alerta, String titulo, String mensagem){
        alerta.setTitle(titulo);
        alerta.setHeaderText(null);
        alerta.setContentText(mensagem);
        alerta.showAndWait();
    }


}


