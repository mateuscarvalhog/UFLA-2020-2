const controller = require('./tarefas-controller');

const express = require('express');
const bodyParser = require('body-parser');
const router = express.Router();
const mongoose = require('mongoose');

mongoose.connect('mongodb+srv://neumar:gcc129@cluster0.6ywka.mongodb.net/myFirstDatabase?retryWrites=true&w=majority', { useNewUrlParser: true, useUnifiedTopology: true });
mongoose.Promise = global.Promise;
try {
    let db = mongoose.connection;
    db.on('errr', console.error.bind(console, "database connection error"));
} catch {
    console.log(e);
}

const app = express();
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
app.use('/', router);

let port = process.env.PORT || 5000;
app.listen(port, () => {
    console.log("Server executing on port " + port);
});

app.get('/', (req, res) => {
    res.send("Operações disponíveis: https://app.swaggerhub.com/apis-docs/neumar/Tarefas/1.0.0#/default");
});

router.get('/tarefas/:id', controller.buscarTarefa);
router.delete('/tarefas/:id', controller.excluirTarefa);
router.put('/tarefas/:id', controller.atualizarTarefa);
router.post('/tarefas', controller.cadastrarTarefa);
router.get('/tarefas', controller.listarTarefas);