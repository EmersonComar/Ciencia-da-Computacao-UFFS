package Apresentacao;

import Calculos.Calcular;
import Calculos.Operacoes.Operacao;
import Calculos.Operacoes.OperacoesBasicas.Soma;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.Spinner;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;

public class CalculadoraController {

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
    void calcularResultado(ActionEvent event) {
        double primeiroValor = Double.parseDouble(txfPrimeiroValor.getText());
        double segundoValor = Double.parseDouble(txfSegundoValor.getText());
        Operacao soma = new Soma();
        double resultado = Calcular.realizarOperacao(soma, primeiroValor, segundoValor, 5);
        
        txaResultado.setText(String.valueOf(resultado));
    }

    @FXML
    void copiarResultado(ActionEvent event) {

    }

    @FXML
    void limparResultado(ActionEvent event) {
        txaResultado.setText("");
    }

}
