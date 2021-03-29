//---------------------------

var express = require('express');
var bodyParser = require('body-parser');

var app = express();
app.use(bodyParser.json());
//app.use(bodyParser.urlencoded({
//	extended: true
//}));

app.listen(5000);

//---------------------------

// Lista de carros
var carros = [
  { fabricante: 'Volkswagen', modelo: 'Jetta', ano: 2013, automatico: true, preco: 56000.00 },
  { fabricante: 'Chevrolet', modelo: 'Cruze', ano: 2016, automatico: false, preco: 70000.50 },
];

// exemplo de um carro no formato JSON
//{ "fabricante": "Ford", "modelo": "Ka", "ano": 2010, "automatico": false, "preco": 11000}

//---------------------------

app.get('/', function (req, res) {
	res.end('Bem vindo API Carros!');
})

app.get('/carros', function (req, res) {
	res.json(carros);
})

app.get('/carros/:id', function(req, res) {
	var id = req.params.id;
	if (id >= 0 && id < carros.length)
		res.json(carros[id]);
	else
		res.status(500).json({status: 'erro', message: "id invalido"});
})

app.post('/carros', function (req, res) {
	var carro = req.body;
	carros[carros.length] = carro;
	res.json(carros[carros.length-1]);  
})

app.delete('/carros/:id', function(req, res) {
	var id = req.params.id;
	if (id >= 0 && id < carros.length) {
		carros.splice(id, 1)
		res.json(carros);
	}
	else
		res.status(500).json({status: 'erro', message: "id invalido"});
})

app.get('/carros/count', function (req, res) {
	res.end(carros.length.toString());
})

app.get('/carros/menorpreco', function (req, res) {
	var menorID = 0;
	var menorPreco = carros[0].preco;
	for (i = 0; i < carros.length; i++) { 
    	if (carros[i].preco < menorPreco) {
    		menorID = i;
    		menorPreco = carros[i].preco;
    	}
	}
	res.json(carros[menorID]);
})



