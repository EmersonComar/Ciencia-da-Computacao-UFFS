package Apresentacao;

import Calculos.Calcular;
import Calculos.Operacoes.Operacao;
import Calculos.Operacoes.OperacoesBasicas.*;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.Spinner;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.control.Alert.AlertType;

public class CalculadoraController extends Exception{

    @FXML
    private Button bntCalcular;

    @FXML
    private Button bntCopiar;

    @FXML
    private Button bntLimpar;

    @FXML
    private ChoiceBox<?> chbOperacao;

    @FXML
    private Spinner<?> spnPrecisao;

    @FXML
    private TextArea txaResultado;

    @FXML
    private TextField txfPrimeiroValor;

    @FXML
    private TextField txfSegundoValor;

    @FXML
    void calcularResultado(ActionEvent event){
        try {
            double primeiroValor = Double.parseDouble(txfPrimeiroValor.getText());
            double segundoValor = Double.parseDouble(txfSegundoValor.getText());
            Operacao soma = new Soma();
            double resultado = Calcular.realizarOperacao(soma, primeiroValor, segundoValor, 5);    
            txaResultado.setText(String.valueOf(resultado));
        } catch (NumberFormatException e) {
            Alert alerta = new Alert(AlertType.ERROR);
            exibirAlertas(alerta, "Tipos incorretos", "Digite apenas valores numéricos");
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
