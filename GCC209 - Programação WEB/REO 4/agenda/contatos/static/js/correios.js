$('#id_cep').change(function() {
    const cep = this.value;
    
    $.ajax({
        url: `https://viacep.com.br/ws/${cep}/json`,
        dataType: 'jsonp',
        crossDomain: true,
        contentType: "application/json",
        statusCode: {
            200: function(data) { 
                $("#id_cep").attr("value", data.cep);
                $("#id_logradouro").attr("value", data.logradouro);
                $("#id_complemento").attr("value", data.complemento)
                $("#id_bairro").attr("value", data.bairro);
                $("#id_estado").attr("value", data.uf);
                $("#id_cidade").attr("value", data.localidade);
            }
        }
    });
});