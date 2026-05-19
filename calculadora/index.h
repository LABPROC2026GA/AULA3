R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Calculadora ESP32</title>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; background-color: #7f7f7f; padding-top: 30px; }
        .container { background: white; padding: 20px; border-radius: 10px; display: inline-block; box-shadow: 0px 0px 10px rgba(0,0,0,0.1); }
        input, select, button { padding: 10px; margin: 10px; font-size: 16px; border-radius: 5px; border: 1px solid #ccc; }
        button { background-color: #000000; color: white; cursor: pointer; border: none; font-weight: bold; }
        button:hover { background-color: #c0392b; }
        #resultado { font-size: 22px; font-weight: bold; margin-top: 15px; color: #2c3e50; }
    </style>
</head>
<body>
    <div class="container">
        <h2>Calculadora 4-Bits</h2>
        
        <input type="text" id="op1"  maxlength="4" placeholder="Operando A">
        
        <select id="operacao">
            <option value="soma">Somar</option>
            <option value="sub">Subtrair</option>
        </select>
        
        <input type="number" id="op2" maxlength="4" placeholder="Operando B">
        
        <br>
        <button onclick="enviarParaOESP32()">Calcular</button>
        
        <div id="resultado">Resultado:</div>
    </div>

    <script>
        function enviarParaOESP32() {
            let a = document.getElementById('op1').value;
            let b = document.getElementById('op2').value;
            let op = document.getElementById('operacao').value;

            alert("Simulação: Enviando para o ESP32 -> /calcula?a=" + a + "&b=" + b + "&op=" + op);

            let regexBinario = /^[01]+$/;

            if(!regexBinario.test(a) || !regexBinario.test(b) || binA === "" || binB === "") {
                alert("Erro: Digite apenas números binários válidos (zeros e uns) de até 4 bits.");
                return;
            }

            fetch(`/calcula?a=${a}&b=${b}&op=${op}`)
                .then(response => {
                    if (!response.ok) {
                        return response.text().then(textoDeErro => {
                            alert(textoDeErro);
                            document.getElementById('resultado').innerText = "Resultado: OVERFLOW";
                            throw new Error('Overflow detectado');
                        });
                    }
                    return response.text();
                })
                .then(resultadoDoMcu => {
                    if(resultadoDoMcu) {
                        document.getElementById('resultado').innerText = "Resultado (Decimal): " + resultadoDoMcu;
                    }
                })
                .catch(err => console.log(err.message));
        }
    </script>
</body>
</html>
)rawliteral"