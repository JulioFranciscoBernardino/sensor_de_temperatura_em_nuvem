let temperature = parseFloat(msg.payload.temperature);

// Verifique se o valor é um número válido
if (isNaN(temperature)) {
    temperature = 0; // Ou qualquer valor padrão que faça sentido para você
}

// Formatar o valor como uma string numérica
const values = [{
    "dataPointId": "DP-Temperatura",
    "qualityCode": "0",
    "value": temperature.toFixed(2) // Converte o número para uma string com duas casas decimais
}];

// Criar um novo objeto Date para o timestamp
msg._time = new Date(); // Cria um objeto Date válido
msg.payload = values;
return msg;
